import java.awt.*;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.*;


public class LoggingMain extends JPanel{
	
	public static String path = "csv.txt";
	public Data data;
	
	public LoggingMain() throws FileNotFoundException {
		super(new GridLayout(1,0));
		data = new Data(path);
        final JTable table = new JTable(data.getData(), data.getColumnNames());
        table.setPreferredScrollableViewportSize(new Dimension(500, 70));
        table.setFillsViewportHeight(true);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);
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
	
	public class Data {
		
		private ArrayList<ArrayList<Object>> dataLines = new ArrayList<ArrayList<Object>>();
		private int numLines = 0;
		private int numColumns = 0;

		public Data(String path) throws FileNotFoundException {
				Scanner dataFile = new Scanner(new FileReader(path));
				
				while(dataFile.hasNextLine()) {
					ArrayList<Object> tempLine = new ArrayList<Object>();
					Scanner temp = new Scanner(dataFile.nextLine());
					temp.useDelimiter(",");
					while (temp.hasNext()) {
						tempLine.add(temp.next());
					}
					dataLines.add(tempLine);
					numLines++;
					temp.close();
				}
				numColumns = dataLines.get(0).size();
				dataFile.close();
		}
		
		public Object[][] getData() {
			Object[][] data = new Object[numLines-1][numColumns];
			for (int i = 1; i < numLines; i++) {
				for (int j = 0; j < numColumns; j++) {
					Object temp = dataLines.get(i).get(j);
					if (temp instanceof String) {
						data[i-1][j] = temp.toString();
					}
					else if (temp instanceof Integer) {
						data[i-1][j] = new Integer((int) temp);
					}
				}
			}
			return data;
		}
		
		public Object[] getColumnNames() {
			Object[] names = new String[numColumns];
			for (int i = 0; i < numColumns; i++) {
				names[i] = dataLines.get(0).get(i).toString();
			}
			return names;
		}
		
		public int getNumRows() {
			return numLines;
		}
		
		public int getNumCols() {
			return numColumns;
		}
		
	}

}
