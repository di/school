package tests;

import chess.Position;
import chess.StateUpdate;
import chess.Piece.PieceType;
import junit.framework.TestCase;

public class StateUpdateTests extends TestCase
{
	public void testStatUpdate()
	{
		StateUpdate su = new StateUpdate(new Position(5), new Position(10));
		assertTrue(su.getOldPosition().equals(new Position(5)));
		assertTrue(su.getNewPosition().equals(new Position(10)));
		su.setOldPosition(new Position(6));
		su.setNewPosition(new Position(11));
		assertTrue(su.getOldPosition().equals(new Position(6)));
		assertTrue(su.getNewPosition().equals(new Position(11)));
		su.setCapturedPiece(PieceType.Rook);
		assertEquals(su.getCapturedPiece(), PieceType.Rook);
	}
}
