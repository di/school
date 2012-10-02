package chess;

import javax.swing.JTextArea;

import chess.Piece.PieceType;

public class JHistoryArea extends JTextArea
{
	private static final long serialVersionUID = 6831559761976141667L;
	private static StateUpdate lastMove;
	
	public JHistoryArea()
	{
		super();
	}
	
	public void updateJHistoryArea(StateUpdate update)
	{
		StringBuilder paneLine = new StringBuilder();
		
		if(lastMove == null)
		{
			lastMove = update;
		}
		
		else
		{
			if(lastMove.getCapturedPiece() != null)
			{
				char notation = characterFromPieceType(lastMove.getMovedPiece());
				if(notation == 'P')
				{
					paneLine.append(Character.toString(
							Position.fileCharFromInt(lastMove.getOldPosition().getFile())));
					paneLine.append("x");
					paneLine.append(Character.toString(
							Position.fileCharFromInt(lastMove.getNewPosition().getFile())));
					paneLine.append(Integer.toString(8 - lastMove.getNewPosition().getRank()));
					paneLine.append(" ");
				}
				
				else
				{
					paneLine.append(notation);
					paneLine.append("x");
					paneLine.append(Character.toString(
							Position.fileCharFromInt(lastMove.getNewPosition().getFile())));
					paneLine.append(Integer.toString(8 - lastMove.getNewPosition().getRank()));
					paneLine.append(" ");
				}
			}
			
			if(lastMove.getCapturedPiece() == null)
			{
				char notation = characterFromPieceType(lastMove.getMovedPiece());
				if(notation == 'P')
				{
					paneLine.append(((Character.toString(
							Position.fileCharFromInt(lastMove.getNewPosition().getFile())))));
					paneLine.append(Integer.toString(8 - lastMove.getNewPosition().getRank()));
					paneLine.append(" ");
				}
				else
				{
					paneLine.append(Character.toString(notation));
					paneLine.append(((Character.toString(
							Position.fileCharFromInt(lastMove.getNewPosition().getFile())))));
					paneLine.append(Integer.toString(8 - lastMove.getNewPosition().getRank()));
					paneLine.append(" ");
				}
			}
			
			
			if(update.getCapturedPiece() != null)
			{
				char notation = characterFromPieceType(update.getMovedPiece());
				if(notation == 'P')
				{
					paneLine.append(Character.toString(
							Position.fileCharFromInt(update.getOldPosition().getFile())));
					paneLine.append("x");
					paneLine.append(Character.toString(
							Position.fileCharFromInt(update.getNewPosition().getFile())));
					paneLine.append(Integer.toString(8 - update.getNewPosition().getRank()));
					paneLine.append(" ");
				}
				
				else
				{
					paneLine.append(notation);
					paneLine.append("x");
					paneLine.append(Character.toString(
							Position.fileCharFromInt(update.getNewPosition().getFile())));
					paneLine.append(Integer.toString(8 - update.getNewPosition().getRank()));
					paneLine.append(" ");
				}
			}
			
			if(update.getCapturedPiece() == null)
			{
				char notation = characterFromPieceType(update.getMovedPiece());
				if(notation == 'P')
				{
					paneLine.append(((Character.toString(
							Position.fileCharFromInt(update.getNewPosition().getFile())))));
					paneLine.append(Integer.toString(8 - update.getNewPosition().getRank()));
					paneLine.append(" ");					
				}
				
				else
				{
					paneLine.append(Character.toString(notation));
					paneLine.append(((Character.toString(
							Position.fileCharFromInt(update.getNewPosition().getFile())))));
					paneLine.append(Integer.toString(8 - update.getNewPosition().getRank()));
					paneLine.append(" ");
				}				
			}
			
			updateTextArea(paneLine.toString());
			lastMove = null;
		}
	}

	private void updateTextArea(String update)
	{
		this.append(update);
		this.append("\n");
	}
	
	private static char characterFromPieceType(PieceType movedPiece) 
	{
		char tempChar = 0;
		if(movedPiece != null)
		{
			switch(movedPiece)
			{
				case King: tempChar = 'K'; break;
				case Queen: tempChar = 'Q'; break;
				case Rook: tempChar = 'R'; break;
				case Bishop: tempChar = 'B'; break;
				case Knight: tempChar = 'N'; break;
				case Pawn: tempChar = 'P'; break;
			
				default: tempChar = '-';
			}
		}
		return tempChar;	
	}
}
