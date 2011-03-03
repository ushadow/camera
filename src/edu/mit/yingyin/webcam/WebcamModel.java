package edu.mit.yingyin.webcam;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.IntBuffer;
import java.util.Vector;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import javax.imageio.ImageIO;

import edu.mit.yingyin.image.ImageConvertUtils;

import yingyin.common.EnvConstants;
import yingyin.webcam.gui.WebcamView;

public class WebcamModel {
	
	public static final String CAM_REC_DIR = EnvConstants.LOCAL_FOLDER + 
	                                         EnvConstants.CALIB_DATA_DIR;
	
	private boolean captureStarted = false;
	private boolean continuousRecording = false;
	
	private IntBuffer ib;
	private BufferedImage bi;
	private IWebcamDriver driver = null;
	private WebcamView wv = null;
	private Thread captureThread = null;
	private Thread savingThread = null;
	private static final int WIDTH = 640;
	private static final int HEIGHT = 480;
	private BlockingQueue<BufferedImage> blockingQueue = 
	    new LinkedBlockingQueue<BufferedImage>();
	
	public WebcamModel(IWebcamDriver webcamDriver) {		
		this.driver = webcamDriver;
		driver.initialize(0);
		
		if (driver instanceof WebcamDriverFirei) {
			WebcamDriverFirei driverFirei = (WebcamDriverFirei)driver;
			driverFirei.setAutoProperty(WebcamDriverFirei.CameraControl.UB);
			driverFirei.setAutoProperty(WebcamDriverFirei.CameraControl.VR);
			driverFirei.setAutoProperty(WebcamDriverFirei.CameraControl.BRIGHTNESS);
			driverFirei.setProperty(WebcamDriverFirei.CameraControl.SATURATION,90);
			driverFirei.setProperty(WebcamDriverFirei.CameraControl.GAIN, 0); //180
			driverFirei.setProperty(WebcamDriverFirei.CameraControl.EXPOSURE, 255); //297
		}
	
    ib = driver.allocateImageBuffer();
    bi = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_ARGB);
	}
	
	public IWebcamDriver getDriver() {
		return driver;
	}
	
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
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void exit() {	
		driver.cleanUp();
		System.exit(0);
	}
	
	public void startCapture(WebcamView _wv) {		
		if(captureStarted)
			return;
		
		this.wv = _wv;
		captureStarted = true;
		
		captureThread = new Thread(new Runnable() {
			public void run() {
				long totalElapsed = 0;
				long totalFrames = 0;
				
				while (captureStarted) {
					try {
						long startTime = System.nanoTime();
						driver.captureNow(ib, WIDTH, HEIGHT);
						long elapsed = System.nanoTime() - startTime;
						ImageConvertUtils.IntBuffer2BufferedImage(ib, bi);
						totalElapsed += elapsed;
						totalFrames++;
						wv.setImage(bi);	
						if (continuousRecording)
							blockingQueue.offer(bi);
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
	public void continuousRecording(String dir) {
		continuousRecording = true;
		
		savingThread = new SavingThread(dir);
		
		savingThread.start();
	}
	
	public Vector<Integer> getControlRange(
	    WebcamDriverFirei.CameraControl control) {
		Vector<Integer> ret = null;
		
		if(driver instanceof WebcamDriverFirei)
			ret = ((WebcamDriverFirei)driver).queryProperty(control);
		
		return ret;
	}
	
	public Vector<Integer> getControlValue(
	    WebcamDriverFirei.CameraControl control) {
		if (driver instanceof WebcamDriverFirei)
			return ((WebcamDriverFirei)driver).getCurrentProperty(control);
		
		return null;
	}
	
	public void setControlValue(WebcamDriverFirei.CameraControl control, 
	                            int value) {
		if(driver instanceof WebcamDriverFirei)
			((WebcamDriverFirei)driver).setProperty(control, value);
	}
	
	private class SavingThread extends Thread {
		final private static String IMAGE_NAME = "/image";
		final private static String IMAGE_TYTE = ".png";
		private String filePrefix;
		private int index = 0;
		
		public SavingThread(String savingDir) {
			this.filePrefix = savingDir + IMAGE_NAME;
		}
		
		public void run() {
			while(continuousRecording) {
				String fileName = filePrefix + index + IMAGE_TYTE;
				index++;         
				try {
					ImageIO.write(blockingQueue.take(),"PNG", new File(fileName));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
}
