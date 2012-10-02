import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.border.EmptyBorder;

class SpokeView extends JFrame {
   
	private static final long serialVersionUID = 1L;
	private SpokeModel spokeModel;   	
	private Dimension maximumSize = new Dimension(600,25);
	private JTextField rightOutput;
	private JTextField leftOutput;
	private JButton calcButton;
	private JButton updateButton;
	private JComboBox spokeComboBox;
	private JTextField erdInput;
	private JTextField osbInput;
	private JTextField wlInput;
	private JTextField wrInput;
	private JTextField dlInput;
	private JTextField drInput;
	private JTextField cInput;
	private SpokeCanvas spokeCanvas;
	private JList rimList;
	private JList hubList;
	private JComboBox faqComboBox;
	private JTextArea answerArea;
	
	
	private String[] faqQuestions = { 
			"What is a spoke?", 
			"What is the ERD?", 
			"What is the OSB?",
			"What is the W(L)?",
			"What is the W(R)?",
			"What is the D(R)?",
			"What is the D(L)?",
			"What is the C?"};
	private String[] faqAnswers = {
			"A spoke is one of the wires connecting the rim to the hub of a bicycle wheel.",
			"The ERD (Effective Rim Diameter) is the diameter on which you want the ends of the spokes to lie. Most people prefer it near the end of the spoke nipple. Of all the dimensions you actually might measure, ERD is the most critical dimension affecting spoke length, so it makes sense to measure it a few times at different places around the rim. Always count to make sure you use spoke holes that are actually opposite each other.",
			"The OSB is the lateral spoke bed offset (from wheel center). Non-zero for asymmetric rims, zero for symmetrical rims",
			"The W is the width from center to flange and may differ between left and right sides of the hub. WL is for the left side of the hub.",
			"The W is the width from center to flange and may differ between left and right sides of the hub. WR is for the right side of the hub.",
			"The D(R) is the right flange diameter. It is measured between centers of opposite holes in the hub flange. It is usually between 38 and 67 millimeters. Note that it is NOT the outside diameter of the hub's flange. Left and right flange diameters are often, but not always, the same.",
			"The D(L) is the left flange diameter. It is measured between centers of opposite holes in the hub flange. It is usually between 38 and 67 millimeters. Note that it is NOT the outside diameter of the hub's flange. Left and right flange diameters are often, but not always, the same.",		
			"The C is the number of crosses each spoke makes of other spokes on it's side of the hub."
	};	
    
    SpokeView(SpokeModel model) {

        spokeModel = model;
        
        // Calculator Panel
        
        JPanel inputPanel = new JPanel();
		inputPanel.setLayout(new BoxLayout(inputPanel, BoxLayout.Y_AXIS));
		inputPanel.setMaximumSize(new Dimension(200, 300));
		inputPanel.setBorder(new EmptyBorder(20,20,20,20));
				
		JPanel spokeComboPanel = new JPanel();
		JLabel spokeComboLabel = new JLabel(" spokes");
		spokeComboBox = new JComboBox(model.getSpokeCombos());
		spokeComboBox.setSelectedIndex(0);
		spokeComboPanel.setLayout(new BoxLayout(spokeComboPanel, BoxLayout.X_AXIS));
		spokeComboPanel.setMaximumSize(maximumSize);
		spokeComboPanel.add(spokeComboBox);
		spokeComboPanel.add(spokeComboLabel);
		inputPanel.add(spokeComboPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel erdPanel = new JPanel();
		JLabel erdLabel = new JLabel("ERD: ");
		erdInput = new JTextField("0.0");
		erdInput.setHorizontalAlignment(SwingConstants.TRAILING);
		erdPanel.setLayout(new BoxLayout(erdPanel, BoxLayout.X_AXIS));
		erdPanel.setMaximumSize(maximumSize);
		erdPanel.add(erdLabel);
		erdPanel.add(erdInput);
		erdPanel.add(new JLabel(" mm"));
		inputPanel.add(erdPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel osbPanel = new JPanel();
		JLabel osbLabel = new JLabel("OSB: ");
		osbInput = new JTextField("0.0");
		osbInput.setHorizontalAlignment(SwingConstants.TRAILING);
		osbPanel.setLayout(new BoxLayout(osbPanel, BoxLayout.X_AXIS));
		osbPanel.setMaximumSize(maximumSize);
		osbPanel.add(osbLabel);
		osbPanel.add(osbInput);
		osbPanel.add(new JLabel(" mm"));
		inputPanel.add(osbPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel wlPanel = new JPanel();
		JLabel wlLabel = new JLabel("W(L): ");
		wlInput = new JTextField("0.0");
		wlInput.setHorizontalAlignment(SwingConstants.TRAILING);
		wlPanel.setLayout(new BoxLayout(wlPanel, BoxLayout.X_AXIS));
		wlPanel.setMaximumSize(maximumSize);
		wlPanel.add(wlLabel);
		wlPanel.add(wlInput);
		wlPanel.add(new JLabel(" mm"));
		inputPanel.add(wlPanel);
				
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel wrPanel = new JPanel();
		JLabel wrLabel = new JLabel("W(R): ");
		wrInput = new JTextField("0.0");
		wrInput.setHorizontalAlignment(SwingConstants.TRAILING);
		wrPanel.setLayout(new BoxLayout(wrPanel, BoxLayout.X_AXIS));
		wrPanel.setMaximumSize(maximumSize);
		wrPanel.add(wrLabel);
		wrPanel.add(wrInput);
		wrPanel.add(new JLabel(" mm"));
		inputPanel.add(wrPanel);
				
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel dlPanel = new JPanel();
		JLabel dlLabel = new JLabel("D(L): ");
		dlInput = new JTextField("0.0");
		dlInput.setHorizontalAlignment(SwingConstants.TRAILING);
		dlPanel.setLayout(new BoxLayout(dlPanel, BoxLayout.X_AXIS));
		dlPanel.setMaximumSize(maximumSize);
		dlPanel.add(dlLabel);
		dlPanel.add(dlInput);
		dlPanel.add(new JLabel(" mm"));
		inputPanel.add(dlPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel drPanel = new JPanel();
		JLabel drLabel = new JLabel("D(R): ");
		drInput = new JTextField("0.0");
		drInput.setHorizontalAlignment(SwingConstants.TRAILING);
		drPanel.setLayout(new BoxLayout(drPanel, BoxLayout.X_AXIS));
		drPanel.setMaximumSize(maximumSize);
		drPanel.add(drLabel);
		drPanel.add(drInput);
		drPanel.add(new JLabel(" mm"));
		inputPanel.add(drPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		JPanel cPanel = new JPanel();
		JLabel cLabel = new JLabel("C: ");
		cInput = new JTextField("3.0");
		cInput.setHorizontalAlignment(SwingConstants.TRAILING);
		cPanel.setLayout(new BoxLayout(cPanel, BoxLayout.X_AXIS));
		cPanel.setMaximumSize(maximumSize);
		cPanel.add(cLabel);
		cPanel.add(cInput);
		cPanel.add(new JLabel(" crosses"));
		inputPanel.add(cPanel);
		
		inputPanel.add(Box.createVerticalStrut(10));
		
		calcButton = new JButton("Calculate");
		inputPanel.add(calcButton);
		
		spokeCanvas = new SpokeCanvas();
		spokeCanvas.setBackground(Color.white);
		
		JPanel modelPanel = new JPanel();
		modelPanel.setLayout(new BoxLayout(modelPanel, BoxLayout.X_AXIS));
		modelPanel.setBorder(BorderFactory.createTitledBorder("Model:"));
		modelPanel.setMinimumSize(new Dimension(100, 100));
		modelPanel.add(spokeCanvas);

		
		JLabel leftLabel = new JLabel("Left: ");
		leftOutput = new JTextField("0.0");
		leftOutput.setHorizontalAlignment(SwingConstants.TRAILING);
		
		JLabel rightLabel = new JLabel("Left: ");
		rightOutput = new JTextField("0.0");
		rightOutput.setHorizontalAlignment(SwingConstants.TRAILING);
		
		JPanel sizePanel = new JPanel();
		sizePanel.setBorder(BorderFactory.createTitledBorder("Spoke Sizes:"));
		sizePanel.setMaximumSize(new Dimension(300, 50));
		sizePanel.setLayout(new BoxLayout(sizePanel, BoxLayout.X_AXIS));
		sizePanel.add(leftLabel);
		sizePanel.add(leftOutput);
		sizePanel.add(Box.createHorizontalStrut(10));
		sizePanel.add(rightLabel);
		sizePanel.add(rightOutput);
				
		JPanel outputPanel = new JPanel();
		outputPanel.setLayout(new BoxLayout(outputPanel, BoxLayout.Y_AXIS));
		outputPanel.setBorder(new EmptyBorder(20,20,20,20));
		outputPanel.add(modelPanel);
		outputPanel.add(sizePanel);
		outputPanel.setMaximumSize(new Dimension(400, 300));
		
		JPanel calculatorPanel = new JPanel();
		calculatorPanel.setLayout(new BoxLayout(calculatorPanel, BoxLayout.X_AXIS));
		calculatorPanel.add(inputPanel);
		calculatorPanel.add(outputPanel);
		
		// Components Panel
		
		rimList = new JList(model.getRimList().getJListData());
		JScrollPane rimScrollPane = new JScrollPane(rimList);
		rimScrollPane.setPreferredSize(new Dimension(260, 280));
		JPanel rimPanel = new JPanel();
		rimPanel.setBorder(BorderFactory.createTitledBorder("Select a Rim"));
		rimPanel.add(rimScrollPane);
		
		hubList = new JList(model.getHubList().getJListData());
		JScrollPane hubScrollPane = new JScrollPane(hubList);
		hubScrollPane.setPreferredSize(new Dimension(260, 280));
		JPanel hubPanel = new JPanel();
		hubPanel.setBorder(BorderFactory.createTitledBorder("Select a Hub"));
		hubPanel.add(hubScrollPane);
		
		JPanel listPanel = new JPanel();
		listPanel.setLayout(new BoxLayout(listPanel, BoxLayout.X_AXIS));
		listPanel.add(rimPanel);
		listPanel.add(hubPanel);
		
		JPanel updatePanel = new JPanel();
		updatePanel.setMaximumSize(new Dimension(100, 100));
		updateButton = new JButton("Update");
		updatePanel.add(updateButton);
		
		JPanel componentsPanel = new JPanel();
		componentsPanel.setLayout(new BoxLayout(componentsPanel, BoxLayout.Y_AXIS));
		componentsPanel.add(listPanel);
		componentsPanel.add(updatePanel);		
		
		faqComboBox = new JComboBox(faqQuestions);
		faqComboBox.setPreferredSize(new Dimension(550, 30));
		JPanel questionPanel = new JPanel();
		questionPanel.setBorder(BorderFactory.createTitledBorder("Question?"));
		questionPanel.add(faqComboBox);
		questionPanel.setMaximumSize(new Dimension(600, 100));
		
		JPanel answerPanel = new JPanel();
		answerPanel.setBorder(BorderFactory.createTitledBorder("Answer!"));
		answerArea = new JTextArea();
		answerArea.setLineWrap(true);
		answerArea.setColumns(50);
		answerArea.setText(faqAnswers[faqComboBox.getSelectedIndex()]);
		answerPanel.add(answerArea);
		
		JPanel helpPanel = new JPanel();
		helpPanel.setLayout(new BoxLayout(helpPanel, BoxLayout.Y_AXIS));
		helpPanel.add(questionPanel);
		helpPanel.add(answerPanel);
				
		JTabbedPane tabbedPane = new JTabbedPane();
		tabbedPane.addTab( "Calculator", calculatorPanel);
		tabbedPane.addTab( "Components", componentsPanel);
		tabbedPane.addTab( "Help", helpPanel);
		
		this.setTitle("The Spokeulator");
		this.setSize( 600, 400 );			
		this.setVisible(true);
		this.getContentPane().add(tabbedPane);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    void addCalculatorListener(ActionListener calcAL) {
    	calcButton.addActionListener(calcAL);
    }

	void addUpdateListener(ActionListener updateListener) {
		updateButton.addActionListener(updateListener);
	}

	void addQuestionListener(ActionListener questionListener) {
		faqComboBox.addActionListener(questionListener);		
	}

	public void updateModel() {
		
		spokeModel.update(Integer.parseInt(spokeModel.getSpokeCombos()[spokeComboBox.getSelectedIndex()]),
				Double.parseDouble(erdInput.getText()),
				Double.parseDouble(osbInput.getText()),
				Double.parseDouble(wlInput.getText()),
				Double.parseDouble(wrInput.getText()),
				Double.parseDouble(dlInput.getText()),
				Double.parseDouble(drInput.getText()),
				Double.parseDouble(cInput.getText()));
	}
	
	public void updateView() {
		
		erdInput.setText(Double.toString(spokeModel.getErdInput()));
		osbInput.setText(Double.toString(spokeModel.getOsbInput()));
		wlInput.setText(Double.toString(spokeModel.getWlInput()));
		wrInput.setText(Double.toString(spokeModel.getWrInput()));
		dlInput.setText(Double.toString(spokeModel.getDlInput()));
		drInput.setText(Double.toString(spokeModel.getDrInput()));
	}

	public void updateOutput() {
		this.leftOutput.setText(Double.toString(spokeModel.getLeftOutput()));
		this.rightOutput.setText(Double.toString(spokeModel.getRightOutput()));		
	}

	public void redraw() {
		spokeCanvas.setModel(spokeModel);
		spokeCanvas.repaint();
	}

	public int getRimIndex() {
		return rimList.getSelectedIndex();
	}
	
	public int getHubIndex() {
		return hubList.getSelectedIndex();
	}

	public void updateQuestion() {
		answerArea.setText(faqAnswers[faqComboBox.getSelectedIndex()]);
	}
}
