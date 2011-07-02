package edu.mit.yingyin.geocalib;

import javax.swing.SwingUtilities;

import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;

import edu.mit.yingyin.util.CommandLineOptions;


/**
 * Main driver for the geometric calibration program.
 * 
 * Keys:
 * 	s: saves all points.
 *  p: automatically creates points from the first 3 points.
 *  c: clears all points.
 *  q: quits program.
 * Mouse:
 * 	left click: creates a point.
 *  right click: removes the last point.
 *  
 * @author Ying Yin
 *
 */
public class GeoCalibApp {

	@SuppressWarnings("static-access")
  public static void main(String[] args) {
	  Option imagePathOption = OptionBuilder.withLongOpt("path").hasArg().
	      create();
	  
	  CommandLineOptions.addOption(imagePathOption);
	  
	  CommandLineOptions.parse(args);
	  
	  final String imagePath = CommandLineOptions.getOptionValue("path", 
	      "data/displayed_image.png");
	  
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				CalibView.createAndShow(new GeoCalibModel(imagePath));
			}
		});		
	}
}
