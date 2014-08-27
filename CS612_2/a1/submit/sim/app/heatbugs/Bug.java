package sim.app.heatbugs;

import sim.engine.Steppable;

public abstract class Bug implements Steppable {

    public abstract void setRandomMovementProbability(double randomMovementProbability);

}