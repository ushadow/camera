package edu.mit.yingyin.camera.gui;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;

import edu.mit.yingyin.camera.CameraDriverFirefly;
import edu.mit.yingyin.camera.CameraDriverFirei;
import edu.mit.yingyin.camera.CameraDriverEmulator;
import edu.mit.yingyin.camera.CameraModel;
import edu.mit.yingyin.camera.ICameraDriver;
import edu.mit.yingyin.gui.StatusBar;
import edu.mit.yingyin.util.CommandLineOptions;

/**
 * Main frame for display webcam images. Allows saving of the image.
 * @author Ying
 * 
 */
public class CameraView extends JFrame implements WindowListener, KeyListener {

  static {
    Option saveDirOption = OptionBuilder.withLongOpt("save-dir").hasArg().
        create();
    Option imagePrefixOption = OptionBuilder.withLongOpt("image-prefix").
        hasArg().create();
    Option imageTypeOption = OptionBuilder.withLongOpt("image-type").hasArg().
        create();
    Option cameraType = OptionBuilder.withLongOpt("camera-type").hasArg().
        create();
    Option recordDir = OptionBuilder.withLongOpt("record-dir").hasArg().
    create();
    CommandLineOptions.addOption(recordDir);
    CommandLineOptions.addOption(saveDirOption);
    CommandLineOptions.addOption(imagePrefixOption);
    CommandLineOptions.addOption(imageTypeOption);
    CommandLineOptions.addOption(cameraType);
  }
  
  public static String getCameraType() {
    return CommandLineOptions.getOptionValue("camera-type", "emulator");
  }
  
  public static String getSaveDir() {
    return CommandLineOptions.getOptionValue("save-dir", "./");
  }  
    
  public static String getImagePrefix() {
    return CommandLineOptions.getOptionValue("image-prefix", "image");
  }
  
  public static String getImageType() {
    return CommandLineOptions.getOptionValue("image-type", "png");
  }
  
	private static final long serialVersionUID = 1L;
	protected ImagePanel ip;
	protected ICameraDriver wd;
	protected CameraModel webcamModel = null;
	
	/*menu*/
	private JMenu menuOptions;
	private JMenu menuFile;
	private JMenuItem menuItemControls;
	private JMenuItem  menuItemSaveAs;
	
	protected ControlDialog cd= null;
	protected StatusBar sb = null;
	
	private int imageIndex = 1;
	private String lastAccessedDir = "./";

	/**
	 * Create an instance of main frame for displaying image frame captured from 
	 * webcam
	 * @param title title of the main frame
	 * @param _wdf	webcam driver for Firei cambera, it has to be initialized 
	 * before passed as a parameter
	 */
	public CameraView(String title, CameraModel webcamModel){
		super(title);
		this.webcamModel = webcamModel;
		
    ip = new ImagePanel(this);
    getContentPane().add(ip);
    sb = new StatusBar();
    getContentPane().add(sb, java.awt.BorderLayout.SOUTH);
    this.wd = webcamModel.getDriver();

    JMenuBar menuBar = new JMenuBar();
    menuOptions = new JMenu("Options");
    menuFile = new JMenu("File");
    menuItemControls = new JMenuItem("Controls");
    menuItemSaveAs = new JMenuItem("Save As");
    menuItemSaveAs.setAccelerator(KeyStroke.getKeyStroke('S',
    	    Toolkit.getDefaultToolkit(  ).getMenuShortcutKeyMask(  ), false));
    
    menuOptions.add(menuItemControls);
    menuFile.add(menuItemSaveAs);
    
    addListeners();
    
    menuBar.add(menuFile);
    menuBar.add(menuOptions);
    
    setJMenuBar(menuBar);
    
    if (wd instanceof CameraDriverFirei)
    	cd = new ControlDialog((CameraDriverFirei)this.wd);
    
    webcamModel.startCapture(this);
	}
	
	public void showUI() {
		pack();
		setVisible(true);
	}
	
	public void setImage(BufferedImage bi) {
		ip.setImage(bi);
	}
	
	public void setStatus(String status) {
		sb.setMessage(status);
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		webcamModel.stopCapture();
		webcamModel.exit();
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		webcamModel.stopCapture();
		webcamModel.exit();
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}
	
	private void addListeners() {
    addWindowListener(this);
    ip.addKeyListener(this);
    ip.setFocusable(true);
	    
		menuItemControls.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(cd!=null)
					cd.showUI();
			}
		});
		
		// save dialog
		menuItemSaveAs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser fc = new JFileChooser();
				
				fc.setCurrentDirectory(new File(lastAccessedDir));
				
				int returnValue = fc.showSaveDialog(CameraView.this);
				
				if (returnValue == JFileChooser.APPROVE_OPTION) {
					File f = fc.getSelectedFile();
					lastAccessedDir = f.getParent();
					ip.saveImage(f);
				}
			}
		});
	}

	@Override
	public void keyPressed(KeyEvent ke) {
		switch(ke.getKeyChar()) {
		case 'c': //continuous recording
			webcamModel.continuousRecording(getSaveDir() + "/" +
          getImagePrefix(), getImageType());
			break;
		case 'i':
			//reset imageIndex
			//imageIndex is initialized to the input index
			String s = (String)JOptionPane.showInputDialog(
          this,
          "Reset image index to:\n",
          "Input",
          JOptionPane.PLAIN_MESSAGE,
          null,null,null);
			
			if (s != null && s.length() > 0) {
				int i = Integer.parseInt(s); 
				imageIndex = i;
			}
			break;
		case 'r':	
			//record the current image with incremental index as the image name
			String path = String.format("%s/%s%04d.%s", getSaveDir(), 
			                            getImagePrefix(), imageIndex, getImageType());
			//record the current image
			ip.saveImage(path);
			imageIndex++;
			break;
		case 's':
		  webcamModel.stopRecording();
		  break;
		case '8':
		  webcamModel.decreaseExposure();
		  break;
		case '9':
		  webcamModel.increaseExposure();
		  break;
		case '5':
		  webcamModel.decreaseSaturation();
		  break;
		case '6':
		  webcamModel.increaseSaturation();
		  break;
		default:
			break;
		}
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
	}

	public static void main(String[] args) {
	  CommandLineOptions.parse(args);
	  String cameraType = CameraView.getCameraType();
	  ICameraDriver driver = null;
	  if (cameraType.equals("emulator"))
	    driver = new CameraDriverEmulator(
	        CommandLineOptions.getOptionValue("record-dir", "./"));
	  else if (cameraType.equals("firefly"))
	    driver = new CameraDriverFirefly(false);
		CameraView wv = new CameraView("Webcam", new CameraModel(driver));
		wv.showUI();
	}
}
