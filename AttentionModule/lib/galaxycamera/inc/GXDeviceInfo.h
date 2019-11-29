//------------------------------------------------------------------------
/**
\file		GXDeviceInfo.h
\brief		The device enumeration process creates a list of CGXDeviceInfo objects 
(GxIAPICPP::gxdeviceinfo_vector). Each CGXDeviceInfo object stores the information of a device.
The information is retrieved during the device enumeration process (IGXFactory::UpdateDeviceList)
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "IGXDeviceInfo.h"
#include "GXSmartPtr.h"

#pragma warning(push)
#pragma warning(disable: 4251) // class 'xxx' needs to have dll-interface to be used by clients of class 'yyy'

class IGXDeviceInfoImpl;
typedef GXSmartPtr<IGXDeviceInfoImpl> CGXDeviceInfoImplPointer;

class GXIAPICPP_API CGXDeviceInfo : public IGXDeviceInfo
{
public:
	//Constructor
	CGXDeviceInfo();

	///Constructor
    CGXDeviceInfo(CGXDeviceInfoImplPointer& objCGXDeviceInfoImplPointer);

	///Destructor
	virtual ~CGXDeviceInfo(void);

public:
	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the vendor name of the device.
	\return   The vendor name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetVendorName() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the model name of the device.
	\return   The model name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetModelName() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the serial number of the device.
	\return   The serial number
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetSN() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the display name of the device.
	\return   The display name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetDisplayName() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the device id of the device.
	\return   The device id
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetDeviceID() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the user defined name of the device if present.
	\return   The user defined name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetUserID() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the current access status of the device(e.g. read only, read & write, or no access).
	\return   The current access status
	*/
	//----------------------------------------------------------------------------------
	virtual GX_ACCESS_STATUS GetAccessStatus() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the class of the device(e.g. USB2.0\Gige\USB3.0).
	\return   The device class
	*/
	//----------------------------------------------------------------------------------
	virtual GX_DEVICE_CLASS_LIST GetDeviceClass() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the MAC address of the device if present.
	\return   The MAC address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetMAC() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the IP address of the device if present.
	\return   The IP address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetIP() const;

	//----------------------------------------------------------------------------------
	/**
	\brief   Retrieves the subnet mask address of the device if present.
	\return  The subnet mask
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetSubnetMask() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the gateway of the device if present.
	\return   The gateway
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetGateway() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's MAC address of the device if present.
	\return   The NIC's MAC address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICMAC() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's IP address of the device if present.
	\return   The NIC's IP address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICIP() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's subnet mask address of the device if present.
	\return   The NIC's subnet mask
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICSubnetMask() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's gateway of the device if present.
	\return   The NIC's gateway
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICGateway() const;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's description of the device if present.
	\return   The NIC's description
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICDescription() const;

	
private:
	CGXDeviceInfoImplPointer        m_CGXDeviceInfoImplPointer;           ///< Internal use only
};

#pragma warning(pop)