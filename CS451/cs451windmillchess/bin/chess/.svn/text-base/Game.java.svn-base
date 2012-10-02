package chess;

import java.io.IOException;
import java.net.Socket;

import javax.swing.JFrame;

import chess.Piece;

public class Game
{
	private ConnectionSetup setup;
	private Connection connection;
	private ChessBoard board;
	private Piece[] gameState;
	private static Game instance;
	private boolean next;
	private Piece.PieceColor color;

	private Game()
	{
		board = new ChessBoard();
		setup = new ConnectionSetup(this, Connection.getNetworkInfo());
		board.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		board.pack();
		board.setResizable(false);
		board.setLocationRelativeTo(null);
		gameState = new Piece[ChessBoard.NUMBER_OF_RANKS * ChessBoard.NUMBER_OF_FILES];
	}

	public Piece.PieceColor getColor()
	{
		return color;
	}

	public void setColor(Piece.PieceColor color)
	{
		this.color = color;
	}

	public boolean getNext()
	{
		return next;
	}
	
	public void setNext(boolean next)
	{
		this.next = next;
		if (next)
			board.setTitle("Move");
		else
			board.setTitle("Wait");
	}

	public void start()
	{
		board.setIconPath(setup.getIconPath());
		board.addPieces();
		board.setVisible(true);
		StateUpdate update = null;

		while (true)
		{
			update = null;
			if (next)
			{
				try
				{
					update = board.getMove();
					connection.sendState(update);
				}
				catch (IOException e)
				{
					board.showDisconnect();
				}
			}
			else
			{
				try
				{
					update = connection.awaitState();
					board.movePiece(update);
				}
				catch (IOException e)
				{
					board.showDisconnect();
				}
				catch (ClassNotFoundException e)
				{
					e.printStackTrace();
				}
			}

			Piece captured = gameState[update.getNewPosition().getCellNumber()];
			
			if(captured != null)
			{
				update.setCapturedPiece(captured.getType());
			}
			
			gameState[update.getNewPosition().getCellNumber()] = gameState[update.getOldPosition().getCellNumber()];
			gameState[update.getOldPosition().getCellNumber()] = null;
			Piece tmp = gameState[update.getNewPosition().getCellNumber()];
			tmp.move(update.getNewPosition());
			update.setMovedPiece(tmp.getType());
			board.getHistoryArea().updateJHistoryArea(update);
			
			if (captured != null && captured.getType() == Piece.PieceType.King)
				break;

			setNext(!next);
		}
		if (next)
			board.showWin();
		else
			board.showLoss();
	}

	public boolean isAllowed(StateUpdate move)
	{
		if (gameState[move.getOldPosition().getCellNumber()] == null)
			return false;
		for (Position p : gameState[move.getOldPosition().getCellNumber()].getAllowedMoves())
			if (p.equals(move.getNewPosition()))
				return true;
		return false;
	}

	public boolean isOccupied(int cellNumber)
	{
		return !(gameState[cellNumber] == null);
	}

	public void connect(String ip, int port) throws java.io.IOException
	{
		connection = new Connection(new Socket(ip, port));
	}

	public void listen(int port) throws java.io.IOException
	{
		connection = new Connection(port);
		connection.awaitConnection();
	}

	public static Game getInstance()
	{
		if (instance == null)
			instance = new Game();
		return instance;
	}

	public Piece[] getGameState()
	{
		return gameState;
	}

	public static void main(String[] args)
	{
		Game chessGame = Game.getInstance();
	}
}
