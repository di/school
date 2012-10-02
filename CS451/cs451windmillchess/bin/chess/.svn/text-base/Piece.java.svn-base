package chess;

import java.util.ArrayList;

public abstract class Piece
{
	public static enum PieceType { King, Queen, Rook, Bishop, Knight, Pawn};
	public static enum PieceColor { White, Black };
	protected Position position;
	protected PieceType type;
	protected PieceColor color;	
	
	public Piece(Position position, PieceColor color)
	{
		this.position = position;
		this.color = color;
	}

    public PieceType getType()
    {
        return this.type;
    }
	
	public PieceColor getColor()
	{
		return color;
	}

	public Position getPosition()
	{
		return this.position;
	}
	
	public void setPosition(Position newPosition)
	{
		this.position = newPosition;
	}
    
	public StateUpdate move(Position newPosition)
	{
		Position oldPosition = position;
		position = newPosition;
		StateUpdate update = new StateUpdate(oldPosition, position);
		update.setMovedPiece(this.getType());
		return update;
	}

	public abstract ArrayList<Position> getAllowedMoves();
}
