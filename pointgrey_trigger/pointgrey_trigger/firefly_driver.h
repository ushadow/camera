// A wrapper around Point Grey Research's FlyCapture API (v1.0.0.13) for
// capturing images through external triggering.
#ifndef _H_FIREFLY_DRIVER_
#define _H_FIREFLY_DRIVER_

#include <string>
#include "pgrflycapture.h"

using namespace std;

class FireflyDriver {
public:
  FireflyDriver() {};
  
  void Initialize(int cameraIndex, int frameRate);
  void Cleanup();
  void CaptureNow(unsigned char* pimageBGRA32, int width, int height);

private:
  static const int kMaxCams = 1;
  FlyCaptureContext	context_;
  FlyCaptureError CheckTriggerReady();
};

// Helper code to handle a FlyCapture error.
inline void HandleError(string function, FlyCaptureError error) {
	if (error != FLYCAPTURE_OK) { 
   printf( "%s: %s\n", function, flycaptureErrorToString(error)); 
   exit(1); 
  }
}

#endif


