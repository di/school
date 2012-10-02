package chess;

import java.io.Serializable;

public class StateUpdate implements Serializable
{
	private static final long serialVersionUID = -3330989439584136830L;
	private Position oldPosition;
	private Position newPosition;
	private Piece.PieceType capturedPiece = null;
	private Piece.PieceType movedPiece = null;

	public StateUpdate(Position oldPosition, Position newPosition)
	{
		this.oldPosition = oldPosition;
		this.newPosition = newPosition;
	}

	public Position getOldPosition()
	{
		return oldPosition;
	}

	public Position getNewPosition()
	{
		return newPosition;
	}

	public void setOldPosition(Position oldPosition)
	{
		this.oldPosition = oldPosition;
	}

	public void setNewPosition(Position newPosition)
	{
		this.newPosition = newPosition;
	}

	public Piece.PieceType getMovedPiece() {
		return movedPiece;
	}

	public void setMovedPiece(Piece.PieceType movedPiece) {
		this.movedPiece = movedPiece;
	}

	public Piece.PieceType getCapturedPiece() {
		return capturedPiece;
	}

	public void setCapturedPiece(Piece.PieceType capturedPiece) {
		this.capturedPiece = capturedPiece;
	}
}
