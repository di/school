package chess;

import java.util.ArrayList;

public class King extends Piece
{
	final static private int[][] moves =
	{
	{ 1, 0 },
	{ 0, 1 },
	{ 1, 1 } };
	//private boolean hasMoved; // disallows castling

	public King(Position position, PieceColor color)
	{
		super(position, color);
		this.type = Piece.PieceType.King;
		//hasMoved = false;
	}

	public boolean getChecked()
	{
		/*
		for( Piece[] pieceRow : Game.getInstance().getGameState() ) for(
		Piece piece : pieceRow ) if( piece != null && piece.getColor() !=
		 color ) for( Position p : piece.getAllowedMoves() ) if( p.getFile()
		== position.getFile() && p.getRank() == position.getRank() ) return
		true;
		*/
		return false;
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

	private ArrayList<Position> addPositions(int ri, int fi,
			ArrayList<Position> positions)
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

	/*
	public ArrayList<Position> getAllowedMoves() { Piece[][] gameState =
	Game.getInstance().getGameState(); int file = position.getFile(); int
	rank = position.getRank(); ArrayList<Position> positions = new
	ArrayList<Position>();
	
	// Handles the simple directional moves for(int i=0; i<moves.length; i++)
	{ int r = moves[i][0] + rank; int f = moves[i][1] + file;
	
	if( r >= 0 && r < ChessBoard.NUMBER_OF_RANKS && f >= 0 && f <
	ChessBoard.NUMBER_OF_FILES && (gameState[f][r] == null ||
	gameState[f][r].getColor() != color) ) { positions.add(new
	Position(r*8+f)); } }
	 
	// Castling if( !hasMoved && !getChecked() ) { // Left boolean
	positionClear = true; for( int i=file-1; i>0; i--) if( gameState[i][rank]
	!= null) positionClear = false; if( positionClear &&
	gameState[0][rank].getType() == Piece.PieceType.Rook &&
	((Rook)gameState[0][rank]).canCastle() ) positions.add(new
	Position(rank*8+(file-2)));
	 
	// Right positionClear = true; for( int i=file+1;
	i<ChessBoard.NUMBER_OF_FILES-1; i++) if( gameState[i][rank] != null)
	positionClear = false; if( positionClear &&
	gameState[ChessBoard.NUMBER_OF_FILES-1][rank].getType() ==
	Piece.PieceType.Rook &&
	((Rook)gameState[ChessBoard.NUMBER_OF_FILES-1][rank]).canCastle() )
	positions.add(new Position(rank*8+(file+2))); }
	
	return (Position[]) positions.toArray(); return new
	ArrayList<Position>(); }
	*/
	
	public boolean handleSpecialMove(Position newPosition)
	{
		/*
		hasMoved = true;
		
		// Castling if( position.getFile() == newPosition.getFile()-2 ||
		position.getFile() == newPosition.getFile()+2 ) { Piece[][] gameState
		= Game.getInstance().getGameState(); gameState[position.getFile() >
		newPosition.getFile() ? 0 :
		ChessBoard.NUMBER_OF_FILES-1][position.getRank()] .move(new
		Position(newPosition.getRank()*8+2)); this.move(newPosition); return
		true; }
		*/
		return false;
	}
}
