import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.*;

public class LoggingFrame extends JFrame {
	
	LoggingMain loggingPanel;
	Listener listener = new Listener();
	JButton graphButton; 
	final String GRAPH = "graph";
	JCheckBox[] checkBoxes;
	
	public LoggingFrame() throws FileNotFoundException {
		this.setLayout(new BorderLayout());
		
		loggingPanel = new LoggingMain();
		this.add(loggingPanel, BorderLayout.CENTER);
		
		JPanel controlPanel = new JPanel();
		this.add(controlPanel, BorderLayout.WEST);		
		controlPanel.setLayout(new GridLayout(0,1));
		
		graphButton = new JButton(GRAPH);
		controlPanel.add(graphButton);
		graphButton.addActionListener(listener);
		
		for (int i = 0; i < loggingPanel.data.getLegend().length; i++) {
			checkBoxes[i] = new JCheckBox("Enable dataset #" + i);
		}
		
		
	}
	
	private class Listener implements ActionListener {
		
		ArrayList<Integer> include = new ArrayList<Integer>();
		
		public Listener() {
			super();
			for (int i = 0; i < loggingPanel.data.getLegend().length; i++) {
				include.add(i);
			}
		}

		@Override
		public void actionPerformed(ActionEvent ev) {
			if (ev.getActionCommand().equals(GRAPH)) {
				loggingPanel.graphData(include);
			}
			else {
				String
			}
			
				
		}
		
	}

	private class LoggingMain extends JPanel{
		
		public static final String path = "csv.txt";
		public Data data;
		LineChart chart;
		
		public LoggingMain() throws FileNotFoundException {
			super(new GridLayout(1,0));
			data = new Data(path);
	        final JTable table = new JTable(data.getData(), data.getColumnNames());
	        table.setPreferredScrollableViewportSize(new Dimension(500, 70));
	        table.setFillsViewportHeight(true); 
	        JScrollPane scrollPane = new JScrollPane(table);
	        add(scrollPane);
	        chart = new LineChart("Sample text", "Sample text", "xAxis", "yAxis", data.getLegend(), data.getXValues(), data.getYValues());	        
		}
		
		public void graphData(ArrayList<Integer> include) {
			String[] legend = data.getLegend();
			String[] filteredLegend = new String[include.size()];
			for (int i = 0; i < legend.length; i++) {
				if (include.contains(i)) {
					filteredLegend[i] = legend[i];
				}
			}
			
			Double[][] xValues = data.getXValues();
			Double[][] filteredXValues = new Double[include.size()][];
			for (int i = 0; i < xValues.length; i++) {
				if (include.contains(i)) {
					filteredXValues[i] = xValues[i];
				}
			}
			
			Double[][] yValues = data.getYValues();
			Double[][] filteredYValues = new Double[include.size()][];
			for (int i = 0; i < include.size(); i++) {
				filteredYValues[i] = yValues[0]; //All y values are the same for any x data set
			}	
			
			
			chart.changeDataset(filteredLegend, filteredXValues, filteredYValues);			
		}
		
	}
}