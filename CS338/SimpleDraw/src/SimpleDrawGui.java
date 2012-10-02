/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #2
 */

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowFocusListener;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

public class SimpleDrawGui {

	private JFrame frame;
	private JSplitPane splitPane;
	private JPanel leftPane;
	private JPanel leftPaneTop;
	private JPanel leftPaneBottom;
	private JPanel rightPane;
	private JList shapeListComponent;
	private JScrollPane shapeListScrollPane;
	private JTabbedPane tabbedPane;
	private JDialog inputDialog;
	private Canvas canvas;
	
	private JPanel squarePanel;
	private JPanel rectanglePanel;
	private JPanel circlePanel;
	private JPanel ovalPanel;
	private JPanel linePanel;
		
	private Dimension maximumSize = new Dimension(600,25);
	
	private InputManager inputManager = new InputManager();
	
	public SimpleDrawGui() {		
		
		shapeListComponent = new JList();
		shapeListComponent.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			
		shapeListScrollPane = new JScrollPane(shapeListComponent);
		shapeListScrollPane.setPreferredSize(new Dimension(240, 380));
		
		leftPaneTop = new JPanel();
		leftPaneTop.setBorder(BorderFactory.createTitledBorder("Shape List:"));
		leftPaneTop.add(shapeListScrollPane);		
		
		buildTabbedPane(-1, null);
						
		JButton addButton = new JButton("Add");
		addButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				buildTabbedPane(-1, null);
				inputDialog.setVisible(true);
			} 
		} );

		JButton changeButton = new JButton("Change");
		changeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedIndex = shapeListComponent.getSelectedIndex();
				if (selectedIndex >= 0)
				{
					Shape changeShape = inputManager.remove(selectedIndex);
					buildTabbedPane(changeShape.type, changeShape);
					inputDialog.setVisible(true);
					
					shapeListComponent.setListData(inputManager.getListData());
				}
				
				shapeListComponent.setListData(inputManager.getListData());
				shapeListScrollPane.revalidate();
				shapeListScrollPane.repaint();
				paint();
			} 
		} );
		
		JButton removeButton = new JButton("Remove");
		removeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedIndex = shapeListComponent.getSelectedIndex();
				if (selectedIndex >= 0)
				{
					inputManager.remove(selectedIndex);
					shapeListComponent.setListData(inputManager.getListData());
				}
			} 
		} );
		
		leftPaneBottom = new JPanel();
		leftPaneBottom.setBorder(BorderFactory.createTitledBorder("Actions:"));
		leftPaneBottom.setMaximumSize(new Dimension(600, 600));
		leftPaneBottom.add(addButton);
		leftPaneBottom.add(changeButton);
		leftPaneBottom.add(removeButton);
		
		leftPane = new JPanel();
		leftPane.add(leftPaneTop);
		leftPane.add(leftPaneBottom);
		leftPane.setLayout(new BoxLayout(leftPane, BoxLayout.Y_AXIS));
		
		canvas = new Canvas();
		canvas.setBackground(Color.white);
		
		rightPane = new JPanel();
		rightPane.setLayout(new BoxLayout(rightPane, BoxLayout.Y_AXIS));
		rightPane.setBorder(BorderFactory.createTitledBorder("Shape Canvas"));
		rightPane.add(canvas);
		
		splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, leftPane, rightPane);
		splitPane.setOneTouchExpandable(true);
		splitPane.setDividerLocation(260);
		
		frame = new JFrame( "SimpleDraw.java" );
		frame.setSize( 750, 500 );
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);		
		frame.getContentPane().add( splitPane );
		frame.addWindowFocusListener(new WindowFocusListener() {

			@Override
			public void windowGainedFocus(WindowEvent e) {
				paint();				
			}

			@Override
			public void windowLostFocus(WindowEvent e) {
				// TODO Auto-generated method stub
				
			}		
		});
		frame.setVisible(true);
		
		
	}

	private void buildTabbedPane(int selectedTab, Shape changeShape) {
		
		createSquarePanel(null);
		createRectanglePanel(null);
		createCirclePanel(null);
		createOvalPanel(null);
		createLinePanel(null);
		
		if(changeShape != null) {
			int changeShapeType = changeShape.type;
			if (changeShapeType == 0)
				createSquarePanel(changeShape);
			if (changeShapeType == 1)
				createRectanglePanel(changeShape);
			if (changeShapeType == 2)
				createCirclePanel(changeShape);
			if (changeShapeType == 3)
				createOvalPanel(changeShape);
			if (changeShapeType == 4)
				createLinePanel(changeShape);
		}
				
		tabbedPane = new JTabbedPane();
		tabbedPane.add(squarePanel, "Square");
		tabbedPane.add(rectanglePanel, "Rectangle");
		tabbedPane.add(circlePanel, "Circle");
		tabbedPane.add(ovalPanel, "Oval");
		tabbedPane.add(linePanel, "Line");
		
		if (selectedTab >= 0 && selectedTab <= tabbedPane.getTabCount()){
			tabbedPane.setSelectedIndex(selectedTab);
		}
		
		inputDialog = new JDialog();
		inputDialog.setSize(400, 400);
		inputDialog.add(tabbedPane);
	}

	private void createSquarePanel(Shape shape) {
		
		squarePanel = new JPanel();
		squarePanel.setLayout(new BoxLayout(squarePanel, BoxLayout.Y_AXIS));
		squarePanel.setBorder(new EmptyBorder(20,20,20,20));
				
		JLabel p1XLabel = new JLabel("Center (X):");
		squarePanel.add(p1XLabel);
		
		final JTextField p1XField = new JTextField();
		p1XField.setMaximumSize(maximumSize);
		p1XField.setName("p1XField");
		squarePanel.add(p1XField);
		
		JLabel p1YLabel = new JLabel("Center (Y):");
		squarePanel.add(p1YLabel);
		
		final JTextField p1YField = new JTextField();
		p1YField.setMaximumSize(maximumSize);
		p1YField.setName("p1YField");
		squarePanel.add(p1YField);
		
		JLabel p2XLabel = new JLabel("Size (of one side):");
		squarePanel.add(p2XLabel);
		
		final JTextField p2XField = new JTextField();
		p2XField.setMaximumSize(maximumSize);
		p2XField.setName("p2XField");
		squarePanel.add(p2XField);
		
		JPanel fillOptionPane = new JPanel();
	    fillOptionPane.setAlignmentX(0);
		fillOptionPane.setLayout(new BoxLayout(fillOptionPane,BoxLayout.X_AXIS));
		fillOptionPane.add(new JLabel("Fill: "));
		ButtonGroup fillOptionGroup = new ButtonGroup();
	    final JRadioButton fillOption0 = new JRadioButton("Yes", true);
	    fillOptionGroup.add(fillOption0);
	    fillOptionPane.add(fillOption0);
	    JRadioButton fillOption1 = new JRadioButton("No", false);
	    fillOptionGroup.add(fillOption1);
	    fillOptionPane.add(fillOption1);
	    squarePanel.add(fillOptionPane);
	    
	    JPanel colorOptionPane = new JPanel();
	    colorOptionPane.setAlignmentX(0);
		colorOptionPane.setLayout(new BoxLayout(colorOptionPane,BoxLayout.X_AXIS));
		colorOptionPane.add(new JLabel("Color: "));
		ButtonGroup colorOptionGroup = new ButtonGroup();
	    final JRadioButton colorOption0 = new JRadioButton("Black", true);
	    colorOptionGroup.add(colorOption0);
	    colorOptionPane.add(colorOption0);
	    final JRadioButton colorOption1 = new JRadioButton("Blue", false);
	    colorOptionGroup.add(colorOption1);
	    colorOptionPane.add(colorOption1);
	    final JRadioButton colorOption2 = new JRadioButton("Green", false);
	    colorOptionGroup.add(colorOption2);
	    colorOptionPane.add(colorOption2);
	    final JRadioButton colorOption3 = new JRadioButton("Red", false);
	    colorOptionGroup.add(colorOption3);
	    colorOptionPane.add(colorOption3);
	    final JRadioButton colorOption4 = new JRadioButton("Yellow", false);
	    colorOptionGroup.add(colorOption4);
	    colorOptionPane.add(colorOption4);	   
	    squarePanel.add(colorOptionPane);
	    
	    JPanel buttonPanel = new JPanel();
	    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
	    buttonPanel.setBorder(new EmptyBorder(20,50,20,50));
	    
	    JButton cancelButton = new JButton("Cancel");
	    cancelButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inputDialog.setVisible(false);
			} 
		} );
	    buttonPanel.add(cancelButton);
	    
	    buttonPanel.add(Box.createHorizontalGlue());
	    
	    JButton okButton = new JButton("OK");
	    okButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Color color;
				if (colorOption0.isSelected())
					color = Color.BLACK;
				else if (colorOption1.isSelected())
					color = Color.BLUE;
				else if (colorOption2.isSelected())
					color = Color.GREEN;
				else if (colorOption3.isSelected())
					color = Color.RED;
				else if (colorOption4.isSelected())
					color = Color.YELLOW;
				else
					color = null;
				Shape addShape = new Shape(0, new Integer(p1XField.getText()), new Integer(p1YField.getText()), 
						new Integer(p2XField.getText()), fillOption0.isSelected(), color);
				if(addShape.isComplete()) {
					inputManager.add(addShape);
					shapeListComponent.setListData(inputManager.getListData());
					shapeListScrollPane.revalidate();
					shapeListScrollPane.repaint();
					inputDialog.setVisible(false);
					paint();
				}
			} 
		} );
	    buttonPanel.add(okButton);
	    buttonPanel.setAlignmentX(0);
	    
	    squarePanel.add(buttonPanel);    

		if(shape != null){
	    	p1XField.setText(new Integer(shape.p1X).toString());
	    	p1YField.setText(new Integer(shape.p1Y).toString());
	    	p2XField.setText(new Integer(shape.p2X).toString());
	    	fillOption0.setSelected(false);
    		fillOption1.setSelected(false);
	    	if(shape.fill) {
	    		fillOption0.setSelected(true);
	    	}
	    	else{	    		
	    		fillOption1.setSelected(true);
	    	}
	    	
	    	colorOption0.setSelected(false);
	    	colorOption1.setSelected(false);
	    	colorOption2.setSelected(false);
	    	colorOption3.setSelected(false);
	    	colorOption4.setSelected(false);
	    	
	    	if (shape.color == Color.BLACK)
	    		colorOption0.setSelected(true);
			else if (shape.color == Color.BLUE)
				colorOption1.setSelected(true);
			else if (shape.color== Color.GREEN)
				colorOption2.setSelected(true);
			else if (shape.color== Color.RED)
				colorOption3.setSelected(true);
			else if (shape.color == Color.YELLOW)
				colorOption4.setSelected(true);
	    		
	    }
		
	}

	private void createRectanglePanel(Shape shape) {
		
		rectanglePanel = new JPanel();
		rectanglePanel.setLayout(new BoxLayout(rectanglePanel, BoxLayout.Y_AXIS));
		rectanglePanel.setBorder(new EmptyBorder(20,20,20,20));
		
		JLabel p1XLabel = new JLabel("Center (X):");
		rectanglePanel.add(p1XLabel);
		
		final JTextField p1XField = new JTextField();
		p1XField.setMaximumSize(maximumSize);
		p1XField.setName("p1XField");		
		rectanglePanel.add(p1XField);
		
		JLabel p1YLabel = new JLabel("Center (Y):");
		rectanglePanel.add(p1YLabel);
		
		final JTextField p1YField = new JTextField();
		p1YField.setMaximumSize(maximumSize);
		p1YField.setName("p1YField");
		rectanglePanel.add(p1YField);
		
		JLabel p2XLabel = new JLabel("Size (X):");
		rectanglePanel.add(p2XLabel);
		
		final JTextField p2XField = new JTextField();
		p2XField.setMaximumSize(maximumSize);
		p2XField.setName("p2XField");
		rectanglePanel.add(p2XField);
		
		JLabel p2YLabel = new JLabel("Size (Y):");
		rectanglePanel.add(p2YLabel);
		
		final JTextField p2YField = new JTextField();
		p2YField.setMaximumSize(maximumSize);
		p2YField.setName("p2YField");
		rectanglePanel.add(p2YField);
		
		JPanel fillOptionPane = new JPanel();
	    fillOptionPane.setAlignmentX(0);
		fillOptionPane.setLayout(new BoxLayout(fillOptionPane,BoxLayout.X_AXIS));
		fillOptionPane.add(new JLabel("Fill: "));
		ButtonGroup fillOptionGroup = new ButtonGroup();
	    final JRadioButton fillOption0 = new JRadioButton("Yes", true);
	    fillOptionGroup.add(fillOption0);
	    fillOptionPane.add(fillOption0);
	    JRadioButton fillOption1 = new JRadioButton("No", false);
	    fillOptionGroup.add(fillOption1);
	    fillOptionPane.add(fillOption1);
	    rectanglePanel.add(fillOptionPane);
	    
	    JPanel colorOptionPane = new JPanel();
	    colorOptionPane.setAlignmentX(0);
		colorOptionPane.setLayout(new BoxLayout(colorOptionPane,BoxLayout.X_AXIS));
		colorOptionPane.add(new JLabel("Color: "));
		ButtonGroup colorOptionGroup = new ButtonGroup();
	    final JRadioButton colorOption0 = new JRadioButton("Black", true);
	    colorOptionGroup.add(colorOption0);
	    colorOptionPane.add(colorOption0);
	    final JRadioButton colorOption1 = new JRadioButton("Blue", false);
	    colorOptionGroup.add(colorOption1);
	    colorOptionPane.add(colorOption1);
	    final JRadioButton colorOption2 = new JRadioButton("Green", false);
	    colorOptionGroup.add(colorOption2);
	    colorOptionPane.add(colorOption2);
	    final JRadioButton colorOption3 = new JRadioButton("Red", false);
	    colorOptionGroup.add(colorOption3);
	    colorOptionPane.add(colorOption3);
	    final JRadioButton colorOption4 = new JRadioButton("Yellow", false);
	    colorOptionGroup.add(colorOption4);
	    colorOptionPane.add(colorOption4);	   
	    rectanglePanel.add(colorOptionPane);
		
	    JPanel buttonPanel = new JPanel();
	    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
	    buttonPanel.setBorder(new EmptyBorder(20,50,20,50));
	    
	    JButton cancelButton = new JButton("Cancel");
	    cancelButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inputDialog.setVisible(false);
			} 
		} );
	    buttonPanel.add(cancelButton);
	    
	    buttonPanel.add(Box.createHorizontalGlue());
	    
	    JButton okButton = new JButton("OK");
	    okButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Color color;
				if (colorOption0.isSelected())
					color = Color.BLACK;
				else if (colorOption1.isSelected())
					color = Color.BLUE;
				else if (colorOption2.isSelected())
					color = Color.GREEN;
				else if (colorOption3.isSelected())
					color = Color.RED;
				else if (colorOption4.isSelected())
					color = Color.YELLOW;
				else
					color = null;				
				Shape addShape = new Shape(1, new Integer(p1XField.getText()), new Integer(p1YField.getText()), 
						new Integer(p2XField.getText()), new Integer(p2YField.getText()), fillOption0.isSelected(), color);
				if(addShape.isComplete()) {
					inputManager.add(addShape);
					shapeListComponent.setListData(inputManager.getListData());
					shapeListScrollPane.revalidate();
					shapeListScrollPane.repaint();
					inputDialog.setVisible(false);
					paint();
				}
			}
		} );
	    buttonPanel.add(okButton);
	    buttonPanel.setAlignmentX(0);	 
	    
	    if(shape != null){
	    	p1XField.setText(new Integer(shape.p1X).toString());
	    	p1YField.setText(new Integer(shape.p1Y).toString());
	    	p2XField.setText(new Integer(shape.p2X).toString());
	    	p2YField.setText(new Integer(shape.p2Y).toString());
	    	fillOption0.setSelected(false);
    		fillOption1.setSelected(false);
	    	if(shape.fill) {
	    		fillOption0.setSelected(true);
	    	}
	    	else{	    		
	    		fillOption1.setSelected(true);
	    	}
	    	
	    	colorOption0.setSelected(false);
	    	colorOption1.setSelected(false);
	    	colorOption2.setSelected(false);
	    	colorOption3.setSelected(false);
	    	colorOption4.setSelected(false);
	    	
	    	if (shape.color == Color.BLACK)
	    		colorOption0.setSelected(true);
			else if (shape.color == Color.BLUE)
				colorOption1.setSelected(true);
			else if (shape.color== Color.GREEN)
				colorOption2.setSelected(true);
			else if (shape.color== Color.RED)
				colorOption3.setSelected(true);
			else if (shape.color == Color.YELLOW)
				colorOption4.setSelected(true);
	    		
	    }
	    
	    rectanglePanel.add(buttonPanel);
	}
	
	private void createCirclePanel(Shape shape) {
		circlePanel = new JPanel();
		circlePanel.setLayout(new BoxLayout(circlePanel, BoxLayout.Y_AXIS));
		circlePanel.setBorder(new EmptyBorder(20,20,20,20));
		
		JLabel p1XLabel = new JLabel("Center (X):");
		circlePanel.add(p1XLabel);
		
		final JTextField p1XField = new JTextField();
		p1XField.setMaximumSize(maximumSize);
		p1XField.setName("p1XField");
		circlePanel.add(p1XField);
		
		JLabel p1YLabel = new JLabel("Center (Y):");
		circlePanel.add(p1YLabel);
		
		final JTextField p1YField = new JTextField();
		p1YField.setMaximumSize(maximumSize);
		p1YField.setName("p1YField");
		circlePanel.add(p1YField);
		
		JLabel p2XLabel = new JLabel("Radius:");
		circlePanel.add(p2XLabel);
		
		final JTextField p2XField = new JTextField();
		p2XField.setMaximumSize(maximumSize);
		p2XField.setName("p2XField");
		circlePanel.add(p2XField);
		
		JPanel fillOptionPane = new JPanel();
	    fillOptionPane.setAlignmentX(0);
		fillOptionPane.setLayout(new BoxLayout(fillOptionPane,BoxLayout.X_AXIS));
		fillOptionPane.add(new JLabel("Fill: "));
		ButtonGroup fillOptionGroup = new ButtonGroup();
	    final JRadioButton fillOption0 = new JRadioButton("Yes", true);
	    fillOptionGroup.add(fillOption0);
	    fillOptionPane.add(fillOption0);
	    JRadioButton fillOption1 = new JRadioButton("No", false);
	    fillOptionGroup.add(fillOption1);
	    fillOptionPane.add(fillOption1);
	    circlePanel.add(fillOptionPane);
	    
	    JPanel colorOptionPane = new JPanel();
	    colorOptionPane.setAlignmentX(0);
		colorOptionPane.setLayout(new BoxLayout(colorOptionPane,BoxLayout.X_AXIS));
		colorOptionPane.add(new JLabel("Color: "));
		ButtonGroup colorOptionGroup = new ButtonGroup();
	    final JRadioButton colorOption0 = new JRadioButton("Black", true);
	    colorOptionGroup.add(colorOption0);
	    colorOptionPane.add(colorOption0);
	    final JRadioButton colorOption1 = new JRadioButton("Blue", false);
	    colorOptionGroup.add(colorOption1);
	    colorOptionPane.add(colorOption1);
	    final JRadioButton colorOption2 = new JRadioButton("Green", false);
	    colorOptionGroup.add(colorOption2);
	    colorOptionPane.add(colorOption2);
	    final JRadioButton colorOption3 = new JRadioButton("Red", false);
	    colorOptionGroup.add(colorOption3);
	    colorOptionPane.add(colorOption3);
	    final JRadioButton colorOption4 = new JRadioButton("Yellow", false);
	    colorOptionGroup.add(colorOption4);
	    colorOptionPane.add(colorOption4);	   
	    circlePanel.add(colorOptionPane);
		
	    JPanel buttonPanel = new JPanel();
	    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
	    buttonPanel.setBorder(new EmptyBorder(20,50,20,50));
	    
	    JButton cancelButton = new JButton("Cancel");
	    cancelButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inputDialog.setVisible(false);
			} 
		} );
	    buttonPanel.add(cancelButton);
	    
	    buttonPanel.add(Box.createHorizontalGlue());
	    
	    JButton okButton = new JButton("OK");
	    okButton.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
				Color color;
				if (colorOption0.isSelected())
					color = Color.BLACK;
				else if (colorOption1.isSelected())
					color = Color.BLUE;
				else if (colorOption2.isSelected())
					color = Color.GREEN;
				else if (colorOption3.isSelected())
					color = Color.RED;
				else if (colorOption4.isSelected())
					color = Color.YELLOW;
				else
					color = null;				
				Shape addShape = new Shape(2, new Integer(p1XField.getText()), new Integer(p1YField.getText()), 
						new Integer(p2XField.getText()), fillOption0.isSelected(), color);
				if(addShape.isComplete()) {
					inputManager.add(addShape);
					shapeListComponent.setListData(inputManager.getListData());
					shapeListScrollPane.revalidate();
					shapeListScrollPane.repaint();
					inputDialog.setVisible(false);
					paint();
				}
			}
		} );
	    buttonPanel.add(okButton);
	    buttonPanel.setAlignmentX(0);
	    
	    if(shape != null){
	    	p1XField.setText(new Integer(shape.p1X).toString());
	    	p1YField.setText(new Integer(shape.p1Y).toString());
	    	p2XField.setText(new Integer(shape.p2X).toString());
	    	fillOption0.setSelected(false);
    		fillOption1.setSelected(false);
	    	if(shape.fill) {
	    		fillOption0.setSelected(true);
	    	}
	    	else{	    		
	    		fillOption1.setSelected(true);
	    	}
	    	
	    	colorOption0.setSelected(false);
	    	colorOption1.setSelected(false);
	    	colorOption2.setSelected(false);
	    	colorOption3.setSelected(false);
	    	colorOption4.setSelected(false);
	    	
	    	if (shape.color == Color.BLACK)
	    		colorOption0.setSelected(true);
			else if (shape.color == Color.BLUE)
				colorOption1.setSelected(true);
			else if (shape.color== Color.GREEN)
				colorOption2.setSelected(true);
			else if (shape.color== Color.RED)
				colorOption3.setSelected(true);
			else if (shape.color == Color.YELLOW)
				colorOption4.setSelected(true);
	    		
	    }
	    
	    circlePanel.add(buttonPanel);
		
	}

	private void createOvalPanel(Shape shape) {
		
		ovalPanel = new JPanel();
		ovalPanel.setLayout(new BoxLayout(ovalPanel, BoxLayout.Y_AXIS));
		ovalPanel.setBorder(new EmptyBorder(20,20,20,20));
		
		JLabel p1XLabel = new JLabel("Center (X):");
		ovalPanel.add(p1XLabel);
		
		final JTextField p1XField = new JTextField();
		p1XField.setMaximumSize(maximumSize);
		p1XField.setName("p1XField");
		ovalPanel.add(p1XField);
		
		JLabel p1YLabel = new JLabel("Center (Y):");
		ovalPanel.add(p1YLabel);
		
		final JTextField p1YField = new JTextField();
		p1YField.setMaximumSize(maximumSize);
		p1YField.setName("p1YField");
		ovalPanel.add(p1YField);
		
		JLabel p2XLabel = new JLabel("Radius (X):");
		ovalPanel.add(p2XLabel);
		
		final JTextField p2XField = new JTextField();
		p2XField.setMaximumSize(maximumSize);
		p2XField.setName("p2XField");
		ovalPanel.add(p2XField);
		
		JLabel p2YLabel = new JLabel("Radius (Y):");
		ovalPanel.add(p2YLabel);
		
		final JTextField p2YField = new JTextField();
		p2YField.setMaximumSize(maximumSize);
		p2YField.setName("p2YField");
		ovalPanel.add(p2YField);
		
		JPanel fillOptionPane = new JPanel();
	    fillOptionPane.setAlignmentX(0);
		fillOptionPane.setLayout(new BoxLayout(fillOptionPane,BoxLayout.X_AXIS));
		fillOptionPane.add(new JLabel("Fill: "));
		ButtonGroup fillOptionGroup = new ButtonGroup();
	    final JRadioButton fillOption0 = new JRadioButton("Yes", true);
	    fillOptionGroup.add(fillOption0);
	    fillOptionPane.add(fillOption0);
	    JRadioButton fillOption1 = new JRadioButton("No", false);
	    fillOptionGroup.add(fillOption1);
	    fillOptionPane.add(fillOption1);
	    ovalPanel.add(fillOptionPane);
	    
	    JPanel colorOptionPane = new JPanel();
	    colorOptionPane.setAlignmentX(0);
		colorOptionPane.setLayout(new BoxLayout(colorOptionPane,BoxLayout.X_AXIS));
		colorOptionPane.add(new JLabel("Color: "));
		ButtonGroup colorOptionGroup = new ButtonGroup();
	    final JRadioButton colorOption0 = new JRadioButton("Black", true);
	    colorOptionGroup.add(colorOption0);
	    colorOptionPane.add(colorOption0);
	    final JRadioButton colorOption1 = new JRadioButton("Blue", false);
	    colorOptionGroup.add(colorOption1);
	    colorOptionPane.add(colorOption1);
	    final JRadioButton colorOption2 = new JRadioButton("Green", false);
	    colorOptionGroup.add(colorOption2);
	    colorOptionPane.add(colorOption2);
	    final JRadioButton colorOption3 = new JRadioButton("Red", false);
	    colorOptionGroup.add(colorOption3);
	    colorOptionPane.add(colorOption3);
	    final JRadioButton colorOption4 = new JRadioButton("Yellow", false);
	    colorOptionGroup.add(colorOption4);
	    colorOptionPane.add(colorOption4);	   
	    ovalPanel.add(colorOptionPane);
		
	    JPanel buttonPanel = new JPanel();
	    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
	    buttonPanel.setBorder(new EmptyBorder(20,50,20,50));
	    
	    JButton cancelButton = new JButton("Cancel");
	    cancelButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inputDialog.setVisible(false);
			} 
		} );
	    buttonPanel.add(cancelButton);
	    
	    buttonPanel.add(Box.createHorizontalGlue());
	    
	    JButton okButton = new JButton("OK");
	    okButton.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
				Color color;
				if (colorOption0.isSelected())
					color = Color.BLACK;
				else if (colorOption1.isSelected())
					color = Color.BLUE;
				else if (colorOption2.isSelected())
					color = Color.GREEN;
				else if (colorOption3.isSelected())
					color = Color.RED;
				else if (colorOption4.isSelected())
					color = Color.YELLOW;
				else
					color = null;				
				Shape addShape = new Shape(3, new Integer(p1XField.getText()), new Integer(p1YField.getText()), 
						new Integer(p2XField.getText()), new Integer(p2YField.getText()), fillOption0.isSelected(), color);
				if(addShape.isComplete()) {
					inputManager.add(addShape);
					shapeListComponent.setListData(inputManager.getListData());
					shapeListScrollPane.revalidate();
					shapeListScrollPane.repaint();
					inputDialog.setVisible(false);
					paint();
				}
			}
		} );
	    buttonPanel.add(okButton);
	    buttonPanel.setAlignmentX(0);
	    
	    if(shape != null){
	    	p1XField.setText(new Integer(shape.p1X).toString());
	    	p1YField.setText(new Integer(shape.p1Y).toString());
	    	p2XField.setText(new Integer(shape.p2X).toString());
	    	p2YField.setText(new Integer(shape.p2Y).toString());
	    	fillOption0.setSelected(false);
    		fillOption1.setSelected(false);
	    	if(shape.fill) {
	    		fillOption0.setSelected(true);
	    	}
	    	else{	    		
	    		fillOption1.setSelected(true);
	    	}
	    	
	    	colorOption0.setSelected(false);
	    	colorOption1.setSelected(false);
	    	colorOption2.setSelected(false);
	    	colorOption3.setSelected(false);
	    	colorOption4.setSelected(false);
	    	
	    	if (shape.color == Color.BLACK)
	    		colorOption0.setSelected(true);
			else if (shape.color == Color.BLUE)
				colorOption1.setSelected(true);
			else if (shape.color== Color.GREEN)
				colorOption2.setSelected(true);
			else if (shape.color== Color.RED)
				colorOption3.setSelected(true);
			else if (shape.color == Color.YELLOW)
				colorOption4.setSelected(true);
	    		
	    }
	    
	    ovalPanel.add(buttonPanel);
	}

	private void createLinePanel(Shape shape) {

		
		linePanel = new JPanel();
		linePanel.setLayout(new BoxLayout(linePanel, BoxLayout.Y_AXIS));
		linePanel.setBorder(new EmptyBorder(20,20,20,20));
		
		JLabel p1XLabel = new JLabel("Point 1 (X):");
		linePanel.add(p1XLabel);
		
		final JTextField p1XField = new JTextField();
		p1XField.setMaximumSize(maximumSize);
		p1XField.setName("p1XField");
		linePanel.add(p1XField);
		
		JLabel p1YLabel = new JLabel("Point 1 (Y):");
		linePanel.add(p1YLabel);
		
		final JTextField p1YField = new JTextField();
		p1YField.setMaximumSize(maximumSize);
		p1YField.setName("p1YField");
		linePanel.add(p1YField);
		
		JLabel p2XLabel = new JLabel("Point 2 (X):");
		linePanel.add(p2XLabel);
		
		final JTextField p2XField = new JTextField();
		p2XField.setMaximumSize(maximumSize);
		p2XField.setName("p2XField");
		linePanel.add(p2XField);
		
		JLabel p2YLabel = new JLabel("Point 2 (Y):");
		linePanel.add(p2YLabel);
		
		final JTextField p2YField = new JTextField();
		p2YField.setMaximumSize(maximumSize);
		p2YField.setName("p2YField");
		linePanel.add(p2YField);
	    
	    JPanel colorOptionPane = new JPanel();
	    colorOptionPane.setAlignmentX(0);
		colorOptionPane.setLayout(new BoxLayout(colorOptionPane,BoxLayout.X_AXIS));
		colorOptionPane.add(new JLabel("Color: "));
		ButtonGroup colorOptionGroup = new ButtonGroup();
	    final JRadioButton colorOption0 = new JRadioButton("Black", true);
	    colorOptionGroup.add(colorOption0);
	    colorOptionPane.add(colorOption0);
	    final JRadioButton colorOption1 = new JRadioButton("Blue", false);
	    colorOptionGroup.add(colorOption1);
	    colorOptionPane.add(colorOption1);
	    final JRadioButton colorOption2 = new JRadioButton("Green", false);
	    colorOptionGroup.add(colorOption2);
	    colorOptionPane.add(colorOption2);
	    final JRadioButton colorOption3 = new JRadioButton("Red", false);
	    colorOptionGroup.add(colorOption3);
	    colorOptionPane.add(colorOption3);
	    final JRadioButton colorOption4 = new JRadioButton("Yellow", false);
	    colorOptionGroup.add(colorOption4);
	    colorOptionPane.add(colorOption4);	   
	    linePanel.add(colorOptionPane);
		
	    JPanel buttonPanel = new JPanel();
	    buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
	    buttonPanel.setBorder(new EmptyBorder(20,50,20,50));
	    
	    JButton cancelButton = new JButton("Cancel");
	    cancelButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inputDialog.setVisible(false);
			} 
		} );
	    buttonPanel.add(cancelButton);
	    
	    buttonPanel.add(Box.createHorizontalGlue());
	    
	    JButton okButton = new JButton("OK");
	    okButton.addActionListener(new ActionListener() {
	    	public void actionPerformed(ActionEvent e) {
				Color color;
				if (colorOption0.isSelected())
					color = Color.BLACK;
				else if (colorOption1.isSelected())
					color = Color.BLUE;
				else if (colorOption2.isSelected())
					color = Color.GREEN;
				else if (colorOption3.isSelected())
					color = Color.RED;
				else if (colorOption4.isSelected())
					color = Color.YELLOW;
				else
					color = null;				
				Shape addShape = new Shape(4, new Integer(p1XField.getText()), new Integer(p1YField.getText()), 
						new Integer(p2XField.getText()), new Integer(p2YField.getText()), false, color);
				if(addShape.isComplete()) {
					inputManager.add(addShape);
					shapeListComponent.setListData(inputManager.getListData());
					shapeListScrollPane.revalidate();
					shapeListScrollPane.repaint();
					inputDialog.setVisible(false);
					paint();
				}
			}
		} );
	    buttonPanel.add(okButton);
	    buttonPanel.setAlignmentX(0);
	    
	    if(shape != null){
	    	p1XField.setText(new Integer(shape.p1X).toString());
	    	p1YField.setText(new Integer(shape.p1Y).toString());
	    	p2XField.setText(new Integer(shape.p2X).toString());
	    	p2YField.setText(new Integer(shape.p2Y).toString());
	    	
	    	colorOption0.setSelected(false);
	    	colorOption1.setSelected(false);
	    	colorOption2.setSelected(false);
	    	colorOption3.setSelected(false);
	    	colorOption4.setSelected(false);
	    	
	    	if (shape.color == Color.BLACK)
	    		colorOption0.setSelected(true);
			else if (shape.color == Color.BLUE)
				colorOption1.setSelected(true);
			else if (shape.color== Color.GREEN)
				colorOption2.setSelected(true);
			else if (shape.color== Color.RED)
				colorOption3.setSelected(true);
			else if (shape.color == Color.YELLOW)
				colorOption4.setSelected(true);
	    		
	    }
	    
	    linePanel.add(buttonPanel);
		
	}
	
	public void paint() {
		Graphics g = canvas.getGraphics();
		ArrayList<Shape> shapelist = inputManager.getShapeList().getShapeList();
		for(int i=0; i<shapelist.size(); i++){
			Shape shape = shapelist.get(i);
			g.setColor(shape.color);
			if (shape.type == 0){
				if (shape.fill) {
					g.fillRect(shape.p1X, shape.p1Y, shape.p2X, shape.p2X);
				}
				else {
					g.drawRect(shape.p1X, shape.p1Y, shape.p2X, shape.p2X);
				}				
			}
			else if (shape.type == 1){
				if (shape.fill) {
					g.fillRect(shape.p1X, shape.p1Y, shape.p2X, shape.p2Y);
				}
				else {
					g.drawRect(shape.p1X, shape.p1Y, shape.p2X, shape.p2Y);
				}				
			}
			else if (shape.type == 2){
				if (shape.fill) {
					g.fillOval(shape.p1X, shape.p1Y, shape.p2X, shape.p2X);
				}
				else {
					g.drawOval(shape.p1X, shape.p1Y, shape.p2X, shape.p2X);
				}				
			}
			else if (shape.type == 3){
				if (shape.fill) {
					g.fillOval(shape.p1X, shape.p1Y, shape.p2X, shape.p2Y);
				}
				else {
					g.drawOval(shape.p1X, shape.p1Y, shape.p2X, shape.p2Y);
				}				
			}
			else if (shape.type == 4){				
				g.drawLine(shape.p1X, shape.p1Y, shape.p2X, shape.p2Y);				
			}
			
		}
		canvas.paintAll(g);
	}
}
