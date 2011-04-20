package edu.mit.yingyin.camera.gui;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;

import edu.mit.yingyin.camera.CameraDriverFirei;


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
	public ControlDialog(CameraDriverFirei wdf) {
		super("Control");
		
		JPanel panel = new JPanel();
		panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.EXPOSURE, wdf));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.GAIN, wdf));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.BRIGHTNESS, 
		                           wdf));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.UB, wdf));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.VR, wdf));
		panel.add(new ControlPanel(CameraDriverFirei.CameraControl.SATURATION, 
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
