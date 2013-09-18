/**
 * CSE 490K Project 2
 */

package mitm;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InterruptedIOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.GeneralSecurityException;
import java.security.MessageDigest;
import java.util.Properties;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// You need to add code to do the following
// 1) use SSL sockets instead of the plain sockets provided
// 2) check user authentication
// 3) perform the given administration command

class MITMAdminServer implements Runnable
{
   private ServerSocket m_serverSocket;
   private Socket       m_socket = null;
   
   public HTTPSProxyEngine m_engine;

   // Constructor
   public MITMAdminServer(String localHost,
                          int adminPort,
                          HTTPSProxyEngine engine) throws IOException, GeneralSecurityException
   {
//      MITMPlainSocketFactory socketFactory = new MITMPlainSocketFactory();
//      this.m_serverSocket = socketFactory.createServerSocket(localHost,
//                                                             adminPort,
//                                                             0);
      
      // Save the reference to the engine 
      this.m_engine = engine;
      
      MITMSSLSocketFactory socketFactory = new MITMSSLSocketFactory();
      this.m_serverSocket = socketFactory.createServerSocket(localHost, adminPort, 0);
   }

   // TODO implement the commands
   private boolean doCommand(String cmd) throws IOException
   {
      boolean retval = false;
      
      System.out.println("Command received:");
      System.out.println(cmd);
      
      String message;
      
      if(cmd.equals("shutdown"))
      {
         message = "Server shutting down...";
         this.m_engine.shutdown_requested = true;
         retval = true;
      }
      else if(cmd.equals("stats"))
      {
         message = "Number of proxied requests: " + this.m_engine.request_count;
      }
      else
      {
         message = "Unknown command";
      }
      
      // Write to the socket
      if(this.m_socket != null)
      {
         PrintWriter writer = new PrintWriter(this.m_socket.getOutputStream());
         writer.println(message);
         writer.flush();
      }
      
      // Close the socket
      this.m_socket.close();
      
      return retval;
   }

   private String hash(String string)
   {
      // Hardcoded salt
      String salt = "salt12345";
      
      // Salt the string
      string += salt;
      
      StringBuffer hexString = new StringBuffer();
      
      try
      {
         MessageDigest digest = MessageDigest.getInstance("SHA-256");
         
         // Hash the salt + string
         byte[] hash = digest.digest(string.getBytes("UTF-8"));
         
         // Convert it to hex representation
         for (int i = 0; i < hash.length; i++) {
             String hex = Integer.toHexString(0xff & hash[i]);
             if(hex.length() == 1) hexString.append('0');
             hexString.append(hex);
         }
      }
      catch(Exception e)
      {
         System.out.println("Hashing error");
      }

      return hexString.toString();
   }
   
   @Override
   public void run()
   {
      System.out.println("Admin server initialized, listening on port " + this.m_serverSocket.getLocalPort());
      boolean shutdown_requested = false;
      while(!shutdown_requested)
      {
         try
         {
            // Open the socket
            this.m_socket = this.m_serverSocket.accept();

            // Allocate a buffer
            byte[] buffer = new byte[40960];

            // Regular expression to match username and password
            Pattern userPwdPattern = Pattern.compile("username:(\\S+)\\s+password:(\\S+)\\s+command:(\\S+)\\sCN:(\\S*)\\s");

            // Open the input stream
            BufferedInputStream in = new BufferedInputStream(this.m_socket.getInputStream(),
                                                             buffer.length);

            // Read a buffer full.
            int bytesRead = in.read(buffer);

            // Turn the buffer contents into a string
            String line = bytesRead > 0 ? new String(buffer, 0, bytesRead) : "";

            // Create a pattern matcher based on the regular expression provided above
            Matcher userPwdMatcher = userPwdPattern.matcher(line);

            // parse username and pwd
            if(userPwdMatcher.find())
            {
               // JRR - Begin Changes
               
               // Username
               String username = userPwdMatcher.group(1);
               
               // Password
               String password = userPwdMatcher.group(2);

               // Load password file
               Properties password_file = new Properties();
               BufferedReader file_reader = new BufferedReader(new FileReader("passwords.properties")); 
               password_file.load(file_reader);
               
               boolean authenticated = false;
               if(password_file.containsKey(username))
               {
                  String stored_password = password_file.getProperty(username);
                  
                  String hashed_password = hash(password);
                  
                  if(hashed_password.equals(stored_password))
                  {
                     authenticated = true;
                  }
               }
               
               // if authenticated, do the command
               if(authenticated)
               {
                  // Match the command
                  String command = userPwdMatcher.group(3);
                  
                  shutdown_requested = this.doCommand(command);
               }
               else
               {
                  System.out.println("Authentication error");
               }
               
            // JRR - End Changes
            }
         }
         catch(InterruptedIOException e)
         {
         }
         catch(Exception e)
         {
            e.printStackTrace();
         }
      }
      
      System.out.println("Shutting Down...");
   }

}
