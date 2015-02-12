import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.JOptionPane;

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
			System.out.println(dataLines.toString());
	}
	
	public Object[][] getData() throws Exception {
		Double[][] data = new Double[numLines-1][numColumns];
		for (int i = 1; i < numLines; i++) {
			for (int j = 0; j < numColumns; j++) {
				Object temp = dataLines.get(i).get(j);
					data[i-1][j] = Double.parseDouble((String) temp);
			}
		}
		return data;
	}
	
	public String[] getLegend() throws Exception{
		String[] legend = new String[dataLines.get(0).size()];
		for (int i = 0; i < legend.length; i++) {
			legend[i] = (String) dataLines.get(0).get(i);
		}
		return legend;
	}
	
	public Double[][] getYValues() throws Exception{
		Double[][] yValues = new Double[numColumns][numLines - 1];
		for (int i = 0; i < yValues.length; i++) {
			for (int j = 0; j < yValues[i].length; j++) {
				yValues[i][j] = Double.parseDouble((String) dataLines.get(j+1).get(0));
			}
		}
		return yValues;
	}
	
	public Double[][] getXValues() throws Exception {
		Double[][] xValues = new Double[numColumns - 1][numLines - 1];
		for (int i = 0; i < xValues.length; i++) {
			for (int j = 0; j < xValues[i].length; j++) {
				xValues[i][j] = Double.parseDouble((String) dataLines.get(j+1).get(i+1));
			}
		}
		return xValues;
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