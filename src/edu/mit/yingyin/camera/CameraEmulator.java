package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Arrays;

import javax.imageio.ImageIO;

import edu.mit.yingyin.util.CommandLineOptions;

/**
 * Emulates a camera by using saved images.
 * @author Ying Yin
 *
 */
public class CameraEmulator implements ICameraDriver {

	private String[] files;
  private int index = 0;
  
	public BufferedImage captureNow() {
	  BufferedImage img = null;
		try {
		  if (index >= files.length) 
		    index = files.length - 1;
		  FileInputStream file = new FileInputStream(getRecordDir() + 
		                                             files[index++]);
		  img = ImageIO.read(file);
		  file.close();
	  } catch (IOException e) {
	    System.err.println(e.getMessage());
    }
	  
	  if (img == null)
	    img = new BufferedImage(getWidth(), getHeight(), 
	                            BufferedImage.TYPE_INT_ARGB);
	  return img;
	}

	public void initialize(int camera) {
	  File dir = new File(getRecordDir());
	  FilenameFilter fileFilter = new FilenameFilter() {
      
      @Override
      public boolean accept(File dir, String name) {
        return name.endsWith(".png");
      }
    };
	  files = dir.list(fileFilter);
	  Arrays.sort(files);
	}
	
  public int getWidth() { return 640; }

  public int getHeight() { return 480; }

  @Override
  public void cleanUp() {}

  private String getRecordDir() {
    return CommandLineOptions.getOptionValue("record-dir", "./");
  }
}
