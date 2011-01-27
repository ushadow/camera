#include <process.h>

#include "FireiDriver.h"

/*******************************************************************************************
 * 
 * The SDK used is FireAPI 1394a/1394b development toolkit, evaluation (demo) version 5.62.
 * 2/12/2010 after changing to a new camera with the same model, the SDK is updated to 5.63. The dll
 * and lib libraries and the header files are updated.
 * 
 * This code references the sample code in 
 * "Unibrain\Fire-i API 5.60 (Dec 2008)\Samples\IIDC\DropedFrames"
 * 
 * Unibrain\Fire-i API 5.60 (Dec 2008)\doc\FireiAPISpec.chm provides detailed explanation on
 * how to use the API, especially the Fire-i ubCore DLL section. The section on Isochronous
 * Processing gives some details of capturing frames and the difference between extended 
 * and non-extended isochronous processing. Extended isochronous engine allows you to specify
 * the number of frames to queue.
 *
 ********************************************************************************************/

//
// Helper code to handle a Firei error.
//
#define _HANDLE_ERROR( status, function ) \
	if( status != FIREi_STATUS_SUCCESS ) \
   { \
   printf( "%s: %s\n", function, FiStatusString( status ) ); \
   return; \
   } 

#define QUEUED_FRAMES 20

const FIREi_OID FireiDriver::m_CAMERA_CONTROLS[NUM_CONTROLS] = {
																OID_BRIGHTNESS_CONTROL,
																OID_AUTO_EXPOSURE_CONTROL,   
																OID_SHARPNESS_CONTROL,      
																OID_UB_CONTROL,              
																OID_VR_CONTROL,              
																OID_HUE_CONTROL,             
																OID_SATURATION_CONTROL,      
																OID_GAMMA_CONTROL,           
																OID_SHUTTER_CONTROL,        
																OID_GAIN_CONTROL,            
																OID_IRIS_CONTROL,           
																OID_FOCUS_CONTROL,           
																OID_TEMPERATURE_CONTROL,    
																OID_ZOOM_CONTROL,            
																OID_PAN_CONTROL,            
																OID_TILT_CONTROL,           
																OID_OPTICAL_FILTER_CONTROL
																};


																
const FIREi_OID FireiDriver::m_CAMERA_INQ[NUM_CONTROLS] = {
															OID_BRIGHTNESS_INQ,          
															OID_AUTO_EXPOSURE_INQ,       
															OID_SHARPNESS_INQ,           
															OID_UB_INQ,                  
															OID_VR_INQ,                  
															OID_HUE_INQ,                
															OID_SATURATION_INQ,          
															OID_GAMMA_INQ,               
															OID_SHUTTER_INQ,            
															OID_GAIN_INQ,                
															OID_IRIS_INQ,                
															OID_FOCUS_INQ,               
															OID_TEMPERATURE_INQ,         
															OID_ZOOM_INQ,                
															OID_PAN_INQ,                 
															OID_TILT_INQ,                
															OID_OPTICAL_FILTER_INQ
															};

/*-----------------------------------------------------------------------------------------------*/
void FireiDriver::initialize(int cameraIndex)
{
	FIREi_CAMERA_GUID   CamGuidArray[MAX_BUS_CAMERAS];
    FIREi_STATUS        FireiStatus;
    ULONG               uCameras;
    ULONG               I;

	if(m_initialized)
		return;

	FiInitialize();

	uCameras = MAX_BUS_CAMERAS;
    FireiStatus = FiLocateCameras(CamGuidArray,FIREi_LOCATE_ALL_CAMERAS,&uCameras );
	_HANDLE_ERROR(FireiStatus, "FireiDriver::initialize()");

	m_totalCameras = 0;
	for(I=0;I<uCameras;I++)
    {
        FireiStatus = FiOpenCameraHandle(&m_cameraArray[m_totalCameras].hCamera,&CamGuidArray[I]);
		_HANDLE_ERROR(FireiStatus, "FireiDriver::initialize()");

        getCameraDescription(&m_cameraArray[m_totalCameras]);

        m_totalCameras++;
    }

	printCameraDescriptions();

   m_startupInfo.Tag = FIREi_CAMERA_STARTUP_INFO_TAG;
   m_startupInfo.FrameRate     = fps_15; //fps_30 is not supported for RGB 640x480
   m_startupInfo.VideoMode     = Mode_4; //640x480 RGB mode (24bits/pixel)
   m_startupInfo.VideoFormat   = Format_0; //VGA non-compression format
   m_startupInfo.TransmitSpeed = S200;
   m_startupInfo.IsochSyCode   = 1;
   m_startupInfo.ChannelNumber = (UCHAR)1;

	// Start the camera
   m_cameraIndex = cameraIndex;
   if(cameraIndex<m_totalCameras)
   {		
	   FireiStatus = FiStartCamera(m_cameraArray[cameraIndex].hCamera, &m_startupInfo);
	   if(FireiStatus == FIREi_STATUS_CAMERA_ALREADY_RUNNING)
	   {
			m_initialized = true;
			cleanup();
			FireiStatus = FiStartCamera(m_cameraArray[cameraIndex].hCamera, &m_startupInfo);
			_HANDLE_ERROR(FireiStatus, "FireiDriver::initialize(): restart");
	   }
	   m_hCamera = &(m_cameraArray[cameraIndex].hCamera);
   }
   else
   {
	   printf("Error: Camera index is greater than total number of cameras!\n");
	   return;
   }

   initIsochEngine();

   m_initialized = true;

   fflush(stdout);
}

/*-----------------------------------------------------------------------------------------------*/
void FireiDriver::getCameraDescription(Camera* a_Camera)
{
    char                szTmp[128];
    FIREi_STATUS        FireiStatus;
	//FIREi_CAMERA_SUPPORTED_FORMAT fcsf;

    FireiStatus = FiQueryCameraRegister( a_Camera->hCamera, 
                                         OID_VENDOR_NAME,
                                         szTmp,
                                         sizeof(szTmp));

	_HANDLE_ERROR(FireiStatus, "FireiDriver::getCameraDesription()");

    strcpy_s(a_Camera->szCamDescription,szTmp);
    strcat_s(a_Camera->szCamDescription,"  ");

    FireiStatus = FiQueryCameraRegister( a_Camera->hCamera, 
                                         OID_MODEL_NAME,
                                         szTmp,
                                         sizeof(szTmp));

    _HANDLE_ERROR(FireiStatus, "FireiDriver::getCameraDesription()");

    strcat_s(a_Camera->szCamDescription,szTmp);
    strcat_s(a_Camera->szCamDescription,"  ");

	//FireiStatus = FiQueryCameraRegister(a_Camera->hCamera,OID_CAMERA_VIDEO_FORMATS, &fcsf, sizeof(FIREi_CAMERA_SUPPORTED_FORMAT));
	//printf("Supported format: %0x\n", fcsf.uFormat);
	//printf("Supported mode for format 0: %x\n", fcsf.SupportedMode[0].uMode);
	//printf("Supported mode for mode 4: %x\n", fcsf.SupportedMode[0].FrameRate[3]);
    return; 
}

/*-----------------------------------------------------------------------------------------------*/
void FireiDriver::printCameraDescriptions()
{
    puts("******************* Bus Cameras Found ***********************");
    for(int i=0;i<m_totalCameras;i++)
    {
        if(FiIsCameraConnected(m_cameraArray[i].hCamera))
            puts(m_cameraArray[i].szCamDescription);
    }
    puts("*************************************************************");

    printf("\n\n");

    return;
}

//------------------------------------------------------------------------------------
// Create and start an isoch receive engine for the first camera found
void FireiDriver::initIsochEngine()
{
    FIREi_STATUS                FireiStatus;

    FireiStatus = FiCreateIsochReceiveEngineEx(&m_hIsochEngine,1,&m_channelStartProcessingEvent);
	_HANDLE_ERROR(FireiStatus, "FireiDriver::InitIsochEngine()");

	FireiStatus = FiAllocateFrames(m_hIsochEngine, &m_startupInfo, QUEUED_FRAMES);
	_HANDLE_ERROR(FireiStatus, "FireiDriver::InitIsochEngine()");

    FireiStatus = FiStartIsochReceiveEngineEx(m_hIsochEngine);
    _HANDLE_ERROR(FireiStatus, "FireiDriver::InitIsochEngine()");
}

void FireiDriver::cleanup()
{
	FIREi_STATUS FireiStatus;

	if(!m_initialized)
		return;

	FireiStatus = FiStopCamera(m_cameraArray[m_cameraIndex].hCamera);

	FireiStatus = FiStopIsochReceiveEngineEx(m_hIsochEngine);
	FiDeallocateFrames(m_hIsochEngine);

	FireiStatus = FiDeleteIsochReceiveEngineEx(m_hIsochEngine);

	freeCameraHandles();
	
	FiTerminate();

	m_initialized = false;

	printf("FireiDriver::cleanup: Done!\n");
	fflush(stdout);
}

void FireiDriver::freeCameraHandles()
{
	FIREi_STATUS        FireiStatus;

	for(int i=0; i<m_totalCameras; i++)
	{
		if(m_cameraArray[i].hCamera)
		{
			FireiStatus = FiCloseCameraHandle(m_cameraArray[i].hCamera);
			_HANDLE_ERROR(FireiStatus, "FireiDriver::freeCameraHandles()");
		}		
	}
}

void FireiDriver::capturenow(unsigned char* pimageBGRA32, int width, int height)
{
	PFIREi_CAMERA_FRAME		pCameraFrame;
	ULONG					uCompleteFrames;
	ULONG					I;
	PFIREi_CAMERA_FRAME		pFramesArray[QUEUED_FRAMES];	

	if(*m_hCamera)
	{
		switch(WaitForSingleObject(m_channelStartProcessingEvent, INFINITE))
		{
			case WAIT_OBJECT_0:
				
				uCompleteFrames = 0;
				//Get as many frames as possible in the buffer
				for(;;)
				{
					pCameraFrame = FiGetNextCompleteFrameEx(m_hIsochEngine);

					if(NULL == pCameraFrame)
						break;

					pFramesArray[uCompleteFrames] = pCameraFrame;
					uCompleteFrames++;
				}


				if(0==uCompleteFrames)
					printf("FireiDriver::capturenow: zero complete frames\n");

				I = 0;

				if (uCompleteFrames > 1)
                {
                        //printf("%u Frames recieved\n",uCompleteFrames);
    
                        // Requeue all the frames except for the last one
                        for(I=0;I<(uCompleteFrames - 1);I++)
                            FiReleaseFrame(pFramesArray[I]);
                }

				if(FIREi_STATUS_SUCCESS == pFramesArray[I]->FireiStatus)
				{
					int index, cameraBufferIndex, returnBufferIndex;

					for(int h = 0; h< height; h++)
						for(int w = 0; w<width; w++)
						{
							index = (w+h*width);
							cameraBufferIndex = index*3;
							returnBufferIndex = index*4;
							*(pimageBGRA32+returnBufferIndex + 3) = 0xff;
							
							//The order of bytes in the camera buffer is R,G,B,R,G,B... see document "DCAM_Spec_V1_30.pdf"
							//The order of bytes in the return buffer is BGRA. The IntBuffer is little endian.
							for(int i = 0; i<3; i++)
								*(pimageBGRA32+returnBufferIndex+i) = *((unsigned char*)(pFramesArray[I]->pCameraFrameBuffer) + cameraBufferIndex + 2 - i);
						}
					//printf("Frame received at time: %u\n",pFramesArray[I]->dwTimeStamp);
				}
				else _HANDLE_ERROR(pFramesArray[I]->FireiStatus,"FireiDriver::capturenow");

				FiReleaseFrame(pFramesArray[I]);
				break;

			default:
				break;
		}
	}

	fflush(stdout);

}

//Effects: If setting property is successful, return 0; else return -1.
int FireiDriver::setProperty(int controlIndex, int value)
{
	FIREi_CAMERA_FEATURE_CONTROL_REGISTER fcfcr;
	FIREi_STATUS	FireiStatus;

	fcfcr.Tag = FIREi_CAMERA_FEATURE_CONTROL_REGISTER_TAG;

	fcfcr.bAbsControl = FALSE;
	fcfcr.bSetOnePush = FALSE;
	fcfcr.bSetOn = TRUE;
	fcfcr.bSetAuto = FALSE;
	fcfcr.ushCurValue = value;

	FireiStatus = FiSetCameraRegister(*m_hCamera, m_CAMERA_CONTROLS[controlIndex], &fcfcr, sizeof(FIREi_CAMERA_FEATURE_CONTROL_REGISTER));
	if(FireiStatus == FIREi_STATUS_SUCCESS)
		return 0;

	printf("Failed to set property %d\n", controlIndex);
	return -1;
}

int FireiDriver::getCurrentProperty(int controlIndex, int* value, int* isAuto)
{
	FIREi_CAMERA_FEATURE_CONTROL_REGISTER fcfcr;
	FIREi_STATUS	FireiStatus;

	fcfcr.Tag = FIREi_CAMERA_FEATURE_CONTROL_REGISTER_TAG;

	FireiStatus = FiQueryCameraRegister(*m_hCamera, m_CAMERA_CONTROLS[controlIndex], &fcfcr, sizeof(FIREi_CAMERA_FEATURE_CONTROL_REGISTER));

	if(FireiStatus == FIREi_STATUS_SUCCESS)
	{
		*value = fcfcr.ushCurValue;
		*isAuto = fcfcr.bSetAuto;
		//printf("FireiDriver::getCurrentProperty value = %d, isAuto = %d\n", *value, *isAuto);
		fflush(stdout);
		return 0;
	}

	printf("Failed to get camera control property: %d \n", controlIndex);
	return -1;
}

int FireiDriver::queryProperty(int controlIndex, int* min, int* max)
{
	FIREi_CAMERA_FEATURE_INQUIRY_REGISTER fcfir;
	FIREi_STATUS	FireiStatus;

	fcfir.Tag = FIREi_CAMERA_FEATURE_INQUIRY_REGISTER_TAG;
	if(*m_hCamera)
		FireiStatus = FiQueryCameraRegister(*m_hCamera, m_CAMERA_INQ[controlIndex], &fcfir, sizeof(FIREi_CAMERA_FEATURE_INQUIRY_REGISTER));

	if(FireiStatus == FIREi_STATUS_SUCCESS && fcfir.bIsReadable)
	{
		*min = (int)fcfir.ushMinValue;
		*max = (int)fcfir.ushMaxValue;
		return 0;
	}

	return -1;
}

void FireiDriver::setAutoProtpery(int controlIndex)
{
	FIREi_CAMERA_FEATURE_CONTROL_REGISTER fcfcr;
	FIREi_STATUS	FireiStatus;

	fcfcr.Tag = FIREi_CAMERA_FEATURE_CONTROL_REGISTER_TAG;

	fcfcr.bAbsControl = FALSE;
	fcfcr.bSetOnePush = FALSE;
	fcfcr.bSetOn = TRUE;
	fcfcr.bSetAuto = TRUE;

	FireiStatus = FiSetCameraRegister(*m_hCamera, m_CAMERA_CONTROLS[controlIndex], &fcfcr, sizeof(FIREi_CAMERA_FEATURE_CONTROL_REGISTER));

	//printf("FireiDriver::setAutoProperty called\n");
}