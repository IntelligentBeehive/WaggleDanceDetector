//------------------------------------------------------------------------
/**
\file		IStringFeature.h
\brief		Definition of the IStringFeature interface
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "GXStringCPP.h"
#include "GXIAPIBase.h"
#include "GXSmartPtr.h"

class GXIAPICPP_API IStringFeature
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IStringFeature(){};

	//---------------------------------------------------------
	/**
	\brief      Get a feature value
	*/
	//--------------------------------------------------------- 
	virtual GxIAPICPP::gxstring GetValue() = 0;

	//---------------------------------------------------------
	/**
	\brief      Set a feature value
	\param      strValue[in]   The value to be set 
	\return     void
	*/
	//--------------------------------------------------------- 
	virtual void SetValue(const GxIAPICPP::gxstring& strValue) = 0;

	//---------------------------------------------------------
	/**
	\brief      Retrieves the maximum length of the string in bytes
	*/
	//--------------------------------------------------------- 
	virtual int64_t GetStringMaxLength() = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IStringFeature>;
typedef GXSmartPtr<IStringFeature>    CStringFeaturePointer;