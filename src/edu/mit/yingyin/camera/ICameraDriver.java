package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;

public interface ICameraDriver {

	public static final int FRAME_HEIGHT = 480;
	public static final int FRAME_WIDTH = 640;
	
	public abstract void initialize(int camera); 

	public abstract void captureNow(BufferedImage image);

	public abstract void cleanUp();
	
	public abstract int getWidth();
	
	public abstract int getHeight();
}
