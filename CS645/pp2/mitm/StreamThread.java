// This file is part of The Grinder software distribution. Refer to
// the file LICENSE which is part of The Grinder distribution for
// licensing details. The Grinder distribution is available on the
// Internet at http://grinder.sourceforge.net/

// JRR - No changes required here

package mitm;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.SocketException;

/**
 * Copies bytes from an InputStream to an OutputStream. Uses a ProxyDataFilter
 * to log the contents appropriately.
 * 
 */
public class StreamThread implements Runnable
{
   // For simplicity, the filters take a buffer oriented approach.
   // This means that they all break at buffer boundaries. Our buffer
   // is huge, so we shouldn't practically cause a problem, but the
   // network clearly can by giving us message fragments.
   // We really ought to take a stream oriented approach.
   private final static int        BUFFER_SIZE = 65536;

   private final ConnectionDetails m_connectionDetails;
   private final InputStream       m_in;
   private final OutputStream      m_out;
   private final ProxyDataFilter   m_filter;
   private final PrintWriter       m_outputWriter;

   public StreamThread(ConnectionDetails connectionDetails,
                       InputStream in,
                       OutputStream out,
                       ProxyDataFilter filter,
                       PrintWriter outputWriter)
   {
      this.m_connectionDetails = connectionDetails;
      this.m_in = in;
      this.m_out = out;
      this.m_filter = filter;
      this.m_outputWriter = outputWriter;

      final Thread t = new Thread(this,
                                  "Filter thread for " + this.m_connectionDetails.getDescription());

      try
      {
         this.m_filter.connectionOpened(this.m_connectionDetails);
      }
      catch(Exception e)
      {
         e.printStackTrace(System.err);
      }

      t.start();
   }

   @Override
   public void run()
   {
      try
      {
         byte[] buffer = new byte[BUFFER_SIZE];

         while(true)
         {
            final int bytesRead = this.m_in.read(buffer, 0, BUFFER_SIZE);

            if(bytesRead == -1)
            {
               break;
            }

            final byte[] newBytes = this.m_filter.handle(this.m_connectionDetails,
                                                         buffer,
                                                         bytesRead);

            this.m_outputWriter.flush();

            if(newBytes != null)
            {
               this.m_out.write(newBytes);
            }
            else
            {
               this.m_out.write(buffer, 0, bytesRead);
            }
         }
      }
      catch(SocketException e)
      {
         // Be silent about SocketExceptions.
      }
      catch(Exception e)
      {
         e.printStackTrace(System.err);
      }

      try
      {
         this.m_filter.connectionClosed(this.m_connectionDetails);
      }
      catch(Exception e)
      {
         e.printStackTrace(System.err);
      }

      this.m_outputWriter.flush();

      // We're exiting, usually because the in stream has been
      // closed. Whatever, close our streams. This will cause the
      // paired thread to exit to.
      try
      {
         this.m_out.close();
      }
      catch(Exception e)
      {
      }

      try
      {
         this.m_in.close();
      }
      catch(Exception e)
      {
      }
   }
}
