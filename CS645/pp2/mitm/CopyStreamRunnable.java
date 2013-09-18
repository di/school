// This file is part of The Grinder software distribution. Refer to
// the file LICENSE which is part of The Grinder distribution for
// licensing details. The Grinder distribution is available on the
// Internet at http://grinder.sourceforge.net/

// JRR - No changes required here

package mitm;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Runnable that actively copies from an InputStream to an OutputStream.
 * 
 */
public class CopyStreamRunnable implements Runnable
{
   private final InputStream  m_in;
   private final OutputStream m_out;

   public CopyStreamRunnable(InputStream in, OutputStream out)
   {
      this.m_in = in;
      this.m_out = out;
   }

   @Override
   public void run()
   {
      final byte[] buffer = new byte[4096];

      try
      {
         short idle = 0;

         while(true)
         {
            final int bytesRead = this.m_in.read(buffer, 0, buffer.length);

            if(bytesRead == -1)
            {
               break;
            }

            if(bytesRead == 0)
            {
               idle++;
            }
            else
            {
               this.m_out.write(buffer, 0, bytesRead);
               idle = 0;
            }

            if(idle > 0)
            {
               Thread.sleep(Math.max(idle * 200, 2000));
            }
         }
      }
      catch(IOException e)
      {
         // Be silent about IOExceptions ...
      }
      catch(InterruptedException e)
      {
         // ... and InterruptedExceptions.
      }

      // We're exiting, usually because the in stream has been
      // closed. Whatever, close our streams. This will cause the
      // paired thread to exit too.
      try
      {
         this.m_out.close();
      }
      catch(IOException e)
      {
      }

      try
      {
         this.m_in.close();
      }
      catch(IOException e)
      {
      }
   }
}
