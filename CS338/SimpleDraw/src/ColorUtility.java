// Modified this a little to suit my needs. - DI

/* Author: Donald Naegely - dpn52@drexel.edu
 * File Name: ColorUtility.java
 * Last Modified: 1/24/2008
 * Description: The toString() method for the Java object returns
 * output meant more for debugging than printing. Since there is
 * no easy way for to get the name of the color out of the color
 * class this class contains a function colorToString that takes
 * an RGB value representing a color and returns the name of the
 * color. If the RGB value does not match any of the following 
 * colors:
 * 		Black
 * 		Blue
 * 		Green
 * 		Red
 * 		Yellow
 * then the string "Unkown" will be returned. To use this file, 
 * place it in your project and then call ColorUtility.colorToString().
 * 
 * Example:
 * 
 * 		Color c;
 * 		c = Color.BLACK;
 * 		System.out.println("c is " + ColorUtility.colorToString(c.getRGB()));
 */

import java.awt.Color;

public class ColorUtility {
	/* Color.toString() is not great so we need a way to convert a 
	 * Color to some easily readable format, since we only 
	 * support black, white, blue, green, red, & yellow we can 
	 * easily check these by looking at the RGB values of the
	 * color found by calling Color.getRGB().
	 */
	public String colorToString(Color color) {
		if ( color.getRGB() == Color.BLACK.getRGB() ) {
			return "Black";
		}
		else if ( color.getRGB() == Color.BLUE.getRGB() ) {
			return "Blue";
		}
		else if ( color.getRGB() == Color.GREEN.getRGB() ) {
			return "Green";
		}
		else if ( color.getRGB() == Color.RED.getRGB() ) {
			return "Red";
		}
		else if ( color.getRGB() == Color.YELLOW.getRGB() ) {
			return "Yellow";
		}
		else {
			return "No Color Information";
		}
	}
}
