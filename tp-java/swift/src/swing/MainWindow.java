package swing;
import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;

public class MainWindow extends JFrame{
	private static final long serialVersionUID = 1L;
	
	Action totoAction = new TotoAction("Add Toto");
	Action titiAction = new TitiAction("Add Titi");
	
	JButton btext1 = new JButton(totoAction);
	JButton btext2 = new JButton(titiAction);
	JButton bexit = new JButton("Exit");
	JTextArea textArea = new JTextArea(10,10);
	
	public static void main(String[] args) {
		new MainWindow();
	}
	
	public MainWindow() {
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
		
		// Setup button panel
		JPanel panelButtons = new JPanel();
		
		// Setup text are and its scroll
		JScrollPane panelTextScroll = new JScrollPane(textArea);
		textArea.setLineWrap(true);
		
		// Add components to button panel
		panelButtons.add(btext1);
		panelButtons.add(btext2);
		panelButtons.add(bexit);
		
		// Add components to main windows
		this.add(panelTextScroll, BorderLayout.CENTER);
		this.add(panelButtons, BorderLayout.SOUTH);
		this.add(toolbar, BorderLayout.NORTH);
		
		// Setup lambdas
		bexit.addActionListener(event -> System.exit(0));
		
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
