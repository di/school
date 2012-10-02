import java.awt.Color;

/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #2
 */

public class Shape {

	int type;
	int p1X;
	int p1Y;
	int p2X;
	int p2Y;
	boolean fill;
	Color color;	

	public Shape() {
		this.p1X = -1;
		this.p1Y = -1;
		this.p2X = -1;
		this.p2Y = -1;
		this.color = null;		
	}
	
	public Shape(int type, int p1X, int p1Y, int p2X, int p2Y, boolean fill, Color color) {
		this.type = type;
		this.p1X = p1X;
		this.p1Y = p1Y;
		this.p2X = p2X;
		this.p2Y = p2Y;
		this.fill = fill;
		this.color = color;
	}
	
	public Shape(int type, int p1X, int p1Y, int p2X, boolean fill, Color color){
		this.type = type;
		this.p1X = p1X;
		this.p1Y = p1Y;
		this.p2X = p2X;
		this.p2Y = -1;
		this.fill = fill;
		this.color = color;
	}

	public boolean isComplete() {
		if(this.p1X >= 0 && this.p1Y >= 0 && this.p2X >= 0 && this.color != null) {
			if (this.type == 0 || this.type == 2 || this.p2Y >=0) {
				return true;			
			}			
		}
		return false;
	}
}
