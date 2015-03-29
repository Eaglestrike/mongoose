import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;


public class LineChart extends JPanel {
	
	private static final long serialVersionUID = 1L;
	String applicationTitle;
	String chartTitle;
	String xAxis;
	String yAxis;
	XYDataset dataset;
	JFreeChart chart;

	public LineChart(String applicationTitle, String chartTitle, String xAxis, String yAxis, String legend, Double[] xValues, Double[] yValues) {
		dataset = createDataSet(legend, xValues, yValues);
		init();
		
		
	}
	
	public LineChart(String applicationTitle, String chartTitle, String xAxis, String yAxis, String[] legend, Double[][] xValues, Double[][] yValues) {
		dataset = createDataSet(legend, xValues, yValues);
		init();
			
			
	}
	
	private void init() {		
		
		chart = createChart(chartTitle, yAxis, xAxis, dataset);
		final ChartPanel chartPanel = new ChartPanel(chart);
		this.add(chartPanel);
	}
		
	private XYDataset createDataSet(String legend, Double[] xValues, Double[] yValues) {
		
		XYSeries setOne = new XYSeries(legend);
		for (int i = 0; i < xValues.length; i++) {
			setOne.add(xValues[i], yValues[i] );
		}
		
		XYSeriesCollection dataset = new XYSeriesCollection();
		dataset.addSeries(setOne);
		
		return dataset;		
			
	}
	
	private XYDataset createDataSet(String[] legend, Double[][] xValues, Double[][] yValues) {
			
			XYSeriesCollection dataset = new XYSeriesCollection();
			for (int set = 1; set < legend.length; set++) {
				XYSeries series = new XYSeries(legend[set]);
				if (xValues[set - 1] == null)
					continue;
				for (int i = 0; i < xValues[set-1].length; i++) {
					series.add(xValues[set-1][i], yValues[0][i]);
				}
				dataset.addSeries(series);
				
			}			
			
			return dataset;		
				
	}
	
	private JFreeChart createChart(String title, String yAxisLabel, String xAxisLabel, final XYDataset dataset) {
		final JFreeChart chart = ChartFactory.createXYLineChart(
				title, 
				xAxisLabel, 
				yAxisLabel, 
				dataset,
				PlotOrientation.VERTICAL,
		        true,                     // include legend
		        true,                     // tooltips
		        false
		);
		
		chart.setBackgroundPaint(Color.white);
		chart.setBorderPaint(Color.black);
		
		return chart;
		
	}
	
	public void changeDataset(String legend, Double[] xValues, Double[] yValues) {
		this.dataset = createDataSet(legend, xValues, yValues);
		this.chart.getXYPlot().setDataset(dataset);
	}
	
	public void changeDataset(String[] legend, Double[][] xValues, Double[][] yValues) {
		this.dataset = createDataSet(legend, xValues, yValues);
		this.chart.getXYPlot().setDataset(dataset);
	}
	
	
	

}
