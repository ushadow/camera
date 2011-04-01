package edu.mit.yingyin.camera;

import java.nio.IntBuffer;

import rywang.util.DirectBufferUtils;
import webcam.IWebcamDriver;

// Simple wrapper of the Firefly camera.
//
// Control of the camera can be done through the FlyCap program privided by 
// Point Grey Research.
public class CameraDriverFirefly implements IWebcamDriver {
  
  private static final int FRAME_RATE = 30;

  static {
    System.loadLibrary("pointgrey_trigger");
  }
  
  private boolean useTrigger;
  
  public CameraDriverFirefly(boolean useTrigger) {
    controlBlock = DirectBufferUtils.allocateIntBuffer(2);
    this.useTrigger = useTrigger;
  }
  
  @Override
  // Starts the camera in the external trigger mode 0 if specified in
  // constructor
  public void initialize(int camera) {
    initialize(controlBlock, camera, FRAME_RATE, useTrigger);
  }

  @Override
  // Captures a new image until there is an external trigger.
  public void captureNow(IntBuffer image, int width, int height) {
    captureNow(controlBlock, image, width, height);
  }

  @Override
  public void captureNow(IntBuffer image) {
    captureNow(controlBlock, image, getWidth(), getHeight());
  }

  @Override
  public void cleanUp() {
    cleanUp(controlBlock);
  }

  @Override
  public int getWidth() { return 640; }

  @Override
  public int getHeight() { return 480; }

  @Override
  public IntBuffer allocateImageBuffer() {
    return DirectBufferUtils.allocateIntBuffer(getWidth() * getHeight());
  }
  
  public static native String[] getDeviceNames();
  
  private native void initialize(IntBuffer cb, int camera, int frameRate, 
                                 boolean useTrigger);
  private native void captureNow(IntBuffer cb, IntBuffer image, int width, 
                                int height);
  private native void cleanUp(IntBuffer cb);
  
  public void increaseExposure() { increaseExposure(controlBlock); }
  
  private native void increaseExposure(IntBuffer cb);
  
  public void decreaseExposure() { decreaseExposure(controlBlock); }
  
  private native void decreaseExposure(IntBuffer cb);
  
  private IntBuffer controlBlock;
  
  public static void main(String[] args) {
    String[] deviceNames = getDeviceNames();
    for (String s : deviceNames) {
      System.out.println(s);
    }
  }
}
