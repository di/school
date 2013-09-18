/**
 * CSE 490K project 2
 */
package mitm;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class MITMAdminClient
{
   // Entry point
   public static void main(String[] args)
   {
      // Create a new client
      MITMAdminClient admin = new MITMAdminClient(args);
      
      // Run the client
      admin.run();
   }

   private Socket m_remoteSocket;
   private String username;
   private String password;
   private String command;
   
   private String commonName = "";

   // Constructor
   private MITMAdminClient(String[] args)
   {
      int remotePort = 8002;
      String remoteHost = "localhost";

      if(args.length < 3)
      {
         throw this.printUsage();
      }

      // Parse Arguments
      try
      {
         for(int i = 0; i < args.length; i++)
         {
            if(args[i].equals("-remoteHost"))
            {
               remoteHost = args[++i];
            }
            else if(args[i].equals("-remotePort"))
            {
               remotePort = Integer.parseInt(args[++i]);
            }
            else if(args[i].equals("-userName"))
            {
               this.username = args[++i];
            }
            else if(args[i].equals("-userPassword"))
            {
               this.password = args[++i];
            }
            else if(args[i].equals("-cmd"))
            {
               this.command = args[++i];
               if(this.command.equals("enable") || this.command.equals("disable"))
               {
                  this.commonName = args[++i];
               }
            }
            else
            {
               throw this.printUsage();
            }
         }

         // TODO upgrade this to an SSL connection
         // this.m_remoteSocket = new Socket(remoteHost, remotePort);
         
         MITMSSLSocketFactory socketFactory = new MITMSSLSocketFactory();
         this.m_remoteSocket = socketFactory.createClientSocket(remoteHost, remotePort);
         System.out.println("Client connected");

      }
      catch(Exception e)
      {
         throw this.printUsage();
      }

   }

   private Error printUsage()
   {
      System.err.println("\n" + "Usage: "
               + "\n java "
               + MITMAdminClient.class
               + " <options>"
               + "\n"
               + "\n Where options can include:"
               + "\n"
               + "\n   <-userName <type> >       "
               + "\n   <-userPassword <pass> >   "
               + "\n   <-cmd <shudown|stats>"
               + "\n   [-remoteHost <host name/ip>]  Default is localhost"
               + "\n   [-remotePort <port>]          Default is 8002"
               + "\n");

      System.exit(1);
      return null;
   }

   // Run the client
   public void run()
   {
      try
      {
         // Write to the socket
         if(this.m_remoteSocket != null)
         {
            PrintWriter writer = new PrintWriter(this.m_remoteSocket.getOutputStream());
            writer.println("username:" + this.username);
            writer.println("password:" + this.password);
            writer.println("command:" + this.command);
            writer.println("CN:" + this.commonName);
            writer.flush();
         }

         // Now read back any response
         System.out.println("");
         System.out.println("Receiving input from MITM proxy:");
         System.out.println("");
         
         // Read from the socket
         BufferedReader r = new BufferedReader(new InputStreamReader(this.m_remoteSocket.getInputStream()));
         String line = null;
         
         // Read until nothing is left
         while((line = r.readLine()) != null)
         {
            // Print out each line to the screen
            System.out.println(line);
         }
      }
      catch(Exception e)
      {
         e.printStackTrace();
      }
      
      // All done
      System.err.println("Admin Client exited");
      System.exit(0);
   }
}
