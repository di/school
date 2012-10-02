import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import static java.lang.Math.*;

public class SpokeCanvas extends Canvas {
    
	private static final long serialVersionUID = 1L;
	private SpokeModel spokeModel;
    private int MAX_MM = 700;
    private int MAX_HEIGHT;
	private int MAX_WIDTH;

	public void paint(Graphics g) {
		
		if(spokeModel != null) {
			
			g.setColor(new Color(0,0,0));
			MAX_HEIGHT = this.getHeight();
			MAX_WIDTH = this.getWidth();
			int center_x = MAX_WIDTH/2;
			int center_y = MAX_HEIGHT/2;
			
			int rimSize = mmToPixels(spokeModel.getErdInput());
			g.drawOval(center_x-rimSize/2, center_y-rimSize/2, rimSize, rimSize);
			
			int hubSize = mmToPixels(spokeModel.getDlInput());
			g.drawOval(center_x-hubSize/2, center_y-hubSize/2, hubSize, hubSize);
			
			//Draw Rim Holes			
			ArrayList<Integer> rimHolesX = new ArrayList<Integer>();
			ArrayList<Integer> rimHolesY = new ArrayList<Integer>();
			
			for (int i = 0; i<spokeModel.getNumSpokes(); i++)
			{
				int x = (int)(rimSize/2*Math.cos( (2*Math.PI/spokeModel.getNumSpokes())*i ));
				int y = (int)(rimSize/2*Math.sin( (2*Math.PI/spokeModel.getNumSpokes())*i ));
				rimHolesX.add(center_x + x);
				rimHolesY.add(center_y - y);
			}
			for (int i = 0; i<spokeModel.getNumSpokes(); i++)
			{
				g.drawOval(rimHolesX.get(i)-1, rimHolesY.get(i)-1, 2, 2);				
			}
			
			//Draw Hub Holes			
			ArrayList<Integer> hubHolesX = new ArrayList<Integer>();
			ArrayList<Integer> hubHolesY = new ArrayList<Integer>();
			
			for (int i = 0; i<spokeModel.getNumSpokes(); i++)
			{
				int x = (int)(hubSize/2*Math.cos( (2*Math.PI/spokeModel.getNumSpokes())*i ));
				int y = (int)(hubSize/2*Math.sin( (2*Math.PI/spokeModel.getNumSpokes())*i ));
				hubHolesX.add(center_x + x);
				hubHolesY.add(center_y - y);
			}
			
			//Draw Spokes
			
			int numSpokes = spokeModel.getNumSpokes(); 
			int numCrosses = (int) spokeModel.getCInput();
			
			for (int i = 0; i<numSpokes; i++)
			{
				if (i%4 == 0)
					g.drawLine(rimHolesX.get(i), rimHolesY.get(i), hubHolesX.get((i+numCrosses*2)%(numSpokes-1)), hubHolesY.get((i+numCrosses*2)%(numSpokes-1)));
				if ((i+1)%4 == 0)
					g.drawLine(rimHolesX.get(i), rimHolesY.get(i), hubHolesX.get((i+numCrosses*2)%(numSpokes-1)), hubHolesY.get((i+numCrosses*2)%(numSpokes-1)));
				if ((i+2)%4 == 0){
					int tmp = i-numCrosses*2;
					if (tmp < 0) 
						tmp = numSpokes - 1 + tmp;
					g.drawLine(rimHolesX.get(i), rimHolesY.get(i), hubHolesX.get(tmp), hubHolesY.get(tmp));
				}
				if ((i+3)%4 == 0){
					int tmp = i-numCrosses*2;
					if (tmp < 0) 
						tmp = numSpokes - 1 + tmp;
					g.drawLine(rimHolesX.get(i), rimHolesY.get(i), hubHolesX.get(tmp), hubHolesY.get(tmp));
				}
					
				
			}
			
		}		
	}

	public void setModel(SpokeModel spokeModel) {
		this.spokeModel = spokeModel;		
	}
	
	public int mmToPixels(double mm){
		return (int)round(mm*((double)MAX_HEIGHT/(double)MAX_MM));		
	}
}
