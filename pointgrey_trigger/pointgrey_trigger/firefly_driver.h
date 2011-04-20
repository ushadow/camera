// A wrapper around Point Grey Research's FlyCapture2.1 API for
// capturing images through external triggering.
// If user_trigger is true, the camera starts with the external trigger mode 0. 
// The exposed controls of the camera are: shutter, and saturation.
#ifndef _H_FIREFLY_DRIVER_
#define _H_FIREFLY_DRIVER_

#include <string>
#include <vector>

#include "FlyCapture2.h"

class FireflyDriver {
public:
  static void ListCameras(std::vector<std::string>& drivers);
  
  FireflyDriver() {};
  // Initializes the camera at the given index, with given frame_rate.
  // Turns triggering mode on if use_trigger is true.
  void InitializeCamera(int index, int frame_rate, bool use_trigger);
  void Cleanup();
  void CaptureNow(unsigned char* pimageBGRA32, int width, int height);
  void IncreaseShutter();
  void DecreaseShutter();
  void IncreaseSaturation();
  void DecreaseSaturation();

private:
  static const int kMaxCams = 5;
  static const int kPropertyIncrement = 4;
  static void PrintError(FlyCapture2::Error error);

  FlyCapture2::Camera camera_;
  FlyCapture2::TriggerMode trigger_mode_;

  bool CheckTriggerReady();
  void MaximizeGain();
  void PrintCameraInfo(FlyCapture2::CameraInfo* pCamInfo);
  bool FireSoftwareTrigger();
  bool CheckSoftwareTriggerPresence();
  void ChangeCameraProperty(FlyCapture2::PropertyType type, int direction);
};

#endif


