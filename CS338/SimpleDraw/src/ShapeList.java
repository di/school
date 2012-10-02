/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #2
 */

import java.util.*;

class ShapeList
{
	private ArrayList<Shape> shapeList;
	
	public ShapeList() {
		shapeList = new ArrayList<Shape>();
	}

	public ArrayList<Shape> getShapeList() {
		return shapeList;
	}
	
	public Vector<String> getListData() {
		ColorUtility colorUtility = new ColorUtility();
		Vector<String> listData = new Vector<String>();
		for(int i=0; i<shapeList.size(); i++){
			String elementString = "<html>";
			
			int tmpType = shapeList.get(i).type;
			if(tmpType == 0) {
				elementString += "<b>Square</b>:" +
					" center (" +
					shapeList.get(i).p1X + "," + shapeList.get(i).p1Y + ")," +
					" size " + shapeList.get(i).p2X ;
			}
			if(tmpType == 1) { 
				elementString += "<b>Rectangle</b>:" +
				" center (" +
				shapeList.get(i).p1X + "," + shapeList.get(i).p1Y + ")," +
				" size (" + 
				shapeList.get(i).p2X + "," + shapeList.get(i).p2Y + ")" ;
			}
			if(tmpType == 2) {
				elementString += "<b>Circle</b>:" +
				" center (" +
				shapeList.get(i).p1X + "," + shapeList.get(i).p1Y + ")," +
				" radius " + shapeList.get(i).p2X ;
			}
			if(tmpType == 3) { 
				elementString += "<b>Oval</b>:" +
				" center (" +
				shapeList.get(i).p1X + "," + shapeList.get(i).p1Y + ")," +
				" radius (" + 
				shapeList.get(i).p2X + "," + shapeList.get(i).p2Y + ")" ;
			}
			if(tmpType == 4) {
				elementString += "<b>Line</b>:" +
				" position1 (" +
				shapeList.get(i).p1X + "," + shapeList.get(i).p1Y + ")," +
				" position2 (" + 
				shapeList.get(i).p2X + "," + shapeList.get(i).p2Y + ")" ;
			}
			if(shapeList.get(i).type != 4) {
				if(shapeList.get(i).fill)
					elementString += ", fill";
				else
					elementString += ", no fill";
			}
			elementString += " (" + colorUtility.colorToString(shapeList.get(i).color) + ")";
			elementString += "</html>";
			listData.addElement(elementString);
		}
		return listData;
	}

	public void add(Shape addShape) {
		Shape tmpShape = new Shape();
		tmpShape.color = addShape.color;
		tmpShape.fill = addShape.fill;
		tmpShape.p1X = addShape.p1X;
		tmpShape.p1Y = addShape.p1Y;
		tmpShape.p2X = addShape.p2X;
		tmpShape.p2Y = addShape.p2Y;
		tmpShape.type = addShape.type;		
		shapeList.add(tmpShape);			
	}

	public Shape remove(int selectedIndex) {
		Shape returnShape = shapeList.get(selectedIndex);
		shapeList.remove(selectedIndex);
		return returnShape;
	}		
}
