package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.io.File;
import java.io.FileInputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Arrays;

import javax.imageio.ImageIO;

import edu.mit.yingyin.image.ImageConvertUtils;

/**
 * Emulates a camera by using saved images.
 * 
 * The default directory it checks for saved images is the current directory. To
 * use another directory, pass the directory in the command line
 * @author Ying Yin
 *
 */
public class CameraDriverEmulator implements ICameraDriver {

	private String[] files;
  private int index = 0;
  private String dirName = "./";
  
  /**
   * Creates a new CameraDriverEmulator instance.
   * @param dirName directory to get the saved images.
   */
  public CameraDriverEmulator(String dirName) {
    this.dirName = dirName;
  }
  /**
   * Captures a new image.
   * 
   * @return an image.
   */
	public void captureNow(BufferedImage bi) {
		try {
		  if (index >= files.length) 
		    index = files.length - 1;
		  FileInputStream file = new FileInputStream(dirName + files[index++]);
		  BufferedImage img = ImageConvertUtils.convertType(ImageIO.read(file), 
		                                                    bi.getType());
		  int[] rgbArray = ((DataBufferInt) img.getRaster().getDataBuffer()).
          getData();
		  int[] dstArray = ((DataBufferInt) bi.getRaster().getDataBuffer()).
          getData();
		  System.arraycopy(rgbArray, 0, dstArray, 0, rgbArray.length);
		  file.close();
	  } catch (IOException e) {
	    System.err.println(e.getMessage());
    }
	}

	public void initialize(int camera) {
	  File dir = new File(dirName);
	  FilenameFilter fileFilter = new FilenameFilter() {
      
      @Override
      public boolean accept(File dir, String name) {
        return name.endsWith(".png");
      }
    };
	  files = dir.list(fileFilter);
	  Arrays.sort(files);
	  index = 0;
	}
	
  public int getWidth() { return 640; }

  public int getHeight() { return 480; }

  @Override
  public void cleanUp() {}
}
