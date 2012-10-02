/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #2
 */

import java.util.Vector;

public class InputManager {
	
	ShapeList shapeList;
	
	public InputManager() {
		shapeList = new ShapeList();
	}
	

	public void add(Shape newShape) {
		shapeList.add(newShape);
	}

	public void change() {
		// TODO Auto-generated method stub
		
	}

	public Shape remove(int selectedIndex) {
		return shapeList.remove(selectedIndex);		
	}
	
	public ShapeList getShapeList()
	{
		return shapeList;
	}

	public Vector<String> getListData() {
		return shapeList.getListData();
	}

}
