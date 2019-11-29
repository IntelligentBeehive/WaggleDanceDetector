//------------------------------------------------------------------------
/**
\file		IGXFactory.h
\brief		Definition of IGXFactory class. Initialize library, enumerates and open devices.
\Date       2018-9-04
\Version    1.1.1809.9041
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXDeviceInfo.h"
#include "GXSmartPtr.h"
#include "IGXDevice.h"
#include "GXStringCPP.h"
#include "GXDeviceInfoVector.h"

class GXIAPICPP_API IGXFactory
{
protected:

	///Constructor
	IGXFactory(){}

	///Destructor
	virtual ~IGXFactory(){}

public:
	//----------------------------------------------------------------------------------
	/**
	\brief     Get the static instance object of IGXFactory
	\return    The static instance object of IGXFactory
	*/
	//----------------------------------------------------------------------------------
	static IGXFactory& GetInstance();

	//----------------------------------------------------------------------------------
	/**
	\brief    Initializes the GxIAPICPP runtime system
	You must call Init before calling any other functions.
	When finished you must call Uninit to free up all resources used by GxIAPICPP.
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void Init() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Frees resources allocated by the GxIAPICPP runtime system.
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieve a list of available devices. If GigE cameras are connected, this can enumerate all GigE camera devices in the same subnet. 
	\param    nTimeout[in]        Timeout for the waits in ms.
	\param    vectorDeviceInfo[int,out] A list of available devices
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void UpdateDeviceList(uint32_t nTimeout, GxIAPICPP::gxdeviceinfo_vector& vectorDeviceInfo) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Retrieve a list of available devices. If GigE cameras are connected, this can enumerate all GigE camera devices in all subnets. 
	\param    nTimeout[in]        Timeout for the waits in ms.
	\param    vectorDeviceInfo[int,out] A list of available devices
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void UpdateAllDeviceList(uint32_t nTimeout, GxIAPICPP::gxdeviceinfo_vector& vectorDeviceInfo) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Open device by IP address, if present
	\param    strIP[in]        IP address
	\param    emAccessMode[in] The access mode
	\return   A smart pointer object of IGXDevice
	*/
	//----------------------------------------------------------------------------------
	virtual CGXDevicePointer OpenDeviceByIP(const GxIAPICPP::gxstring& strIP, GX_ACCESS_MODE emAccessMode) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Open device by MAC address, if present
	\param    strIP[in]        MAC address
	\param    emAccessMode[in] The access mode
	\return   A smart pointer object of IGXDevice
	*/
	//----------------------------------------------------------------------------------
	virtual CGXDevicePointer OpenDeviceByMAC(const GxIAPICPP::gxstring& strMAC, GX_ACCESS_MODE emAccessMode) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Open device by serials number
	\param    strIP[in]        Serials number
	\param    emAccessMode[in] The access mode
	\return   A smart pointer object of IGXDevice
	*/
	//----------------------------------------------------------------------------------
	virtual CGXDevicePointer OpenDeviceBySN(const GxIAPICPP::gxstring& strSN, GX_ACCESS_MODE emAccessMode) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Open device by user defined name, if present
	\param    strIP[in]        The user defined name
	\param    emAccessMode[in] The access mode
	\return   A smart pointer object of IGXDevice
	*/
	//----------------------------------------------------------------------------------
	virtual CGXDevicePointer OpenDeviceByUserID(const GxIAPICPP::gxstring& strUserID, GX_ACCESS_MODE emAccessMode) = 0;

	// ---------------------------------------------------------------------------
		/**
		\brief       Set Device's Static IP Address
		\param[in]   strDevcieMacAddress   Device's MAC Address
		\param[in]   emIpConfigMode        IP Configure Mode(Static IP/DHCP/LLA)
		\param[in]   strIPAddress          IP Address
		\param[in]   strSubnetMask         Subnet Mask
		\param[in]   strDefaultGateway     Default Gateway
		\param[in]   strUserID             User's Name

		\retrun     void
		*/
       // ---------------------------------------------------------------------------
		virtual void GigEIpConfiguration(const GxIAPICPP::gxstring& strDeviceMacAddress, 
			GX_IP_CONFIGURE_MODE emIpConfigMode,
			const GxIAPICPP::gxstring& strIpAddress,
			const GxIAPICPP::gxstring& strSubnetMask, 
			const GxIAPICPP::gxstring& strDefaultGateway,
			const GxIAPICPP::gxstring& strUserID) = 0;

		// ---------------------------------------------------------------------------
		/**
		\brief       ForceIP
		\param[in]   strDevcieMacAddress  Device's MAC Address
		\param[in]   strIPAddress         Ip Address
		\param[in]   strSubnetMask        Subnet Mask
		\param[in]   strDefaultGateway    Default Gateway

		\retrun      void
		*/
        // ---------------------------------------------------------------------------
		virtual void GigEForceIp(const GxIAPICPP::gxstring& pszDeviceMacAddress, 
			const GxIAPICPP::gxstring& strIpAddress,
			const GxIAPICPP::gxstring& strSubnetMask, 
			const GxIAPICPP::gxstring& strDefaultGateway) = 0;

		// ---------------------------------------------------------------------------
		/**
		\brief       reset/reconnect Device
		\param[in]   pszDevcieMacAddress  Device's MAC Address
		\param[in]   ui32FeatureInfo      reset Mode

		\retrun     
		*/
		// ---------------------------------------------------------------------------
		virtual void GigEResetDevice(const GxIAPICPP::gxstring& strDeviceMacAddress, GX_RESET_DEVICE_MODE ui32FeatureInfo) = 0;

private:
	IGXFactory& operator=(const IGXFactory&);
	IGXFactory(const IGXFactory&);
};

