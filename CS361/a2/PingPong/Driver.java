
public class Driver
{
	public static void main(String[] args)
	{
		Globals g = Globals.getInstance();
		g.wantp = false;
		g.wantq = false;
		g.turn = 1;
		PingThread pingThread = new PingThread();
		PongThread pongThread = new PongThread();
		
		Thread p = new Thread(pingThread);
		p.start();
		Thread q = new Thread(pongThread);
		q.start();
	}
}
