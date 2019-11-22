//------------------------------------------------------------------------
/**
\file		IGXDeviceInfo.h
\brief		Holds information about an enumerated device
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXStringCPP.h"

class GXIAPICPP_API IGXDeviceInfo
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IGXDeviceInfo(){};

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the vendor name of the device.
	\return   The vendor name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetVendorName() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the model name of the device.
	\return   The model name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetModelName() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the serial number of the device.
	\return   The serial number
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetSN() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the display name of the device.
	\return   The display name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetDisplayName() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the device id of the device.
	\return   The device id
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetDeviceID() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the user defined name of the device if present.
	\return   The user defined name
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetUserID() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the current access status of the device(for example, read only\read and write\no access).
	\return   The current access status
	*/
	//----------------------------------------------------------------------------------
	virtual GX_ACCESS_STATUS GetAccessStatus() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the class of the device(for example, USB2.0\Gige\USB3.0).
	\return   The device class
	*/
	//----------------------------------------------------------------------------------
	virtual GX_DEVICE_CLASS_LIST GetDeviceClass() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the MAC address of the device if present.
	\return   The MAC address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetMAC() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the IP address of the device if present.
	\return   The IP address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetIP() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief   Retrieves the subnet mask address of the device if present.
	\return  The subnet mask
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetSubnetMask() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the gateway of the device if present.
	\return   The gateway
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetGateway() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's MAC address of the device if present.
	\return   The NIC's MAC address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICMAC() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's IP address of the device if present.
	\return   The NIC's IP address
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICIP() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's subnet mask address of the device if present.
	\return   The NIC's subnet mask
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICSubnetMask() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's gateway of the device if present.
	\return   The NIC's gateway
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICGateway() const = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieves the NIC's description of the device if present.
	\return   The NIC's description
	*/
	//----------------------------------------------------------------------------------
	virtual GxIAPICPP::gxstring GetNICDescription() const = 0;
};