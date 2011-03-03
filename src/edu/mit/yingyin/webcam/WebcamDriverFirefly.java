package edu.mit.yingyin.webcam;

import java.nio.IntBuffer;

import rywang.util.DirectBufferUtils;

// Simple wrapper of the Firefly camera.
//
// Control of the camera can be done through the FlyCap program privided by 
// Point Grey Research.
public class WebcamDriverFirefly implements IWebcamDriver {
  
  private static final int FRAME_RATE = 30;

  static {
    System.loadLibrary("pointgrey_trigger");
  }
  
  public WebcamDriverFirefly() {
    controlBlock = DirectBufferUtils.allocateIntBuffer(2);
  }
  
  @Override
  // Starts the camera in the exteranl trigger mode 0.
  public void initialize(int camera) {
    initialize(controlBlock, camera, FRAME_RATE);
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
  
  public native void initialize(IntBuffer cb, int camera, int frameRate);
  public native void captureNow(IntBuffer cb, IntBuffer image, int width, 
                                int height);
  public native void cleanUp(IntBuffer cb);
  
  private IntBuffer controlBlock;
}
