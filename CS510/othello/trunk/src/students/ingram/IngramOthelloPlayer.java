package students.ingram;

import java.util.AbstractSet;
import java.util.Date;

import edu.drexel.cs.ai.othello.GameState;
import edu.drexel.cs.ai.othello.GameState.Player;
import edu.drexel.cs.ai.othello.OthelloPlayer;
import edu.drexel.cs.ai.othello.Square;

class State {
    public GameState state;
    public Square parentMove;
    public int value;
    public int depth;
    
    public State(GameState state, Square parentMove, int depth, int value) {
        this.state = state;
        this.parentMove = parentMove;
        this.depth = depth;
        this.value = value;
    }
    
    public State(int value) {
        this.value = value;
    }
    
    public int getValue() {
        return this.value;
    }
    
    public boolean terminal() {
        return (this.depth == 0 || this.actions().size() == 0);
    }

    public AbstractSet<Square> actions() {
        return this.state.getValidMoves();
    }
}

public class IngramOthelloPlayer extends OthelloPlayer {
    private Player me;
    private Player them;
    private boolean initialized = false;
    private int MAX_DEPTH = 7;
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
        if (!initialized) {
            me = currentState.getCurrentPlayer();
            them = currentState.getOpponent(me);
            initialized = true;
        }
            
        /*
        this.registerCurrentBestMove(square);
        
        if (deadline != null)
            log("I have " + this.getMillisUntilDeadline() + "ms remaining until the deadline.");
        */
        State node;
        node = alphabeta(new State(currentState, null, MAX_DEPTH, 0));
        log("Ingram moving to: " + node.parentMove);
        return node.parentMove;
    }

    private State alphabeta(State state) {
        return maxValue(state, new State(Integer.MIN_VALUE), new State(Integer.MAX_VALUE));
    }
    
    private State maxValue(State state, State alpha, State beta) {
        if(state.terminal()){
            return state;
        }
        State v  = new State(Integer.MIN_VALUE);
        for (Square move : state.actions()){
            v = max(v, minValue(result(state, move), alpha, beta));
            if (v.getValue() >= beta.getValue()) {
                return v;
            }
            alpha = max(alpha, v);
        }
        return v;
    }
    
    private State minValue(State state, State alpha, State beta) {
        if(state.terminal()){
            return state;
        }
        State v  = new State(Integer.MAX_VALUE);
        for (Square move : state.actions()){
            v = min(v, maxValue(result(state, move), alpha, beta));
            if (v.getValue() <= alpha.getValue()) {
                return v;
            }
            beta = min(beta, v);
        }
        return v;
    }

    private State max(State a, State b) {
        if(a.getValue() > b.getValue())
            return a;
        return b;
    }

    private State min(State a, State b) {
        if(a.getValue() < b.getValue())
            return a;
        return b;
    }
    
    public State result(State state, Square move) {
        GameState newState = state.state.applyMove(move);
        if (state.parentMove == null) {
            return new State(newState, move, state.depth-1, h(newState));
        } else {
            return new State(newState, state.parentMove, state.depth-1, h(newState));
        }
    }
    
    // Move should be applied BEFORE passing
    int h(GameState state) {
        float count = state.getScore(me) + state.getScore(them);
        int dh = (int)(Math.floor(100*Math.pow((count/64), 7)))*discHeuristic(state);
        int mh = (int)(Math.floor(100*(1-(count/64.0))))*movesHeuristic(state);
        int ph = positionHeuristic(state);
        //System.out.println((int)count + ", " + dh + ", " + mh + ", " + ph);
        return dh + mh + ph;
    }

    private int discHeuristic(GameState state) {
        int ret = state.getScore(me) - state.getScore(them);
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
}
