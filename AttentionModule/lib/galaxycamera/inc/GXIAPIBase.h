//------------------------------------------------------------------------
/**
\file		GXIAPIBase.h
\brief		Platform-dependent type definitions
\Date       2018-9-05
\Version    1.1.1809.9051
*/
//------------------------------------------------------------------------

#ifndef GXIAPI_BASE_H
#define GXIAPI_BASE_H

#if defined(_WIN32)
#ifndef _STDINT_H 
#ifdef _MSC_VER // Microsoft compiler
#if _MSC_VER < 1600
typedef __int8            int8_t;   ///< makes int 8 portable across different platforms
typedef __int16           int16_t;  ///< makes short portable across different platforms
typedef __int32           int32_t;  ///< makes __int32 portable across different platforms
typedef __int64           int64_t;  ///< makes int64 portable across different platforms
typedef unsigned __int8   uint8_t;  ///< makes unsigned char portable across different platforms
typedef unsigned __int16  uint16_t; ///< makes unsigned short portable across different platforms
typedef unsigned __int32  uint32_t; ///< makes unsigned int32 portable across different platforms
typedef unsigned __int64  uint64_t; ///< makes unsigned int64 portable across different platforms
#else
// stdint.h is already included in Visual Studio 2010 
#include <stdint.h>
#endif
#else
// Not a Microsoft compiler
#include <stdint.h>
#endif
#endif 
#else
// Linux
#include <stdint.h>
#endif

#ifdef GXIAPICPP_EXPORTS
#define GXIAPICPP_API __declspec(dllexport)
#else
#define GXIAPICPP_API __declspec(dllimport)
#endif

//------------------------------------------------------------------------------
//  The error codes list
//------------------------------------------------------------------------------
typedef enum GX_STATUS_LIST
{
	GX_STATUS_SUCCESS                =  0,           ///< Operation was successful; no error occurred.
	GX_STATUS_ERROR                  = -1,           ///< Unspecified runtime error.
	GX_STATUS_NOT_FOUND_TL           = -2,           ///< Special error code for initialize, when IGXFactory::Init was called.
	GX_STATUS_NOT_FOUND_DEVICE       = -3,           ///< Special error code for opening device, when IGXFactory::OpenDeviceByxxx was called.
	GX_STATUS_OFFLINE                = -4,           ///< Communication error has occurred; e.g. a read or write operation failed.
	GX_STATUS_INVALID_PARAMETER      = -5,           ///< One of the parameters given was not valid or out of range.
	GX_STATUS_INVALID_HANDLE         = -6,           ///< Given handle does not support the operation; e.g. function call on wrong handle or NULL pointer.
	GX_STATUS_INVALID_CALL           = -7,           ///< Requested operation is not allowed, special for interface; e.g. callback capture and the getimage can not be used at the same time.
	GX_STATUS_INVALID_ACCESS         = -8,           ///< Requested operation is not allowed, special for camera; e.g. a remote device has be opened by another client.
	GX_STATUS_NEED_MORE_BUFFER       = -9,           ///< A provided buffer is too small to receive the expected amount of data.
	GX_STATUS_ERROR_TYPE             = -10,          ///< Special error code for IGXFeatureControl::GetxxxFeature(); e.g. code like this "GetIntFeature("Gain")" is wrong, because "Gain" is an fload feature.
	GX_STATUS_OUT_OF_RANGE           = -11,          ///< A given value is out of range; e.g. IIntFeautre::SetValue() had been set an value bigger than the Max Value.
	GX_STATUS_NOT_IMPLEMENTED        = -12,          ///< Requested operation is not implemented; e.g. no color feature on Mono Camera.
	GX_STATUS_NOT_INIT_API           = -13,          ///< A module or resource is not initialized; e.g. IGXFactory::Init was not called.
	GX_STATUS_TIMEOUT                = -14,          ///< An operation's timeout time expired before it could be completed.		
}GX_STATUS_LIST;
typedef int32_t GX_STATUS;

//------------------------------------------------------------------------------
//  Used for open device interface; IGXFactory::OpenDeviceByxxx
//------------------------------------------------------------------------------
typedef enum GX_ACCESS_MODE
{
	GX_ACCESS_READONLY      =2,        ///< Open a device read only. All Port functions can only read from the device.
	GX_ACCESS_CONTROL       =3,        ///< Open a device in a way that other hosts/processes can have read only access to the device. Device's access level is read/write for this process.
	GX_ACCESS_EXCLUSIVE     =4,        ///< Open a device in a way that only this host/process can have access to the device. Device's access level is read/write for this process.
}GX_ACCESS_MODE;
typedef int32_t GX_ACCESS_MODE_CMD;

//------------------------------------------------------------------------------
//  Used for CGXDeviceInfo
//------------------------------------------------------------------------------
typedef enum  GX_DEVICE_CLASS_LIST
{
	GX_DEVICE_CLASS_UNKNOWN = 0,     ///< Not used in a command. Can be used to initialize a variable to query that information
	GX_DEVICE_CLASS_USB2    = 1,     ///< USB2.0 Cameras
	GX_DEVICE_CLASS_GEV     = 2,     ///< GigE Vision Cameras
	GX_DEVICE_CLASS_U3V     = 3,     ///< USB3.0 Cameras
}GX_DEVICE_CLASS_LIST;
typedef  int32_t GX_DEVICE_CLASS;

//------------------------------------------------------------------------------
//  Used for CGXDeviceInfo
//------------------------------------------------------------------------------
typedef enum  GX_ACCESS_STATUS
{
	GX_ACCESS_STATUS_UNKNOWN    = 0,   ///< Not used in a command. Can be used to initialize a variable to query that information
	GX_ACCESS_STATUS_READWRITE  = 1,   ///< Device can be read and write
	GX_ACCESS_STATUS_READONLY   = 2,   ///< Device can only be read
	GX_ACCESS_STATUS_NOACCESS   = 3,   ///< Device no access
}GX_ACCESS_STATUS;
typedef int32_t GX_ACCESS_STATUS_CMD;

//------------------------------------------------------------------------------
//  Used for IImageData::GetStatus 
//------------------------------------------------------------------------------
typedef enum GX_FRAME_STATUS_LIST
{
	GX_FRAME_STATUS_SUCCESS          = 0,     ///< Flag to indicate that a buffer was filled completed.
	GX_FRAME_STATUS_INCOMPLETE       = -1,    ///< Flag to indicate that a buffer was filled but an error occurred during that process.
}GX_FRAME_STATUS_LIST;
typedef  int32_t  GX_FRAME_STATUS;

//------------------------------------------------------------------------------
//  IP Confingure Mode
//------------------------------------------------------------------------------
enum GX_IP_CONFIGURE_MODE_LIST
{
	GX_IP_CONFIGURE_DHCP       = 6,   ///< Enable DHCP
	GX_IP_CONFIGURE_LLA        = 4,   ///< LLA
	GX_IP_CONFIGURE_STATIC_IP  = 5,   ///< Static IP
	GX_IP_CONFIGURE_DEFAULT    = 7,   ///< Default
};
typedef int32_t GX_IP_CONFIGURE_MODE;

//------------------------------------------------------------------------------
//  Used for IGXFeatureControl::GetFeatureType 
//------------------------------------------------------------------------------
typedef enum GX_FEATURE_TYPE
{
	GX_FEATURE_INT				   =0x10000000,  ///< Int feature
	GX_FEATURE_FLOAT               =0X20000000,  ///< Float feature
	GX_FEATURE_ENUM				   =0x30000000,  ///< Enum feature
	GX_FEATURE_BOOL				   =0x40000000,  ///< Bool feature
	GX_FEATURE_STRING			   =0x50000000,  ///< String feature
	GX_FEATURE_BUFFER			   =0x60000000,  ///< Register feature
	GX_FEATURE_COMMAND			   =0x70000000,  ///< Command feature
}GX_FEATURE_TYPE;

#define GX_PIXEL_MONO                  ( 0x01000000 )
#define GX_PIXEL_COLOR                 ( 0x02000000 )

#define GX_PIXEL_8BIT                  ( 0x00080000 )
#define GX_PIXEL_10BIT                 ( 0x000A0000 )
#define GX_PIXEL_12BIT                 ( 0x000C0000 )
#define GX_PIXEL_16BIT                 ( 0x00100000 )
#define GX_PIXEL_24BIT                 ( 0x00180000 )
#define GX_PIXEL_30BIT                 ( 0x001E0000 )
#define GX_PIXEL_32BIT                 ( 0x00200000 )
#define GX_PIXEL_36BIT                 ( 0x00240000 )
#define GX_PIXEL_48BIT                 ( 0x00300000 )
#define GX_PIXEL_64BIT                 ( 0x00400000 )

//------------------------------------------------------------------------------
//  Used for IImageData::GetPixelFormat 
//------------------------------------------------------------------------------
typedef enum GX_PIXEL_FORMAT_ENTRY
{
	GX_PIXEL_FORMAT_UNDEFINED          = (0),
	GX_PIXEL_FORMAT_MONO8              = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0001),//0x1080001,
	GX_PIXEL_FORMAT_MONO8_SIGNED       = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0002),//0x1080002,
	GX_PIXEL_FORMAT_MONO10             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0003),//0x1100003,	
	GX_PIXEL_FORMAT_MONO12             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0005),//0x1100005,	
	GX_PIXEL_FORMAT_MONO14             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0025),//0x1100025,
	GX_PIXEL_FORMAT_MONO16             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0007),//0x1100007,
	GX_PIXEL_FORMAT_BAYER_GR8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0008),//0x1080008,               
	GX_PIXEL_FORMAT_BAYER_RG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0009),//0x1080009,                
	GX_PIXEL_FORMAT_BAYER_GB8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000A),//0x108000A,
	GX_PIXEL_FORMAT_BAYER_BG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000B),//0x108000B,
	GX_PIXEL_FORMAT_BAYER_GR10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000C),//0x110000C,                
	GX_PIXEL_FORMAT_BAYER_RG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000D),//0x110000D,
	GX_PIXEL_FORMAT_BAYER_GB10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000E),//0x110000E,
	GX_PIXEL_FORMAT_BAYER_BG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000F),//0x110000F,
	GX_PIXEL_FORMAT_BAYER_GR12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0010),//0x1100010,              
	GX_PIXEL_FORMAT_BAYER_RG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0011),//0x1100011,
	GX_PIXEL_FORMAT_BAYER_GB12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0012),//0x1100012,
	GX_PIXEL_FORMAT_BAYER_BG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0013),//0x1100013,	
	GX_PIXEL_FORMAT_BAYER_GR16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002E),//0x110002E,                
	GX_PIXEL_FORMAT_BAYER_RG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002F),//0x110002F,
	GX_PIXEL_FORMAT_BAYER_GB16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0030),//0x1100030,
	GX_PIXEL_FORMAT_BAYER_BG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0031),//0x1100031,	
	GX_PIXEL_FORMAT_RGB8_PLANAR        = (GX_PIXEL_COLOR | GX_PIXEL_24BIT | 0x0021),//0x2180021,
	GX_PIXEL_FORMAT_RGB10_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0022),//0x2300022,
	GX_PIXEL_FORMAT_RGB12_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0023),//0x2300023,
	GX_PIXEL_FORMAT_RGB16_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0024),//0x2300024,
}GX_PIXEL_FORMAT_ENTRY;

//------------------------------------------------------------------------------
//  Image interpolation method; Used for IImageProcessConfig::SetConvertType 
//------------------------------------------------------------------------------
typedef enum  GX_BAYER_CONVERT_TYPE_LIST
{
	GX_RAW2RGB_NEIGHBOUR  = 0,
	GX_RAW2RGB_ADAPTIVE   = 1,
	GX_RAW2RGB_NEIGHBOUR3 = 2
}GX_BAYER_CONVERT_TYPE_LIST;

//------------------------------------------------------------------------------
//  Image valid bit; Used for IImageData::ConvertToRaw8/IImageData::ConvertToRGB24/IImageProcessConfig.SetValidBit 
//------------------------------------------------------------------------------
typedef enum  GX_VALID_BIT_LIST
{
	GX_BIT_0_7	    = 0,    ///< bit 0~7
	GX_BIT_1_8	    = 1,    ///< bit 1~8
	GX_BIT_2_9	    = 2,    ///< bit 2~9
	GX_BIT_3_10	    = 3,    ///< bit 3~10
	GX_BIT_4_11	    = 4     ///< bit 4~11
}GX_VALID_BIT_LIST;


//------------------------------------------------------------------------------
//  Reset Device Mode
//------------------------------------------------------------------------------
typedef enum GX_RESET_DEVICE_MODE
{
	GX_MANUFACTURER_SPECIFIC_RECONNECT   = 0x1,    ///< reconnect Device
	GX_MANUFACTURER_SPECIFIC_RESET     = 0x2     ///< reset Device 
}GX_RESET_DEVICE_MODE;


//------------------------------------------------------------------------------
//  Call back handles
//------------------------------------------------------------------------------
typedef void* GX_DEVICE_OFFLINE_CALLBACK_HANDLE;    ///< Retrieve from IGXDevice::RegisterDeviceOfflineCallback 
typedef void* GX_FEATURE_CALLBACK_HANDLE;           ///< Retrieve from IGXFeatureControl::RegisterFeatureCallback 

#endif //GXIAPI_BASE_H