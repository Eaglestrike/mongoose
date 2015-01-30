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
	Listener listener; 
	JButton graphButton; 
	final String GRAPH = "graph";
	JCheckBox[] checkBoxes;
	
	public LoggingFrame() throws FileNotFoundException {
		this.setLayout(new BorderLayout());
		
		loggingPanel = new LoggingMain();
		this.add(loggingPanel, BorderLayout.CENTER);
		
		listener = new Listener();
		
		JPanel controlPanel = new JPanel(new GridLayout(1,0));
		this.add(controlPanel, BorderLayout.NORTH);		
		controlPanel.setLayout(new GridLayout(0,1));
		
		graphButton = new JButton(GRAPH);
		controlPanel.add(graphButton);
		graphButton.doClick();
		graphButton.setSize(200, 100);
		graphButton.addActionListener(listener);
		
		checkBoxes = new JCheckBox[loggingPanel.data.getLegend().length];
		for (int i = 1; i < loggingPanel.data.getLegend().length; i++) {
			checkBoxes[i] = new JCheckBox("Enable dataset " + loggingPanel.data.getLegend()[i]);
			checkBoxes[i].setActionCommand("" + i);
			checkBoxes[i].setSize(200, 100);
			checkBoxes[i].setSelected(true);;
			checkBoxes[i].addActionListener(listener);
			checkBoxes[i].setEnabled(true);
			controlPanel.add(checkBoxes[i]);
		}
		
		this.setVisible(true);
		
	}
	
	private class Listener implements ActionListener {
		
		ArrayList<Integer> include;
		int includeSize;
		
		public Listener() {
			super();
			include = new ArrayList<Integer>();
			for (int i = 1; i < loggingPanel.data.getLegend().length; i++) {
				include.add(i);
				includeSize++;
			}
		}

		@Override
		public void actionPerformed(ActionEvent ev) {
			if (ev.getActionCommand().equals(GRAPH)) {
				loggingPanel.graphData(include);
			}
			else {
				for (int i = 1; i < includeSize; i++) {
					if (ev.getActionCommand().contains("" + i)) {
						if (((JCheckBox) ev.getSource()).isSelected() == false) {
							include.remove((Integer) i);
							System.out.println("Removed");
						}
						else {
							include.add((Integer) i);
							System.out.println("Added");
						}
						break;
					}					
				}
			}
			
				
		}
		
	}

	private class LoggingMain extends JPanel{
		
		public static final String path = "csv.txt";
		public Data data;
		LineChart chart;
		
		public LoggingMain() throws FileNotFoundException {
			super(new BorderLayout());
			data = new Data(path);
	        final JTable table = new JTable(data.getData(), data.getColumnNames());
	        table.setPreferredScrollableViewportSize(new Dimension(500, 70));
	        table.setFillsViewportHeight(true); 
	        JScrollPane scrollPane = new JScrollPane(table);
	        add(scrollPane, BorderLayout.NORTH);
	        chart = new LineChart("Sample text", "Sample text", "xAxis", "yAxis", data.getLegend(), data.getXValues(), data.getYValues());	        
	               
	        add(chart, BorderLayout.CENTER);
		}
		
		public void graphData(ArrayList<Integer> include) {
			String[] legend = data.getLegend();
			String[] filteredLegend = new String[include.size() + 1];
			filteredLegend[0] = legend[0];
			for (int i = 1, j = 1; i < legend.length; i++) {				
				if (include.contains(i)) {
					filteredLegend[j] = legend[i];
					j++;
				}
			}
			
			Double[][] xValues = data.getXValues();
			Double[][] filteredXValues = new Double[include.size()][];
			for (int dataset = 1, g = 0, j = 0; g < xValues.length; dataset++, g++) {
				if (include.contains(dataset)) {
					filteredXValues[j] = xValues[g];
					j++;
				}
			}
			
			Double[][] yValues = data.getYValues();
			Double[][] filteredYValues = new Double[include.size()][];
			for (int i = 0; i < include.size(); i++) {
				filteredYValues[i] = yValues[i]; //All y values are the same for any x data set
			}	
			
			
			chart.changeDataset(filteredLegend, filteredXValues, filteredYValues);			
		}
		
	}
}