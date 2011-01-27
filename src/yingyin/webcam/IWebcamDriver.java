package yingyin.webcam;

import java.nio.IntBuffer;

public interface IWebcamDriver {

	public static final int FRAME_HEIGHT = 480;
	public static final int FRAME_WIDTH = 640;
	
	public abstract void initialize(int camera); 

	public abstract void captureNow(IntBuffer image, int width, int height);

	public abstract void captureNow(IntBuffer image);
	
	public abstract void cleanUp();
	
	public abstract int getWidth();
	
	public abstract int getHeight();
	
	public abstract IntBuffer allocateImageBuffer();
	
}
