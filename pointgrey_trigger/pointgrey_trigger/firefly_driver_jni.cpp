#include "firefly_driver_jni.h"
#include "firefly_driver.h"

JNIEXPORT void JNICALL Java_edu_mit_yingyin_webcam_WebcamDriverFirefly_initialize
    (JNIEnv *env, jobject obj, jobject cb, jint cameraIndex, jint frameRate) {
	FireflyDriver** fireflyDriver = (FireflyDriver**)env->GetDirectBufferAddress(cb);
  *fireflyDriver = new FireflyDriver();
  (*fireflyDriver)->Initialize(cameraIndex, frameRate);
}

JNIEXPORT void JNICALL Java_edu_mit_yingyin_webcam_WebcamDriverFirefly_captureNow
    (JNIEnv *env, jobject obj, jobject cb, jobject image, jint width, jint height) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->CaptureNow((unsigned char*) env->GetDirectBufferAddress(image), width, height);
}


JNIEXPORT void JNICALL Java_edu_mit_yingyin_webcam_WebcamDriverFirefly_cleanUp
    (JNIEnv *env, jobject obj, jobject cb) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->Cleanup();
}