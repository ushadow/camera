#pragma once

/*
    Shared enum definitions between DirectShow and Firei.DLL headers
*/

/////////////////////////////////////////////////////////////////////
// The known pixel encoding formats.
/////////////////////////////////////////////////////////////////////
typedef enum
{
    ILLEGAL_PIXEL_FORMAT = -1,
    pixel_format_none = -1,
    Y_MONO = 0,     //the order of the pixel formats matters.
    YUV_411 = 1,	//as it is, it resembles the order of the color codings
    YUV_422 = 2,	//in the COLOR_CODING_INQ register of the FORMAT7 related registers
    YUV_444 = 3,	//this order is used to determine if for example F7Mx supports YUV411
    RGB_24 = 4,		//by checking bit[YUV_411] of the COLOR_CODING_INQ registers
    Y_MONO_16 = 5,	//it is also used to set the COLOR_CODING_ID as it is, for example
    RGB_48 = 6,		//YUV411=1 and 1 corresponds to the COLOR_CODING_ID for YUV_411.
    Y_MONO_16_SIGNED = 7,
    S_Y_MONO_16 = 7,
    RGB_48_SIGNED = 8,
    S_RGB_48 = 8,
    RAW_8 = 9,
    RAW_16 = 10
}
FIREi_PIXEL_FORMAT, *PFIREi_PIXEL_FORMAT;

#ifdef __cplusplus
inline FIREi_PIXEL_FORMAT operator++( FIREi_PIXEL_FORMAT &rs, int )
{
    rs = (FIREi_PIXEL_FORMAT)(rs + 1);

    return rs;
}
#endif

//--------------------------------------------
// DirectShow resolutions
//--------------------------------------------
typedef enum
{
    res_none = -1,
    res_160x120 = 0,
    res_320x240,
    res_640x480,
    res_800x600,
    res_1024x768,
    res_1280x960,
    res_1600x1200,
    res_variable,
    res_variable_1,
    res_variable_2,
    res_variable_3,
    res_variable_4,
    res_variable_5,
    res_variable_6,
    res_variable_7
} 
FIREi_RES, *PFIREi_RES;

#ifdef __cplusplus
inline FIREi_RES operator++( FIREi_RES &rs, int )
{
    rs = (FIREi_RES)(rs + 1);

    return rs;
}
#endif

/////////////////////////////////////////////////////////////////////
// The defined FPS rates
/////////////////////////////////////////////////////////////////////
typedef enum
{
    fps_none = -1,
    fps_1_875 = 0,
    fps_3_75,
    fps_7_5,
    fps_15,
    fps_30,
    fps_60,
    fps_120,
    fps_240
}
FIREi_FPS, *PFIREi_FPS;

#ifdef __cplusplus
inline FIREi_FPS operator++( FIREi_FPS &rs, int )
{
    rs = (FIREi_FPS)(rs + 1);

    return rs;
}
#endif

/////////////////////////////////////////////////////////////////////
// The known raw mode conversion color filters
/////////////////////////////////////////////////////////////////////
typedef UCHAR FIREi_RAW_MODE;
typedef FIREi_RAW_MODE* PFIREi_RAW_MODE;
#define raw_mode_none ((UCHAR)0)
#define raw_mode_rggb ((UCHAR)1)
#define raw_mode_grbg ((UCHAR)2)
#define raw_mode_gbrg ((UCHAR)3)
#define raw_mode_bggr ((UCHAR)4)

/////////////////////////////////////////////////////////////////////
// The defined Video Formats
/////////////////////////////////////////////////////////////////////
typedef enum
{
    Format_0 = 0,
    Format_1 = 1,
    Format_2 = 2,
    Format_6 = 6,
    Format_7 = 7
}
FIREi_VIDEO_FORMAT, *PFIREi_VIDEO_FORMAT;

#ifdef __cplusplus
inline FIREi_VIDEO_FORMAT operator++( FIREi_VIDEO_FORMAT &vf, int )
{
    vf = (FIREi_VIDEO_FORMAT)(vf + 1);

    return vf;
}
#endif

/////////////////////////////////////////////////////////////////////
// The defined Video Modes
/////////////////////////////////////////////////////////////////////
typedef enum
{
    Mode_0=0,
    Mode_1,
    Mode_2,
    Mode_3,
    Mode_4,
    Mode_5,
    Mode_6,
    Mode_7
}
FIREi_VIDEO_MODE, *PFIREi_VIDEO_MODE;

#ifdef __cplusplus
inline FIREi_VIDEO_MODE operator++( FIREi_VIDEO_MODE &vm, int )
{
    vm = (FIREi_VIDEO_MODE)(vm + 1);

    return vm;
}
#endif

//-----------------------------------------------------------------------
typedef enum
{
    FiExpoControl_Autoexp=0,
    FiExpoControl_Shutter,
    FiExpoControl_Gain,
    FiExpoControl_Iris
} 
FiExpoControlProperty;

//-----------------------------------------------------------------------
typedef enum
{
    FiColorControl_UB=0,
    FiColorControl_VR,
    FiColorControl_Hue,
    FiColorControl_Saturation
} 
FiColorControlProperty;

//-----------------------------------------------------------------------
typedef enum
{
    FiBasicControl_Focus=0,
    FiBasicControl_Zoom,
    FiBasicControl_Brightness,
    FiBasicControl_Sharpness,
    FiBasicControl_Gamma
}
FiBasicControlProperty;

