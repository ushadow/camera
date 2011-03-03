#include <stdio.h>
#include <stdlib.h>

#include "firefly_driver.h"
#include "pgrflycapture.h"

// Register definitions.
#define INITIALIZE         0x000
#define TRIGGER_INQ        0x530
#define CAMERA_POWER       0x610
#define SOFTWARE_TRIGGER   0x62C
#define SOFT_ASYNC_TRIGGER 0x102C

void FireflyDriver::Initialize(int cameraIndex, int frameRate) {
  // Enumerate the cameras on the bus.
  FlyCaptureInfoEx  arInfo[kMaxCams];
  unsigned int  uiSize = kMaxCams;

  FlyCaptureError error;

  error = flycaptureBusEnumerateCamerasEx(arInfo, &uiSize);
  HandleError("flycaptureBusEnumerateCameras()", error);

  for (unsigned int uiBusIndex = 0; uiBusIndex < uiSize; uiBusIndex++) {
    FlyCaptureInfoEx* pinfo = &arInfo[uiBusIndex];
    printf( 
      "Index %u: %s (%u)\n",
      uiBusIndex,
      pinfo->pszModelName,
      pinfo->SerialNumber);
  }
  
  // Create the context.
  error = flycaptureCreateContext(&context_);
  HandleError("flycaptureCreateContext()", error);

	// Initialize the camera.
  printf("Initializing camera %u.\n", cameraIndex);
  error = flycaptureInitialize(context_, cameraIndex);
  HandleError("flycaptureInitialize()", error);

  // Determine whether or not the camera supports external trigger mode.
  // If it does, put the camera into external trigger mode and otherwise 
  // exit.
  bool bTriggerPresent;

  error = flycaptureQueryTrigger( 
    context_, &bTriggerPresent, NULL, NULL, NULL, NULL, NULL, NULL, NULL );
  HandleError("flycaptureQueryTrigger()", error);

  if (!bTriggerPresent) {
    printf("This camera does not support external trigger... exiting\n");
    return;
  }

  int iPolarity;
  int iSource;
  int iRawValue;
  int iMode;

  error = flycaptureGetTrigger( 
    context_, NULL, &iPolarity, &iSource, &iRawValue, &iMode, NULL );
  HandleError( "flycaptureGetTrigger()", error );

  printf( "Going into asynchronous Trigger_Mode_0.\n" );

  // Ensure the camera is in Trigger Mode 0 by explicitly setting it, 
  // as the camera could have a different default trigger mode.
  // We are triggering the camera using an external hardware trigger.
  error = flycaptureSetTrigger( 
    context_, true, iPolarity, iSource, 0, 0 );
  HandleError("flycaptureSetCameraTrigger()", error);

  // Poll the camera to make sure the camera is actually in trigger mode
  // before we start it (avoids timeouts due to the trigger not being armed)
  CheckTriggerReady();

  // Start the camera and grab any excess images that are already in the pipe.
  // Although it is extremely rare for spurious images to occur, it is
  // possible for the grab call to return an image that is not a result of a
  // user-generated trigger. To grab excess images, set a zero-length timeout.
  // A value of zero makes the grab call non-blocking.
  printf( "Checking for any buffered images..." );
  error = flycaptureSetGrabTimeoutEx(context_, 0);
  HandleError("flycaptureSetGrabTimeoutEx()", error);
    
  error = flycaptureStart(
    context_, FLYCAPTURE_VIDEOMODE_ANY, FLYCAPTURE_FRAMERATE_ANY);
  HandleError("flycaptureStart()", error);

  // Grab the image immediately whether or not trigger present
  FlyCaptureImage  image;
  error = flycaptureGrabImage2(context_, &image);
  if( error == FLYCAPTURE_OK ) {
    printf( "buffered image found. Flush successful.\n" );
  } else if( error == FLYCAPTURE_TIMEOUT ) {
    printf( "no flush required! (normal behaviour)\n" );
  } else {
    HandleError( "flycaptureGrabImage2()", error );
  }

  error = flycaptureStop(context_);
  HandleError("flycaptureStop()", error);

  // Start camera.  This is done after setting the trigger so that
  // excess images isochronously streamed from the camera don't fill up 
  // the internal buffers.
  FlyCaptureFrameRate rate;
  switch (frameRate) {
    case 60:
      rate = FLYCAPTURE_FRAMERATE_60;
      break;
    case 30:
    default:
      rate = FLYCAPTURE_FRAMERATE_30;
      break;
  }
  error = flycaptureStart( 
    context_, FLYCAPTURE_VIDEOMODE_640x480Y8, FLYCAPTURE_FRAMERATE_30);
  HandleError("flycaptureStart()", error);
  printf( "Camera started.\n" );

  // Set the grab timeout to be infinite so that calls to flycaptureGrabImage2 will never return 
  // until the next trigger.
  error = flycaptureSetGrabTimeoutEx(context_, FLYCAPTURE_INFINITE);
  HandleError("flycaptureSetGrabTimeoutEx()", error);
  fflush(stdout);
}

void FireflyDriver::CaptureNow(unsigned char *pimageBGRU32, int width, int height) {
  FlyCaptureImage image;
  FlyCaptureError error;
	// Initialize the image structure to sane values
	image.iCols = 0;
	image.iRows = 0;

	error = flycaptureGrabImage2(context_, &image);
  HandleError("flycaptureGrabImage2()", error);

	// Convert the last image to BGRU32.
	FlyCaptureImage imageConverted;
  imageConverted.pData = pimageBGRU32;
  imageConverted.pixelFormat = FLYCAPTURE_BGRU;

  //printf( "Converting last image.\n" );
  error = flycaptureConvertImage(context_, &image, &imageConverted);
  HandleError("flycaptureConvertImage()", error);

  int index = 3;
  for (int h = 0; h < height; h++)
    for (int w = 0; w < width; w++) {
      *(pimageBGRU32 + index) = 0xff;
      index += 4;
    }

	fflush(stdout);
}

void FireflyDriver::Cleanup() {
  FlyCaptureError error;
  error = flycaptureStop(context_);
  HandleError("flycaptureStop()", error);
	error = flycaptureDestroyContext(context_);
	HandleError("flycaptureBusEnumerateCameras()", error);

	printf("Done!");
	fflush(stdout);
}


FlyCaptureError FireflyDriver::CheckTriggerReady() {
  FlyCaptureError  error;
  unsigned long  ulValue;

  // Do our check to make sure the camera is ready to be triggered
  // by looking at bits 30-31. Any value other than 1 indicates
  // the camera is not ready to be triggered.
  error = flycaptureGetCameraRegister(context_, SOFT_ASYNC_TRIGGER, &ulValue);
  HandleError("flycaptureGetCameraRegister()", error);

  while( ulValue != 0x80000001 ) {
    error = flycaptureGetCameraRegister(context_, SOFT_ASYNC_TRIGGER, &ulValue);
    HandleError( "flycaptureGetCameraRegister()", error );
  }
  return FLYCAPTURE_OK;
}

