

public class GraphLoggingWindow {

	public static PieChart pieChart(String applicationTitle, String graphTitle, String[] legend, Double[] percetangeValues) {
		return new PieChart(applicationTitle, graphTitle, legend, percetangeValues);		
    }
	
	public static LineChart lineChart(String applicationTitle, String chartTitle, String xAxis, String yAxis, String legend, Double[] xValues, Double[] yValues) {	
		return new LineChart(applicationTitle, chartTitle, xAxis, yAxis, legend, xValues, yValues);
	}
	
	public static BarChart barChart(String applicationTitle, String chartTitle, String xAxis, String yAxis, String[] legend, String[] categories, Double[][] values) {
		return new BarChart(applicationTitle, chartTitle, xAxis, yAxis, legend, categories, values);
	}
}

