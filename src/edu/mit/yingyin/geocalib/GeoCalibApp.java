package edu.mit.yingyin.geocalib;

import javax.swing.SwingUtilities;

import edu.mit.yingyin.geocalib.GeoCalibModel.ImageType;


/**
 * Main driver for the geometric calibration program.
 * 
 * Keys:
 * 	s: save all points
 *  p: automatically create points from the first 3 points
 *  c: clear all points
 *  q: quit program
 * Mouse:
 * 	left click: create a point
 *  right click: remove the last point
 *  
 * @author Ying Yin
 *
 */
public class GeoCalibApp {

	public static final ImageType IMAGE_TYPE = ImageType.CAMERA;
	public static final String IMAGE_PATH = "CameraCalib/patternNumbered.png";
	
	/** Path to rectified camera image. */
	public static final String CAMERA_IMAGE_PATH = "cameraImageRect.png";
	
	public static void main(String[] args) {
	    
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				String imagePath;
				
				if(IMAGE_TYPE == ImageType.PROJECTOR)
					imagePath = IMAGE_PATH;
				else imagePath = CAMERA_IMAGE_PATH;
				
				CalibView.createAndShow(new GeoCalibModel(IMAGE_TYPE, imagePath));
			}
		});		
	}
}
