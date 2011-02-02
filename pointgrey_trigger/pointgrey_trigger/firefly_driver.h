#ifndef _H_FIREFLY_DRIVER_
#define _H_FIREFLY_DRIVER_

#include "pgrflycapture.h"

class FireflyDriver
{
public:
  FireflyDriver() {};
  
  void initialize(int cameraIndex, int frameRate);
  void cleanup();
  void capturenow(unsigned char* pimageBGRA32, int width, int height);

private:
  static const int _MAX_CAMS = 2;
  FlyCaptureContext	_context;
  FlyCaptureError checkTriggerReady();
};

#endif


