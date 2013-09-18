//Based on SnifferSSLSocketFactory.java from The Grinder distribution.
// The Grinder distribution is available at http://grinder.sourceforge.net/

package mitm;

import iaik.asn1.ObjectID;
import iaik.asn1.structures.AlgorithmID;
import iaik.asn1.structures.Name;

import java.io.FileInputStream;
import java.io.IOException;
import java.math.BigInteger;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.GeneralSecurityException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.SecureRandom;
import java.security.cert.X509Certificate;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.net.ServerSocketFactory;
import javax.net.SocketFactory;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

/**
 * MITMSSLSocketFactory is used to create SSL sockets.
 * 
 * This is needed because the javax.net.ssl socket factory classes don't allow
 * creation of factories with custom parameters.
 * 
 */
public final class MITMSSLSocketFactory implements MITMSocketFactory
{
   /**
    * We're carrying out a MITM attack, we don't care whether the cert chains
    * are trusted or not ;-)
    * 
    */
   private static class TrustEveryone implements X509TrustManager
   {
      @Override
      public void checkClientTrusted(X509Certificate[] chain,
                                     String authenticationType)
      {
      }

      @Override
      public void checkServerTrusted(X509Certificate[] chain,
                                     String authenticationType)
      {
      }

      @Override
      public X509Certificate[] getAcceptedIssuers()
      {
         // JRR - I think this needs to be written to return valid certificates
         return null;
      }
   }

   final ServerSocketFactory m_serverSocketFactory;
   final SocketFactory       m_clientSocketFactory;

   final SSLContext          m_sslContext;

   /*
    * 
    * We can't install our own TrustManagerFactory without messing with the
    * security properties file. Hence we create our own SSLContext and
    * initialise it. Passing null as the keystore parameter to SSLContext.init()
    * results in a empty keystore being used, as does passing the key manager
    * array obtain from keyManagerFactory.getInstance().getKeyManagers(). To
    * pick up the "default" keystore system properties, we have to read them
    * explicitly. UGLY, but necessary so we understand the expected properties.
    */

   public KeyStore           ks = null;

   /**
    * This constructor will create an SSL server socket factory that is
    * initialized with a fixed CA certificate
    */
   public MITMSSLSocketFactory() throws IOException, GeneralSecurityException
   {
      this.m_sslContext = SSLContext.getInstance("SSL");

      final KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());

      final String keyStoreFile = System.getProperty(JSSEConstants.KEYSTORE_PROPERTY);
      final char[] keyStorePassword = System.getProperty(JSSEConstants.KEYSTORE_PASSWORD_PROPERTY,
                                                         "")
                                            .toCharArray();
      final String keyStoreType = System.getProperty(JSSEConstants.KEYSTORE_TYPE_PROPERTY,
                                                     "jks");

      final KeyStore keyStore;

      if(keyStoreFile != null)
      {
         keyStore = KeyStore.getInstance(keyStoreType);
         keyStore.load(new FileInputStream(keyStoreFile), keyStorePassword);

         this.ks = keyStore;
      }
      else
      {
         keyStore = null;
      }

      keyManagerFactory.init(keyStore, keyStorePassword);

      this.m_sslContext.init(keyManagerFactory.getKeyManagers(),
                             new TrustManager[]{new TrustEveryone()},
                             null);

      this.m_clientSocketFactory = this.m_sslContext.getSocketFactory();
      this.m_serverSocketFactory = this.m_sslContext.getServerSocketFactory();
   }

   /**
    * This constructor will create an SSL server socket factory that is
    * initialized with a dynamically generated server certificate that contains
    * the specified common name.
    */
   public MITMSSLSocketFactory(String remoteServerIssuer,
                               String remoteServerSubject, 
                               BigInteger serialno) throws IOException,
                                                                    GeneralSecurityException,
                                                                    Exception
   {
      // Call the default constructor above
      // this();

      // JRR - Begin Additions
      
      // Get a calendar
      GregorianCalendar calendar = new GregorianCalendar();
      
      // Back up the calendar by 3 days
      calendar.add(Calendar.DAY_OF_YEAR, -3);
      
      // Create keypair
      KeyPairGenerator keypair_generator = KeyPairGenerator.getInstance("RSA");
      keypair_generator.initialize(1024, new SecureRandom());
      KeyPair keypair = keypair_generator.generateKeyPair();
      
      // Parse out the issuer information
      // Only parse out "CN", "O", and "C"
      // CN first
      Pattern pattern = Pattern.compile("^CN=([^,]*).*",
                                           Pattern.DOTALL);
      Matcher matcher = pattern.matcher(remoteServerIssuer);
      matcher.find();
      String common_name = matcher.group(1);
      
      // Now O
      pattern = Pattern.compile("O=([^,]*)",
                                        Pattern.DOTALL);
      matcher = pattern.matcher(remoteServerIssuer);
      matcher.find();
      String organization = matcher.group(1);
      
      // Now C
      pattern = Pattern.compile("C=([^,]*)",
                                        Pattern.DOTALL);
      matcher = pattern.matcher(remoteServerIssuer);
      matcher.find();
      String country = matcher.group(1);
      
      // Create certificate issuer
      Name issuer = new Name();
      issuer.addRDN(ObjectID.country, country);
      issuer.addRDN(ObjectID.organization, organization);
      issuer.addRDN(ObjectID.commonName, common_name);
      
      System.out.println(issuer.toString());
      
      // Parse out the subject information
      // (Shouldn't there be an easier way than this?)
      // Only parse out "CN", "O", and "C"
      // CN first
      pattern = Pattern.compile("^CN=([^,]*).*",
                                           Pattern.DOTALL);
      matcher = pattern.matcher(remoteServerSubject);
      matcher.find();
      common_name = matcher.group(1);
      
      // Now O
      pattern = Pattern.compile("O=([^,]*)",
                                        Pattern.DOTALL);
      matcher = pattern.matcher(remoteServerSubject);
      matcher.find();
      organization = matcher.group(1);
      
      // Now C
      pattern = Pattern.compile("C=([^,]*)",
                                        Pattern.DOTALL);
      matcher = pattern.matcher(remoteServerSubject);
      matcher.find();
      country = matcher.group(1);
      
      // Create a subject
      Name subject = new Name();
      subject.addRDN(ObjectID.country, country);
      subject.addRDN(ObjectID.organization, organization);
      subject.addRDN(ObjectID.commonName, common_name);
      
      System.out.println(subject.toString());
      
      // Create Certificate
      // From https://forums.oracle.com/thread/1538320
      iaik.x509.X509Certificate cert = new iaik.x509.X509Certificate();
      cert.setIssuerDN(issuer);
      cert.setSubjectDN(subject);
      cert.setSerialNumber(serialno); // Set the serial number
      cert.setPublicKey(keypair.getPublic()); // Set the public key
      
      // Set valid time to current time and date
      cert.setValidNotBefore(calendar.getTime());
      
      // Add six months to the calendar
      calendar.add(Calendar.MONTH, 6);
      
      // Set valid time to 6 months in future
      cert.setValidNotAfter(calendar.getTime());
      
      // Sign the certificate with the private key
      cert.sign(AlgorithmID.sha1WithRSAEncryption, keypair.getPrivate());
      
      // Output the certificate
      System.out.println("\nStart Generated Certificate....................................");
      System.out.println(cert.toString());
      System.out.println("End Generated Certificate......................................\n");
      
      // JRR - End Additions
      
      // Copied from default constructor above
      this.m_sslContext = SSLContext.getInstance("SSL");

      final KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());

      final String keyStoreFile = System.getProperty(JSSEConstants.KEYSTORE_PROPERTY);
      final char[] keyStorePassword = System.getProperty(JSSEConstants.KEYSTORE_PASSWORD_PROPERTY,
                                                         "")
                                            .toCharArray();
      final String keyStoreType = System.getProperty(JSSEConstants.KEYSTORE_TYPE_PROPERTY,
                                                     "jks");

      final KeyStore keyStore;

      if(keyStoreFile != null)
      {
         keyStore = KeyStore.getInstance(keyStoreType);
         keyStore.load(new FileInputStream(keyStoreFile), keyStorePassword);
         
         // JRR - Adding newly created certificate to the keystore
         keyStore.setCertificateEntry(common_name, cert);
         

         this.ks = keyStore;
      }
      else
      {
         keyStore = null;
      }

      keyManagerFactory.init(keyStore, keyStorePassword);

      this.m_sslContext.init(keyManagerFactory.getKeyManagers(),
                             new TrustManager[]{new TrustEveryone()},
                             null);

      this.m_clientSocketFactory = this.m_sslContext.getSocketFactory();
      this.m_serverSocketFactory = this.m_sslContext.getServerSocketFactory();
      
   }

   @Override
   public final Socket
            createClientSocket(String remoteHost, int remotePort) throws IOException
   {
      final SSLSocket socket = (SSLSocket)this.m_clientSocketFactory.createSocket(remoteHost,
                                                                                  remotePort);

      socket.setEnabledCipherSuites(socket.getSupportedCipherSuites());

      socket.startHandshake();

      return socket;
   }

   @Override
   public final ServerSocket createServerSocket(String localHost,
                                                int localPort,
                                                int timeout) throws IOException
   {
      final SSLServerSocket socket = (SSLServerSocket)this.m_serverSocketFactory.createServerSocket(localPort,
                                                                                                    50,
                                                                                                    InetAddress.getByName(localHost));

      socket.setSoTimeout(timeout);

      socket.setEnabledCipherSuites(socket.getSupportedCipherSuites());

      return socket;
   }
}
