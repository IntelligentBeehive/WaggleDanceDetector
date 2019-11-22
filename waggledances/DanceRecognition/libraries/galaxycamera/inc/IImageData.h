//------------------------------------------------------------------------
/**
\file		IImageData.h
\brief		Definition of the IIntFeature interface
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXSmartPtr.h"
#include "IImageProcessConfig.h"

class GXIAPICPP_API IImageData
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IImageData(){};

	//----------------------------------------------------------------------------------
	/**
	\brief     Get the status of the image, referring to GX_FRAME_STATUS_LIST
	\return    the status of the image, referring to GX_FRAME_STATUS_LIST
	*/
	//----------------------------------------------------------------------------------
	virtual GX_FRAME_STATUS_LIST GetStatus() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the payload size of the image
	\return   The payload size of the image
	*/
	//----------------------------------------------------------------------------------
	virtual uint64_t GetPayloadSize() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the width of the image
	\return   The width of the image
	*/
	//----------------------------------------------------------------------------------
	virtual uint64_t GetWidth() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the height of the image
	\return   The height of the image
	*/
	//----------------------------------------------------------------------------------
	virtual uint64_t GetHeight() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the pixel format of the image
	\return   The pixel format of the image
	*/
	//----------------------------------------------------------------------------------
	virtual GX_PIXEL_FORMAT_ENTRY GetPixelFormat() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the frame id of the image
	\return   The frame id of the image
	*/
	//----------------------------------------------------------------------------------
	virtual uint64_t GetFrameID() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the time stamp of the image
	\return   The the time stamp of the image
	*/
	//----------------------------------------------------------------------------------
	virtual uint64_t GetTimeStamp() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get the raw data image buffer pointer address
	\return   The raw data image buffer pointer address
	*/
	//----------------------------------------------------------------------------------
	virtual void* GetBuffer() =0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Special for more than 8 bits data image, To choose a segment contain 8 bits data
	\param     [in]emValidBits  refer to GX_VALID_BIT_LIST
	\return    The 8 bits data buffer pointer address
	*/
	//----------------------------------------------------------------------------------
	virtual void* ConvertToRaw8(GX_VALID_BIT_LIST emValidBits) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Convert the raw data to RGB24 data
	\param     [in]emValidBits   To choose a segment contain 8 bits to convert
	\param     [in]emConvertType The method for image interpolation
	\param     bFlip             The flip mode for image interpolation
	\return    The RGB24 data buffer pointer address
	*/
	//----------------------------------------------------------------------------------
	virtual void* ConvertToRGB24(GX_VALID_BIT_LIST emValidBits
		,GX_BAYER_CONVERT_TYPE_LIST emConvertType
		,bool bFlip) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     To enhance the image effect by ImageProcess
	\param     [in]objCfg  A smart pointer object CImageProcessConfigPointer, contain a set of params
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void* ImageProcess(CImageProcessConfigPointer &objCfg) = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IImageData>;
typedef GXSmartPtr<IImageData>           CImageDataPointer;