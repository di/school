import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Chunk extends Remote {
    int sum(int[] sub_array) throws RemoteException;
}
