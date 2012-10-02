package tests;

import chess.Game;
import chess.Piece.PieceColor;
import junit.framework.TestCase;

public class GameTests extends TestCase
{
	public void testColor()
	{
		Game.getInstance().setColor(PieceColor.Black);
		assertEquals(Game.getInstance().getColor(), PieceColor.Black);
		
		Game.getInstance().setNext(true);
		assertTrue(Game.getInstance().getNext());
		
		assertFalse(Game.getInstance().isOccupied(0));
	}
}
