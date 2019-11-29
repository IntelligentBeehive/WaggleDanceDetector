//------------------------------------------------------------------------
/**
\file		ICaptureEventHandler.h
\brief		Contains the image event handler base class.
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#ifndef GX_CAPUTRE_EVENT_HANDLER_H
#define GX_CAPUTRE_EVENT_HANDLER_H
#include "IImageData.h"


class ICaptureEventHandler
{
  public:
    //---------------------------------------------------------
    /**
    \brief Destructor
    */
    //---------------------------------------------------------
	virtual ~ICaptureEventHandler(void){};

    //---------------------------------------------------------
    /**
	\brief This method is called when an image has been grabbed.
	Only very short processing tasks can be performed by this method. Otherwise, the event notification will block the
	receiving of images.

	The status of the grab needs to be checked before accessing The image data.
	See IImageData::GetStatus ,for more information.

	\param[in]  objImageDataPointer  The image data.
	\param[in]  pUserParam           The user param, it has been registered in CGXStream::RegisterCaptureCallback by user.
    */
    //---------------------------------------------------------
    virtual void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam) = 0;
};

#endif //GX_CAPUTRE_EVENT_HANDLER_H