#include "firefly_driver_jni.h"
#include "firefly_driver.h"

JNIEXPORT void JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_initialize
    (JNIEnv *env, jobject obj, jobject cb, jint cameraIndex, jint frameRate, jboolean useTrigger) {
	FireflyDriver** fireflyDriver = (FireflyDriver**)env->GetDirectBufferAddress(cb);
  *fireflyDriver = new FireflyDriver();
  (*fireflyDriver)->InitializeCamera(cameraIndex, frameRate, useTrigger == JNI_TRUE);
}

JNIEXPORT void JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_captureNow
    (JNIEnv *env, jobject obj, jobject cb, jobject image, jint width, jint height) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->CaptureNow((unsigned char*) env->GetDirectBufferAddress(image), width, height);
}


JNIEXPORT void JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_cleanUp
    (JNIEnv *env, jobject obj, jobject cb) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->Cleanup();
}

JNIEXPORT jobjectArray JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_getDeviceNames
(JNIEnv *env, jclass obj) {
  std::vector<std::string> devices;
  FireflyDriver::listCameras(devices);
  int numDevices = (int) devices.size();

  jstring str = NULL;
  jclass strCls = env->FindClass("Ljava/lang/String;");
  jobjectArray strarray = env->NewObjectArray(numDevices,strCls,NULL);
  for (int i=0; i<numDevices; i++) {
    str = env->NewStringUTF(devices[i].c_str());
    env->SetObjectArrayElement(strarray,i,str);
    env->DeleteLocalRef(str);
  }
  return strarray;
}

JNIEXPORT void JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_increaseExposure
(JNIEnv *env, jobject obj, jobject cb) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->increaseExposure();
}

/*
 * Class:     edu_mit_yingyin_camera_CameraDriverFirefly
 * Method:    decreaseExposure
 * Signature: (Ljava/nio/IntBuffer;)V
 */
JNIEXPORT void JNICALL Java_edu_mit_yingyin_camera_CameraDriverFirefly_decreaseExposure
(JNIEnv *env, jobject obj, jobject cb) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->decreaseExposure();
}