#include <stdio.h>
#include <stdlib.h>

#include "firefly_driver.h"
#include "FlyCapture2.h"

/**
 * This is a wrapper around Point Grey Research's FlyCapture2 API. 
 * 
 * To compile, you need to specify additional include and lib directories:
 * Point Grey Research\FlyCapture2\include and Point Grey Research\FlyCapture2\lib.
 */

void FireflyDriver::InitializeCamera(int cameraIndex, int frame_rate, 
                                     bool user_trigger) {
  using FlyCapture2::PGRERROR_OK;
  // Enumerate the cameras on the bus.
  FlyCapture2::Error error;

  FlyCapture2::BusManager busMgr;
  unsigned int numCameras;
  error = busMgr.GetNumOfCameras(&numCameras);
  if (error != PGRERROR_OK) {
    PrintError( error );
    exit(-1);
  }

  printf("Number of cameras detected: %u\n", numCameras);

  if ((int)numCameras < cameraIndex + 1) {
    printf("Insufficient number of cameras... exiting\n");
    exit(-1);
  }
  
  FlyCapture2::PGRGuid guid;
  error = busMgr.GetCameraFromIndex(cameraIndex, &guid);
  if (error != PGRERROR_OK) {
    PrintError(error);
    exit(-1);
  }

  // Connect to a camera
  error = camera_.Connect(&guid);
  if (error != PGRERROR_OK) {
    PrintError(error);
    exit(-1);
  }
  
  // Get the camera information
  FlyCapture2::CameraInfo camInfo;
  error = camera_.GetCameraInfo(&camInfo);
  if (error != PGRERROR_OK) {
    PrintError(error);
    exit(-1);
  }

  PrintCameraInfo(&camInfo);  

  FlyCapture2::FrameRate rate;
  switch (frame_rate) {
    case 30:
      rate = FlyCapture2::FRAMERATE_30;
      break;
    case 60:
      rate = FlyCapture2::FRAMERATE_60;
      break;
    default:
      rate = FlyCapture2::FRAMERATE_30;
      break;
  }
  
  camera_.SetVideoModeAndFrameRate(FlyCapture2::VIDEOMODE_640x480Y8, rate); 
  
  // Get current trigger settings
  error = camera_.GetTriggerMode(&trigger_mode_);
  if (error != PGRERROR_OK) {
      PrintError( error );
      exit(-1);
  }
  if (user_trigger) {
#ifndef SOFTWARE_TRIGGER_CAMERA
    // Determine whether or not the camera supports external trigger mode.
    // If it does, put the camera into external trigger mode and otherwise 
    // exit.
    FlyCapture2::TriggerModeInfo trigger_mode_info;
    error = camera_.GetTriggerModeInfo(&trigger_mode_info);
    if (error != PGRERROR_OK){
      PrintError( error );
      exit(-1);
    }

    if (trigger_mode_info.present != true) {
      printf("Camera does not support external trigger! Exiting...\n");
      exit(-1);
    }
#endif
    // Set camera to trigger mode 0
    trigger_mode_.onOff = true;
    trigger_mode_.mode = 0;
    trigger_mode_.parameter = 0;

#ifdef SOFTWARE_TRIGGER_CAMERA
    // A source of 7 means software trigger
    trigger_mode_.source = 7;
#else
    // Triggering the camera externally using source 0.
    trigger_mode_.source = 0;
#endif

    error = camera_.SetTriggerMode(&trigger_mode_);
    if (error != PGRERROR_OK) {
      PrintError( error );
      exit(-1);
    }
    printf( "Going into asynchronous Trigger_Mode_0.\n" );
    
    // Poll the camera to make sure the camera is actually in trigger mode
    // before we start it (avoids timeouts due to the trigger not being armed)
    bool retVal = CheckTriggerReady();
    if (!retVal) {
      printf("\nError polling for trigger ready!\n");
		  exit(-1);
	  }

    // Get the camera configuration
    FlyCapture2::FC2Config config;
    error = camera_.GetConfiguration(&config);
    if (error != PGRERROR_OK) {
      PrintError( error );
      exit(-1);
    } 
    
    config.grabTimeout = FlyCapture2::TIMEOUT_INFINITE;

    // Set the camera configuration
    error = camera_.SetConfiguration(&config);
    if (error != PGRERROR_OK) {
      PrintError( error );
      exit(-1);
    }
#ifdef SOFTWARE_TRIGGER_CAMERA
	if (!CheckSoftwareTriggerPresence()) {
		printf( "SOFT_ASYNC_TRIGGER not implemented on this camera!  Stopping application\n");
		return -1;
	}
#else	
	printf( "Trigger the camera by sending a trigger pulse to GPIO%d.\n", 
      trigger_mode_.source );
#endif
  }

  // Camera is ready, start capturing images
  error = camera_.StartCapture();
  if (error != PGRERROR_OK) {
    PrintError( error );
    exit(-1);
  }   
}

bool FireflyDriver::FireSoftwareTrigger() {
  const unsigned int k_softwareTrigger = 0x62C;
  const unsigned int k_fireVal = 0x80000000;
  FlyCapture2::Error error;    

  error = camera_.WriteRegister(k_softwareTrigger, k_fireVal);
  if (error != FlyCapture2::PGRERROR_OK) {
    PrintError( error );
    return false;
  }

  return true;
}

void FireflyDriver::CaptureNow(unsigned char *pimageBGRU32, int width, int height) {
  using FlyCapture2::PGRERROR_OK;
  FlyCapture2::Error error;
  FlyCapture2::Image image, converted_image;

#ifdef SOFTWARE_TRIGGER_CAMERA
	// Check that the trigger is ready
	CheckTriggerReady();

  // Fire software trigger
  bool retVal = FireSoftwareTrigger();
  if (!retVal) {
    printf("\nError firing software trigger!\n");
    exit(-1);        
	}
#endif

  // Grab image        
	error = camera_.RetrieveBuffer(&image);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return;
  }
  
  converted_image.SetData(pimageBGRU32, width * height * 4);
  error = image.Convert(FlyCapture2::PIXEL_FORMAT_BGRU, &converted_image);
  
  int index = 3;
  for (int h = 0; h < height; h++)
    for (int w = 0; w < width; w++) {
      *(pimageBGRU32 + index) = 0xff;
      index += 4;
    }

	fflush(stdout);
}

void FireflyDriver::Cleanup() {
  using FlyCapture2::PGRERROR_OK;
  FlyCapture2::Error error;
  // Turn trigger mode off.
  trigger_mode_.onOff = false;    
  error = camera_.SetTriggerMode(&trigger_mode_);
  if (error != PGRERROR_OK) {
    PrintError(error);
    exit(-1);
  }

  // Stop capturing images
  error = camera_.StopCapture();
  if (error != PGRERROR_OK) {
    PrintError( error );
    exit(-1);
  }      

  // Disconnect the camera
  error = camera_.Disconnect();
  if (error != PGRERROR_OK) {
    PrintError( error );
    exit(-1);
  }
}

bool FireflyDriver::CheckTriggerReady() {
  using FlyCapture2::PGRERROR_OK;
  const unsigned int k_softwareTrigger = 0x62C;
  FlyCapture2::Error error;
  unsigned int regVal = 0;

  do {
    error = camera_.ReadRegister(k_softwareTrigger, &regVal);
    if (error != PGRERROR_OK) {
      PrintError( error );
		  return false;
    }
  } while ((regVal >> 31) != 0);

	return true;
}

// static
void FireflyDriver::ListCameras(std::vector<std::string>& drivers) {
  using FlyCapture2::PGRERROR_OK;
  FlyCapture2::Error error;
  FlyCapture2::PGRGuid guid;
  FlyCapture2::Camera camera;
  FlyCapture2::BusManager busMgr;
  FlyCapture2::CameraInfo camInfo;
  unsigned int numCameras;
  error = busMgr.GetNumOfCameras(&numCameras);
  if (error != PGRERROR_OK) {
    PrintError( error );
    exit(-1);
  }

  for (unsigned int uiBusIndex = 0; uiBusIndex < numCameras; uiBusIndex++) {
    error = busMgr.GetCameraFromIndex(uiBusIndex, &guid);
    if (error != PGRERROR_OK) {
      PrintError(error);
      exit(-1);
    }
    // Connect to a camera
    error = camera.Connect(&guid);
    if (error != PGRERROR_OK) {
      PrintError(error);
      exit(-1);
    }
    
    // Get the camera information
    error = camera.GetCameraInfo(&camInfo);
    if (error != PGRERROR_OK) {
      PrintError(error);
      exit(-1);
    }
    drivers.push_back(camInfo.modelName);
  }
}

void FireflyDriver::MaximizeGain() {
  // set the gain to max
  FlyCapture2::PropertyInfo info;
  FlyCapture2::Property camera_property;
  info.type = FlyCapture2::GAIN;
  camera_property.type = FlyCapture2::GAIN;
  camera_.GetPropertyInfo(&info);
  camera_.GetProperty(&camera_property);
  camera_property.valueA = camera_property.valueB = info.max;
  camera_property.absControl = false;
  camera_property.autoManualMode = false;
  
  camera_.SetProperty(&camera_property);

}

void FireflyDriver::IncreaseShutter() {
  MaximizeGain();
  ChangeCameraProperty(FlyCapture2::SHUTTER, 1);
}

void FireflyDriver::DecreaseShutter() {
  MaximizeGain();
  ChangeCameraProperty(FlyCapture2::SHUTTER, -1);
}

void FireflyDriver::IncreaseSaturation() {
  ChangeCameraProperty(FlyCapture2::SATURATION, 1);
}

void FireflyDriver::DecreaseSaturation() {
  ChangeCameraProperty(FlyCapture2::SATURATION, -1);
}

void FireflyDriver::ChangeCameraProperty(FlyCapture2::PropertyType type, int direction) {
  FlyCapture2::PropertyInfo info;
  FlyCapture2::Property camera_property;
  info.type = type;
  camera_property.type = type;
  camera_.GetPropertyInfo(&info);
  if (!info.present) {
    printf("%d control is not supported.\n", type);
    return;
  }
  camera_.GetProperty(&camera_property);
  unsigned long new_value = camera_property.valueA + kPropertyIncrement * direction;
  new_value = (new_value < info.max) ? new_value : info.max;
  new_value = (new_value > info.min) ? new_value : info.min;
  camera_property.valueA = camera_property.valueB = new_value;
  camera_property.absControl = false;
  camera_property.autoManualMode = false;
  
  camera_.SetProperty(&camera_property);
  printf("Set %d to: %d in range %d %d\n", type, new_value, info.min, info.max);

  fflush(stdout);
}

bool FireflyDriver::CheckSoftwareTriggerPresence() {
  using FlyCapture2::PGRERROR_OK;
  const unsigned int k_triggerInq = 0x530;

	FlyCapture2::Error error;
	unsigned int regVal = 0;

	error = camera_.ReadRegister(k_triggerInq, &regVal);

	if (error != PGRERROR_OK) {
		PrintError( error );
		return false;
	}

	if(( regVal & 0x10000 ) != 0x10000) {
		return false;
	}
	return true;
}

// Helper code to handle a FlyCapture error.
void FireflyDriver::PrintError(FlyCapture2::Error error) {
	error.PrintErrorTrace();
}

void FireflyDriver::PrintCameraInfo(FlyCapture2::CameraInfo* pCamInfo) {
  printf(
      "\n*** CAMERA INFORMATION ***\n"
      "Serial number - %u\n"
      "Camera model - %s\n"
      "Camera vendor - %s\n"
      "Sensor - %s\n"
      "Resolution - %s\n"
      "Firmware version - %s\n"
      "Firmware build time - %s\n\n",
      pCamInfo->serialNumber,
      pCamInfo->modelName,
      pCamInfo->vendorName,
      pCamInfo->sensorInfo,
      pCamInfo->sensorResolution,
      pCamInfo->firmwareVersion,
      pCamInfo->firmwareBuildTime);
}