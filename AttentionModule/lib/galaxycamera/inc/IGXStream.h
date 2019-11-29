//------------------------------------------------------------------------
/**
\file		IGXStream.h
\brief		Definition of the IGXDevice interface
\Date       2019-8-15
\Version    1.1.1908.9151
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXSmartPtr.h"
#include "IGXFeatureControl.h"
#include "IImageData.h"
#include "ICaptureEventHandler.h"

class GXIAPICPP_API IGXStream
{
public:	
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IGXStream(){};

	//----------------------------------------------------------------------------------
	/**
	\brief     Start the grab thread, and allocate resource for grab.
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void StartGrab() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Stop the grab thread, and release the resource for grab.
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void StopGrab() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Register capture call back for a new buffer event.
	When a buffer is filled, the grab thread will call the ICaptureEventHandler* , pointed to the user method, registered by user.
	Only very short processing tasks can be performed in this function. Otherwise, the event notification will block the
	receiving of images.
	\param    pUserParam[in]        The user param
	\param    pEventHandler[in]     The call back handler pointer; ; that must be inherited from ICaptureEventHandler
	\return   void
	*/
	//----------------------------------------------------------------------------------
	virtual void RegisterCaptureCallback(ICaptureEventHandler* pEventHandler, void *pUserParam) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Unregister capture call back
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void UnregisterCaptureCallback() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Get one image. Different from the call back way, User can call this function to get one image at one time.
	If you have registered capture call back, you can't use GetImage at the same time.
	\param     nTimeout[in]       The timeout waits in ms.
	\return    A smart pointer object CImageDataPointer
	*/
	//----------------------------------------------------------------------------------
	virtual CImageDataPointer GetImage(uint32_t nTimeout) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Returns the set of camera related stream parameters.
	\return   A CGXFeatureControlPointer object to a feature control.
	*/
	//----------------------------------------------------------------------------------
	virtual CGXFeatureControlPointer GetFeatureControl() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     when underlying thread receives data from a device, it will fill a buffer from the receiving buffer pool.
	when a buffer is filled it is removed from the pool and if successfully filled,	it is put into the output buffer queue. 
	The upper thread get a buffer from the output buffer queue and call user method back, 
	after the user method returned, the upper thread queue the buffer back to the receiving buffer pool.
	Flush queue means to flush the output buffer queue.
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void FlushQueue() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Close stream
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void Close() = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Set Acqusition Buffer Number
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void SetAcqusitionBufferNumber(uint64_t nBufferNum) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Get the Optimal Packet Size 
	\return    uint32_t
	*/
	//----------------------------------------------------------------------------------
    virtual uint32_t GetOptimalPacketSize(void) = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IGXStream>;
typedef GXSmartPtr<IGXStream>            CGXStreamPointer;