package yingyin.common;

public class EnvConstants {

	public static final String MAIN_FOLDER = "G:/data/HandTracking/YingColorCalibration/";
	public static final String LOCAL_FOLDER = "C:/Documents and Settings/yingyin/Desktop/";
	
	public static final String IMAGE_NAME = "/image1"; //image used for calibration
	public static final String IMAGE_TYPE = ".png";
	public static final String CHALLENGE_SUFFIX = ".colorchallenge";
	
	public static final String CAMERA_CALIB_FOLDER = MAIN_FOLDER + "CameraCalib/01_15/";
	
	/**
	 * Directory containing the calibration data. Note this path does not end with '/'
	 */
	public static final String CALIB_DATA_DIR = "data/HandTracking/Polarize_LF/calib_data";
	public static final String CALIB_IMAGE_PREFIX = CALIB_DATA_DIR + "/image";
	public static final String TARGET_IMAGE_PATH = CALIB_DATA_DIR + IMAGE_NAME + IMAGE_TYPE;
	public static final String TARGET_DATA_PATH = CALIB_DATA_DIR + IMAGE_NAME + CHALLENGE_SUFFIX;
	public static final String TARGET_POINTS_PATH = CALIB_DATA_DIR + IMAGE_NAME + ".pts";
	public static final String CORRESPONDENCE_PATH = CALIB_DATA_DIR + "/correspondence.txt";
	public static final String TRANSFORMED_PATH = CALIB_DATA_DIR + "/transformed.txt";
	public static final String TRANFORM_MATRIX_PATH = CALIB_DATA_DIR + "/transform.matrix";
	
	public static final String RECORDING_DIR = LOCAL_FOLDER + "recording/";
}
