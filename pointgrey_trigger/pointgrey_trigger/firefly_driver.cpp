#include <stdio.h>
#include <stdlib.h>

#include "firefly_driver.h"
#include "pgrflycapture.h"

// Register defines
#define INITIALIZE         0x000
#define TRIGGER_INQ        0x530
#define CAMERA_POWER       0x610
#define SOFTWARE_TRIGGER   0x62C
#define SOFT_ASYNC_TRIGGER 0x102C

// Helper code to handle a FlyCapture error.
#define HANDLE_ERROR(function, error) \
	if( error != FLYCAPTURE_OK ) { \
   printf( "%s: %s\n", function, flycaptureErrorToString(error)); \
   ::exit(1); \
   } \

void FireflyDriver::initialize(int cameraIndex, int frameRate) {
  // Enumerate the cameras on the bus.
  FlyCaptureInfoEx  arInfo[_MAX_CAMS];
  unsigned int  uiSize = _MAX_CAMS;

  FlyCaptureError error;

  error = flycaptureBusEnumerateCamerasEx(arInfo, &uiSize);
  HANDLE_ERROR("flycaptureBusEnumerateCameras()", error);

  for (unsigned int uiBusIndex = 0; uiBusIndex < uiSize; uiBusIndex++) {
     FlyCaptureInfoEx* pinfo = &arInfo[uiBusIndex];
     printf( 
        "Index %u: %s (%u)\n",
        uiBusIndex,
        pinfo->pszModelName,
        pinfo->SerialNumber);
  }
  
  // Create the context.
  error = flycaptureCreateContext(&_context);
  HANDLE_ERROR("flycaptureCreateContext()", error);

	// Initialize the camera.
  printf("Initializing camera %u.\n", cameraIndex);
  error = flycaptureInitialize(_context, cameraIndex);
  HANDLE_ERROR("flycaptureInitialize()", error);

  // Determine whether or not the camera supports external trigger mode.
  // If it does, put the camera into external trigger mode and otherwise 
  // exit.
  bool bTriggerPresent;

  error = flycaptureQueryTrigger( 
    _context, &bTriggerPresent, NULL, NULL, NULL, NULL, NULL, NULL, NULL );
  HANDLE_ERROR("flycaptureQueryTrigger()", error);

  if (!bTriggerPresent) {
    printf("This camera does not support external trigger... exiting\n");
    return;
  }

  int iPolarity;
  int iSource;
  int iRawValue;
  int iMode;

  error = flycaptureGetTrigger( 
    _context, NULL, &iPolarity, &iSource, &iRawValue, &iMode, NULL );
  HANDLE_ERROR( "flycaptureGetTrigger()", error );

  printf( "Going into asynchronous Trigger_Mode_0.\n" );
  //
  // Ensure the camera is in Trigger Mode 0 by explicitly setting it, 
  // as the camera could have a different default trigger mode
  //
#ifdef SOFTWARE_TRIGGER_CAMERA
  //
  // We are triggering the camera using the internal software trigger.
  // If we are using the DCAM SOFTWARE_TRIGGER functionality, we must
  // change the Trigger_Source to reflect the Software Trigger ID = 7.
  //
  error = flycaptureSetTrigger( 
    context, true, iPolarity, 7, 0, 0 );
  HANDLE_ERROR( "flycaptureSetCameraTrigger()", error );
#else
  //
  // We are triggering the camera using an external hardware trigger.
  //
  error = flycaptureSetTrigger( 
    _context, true, iPolarity, iSource, 0, 0 );
  HANDLE_ERROR("flycaptureSetCameraTrigger()", error);
#endif
  // 
  // Poll the camera to make sure the camera is actually in trigger mode
  // before we start it (avoids timeouts due to the trigger not being armed)
  //
  checkTriggerReady();

  //
  // Start the camera and grab any excess images that are already in the pipe.
  // Although it is extremely rare for spurious images to occur, it is
  // possible for the grab call to return an image that is not a result of a
  // user-generated trigger. To grab excess images, set a zero-length timeout.
  // A value of zero makes the grab call non-blocking.
  //
  printf( "Checking for any buffered images..." );
  error = flycaptureSetGrabTimeoutEx(_context, 0);
  HANDLE_ERROR("flycaptureSetGrabTimeoutEx()", error);
    
  error = flycaptureStart(
    _context, FLYCAPTURE_VIDEOMODE_ANY, FLYCAPTURE_FRAMERATE_ANY);
  HANDLE_ERROR("flycaptureStart()", error);

  // Grab the image immediately whether or not trigger present
  FlyCaptureImage  image;
  error = flycaptureGrabImage2(_context, &image);
  if( error == FLYCAPTURE_OK ) {
    printf( "buffered image found. Flush successful.\n" );
  } else if( error == FLYCAPTURE_TIMEOUT ) {
    printf( "no flush required! (normal behaviour)\n" );
  } else {
    HANDLE_ERROR( "flycaptureGrabImage2()", error );
  }

  error = flycaptureStop(_context);
  HANDLE_ERROR("flycaptureStop()", error);

  //
  // Start camera.  This is done after setting the trigger so that
  // excess images isochronously streamed from the camera don't fill up 
  // the internal buffers.
  //
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
  printf( "Starting camera.\n" );
  error = flycaptureStart( 
    _context, FLYCAPTURE_VIDEOMODE_640x480Y8, FLYCAPTURE_FRAMERATE_30);
  HANDLE_ERROR("flycaptureStart()", error);

  //
  // Set the grab timeout so that calls to flycaptureGrabImage2 will return 
  // after TIMEOUT milliseconds if the trigger hasn't fired.
  //
  error = flycaptureSetGrabTimeoutEx(_context, FLYCAPTURE_INFINITE);
  HANDLE_ERROR("flycaptureSetGrabTimeoutEx()", error);
  fflush(stdout);
}

void FireflyDriver::capturenow(unsigned char *pimageBGRU32, int width, int height) {
  FlyCaptureImage image;
  FlyCaptureError error;
	// Initialize the image structure to sane values
	image.iCols = 0;
	image.iRows = 0;

	error = flycaptureGrabImage2(_context, &image);
  HANDLE_ERROR("flycaptureGrabImage2()", error);

	// Convert the last image to BGRU32.
	FlyCaptureImage imageConverted;
  imageConverted.pData = pimageBGRU32;
  imageConverted.pixelFormat = FLYCAPTURE_BGRU;

  //printf( "Converting last image.\n" );
  error = flycaptureConvertImage(_context, &image, &imageConverted);
  HANDLE_ERROR("flycaptureConvertImage()", error);

  int index = 3;
  for (int h = 0; h < height; h++)
    for (int w = 0; w < width; w++) {
      *(pimageBGRU32 + index) = 0xff;
      index += 4;
    }

	fflush(stdout);
}

void FireflyDriver::cleanup() {
  FlyCaptureError error;
  error = flycaptureStop(_context);
  HANDLE_ERROR("flycaptureStop()", error);
	error = flycaptureDestroyContext(_context);
	HANDLE_ERROR("flycaptureBusEnumerateCameras()", error);

	printf("Done!");
	fflush(stdout);
}


FlyCaptureError FireflyDriver::checkTriggerReady() {
  FlyCaptureError  error;
  unsigned long  ulValue;

  // Do our check to make sure the camera is ready to be triggered
  // by looking at bits 30-31. Any value other than 1 indicates
  // the camera is not ready to be triggered.
  error = flycaptureGetCameraRegister(_context, SOFT_ASYNC_TRIGGER, &ulValue);
  HANDLE_ERROR("flycaptureGetCameraRegister()", error);

  while( ulValue != 0x80000001 ) {
    error = flycaptureGetCameraRegister(_context, SOFT_ASYNC_TRIGGER, &ulValue);
    HANDLE_ERROR( "flycaptureGetCameraRegister()", error );
  }
  return FLYCAPTURE_OK;
}

