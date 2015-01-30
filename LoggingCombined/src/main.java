import java.io.FileNotFoundException;


public class main {
	
	public static void main(String[] args) {
		try {
			LoggingFrame frame = new LoggingFrame();
			frame.setSize(700, 700);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

	}

}
