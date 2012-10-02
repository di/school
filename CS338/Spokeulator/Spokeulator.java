/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #1
 */

public class Spokeulator {
    public static void main(String[] args) {
        
        SpokeModel      model      = new SpokeModel();
        SpokeView       view       = new SpokeView(model);
        SpokeController controller = new SpokeController(model, view);
        
        view.setVisible(true);
    }
}
