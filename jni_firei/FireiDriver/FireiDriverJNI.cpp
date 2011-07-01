#include "yingyin_webcam_WebcamDriverFirei.h"
#include "FireiDriver.h"

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_initialize
  (JNIEnv *env, jobject obj, jobject cb, jint cameraIndex) {
	FireiDriver** fireiDriver = (FireiDriver**)env->GetDirectBufferAddress(cb);
	*fireiDriver = new FireiDriver();
	(*fireiDriver)->initialize(cameraIndex);
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_captureNowNative
  (JNIEnv *env, jobject obj, jobject cb, jobject image, jint width, jint height) {
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	fireiDriver->capturenow((unsigned char*)env->GetDirectBufferAddress(image), width, height);
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_cleanUp
  (JNIEnv *env, jobject obj, jobject cb) {
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	fireiDriver->cleanup();
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_setPropertyNative
  (JNIEnv *env, jobject obj, jobject cb, jint prop, jint value) {
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	fireiDriver->setProperty(prop, value);
}

JNIEXPORT jint JNICALL Java_yingyin_webcam_WebcamDriverFirei_getCurrentPropertyNative
  (JNIEnv *env, jobject obj, jobject cb, jint prop, jobject value, jobject isAuto)
{
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	return fireiDriver->getCurrentProperty(prop, (int*)env->GetDirectBufferAddress(value),
		(int*)env->GetDirectBufferAddress(isAuto));
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_qeuryPropertyNative
  (JNIEnv *env, jobject obj, jobject cb, jint prop, jobject a_min, jobject a_max)
{
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	fireiDriver->queryProperty(prop, (int*)env->GetDirectBufferAddress(a_min),
		(int*)env->GetDirectBufferAddress(a_max));
}

JNIEXPORT void JNICALL Java_yingyin_webcam_WebcamDriverFirei_setAutoPropertyNative
  (JNIEnv *env, jobject obj, jobject cb, jint prop)
{
	FireiDriver* fireiDriver = *((FireiDriver**)env->GetDirectBufferAddress(cb));
	fireiDriver->setAutoProtpery(prop);
}