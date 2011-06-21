package edu.mit.yingyin.geocalib;

import javax.swing.SwingUtilities;

import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;

import edu.mit.yingyin.geocalib.GeoCalibModel.CalibImageType;
import edu.mit.yingyin.util.CommandLineOptions;


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

	@SuppressWarnings("static-access")
  public static void main(String[] args) {
	  Option calibImageTypeOption = OptionBuilder.withLongOpt("type").
	      hasArg().create();
	  Option imagePathOption = OptionBuilder.withLongOpt("path").hasArg().
	      create();
	  
	  CommandLineOptions.addOption(calibImageTypeOption);
	  CommandLineOptions.addOption(imagePathOption);
	  
	  CommandLineOptions.parse(args);
	  
	  String calibImageTypeStr = CommandLineOptions.getOptionValue("type", 
	      "projector");
	  final String imagePath = CommandLineOptions.getOptionValue("path", 
	      "data/patternNumbered.png");
	  final CalibImageType calibImageType = CalibImageType.valueOf(
	      calibImageTypeStr.toUpperCase());
	  
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				CalibView.createAndShow(new GeoCalibModel(calibImageType, imagePath));
			}
		});		
	}
}
