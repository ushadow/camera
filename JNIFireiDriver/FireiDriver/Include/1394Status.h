#pragma once
/*
    1394Status.h

    DESCRIPTION
      This file is the Windows NT version of the definitions of the error codes that we will be using.

*/

#if defined(C1394_CLASS_DRIVER) || defined(C1394_CLIENT_DRIVER) || defined(C1394_MINIPORT_DRIVER)
#include <ntddk.h>
#else
// Copied from NTDDK.H
#define FACILITY_IO_ERROR_CODE           0x4
#define STATUS_SEVERITY_ERROR            0x3
#if !defined(STATUS_SUCCESS)
#ifdef SWIG
#define STATUS_SUCCESS                   (0)
#else
#define STATUS_SUCCESS                   (0L)
#endif
#endif
#endif

/*
    (Copied from NTSTATUS.H for easy reference)

    //
    //  Values are 32 bit values layed out as follows:
    //
    //   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
    //   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
    //  +---+-+-+-----------------------+-------------------------------+
    //  |Sev|C|R|     Facility          |               Code            |
    //  +---+-+-+-----------------------+-------------------------------+
    //
    //  where
    //
    //      Sev - is the severity code
    //
    //          00 - Success
    //          01 - Informational
    //          10 - Warning
    //          11 - Error
    //
    //      C - is the Customer code flag
    //
    //      R - is a reserved bit
    //
    //      Facility - is the facility code
    //
    //      Code - is the facility's status code
    //
    //
    // Define the facility codes
    //
    #define FACILITY_RPC_STUBS               0x3
    #define FACILITY_RPC_RUNTIME             0x2
    #define FACILITY_IO_ERROR_CODE           0x4


    //
    // Define the severity codes
    //
    #define STATUS_SEVERITY_WARNING          0x2
    #define STATUS_SEVERITY_SUCCESS          0x0
    #define STATUS_SEVERITY_INFORMATIONAL    0x1
    #define STATUS_SEVERITY_ERROR            0x3

*/

#ifdef SWIG
#define MAKE_ERROR_CODE(code)     \
    unchecked((int)(((((ulong)(STATUS_SEVERITY_ERROR))<<30) | (1<<29) | (((ulong)FACILITY_IO_ERROR_CODE)<<16)| (code))))
#else
#define MAKE_ERROR_CODE(code)     \
    (((((ULONG)(STATUS_SEVERITY_ERROR))<<30) | (1<<29) | (((ULONG)FACILITY_IO_ERROR_CODE)<<16)| (code)))
#endif

typedef enum tagSTATUS_1394
{
    STATUS_1394_SUCCESS                             = STATUS_SUCCESS,
    FIREi_STATUS_SUCCESS                            = STATUS_SUCCESS,
    STATUS_1394_ABORTED                             = MAKE_ERROR_CODE(0x0100L),
    STATUS_1394_ADAPTER_ERROR                       = MAKE_ERROR_CODE(0x0200L),
    STATUS_1394_ALREADY_OPEN                        = MAKE_ERROR_CODE(0x0250L),
    STATUS_1394_BR_LIMIT                            = MAKE_ERROR_CODE(0x0270L),
    STATUS_1394_BUS_RESET                           = MAKE_ERROR_CODE(0x0300L),
    STATUS_1394_CONFLICT                            = MAKE_ERROR_CODE(0x0350L),
    STATUS_1394_CRC_ERROR                           = MAKE_ERROR_CODE(0x0370L),
    STATUS_1394_CRITICAL_ADAPTER_ERROR              = MAKE_ERROR_CODE(0x0400L),
    STATUS_1394_DEVICE_BUSY                         = MAKE_ERROR_CODE(0x0500L),
    STATUS_1394_DEVICE_NOT_FOUND                    = MAKE_ERROR_CODE(0x0550L),
    STATUS_1394_DMA_LIMIT                           = MAKE_ERROR_CODE(0x0560L),
    STATUS_1394_DMA_ERROR                           = MAKE_ERROR_CODE(0x0572L),
    // Don't insert anything between DMA_ERROR and INTERNAL_ERROR
    STATUS_1394_DRIVER_INTERNAL_ERROR               = MAKE_ERROR_CODE(0x0600L),
    STATUS_1394_DUPLICATE_CHANNEL                   = MAKE_ERROR_CODE(0x0639L),
    STATUS_1394_FIFO_OVERRUN                        = MAKE_ERROR_CODE(0x0645L),
    STATUS_1394_FIFO_UNDERRUN                       = MAKE_ERROR_CODE(0x0658L),
    STATUS_1394_GAP_COUNT_ERROR                     = MAKE_ERROR_CODE(0x0671L),
    STATUS_1394_INCORRECT_RESPONSE                  = MAKE_ERROR_CODE(0x06B2L),
    STATUS_1394_INSUFFICIENT_RESOURCES              = MAKE_ERROR_CODE(0x0700L),
    STATUS_1394_INVALID_BUFFER_SIZE                 = MAKE_ERROR_CODE(0x0800L),
    STATUS_1394_INVALID_CHANNEL_TYPE                = MAKE_ERROR_CODE(0x0900L),
    STATUS_1394_INVALID_CHANNEL_STATE               = MAKE_ERROR_CODE(0x0A00L),
    FIREi_STATUS_INVALID_PARAMETER                  = MAKE_ERROR_CODE(0x0A01L),
    FIREi_STATUS_NO_MEMORY                          = MAKE_ERROR_CODE(0x0A02L),
    FIREi_STATUS_INTERNAL_ERROR                     = MAKE_ERROR_CODE(0x0A03L),
    FIREi_STATUS_ACCESS_VIOLATION                   = MAKE_ERROR_CODE(0x0A04L),
    FIREi_STATUS_UNSUCCESSFUL                       = MAKE_ERROR_CODE(0x0A05L),
    FIREi_BUFFER_TOO_SMALL                          = MAKE_ERROR_CODE(0x0A06L),
    STATUS_1394_INVALID_DEVICE_STATE                = MAKE_ERROR_CODE(0x0B00L),
    STATUS_1394_INVALID_HANDLE                      = MAKE_ERROR_CODE(0x0C00L),
    FIREi_STATUS_BUS_RESET                          = MAKE_ERROR_CODE(0x0C01L),
    FIREi_STATUS_ADAPTER_ERROR                      = MAKE_ERROR_CODE(0x0C02L),
    FIREi_STATUS_CAMERA_READ_FAIL                   = MAKE_ERROR_CODE(0x0C03L),
    FIREi_STATUS_CAMERA_WRITE_FAIL                  = MAKE_ERROR_CODE(0x0C04L),
    FIREi_STATUS_CAMERA_ALREADY_RUNNING             = MAKE_ERROR_CODE(0x0C05L),
    FIREi_STATUS_CAMERA_UNSUPPORTED_FEATURE         = MAKE_ERROR_CODE(0x0C06L),
    FIREi_STATUS_FEATURE_INVALID_VALUE              = MAKE_ERROR_CODE(0x0C07L),
    FIREi_STATUS_UNDEFINED_OID                      = MAKE_ERROR_CODE(0x0C08L),
    STATUS_1394_INVALID_ISOCHRONOUS_BUFFERS         = MAKE_ERROR_CODE(0x0D00L),
    FIREi_STATUS_DDRAWINITFAILED                    = MAKE_ERROR_CODE(0x0D01L),
    FIREi_STATUS_WINDOW_TOO_SMALL                   = MAKE_ERROR_CODE(0x0D02L),
    FIREi_STATUS_DISPLAY_TOO_SMALL                  = MAKE_ERROR_CODE(0x0D03L),
    FIREi_STATUS_NO_STRETCHING_SUPPORT              = MAKE_ERROR_CODE(0x0D04L),
    STATUS_1394_INVALID_OFFSET                      = MAKE_ERROR_CODE(0x0D47L),
    STATUS_1394_INVALID_PARAMETER                   = MAKE_ERROR_CODE(0x0E00L),
    FIREi_STATUS_TIMEOUT                            = MAKE_ERROR_CODE(0x0E01L),
    FIREi_CHANNEL_ALLOCATION_FAILED                 = MAKE_ERROR_CODE(0x0E02L),
    FIREi_CHANNEL_ALOCATION_FAILED                  = FIREi_CHANNEL_ALLOCATION_FAILED, // For backwards source compatibility
    FIREi_STATUS_COULD_NOT_QUEUE_FRAMES             = MAKE_ERROR_CODE(0x0E03L),
    FIREi_NO_FRAMES_RECEIVED                        = MAKE_ERROR_CODE(0x0E04L),
    FIREi_STATUS_BAD_FRAME                          = MAKE_ERROR_CODE(0x0E05L),
    FIREi_STATUS_NO_FRAMES_ALOCATED                 = MAKE_ERROR_CODE(0x0E06L),
    FIREi_STATUS_ENGINE_STARTED                     = MAKE_ERROR_CODE(0x0E07L),
    FIREi_STATUS_FRAMES_ALREADY_ALLOCATED           = MAKE_ERROR_CODE(0x0E08L),
    FIREi_STATUS_LONG_PACKET                        = MAKE_ERROR_CODE(0x0E09L),
    STATUS_1394_INVALID_REQUEST                     = MAKE_ERROR_CODE(0x0F00L),
    STATUS_1394_INVALID_RESPONSE                    = MAKE_ERROR_CODE(0x0F50L),
    STATUS_1394_LOCK_FAILED                         = MAKE_ERROR_CODE(0x0F73L),
    STATUS_1394_LONG_PACKET                         = MAKE_ERROR_CODE(0x0F8AL),
    STATUS_1394_NO_MEMORY                           = MAKE_ERROR_CODE(0x1000L),
    STATUS_1394_NOT_FOUND                           = MAKE_ERROR_CODE(0x1070L),
    STATUS_1394_NOT_IMPLEMENTED                     = MAKE_ERROR_CODE(0x1100L),
    STATUS_1394_NOT_SUPPORTED                       = MAKE_ERROR_CODE(0x1200L),
    STATUS_1394_OLDER_VERSION                       = MAKE_ERROR_CODE(0x1242L),
    STATUS_1394_PENDING                             = MAKE_ERROR_CODE(0x1300L),
    STATUS_1394_SELFID_ERROR                        = MAKE_ERROR_CODE(0x1313L),
    STATUS_1394_SIZE_LIMITATION                     = MAKE_ERROR_CODE(0x132AL),
    STATUS_1394_SPEED_LIMITATION                    = MAKE_ERROR_CODE(0x1350L),
    STATUS_1394_TIMEOUT                             = MAKE_ERROR_CODE(0x1400L),
    STATUS_1394_TOPOLOGY_ERROR                      = MAKE_ERROR_CODE(0x1409L),
    STATUS_1394_TRANSACTION_FAILED                  = MAKE_ERROR_CODE(0x1433L),
    STATUS_1394_UNSOLICITED_RESPONSE                = MAKE_ERROR_CODE(0x1450L),
    STATUS_1394_UNSUCCESSFUL                        = MAKE_ERROR_CODE(0x1500L),
}
STATUS_1394, FIREi_STATUS;

