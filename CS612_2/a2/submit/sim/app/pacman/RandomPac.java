/*
  Copyright 2009  by Sean Luke and Vittorio Zipparo
  Licensed under the Academic Free License version 3.0
  See the file "LICENSE" for more information
*/

package sim.app.pacman;
import sim.engine.*;
import sim.field.continuous.*;
import sim.portrayal.Oriented2D;
import sim.util.*;
import ec.util.*;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Random;

/* The Pac is the Pac Man in the game.  Pac is an Agent and is also Steppable.  The Pac moves first, then the ghosts. */

public class RandomPac extends Pac
    {

    Random random;
    ArrayList<Integer> lastPossibleActions = new ArrayList<Integer>();
    int lastBestAction = Pac.E; // Go right when the level starts
    int timeInThisDirection = 0;

    public RandomPac(PacMan pacman, Ghost blinky, Ghost pinky, Ghost inky, Ghost clyde) 
        {
        super(pacman, 0);
        this.random = new Random();
        }

    /*
     * Return a random valid action
     */
    protected int getRandomAction(SimState state){
        ArrayList<Integer> possibleActions = new ArrayList<Integer>();
        if(isPossibleToDoAction(Pac.N)){
            possibleActions.add(Pac.N);
        }
        if(isPossibleToDoAction(Pac.E)){
            possibleActions.add(Pac.E);
        }
        if(isPossibleToDoAction(Pac.S)){
            possibleActions.add(Pac.S);
        }
        if(isPossibleToDoAction(Pac.W)){
            possibleActions.add(Pac.W);
        }
        int bestAction = lastBestAction;
        timeInThisDirection++;
        if(!possibleActions.equals(lastPossibleActions) && timeInThisDirection > 7){
            bestAction = possibleActions.get(random.nextInt(possibleActions.size()));
            timeInThisDirection = 0;
        }
        lastPossibleActions = possibleActions;
        lastBestAction = bestAction;
        return bestAction;
    }


    protected void doPolicyStep(SimState state)
        {
        int nextAction = getRandomAction(state);

        if (isPossibleToDoAction(nextAction))
            {
            performAction(nextAction);
            }
        else if (isPossibleToDoAction(lastAction))
            {
            performAction(lastAction);
            }
        }
    }