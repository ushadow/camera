#pragma once

#if defined(FIREiAPI_DLL_BUILD)
#include "..\FireApi.h"
#include "..\UB1394DH.h"
#endif

#include "FireiStatus.h"
#ifndef SWIG
#include "FireiEnums.h"
#endif

/////////////////////////////////////////////////////////////////////
// General Declaration of FIREi Handles
/////////////////////////////////////////////////////////////////////
#if !defined(_WIN64)
#define DECLARE_FIREi_HANDLE(Owner, Item)    \
typedef struct { int Unused; } tag##Owner##_##Item##_HANDLE; \
typedef tag##Owner##_##Item##_HANDLE* Owner##_##Item##_HANDLE; \
typedef Owner##_##Item##_HANDLE* P##Owner##_##Item##_HANDLE;
#else
#define DECLARE_FIREi_HANDLE(Owner, Item)    \
typedef struct {__int64 Unused; } tag##Owner##_##Item##_HANDLE; \
typedef tag##Owner##_##Item##_HANDLE* Owner##_##Item##_HANDLE; \
typedef Owner##_##Item##_HANDLE* P##Owner##_##Item##_HANDLE;
#endif

//--------------------------- FIREi handle definitions ----------------------
// The handle type that identifies a FIREi Camera
DECLARE_FIREi_HANDLE(FIREi, CAMERA);

// The handle type that identifies a FIREi Isochronous engine.
DECLARE_FIREi_HANDLE(FIREi, ISOCH_ENGINE);

// The handle type that identifies a FIREi Extended Isochronous engine.
DECLARE_FIREi_HANDLE(FIREi, ISOCH_ENGINE_EX);

// The handle type that identifies a FIREi Display Window.
DECLARE_FIREi_HANDLE(FIREi, DISPLAY);

// The handle type that identifies a frame request.
// This handle is only used internally by the extended
// isochronous processing functions in order to requeue
// a frame for reception
DECLARE_FIREi_HANDLE(FIREi, REQUEST);
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////
//  Structures specific for the FiQueryCameraRegister
///////////////////////////////////////////////////////////
// The type used for the complete 16-bit Node IDs.
#pragma warning(disable:4201)
typedef union
{
    USHORT  Value;

    struct
    {
        USHORT  PhysicalID:6;
        USHORT  BusID:10;
    };
}
FIREi_NODE_ID, *PFIREi_NODE_ID;
#pragma warning(default:4201)
// The structure used to export Parent Node Id and Physical Port
typedef struct
{
    FIREi_NODE_ID   NodeID;
    ULONG           PhysicalPort;
}
FIREi_PARENT_PHYSICAL_PORT, *PFIREi_PARENT_PHYSICAL_PORT;

///////////////////////////////////////////////////////////

// Camera Guid definition
typedef struct
{
    UCHAR Bytes[8];
}
FIREi_CAMERA_GUID, *PFIREi_CAMERA_GUID;

typedef UCHAR    TRANSMIT_SPEED;

#ifndef S100
#define S100        ((TRANSMIT_SPEED)0)
#define S200        ((TRANSMIT_SPEED)1)
#define S400        ((TRANSMIT_SPEED)2)
#define S800        ((TRANSMIT_SPEED)3)
#define S1600       ((TRANSMIT_SPEED)4)
#define S3200       ((TRANSMIT_SPEED)5)
#endif

// Camera OID definition
#define FIREi_OID           ULONG


//////////////////////////////////////////////////////////////////////////////////
//  Define all the different Object Identifiers for FiQuery/SetCameraRegister   //
//////////////////////////////////////////////////////////////////////////////////
// Format of the OID is: 3 Most Significant Bytes = Offset of the camera register where the capability lays. 0x000000 if capability is not a camera register
//                         Least Significant Byte = Position of the OID on the abSupportedOIDs array.
//  ONE EXCEPTION: VR and UB features have the same OID, except from the Bit 7 that in VR OID is 1.

//////////////////////
// Inquiry Register //
//////////////////////
// All the following use the same structure
#define OID_BRIGHTNESS_INQ          0x00050000
#define OID_AUTO_EXPOSURE_INQ       0x00050401
#define OID_SHARPNESS_INQ           0x00050802
#define OID_UB_INQ                  0x00050C03
#define OID_VR_INQ                  0x00050C83 // Same register with UB.
#define OID_HUE_INQ                 0x00051004
#define OID_SATURATION_INQ          0x00051405
#define OID_GAMMA_INQ               0x00051806
#define OID_SHUTTER_INQ             0x00051C07
#define OID_GAIN_INQ                0x00052008
#define OID_IRIS_INQ                0x00052409
#define OID_FOCUS_INQ               0x0005280A
#define OID_TEMPERATURE_INQ         0x00052C0B
#define OID_ZOOM_INQ                0x0005800C
#define OID_PAN_INQ                 0x0005840D
#define OID_TILT_INQ                0x0005880E
#define OID_OPTICAL_FILTER_INQ      0x00058C0F

// Trigger inquiry register uses another structure
#define OID_TRIGGER_INQ             0x00053010

///////////////////////
// Absolute Register //
///////////////////////
#define OID_BRIGHTNESS_ABS          0x00070000
#define OID_AUTO_EXPOSURE_ABS       0x00070401
#define OID_SHARPNESS_ABS           0x00070802
#define OID_UB_ABS                  0x00070C03
#define OID_VR_ABS                  0x00070C83
#define OID_HUE_ABS                 0x00071004
#define OID_SATURATION_ABS          0x00071405
#define OID_GAMMA_ABS               0x00071806
#define OID_SHUTTER_ABS             0x00071C07
#define OID_GAIN_ABS                0x00072008
#define OID_IRIS_ABS                0x00072409
#define OID_FOCUS_ABS               0x0007280A
#define OID_TEMPERATURE_ABS         0x00072C0B
#define OID_ZOOM_ABS                0x0007800C
#define OID_PAN_ABS                 0x0007840D
#define OID_TILT_ABS                0x0007880E
#define OID_OPTICAL_FILTER_ABS      0x00078C0F

//////////////////////
// Control Register //
//////////////////////
#define OID_BRIGHTNESS_CONTROL      0x00080000
#define OID_AUTO_EXPOSURE_CONTROL   0x00080401
#define OID_SHARPNESS_CONTROL       0x00080802
#define OID_UB_CONTROL              0x00080C03
#define OID_VR_CONTROL              0x00080C83
#define OID_HUE_CONTROL             0x00081004
#define OID_SATURATION_CONTROL      0x00081405
#define OID_GAMMA_CONTROL           0x00081806
#define OID_SHUTTER_CONTROL         0x00081C07
#define OID_GAIN_CONTROL            0x00082008
#define OID_IRIS_CONTROL            0x00082409
#define OID_FOCUS_CONTROL           0x0008280A
#define OID_TEMPERATURE_CONTROL     0x00082C0B
#define OID_ZOOM_CONTROL            0x0008800C
#define OID_PAN_CONTROL             0x0008840D
#define OID_TILT_CONTROL            0x0008880E
#define OID_OPTICAL_FILTER_CONTROL  0x00088C0F

// Trigger control register uses another structure
#define OID_TRIGGER_CONTROL         0x00083010

//////////////////////
// Other Features   //
//////////////////////
#define OID_FORMAT_7_REGISTERS          0x00000011
#define OID_UNIT_SOFTWARE_VERSION       0x00000012
#define OID_CSR_BASE_OFFSET             0x00000013
#define OID_VENDOR_NAME                 0x00000014
#define OID_MODEL_NAME                  0x00000015
#define OID_MAX_MEMORY_CHANNEL_NUMBER   0x00000016
#define OID_CAMERA_GUID                 0x00000017
#define OID_CAMERA_VIDEO_FORMATS        0x00000018
#define OID_CAMERA_MAX_SPEED            0x00000019
#define OID_CAMERA_SERIAL_NUMBER        0x0000001A
#define OID_CAMERA_NODE_ID              0x0000001B
#define OID_PARENT_PHYSICAL_PORT        0x0000001C
#define OID_FORMAT7_IMAGE_POS           0x0000001D
#define OID_UNIT_SUB_SOFTWARE_VERSION   0x0000001E
#define OID_FORMAT_7_OFFSETS            0x0000001F
#define OID_CAMERA_DEVICE_HANDLE        0x00000020
#define OID_CUR_MEMORY_CHANNEL_NUMBER   0x00000021
#define OID_CAMERA_CUR_SPEED            0x00000022
#define OID_ISO_CHANNELS_SUPPORTED      0x00000023
#define MAX_QUERY_OID_NUMBER            OID_ISO_CHANNELS_SUPPORTED

#define CAMERA_INQUIRY_REGISTERS    0x10
#define MAX_SET_OID_NUMBER          0x11
#define MAX_QUERY_OIDS              (MAX_QUERY_OID_NUMBER + 1)

//////////////////////
// Special Features //
//////////////////////
#define OID_EXTRA_PACKETS_PER_CYCLE     0x00010000
#define OID_JUMBO_PACKETS               0x00010001

//////////////////
// MASK DEFINES //
//////////////////

// Mask for Locate Cameras function
#define FIREi_LOCATE_NEW_CAMERAS    0x00000001
#define FIREi_LOCATE_ALL_CAMERAS    0x00000002

// Option for FiGetAvailableIsoChannel
#define FIREi_SEARCH_FOR_CHANNEL    0xFF

//////////////////////////
// Transmit Speed Codes //
//////////////////////////

// This is defined for use by C1394GetAdapterSpeed when the adapter
// handle is invalid. This value is the value stored in the 4-bit
// speed table entries for any pair that is not physically present.
#define TRANSMIT_SPEED_INVALID  ((TRANSMIT_SPEED)0xF)



//////////////////////////////////////////////////////////////
// A Structure for Feature Inquiry Register for the camera  //
//////////////////////////////////////////////////////////////
typedef struct
{
    ULONG   Tag; // Must be set to FIREi_CAMERA_FEATURE_INQUIRY_REGISTER_TAG
    BOOL    bIsPresent;
    BOOL    bHasOnePush;
    BOOL    bIsReadable;
    BOOL    bHasOnOff;
    BOOL    bHasAuto;
    BOOL    bHasManual;
    USHORT  ushMinValue;
    USHORT  ushMaxValue;
    BOOL    bAbsControlInq;
}
FIREi_CAMERA_FEATURE_INQUIRY_REGISTER, *PFIREi_CAMERA_FEATURE_INQUIRY_REGISTER;

//////////////////////////////////////////////////////////////
// A Structure for Feature Inquiry Register for the camera  //
//////////////////////////////////////////////////////////////
typedef struct
{
    ULONG   Tag; // Must be set to FIREi_CAMERA_FEATURE_CONTROL_REGISTER_TAG
    BOOL    bSetOnePush;
    BOOL    bSetOn;
    BOOL    bSetAuto;
    USHORT  ushCurValue;
    BOOL    bAbsControl;
    BOOL    bPresenceInq;
}
FIREi_CAMERA_FEATURE_CONTROL_REGISTER, *PFIREi_CAMERA_FEATURE_CONTROL_REGISTER;

//////////////////////////////////////////////////////////////////////////////////
// A structure specifically designed for TRIGGER feature inquiry of a camera    //
//////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ULONG   Tag; // Must be set to FIREi_CAMERA_TRIGGER_FEATURE_INQUIRY_REGISTER_TAG
    BOOL    bIsPresent;
    BOOL    bIsReadable;
    BOOL    bHasOnOff;
    BOOL    bCanChangePolarity;
    BOOL    bTriggerModeArray[4];
}
FIREi_CAMERA_TRIGGER_FEATURE_INQUIRY_REGISTER, *PFIREi_CAMERA_TRIGGER_FEATURE_INQUIRY_REGISTER;

//////////////////////////////////////////////////////////////////////////////////
// A structure specifically designed for TRIGGER feature control of a camera    //
//////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ULONG   Tag; // Must be set to FIREi_CAMERA_TRIGGER_FEATURE_CONTROL_REGISTER_TAG
    BOOL    bSetOn;
    BOOL    bSetHighPolarity;
    BOOL    bTriggerModeArray[4];
    USHORT  ushParameter;
}
FIREi_CAMERA_TRIGGER_FEATURE_CONTROL_REGISTER, *PFIREi_CAMERA_TRIGGER_FEATURE_CONTROL_REGISTER;

/////////////////////////////////////////////////////////////
// The raw mode conversion algorithms that are implemented
/////////////////////////////////////////////////////////////
typedef UCHAR FIREi_RAW_CONVERSION_METHOD;
typedef FIREi_RAW_CONVERSION_METHOD* PFIREi_RAW_CONVERSION_METHOD;
#define raw_conv_NearestNeighbor ((UCHAR)0)
#define raw_conv_BilinearInterpolation ((UCHAR)1)
#define raw_conv_SmoothHueTransition ((UCHAR)2)

// Some additional definitions to match the specification naming.
#define FrameRate_0  fps_1_875
#define FrameRate_1  fps_3_75
#define FrameRate_2  fps_7_5
#define FrameRate_3  fps_15
#define FrameRate_4  fps_30
#define FrameRate_5  fps_60
#define FrameRate_6  fps_120
#define FrameRate_7  fps_240


/////////////////////////////////////////////////////////////////////
// The structure containing FPS specific information.
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Indicates whether the frame rate is supported by the camera or the application.
    BOOL    bSupported;

    // Self-referencing information.
    FIREi_FPS   fps;

    // The required speed for this FPS.
    TRANSMIT_SPEED    MinRate;

    // Isochronous transfer information.
    ULONG   uPacketsPerFrame;
    ULONG   uBytesPerPacket;
}
FIREi_FPS_INFO, *PFIREi_FPS_INFO;

/////////////////////////////////////////////////////////////////////
// The structure that describes the characteristics of a Video Mode.
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Indicates whether the mode is supported by the camera or the application.
    BOOL                bSupported;

    // Self-referencing information.
    FIREi_VIDEO_MODE    VideoMode;

    // The format for this mode.
    FIREi_PIXEL_FORMAT  PixelFormat;

    // The image size for this mode.
    ULONG               uWidth;
    ULONG               uHeight;

    // The frame rate information for this mode.
    FIREi_FPS_INFO      FpsInfo[8];
}
FIREi_VIDEO_MODE_INFO, *PFIREi_VIDEO_MODE_INFO;

/////////////////////////////////////////////////////////////////////
// The structure that describes the characteristics of a video format.
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Indicates whether the format is supported by the camera or the application.
    BOOL                    bSupported;

    // Self-referencing information.
    FIREi_VIDEO_FORMAT      VideoFormat;

    // The video mode information for this format
    FIREi_VIDEO_MODE_INFO   Mode[8];
}
FIREi_VIDEO_FORMAT_INFO, *PFIREi_VIDEO_FORMAT_INFO;

/////////////////////////////////////////////////////////////////////
// The camera's structure that contains all information
// about supported formats, modes and frame rates
/////////////////////////////////////////////////////////////////////
#define FIREi_CAMERA_SUPPORTED_FRAME_RATE   BYTE

typedef struct
{
    // Field mask indicating which mode is supported by the camera
    BYTE                                uMode;

    // Array of FIREi_CAMERA_SUPPORTED_FRAME_RATE's for each FrameRate
    FIREi_CAMERA_SUPPORTED_FRAME_RATE   FrameRate[8];
}
FIREi_CAMERA_SUPPORTED_MODE, *PFIREi_CAMERA_SUPPORTED_MODE;

typedef struct
{
    // Field mask indicating which format is supported by the camera
    BYTE                                uFormat;

    // Array of FIREi_CAMERA_SUPPORTED_MODE for each format
    FIREi_CAMERA_SUPPORTED_MODE         SupportedMode[8];
}
FIREi_CAMERA_SUPPORTED_FORMAT, *PFIREi_CAMERA_SUPPORTED_FORMAT;

/////////////////////////////////////////////////////////////////////
// Structure designed to contain information about Format 7
// Will be used in both FIREi_CAMERA_FORMAT_7_INQUIRY_REGISTERS and
// FIREi_CAMERA_STARTUP_INFO
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Tag. Must be set to FIREi_CAMERA_FORMAT_7_STARTUP_INFO_TAG
    // SHOULD be filled by the application
    ULONG               Tag;

    // Pixel number per frame
    // Filled by the DLL
    ULONG               PixelsPerFrame;

    // Bytes per frame
    // Filled by the DLL
    ULONGLONG           BytesPerFrame;

    // Width of requested image region (pixels)
    // Filled by the application
    USHORT              ushImageWidth;

    // Height of requested image region (pixels)
    // Filled by the application
    USHORT              ushImageHeight;

    // Left position of requested image region (pixels)
    // Filled by the application
    USHORT              ushLeftImagePosition;

    // Top position of requested image region (pixels)
    // Filled by the application
    USHORT              ushTopImagePosition;

    // Color Coding
    // Filled by the application
    FIREi_PIXEL_FORMAT  PixelFormat;

    // Packet Size
    // Filled by the application
    USHORT              ushPacketSize;

    // Number of Packets
    // Filled by the DLL
    USHORT              ushNumberOfPackets;

    // Raw Mode
    // Filled by the DLL
    FIREi_RAW_MODE      RawMode;

    // Raw Mode Conversion Method
    // Filled by the DLL
    FIREi_RAW_CONVERSION_METHOD RawConversion;
}
FIREi_CAMERA_FORMAT_7_STARTUP_INFO, *PFIREi_CAMERA_FORMAT_7_STARTUP_INFO;

//////////////////////////////////////////////////////////////////////////////
// General Structure containing ALL necessary information about Format 7    //
//////////////////////////////////////////////////////////////////////////////

typedef struct
{
    // Must be set to FIREi_CAMERA_FORMAT_7_REGISTERS_TAG
    ULONG               Tag;

    // Mode. Should be set by the application
    FIREi_VIDEO_MODE    Mode;

    // Transmission Speed. Should be set by the application
    TRANSMIT_SPEED      TransmitSpeed;

    //////////////////////////////////
    // Image related Information    //
    //////////////////////////////////

    // Maximum horizontal pixel number in image
    USHORT              ushMaxImageHSize;

    // Maximum vertical pixel number in image
    USHORT              ushMaxImageVSize;

    // Horizontal unit pixel number
    USHORT              ushUnitHSize;

    // Vertical unit pixel number
    USHORT              ushUnitVSize;

    // Horizontal unit pixel number for position
    USHORT              ushUnitHPosition;

    // Vertical unit pixel number for position
    USHORT              ushUnitVPosition;

    // Color coding (Pixel format) that are supported
    ULONG               SupportedPixelFormat;

    //////////////////////////////////
    // Packet related Information   //
    //////////////////////////////////

    // Minimum bytes per packets
    USHORT              ushUnitPacketBytes;

    // Maximum bytes per packets
    USHORT              ushMaxPacketBytes;

    // Recommended bytes per packet
    USHORT              ushRecPacketBytes;

    //////////////////////////////
    // Format 7 startup values  //
    //////////////////////////////
    PFIREi_CAMERA_FORMAT_7_STARTUP_INFO pFiFormat7StartupInfo;

}
FIREi_CAMERA_FORMAT_7_REGISTERS, *PFIREi_CAMERA_FORMAT_7_REGISTERS;

/////////////////////////////////////////////////////////////////////
// The camera's startup info structure
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Tag. Must be set to FIREi_CAMERA_STARTUP_INFO_TAG
    ULONG                   Tag;

    // Video Format
    FIREi_VIDEO_FORMAT      VideoFormat;

    // Video Mode
    FIREi_VIDEO_MODE        VideoMode;

    // Frames per second
    FIREi_FPS               FrameRate;

    // Isochronous channel
    UCHAR                   ChannelNumber;

    // Synchronization code
    UCHAR                   IsochSyCode;

    // Transmission Speed
    TRANSMIT_SPEED          TransmitSpeed;

    //////////////////////////////////////
    //  Format 7 Specific Parameter(s)  //
    //////////////////////////////////////

    // Pointer to Format 7 Startup Info struct
    // Should be provided when the camera is started
    // in Format 7
    PFIREi_CAMERA_FORMAT_7_STARTUP_INFO pFiFormat7StartupInfo;

}
FIREi_CAMERA_STARTUP_INFO, *PFIREi_CAMERA_STARTUP_INFO;


/////////////////////////////////////////////////////////////////////
// Structure that will be returned by FiGetNextCompleteFrame and will
// be used to display the frame
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // A pointer to the buffer used to hold the Camera Frame
    void*                         pCameraFrameBuffer;

    // The size in bytes of the camera Frame
    ULONG                         uFrameBufferBytes;

    // The width of the frame
    ULONG                         uFrameWidth;

    // The height of the frame
    ULONG                         uFrameHeight;

    // The number of packets that compose the frame
    ULONG                         uPackets;

    // The pixel format of the frame
    FIREi_PIXEL_FORMAT            PixelFormat;

    // A handle to the isoch request that corresponds to the camera
    // frame. This is used by the Fire-i dll in order to requeue the
    // frame for reception when FiReleaseFrame is called.
    FIREi_REQUEST_HANDLE          hFrameRequest;

    // The Isochronous channel where the frame was received from
    UCHAR                         ChannelNumber;

    // This is the current Raw Mode
    FIREi_RAW_MODE                RawMode;

    // If there is raw conversion to happen, this is the algorithm
    FIREi_RAW_CONVERSION_METHOD   RawConversion;

    // Reserved for future use
    UCHAR                         uchReserved;

    // The timestamp. This is taken when the frame is
    // actually received by the Fire-i dll. This timestamp
    // is not really accurate since it is inserted
    // when the frame is receive by the DLL. It should be
    // inserted by the camera at transmission time for accuracy.
    DWORD                         dwTimeStamp;

    // The status of the frame. If the frame was received ok this will
    // be FIREi_STATUS_SUCCESS
    FIREi_STATUS                  FireiStatus;

}
FIREi_CAMERA_FRAME, *PFIREi_CAMERA_FRAME;

/////////////////////////////////////////////////////////////////////
// Structure that will be returned by FiGetIsochEngineStats and will
// be used to monitor frame reception statistics
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // Structure Tag. Used for parameter validation
    // Must be FIREi_ISOCH_ENGINE_STATS_STRUCT_TAG
    ULONG                         Tag;

    // Holds the total received frames, including erroneous
    ULONG                         uTotalFramesReceived;

    // Holds frames that were received but not processed
    ULONG                         uDroppedFrames;

    // Holds frames that were received with error code
    // STATUS_1394_FIFO_OVERRUN
    ULONG                         uFIFOOverruns;

    // Holds frames that were received with error code
    // STATUS_1394_FIFO_UNDERRUN
    ULONG                         uFIFOUnderruns;

    // Holds frames that were received with error code
    // STATUS_1394_LONG_PACKET
    ULONG                         uLongPackets;

    // Holds frames that were received with error code
    // STATUS_1394_BUS_RESET
    ULONG                         uBusResets;

    // Holds frames that were received with error code
    // STATUS_1394_DMA_ERROR
    ULONG                         uDMAErrors;

    // Holds frames that were received with any other error code
    ULONG                         uOtherErrors;
}
FIREi_ISOCH_ENGINE_STATS, *PFIREi_ISOCH_ENGINE_STATS;

/////////////////////////////////////////////////////////////////////
// Structure that will be used for the special configuration of the camera
/////////////////////////////////////////////////////////////////////
typedef struct
{
    // 32-bit Offset of the register to write to (0xFFFF00000000 will be added)
    ULONG uOffset;

    // Value to write to the register (it will be swapped so no need to do that)
    ULONG uValue;
}
FIREi_CONFIGURATION_ENTRY, *PFIREi_CONFIGURATION_ENTRY;
