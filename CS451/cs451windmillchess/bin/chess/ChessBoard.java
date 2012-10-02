package chess;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ChessBoard extends JFrame implements MouseListener, MouseMotionListener
{
	private static final long serialVersionUID = 1L;
	private JLayeredPane layeredPane;
	private JHistoryArea historyArea;
	private JPanel chessBoard;
	private JLabel chessPiece;
	private int xAdjustment;
	private int yAdjustment;
	public static final int NUMBER_OF_RANKS = 8;
	public static final int NUMBER_OF_FILES = 8;
	private Dimension boardSize = new Dimension(600, 600);
	private StateUpdate move = new StateUpdate(null, null);
	private int origin;
	private Object waitObj = new Object();
	private String iconPath;
	
	public ChessBoard()
	{
		// Setup the board pane
		setupBoard();
		// Setup the history pane
		addHistory();
		JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, layeredPane, historyArea);
		getContentPane().add(splitPane);
	}

	private ImageIcon createImageIcon(String path)
	{
		return new ImageIcon(new ImageIcon(path).getImage().getScaledInstance(boardSize.height / NUMBER_OF_RANKS, boardSize.width / NUMBER_OF_FILES, java.awt.Image.SCALE_SMOOTH));
	}

	private void setupBoard()
	{
		layeredPane = new JLayeredPane();
		layeredPane.setPreferredSize(new Dimension(800, 600));
		layeredPane.addMouseListener(this);
		layeredPane.addMouseMotionListener(this);
		chessBoard = new JPanel();
		layeredPane.add(chessBoard, JLayeredPane.DEFAULT_LAYER);
		chessBoard.setLayout(new GridLayout(NUMBER_OF_RANKS, NUMBER_OF_FILES));
		chessBoard.setPreferredSize(boardSize);
		chessBoard.setBounds(0, 0, boardSize.width, boardSize.height);

		for (int i = 0; i < NUMBER_OF_RANKS * NUMBER_OF_FILES; i++)
		{
			JChessPanel square = new JChessPanel(new BorderLayout());
			square.setPosition(i);
			chessBoard.add(square);

			if ((i / NUMBER_OF_RANKS) % 2 == 0){
				square.setIsLight(i % 2 == 0 ? true : false);
			}
				
			else {
				square.setIsLight(i % 2 == 0 ? false : true);
			}
		}
	}

	public void addPieces()
	{
		// Dark rooks
		addPieceToBoard(new Rook(new Position(0), Piece.PieceColor.Black));
		addPieceToBoard(new Rook(new Position(7), Piece.PieceColor.Black));

		// Dark knights
		addPieceToBoard(new Knight(new Position(1), Piece.PieceColor.Black));
		addPieceToBoard(new Knight(new Position(6), Piece.PieceColor.Black));

		// Dark bishops
		addPieceToBoard(new Bishop(new Position(2), Piece.PieceColor.Black));
		addPieceToBoard(new Bishop(new Position(5), Piece.PieceColor.Black));

		// Dark queen
		addPieceToBoard(new Queen(new Position(3), Piece.PieceColor.Black));

		// Dark king
		addPieceToBoard(new King(new Position(4), Piece.PieceColor.Black));

		// Add dark pawns
		for (int i = 0; i < NUMBER_OF_RANKS; i++)
			addPieceToBoard(new Pawn(new Position(i + NUMBER_OF_RANKS), Piece.PieceColor.Black));

		// Light rooks
		addPieceToBoard(new Rook(new Position(56), Piece.PieceColor.White));
		addPieceToBoard(new Rook(new Position(63), Piece.PieceColor.White));

		// Light knights
		addPieceToBoard(new Knight(new Position(57), Piece.PieceColor.White));
		addPieceToBoard(new Knight(new Position(62), Piece.PieceColor.White));

		// Light bishops
		addPieceToBoard(new Bishop(new Position(58), Piece.PieceColor.White));
		addPieceToBoard(new Bishop(new Position(61), Piece.PieceColor.White));

		// Light queen
		addPieceToBoard(new Queen(new Position(59), Piece.PieceColor.White));

		// Light king
		addPieceToBoard(new King(new Position(60), Piece.PieceColor.White));

		// Add light pawns
		for (int i = 0; i < NUMBER_OF_RANKS; i++)
			addPieceToBoard(new Pawn(new Position(i + 6 * NUMBER_OF_RANKS), Piece.PieceColor.White));
	}

	private void addPieceToBoard(Piece piece)
	{
		JLabel pieceImage = new JLabel(createImageIcon(iconPath + piece.getType().toString() + piece.getColor().toString() + ".png"));
		JPanel panel = (JPanel) chessBoard.getComponent(piece.position.getCellNumber());
		panel.add(pieceImage);
		Game.getInstance().getGameState()[piece.getPosition().getCellNumber()] = piece;		
	}

	public void movePiece(StateUpdate state)
	{
		JPanel oldPanel = (JPanel) chessBoard.getComponent(state.getOldPosition().getCellNumber());
		JLabel movedPiece = (JLabel) oldPanel.getComponent(0);
		movedPiece.setVisible(false);

		oldPanel.remove(0);

		JPanel newPanel = (JPanel) chessBoard.getComponent(state.getNewPosition().getCellNumber());
		while (newPanel.getComponentCount() > 0)
			newPanel.remove(0);
		newPanel.add(movedPiece);
		movedPiece.setVisible(true);
	}

	// Add the selected chess piece to the dragging layer so it can be moved
	public void mousePressed(MouseEvent e)
	{
		if (!Game.getInstance().getNext())
			return;
		chessPiece = null;
		Component c = chessBoard.findComponentAt(e.getX(), e.getY());

		if (c instanceof JChessPanel)
			return;
		
		int cellNum = ((JChessPanel) c.getParent()).getPosition().getCellNumber();
		if(Game.getInstance().getGameState()[cellNum] == null || Game.getInstance().getGameState()[cellNum].getColor() != Game.getInstance().getColor())
			return;
		Point parentLocation = c.getParent().getLocation();
		xAdjustment = parentLocation.x - e.getX();
		yAdjustment = parentLocation.y - e.getY();
		move.setOldPosition(new Position(cellNum));
		chessPiece = (JLabel) c;
		chessPiece.setLocation(e.getX() + xAdjustment, e.getY() + yAdjustment);
		chessPiece.setSize(chessPiece.getWidth(), chessPiece.getHeight());
		layeredPane.add(chessPiece, JLayeredPane.DRAG_LAYER);
		origin = cellNum;
		
		shadeMoves(origin);
	}
	
	public void shadeMoves(int origin)
	{
		for(Position p : Game.getInstance().getGameState()[origin].getAllowedMoves())
		{
			((JChessPanel)chessBoard.getComponent(p.getCellNumber())).shade();
		}
	}
	
	public void unshadeMoves()
	{
		for(int i=0; i<NUMBER_OF_RANKS*NUMBER_OF_FILES; i++)
		{
			((JChessPanel)chessBoard.getComponent(i)).unshade();
		}
	}

	// Drop the chess piece back onto the chess board
	public void mouseReleased(MouseEvent e)
	{
		unshadeMoves();
		if (chessPiece == null)
			return;

		chessPiece.setVisible(false);
		Component c = chessBoard.findComponentAt(e.getX(), e.getY());
		
		Container block;
		if (c instanceof JLabel)
			block = c.getParent();
		else
			block = (Container) c;
		
		if(block == null)
		{
			((JPanel)chessBoard.getComponent(origin)).add(chessPiece);
			chessPiece.setVisible(true);
			chessPiece = null;
			return;
		}
		move.setNewPosition(new Position(((JChessPanel) block).getPosition().getCellNumber()));

		if(Game.getInstance().isAllowed(move))
		{
			while (block.getComponentCount() > 0)
				block.remove(0);
			block.add(chessPiece);
			if (!move.getOldPosition().equals(move.getNewPosition()))
			{
				synchronized(waitObj)
				{
					waitObj.notifyAll();
				}
			}
		}
		else
		{
			((JPanel)chessBoard.getComponent(origin)).add(chessPiece);
		}
		chessPiece.setVisible(true);
		chessPiece = null;
	}

	// Move the chess piece around
	public void mouseDragged(MouseEvent me)
	{
		if (chessPiece == null)
			return;
		chessPiece.setLocation(me.getX() + xAdjustment, me.getY() + yAdjustment);
	}

	public StateUpdate getMove()
	{
		synchronized(waitObj)
		{
			try
			{
				waitObj.wait();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		return this.move;
	}

	public void showWin()
	{
		JOptionPane.showMessageDialog(this, "Congratulations! You have won the game!");
		System.exit(0);
	}

	public void showLoss()
	{
		JOptionPane.showMessageDialog(this, "You have lost the game. Better luck next time!");
		System.exit(0);
	}
	
	public void showDisconnect()
	{
		JOptionPane.showMessageDialog(this, "Your opponent has disconnected!");
		System.exit(0);
	}

	private void addHistory()
	{
		historyArea = new JHistoryArea();
		JScrollPane historyScrollPane = new JScrollPane(historyArea);
		historyArea.setMaximumSize(new Dimension(200, 600));
		historyArea.setMinimumSize(new Dimension(200, 600));
		historyArea.setEditable(false);
		layeredPane.add(historyScrollPane, JLayeredPane.DEFAULT_LAYER);
	}
	
	public void mouseClicked(MouseEvent e)
	{
	}

	public void mouseMoved(MouseEvent e)
	{
	}

	public void mouseEntered(MouseEvent e)
	{
	}

	public void mouseExited(MouseEvent e)
	{
	}

	public void setIconPath(String iconPath)
	{
		this.iconPath = iconPath;
	}
	
	public JHistoryArea getHistoryArea() {
		return historyArea;
	}
}
