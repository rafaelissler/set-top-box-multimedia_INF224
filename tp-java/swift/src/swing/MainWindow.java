package swing;
import javax.swing.*;
import java.awt.*;

import java.awt.BorderLayout;
import java.awt.event.*;


public class MainWindow extends JFrame{
	private static final long serialVersionUID = 1L;
	
	Action totoAction = new TotoAction("Add Toto");
	Action titiAction = new TitiAction("Add Titi");
	
	JButton btext1 = new JButton(totoAction);
	JButton btext2 = new JButton(titiAction);
	JTextArea textArea = new JTextArea(10,10);
	
	JRadioButton getButton = new JRadioButton("Get object");
	JRadioButton getTypeButton = new JRadioButton("Get object of type");
	JRadioButton getNameButton = new JRadioButton("Get object with name with");
	JRadioButton getGroupButton = new JRadioButton("Get group");
	JRadioButton playButton = new JRadioButton("Play object");
	
	JButton sendButton = new JButton("Send");
	JButton exitButton = new JButton("Exit");
	
	public static void main(String[] args) {
		new MainWindow();
	}
	
	public MainWindow() {
		this.setName("Multimedia Player");
		
		// Setup command buttons
		getButton.isSelected();
		
		// Setup button groups
		ButtonGroup buttonGroup = new ButtonGroup();
		buttonGroup.add(getButton);
		buttonGroup.add(getTypeButton);
		buttonGroup.add(getNameButton);
		buttonGroup.add(getGroupButton);
		buttonGroup.add(playButton);
		
		// Setup command options panel
		JPanel panelOptions = new JPanel();
		panelOptions.add(getButton);
		panelOptions.add(getTypeButton);
		panelOptions.add(getNameButton);
		panelOptions.add(getGroupButton);
		panelOptions.add(playButton);
		
		// Setup send and exit buttons panel
		JPanel panelButtons = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		panelButtons.add(sendButton);
		panelButtons.add(exitButton);
		
		// Setup super-panel
		JPanel panelSup = new JPanel();
		panelSup.setLayout(new BoxLayout(panelSup, BoxLayout.Y_AXIS));
		panelSup.add(panelOptions);
		panelSup.add(panelButtons);
		
		
		
		// Setup menu
		JMenu menu = new JMenu("Menu 1");
		menu.add(totoAction);
		menu.add(titiAction);
		
		// Setup menu bar
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(menu);
		this.setJMenuBar(menuBar);
		
		// Setup toolbar
		JToolBar toolbar = new JToolBar("Toolbar");
		toolbar.add(totoAction);
		toolbar.add(titiAction);
		
		// Setup text are and its scroll
		JScrollPane panelTextScroll = new JScrollPane(textArea);
		textArea.setLineWrap(true);
		
		// Add components to main windows
		this.add(panelTextScroll, BorderLayout.CENTER);
		this.add(panelSup, BorderLayout.SOUTH);
		this.add(toolbar, BorderLayout.NORTH);
		
		// Setup lambdas
		exitButton.addActionListener(event -> System.exit(0));
		
		// Finish
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}
	
	class TotoAction extends AbstractAction {
		private static final long serialVersionUID = 1L;
		public TotoAction(String text) {
			super(text);
		}
		public void actionPerformed(ActionEvent e) {
			textArea.append("Toto ");
		}
	}
	
	class TitiAction extends AbstractAction {
		private static final long serialVersionUID = 1L;
		public TitiAction(String text) {
			super(text);
		}
		public void actionPerformed(ActionEvent e) {
			textArea.append("Titi ");
		}
	}
}
