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

    private int[][] positions = {
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
        Square square = alphabeta(new Node(currentState, null, null), 5, new Node(-10000), new Node(10000), them).getParentMove();

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
                alpha = max(alpha, alphabeta(child, depth-1, alpha, beta, them));
                if(beta.getValue() <= alpha.getValue()){
                    break;
                }
            }
            return alpha;
        } else {
            for (Square move : node.getState().getValidMoves()){
                Node child = new Node(node.getState().applyMove(move), move, node.getParentMove());
                beta = min(beta, alphabeta(child, depth-1, alpha, beta, me));
                if (beta.getValue() <= alpha.getValue()) {
                    break;
                }
            }
            return beta;
        }
    }

    private Player not(Player player) {
        if (player == me)
            return them;
        return me;
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
        int ret = state.getValidMoves(me).size();
        //log("Moves heuristic:" + ret);
        return ret;
    }
    
    private int positionHeuristic(GameState state){
        int ret = positions[square.getRow()][square.getCol()];
        //log("Position heuristic:" + ret);
        return ret;
    }

    private void init(GameState currentState) {
        if (!initialized) {
            me = currentState.getCurrentPlayer();
            them = currentState.getOpponent(currentState.getOpponent(me));
            initialized = true;
        }
    }
}
