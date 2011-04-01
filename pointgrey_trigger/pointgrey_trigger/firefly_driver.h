// A wrapper around Point Grey Research's FlyCapture API (v1.0.0.13) for
// capturing images through external triggering.
// The camera starts with the external trigger mode 0. The other controls of the camera
// is not exposed yet.
#ifndef _H_FIREFLY_DRIVER_
#define _H_FIREFLY_DRIVER_

#include <string>
#include <vector>

#include "pgrflycapture.h"

class FireflyDriver {
public:
  FireflyDriver() {};
  
  void InitializeCamera(int cameraIndex, int frameRate, bool useTrigger);

  void Cleanup();
  void CaptureNow(unsigned char* pimageBGRA32, int width, int height);

  static void listCameras(std::vector<std::string>& drivers);

  void increaseExposure();
  void decreaseExposure();

private:
  void maximizeGain();

  static const int kMaxCams = 5;
  static const int kShutterIncrement = 4;

  FlyCaptureContext	context_;
  FlyCaptureError CheckTriggerReady();
};

// Helper code to handle a FlyCapture error.
inline void HandleError(std::string function, FlyCaptureError error) {
	if (error != FLYCAPTURE_OK) { 
   printf( "%s: %s\n", function, flycaptureErrorToString(error)); 
   exit(1); 
  }
}

#endif


