import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;


public class BarChart extends JFrame {
	
	private static final long serialVersionUID = 1L;
	boolean isClosed = false;
	
	JFreeChart chart;
	CategoryDataset dataset;
	String chartTitle;
	String xAxis;
	String yAxis;

	public BarChart(String applicationTitle, String chartTitle, String xAxis, String yAxis, String[] legend, String[] categories, Double[][] values) {	
      this.chartTitle = chartTitle;
      this.xAxis = xAxis;
      this.yAxis = yAxis;
	  dataset = createDataset(legend, categories, values);
	  chart = createBarChart(this.chartTitle, this.xAxis, this.yAxis, legend, categories, values);
	  this.addWindowListener(new WindowAdapter() {
		  @Override
		  public void windowClosing(WindowEvent evt) {
			  isClosed = true;
			  dispose();
		  }
	  });
	         
	  this.setSize(1000, 500); 
	  init();
	}
	
	private void init() {
		ChartPanel chartPanel = new ChartPanel( chart );  
		chartPanel.setVisible(true);
	    setContentPane( chartPanel ); 
	    this.setVisible(true);
	    
	}
	
	private JFreeChart createBarChart(String chartTitle, String xAxis, String yAxis, String[] legend, String[] categories, Double[][] values) {
		return ChartFactory.createBarChart(
		         chartTitle,           
		         xAxis,            
		         yAxis,            
		         dataset,          
		         PlotOrientation.VERTICAL,           
		         true, 
		         true, 
		         false);
	}

	private CategoryDataset createDataset(String[] legends, String[] categories, Double[][] values) {
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
		for (int legendIndex = 0; legendIndex < legends.length; legendIndex++) {
			for (int categoryIndex = 0; categoryIndex < categories.length; categoryIndex++) {
				dataset.addValue(values[legendIndex][categoryIndex], legends[legendIndex], categories[categoryIndex]);
			}
		}
		
		return dataset;
	}
	
	public void changeDataset(String[] legends, String[] categories, Double[][] values) {
		if (isClosed == false) {
			dataset = createDataset(legends, categories, values);
			chart = createBarChart(chartTitle, xAxis, yAxis, legends, categories, values);
			init();
		}
	}

}
