package yingyin.webcam.gui;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import edu.mit.yingyin.util.FileUtil;


public class ImagePanel extends JPanel implements MouseListener
{
	    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private BufferedImage myimg = null;
	private CameraView parent =null;
	
    public ImagePanel(CameraView mf) 
    {
      setLayout(null);
      setPreferredSize(new Dimension(640,480));
      parent = mf;
      addMouseListener(this);
      setOpaque(false);
    }
    
    public void setImage(BufferedImage img) 
    {
      this.myimg = img;
      repaint();
    }
    
    public void update(Graphics g)
    {
    	paint(g);
    }
    
    public void paint(Graphics g) 
    {
      if (myimg != null) 
      {
    	  ((Graphics2D)g).drawImage(myimg, null, 0, 0);
      }
    }
    
    /**
     * Save image to a particular path
     * @param filePath full path to save the image. If the path is not valid, an error message is generated
     */
    public void saveImage(String filePath)
    {
		File f = new File(filePath);
		saveImage(f);
    }
    
    public void saveImage(File f)
    {
    	try {
    		String extension = FileUtil.getExtension(f);
    		if(extension == null || (!extension.equals(FileUtil.JPG)&&!extension.equals(FileUtil.PNG)))
    		{
    			extension = FileUtil.PNG;
    			f = FileUtil.setExtension(f,extension);
    		}
    		
    		ImageIO.write(myimg, extension, f);
    		
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    }

	@Override
	public void mouseClicked(MouseEvent e) {
		Point p = e.getPoint();
		int value = myimg.getRGB(p.x, p.y);
		parent.setStatus(" X: " + p.x +
						 " Y: " + p.y +
						 " B: " + (short)(value & 0x000000FF)+ 
					     " G: " + (short)((value>>8)& 0x000000FF)+ 
					     " R: " + (short)((value>>16)&0x000000FF)+ 
					     " A: " + (short)((value>>24)&0x000000FF));
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
			
	}
}
