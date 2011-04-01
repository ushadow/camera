package yingyin.webcam.gui;

import java.awt.Dimension;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import edu.mit.yingyin.camera.CameraDriverFirei;


public class ControlPanel extends JPanel implements ChangeListener, 
                                                    ItemListener {

	private static final long serialVersionUID = 1L;
	private JSlider slider;
	private CameraDriverFirei td;
	private CameraDriverFirei.CameraControl control;
	private JTextField tf;
	private JCheckBox cb;

	/**
	 * Create a control panel for controlling one of the webcam properties
	 * 
	 * @param _control the name of the control property
	 * @param _td webcam driver which has to be initialized before it is passed as 
	 * a parameter
	 */
	public ControlPanel(CameraDriverFirei.CameraControl _control, 
	                    CameraDriverFirei _td) {
		super();
		setBorder(BorderFactory.createEmptyBorder(2,2,2,2));
		setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
		
		td = _td;
		control = _control;
		JLabel lControl = new JLabel(_control.toString());
		lControl.setHorizontalAlignment(SwingConstants.LEFT);
		lControl.setPreferredSize(new Dimension(100, 25));
		
		
		Vector<Integer> vi = td.queryProperty(_control);
		JLabel lMin = new JLabel((vi.get(0)).toString());
		lMin.setPreferredSize(new Dimension(25, 25));
		lMin.setHorizontalAlignment(SwingConstants.RIGHT);
		
		JLabel lMax = new JLabel((vi.get(1)).toString());
		lMax.setPreferredSize(new Dimension(25, 25));
		lMax.setHorizontalAlignment(SwingConstants.LEFT);
		
		Vector<Integer> property = td.getCurrentProperty(_control);
		slider = new JSlider(JSlider.HORIZONTAL, vi.get(0), vi.get(1), 
		                     property.get(0));
		tf = new JTextField(property.get(0).toString());
		
		cb = new JCheckBox();
		if (property.get(1)==1) {
			cb.setSelected(true);
			slider.setEnabled(false);
		}
		
		tf.setEditable(false);
		
		slider.addChangeListener(this);
		cb.addItemListener(this);

		add(lControl);
		add(lMin);
		add(slider);
		add(lMax);
		add(tf);
		add(cb);
	}

	@Override
	/**
	 * Actions when the state of the slide bar changes
	 */
	public void stateChanged(ChangeEvent e) {
		JSlider source = (JSlider)e.getSource();
		Integer value = (int)source.getValue();
		td.setProperty(control, value);
		tf.setText(value.toString());
	}

	@Override
	public void itemStateChanged(ItemEvent e) {
		JCheckBox source = (JCheckBox)e.getSource();
		if (source.isSelected()) {
			slider.setEnabled(false);
			td.setAutoProperty(control);
		}
		else slider.setEnabled(true);
	}
}
