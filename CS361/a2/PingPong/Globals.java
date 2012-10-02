
public class Globals
{
	volatile public boolean wantp;
	volatile public boolean wantq;
	volatile public int turn;
	
	private static Globals instance = null;
	
	protected Globals() { }
	
	public static Globals getInstance()
	{
		if(instance == null)
			instance = new Globals();
		return instance;
	}
}
