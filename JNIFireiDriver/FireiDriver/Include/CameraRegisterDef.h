#pragma once

#define CAMERA_CSR_BASIC_FUNC_INQ           (ULONG)0x400
#define CAMERA_CSR_BRIGHTNESS_INQ           (ULONG)0x500
#define CAMERA_CSR_ZOOM_INQ                 (ULONG)0x580
#define V_FORMAT_INQ                        (ULONG)0x100
#define V_MODE_INQ_0                        (ULONG)0x180
#define V_RATE_INQ_0_0                      (ULONG)0x200

// Status and Control registers for the camera
#define CUR_V_FRM_RATE                      (ULONG)0x600
#define CUR_V_MODE                          (ULONG)0x604
#define CUR_V_FORMAT                        (ULONG)0x608
#define ISO_CHANNEL_AND_SPEED               (ULONG)0x60C
