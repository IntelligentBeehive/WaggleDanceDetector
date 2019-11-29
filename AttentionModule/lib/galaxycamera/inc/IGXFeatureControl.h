//------------------------------------------------------------------------
/**
\file		IGXFeatureControl.h
\brief		Definition of IGXFeatureControl class.
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#ifndef IGXFEATURE_CONTROL_H
#define IGXFEATURE_CONTROL_H

#include "GXIAPIBase.h"
#include "GXStringCPP.h"
#include "GXStringVector.h"

#include "GXSmartPtr.h"
#include "IBoolFeature.h"
#include "IFloatFeature.h"
#include "IIntFeature.h"
#include "IEnumFeature.h"
#include "IStringFeature.h"
#include "IRegisterFeature.h"
#include "ICommandFeature.h"
#include "IFeatureEventHandler.h"

class GXIAPICPP_API IGXFeatureControl
{

public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IGXFeatureControl(){};

	//----------------------------------------------------------------------------------
	/**
	\brief     Retrieves all feature names in the feature control
	\param     vectorFeatureNameList[int,out] A list of feature name
	\return    void
	*/
	//----------------------------------------------------------------------------------
	virtual void GetFeatureNameList(GxIAPICPP::gxstring_vector& vectorFeatureNameList) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief     Get the feature type of the given feature name
	\param     strFeatureName[in]   The feature name
	\return    The feature type
	*/
	//----------------------------------------------------------------------------------
	virtual GX_FEATURE_TYPE GetFeatureType(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//---------------------------------------------------------
	/**
	\brief      Checks if a feature is implemented
	\param      strFeatureName[in]  The feature name
	\return     True if the feature was implemented
	*/
	//---------------------------------------------------------
	virtual bool IsImplemented(const GxIAPICPP::gxstring& strFeatureName) = 0;	

	//---------------------------------------------------------
	/**
	\brief      Checks if a feature is readable
	\param      strFeatureName[in]  The feature name
	\return     True if the feature was readable
	*/
	//---------------------------------------------------------
	virtual bool IsReadable(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//---------------------------------------------------------
	/**
	\brief      Checks if a feature is writable
	\param      strFeatureName[in]  The feature name
	\return     True if the feature was writable
	*/
	//---------------------------------------------------------
	virtual bool IsWritable(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//---------------------------------------------------------
	/**
	\brief      Read specified register value
	\param [in]ui64Address     Register Address
	\param [out]pBuffer        return register value,It can not be NULL
	\param [in, out]piSize     [in]Buffer size of the user application
	[out]After reading the value of the register successfully, return the actual size.

	\return void
	*/
	//---------------------------------------------------------
	virtual void ReadPort(uint64_t uiAddress, void *pBuffer, size_t *piSize) = 0;

	//---------------------------------------------------------
	/**
	\brief     Write specified register value
	\param [in]ui64Address     Register Address
	\param [out]pBuffer        Write register value,It can not be NULL
	\param [in]piSize     [in]Buffer size of the user application

	\return void
	*/
	//---------------------------------------------------------
	virtual void WritePort(uint64_t uiAddress, const void *pBuffer, size_t *piSize) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a int feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A int feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CIntFeaturePointer GetIntFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a float feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A float feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CFloatFeaturePointer GetFloatFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a enum feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A enum feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CEnumFeaturePointer GetEnumFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a bool feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A bool feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CBoolFeaturePointer GetBoolFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a string feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A string feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CStringFeaturePointer GetStringFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a command feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A command feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CCommandFeaturePointer GetCommandFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief    Get a register feature control, associated with the given feature name
	\param    strFeatureName[in] The feature name
	\return   A register feature control
	*/
	//----------------------------------------------------------------------------------
	virtual CRegisterFeaturePointer GetRegisterFeature(const GxIAPICPP::gxstring& strFeatureName) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief Register feature event call back
	\param strFeatureName[in]        The feature name
	\param pUserParam[in]            The user param
	\param callBackFun[in]           The call back handler pointer; that must be inherited from IFeatureEventHandler
	\return The call back handle
	*/
	//----------------------------------------------------------------------------------
	virtual GX_FEATURE_CALLBACK_HANDLE RegisterFeatureCallback(const GxIAPICPP::gxstring& strFeatureName, 
		IFeatureEventHandler* pEventHandler, void* pUserParam) = 0;

	//----------------------------------------------------------------------------------
	/**
	\brief Unregister feature event call back
	\param hCallback[in]  The call back handle
	\return void
	*/
	//----------------------------------------------------------------------------------
	virtual void UnregisterFeatureCallback(GX_FEATURE_CALLBACK_HANDLE hCallback) = 0;

};

template class GXIAPICPP_API  GXSmartPtr<IGXFeatureControl>;
typedef GXSmartPtr<IGXFeatureControl>    CGXFeatureControlPointer;

#endif //IGXFEATURE_CONTROL_H