//------------------------------------------------------------------------
/**
\file		IRegisterFeature.h
\brief		Definition of the IRegisterFeature interface
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#include "GXIAPIBase.h"
#include "GXSmartPtr.h"

class GXIAPICPP_API IRegisterFeature
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IRegisterFeature(){};

	//---------------------------------------------------------
	/**
	\brief      Retrieves the length of the register [Bytes]
	*/
	//---------------------------------------------------------
	virtual int64_t GetLength() = 0;

	//---------------------------------------------------------
	/**
	\brief    Fills a buffer with the register's contents
	\param    [in,out]pBuffer The buffer receiving the data to read
	\param    [in]nLength     The number of bytes to retrieve
	\return   void
	*/
	//---------------------------------------------------------
	virtual void GetBuffer(uint8_t* pBuffer, int64_t nLength) = 0;

	//---------------------------------------------------------
	/**
	\brief     Set the register's contents
	\param     [in]pBuffer The buffer containing the data to set
	\param     [in]nLength The number of bytes in pBuffer
	\return    void
	*/
	//--------------------------------------------------------- 
	virtual void SetBuffer(uint8_t* pBuffer, int64_t nLength) = 0;		
};

template class GXIAPICPP_API  GXSmartPtr<IRegisterFeature>;
typedef GXSmartPtr<IRegisterFeature>  CRegisterFeaturePointer;