//------------------------------------------------------------------------
/**
\file		IFeatureEventHandler.h
\brief		Contains the feature event handler base class.
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#ifndef GX_FEATURE_EVENT_HANDLER_H
#define GX_FEATURE_EVENT_HANDLER_H
#include "GXStringCPP.h"

class IFeatureEventHandler
{
  public:
    //---------------------------------------------------------
    /**
    \brief      Destructor
    */
    //---------------------------------------------------------
	virtual ~IFeatureEventHandler(void){};

    //---------------------------------------------------------
    /**
	\brief      This method is called when a camera event has been received.
	Only very short processing tasks can be performed in this function. Otherwise, the event notification will block the
	receiving of events.
	\param[in]  strFeatureName The feature name registered.
	\param[in]  pUserParam     The user param passed when registering for the event. It can be used to distinguish between different events.	
    */
    //---------------------------------------------------------
	virtual void DoOnFeatureEvent(const GxIAPICPP::gxstring& strFeatureName, void* pUserParam) = 0;
};

#endif //GX_FEATURE_EVENT_HANDLER_H