package yingyin.webcam.gui;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;

import yingyin.webcam.WebcamDriverFirei;

/**
 * Control dialog for adjusting parameters of Firei camera.
 * @author Ying
 *
 */
public class ControlDialog extends JFrame {

	private static final long serialVersionUID = 1L;

	/**
	 * Constructs a ControlDialog and initialize its components. 
	 * @param wdf Driver for the Firei camera. The driver has to call the 
	 * initialize method before being passed as a parameter.
	 */
	public ControlDialog(WebcamDriverFirei wdf) {
		super("Control");
		
		JPanel panel = new JPanel();
		panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.EXPOSURE, wdf));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.GAIN, wdf));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.BRIGHTNESS, 
		                           wdf));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.UB, wdf));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.VR, wdf));
		panel.add(new ControlPanel(WebcamDriverFirei.CameraControl.SATURATION, 
		                           wdf));
		
		setContentPane(panel);
	}
	
	/**
	 * Display the ControlDialog
	 */
	public void showUI() {
		pack();
		setVisible(true);
	}
}
