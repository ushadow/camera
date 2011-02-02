#include "yingyin_webcam_WebcamDriverFirefly.h"
#include "firefly_driver.h"

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirefly_initialize
    (JNIEnv *env, jobject obj, jobject cb, jint cameraIndex, jint frameRate) {
	FireflyDriver** fireflyDriver = (FireflyDriver**)env->GetDirectBufferAddress(cb);
  *fireflyDriver = new FireflyDriver();
  (*fireflyDriver)->initialize(cameraIndex, frameRate);
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirefly_captureNow
    (JNIEnv *env, jobject obj, jobject cb, jobject image, jint width, jint height) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->capturenow((unsigned char*) env->GetDirectBufferAddress(image), width, height);
}


JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirefly_cleanUp
    (JNIEnv *env, jobject obj, jobject cb) {
  FireflyDriver* fireflyDriver = *((FireflyDriver**) env->GetDirectBufferAddress(cb));
  fireflyDriver->cleanup();
}