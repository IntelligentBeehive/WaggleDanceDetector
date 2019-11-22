//------------------------------------------------------------------------
/**
\file		IEnumFeature.h
\brief		Definition of interface IEnumFeature
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "GXStringCPP.h"
#include "GXStringVector.h"
#include "GXIAPIBase.h"
#include "GXSmartPtr.h"


class GXIAPICPP_API IEnumFeature
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IEnumFeature(){};

	//---------------------------------------------------------
	/**
	\brief   Get list of symbolic Values
	*/
	//---------------------------------------------------------
	virtual GxIAPICPP::gxstring_vector GetEnumEntryList() = 0;

	//---------------------------------------------------------
	/**
	\brief   Get the current value of the enum feature
	*/
	//---------------------------------------------------------
	virtual GxIAPICPP::gxstring GetValue() = 0;

	//---------------------------------------------------------
	/**
	\brief      Set the current value of the enum feature
	\param      [in]strValue      the value write
	*/
	//--------------------------------------------------------- 
	virtual void SetValue(const GxIAPICPP::gxstring& strValue) = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IEnumFeature>;
typedef GXSmartPtr<IEnumFeature>      CEnumFeaturePointer;