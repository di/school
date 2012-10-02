
public class PingThread implements Runnable
{
	private void dbg(String s)
	{
		//System.out.println("> p: " + s);
	}
	
	public void run()
	{
		while(true)
		{
			Globals.getInstance().wantp = true;
			dbg("a");
			while(Globals.getInstance().wantq)
			{
				dbg("b");
				if(Globals.getInstance().turn == 2)
				{
					Globals.getInstance().wantp = false;
					dbg("c");
					while(Globals.getInstance().turn != 1) { }
					Globals.getInstance().wantp = true;
				}
			}
			dbg("d");
			criticalSection();
			//
			Globals.getInstance().wantq = true;
			//
			Globals.getInstance().turn = 2;
			Globals.getInstance().wantp = false;
		}
	}
	
	public void criticalSection()
	{
		System.out.println("PING");
	}
}
