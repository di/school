//Based on HTTPProxySnifferEngine.java from The Grinder distribution.
// The Grinder distribution is available at http://grinder.sourceforge.net/

package mitm;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InterruptedIOException;
import java.io.OutputStream;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLSocket;
import javax.security.auth.x500.X500Principal;

/**
 * HTTPS proxy implementation.
 * 
 * A HTTPS proxy client first send a CONNECT message to the proxy port. The
 * proxy accepts the connection responds with a 200 OK, which is the client's
 * queue to send SSL data to the proxy. The proxy just forwards it on to the
 * server identified by the CONNECT message.
 * 
 * The Java API presents a particular challenge: it allows sockets to be either
 * SSL or not SSL, but doesn't let them change their stripes midstream. (In
 * fact, if the JSSE support was stream oriented rather than socket oriented, a
 * lot of problems would go away). To hack around this, we accept the CONNECT
 * then blindly proxy the rest of the stream through a special ProxyEngine class
 * (ProxySSLEngine) which is instantiated to handle SSL.
 * 
 */
public class HTTPSProxyEngine extends ProxyEngine
{

   public int request_count = 0;
   public boolean shutdown_requested = false;
   
   /*
    * Used to funnel data between a client (e.g. a web browser) and a remote
    * SSLServer, that the client is making a request to.
    */
   private class ProxySSLEngine extends ProxyEngine
   {
      Socket remoteSocket = null;
      int    timeout      = 0;

      /*
       * NOTE: that port number 0, used below indicates a system-allocated,
       * dynamic port number.
       */
      ProxySSLEngine(MITMSSLSocketFactory socketFactory,
                     ProxyDataFilter requestFilter,
                     ProxyDataFilter responseFilter) throws IOException
      {
         super(socketFactory,
               requestFilter,
               responseFilter,
               new ConnectionDetails(HTTPSProxyEngine.this.getConnectionDetails()
                                                          .getLocalHost(),
                                     0,
                                     "",
                                     -1,
                                     true),
               0);
      }

      public final ServerSocket
               createServerSocket(String remoteServerIssuer,
                                  String remoteServerSubject,
                                  BigInteger serialno) throws IOException,
                                                      java.security.GeneralSecurityException,
                                                      Exception
      {
         // Calls our custom function to create a dynamic certificate
         MITMSSLSocketFactory ssf = new MITMSSLSocketFactory(remoteServerIssuer,
                                                             remoteServerSubject,
                                                             serialno);

         // you may want to consider caching this result for better performance
         this.m_serverSocket = ssf.createServerSocket("localhost",
                                                      0,
                                                      this.timeout);
         return this.m_serverSocket;
      }

      /*
       * localSocket.get[In|Out]putStream() is data that's (indirectly) being
       * read from / written to the client.
       * 
       * m_tempRemoteHost is the remote SSL Server.
       */
      @Override
      public void run()
      {
         try
         {
            final Socket localSocket = this.getServerSocket().accept();

            System.err.println("New proxy proxy connection to " + HTTPSProxyEngine.this.m_tempRemoteHost
                     + ":"
                     + HTTPSProxyEngine.this.m_tempRemotePort);

            this.launchThreadPair(localSocket,
                                  this.remoteSocket,
                                  localSocket.getInputStream(),
                                  localSocket.getOutputStream(),
                                  HTTPSProxyEngine.this.m_tempRemoteHost,
                                  HTTPSProxyEngine.this.m_tempRemotePort);
         }
         catch(IOException e)
         {
            e.printStackTrace(System.err);
         }
      }

      public final void setRemoteSocket(Socket s)
      {
         this.remoteSocket = s;
      }
   }

   public static final String   ACCEPT_TIMEOUT_MESSAGE = "Listen time out";
   private String               m_tempRemoteHost;

   private int                  m_tempRemotePort;

   private final Pattern        m_httpsConnectPattern;

   private final ProxySSLEngine m_proxySSLEngine;

   public HTTPSProxyEngine(MITMPlainSocketFactory plainSocketFactory,
                           MITMSSLSocketFactory sslSocketFactory,
                           ProxyDataFilter requestFilter,
                           ProxyDataFilter responseFilter,
                           String localHost,
                           int localPort,
                           int timeout) throws IOException,
                                       PatternSyntaxException
   {
      // We set this engine up for handling plain HTTP and delegate
      // to a proxy for HTTPS.
      super(plainSocketFactory,
            requestFilter,
            responseFilter,
            new ConnectionDetails(localHost, localPort, "", -1, false),
            timeout);

      this.m_httpsConnectPattern = Pattern.compile("^CONNECT[ \\t]+([^:]+):(\\d+).*\r\n\r\n",
                                                   Pattern.DOTALL);

      // When handling HTTPS proxies, we use our plain socket to
      // accept connections on. We suck the bit we understand off
      // the front and forward the rest through our proxy engine.
      // The proxy engine listens for connection attempts (which
      // come from us), then sets up a thread pair which pushes data
      // back and forth until either the server closes the
      // connection, or we do (in response to our client closing the
      // connection). The engine handles multiple connections by
      // spawning multiple thread pairs.

      assert sslSocketFactory != null;
      this.m_proxySSLEngine = new ProxySSLEngine(sslSocketFactory,
                                                 requestFilter,
                                                 responseFilter);

   }

   @Override
   public void run()
   {
      // Should be more than adequate.
      final byte[] buffer = new byte[40960];

      while(!this.shutdown_requested)
      {
         try
         {
            // Plaintext Socket with client (i.e. browser)
            final Socket localSocket = this.getServerSocket().accept();

            // Grab the first plaintext upstream buffer, which we're hoping is
            // a CONNECT message.
            final BufferedInputStream in = new BufferedInputStream(localSocket.getInputStream(),
                                                                   buffer.length);

            in.mark(buffer.length);

            // Read a buffer full.
            final int bytesRead = in.read(buffer);

            final String line = bytesRead > 0 ? new String(buffer,
                                                           0,
                                                           bytesRead,
                                                           "US-ASCII") : "";

            final Matcher httpsConnectMatcher = this.m_httpsConnectPattern.matcher(line);

            // 'grep' for CONNECT message and extract the remote server/port
            if(httpsConnectMatcher.find())
            {
               // then we have a proxy CONNECT message!
               // Discard any other plaintext data the client sends us:
               while(in.read(buffer, 0, in.available()) > 0)
               {
               }

               final String remoteHost = httpsConnectMatcher.group(1);

               // Must be a port number by specification.
               final int remotePort = Integer.parseInt(httpsConnectMatcher.group(2));

               final String target = remoteHost + ":" + remotePort;

               System.err.println("******* Establishing a new HTTPS proxy connection to " + target);

               this.m_tempRemoteHost = remoteHost;
               this.m_tempRemotePort = remotePort;

               X509Certificate java_cert = null;
               SSLSocket remoteSocket = null;
               try
               {
                  // Lookup the "common name" field of the certificate from the
                  // remote server:
                  remoteSocket = (SSLSocket)this.m_proxySSLEngine.getSocketFactory()
                                                                 .createClientSocket(remoteHost,
                                                                                     remotePort);
               }
               catch(IOException ioe)
               {
                  ioe.printStackTrace();
                  // Try to be nice and send a reasonable error message to
                  // client
                  this.sendClientResponse(localSocket.getOutputStream(),
                                          "504 Gateway Timeout",
                                          remoteHost,
                                          remotePort);
                  continue;
               }

               BigInteger serialno = null;

               // JRR - Begin Additions

               // Get HTTPS connection to remote host
               // From
               // http://stackoverflow.com/questions/7199129/how-to-get-server-certificate-chain-then-verify-its-valid-and-trusted-in-java
               URL remote_url = new URL("https://" + remoteHost);
               HttpsURLConnection connection = (HttpsURLConnection)remote_url.openConnection();
               connection.connect();

               // Get certificate from server
               Certificate[] certs = connection.getServerCertificates();
               X509Certificate cert = (X509Certificate)certs[0];

               // Close the connection
               connection.disconnect();

               // Get serial number
               serialno = cert.getSerialNumber();

               // Get CN (Is this subject (google) or issuer (geotrust)?)
               // I think that we need both the subject and issuer to get passed
               // in to the factory,
               // and parse out the information in there.

               // Get issuer information
               X500Principal principal = cert.getIssuerX500Principal(); // cert.getSubjectX500Principal();
               String issuer = principal.getName();
               
               // Get subject information
               principal = cert.getSubjectX500Principal();
               String subject = principal.getName();

               // Output the remote certificate
               System.out.println("\nStart Remote Certificate....................................");
               System.out.println("Version: " + cert.getVersion());
               System.out.println("Issuer: " + issuer);
               System.out.println("Subject: " + subject);
               System.out.println("Serial Number: " + serialno);
               System.out.println("End Remote Certificate......................................\n");
               
               // JRR - End Additions

               // We've already opened the socket, so might as well keep using
               // it:
               this.m_proxySSLEngine.setRemoteSocket(remoteSocket);

               // This is a CRUCIAL step: we dynamically generate a new cert,
               // based
               // on the remote server's CN, and return a reference to the
               // internal
               // server socket that will make use of it.
               ServerSocket localProxy = this.m_proxySSLEngine.createServerSocket(issuer,
                                                                                  subject,
                                                                                  serialno);

               // Kick off a new thread to send/recv data to/from the remote
               // server.
               // Remote server's response data is made available via an
               // internal
               // SSLServerSocket. All this work is handled by the
               // m_proxySSLEngine:
               new Thread(this.m_proxySSLEngine, "HTTPS proxy SSL engine").start();

               try
               {
                  Thread.sleep(10);
               }
               catch(Exception ignore)
               {
               }

               // Create a new socket connection to our proxy engine.
               final Socket sslProxySocket = this.getSocketFactory()
                                                 .createClientSocket(this.getConnectionDetails()
                                                                         .getLocalHost(),
                                                                     localProxy.getLocalPort());

               // Now set up a couple of threads to punt
               // everything we receive over localSocket to
               // sslProxySocket, and vice versa.
               new Thread(new CopyStreamRunnable(in,
                                                 sslProxySocket.getOutputStream()),
                          "Copy to proxy engine for " + target).start();

               final OutputStream out = localSocket.getOutputStream();

               new Thread(new CopyStreamRunnable(sslProxySocket.getInputStream(),
                                                 out),
                          "Copy from proxy engine for " + target).start();

               // Send a 200 response to send to client. Client
               // will now start sending SSL data to localSocket.
               this.sendClientResponse(out, "200 OK", remoteHost, remotePort);
               
               // At this point, we consider the request successfully proxied, and increment the count for stats.
               this.request_count += 1;
            }
            else
            { // Not a CONNECT request.. nothing we can do.
               System.err.println("Failed to determine proxy destination from message:");
               System.err.println(line);
               this.sendClientResponse(localSocket.getOutputStream(),
                                       "501 Not Implemented",
                                       "localhost",
                                       this.getConnectionDetails()
                                           .getLocalPort());
            }
         }
         catch(InterruptedIOException e)
         {
            System.err.println(ACCEPT_TIMEOUT_MESSAGE);
            break;
         }
         catch(Exception e)
         {
            e.printStackTrace(System.err);
         }
      }
   }

   private void sendClientResponse(OutputStream out,
                                   String msg,
                                   String remoteHost,
                                   int remotePort) throws IOException
   {
      final StringBuffer response = new StringBuffer();
      response.append("HTTP/1.0 ").append(msg).append("\r\n");
      response.append("Host: " + remoteHost + ":" + remotePort + "\r\n");
      response.append("Proxy-agent: CSE490K-MITMProxy/1.0\r\n");
      response.append("\r\n");
      out.write(response.toString().getBytes());
      out.flush();
   }

}
