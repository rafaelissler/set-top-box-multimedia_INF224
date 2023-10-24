package swing;
import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;

public class MainWindow extends JFrame{
	private static final long serialVersionUID = 1L;
	
	JButton btext1 = new JButton("Add Toto");
	JButton btext2 = new JButton("Add Titi");
	JButton bexit = new JButton("Exit");
	JTextArea textArea = new JTextArea(10,10);
	
	public static void main(String[] args) {
		new MainWindow();
	}
	
	public MainWindow() {
		JPanel panelButtons = new JPanel();
		JScrollPane panelTextScroll = new JScrollPane(textArea);
		textArea.setLineWrap(true);
		
		panelButtons.add(btext1);
		panelButtons.add(btext2);
		panelButtons.add(bexit);
		
		add(panelTextScroll, BorderLayout.CENTER);
		add(panelButtons, BorderLayout.SOUTH);
		
		btext1.addActionListener(event -> textArea.append("Toto "));
		btext2.addActionListener(event -> textArea.append("Titi "));
		bexit.addActionListener(event -> System.exit(0));
		
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}
}
