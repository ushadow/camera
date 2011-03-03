package edu.mit.yingyin.webcam;

import java.nio.IntBuffer;
import java.util.Vector;

import rywang.util.DirectBufferUtils;

public class WebcamDriverFirei implements IWebcamDriver {
	
	public enum CameraControl {
		BRIGHTNESS, EXPOSURE, SHARPNESS, UB, VR, HUE, SATURATION, GAMMA, SHUTTER, 
		GAIN, IRIS, FOCUS, TEMPERATURE, ZOOM
	}
	
	
	public WebcamDriverFirei() {
		controlBlock = DirectBufferUtils.allocateIntBuffer(2);
	}
	
	@Override
	public IntBuffer allocateImageBuffer() {
		return DirectBufferUtils.allocateIntBuffer(getWidth() * getHeight());
	}

	@Override
	public void captureNow(IntBuffer image, int width, int height) {
		image.clear();
		captureNowNative(controlBlock, image, width, height);
	}

	@Override
	public void captureNow(IntBuffer image) {
		captureNow(image, getWidth(), getHeight());
	}

	/**
	 * Cleanup the context for the Firei driver. This method should be called 
	 * after the last caputreNow has finished (returned).
	 */
	@Override
	public void cleanUp() {
		cleanUp(controlBlock);
	}

	@Override
	public int getHeight() {
		return 480;
	}

	@Override
	public int getWidth() {
		return 640;
	}

	@Override
	public void initialize(int camera) {
		initialize(controlBlock, camera);
	}
	
	/**
	 * Set the camera control property value. If the value to set is negative, 
	 * there is no effect.
	 * 
	 * @param property the control property to set
	 * @param value	the value must be >= 0
	 */
	public void setProperty(CameraControl property, int value) {
		if (value >= 0)
			setPropertyNative(controlBlock, property.ordinal(), value);
	}
	
	/**
	 * Get the current value of the property and whether the property is set to 
	 * auto of the camera 
	 * @param property the property of the camera control
	 * @return a Vector of Integers, the first int is the value and the second is 
	 * auto
	 */
	public Vector<Integer> getCurrentProperty(CameraControl property) {
		IntBuffer value = DirectBufferUtils.allocateIntBuffer(1);
		IntBuffer auto = DirectBufferUtils.allocateIntBuffer(1);
		getCurrentPropertyNative(controlBlock, property.ordinal(), value, auto);
	
		Vector<Integer> vi = new Vector<Integer>(2);
		vi.add(value.get(0));
		vi.add(auto.get(0));
		
		return vi;
	}
	
	/**
	 * Qeuries the camera about the min and max values of a control property.
	 * 
	 * @param property the control property to query, for example 
	 * WebcamDriverFirei.CameraControl.EXPOSURE
	 * @return a Vector of Integers, the first one is the minimum value, and the 
	 * second one is the maximum value
	 */
	public Vector<Integer> queryProperty(CameraControl property) {
		IntBuffer min = DirectBufferUtils.allocateIntBuffer(1);
		IntBuffer max = DirectBufferUtils.allocateIntBuffer(1);
		qeuryPropertyNative(controlBlock, property.ordinal(), min, max);
		
		Vector<Integer> vi = new Vector<Integer>(2);
		vi.add(min.get(0));
		vi.add(max.get(0));
		
		return vi;
	}
	
	public void setAutoProperty(CameraControl property) {
		setAutoPropertyNative(controlBlock, property.ordinal());
	}
	
	static {
	  System.loadLibrary("FireiDriver");
	}
	
	private IntBuffer controlBlock;
	
	private native void initialize(IntBuffer cb, int camera);
	private native void captureNowNative(IntBuffer cb, IntBuffer image, int width, 
	                                     int height);
	private native void cleanUp(IntBuffer cb);
	private native void setPropertyNative(IntBuffer cb, int property, int value);
	private native int getCurrentPropertyNative(IntBuffer cb, int property, 
	                                            IntBuffer value, IntBuffer auto);
	private native void qeuryPropertyNative(IntBuffer cb, int property, 
	                                        IntBuffer min, IntBuffer max);
	private native void setAutoPropertyNative(IntBuffer cb, int property);
}
