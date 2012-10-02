package chess;

import java.util.ArrayList;

public class Pawn extends Piece
{
	private final int rankDirection = color == PieceColor.White ? -1 : 1; 
	
	public Pawn(Position position, PieceColor color)
	{
		super(position, color);
		this.type = Piece.PieceType.Pawn;
	}
	
	public ArrayList<Position> getAllowedMoves()
	{
		Piece[] gameState = Game.getInstance().getGameState();
		int file = position.getFile();
		int rank = position.getRank();
		ArrayList<Position> positions = new ArrayList<Position>();
		
		// Forward
		if( gameState[(rank+rankDirection)*8+file] == null ) {
			positions.add(new Position((rank+rankDirection)*8+file));
			if( gameState[(rank+2*rankDirection)*8+file] == null && (rank-rankDirection == 0 || rank-rankDirection == ChessBoard.NUMBER_OF_RANKS-1))
				positions.add(new Position((rank+2*rankDirection)*8+file));
		}
		
		// TODO: En Passant check - only possible if the last move the opposing pawn
		
		// Forward-Left
		if( file > 0 && gameState[(rank+rankDirection)*8+file-1] != null && gameState[(rank+rankDirection)*8+file-1].color != color )
			positions.add(new Position((rank+rankDirection)*8+file-1));
		
		// Forward-Right
		if( file < ChessBoard.NUMBER_OF_FILES && gameState[(rank+rankDirection)*8+file+1] != null && gameState[(rank+rankDirection)*8+file+1].color != color )
			positions.add(new Position((rank+rankDirection)*8+file+1));
		
		return positions;
	}
	
	public boolean handleSpecialMove(Position newPosition)
	{
		/*
		Piece[] gameState = Game.getInstance().getGameState();
		
		// Promotion
		if( newPosition.getRank() == ChessBoard.NUMBER_OF_RANKS-1 || newPosition.getRank() == 0 ) {
			ChessBoard.addPieceToBoard(new Queen(newPosition, color ), gameState);
			gameState[position.getCellNumber()] = null;
			return true;
		}
		
		// En Passant
		if( position.getFile() != newPosition.getFile() &&
			gameState[newPosition.getCellNumber()] == null )
		{
			gameState[position.getCellNumber()] = null;
			return false;
		}
		*/
		return false;
	}
}
