
public class PongThread implements Runnable
{
	private void dbg(String s)
	{
		//System.out.println("> r: " + s);
	}
	
	public void run()
	{
		while(true)
		{
			Globals.getInstance().wantr = true;
			dbg("a");
			while(Globals.getInstance().wantp || Globals.getInstance().wantq)
			{
				dbg("b");
				if(Globals.getInstance().turn == 1 || Globals.getInstance().turn == 2)
				{
					Globals.getInstance().wantr = false;
					dbg("c");
					while(Globals.getInstance().turn != 3) { }
					Globals.getInstance().wantr = true;
				}
			}
			dbg("d");
			criticalSection();
			Globals.getInstance().last_turn = 3;
			//
			Globals.getInstance().wantq = true;
			//
			Globals.getInstance().turn = 2;
			Globals.getInstance().wantr = false;
		}
	}
	
	public void criticalSection()
	{
		System.out.println("PONG");
	}
}
