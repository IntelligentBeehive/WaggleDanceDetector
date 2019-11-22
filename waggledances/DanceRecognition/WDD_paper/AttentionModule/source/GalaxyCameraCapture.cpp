#include "stdafx.h"
#include "GalaxyCameraCapture.h"
#include "stdio.h"
using namespace std;

GalaxyCameraCapture::GalaxyCameraCapture()
{
}


GalaxyCameraCapture::~GalaxyCameraCapture()
{
}

void GalaxyCameraCapture::Initialize(gxstring storagePath)
{
	this->storagePath = storagePath;
}

bool GalaxyCameraCapture::StartCapture()
{
	try
	{
		cout << "Trying To start capturing..." << endl;

		// Start stream channel acquisition
		this->cameraStream->StartGrab();

		// Send acquisitionStart command
		cout << "<Send start capture command to device>" << endl;
		this->cameraFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
		this->isCapturing = true;
	}
	catch (CGalaxyException &e)
	{
		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
	}
	catch (std::exception &e)
	{
		cout << "<" << e.what() << ">" << endl;
	}

	return this->isCapturing;
}

bool GalaxyCameraCapture::Connect()
{
	bool cameraIsOpen = false, cameraStreamIsOpen = false;

	try {
		TList_vector availableDevices;
		IGXFactory::GetInstance().UpdateDeviceList(1000, availableDevices);

		// Check if found any device
		if (availableDevices.size() <= 0)
		{
			cout << "No found device!" << endl;
			return this->isOnline;
		}

		CGXDeviceInfo cameraInfo = availableDevices[0];

		// Check whether the device is Gige
		if (cameraInfo.GetDeviceClass() != GX_DEVICE_CLASS_GEV)
		{
			cout << "The device is not GEV" << endl;
			return this->isOnline;
		}

		this->deviceMAC = cameraInfo.GetMAC();

		cout << "<Open device by MAC:" << this->deviceMAC << endl;

		camera = IGXFactory::GetInstance().OpenDeviceByMAC(this->deviceMAC, GX_ACCESS_EXCLUSIVE);
		cameraIsOpen = true;
		this->cameraFeatureControlPtr = this->camera->GetRemoteFeatureControl();
		int32_t nStreamCount = this->camera->GetStreamCount();
		
		// Check if found any stream
		if (nStreamCount > 0)
		{
			this->cameraStream = this->camera->OpenStream(0);
			cameraStreamIsOpen = true;
		}
		else
		{
			throw exception("No found stream!");
		}

		this->__ChangeCameraSettings();

		// Export the parameter config file 
		cout << "<Export config file>" << endl;
		this->camera->ExportConfigFile(this->storagePath);
		
		this->onDeviceOffline = this->camera->RegisterDeviceOfflineCallback(this->onDeviceOfflineEventHandle, this);

		return true;
	}
	catch (CGalaxyException &e)
	{
		// Check whether the stream has been closed
		if (cameraStreamIsOpen)
		{
			this->cameraStream->Close();
		}

		// Check whether the device has been closed
		if (this->isOnline)
		{
			this->camera->Close();
		}
		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
		return this->isOnline;
	}
	catch (std::exception &e)
	{
		// Check whether the stream has been closed
		if (cameraStreamIsOpen)
		{
			cameraStream->Close();
		}

		// Check whether the device has been closed
		if (this->isOnline)
		{
			camera->Close();
		}
		cout << "<" << e.what() << ">" << endl;
		return this->isOnline;
	}
}

void GalaxyCameraCapture::Reconnect()
{
	if (this->Connect()) {
		if (this->StartCapture()) {
			cout << "<Capturing Restarted!>";
		}
	}
}

// TODO: make a good capture method 
//cout << "====================CGigeRecovery::__Acquisition()====================" << endl;;
//cout << "<Press any key to stop acquisition>" << endl;
//
//// Check whether the keyboard is pressed
//while (!_kbhit())
//{
//	try
//	{
//		if (m_bIsOffline)        // The device is OffLine
//		{
//			// Deal with offline
//			__ProcessOffline();
//
//			// Device recovery
//			__Recovery();
//		}
//		else                    // The device is OnLine 
//		{
//			m_objImageDataPtr = m_objStreamPtr->GetImage(500);
//			printf("Successfully get Image\n");
//		}
//	}
//	catch (CGalaxyException &e)
//	{
//		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
//	}
//	catch (std::exception &e)
//	{
//		cout << "<" << e.what() << ">" << endl;
//	}
//
//}
//_getch();

void GalaxyCameraCapture::Disconnect()
{
	try
	{
		cout << "====================CGigeRecovery::__OnCloseDevice()====================" << endl;

		// Unregister the device OffLine callback function 
		cout << "<Unregister device Offline callback>" << endl;
		this->camera->UnregisterDeviceOfflineCallback(this->onDeviceOffline);
		this->cameraStream->Close();

		// Close device
		cout << "<Close device>" << endl;
		this->camera->Close();
		this->isOnline = false;
	}
	catch (CGalaxyException &e)
	{
		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
		throw e;
	}
	catch (std::exception &e)
	{
		cout << "<" << e.what() << ">" << endl;
		throw e;
	}
}

void GalaxyCameraCapture::StopCapture()
{
	try
	{
		cout << "====================CGigeRecovery::__OnStopSnap()====================" << endl;

		// Send acquisitionStop command
		cout << "<Send stop snap command to device>" << endl;
		this->cameraFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

		// Stop stream channel acquisition
		this->cameraStream->StopGrab();
		this->isCapturing = false;
	}
	catch (CGalaxyException &e)
	{
		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
		//throw e;
	}
	catch (std::exception &e)
	{
		cout << "<" << e.what() << ">" << endl;
		//throw e;
	}
}

bool GalaxyCameraCapture::GetOnlineStatus()
{
	return this->isOnline;
}

void GalaxyCameraCapture::SetOnlineStatus(bool value)
{
	this->isOnline = value;
}

CGXStreamPointer GalaxyCameraCapture::GetStream()
{
	return this->cameraStream;
}

CImageDataPointer GalaxyCameraCapture::GetFrame()
{
	return this->cameraStream->GetImage(1000);
}

void GalaxyCameraCapture::__ChangeCameraSettings()
{	
	cout << "<Initialize the device parameters>" << endl;
	// Set the continuous frame acquisition mode
	this->cameraFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

	// Close the TriggerMode
	this->cameraFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");

	//Set heartbeat timeout for 1s
	//If you build this sample in debug mode and run it using a GigE camera device,the device will be set heartbeat timeout to 5 minutes
	//This is done to prevent the camera's heartbeat timeout from affecting the program's debugging and single stepping of execution, This also means that the camera can not be disconnected for 5 minutes unless the camera is powered off and on 
	//To work around this, the heartbeat timeout will be set to 1000 ms 
	this->cameraFeatureControlPtr->GetIntFeature("GevHeartbeatTimeout")->SetValue(1000);
}

void GalaxyCameraCapture::__ProcessOffline()
{
	try
	{
		printf("**********************Process Offline**********************\r");

		// If the device is acquiring image then stop it.
		if (this->isCapturing)
		{
			cout << "\n<Send stop snap command to device>" << endl;
			this->cameraFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
		}
	}
	catch (CGalaxyException &e)
	{
		cout << "<" << e.GetErrorCode() << ">" << "<" << e.what() << ">" << endl;
	}
	catch (std::exception &e)
	{
		cout << "<" << e.what() << ">" << endl;
	}

	try
	{
		// If the device is acquiring image then stop it.
		if (this->isCapturing)
		{
			this->cameraStream->StopGrab();
			this->isCapturing = false;
		}
	}
	catch (CGalaxyException)
	{
		//do noting
	}
	catch (std::exception)
	{
		//do noting
	}

	try
	{
		// If the device is opened then close it.
		if (this->isOnline)
		{
			// Unregister the OffLine callback function
			cout << "<Unregister device Offline callback>" << endl;
			this->camera->UnregisterDeviceOfflineCallback(this->onDeviceOffline);

			// Close stream and device
			cout << "<Close device>" << endl;
			this->cameraStream->Close();
			this->camera->Close();
			this->isOnline = false;

		}
	}
	catch (CGalaxyException)
	{
		//do noting
	}
	catch (std::exception)
	{
		//do noting
	}
}
