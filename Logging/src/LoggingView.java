import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;

import javax.swing.*;


public class LoggingView extends JFrame{
	
	public String path;
	public Data data;
	public JPanel panel;
	private JMenuItem pathCommand;
	private JTable table;
	final JFileChooser fc = new JFileChooser();

	public LoggingView() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        panel = new JPanel(new GridLayout(0,1)); 
		panel.setOpaque(true);
        
        JMenuBar menuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		pathCommand = new JMenuItem("Change Data Path");
		fileMenu.add(pathCommand);
		menuBar.add(fileMenu);
		this.setJMenuBar(menuBar);
		
		pathCommand.addActionListener(new MainListener());
		
		changePath();
        
        this.setContentPane(panel);
        this.pack();
	}

	public class MainListener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			// TODO Auto-generated method stub
			String command = ev.getActionCommand();
			if (command.equals("Change Data Path")) {
				changePath();
			}
		}
		
	}
	
	public void update() {
		panel.removeAll();
		table = new JTable(data.getData(), data.getColumnNames());
		table.setAutoCreateRowSorter(true);
        table.setPreferredScrollableViewportSize(new Dimension(500, 600));
        table.setFillsViewportHeight(true);
	    JScrollPane scrollPane = new JScrollPane(table);
	    panel.add(scrollPane);
	    this.pack();
	}
	
	public void changePath() {
		
		boolean done = false;
		
		while (!done) {
			try {
				path = JOptionPane.showInputDialog(this, "Enter file path:", null);
				data = new Data(path);
				update();
                done = true;
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
			}
		}
	}
	
}