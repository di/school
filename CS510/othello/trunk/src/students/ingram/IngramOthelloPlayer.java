package students.ingram;

import java.util.Date;

import edu.drexel.cs.ai.othello.GameState;
import edu.drexel.cs.ai.othello.GameState.Player;
import edu.drexel.cs.ai.othello.OthelloPlayer;
import edu.drexel.cs.ai.othello.Square;

class Node {
    private GameState state;
    private Square move;
    private Square parentMove;
    private int value;
    
    public Node(GameState state, Square move, Square parentMove) {
        this.state = state;
        this.move = move;
        this.parentMove = parentMove;
    }
    
    public Node(int value) {
        this.value = value;
    }
    
    public Square getMove() {
        return this.move;
    }
    
    public GameState getState() {
        return this.state;
    }
    
    public int getValue() {
        return this.value;
    }
    
    public void setValue(int value) {
        this.value = value;
    }
    
    public Square getParentMove() {
        return this.parentMove;
    }
    
    public Square getParentMove(Square move) {
        if (this.parentMove == null)
            this.parentMove = move;
        return this.parentMove;
    }
}


public class IngramOthelloPlayer extends OthelloPlayer {

    private Player me;
    private Player them;
    private boolean initialized = false;
    private int[][] pre16positions =  {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 100, 100, 100, 100, 0, 0 },
        { 0, 0, 100, 100, 100, 100, 0, 0 },
        { 0, 0, 100, 100, 100, 100, 0, 0 },
        { 0, 0, 100, 100, 100, 100, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    private static int[][] positions = {
        { 500, -150, 30, 10, 10, 30, -150, 500 },
        { -150, -250, 0, 0, 0, 0, -250, -150 },
        { 30, 0, 1, 2, 2, 1, 0, 30 },
        { 10, 0, 2, 0, 0, 2, 0, 10 },
        { 10, 0, 2, 0, 0, 2, 0, 10 },
        { 30, 0, 1, 2, 2, 1, 0, 30 },
        { -150, -250, 0, 0, 0, 0, -250, -150 },
        { 500, -150, 30, 10, 10, 30, -150, 500 }
    };

    public IngramOthelloPlayer(String name) {
        super(name);
    }

    public Square getMove(GameState currentState, Date deadline) {
        init(currentState);
        /*
        Square square = currentState.getValidMoves().toArray(new Square[0])[0];

        int maxH = -10000;
        for (Square validSquare : currentState.getValidMoves()) {
            int curH = h(currentState, validSquare);
            if (curH > maxH) {
                maxH = curH;
                square = validSquare;
            }
        }

        this.registerCurrentBestMove(square);
        
        if (deadline != null)
            log("I have " + this.getMillisUntilDeadline() + "ms remaining until the deadline.");
        */
        Node node = alphabeta(new Node(currentState, null, null), 7, new Node(Integer.MAX_VALUE), new Node(Integer.MIN_VALUE), me);
        Square square = node.getParentMove();
        System.out.println("me:" + currentState.getScore(me) + " them: " + currentState.getScore(them));
        System.out.println(node.getState());
        System.out.println(node.getValue());

        log("Example player is moving to " + square + "...");
        if (square == null) {
            try {
                Thread.sleep(30000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        return square;
    }
    
    
    private Node alphabeta(Node node, int depth, Node alpha, Node beta, Player player) {
        if (depth == 0 || node.getState().getValidMoves().size() == 0) {// || node is a terminal node
            node.setValue(h(node.getState(), node.getMove()));
            return node;
        }
        if (player == me) {
            for (Square move : node.getState().getValidMoves()){
                Node child = new Node(node.getState().applyMove(move), move, node.getParentMove(move));
                alpha = min(alpha, alphabeta(child, depth-1, alpha, beta, them));
                if(beta.getValue() >= alpha.getValue()){
                    break;
                }
            }
            return alpha;
        } else {
            for (Square move : node.getState().getValidMoves()){
                Node child = new Node(node.getState().applyMove(move), move, node.getParentMove());
                beta = max(beta, alphabeta(child, depth-1, alpha, beta, me));
                if (beta.getValue() >= alpha.getValue()) {
                    break;
                }
            }
            return beta;
        }
    }

    private Node max(Node a, Node b) {
        if(a.getValue() > b.getValue())
            return a;
        return b;
    }

    private Node min(Node a, Node b) {
        if(a.getValue() < b.getValue())
            return a;
        return b;
    }

    // Move should be applied BEFORE passing
    Integer h(GameState state, Square square) {
        int ret = discHeuristic(state) + 100*movesHeuristic(state) + positionHeuristic(state);

        //log("Heuristic for: " + square + "is: " + ret);
        return ret;
    }

    private int discHeuristic(GameState state) {
        int ret = state.getScore(state.getCurrentPlayer());
        //log("Disc heuristic:" + ret);
        return ret;
    }

    private int movesHeuristic(GameState state) {
        int ret = state.getValidMoves(me).size() - state.getValidMoves(them).size();
        //log("Moves heuristic:" + ret);
        return ret;
    }
    
    public int positionHeuristic(GameState state){
    	int [][] bonus = {
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 }
    	};
    	int ret = 0;
    	/*
    	Player currentCorner = state.getSquare(0, 0);
        if (currentCorner != Player.EMPTY) {
        	bonus[1][1] = bonus[1][1]-positions[1][1];
        	bonus[1][0] = bonus[1][0]-positions[1][0];
        	bonus[0][1] = bonus[0][1]-positions[0][1];
        	
        	for (int i = 0; i < 7; i++) {
        	    if (state.getSquare(0, i) == currentCorner){
        	        bonus[0][i] += 30;
        	    } else {
        	        break;
        	    }
        	}
            for (int i = 0; i < 7; i++) {
                if (state.getSquare(i, 0) == currentCorner){
                    bonus[i][0] += 30;
                } else {
                    break;
                }
            }
        }
        currentCorner = state.getSquare(0, 7);
        if (currentCorner != Player.EMPTY) {
            bonus[0][6] = bonus[0][6]-positions[0][6];
            bonus[1][6] = bonus[1][6]-positions[1][6];
            bonus[1][7] = bonus[1][7]-positions[1][7];

            for (int i = 6; i >= 0; i--) {
                if (state.getSquare(0, i) == currentCorner){
                    bonus[0][i] += 30;
                } else {
                    break;
                }
            }
            for (int i = 0; i < 7; i++) {
                if (state.getSquare(i, 7) == currentCorner){
                    bonus[i][7] += 30;
                } else {
                    break;
                }
            }
        }
        currentCorner = state.getSquare(7, 0);
        if (state.getSquare(7, 0) != Player.EMPTY) {
            bonus[6][0] = bonus[6][0]-positions[6][0];
            bonus[6][1] = bonus[6][1]-positions[6][1];
            bonus[7][1] = bonus[7][1]-positions[7][1];
            for (int i = 0; i < 7; i++) {
                if (state.getSquare(7, i) == currentCorner){
                    bonus[7][i] += 30;
                } else {
                    break;
                }
            }
            for (int i = 6; i >= 0; i--) {
                if (state.getSquare(i, 0) == currentCorner){
                    bonus[i][0] += 30;
                } else {
                    break;
                }
            }
        }
        currentCorner = state.getSquare(7, 7);
        if (currentCorner != Player.EMPTY) {
            bonus[6][7] = bonus[6][7]-positions[6][7];
            bonus[7][6] = bonus[7][6]-positions[7][6];
            bonus[6][6] = bonus[6][6]-positions[6][6];
            for (int i = 6; i >= 0; i--) {
                if (state.getSquare(7, i) == currentCorner){
                    bonus[7][i] += 30;
                } else {
                    break;
                }
            }
            for (int i = 6; i >= 0; i--) {
                if (state.getSquare(i, 7) == currentCorner){
                    bonus[i][7] += 30;
                } else {
                    break;
                }
            }
        }
        */
        for (int r = 0; r <= 7; r++){
            for (int c = 0; c <= 7; c++){
                if(state.getSquare(r, c) == me){
                    ret += positions[r][c] + bonus[r][c];
                } else if (state.getSquare(r, c) == them) {
                    ret -= (positions[r][c] + bonus[r][c]);
                }
            }
        }
        /*
        System.out.println("Position heuristic:" + ret);
        System.out.println(state);
        */
        return ret;
    }

    private void init(GameState currentState) {
        if (!initialized) {
            me = currentState.getCurrentPlayer();
            them = currentState.getOpponent(me);
            initialized = true;
        }
    }
}
