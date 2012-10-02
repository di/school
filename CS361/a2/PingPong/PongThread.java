
public class PongThread implements Runnable
{
	private void dbg(String s)
	{
		//System.out.println("> q: " + s);
	}
	
	public void run()
	{
		while(true)
		{
			Globals.getInstance().wantq = true;
			dbg("a");
			while(Globals.getInstance().wantp)
			{
				dbg("b");
				if(Globals.getInstance().turn == 1)
				{
					Globals.getInstance().wantq = false;
					dbg("c");
					while(Globals.getInstance().turn != 2) { }
					Globals.getInstance().wantq = true;
				}
			}
			dbg("d");
			criticalSection();
			//
			Globals.getInstance().wantp = true;
			//
			Globals.getInstance().turn = 1;
			Globals.getInstance().wantq = false;
		}
	}
	
	public void criticalSection()
	{
		System.out.println("PONG");
	}
}
