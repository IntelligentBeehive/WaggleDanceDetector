#pragma once
#include "GalaxyIncludes.h"
#include "conio.h"
#include <iostream>
//D:\lib\openblas\include;D:\lib\openblas\lib;
class CameraOfflineEventHandle :public IDeviceOfflineEventHandler
{
public:
	void DoOnDeviceOfflineEvent(void* pUserParam)
	{
		try
		{
			//GalaxyCameraCapture* pGigeRecovery = (GalaxyCameraCapture*)pUserParam;
			//pGigeRecovery->SetOnlineStatus(true);
			//std::cout << "**********************Device offline**********************" << std::endl;
		}
		catch (CGalaxyException) {}
		catch (std::exception) {}
	}
};

class GalaxyCameraCapture
{
public:
	GalaxyCameraCapture();
	~GalaxyCameraCapture();
	void Initialize(gxstring storagePath);
	bool StartCapture();
	bool Connect();
	void Disconnect();

	void StopCapture();
	bool GetOnlineStatus();
	void SetOnlineStatus(bool value);
	CGXStreamPointer GetStream();
	CImageDataPointer GetFrame();
	CameraOfflineEventHandle* onDeviceOfflineEventHandle;
private:
	bool isOnline;
	bool isCapturing;
	gxstring storagePath;
	gxstring deviceMAC;
	CGXDevicePointer camera;
	CGXFeatureControlPointer cameraFeatureControlPtr;
	CGXStreamPointer cameraStream;

	GX_DEVICE_OFFLINE_CALLBACK_HANDLE onDeviceOffline;

	void __ChangeCameraSettings();
	void __ProcessOffline();
	void Reconnect();
};
