import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
	
public class Server implements Chunk {
	
    public Server() {}

    public int sum(int[] sub_array) {
	int ret = 0;
	for(int i=0;i<sub_array.length;i++)
		ret += sub_array[i];
	return ret;
    }
	
    public static void main(String args[]) {
	
	try {
	    Server obj = new Server();
	    Chunk stub = (Chunk) UnicastRemoteObject.exportObject(obj, 0);

	    // Bind the remote object's stub in the registry
	    Registry registry = LocateRegistry.getRegistry(4242);
	    registry.bind("Chunk" + args[0], stub);

	    System.err.println("Server ready");
	} catch (Exception e) {
	    System.err.println("Server exception: " + e.toString());
	    e.printStackTrace();
	}
    }
}
