#ifndef _H_FIREIDRIVER_
#define _H_FIREIDRIVER_

#include <windows.h>
#include <stdio.h>
#include "Firei.h"

#define MAX_BUS_CAMERAS  20
#define NUM_CONTROLS 17

struct Camera
{
    // The handle to the camera
    FIREi_CAMERA_HANDLE   hCamera;

    // The camera description
    char	szCamDescription[256];
};

class FireiDriver
{
public:
	FireiDriver(){
		m_initialized = false;
	}

	void initialize(int cameraIndex);
	void cleanup();
	void capturenow(unsigned char* pimageBGRA32, int width, int height);
	void getCameraDescription(Camera* camera);
	void printCameraDescriptions();
	int setProperty(int controlIndex, int value);
	int getCurrentProperty(int controlIndex, int* value, int* isAuto);
	int queryProperty(int controlIndex, int* min, int* max);
	void setAutoProtpery(int controlIndex);

private:
	
	FIREi_CAMERA_STARTUP_INFO		m_startupInfo;
	FIREi_ISOCH_ENGINE_EX_HANDLE	m_hIsochEngine;
	Camera							m_cameraArray[MAX_BUS_CAMERAS];
	int								m_cameraIndex, m_totalCameras;
	static const FIREi_OID			m_CAMERA_CONTROLS[NUM_CONTROLS];
	static const FIREi_OID			m_CAMERA_INQ[NUM_CONTROLS];
	FIREi_CAMERA_HANDLE				*m_hCamera;
	HANDLE							m_channelStartProcessingEvent;
	bool							m_initialized;

	void initIsochEngine();
	void freeCameraHandles();
};
#endif