package tests;

import chess.Connection;
import chess.ConnectionSetup;
import chess.Game;
import junit.framework.TestCase;

public class ConnectionSetupTests extends TestCase
{
	ConnectionSetup cs = new ConnectionSetup(Game.getInstance(), Connection.getNetworkInfo());
	public void testValidate()
	{
		assertTrue(cs.validateIP("127.0.0.1"));
		assertTrue(cs.validatePort("12345"));
	}
	
	public void testDefaultIcon()
	{
		assertEquals(cs.getIconPath(), "./default_icons/");
	}
}
