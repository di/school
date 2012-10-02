import java.awt.event.*;

public class SpokeController {
    private SpokeModel spokeModel;
    private SpokeView  spokeView;
    
    SpokeController(SpokeModel model, SpokeView view) {
        spokeModel = model;
        spokeView  = view;
        
        view.addCalculatorListener(new CalculatorListener());        
        view.addUpdateListener(new UpdateListener());           
        view.addQuestionListener(new QuestionListener()); 
    }
    
    class CalculatorListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
        	spokeView.updateModel();
        	spokeModel.calculate();
        	spokeView.updateOutput();
        	spokeView.redraw();
           
        }
    }  
    
    class QuestionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
        	spokeView.updateQuestion();           
        }
    }  
    
    class UpdateListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
        	
           Rim tmpRim = (Rim)spokeModel.getRimList().get(spokeView.getRimIndex());
           Hub tmpHub = (Hub)spokeModel.getHubList().get(spokeView.getHubIndex());
           
           spokeModel.update(-1,
        		   tmpRim.getErd(),
        		   tmpRim.getOsb(),
        		   tmpHub.getWL(),
        		   tmpHub.getWR(),
        		   tmpHub.getDL(),
        		   tmpHub.getDR(),
        		   -1);
           
           spokeView.updateView();
           spokeModel.calculate();
           spokeView.updateOutput();
           spokeView.redraw();           
           
        }
    }  
}
