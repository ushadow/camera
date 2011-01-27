#ifndef SWIG
#include <windows.h>
#endif

// Display Engine Structures Tags
#define  YUVOVERLAY_TAG                                     0xF6216548
#define  OFFSCREENRGB_TAG                                   0xFF344314
// Camera Control Engine Structures Tags
#define  FIREi_CAMERA_INFO_STRUCT_TAG                       0xC6009569
#define  FIREi_CAMERA_STARTUP_INFO_TAG                      0xC6620044
#define  FIREi_CAMERA_FEATURE_INQUIRY_REGISTER_TAG          0xC6756320
#define  FIREi_CAMERA_FEATURE_CONTROL_REGISTER_TAG          0xC1234556
#define  FIREi_CAMERA_TRIGGER_FEATURE_INQUIRY_REGISTER_TAG  0xC7654321
#define  FIREi_CAMERA_TRIGGER_FEATURE_CONTROL_REGISTER_TAG  0xC8218868
#define  FIREi_CAMERA_FORMAT_7_REGISTERS_TAG                0xC6523995
#define  FIREi_CAMERA_FORMAT_7_STARTUP_INFO_TAG             0xC9931563
// Isochronous Receive Engine Structures Tags
#define  FIREi_ISOCH_ENGINE_STRUCT_TAG                      0xAA255123
#define  FIREi_ISOCH_ENGINE_EX_STRUCT_TAG                   0xAB552336
#define  FIREi_REQUEST_STRUCT_TAG                           0xA4552336
#define  FIREi_ISOCH_ENGINE_STATS_STRUCT_TAG                0x19760708

#ifndef SWIG
//------------------------------------------------------------------------------------
BOOL FiIsDisplayHandleValid( FIREi_DISPLAY_HANDLE a_DisplayHandle );
//------------------------------------------------------------------------------------
BOOL FiIsCameraHandleValid( FIREi_CAMERA_HANDLE a_hCamera);
//------------------------------------------------------------------------------------
BOOL FiIsCameraStartupInfoValid( FIREi_CAMERA_HANDLE a_hCamera,
                                 PFIREi_CAMERA_STARTUP_INFO a_pFiCameraStartupInfo);
//------------------------------------------------------------------------------------
BOOL FiIsIsochEngineHandleValid( FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine);
//------------------------------------------------------------------------------------
BOOL FiIsIsochEngineExHandleValid(FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//------------------------------------------------------------------------------------
BOOL FiIsRequestHandleValid(FIREi_REQUEST_HANDLE a_hRequest);
//------------------------------------------------------------------------------------
#endif