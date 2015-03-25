
public class Main {
   public static void main(String[] args) {
	   
	   String[] legend = new String[] {"Mac","Windows","Linux"};
	   String[] categories = new String[] {"Speed","Memory","Price"};
	   Double[][] values = new Double[][] {{8.0,8.0,5.0},{7.0,7.0,8.0},{6.0,6.0,10.0}};
	   
	   while (true) {
		   new BarChart("Sample bar", "Sample Computer chart", "Category", "Score", legend, categories, values);
	}   
   }
} 
