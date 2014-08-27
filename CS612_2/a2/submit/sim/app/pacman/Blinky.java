/*
  Copyright 2009  by Sean Luke and Vittorio Zipparo
  Licensed under the Academic Free License version 3.0
  See the file "LICENSE" for more information
*/

package sim.app.pacman;
import java.util.Random;

import sim.engine.*;
import sim.field.continuous.*;
import sim.util.*;
import ec.util.*;

/** Blinky is the red ghost.  He starts outside of the box (and is not initially waiting).
    His target (see Ghost.java) is the Pac himself.  */
        
public class Blinky extends Ghost
    {
    private static final long serialVersionUID = 1;
    Random rand = new Random();


    public Double2D getStartLocation() { return new Double2D(13.5, 13); }

    public Blinky(PacMan pacman) 
        {
        super(pacman);
        waiting = 0;  // not waiting.
        }
        
    public Double2D getTarget()
        {
        MutableDouble2D loc = new MutableDouble2D();
        Pac pman = pacman.pacClosestTo(location);
        double x_diff = Math.abs(this.location.x - pman.location.x);
        double y_diff = Math.abs(this.location.y - pman.location.y);
        double manhattan_dist = Math.sqrt(Math.pow(x_diff, 2) + Math.pow(y_diff, 2));
        if (manhattan_dist <= 3){
            loc.x = 0;
            loc.y = 0;
        }
        else {
            loc.x = Math.min(Math.abs(pman.location.x + rand.nextInt((int)manhattan_dist/2) - (int)(manhattan_dist/4)), 28);
            loc.y = Math.min(Math.abs(pman.location.y + rand.nextInt((int)manhattan_dist/2) - (int)(manhattan_dist/4)), 28);
        }

        return new Double2D(loc);  
        }
    }
