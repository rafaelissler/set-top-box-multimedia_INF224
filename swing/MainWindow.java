import javax.swing.*;
import java.awt.*;

import java.awt.BorderLayout;
import java.awt.event.*;

public class MainWindow extends JFrame{
	private static final long serialVersionUID = 1L;
	
	Client client = null;
	
	JRadioButton getButton = new JRadioButton("Get object");
	JRadioButton getTypeButton = new JRadioButton("Get object of type");
	JRadioButton getNameButton = new JRadioButton("Get object that has");
	JRadioButton getGroupButton = new JRadioButton("Get group");
	JRadioButton playButton = new JRadioButton("Play object");

	JRadioButton createObjectButton = new JRadioButton("Create object");
	JRadioButton createGroupButton = new JRadioButton("Create group");
	JRadioButton addToGroupButton = new JRadioButton("Add to group");
	JRadioButton removeObjectButton = new JRadioButton("Remove object");
	JRadioButton removeGroupButton = new JRadioButton("Remove group");
	
	JButton sendButton = new JButton(new SendAction("Send"));
	JButton exitButton = new JButton("Exit");

	JTextArea textArea = new JTextArea(15,10);
	JTextField textField = new JTextField(39);
	
	int commandPrefix = 0;
	String delimiter = "\\|";
	String[] types = {"photo", "video", "film"};
	
	public static void main(String[] args) {
		new MainWindow(args);	
	}
	
	public MainWindow(String[] args) {
		super("Multimedia Player");
		this.setResizable(false);
		
		// Setup command buttons
		getButton.isSelected();
		
		// Setup button groups
		ButtonGroup buttonGroup = new ButtonGroup();
		buttonGroup.add(getButton);
		buttonGroup.add(getTypeButton);
		buttonGroup.add(getNameButton);
		buttonGroup.add(getGroupButton);
		buttonGroup.add(playButton);
		buttonGroup.add(createObjectButton);
		buttonGroup.add(createGroupButton);
		buttonGroup.add(addToGroupButton);
		buttonGroup.add(removeObjectButton);
		buttonGroup.add(removeGroupButton);
		
		// Setup command options panel
		JPanel panelOptions = new JPanel();
		panelOptions.add(getButton);
		panelOptions.add(getTypeButton);
		panelOptions.add(getNameButton);
		panelOptions.add(getGroupButton);
		panelOptions.add(playButton);
		
		// Setup manipulation (create and remove) options panel
		JPanel panelManipulation = new JPanel();
		panelManipulation.add(createObjectButton);
		panelManipulation.add(createGroupButton);
		panelManipulation.add(addToGroupButton);
		panelManipulation.add(removeObjectButton);
		panelManipulation.add(removeGroupButton);
		
		// Setup send and exit buttons panel
		JPanel panelButtons = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		panelButtons.add(textField);
		panelButtons.add(sendButton);
		panelButtons.add(exitButton);
		
		// Setup super-panel
		JPanel panelSup = new JPanel();
		panelSup.setLayout(new BoxLayout(panelSup, BoxLayout.Y_AXIS));
		panelSup.add(panelOptions);
		panelSup.add(panelManipulation);
		panelSup.add(panelButtons);
		
		// Setup text and its scroll
		JScrollPane panelTextScroll = new JScrollPane(textArea);
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		textArea.setText(startupMsg);
		
		// Add components to main windows
		this.add(panelTextScroll, BorderLayout.CENTER);
		this.add(panelSup, BorderLayout.SOUTH);
		
		// Setup lambdas
		exitButton.addActionListener(event -> System.exit(0));
		
		// Finish
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setVisible(true);
		
		// Setup client
		setupClient(args);
	}
	
	public void setupClient(String[] args) {
		// Setups the client
	    String host = "localhost";
	    int port = 4466;
	    if (args.length >=1) host = args[0];
	    if (args.length >=2) port = Integer.parseInt(args[1]);
	    
	    try {
	      client = new Client(host, port);
	    }
	    catch (Exception e) {
	      System.err.println("Client: Couldn't connect to "+host+":"+port);
	      System.exit(1);
	    }
	    
	    System.out.println("Client connected to "+host+":"+port);
	}
	
	public void parseResponse(String response) {
		// Just makes the objects received by the server more readable to human eyes
		// Don't worry about this
		textArea.setText("");
		String[] fields = response.split(delimiter);
		
		boolean writeName;
		int depth;
		String prefix;
		
		for (int i = 0; i < fields.length; i++) {
			writeName = false;
			depth = 2;
			prefix = "";
			if (fields[i].equals("group")) {
				depth = 0;
				writeName = true;
			}
			else if (fields[i].equals("no groups")) {
				depth = 0;
			}
			for (String name : types) {
				if (fields[i].equals(name)) {
					depth = 1;
					writeName = true;
					break;
				}
			}
			
			for (int j = 0; j < depth; j++) {
				prefix += "    ";
			}
			textArea.append(prefix);
			
			if (writeName) {
				textArea.append(fields[i++]);
				textArea.append(" : ");
			}
			textArea.append(fields[i]);
			textArea.append("\n");
		}
	}
	
	class SendAction extends AbstractAction {
		private static final long serialVersionUID = 1L;
		public SendAction(String text) {
			super(text);
		}
		
		public void actionPerformed(ActionEvent e) {
			System.out.println("ActionPerformed");
			String msg = "";
			if (getButton.isSelected()) {
				msg = "get|";
			} else if (getTypeButton.isSelected()) {
				msg = "get-type|";
			} else if (getNameButton.isSelected()) {
				msg = "get-has|";
			} else if (getGroupButton.isSelected()) {
				msg = "get-group|";
			} else if (playButton.isSelected()) {
				msg = "play|";
			} else if (removeObjectButton.isSelected()) {
				msg = "remove|";
			} else if (removeGroupButton.isSelected()) {
				msg = "remove-group|";
			} else if (createGroupButton.isSelected()) {
				msg = "create-group|";
			} else if (createObjectButton.isSelected()) {
				msg = "create|";
			} else if (addToGroupButton.isSelected()) {
				msg = "link|";
			} else return;
			
			msg += textField.getText();
			textField.setText("");
			String response = client.send(msg);
			parseResponse(response);
		}
	}
	String startupMsg = "# INF224 - Set-Top Box Multimédia\r\n"
			+ "#### Rafael Issler Rodrigues\r\n"
			+ "\r\n"
			+ "### How to use:\r\n"
			+ "Select a function (one of the buttons above the input box), type on the text input box and then click on \"Send\".\r\n"
			+ "\r\n"
			+ "### Commands\r\n"
			+ "- Get object: Prints the multimedia object with the given name on the input box\r\n"
			+ "- Get object of type: Prints the multimedia object with the given type on the input box. Currently, all the objects are of type photo, video or film\r\n"
			+ "- Get object that has: Prints the multimedia objects and groups (alongside with their objects) with a string in their name. The string is given on the input box. Leave the input box empty to get a list of everything.\r\n"
			+ "- Get group: Prints the group with the given name on the input box and all the multimedia objects associated with it\r\n"
			+ "- Play object: Plays the multimedia object with the given name on the input box\r\n"
			+ "- Create object: Creates an object. The input box must be structured following the serialization protocol, using the symbol | as the delimiter\r\n"
			+ "Example 1: photo|family|~/family.png|200|300|\r\n"
			+ "Example 2: video|telecom presentation|C:\\Photos\\telecom(1).mp4|15|\r\n"
			+ "Example 3: film|oppenheimer 2023|oppenheimer.mov|50|4|10 5 20 15|\r\n"
			+ "- Create group: Creates a group with the given game on the input box\r\n"
			+ "- Add to group: Link a multimedia object to a group. The input box must use the delimiter | and follow the pattern: \\<group\\>|\\<object\\>\r\n"
			+ "- Remove object: Removes the multimedia object with the given name on the input box\r\n"
			+ "- Remove group: Removes the group with the given name on the input box\r\n"
			+ "";
}
