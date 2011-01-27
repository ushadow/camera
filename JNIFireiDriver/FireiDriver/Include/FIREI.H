#pragma once

#include "FireiTypes.h"
#include "FireiStatus.h"
#include "ParameterValidation.h"
#include "CameraRegisterDef.h"

//The debugging functions
#include "dbg.h"

// In some environments these might not be defined.
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MIN(A,B) ((A>B)?(B):(A))
#define MAX(A,B) ((A>B)?(A):(B))

///////////////////////////////////////////////////////////
// Declaration specifiers for functions
///////////////////////////////////////////////////////////
// Sambanis: This is done because the x64 compiler doesn't like doubly exported functions (.def and here)
#if defined(FIREiAPI_DLL_BUILD) && defined(_WIN64)
#define FIREiAPI_DLL_SPEC
#elif defined(FIREiAPI_DLL_BUILD)
#define FIREiAPI_DLL_SPEC __declspec(dllexport)
#else
#define FIREiAPI_DLL_SPEC __declspec(dllimport)
#endif

#define FIREiAPI(type) FIREiAPI_DLL_SPEC type WINAPI

#ifdef FIREi_OPEN_DLL
#define FiPixelFormatStringA            FiOPixelFormatStringA
#define FiPixelFormatStringW            FiOPixelFormatStringW
#define FiFpsStringA                    FiOFpsStringA
#define FiFpsStringW                    FiOFpsStringW
#define FiVideoModeStringA              FiOVideoModeStringA
#define FiVideoModeStringW              FiOVideoModeStringW
#define FiVideoFormatStringA            FiOVideoFormatStringA
#define FiVideoFormatStringW            FiOVideoFormatStringW
#define FiRawModeStringA                FiORawModeStringA
#define FiRawModeStringW                FiORawModeStringW
#define FiRawConversionMethodStringA    FiORawConversionMethodStringA
#define FiRawConversionMethodStringW    FiORawConversionMethodStringW
#define FiStatusStringA                 FiOStatusStringA
#define FiStatusStringW                 FiOStatusStringW
#define FiSpeedStringA                  FiOSpeedStringA
#define FiSpeedStringW                  FiOSpeedStringW
#define FiSwapEndian32                  FiOSwapEndian32
#define FiInitFormatInfo                FiOInitFormatInfo
#define FiInitialize                    FiOInitialize
#define FiTerminate                     FiOTerminate
#define FiBusReset                      FiOBusReset
#define FiGetAdapterBusResetHandle      FiOGetAdapterBusResetHandle
#define FiResetBusResetEvent            FiOResetBusResetEvent
#define FiLocateCameras                 FiOLocateCameras
#define FiLocateCamerasEx               FiOLocateCamerasEx
#define FiLocateCameraUnits             FiOLocateCameraUnits
#define FiLocateCameraUnitsEx           FiOLocateCameraUnitsEx
#define FiOpenCameraHandle              FiOOpenCameraHandle
#define FiOpenCameraHandleEx            FiOOpenCameraHandleEx
#define FiOpenCameraUnitHandle          FiOOpenCameraUnitHandle
#define FiOpenCameraUnitHandleEx        FiOOpenCameraUnitHandleEx
#define FiOpenCameraUnitHandles         FiOOpenCameraUnitHandles
#define FiOpenCameraUnitHandlesEx       FiOOpenCameraUnitHandlesEx
#define FiCloseCameraHandle             FiOCloseCameraHandle
#define FiGetCameraStartupInfo          FiOGetCameraStartupInfo
#define FiSetCameraStartupInfo          FiOSetCameraStartupInfo
#define FiQueryCameraRegister           FiOQueryCameraRegister
#define FiSetCameraRegister             FiOSetCameraRegister
#define FiQueryCameraRegisterEx         FiOQueryCameraRegisterEx
#define FiSetCameraRegisterEx           FiOSetCameraRegisterEx
#define FiSaveToCameraMemoryChannel     FiOSaveToCameraMemoryChannel
#define FiLoadFromCameraMemoryChannel   FiOLoadFromCameraMemoryChannel
#define FiStopCamera                    FiOStopCamera
#define FiStartCamera                   FiOStartCamera
#define FiStartAll                      FiOStartAll
#define FiCameraOneShotTransmit         FiOCameraOneShotTransmit
#define FiIsCameraRunning               FiOIsCameraRunning
#define FiIsCameraOneMultiShooting      FiOIsCameraOneMultiShooting
#define FiResetCamera                   FiOResetCamera
#define FiIsCameraConnected             FiOIsCameraConnected
#define FiWriteQuad                     FiOWriteQuad
#define FiReadQuad                      FiOReadQuad
#define FiWriteQuadEx                   FiOWriteQuadEx
#define FiReadQuadEx                    FiOReadQuadEx
#define FiWriteBlock                    FiOWriteBlock
#define FiReadBlock                     FiOReadBlock
#define FiInitializeDisplay             FiOInitializeDisplay
#define FiCreateDisplayWindow           FiOCreateDisplayWindow
#define FiResizeDisplayWindow           FiOResizeDisplayWindow
#define FiMoveDisplayWindow             FiOMoveDisplayWindow
#define FiGetDisplayWindowSize          FiOGetDisplayWindowSize
#define FiDisplayCameraFrame            FiODisplayCameraFrame
#define FiUpdateDisplayWindow           FiOUpdateDisplayWindow
#define FiCloseDisplayWindow            FiOCloseDisplayWindow
#define FiHideDisplayWindow             FiOHideDisplayWindow
#define FiShowDisplayWindow             FiOShowDisplayWindow
#define FiSetRawMode                    FiOSetRawMode
#define FiGetRawMode                    FiOGetRawMode
#define FiYuv2Rgb                       FiOYuv2Rgb
#define FiYuv2Bgr                       FiOYuv2Bgr
#define FiConvertToRGB24                FiOConvertToRGB24
#define FiCreateIsochReceiveEngine      FiOCreateIsochReceiveEngine
#define FiStartIsochReceiveEngine       FiOStartIsochReceiveEngine
#define FiGetNextCompleteFrame          FiOGetNextCompleteFrame
#define FiCleanupIsochReceiveEngine     FiOCleanupIsochReceiveEngine
#define FiStopIsochReceiveEngine        FiOStopIsochReceiveEngine
#define FiDeleteIsochReceiveEngine      FiODeleteIsochReceiveEngine
#define FiSaveFrame                     FiOSaveFrame
#define FiSaveFrameExA                  FiOSaveFrameExA
#define FiSaveFrameExW                  FiOSaveFrameExW
#define FiCreateIsochReceiveEngineEx    FiOCreateIsochReceiveEngineEx
#define FiCreateIsochReceiveEngineExEx  FiOCreateIsochReceiveEngineExEx
#define FiAllocateFrames                FiOAllocateFrames
#define FiStartIsochReceiveEngineEx     FiOStartIsochReceiveEngineEx
#define FiReleaseFrame                  FiOReleaseFrame
#define FiGetNextCompleteFrameEx        FiOGetNextCompleteFrameEx
#define FiStopIsochReceiveEngineEx      FiOStopIsochReceiveEngineEx
#define FiDeallocateFrames              FiODeallocateFrames
#define FiDeleteIsochReceiveEngineEx    FiODeleteIsochReceiveEngineEx
#define FiFlushIsochReceiveEngine       FiOFlushIsochReceiveEngine
#define FiSetDisplayCallback            FiOSetDisplayCallback
#define FiSetIsochEngineOption          FiOSetIsochEngineOption
#define FiGetSpecialFeaturePresence     FiOGetSpecialFeaturePresence
#define FiGetSpecialFeatureCaps         FiOGetSpecialFeatureCaps
#define FiSetSpecialFeatureCaps         FiOSetSpecialFeatureCaps
#define FiSendBroadcastQuadEx           FiOSendBroadcastQuadEx
#define FiSendBroadcastQuad             FiOSendBroadcastQuad
#define FiGetAvailableIsoChannel        FiOGetAvailableIsoChannel
#define FiSetConversionCallback         FiOSetConversionCallback
#define FiGetLUT                        FiOGetLUT
#define FiSetLUT                        FiOSetLUT
#endif

///////////////////////////////////////////////////////////
// String Helper Functions
///////////////////////////////////////////////////////////
FIREiAPI(char*)  FiPixelFormatStringA( FIREi_PIXEL_FORMAT a_PixelFormat );
FIREiAPI(WCHAR*) FiPixelFormatStringW( FIREi_PIXEL_FORMAT a_PixelFormat );
FIREiAPI(char*)  FiFpsStringA( FIREi_FPS a_fps );
FIREiAPI(WCHAR*) FiFpsStringW( FIREi_FPS a_fps );
FIREiAPI(char*)  FiVideoModeStringA( FIREi_VIDEO_MODE a_VideoMode );
FIREiAPI(WCHAR*) FiVideoModeStringW( FIREi_VIDEO_MODE a_VideoMode );
FIREiAPI(char*)  FiVideoFormatStringA( FIREi_VIDEO_FORMAT a_VideoFormat );
FIREiAPI(WCHAR*) FiVideoFormatStringW( FIREi_VIDEO_FORMAT a_VideoFormat );
FIREiAPI(char*)  FiStatusStringA(ULONG a_StatusCode);
FIREiAPI(WCHAR*) FiStatusStringW(ULONG a_StatusCode);
FIREiAPI(char*)  FiSpeedStringA( TRANSMIT_SPEED a_Speed );
FIREiAPI(WCHAR*) FiSpeedStringW( TRANSMIT_SPEED a_Speed );
FIREiAPI(char*)  FiRawModeStringA( FIREi_RAW_MODE a_RawMode );
FIREiAPI(WCHAR*) FiRawModeStringW( FIREi_RAW_MODE a_RawMode );
FIREiAPI(char*)  FiRawConversionMethodStringA( FIREi_RAW_CONVERSION_METHOD a_RawConversion );
FIREiAPI(WCHAR*) FiRawConversionMethodStringW( FIREi_RAW_CONVERSION_METHOD a_RawConversion );

///////////////////////////////////////////////////////////
// Utility Functions
///////////////////////////////////////////////////////////
FIREiAPI(ULONG)  FiSwapEndian32(ULONG a_Value);

#if defined(UNICODE) || defined(_UNICODE)
#define FiPixelFormatString         FiPixelFormatStringW
#define FiFpsString                 FiFpsStringW
#define FiVideoModeString           FiVideoModeStringW
#define FiVideoFormatString         FiVideoFormatStringW
#define FiStatusString              FiStatusStringW
#define FiSpeedString               FiSpeedStringW
#define FiRawModeString             FiRawModeStringW
#define FiRawConversionMethodString FiRawConversionMethodStringW
#define FiSaveFrameEx               FiSaveFrameExW
#else
#define FiPixelFormatString         FiPixelFormatStringA
#define FiFpsString                 FiFpsStringA
#define FiVideoModeString           FiVideoModeStringA
#define FiVideoFormatString         FiVideoFormatStringA
#define FiStatusString              FiStatusStringA
#define FiSpeedString               FiSpeedStringA
#define FiRawModeString             FiRawModeStringA
#define FiRawConversionMethodString FiRawConversionMethodStringA
#define FiSaveFrameEx               FiSaveFrameExA
#endif

//--------------------------------------------------------------------
FIREiAPI(BOOL) FiInitFormatInfo(
    IN  OUT PFIREi_VIDEO_FORMAT_INFO a_pFormatInfo,
    IN      FIREi_VIDEO_FORMAT       a_VideoFormat
);
//********************************************************************
//--------------------------------------------------------------------
// Camera Control Engine Function prototypes
//--------------------------------------------------------------------
//********************************************************************
FIREiAPI(FIREi_STATUS) FiInitialize(void);
//--------------------------------------------------------------------
FIREiAPI(void)         FiTerminate( void );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiBusReset(
    IN      ULONG                       a_uAdapterNumber,
    IN      BOOLEAN                     a_bShortReset );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetAdapterBusResetHandle(
    IN      ULONG                       a_uAdapterNumber,
    OUT     HANDLE                      *a_pBusResetHandle );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiResetBusResetEvent(
    IN      ULONG                       a_uAdapterNumber);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiLocateCameras(
    IN OUT  FIREi_CAMERA_GUID           *a_pCameraGuidArray,
    IN      ULONG                       uFlags,
    IN OUT  ULONG                       *a_uNumberOfCameras );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiLocateCamerasEx(
    IN      ULONG                       a_uAdapterNumber,
    IN OUT  FIREi_CAMERA_GUID           *a_pCameraGuidArray,
    IN      ULONG                       uFlags,
    IN OUT  ULONG                       *a_uNumberOfCameras );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiLocateCameraUnits(
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    OUT     UCHAR                      *a_uchNumberOfUnits);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiLocateCameraUnitsEx(
    IN      ULONG                       a_uAdapterNumber,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    OUT     UCHAR                      *a_uchNumberOfUnits);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraHandle(
    OUT     PFIREi_CAMERA_HANDLE        a_pCameraHandle,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraHandleEx(
    IN      ULONG                       a_uAdapterNumber,
       OUT  PFIREi_CAMERA_HANDLE        a_pCameraHandle,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraUnitHandle(
    OUT     PFIREi_CAMERA_HANDLE        a_pCameraHandle,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    IN      UCHAR                       a_uchUnitNumber );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraUnitHandleEx(
    IN      ULONG                       a_uAdapterNumber,
    OUT     PFIREi_CAMERA_HANDLE        a_pCameraHandle,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    IN      UCHAR                       a_uchUnitNumber,
    IN      FIREi_CONFIGURATION_ENTRY  *a_pConfigArray,
    IN      ULONG                       a_uConfigNumber );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraUnitHandles(
    IN OUT  FIREi_CAMERA_HANDLE        *a_pCameraHandleArray,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    IN      UCHAR                       a_uchNumberOfUnits );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiOpenCameraUnitHandlesEx(
    IN      ULONG                       a_uAdapterNumber,
    IN OUT  FIREi_CAMERA_HANDLE        *a_pCameraHandleArray,
    IN      PFIREi_CAMERA_GUID          a_pCameraGuid,
    IN      UCHAR                       a_uchNumberOfUnits );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCloseCameraHandle(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetCameraStartupInfo(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle,
       OUT  PFIREi_CAMERA_STARTUP_INFO  a_pCameraStartupInfo );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetCameraStartupInfo(
    IN  FIREi_CAMERA_HANDLE             a_CameraHandle,
    OUT PFIREi_CAMERA_STARTUP_INFO      a_pFiCameraStartupInfo );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiQueryCameraRegister(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle,
    IN OUT  FIREi_OID                   a_ControlOID,
    IN OUT  PVOID                       Buffer,
    IN      ULONG                       uBufferLength);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetCameraRegister(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle,
    IN      FIREi_OID                   a_ControlOID,
    IN OUT  PVOID                       InputBuffer,
    IN      ULONG                       uInputBufferLength);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiQueryCameraRegisterEx(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN      ULONG                   a_Offset,
        OUT PVOID                   a_Buffer);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetCameraRegisterEx(
    IN FIREi_CAMERA_HANDLE          a_CameraHandle,
    IN      ULONG                   a_Offset,
    IN      PVOID                   a_Buffer);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSaveToCameraMemoryChannel(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN      USHORT                  a_ChannelNumber);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiLoadFromCameraMemoryChannel(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN      USHORT                  a_ChannelNumber);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStopCamera(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStartCamera(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle,
    IN      PFIREi_CAMERA_STARTUP_INFO  a_pCameraStartupInfo );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStartAll(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCameraOneShotTransmit(
    IN      FIREi_CAMERA_HANDLE         a_CameraHandle,
    IN      PFIREi_CAMERA_STARTUP_INFO  a_pCameraStartupInfo,
    IN      ULONG                       a_uNumberOfFrames );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiIsCameraRunning(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle,
    OUT     BOOLEAN                 *a_pIsRunning);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiIsCameraOneMultiShooting(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle,
    OUT     BOOLEAN                 *a_pbIsOneMultiShooting);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiResetCamera(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle);
//--------------------------------------------------------------------
FIREiAPI(BOOLEAN) FiIsCameraConnected(
    IN      FIREi_CAMERA_HANDLE     a_CameraHandle);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiWriteQuad(
    IN FIREi_CAMERA_HANDLE    a_CameraHandle,
    IN ULONG                  a_Offset,
    IN ULONG                  a_Quad);
//--------------------------------------------------------------------
#if defined(TYPES_1394_H_INCLUDED)
FIREiAPI(FIREi_STATUS) FiWriteQuadEx(
    IN FIREi_CAMERA_HANDLE    a_CameraHandle,
    IN ULONG                  a_Offset,
    IN ULONG                    a_Quad,
    OUT C1394_ACK_CODE         *a_pAcknowledgeCode,
    OUT C1394_RESPONSE_CODE    *a_pResponseCode);
#endif
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiReadQuad(
    IN FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN ULONG                   a_Offset,
    IN ULONG                  *a_Quad);
//--------------------------------------------------------------------
#if defined(TYPES_1394_H_INCLUDED)
FIREiAPI(FIREi_STATUS) FiReadQuadEx(
    IN FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN ULONG                   a_Offset,
    IN ULONG                   *a_Quad,
    OUT C1394_ACK_CODE         *a_pAcknowledgeCode,
    OUT C1394_RESPONSE_CODE    *a_pResponseCode);
#endif
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiWriteBlock(
    IN FIREi_CAMERA_HANDLE    a_CameraHandle,
    IN ULONG                  a_Offset,
    IN UCHAR                 *a_Buffer,
    IN ULONG                  a_BufferSize);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiReadBlock(
    IN FIREi_CAMERA_HANDLE     a_CameraHandle,
    IN ULONG                   a_Offset,
    IN UCHAR                  *a_Buffer,
    IN ULONG                   a_BufferSize);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetSpecialFeaturePresence(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    IN ULONG                   a_uSpecialFeatureOID,
    OUT PBOOL                  a_pPresent);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetSpecialFeatureCaps(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    IN ULONG                   a_uSpecialFeatureOID,
    OUT PVOID                  a_pBuffer);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetSpecialFeatureCaps(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    IN ULONG                   a_uSpecialFeatureOID,
    IN PVOID                   a_pBuffer);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSendBroadcastQuadEx(
    IN ULONG                   a_uAdapterNumber,
    IN ULONG                   a_Offset,
    IN ULONG                   a_Quad);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSendBroadcastQuad(
    IN ULONG                   a_Offset,
    IN ULONG                   a_Quad);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetAvailableIsoChannel(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    IN OUT PUCHAR              a_uchChannel);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetLUT(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    OUT BOOL                  *a_pbOnOff,
    OUT BOOL                  *a_pbPath,
    OUT UCHAR                 *a_puchLUTIndex);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetLUT(
    IN FIREi_CAMERA_HANDLE     a_hCamera,
    IN BOOL                    a_bOnOff,
    IN BOOL                    a_bPath,
    IN UCHAR                   a_uchLUTIndex,
    IN USHORT                 *a_pushData);
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//********************************************************************
//--------------------------------------------------------------------
//  Display Engine Function prototypes
//--------------------------------------------------------------------
//********************************************************************
FIREiAPI(FIREi_STATUS) FiInitializeDisplay();
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCreateDisplayWindow(
    IN      HWND                        a_hWnd,
       OUT  PFIREi_DISPLAY_HANDLE       a_pFIREiDisplayHandle,
    IN      PFIREi_CAMERA_STARTUP_INFO  a_pStartupInfo,
    IN      POINT                       a_DisplayPosition,
    IN      BOOL*                       a_pbOverlay);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiResizeDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      PLONG                       a_sizeX,
    IN      PLONG                       a_sizeY );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiMoveDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      POINT                       a_NewPosition);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetDisplayWindowSize(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    OUT     PLONG                       a_sizeX,
    OUT     PLONG                       a_sizeY );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiDisplayCameraFrame(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      PFIREi_CAMERA_FRAME         a_pCameraFrame);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiUpdateDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      BOOL                        a_bStretch);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCloseDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiHideDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiShowDisplayWindow(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay);
//--------------------------------------------------------------------
FIREiAPI(float) FiGetAverageFrameTime(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetRawMode(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      FIREi_RAW_MODE              a_RawMode,
    IN      FIREi_RAW_CONVERSION_METHOD a_RawConversion);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetRawMode(
    IN      FIREi_DISPLAY_HANDLE         a_hDisplay,
    OUT     PFIREi_RAW_MODE              a_pRawMode,
    OUT     PFIREi_RAW_CONVERSION_METHOD a_pRawConversion);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiYuv2Rgb(
    IN      PFIREi_CAMERA_FRAME         a_pCameraFrame,
    OUT     BYTE                        *a_pRgbBuffer,
    IN OUT  DWORD                       *a_pdwBufferSize);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiYuv2Bgr(
	IN		PFIREi_CAMERA_FRAME		a_pCameraFrame,
	OUT		BYTE					*a_pBgrBuffer,
	IN OUT	DWORD					*a_pdwBufferSize);
//--------------------------------------------------------------------
FIREiAPI(void) FiConvertToRGB24(
    IN		FIREi_CAMERA_FRAME			*a_pCameraFrame,
    OUT		BYTE*						*a_pBuffer,
    IN      BOOL                         a_bFlipY);
//--------------------------------------------------------------------
typedef void (*DISPLAYCALLBACK)(HDC, PFIREi_CAMERA_FRAME, LPVOID);
FIREiAPI(FIREi_STATUS) FiSetDisplayCallback(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      DISPLAYCALLBACK             a_CallbackFunc,
    IN      LPVOID                      a_pContext);
//--------------------------------------------------------------------
typedef void (*CONVERSIONCALLBACK)(PFIREi_CAMERA_FRAME, LPVOID);
FIREiAPI(FIREi_STATUS) FiSetConversionCallback(
    IN      FIREi_DISPLAY_HANDLE        a_hDisplay,
    IN      CONVERSIONCALLBACK          a_CallbackFunc,
    IN      LPVOID                      a_pContext);

//********************************************************************
//--------------------------------------------------------------------
//  Isochronous receive Engine Function prototypes
//--------------------------------------------------------------------
//********************************************************************
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCreateIsochReceiveEngine(OUT PFIREi_ISOCH_ENGINE_HANDLE  a_phIsochEngine );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStartIsochReceiveEngine
(
    IN      FIREi_ISOCH_ENGINE_HANDLE   a_hIsochEngine,
    IN      PFIREi_CAMERA_STARTUP_INFO  a_StartupInfo,
    IN      ULONG                       a_uAdapterIndex
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetNextCompleteFrame
(
       OUT  PFIREi_CAMERA_FRAME         a_pCameraFrame,
    IN      FIREi_ISOCH_ENGINE_HANDLE   a_hIsochEngine,
    IN  DWORD                       a_dwTimeout
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCleanupIsochReceiveEngine(IN FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiFlushIsochReceiveEngine(IN FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStopIsochReceiveEngine(IN FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine );
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiDeleteIsochReceiveEngine(IN FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSaveFrame
(
    IN      PFIREi_CAMERA_FRAME         pCameraFrame,
    IN      char                       *pSavePath,
    IN      DWORD                       dwFileFormat
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSaveFrameExA
(
    IN      PFIREi_CAMERA_FRAME         pCameraFrame,
    IN      const char                 *pszSavePath,
    OUT     DWORD                      *pdwWin32ErrorCode
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSaveFrameExW
(
    IN      PFIREi_CAMERA_FRAME         pCameraFrame,
    IN      const WCHAR                *pszSavePath,
    OUT     DWORD                      *pdwWin32ErrorCode
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCreateIsochReceiveEngineEx
(
    OUT PFIREi_ISOCH_ENGINE_EX_HANDLE   phIsochEngineEx,
    IN  ULONG                           uAdapterIndex,
    OUT HANDLE                         *pChannelStartProcessingEvent
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiCreateIsochReceiveEngineExEx
(
    OUT  PFIREi_ISOCH_ENGINE_EX_HANDLE   phIsochEngineEx,
    IN   ULONG                           uAdapterIndex,
    OUT  HANDLE                         *pChannelStartProcessingEvent,
    IN   ULONG							MaxPacketsPerFrame,
    IN   FIREi_FPS						MinFps
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiAllocateFrames
(
    IN     FIREi_ISOCH_ENGINE_EX_HANDLE hIsochEngineEx,
    IN     PFIREi_CAMERA_STARTUP_INFO   StartupInfo,
    IN     ULONG                        uFrames
);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStartIsochReceiveEngineEx(IN FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiReleaseFrame(IN PFIREi_CAMERA_FRAME a_pCameraFrame);
//--------------------------------------------------------------------
FIREiAPI(PFIREi_CAMERA_FRAME) FiGetNextCompleteFrameEx(IN FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiStopIsochReceiveEngineEx(IN FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiDeallocateFrames(IN FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiDeleteIsochReceiveEngineEx(IN FIREi_ISOCH_ENGINE_EX_HANDLE a_hIsochEngineEx);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiSetIsochEngineOption(
    IN FIREi_ISOCH_ENGINE_HANDLE a_hIsochEngine,
    IN ULONG                   a_uSpecialFeatureOID,
    IN PVOID                   a_pBuffer);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetIsochEngineStats(
    IN  FIREi_ISOCH_ENGINE_HANDLE       a_hIsochEngine,
    OUT PFIREi_ISOCH_ENGINE_STATS       a_pStats);
//--------------------------------------------------------------------
FIREiAPI(FIREi_STATUS) FiGetIsochEngineStatsEx(
    IN  FIREi_ISOCH_ENGINE_EX_HANDLE    a_hIsochEngineEx,
    OUT PFIREi_ISOCH_ENGINE_STATS       a_pStats);
//--------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
