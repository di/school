
public class Globals
{
	volatile public boolean wantp;
	volatile public boolean wantq;
	volatile public boolean wantr;
	volatile public int turn;
	volatile public int last_turn;
	
	private static Globals instance = null;
	
	protected Globals() { }
	
	public static Globals getInstance()
	{
		if(instance == null)
			instance = new Globals();
		return instance;
	}
}
