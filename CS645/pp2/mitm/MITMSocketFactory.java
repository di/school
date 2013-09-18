package mitm;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public interface MITMSocketFactory
{
            Socket
            createClientSocket(String remoteHost, int remotePort) throws IOException;

            ServerSocket
            createServerSocket(String localHost, int localPort, int timeout) throws IOException;
}
