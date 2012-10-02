import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    private Client() {}

    public static void main(String[] args) {

	String host = (args.length < 1) ? null : args[0];
	int[] big_array = new int[100000];
	for(int i=0;i<big_array.length;i++)
		big_array[i] = i;
	try {
	    int[] first_arr = new int[big_array.length/2];
	    for(int i=0;i<first_arr.length;i++)
		first_arr[i] = big_array[i];
	    int[] second_arr = new int[big_array.length/2];
	    for(int i=0;i<second_arr.length;i++)
		second_arr[i] = big_array[i+big_array.length/2];

	    Registry registry = LocateRegistry.getRegistry(host,4242);
	    Chunk stub = (Chunk) registry.lookup("Chunk1");
	    int a = stub.sum(first_arr);
	    System.out.println("sub sub:" + a);

	    Registry registry2 = LocateRegistry.getRegistry(host,4242);
	    Chunk stub2 = (Chunk) registry.lookup("Chunk2");
	    int b = stub.sum(second_arr);
	    System.out.println("sub sub:" + b);
	
		System.out.println("Total: " + (a+b));

	} catch (Exception e) {
	    System.err.println("Client exception: " + e.toString());
	    e.printStackTrace();
	}
    }
}
