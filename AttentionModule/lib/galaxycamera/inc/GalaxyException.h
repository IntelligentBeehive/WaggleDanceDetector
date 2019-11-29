//------------------------------------------------------------------------
/**
\file		GalaxyException.h
\brief		GXIAPICPP's exception class
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once
#pragma warning(disable: 4275) ///< non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#include <iostream>
#include "GXStringCPP.h"
using namespace GxIAPICPP;

class GXIAPICPP_API CGalaxyException:public std::runtime_error
{
public:
	///Constructor
	CGalaxyException(int emErrorCode,const GxIAPICPP::gxstring& strDescription);

	///Destructor
	virtual ~CGalaxyException(void) throw();

	///Get exception message
	virtual const char * what() const throw();

	///Get error code
	int GetErrorCode();
private:
	int                  m_emErrorCode;               ///< The error code
	GxIAPICPP::gxstring  m_strDescription;            ///< The stored message string

};




