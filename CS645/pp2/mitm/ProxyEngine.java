// JRR - No changes required here

package mitm;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public abstract class ProxyEngine implements Runnable
{

   public static final String      ACCEPT_TIMEOUT_MESSAGE = "Listen time out";
   private final ProxyDataFilter   m_requestFilter;
   private final ProxyDataFilter   m_responseFilter;
   private final ConnectionDetails m_connectionDetails;

   private final PrintWriter       m_outputWriter;

   public final MITMSocketFactory  m_socketFactory;
   protected ServerSocket          m_serverSocket;

   public ProxyEngine(MITMSocketFactory socketFactory,
                      ProxyDataFilter requestFilter,
                      ProxyDataFilter responseFilter,
                      ConnectionDetails connectionDetails,
                      int timeout) throws IOException
   {
      this.m_socketFactory = socketFactory;
      this.m_requestFilter = requestFilter;
      this.m_responseFilter = responseFilter;
      this.m_connectionDetails = connectionDetails;

      this.m_outputWriter = requestFilter.getOutputPrintWriter();

      this.m_serverSocket = this.m_socketFactory.createServerSocket(connectionDetails.getLocalHost(),
                                                                    connectionDetails.getLocalPort(),
                                                                    timeout);
   }

   // run() method from Runnable is implemented in subclasses

   protected final ConnectionDetails getConnectionDetails()
   {
      return this.m_connectionDetails;
   }

   public final ServerSocket getServerSocket()
   {
      return this.m_serverSocket;
   }

   protected final MITMSocketFactory getSocketFactory()
   {
      return this.m_socketFactory;
   }

   /*
    * Launch a pair of threads that: (1) Copy data sent from the client to the
    * remote server (2) Copy data sent from the remote server to the client
    */
   protected final void launchThreadPair(Socket localSocket,
                                         Socket remoteSocket,
                                         InputStream localInputStream,
                                         OutputStream localOutputStream,
                                         String remoteHost,
                                         int remotePort) throws IOException
   {

      new StreamThread(new ConnectionDetails(this.m_connectionDetails.getLocalHost(),
                                             localSocket.getPort(),
                                             remoteHost,
                                             remoteSocket.getPort(),
                                             this.m_connectionDetails.isSecure()),
                       localInputStream,
                       remoteSocket.getOutputStream(),
                       this.m_requestFilter,
                       this.m_outputWriter);

      new StreamThread(new ConnectionDetails(remoteHost,
                                             remoteSocket.getPort(),
                                             this.m_connectionDetails.getLocalHost(),
                                             localSocket.getPort(),
                                             this.m_connectionDetails.isSecure()),
                       remoteSocket.getInputStream(),
                       localOutputStream,
                       this.m_responseFilter,
                       this.m_outputWriter);
   }
}
