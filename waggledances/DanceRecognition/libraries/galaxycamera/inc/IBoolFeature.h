//------------------------------------------------------------------------
/**
\file		IBoolFeature.h
\brief		Definition of interface IBoolFeature
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once

#include "GXIAPIBase.h"
#include "GXSmartPtr.h"

class GXIAPICPP_API IBoolFeature
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IBoolFeature(){};

	//---------------------------------------------------------
	/**
	\brief      Get node value
	\return     The value read
	*/
	//---------------------------------------------------------
	virtual bool GetValue() = 0;

	//---------------------------------------------------------
	/**
	\brief      Set node value
	\param      bValue[in]       The value to set
	\return     void
	*/
	//--------------------------------------------------------- 
	virtual void SetValue(bool bValue) = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IBoolFeature>;
typedef GXSmartPtr<IBoolFeature>      CBoolFeaturePointer;