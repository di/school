package chess;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JPanel;

public class JChessPanel extends JPanel {

	private static final long serialVersionUID = 3962278883941748353L;
	
	private Position position;
	private Color originalBackground;	
	
	private boolean isLight;

	private Color light = new Color(255, 206, 158);
	private Color dark = new Color(209, 139, 71);
	private Color darkShaded = new Color(133, 88, 45);
	private Color lightShaded = new Color(178, 144, 111);

	public JChessPanel(BorderLayout layout) {
		super(layout);
	}

	public Position getPosition() {
		return this.position;
	}
	
	public void setPosition(int cellNumber){
		this.position = new Position(cellNumber);
	}
	
	public Color originalBackground(){
		return this.originalBackground;
	}

	public void setOriginalBackground(Color color) {
		this.originalBackground = color;		
	}

	public void setIsLight(boolean b) {
		this.isLight = b;
		this.unshade();
	}
	
	public void shade() {
		if (isLight){
			this.setBackground(lightShaded);
		}
		else {
			this.setBackground(darkShaded);
		}
	}
	
	public void unshade() {
		if (isLight){
			this.setBackground(light);
		}
		else {
			this.setBackground(dark);
		}
	}
}
