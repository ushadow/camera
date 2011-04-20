package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.nio.IntBuffer;

import rywang.util.DirectBufferUtils;

// Simple wrapper of the Firefly camera.
//
// Control of the camera can be done through the FlyCap program privided by 
// Point Grey Research.
public class CameraDriverFirefly implements ICameraDriver {
  
  private static final int FRAME_RATE = 30;

  static {
    System.loadLibrary("pointgrey_trigger");
  }

  public static void main(String[] args) {
    String[] deviceNames = getDeviceNames();
    for (String s : deviceNames) {
      System.out.println(s);
    }
  }
  public static native String[] getDeviceNames();
  
  private IntBuffer controlBlock;
  private IntBuffer imageBuf;
  private int[] rgbArray;
  private boolean useTrigger;
  
  public CameraDriverFirefly(boolean useTrigger) {
    controlBlock = DirectBufferUtils.allocateIntBuffer(2);
    imageBuf = DirectBufferUtils.allocateIntBuffer(getWidth() * getHeight());
    rgbArray = new int[imageBuf.capacity()];
    this.useTrigger = useTrigger;
  }
  
  // Starts the camera in the external trigger mode 0 if specified in
  // constructor
  public void initialize(int camera) {
    initialize(controlBlock, camera, FRAME_RATE, useTrigger);
  }

  // Captures a new image until there is an external trigger.
  public void captureNow(BufferedImage image) {
    captureNow(controlBlock, imageBuf, getWidth(), getHeight());
    imageBuf.rewind();
    imageBuf.get(rgbArray);
    int[] dstArray = ((DataBufferInt) image.getRaster().getDataBuffer()).
                     getData();
    System.arraycopy(rgbArray, 0, dstArray, 0, rgbArray.length);
  }

  public void cleanUp() {
    cleanUp(controlBlock);
  }

  public int getWidth() { return 640; }

  public int getHeight() { return 480; }

  public IntBuffer allocateImageBuffer() {
    return DirectBufferUtils.allocateIntBuffer(getWidth() * getHeight());
  }
  public void decreaseExposure() { decreaseExposure(controlBlock); }
  public void increaseExposure() { increaseExposure(controlBlock); }
  public void increaseSaturation() { increaseSaturation(controlBlock); }
  public void decreaseSaturation() { decreaseSaturation(controlBlock); }
  private native void initialize(IntBuffer cb, int camera, int frameRate, 
                                 boolean useTrigger);
  private native void captureNow(IntBuffer cb, IntBuffer image, int width, 
                                int height);
  private native void cleanUp(IntBuffer cb);
  private native void increaseExposure(IntBuffer cb);
  private native void decreaseExposure(IntBuffer cb);
  private native void increaseSaturation(IntBuffer cb);
  private native void decreaseSaturation(IntBuffer cb);
}
