package chess;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.io.IOException;
import java.util.regex.*;
import javax.swing.*;
import javax.swing.text.html.HTMLEditorKit;

public class ConnectionSetup implements ActionListener, KeyListener
{
	private JFrame mainFrame;
	private JPanel contentPane, fieldPane, submitPane, directoryPane;
	private JLabel ipLabel, portLabel, currentDirectoryLabel;
	private JEditorPane editorPane;
	private ButtonGroup connectionChoice;
	private JRadioButton listenButton, connectButton;
	private JTextField ipField, portField, directoryField;
	private JButton submit, browse;
	private JScrollPane adapterPane;
	private boolean connect = true;
	private String netInfo, chooserTitle;
	private final Game gameInstance;
	private JFileChooser chooser;

	public ConnectionSetup(Game gameInstance, String netInfo)
	{
		this.gameInstance = gameInstance;

		this.netInfo = netInfo;

		mainFrame = new JFrame("Choose a connection");

		contentPane = new JPanel();
		fieldPane = new JPanel(new GridLayout(2, 2));
		submitPane = new JPanel();

		ipLabel = new JLabel("IP Address:");
		portLabel = new JLabel("Port Number:");

		editorPane = new JEditorPane();

		connectionChoice = new ButtonGroup();

		listenButton = new JRadioButton("Wait for an opponent");
		connectButton = new JRadioButton("Connect to an opponent");

		ipField = new JTextField();
		portField = new JTextField();
		directoryField = new JTextField();

		submit = new JButton("Go!");
		browse = new JButton("Browse");

		currentDirectoryLabel = new JLabel();

		adapterPane = new JScrollPane(editorPane);
		directoryPane = new JPanel();

		setupComponents();
	}

	public void setupComponents()
	{
		// add radio buttons to a group
		connectionChoice.add(connectButton);
		connectionChoice.add(listenButton);

		// configure buttons and add actionlistener
		connectButton.setSelected(true);
		connectButton.addActionListener(this);
		connectButton.setAlignmentX(Component.LEFT_ALIGNMENT);
		listenButton.addActionListener(this);
		listenButton.setAlignmentX(Component.LEFT_ALIGNMENT);
		submit.addActionListener(this);
		submit.setAlignmentX(Component.CENTER_ALIGNMENT);

		// pane with "Go!" button
		submitPane.setAlignmentX(Component.LEFT_ALIGNMENT);
		submitPane.add(submit);

		// configure scrollpane
		adapterPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		adapterPane.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10), BorderFactory.createTitledBorder("Adapter Info")));
		adapterPane.setPreferredSize(new Dimension(400, 200));
		adapterPane.setAlignmentX(Component.LEFT_ALIGNMENT);

		// text area
		editorPane.setEditable(false);
		editorPane.setEditorKit(new HTMLEditorKit());
		editorPane.setText(netInfo);

		// set field size
		ipField.setColumns(15);
		ipField.addKeyListener(this);
		portField.setColumns(15);
		portField.addKeyListener(this);

		// Icon Directory Chooser
		chooser = new JFileChooser();
		try
		{
			chooser.setCurrentDirectory(new File("./default_icons/").getCanonicalFile());
		}
		catch (IOException e)
		{
			System.out.println("[Error] Default Icon Directory Not Found.");
			e.printStackTrace();
		}
		chooserTitle = "Icon Directory";
		currentDirectoryLabel.setText("Current Icon Directory: ");
		directoryField.setText(chooser.getCurrentDirectory().toString());
		directoryField.setEditable(false);
		directoryPane.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(0, 10, 10, 10), BorderFactory.createTitledBorder(chooserTitle)));
		directoryPane.setAlignmentX(Component.LEFT_ALIGNMENT);

		browse.addActionListener(this);
		browse.setAlignmentX(Component.RIGHT_ALIGNMENT);

		// directoryPane.add(currentDirectoryLabel);
		directoryPane.add(directoryField);
		directoryPane.add(browse);

		// TODO Delete this
		ipField.setText("127.0.0.1");
		portField.setText("12345");

		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
		contentPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		contentPane.add(connectButton);
		contentPane.add(listenButton);

		fieldPane.add(ipLabel);
		fieldPane.add(ipField);
		fieldPane.add(portLabel);
		fieldPane.add(portField);
		fieldPane.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 10));
		fieldPane.setAlignmentX(Component.LEFT_ALIGNMENT);

		contentPane.add(fieldPane);
		contentPane.add(adapterPane);
		contentPane.add(directoryPane);
		contentPane.add(submitPane);

		mainFrame.setContentPane(contentPane);
		mainFrame.setResizable(true);
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.pack();
		mainFrame.setLocation(200, 200);
		mainFrame.setVisible(true);
	}

	// make sure it has a chance of being a valid IP address
	public boolean validateIP(String ip)
	{
		Pattern p = Pattern.compile("([0-9]{1,3}.){3}[0-9]{1,3}+");
		Matcher m = p.matcher(ip);

		if (m.matches())
			return true;
		else
			return false;
	}

	// make sure its a valid port num
	public boolean validatePort(String port)
	{
		Pattern p = Pattern.compile("[0-9]{3,5}");
		Matcher m = p.matcher(port);

		if (m.matches())
		{
			// ports must be at least 256 and no greater than 65535
			if (Integer.parseInt(port) < 256 || Integer.parseInt(port) > 65535)
				return false;
			else
				return true;
		}
		else
			return false;
	}

	public void throwErrorWindow(String message)
	{
		JOptionPane.showMessageDialog(null, message, "Error!", JOptionPane.ERROR_MESSAGE);
	}

	public void attemptConnection()
	{
		// if connecting to another computer
		if (connect)
		{
			// if the port and ip are valid
			if (validateIP(ipField.getText()) && validatePort(portField.getText()))
			{
				try
				{
					gameInstance.connect(ipField.getText(), Integer.parseInt(portField.getText()));
					mainFrame.setVisible(false);
					gameInstance.setNext(false);
					gameInstance.setColor(Piece.PieceColor.Black);
					new Thread(new Runnable()
					{
						public void run()
						{
							gameInstance.start();
						}
					}).start();
				} catch (java.io.IOException ex)
				{
					throwErrorWindow("Unable to connect.  Connection refused.");
				}
			}
			else
				throwErrorWindow("Invalid IP and/or Port Number!");
		}
		// otherwise youre just listening on a port
		else
		{
			if (validatePort(portField.getText()))
			{
				try
				{
					gameInstance.listen(Integer.parseInt(portField.getText()));
					mainFrame.setVisible(false);
					gameInstance.setNext(true);
					gameInstance.setColor(Piece.PieceColor.White);
					new Thread(new Runnable()
					{
						public void run()
						{
							gameInstance.start();
						}
					}).start();
				} catch (java.io.IOException ex)
				{
					throwErrorWindow("Could not bind to port.");
				}
			}
			else
				throwErrorWindow("Invalid IP and/or Port Number!");
		}
	}

	public void actionPerformed(ActionEvent e)
	{
		if (e.getSource() == connectButton)
		{
			connect = true;
			ipField.setEnabled(true);
		}
		else if (e.getSource() == listenButton)
		{
			connect = false;
			ipField.setEnabled(false);
		}
		else if (e.getSource() == submit)
		{
			attemptConnection();
		}
		else if (e.getSource() == browse)
		{
			chooseDirectory();
		}
	}

	private void chooseDirectory()
	{
		chooser.setDialogTitle(chooserTitle);
		chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		chooser.setAcceptAllFileFilterUsed(false);

		if (chooser.showOpenDialog(directoryPane) == JFileChooser.APPROVE_OPTION)
		{
			directoryField.setText(chooser.getSelectedFile().toString());
		}
	}

	public void keyPressed(KeyEvent ke)
	{
	}

	public void keyReleased(KeyEvent arg0)
	{
	}

	public void keyTyped(KeyEvent ke)
	{
		if (ke.getSource() == ipField || ke.getSource() == portField)
		{
			if (ke.getKeyChar() == KeyEvent.VK_ENTER)
				attemptConnection();
		}

	}

	public String getIconPath()
	{
		try
		{
			String path = chooser.getSelectedFile().getCanonicalFile().toString() + '/';
			if (new File(path + "KingWhite.png").exists())
				return path;
		}
		catch (IOException e)
		{
			throwErrorWindow("Directory not found.");
		}
		catch (NullPointerException e)
		{
			if(chooser.getSelectedFile() != null){
				throwErrorWindow("Directory does not contain chess images. Using default images.");
			}
		}
		return "./default_icons/";
	}
}
