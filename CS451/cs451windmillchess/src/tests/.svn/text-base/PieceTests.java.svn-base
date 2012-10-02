package tests;

import java.util.ArrayList;

import chess.*;
import chess.Piece.PieceColor;
import junit.framework.TestCase;

public class PieceTests extends TestCase
{
	private boolean includedInInts(int n, int[] set)
	{
		for(int v : set)
			if(v == n)
				return true;
		return false;
	}
	
	private boolean includedInPositions(int n, ArrayList<Position> pos)
	{
		for(Position p : pos)
			if(new Position(n).equals(p))
				return true;
		return false;
	}
	
	private void validate(Piece piece, int[] known)
	{
		for(Position p : piece.getAllowedMoves())
			assertTrue(includedInInts(p.getCellNumber(), known));
		for(int n : known)
			assertTrue(includedInPositions(n, piece.getAllowedMoves()));
	}
	
	public void testBishop()
	{
		Bishop b = new Bishop(new Position(0), Piece.PieceColor.Black);
		int[] moves = { 9, 18, 27, 36, 45, 54, 63, 9, 18, 27, 36, 45, 54, 63 };
		validate(b, moves);
	}
	
	public void testKing()
	{
		King k = new King(new Position(0), PieceColor.Black);
		int[] moves = { 1, 9 , 8 };
		validate(k, moves);
	}
	
	public void testKnight()
	{
		Knight n = new Knight(new Position(0), PieceColor.Black);
		int[] moves = { 10, 17 };
		validate(n, moves);
	}
	
	public void testPawn()
	{
		Pawn p = new Pawn(new Position(0), PieceColor.Black);
		int[] moves = { 8 };
		validate(p, moves);
	}
	
	public void testQueen()
	{
		Queen q = new Queen(new Position(0), PieceColor.Black);
		int[] moves = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 18, 24, 27, 32, 36, 40, 45, 48, 54, 56, 63 };
		validate(q, moves);
	}
	
	public void testRook()
	{
		Rook r = new Rook(new Position(0), PieceColor.Black);
		int[] moves = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 32, 40, 48, 56 };
		validate(r, moves);
	}
}
