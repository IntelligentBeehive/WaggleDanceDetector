//------------------------------------------------------------------------
/**
\file		IGXDevice.h
\brief		Definition of the IGXDevice interface
\Date       2018-11-08
\Version    1.1.1811.9081
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXDeviceInfo.h"
#include "GXSmartPtr.h"
#include "IDeviceOfflineEventHandler.h"
#include "GXStringCPP.h"
#include "IGXStream.h"
#include "IGXFeatureControl.h"
#include "IImageProcessConfig.h"

class GXIAPICPP_API IGXDevice
{

public:
	//---------------------------------------------------------
    /**
    \brief Destructor
    */
    //---------------------------------------------------------
	virtual ~IGXDevice(){};

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns info object which stores the informations of the device, such as the device's name.
	\return   A reference to the device info object
	*/
	//----------------------------------------------------------------------------------
	virtual const CGXDeviceInfo& GetDeviceInfo() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns the number of the stream object that the camera object provides.
	\return   The number of stream object
	*/
	//----------------------------------------------------------------------------------
	virtual uint32_t GetStreamCount() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns a CGXStreamPointer object
	Stream grabbers (CGXStreamPointer) are the objects used for grabbing images
	from a camera device. A camera device might be able to send image data
	over more than one logical channel which is also called stream. A stream grabber grabs
	data from one single stream.

	\param [in]nStreamID   The number of the grabber to return
	\return A CGXStreamPointer object to a stream grabber
	*/
	//----------------------------------------------------------------------------------
	virtual CGXStreamPointer OpenStream(uint32_t nStreamID) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns the set of related local device parameters.
	\return   A CGXFeatureControlPointer object to a feature control.
	*/
	//----------------------------------------------------------------------------------
	virtual CGXFeatureControlPointer GetFeatureControl() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns the set of related remote device parameters.
	\return   A CGXFeatureControlPointer object to a feature control.
	*/
	//----------------------------------------------------------------------------------
	virtual CGXFeatureControlPointer GetRemoteFeatureControl() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Clear the receiving buffer list for the remote device's event
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void FlushEvent() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the current size of receiving buffer list for the remote device's event
	*/
	//----------------------------------------------------------------------------------
	virtual uint32_t GetEventNumInQueue() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Register the device's off-line event
	\param    pUserParam[in]        The user param can be used to distinguish different call back events
	\param    callBackFun[in]       The call back handler pointer; that must be inherited from IDeviceOfflineEventHandler
	\return   The call back handle
	*/
	//----------------------------------------------------------------------------------
	virtual GX_DEVICE_OFFLINE_CALLBACK_HANDLE RegisterDeviceOfflineCallback(IDeviceOfflineEventHandler* pEventHandler, void* pUserParam) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Unregister the device's off-line event
	\param    hCallback[in]        The call back handle
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void UnregisterDeviceOfflineCallback(GX_DEVICE_OFFLINE_CALLBACK_HANDLE hCallback) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief      Export the current feature values of a device to a config file
	\param      [in]strFilePath     The export file path
	\return     void
	*/
	//----------------------------------------------------------------------------------
	virtual void ExportConfigFile(const GxIAPICPP::gxstring& strFilePath) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief      Import a config file to the device
	\param      [in]strFilePath     The import file path
	\return     void
	*/
	//----------------------------------------------------------------------------------
	virtual void ImportConfigFile(const GxIAPICPP::gxstring& strFilePath) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Close the device
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void Close() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns a CImageProcessConfigPointer object, 
	which contains a set of set parameters for image processing. e.g. IImageData::ImageProcess 
	\return   A CImageProcessConfigPointer object
	*/
	//----------------------------------------------------------------------------------
	virtual CImageProcessConfigPointer CreateImageProcessConfig() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief      Export the current feature values of a device to a config file
	\param      [in]strFilePath     The export file path
	\return     void
	*/
	//----------------------------------------------------------------------------------
	virtual void ExportConfigFileW(const wchar_t* pchWFilePath) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief      Import a config file to the device
	\param      [in]strFilePath     The import file path
	\return     void
	*/
	//----------------------------------------------------------------------------------
	virtual void ImportConfigFileW(const wchar_t*  pchWFilePath) = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IGXDevice>;
typedef GXSmartPtr<IGXDevice>            CGXDevicePointer;