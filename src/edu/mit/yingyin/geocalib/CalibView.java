package edu.mit.yingyin.geocalib;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class CalibView extends JFrame implements KeyListener {
  private class ImagePanel extends JPanel implements MouseListener {
    private static final long serialVersionUID = 1L;

    private static final int OVAL_WIDTH = 10;

    private BufferedImage myimg = null;
    private GeoCalibModel icm;

    public ImagePanel(CalibView imf, Dimension d, GeoCalibModel icm) {
      super();
      setLayout(null);
      setPreferredSize(d);
      this.icm = icm;
      addMouseListener(this);
      setOpaque(false);
    }

    public void setImage(BufferedImage img) {
      this.myimg = img;
      repaint();
    }

    public void update(Graphics g) {
      paint(g);
    }

    public void update() {
      // Validates this container and all of its subcomponents.
      // The validate method is used to cause a container to lay out its
      // subcomponents again.
      // It should be invoked when this container's subcomponents are modified
      // (added to or removed from
      // the container, or layout-related information changed) after the 
      // container has been displayed.
      validate();
      repaint();
    }

    public void paint(Graphics g) {
      Graphics2D g2d = (Graphics2D) g;
      if (myimg != null)
        g2d.drawImage(myimg, null, 0, 0);

      List<Point> pts = icm.getImagePoints();

      g2d.setColor(Color.RED);
      for (Point p : pts) {
        if (!icm.isCameraImage())
          SwingUtilities.convertPointFromScreen(p, this);

        g2d.drawOval(p.x - OVAL_WIDTH / 2, p.y - OVAL_WIDTH / 2, OVAL_WIDTH, 
            OVAL_WIDTH);
      }
    }

    /**
     * Save image to a particular path
     * 
     * @param fileName  path to save the image. If the path is not valid, an 
     *                  error message is generated.
     */
    public void saveImage(String fileName) {
      try {
        ImageIO.write(myimg, "PNG", new File(fileName));
      } catch (IOException e) {

        // folder may not exist, show the error message
        // the file is not saved, but the program can continue
        System.err.println(e.getMessage());
      }
    }


    @Override
    public void mousePressed(MouseEvent e) {
      Point p = e.getPoint();

      // left click
      if ((e.getModifiersEx() | InputEvent.BUTTON1_DOWN_MASK) == 
          InputEvent.BUTTON1_DOWN_MASK) {
        // Convert a point from a component's coordinate system to screen
        // coordinates.
        if (!icm.isCameraImage())
          SwingUtilities.convertPointToScreen(p, this);

        icm.addImagePoint(p);
        repaint();
      }

      // right click
      if ((e.getModifiersEx() | InputEvent.BUTTON3_DOWN_MASK) == 
          InputEvent.BUTTON3_DOWN_MASK) {
        icm.removeLastPoint();
        repaint();
      }
    }

    @Override
    public void mouseReleased(MouseEvent arg0) {}
    
    @Override
    public void mouseClicked(MouseEvent e) {}
    
    @Override
    public void mouseEntered(MouseEvent arg0) {}
    
    @Override
    public void mouseExited(MouseEvent arg0) {}
  }
  
  private static final long serialVersionUID = -6672495506940884693L;

  ImagePanel ip;
  GeoCalibModel icm;

  public CalibView(GeoCalibModel icm) {
    super("Calibration Pattern");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setUndecorated(true);
    setResizable(false);

    this.icm = icm;
    BufferedImage bi = icm.getImage();

    ip = new ImagePanel(this, new Dimension(bi.getWidth(), bi.getHeight()), 
                        icm);

    ip.setImage(bi);
    getContentPane().add(ip);
    addKeyListener(this);
    this.setLocation(170, 150);
  }

  public static void createAndShow(GeoCalibModel icm) {
    CalibView imf = new CalibView(icm);
    imf.pack();
    imf.setVisible(true);
  }

  public void setStatus(String status) {}

  @Override
  public void keyPressed(KeyEvent ke) {
    switch (ke.getKeyCode()) {
    case KeyEvent.VK_S:
      icm.saveImagePoints();
      break;

    case KeyEvent.VK_P:
      icm.createPoints();
      ip.update();
      break;

    case KeyEvent.VK_C:
      icm.clearPoints();
      ip.update();
      break;

    case KeyEvent.VK_Q:
    case KeyEvent.VK_ESCAPE:
      System.exit(0);
      break;
    default:
      break;
    }
  }

  @Override
  public void keyReleased(KeyEvent arg0) {}

  @Override
  public void keyTyped(KeyEvent arg0) {}

}
