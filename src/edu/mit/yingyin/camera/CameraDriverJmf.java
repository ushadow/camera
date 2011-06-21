package edu.mit.yingyin.camera;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.io.IOException;
import java.util.Vector;

import javax.media.Buffer;
import javax.media.CannotRealizeException;
import javax.media.CaptureDeviceInfo;
import javax.media.CaptureDeviceManager;
import javax.media.Format;
import javax.media.Manager;
import javax.media.MediaLocator;
import javax.media.NoPlayerException;
import javax.media.Player;
import javax.media.control.FormatControl;
import javax.media.control.FrameGrabbingControl;
import javax.media.control.FrameRateControl;
import javax.media.format.VideoFormat;

/**
 * WebcamDriverJmf is a driver for webcams using java media framework
 * 
 * @author Ying
 * 
 */
public class CameraDriverJmf implements ICameraDriver {

  /* Constants */
  private static final String CAPTURE_FORMAT = VideoFormat.RGB;
  public static final float FRAME_RATE = (float) 15.0; // fps

  // Video format: RGB, 640x480, 24 bit
  private static final int FORMAT_INDEX = 10; // the index is obtained from JMF
                                              // Registry

  private CaptureDeviceInfo device = null; // Contains the device properties
  private MediaLocator ml = null; // Contains the location of the media coming
                                  // from the webcam
  private FormatControl fc = null;
  private static Player player = null;
  private FrameGrabbingControl fgc = null;
  private int[] rgbArray;

  public CameraDriverJmf() {
    rgbArray = new int[getWidth() * getHeight()];
  }

  /**
   * The capture an image frame and store the image in IntBuffer. For each int
   * in the IntBuffer, the least significant byte is green, the second byte is
   * blue, and the third byte is red. If the camera is not ready for capturing,
   * the image may not contain the correct values, and calling get on image may
   * throw BufferUnderflowException.
   * 
   * @param image
   *          an IntBuffer to store the captured image
   * @param width
   *          of the image
   * @param height
   *          of the image
   */
  @Override
  public void captureNow(BufferedImage image) {

    int width = getWidth();
    int height = getHeight();
    Buffer buf = fgc.grabFrame();
    Object o = buf.getData();
    if (o instanceof byte[]) {
      byte[] ba = (byte[]) o;

      if (ba.length >= width * height * 3) {
        for (int h = 0; h < height; h++)
          for (int w = 0; w < width; w++) {
            int index = h * width + w;
            int ibIndex = height * width - 1 - index;
            int baIndex = index * 3;
            rgbArray[ibIndex] = (ba[baIndex] & 0xff) | 
                                ((ba[baIndex + 1] & 0xff) << 8) |
                                ((ba[baIndex + 2] & 0xff) << 16) | 0xff000000;
          }
        int[] dstArray = ((DataBufferInt) image.getRaster().getDataBuffer()).
            getData();
        System.arraycopy(rgbArray, 0, dstArray, 0, rgbArray.length);
      }
    }
  }

  @Override
  public void cleanUp() {
    player.close();
    player.deallocate();
  }

  @Override
  public int getHeight() {

    return 480;
  }

  @Override
  public int getWidth() {
    return 640;
  }

  @SuppressWarnings("rawtypes")
  @Override
  public void initialize(int camera) {

    Vector deviceList = CaptureDeviceManager.getDeviceList(
        new VideoFormat(CAPTURE_FORMAT));

    if (deviceList.size() > camera) {
      device = (CaptureDeviceInfo) deviceList.elementAt(camera);
    } else {
      System.err.println("WebcamDriverJmf::initialize: No device for camera " + 
          camera);
      System.exit(1);
    }

    ml = device.getLocator();

    System.out.println("Media Locator: " + ml.toString());

    try {
      player = Manager.createRealizedPlayer(ml);

      fc = (FormatControl) player.getControl(
          "javax.media.control.FormatControl");
      Format[] formats = fc.getSupportedFormats();

      fc.setFormat(formats[FORMAT_INDEX]);

      System.out.println(fc.getFormat());

      FrameRateControl frc = (FrameRateControl) player
          .getControl("javax.media.control.FrameRateControl");

      frc.setFrameRate(FRAME_RATE);
      System.out.println("Frame rate is: " + frc.getFrameRate());

      player.start();

      fgc = (FrameGrabbingControl) player.getControl(
          "javax.media.control.FrameGrabbingControl");
    } catch (NoPlayerException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (CannotRealizeException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }
}
