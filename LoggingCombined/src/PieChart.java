import java.awt.Dimension;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;

class PieChart extends JFrame {

	  private static final long serialVersionUID = 1L;
	  JFreeChart chart;
	  PieDataset dataset;
	  boolean isClosed = false;

	  public PieChart(String applicationTitle, String chartTitle, String[] legend, Double[] percentageValue) {
	        super(applicationTitle);
	        // This will create the dataset 
	        dataset = createDataset(legend, percentageValue);
	        // based on the dataset we create the chart
	        chart = createChart(dataset, chartTitle);
	        // we put the chart into a panel
	        this.setLocation(200, 200);
	        this.setSize(new Dimension(1000,500));
	        this.addWindowListener(new WindowAdapter() {
	        	@Override
	        	public void windowClosing(WindowEvent evt) {
	        		isClosed = true;
	        		dispose();
	        	}
	        });
	        init();
	        
	        

	    }
	  
	    private void init() {
	    	ChartPanel chartPanel = new ChartPanel(chart);
	        // default size
	        // add it to our application
	        setContentPane(chartPanel);
	        this.setVisible(true);	        
	        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	    }	    
	    
	/**
	     * Creates a sample dataset 
	     */

	    private  PieDataset createDataset(String[] legend, Double[] percentageValue) {
	        DefaultPieDataset result = new DefaultPieDataset();
	        for (int i = 0; i < legend.length; i++) {
	        	result.setValue(legend[i], percentageValue[i]);
	        }
	        return result;
	        
	    }
	    
	    
	/**
	     * Creates a chart
	     */

	    private JFreeChart createChart(PieDataset dataset, String title) {
	        
	        JFreeChart chart = ChartFactory.createPieChart3D(title,          // chart title
	            dataset,                // data
	            true,                   // include legend
	            true,
	            false);

	        return chart;
	        
	    }
	    
	    public void changeDataset(String[] legend, Double[] percentageValue) {
	    	if (isClosed)
	    		return;
	    	dataset = createDataset(legend, percentageValue);
	    	chart = createChart(dataset, getTitle());
	    	init();
	    }
	} 