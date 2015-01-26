import java.awt.*;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.*;


public class LoggingMain extends JPanel{
	
	public static final String path = "csv.txt";
	public Data data;
	
	public LoggingMain() throws FileNotFoundException {
		super(new GridLayout(1,0));
		data = new Data(path);
        final JTable table = new JTable(data.getData(), data.getColumnNames());
        table.setPreferredScrollableViewportSize(new Dimension(500, 70));
        table.setFillsViewportHeight(true); 
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);
        graphData();
	}

	public static void main(String[] args){
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	JFrame frame = new JFrame("SimpleTableDemo");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                LoggingMain newContentPane; 
				try {
					newContentPane = new LoggingMain();
					newContentPane.setOpaque(true);
	                frame.setContentPane(newContentPane);
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				}
                frame.pack();
                frame.setVisible(true);
            }            
        });
        }
	
	public void graphData() {
        new LineChart("Sample text", "Sample text", "xAxis", "yAxis", data.getLegend(), data.getXValues(), data.getYValues());
	}
	
}