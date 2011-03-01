package yingyin.webcam.gui;

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

import edu.mit.yingyin.gui.StatusBar;

import yingyin.common.EnvConstants;
import yingyin.webcam.IWebcamDriver;
import yingyin.webcam.WebcamDriverFirefly;
import yingyin.webcam.WebcamModel;
import yingyin.webcam.WebcamDriverFirei;

/**
 * Main frame for display webcam images. Allows saving of the image.
 * @author Ying
 * 
 */
public class WebcamView extends JFrame implements WindowListener, KeyListener {

	private static final long serialVersionUID = 1L;
	protected ImagePanel ip;
	protected IWebcamDriver wd;
	protected WebcamModel webcamModel = null;
	
	/*menu*/
	private JMenu menuOptions;
	private JMenu menuFile;
	private JMenuItem menuItemControls;
	private JMenuItem  menuItemSaveAs;
	
	protected ControlDialog cd= null;
	protected StatusBar sb = null;
	
	private int imageIndex = 1;
	private String lastAccessedDir = EnvConstants.MAIN_FOLDER;

	/**
	 * Create an instance of main frame for displaying image frame captured from 
	 * webcam
	 * @param title title of the main frame
	 * @param _wdf	webcam driver for Firei cambera, it has to be initialized 
	 * before passed as a parameter
	 */
	public WebcamView(String title, WebcamModel webcamModel){
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
    
    if (wd instanceof WebcamDriverFirei)
    	cd = new ControlDialog((WebcamDriverFirei)this.wd);
    
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
				
				int returnValue = fc.showSaveDialog(WebcamView.this);
				
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
			String saveDir = (String)JOptionPane.showInputDialog(
          this,
          "Please input the name of the folder to save in\n"
          + EnvConstants.LOCAL_FOLDER + "\n",
          "Input Dialog",
          JOptionPane.PLAIN_MESSAGE,
          null,
          null,
          "recording");
			
			//folder name should not end with "/"
			if (saveDir!=null && saveDir.length()>0) {
				saveDir = EnvConstants.LOCAL_FOLDER + saveDir;
				webcamModel.continuousRecording(saveDir);
			}
			else
				JOptionPane.showMessageDialog(this, "Invalid folder name!", "Error", 
				                              JOptionPane.ERROR_MESSAGE);
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
			
			if (s!=null && s.length() > 0) {
				int i = Integer.parseInt(s); 
				imageIndex = i;
			}
			break;
			
		case 'r':	
			//record the current image with incremental index as the image name
	
			String path = WebcamModel.CAM_REC_DIR + "image" + imageIndex + 
			    EnvConstants.IMAGE_TYPE;
			//record the current image
			ip.saveImage(path);
			imageIndex++;
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
		IWebcamDriver driver = new WebcamDriverFirefly();
		WebcamView wv = new WebcamView("Webcam", new WebcamModel(driver));
		wv.showUI();
	}
}
