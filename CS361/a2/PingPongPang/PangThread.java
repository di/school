
public class PangThread implements Runnable
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
			while(Globals.getInstance().wantp || Globals.getInstance().wantr)
			{
				dbg("b");
				if(Globals.getInstance().turn == 1 || Globals.getInstance().turn == 3)
				{
					Globals.getInstance().wantq = false;
					dbg("c");
					while(Globals.getInstance().turn != 2) { }
					Globals.getInstance().wantq = true;
				}
			}
			dbg("d");
			criticalSection();
			if(Globals.getInstance().last_turn == 1)
			{
				//
				Globals.getInstance().wantr = true;
				//
				Globals.getInstance().turn = 3;
			}
			else if(Globals.getInstance().last_turn == 3)
			{
				//
				Globals.getInstance().wantp = true;
				//
				Globals.getInstance().turn = 1;
			}
			Globals.getInstance().wantq = false;
		}
	}
	
	public void criticalSection()
	{
		System.out.println("PANG");
	}
}
