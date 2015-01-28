import java.io.FileNotFoundException;

import javax.swing.JFrame;


public class main {
	public static void main(String[] args){
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	JFrame frame = new JFrame("SimpleTableDemo");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                LoggingFrame newContentPane; 
				try {
					newContentPane = new LoggingFrame();
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
} 
