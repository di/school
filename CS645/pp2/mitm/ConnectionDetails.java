// This file is part of The Grinder software distribution. Refer to
// the file LICENSE which is part of The Grinder distribution for
// licensing details. The Grinder distribution is available on the
// Internet at http://grinder.sourceforge.net/

// JRR - No changes required here 

package mitm;

/**
 * ConnectionDetails represents the endpoints of a TCP connection, and whether
 * SSL is used.
 * 
 */
public class ConnectionDetails
{

   private final int m_hashCode;

   private String    m_localHost;
   private int       m_localPort;
   private String    m_remoteHost;
   private int       m_remotePort;
   private boolean   m_isSecure;

   /**
    * Creates a new ConnectionDetails instance.
    */
   public ConnectionDetails(String localHost,
                            int localPort,
                            String remoteHost,
                            int remotePort,
                            boolean isSecure)
   {
      this.m_localHost = localHost.toLowerCase();
      this.m_localPort = localPort;
      this.m_remoteHost = remoteHost.toLowerCase();
      this.m_remotePort = remotePort;
      this.m_isSecure = isSecure;

      this.m_hashCode = this.m_localHost.hashCode() ^ this.m_remoteHost.hashCode()
               ^ this.m_localPort
               ^ this.m_remotePort
               ^ (this.m_isSecure ? 0x55555555 : 0);
   }

   /**
    * Value based equality.
    * 
    * @param other
    *           an <code>Object</code> value
    * @return <code>true</code> => <code>other</code> is equal to this object.
    * 
    */
   @Override
   public boolean equals(Object other)
   {
      if(other == this)
      {
         return true;
      }

      if(!(other instanceof ConnectionDetails))
      {
         return false;
      }

      final ConnectionDetails otherConnectionDetails = (ConnectionDetails)other;

      return (this.hashCode() == otherConnectionDetails.hashCode()) && (this.getLocalPort() == otherConnectionDetails.getLocalPort())
               && (this.getRemotePort() == otherConnectionDetails.getRemotePort())
               && (this.isSecure() == otherConnectionDetails.isSecure())
               && this.getLocalHost()
                      .equals(otherConnectionDetails.getLocalHost())
               && this.getRemoteHost()
                      .equals(otherConnectionDetails.getRemoteHost());
   }

   public String getDescription()
   {
      return this.m_localHost + ":"
               + this.m_localPort
               + "->"
               + this.m_remoteHost
               + ":"
               + this.m_remotePort;
   }

   public String getLocalHost()
   {
      return this.m_localHost;
   }

   public int getLocalPort()
   {
      return this.m_localPort;
   }

   public String getRemoteHost()
   {
      return this.m_remoteHost;
   }

   public int getRemotePort()
   {
      return this.m_remotePort;
   }

   @Override
   public final int hashCode()
   {
      return this.m_hashCode;
   }

   public boolean isSecure()
   {
      return this.m_isSecure;
   }

}
