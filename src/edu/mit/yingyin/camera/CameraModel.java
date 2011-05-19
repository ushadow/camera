package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import javax.imageio.ImageIO;

import edu.mit.yingyin.camera.gui.CameraView;

import rywang.util.awt.BufferedImageUtils;

public class CameraModel {
  
  private class SavingThread extends Thread {
    private String imagePrefix;
    private String imageType;
    private int index = 0;
    
    public SavingThread(String imagePrefix, String imageType) {
      this.imagePrefix = imagePrefix;
      this.imageType = imageType;
    }
    
    public void run() {
      System.out.println("Started continuous recording");
      while(continuousRecording) {
        String fileName = String.format("%s%04d.%s", imagePrefix, index, 
            imageType);
        index++;         
        try {
          ImageIO.write(blockingQueue.take(), "PNG", new File(fileName));
        } catch (IOException e) {
          e.printStackTrace();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
      List<BufferedImage> images = new ArrayList<BufferedImage>();
      blockingQueue.drainTo(images);
      for (BufferedImage image : images) {
        String fileName = String.format("%s%04d.%s", imagePrefix, index, 
            imageType);
        index++;         
        try {
          ImageIO.write(image, "PNG", new File(fileName));
        } catch (IOException e) {
          e.printStackTrace();
        }
      }
      System.out.println("Finished continuous recording");
    }
  }
	
	private boolean captureStarted = false;
	private boolean continuousRecording = false;
	
	private BufferedImage bi;
	private ICameraDriver driver = null;
	private CameraView wv = null;
	private Thread captureThread = null;
	private Thread savingThread = null;
	private BlockingQueue<BufferedImage> blockingQueue = 
	    new LinkedBlockingQueue<BufferedImage>();
	
	public CameraModel(ICameraDriver webcamDriver) {		
		this.driver = webcamDriver;
		driver.initialize(0);
		
		if (driver instanceof CameraDriverFirei) {
			CameraDriverFirei driverFirei = (CameraDriverFirei)driver;
			driverFirei.setAutoProperty(CameraDriverFirei.CameraControl.UB);
			driverFirei.setAutoProperty(CameraDriverFirei.CameraControl.VR);
			driverFirei.setAutoProperty(CameraDriverFirei.CameraControl.BRIGHTNESS);
			driverFirei.setProperty(CameraDriverFirei.CameraControl.SATURATION,90);
			driverFirei.setProperty(CameraDriverFirei.CameraControl.GAIN, 0); //180
			driverFirei.setProperty(CameraDriverFirei.CameraControl.EXPOSURE, 255); //297
		}
		
		bi = new BufferedImage(640, 480, BufferedImage.TYPE_INT_ARGB);
	}
	
	public ICameraDriver getDriver() { return driver; }
	
	/**
	 * If the capturing thread is not started, return;
	 * else stop the capturing thread and wait for the thread to stop.
	 */
	public void stopCapture() {
		if(!captureStarted)
			return;
			
		captureStarted = false;
		
		try {
			captureThread.join();
			if(continuousRecording) {
				continuousRecording = false;
				savingThread.join();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public void exit() {	
		driver.cleanUp();
		System.exit(0);
	}
	
	public void startCapture(CameraView _wv) {		
		if(captureStarted) return;
		
		this.wv = _wv;
		captureStarted = true;
		
		captureThread = new Thread(new Runnable() {
			public void run() {
				long totalElapsed = 0;
				long totalFrames = 0;
				
				while (captureStarted) {
					try {
						long startTime = System.nanoTime();
						driver.captureNow(bi);
						long elapsed = System.nanoTime() - startTime;
						totalElapsed += elapsed;
						totalFrames++;
						wv.setImage(bi);	
						if (continuousRecording)
							blockingQueue.offer(BufferedImageUtils.fastCopy(bi));
					} catch (Exception e) {
					  e.printStackTrace();
					}
				}
				
				System.out.println("Average capture elapsed time is " + 
				    totalElapsed / (totalFrames * 1000000) + "ms.");
			}
		});
		
		captureThread.start();
	}
	
	/**
	 * Start a thread to continuously save the image to the local directory.
	 * @param dir directory to save the images
	 */
	public void continuousRecording(String imagePrefix, String imageType) {
		continuousRecording = true;
		savingThread = new SavingThread(imagePrefix, imageType);
		savingThread.start();
	}
	
	public void stopRecording() {
	  continuousRecording = false;
	}
	
	public Vector<Integer> getControlRange(
	    CameraDriverFirei.CameraControl control) {
		Vector<Integer> ret = null;
		
		if(driver instanceof CameraDriverFirei)
			ret = ((CameraDriverFirei)driver).queryProperty(control);
		
		return ret;
	}
	
	public Vector<Integer> getControlValue(
	    CameraDriverFirei.CameraControl control) {
		if (driver instanceof CameraDriverFirei)
			return ((CameraDriverFirei)driver).getCurrentProperty(control);
		
		return null;
	}
	
	public void setControlValue(CameraDriverFirei.CameraControl control, 
	                            int value) {
		if(driver instanceof CameraDriverFirei)
			((CameraDriverFirei)driver).setProperty(control, value);
	}
	
	public void increaseExposure() {
	  if (driver instanceof CameraDriverFirefly) {
	    CameraDriverFirefly firefly = (CameraDriverFirefly) driver;
	    firefly.increaseExposure();
	  }
	}
	
	public void decreaseExposure() {
    if (driver instanceof CameraDriverFirefly) {
      CameraDriverFirefly firefly = (CameraDriverFirefly) driver;
      firefly.decreaseExposure();
    }
	}
	
	public void increaseSaturation() {
    if (driver instanceof CameraDriverFirefly) {
      CameraDriverFirefly firefly = (CameraDriverFirefly) driver;
      firefly.increaseSaturation();
    }
  }
  
  public void decreaseSaturation() {
    if (driver instanceof CameraDriverFirefly) {
      CameraDriverFirefly firefly = (CameraDriverFirefly) driver;
      firefly.decreaseSaturation();
    }
  }
}
