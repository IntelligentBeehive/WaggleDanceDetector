//------------------------------------------------------------------------
/**
\file		ICommandFeature.h
\brief		Definition of ICommand interface
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once

#include "GXIAPIBase.h"
#include "GXSmartPtr.h"

class GXIAPICPP_API ICommandFeature
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~ICommandFeature(){};

	//---------------------------------------------------------
	/**
	\brief      Execute the command
	\return     void
	*/
	//--------------------------------------------------------- 
	virtual void Execute() = 0;
};

template class GXIAPICPP_API  GXSmartPtr<ICommandFeature>;
typedef GXSmartPtr<ICommandFeature>   CCommandFeaturePointer;