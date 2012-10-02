package chess;

import java.util.ArrayList;

public class Knight extends Piece
{

	final static private int[][] moves =
	{
	{ 2, 1 },
	{ 1, 2 } };

	public Knight(Position position, PieceColor color)
	{
		super(position, color);
		this.type = Piece.PieceType.Knight;
	}

	public ArrayList<Position> getAllowedMoves()
	{
		ArrayList<Position> positions = new ArrayList<Position>();

		positions.addAll(addPositions(1,1, positions));
		positions.addAll(addPositions(1,-1, positions));
		positions.addAll(addPositions(-1,1, positions));
		positions.addAll(addPositions(-1,-1, positions));
		
		return positions;
	}
	
	private ArrayList<Position> addPositions(int ri, int fi, ArrayList<Position> positions)
	{
		Piece[] gameState = Game.getInstance().getGameState();
		for (int i = 0; i < moves.length; i++)
		{
			int r = (moves[i][0] * ri) + position.getRank();
			int f = (moves[i][1] * fi) + position.getFile();

			if (r >= 0 && r < ChessBoard.NUMBER_OF_RANKS && f >= 0
					&& f < ChessBoard.NUMBER_OF_FILES)
			{
				if (gameState[r * 8 + f] == null)
					positions.add(new Position(r * 8 + f));
				else if (gameState[r * 8 + f].getColor() != color)
				{
					positions.add(new Position(r * 8 + f));
				}
			}

		}		
		
		return positions;
	}
}
