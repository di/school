package edu.drexel.cs.ai.othello;

import edu.drexel.cs.ai.othello.GameState.GameStatus;
import edu.drexel.cs.ai.othello.GameState.Player;

public class BatchUserInterface implements UserInterface, Logger {

    @Override
    public void handleStateUpdate(GameState newState) {
        GameStatus status = newState.getStatus();
        if(status != GameStatus.PLAYING) {
            System.out.println(newState.getScore(Player.PLAYER1) + "," + newState.getScore(Player.PLAYER2));
        }
    }

    @Override
    public OthelloPlayer[] getPlayers() {
        return null;
    }

    @Override
    public void setPlayers(OthelloPlayer player1, OthelloPlayer player2) {}

    @Override
    public void updateTimeRemaining(OthelloPlayer player, int secondsRemaining) {}

    @Override
    public void updateTimeUsed(OthelloPlayer player, long millisUsed) {}

    @Override
    public void log(String message, Object source) {}
    
}