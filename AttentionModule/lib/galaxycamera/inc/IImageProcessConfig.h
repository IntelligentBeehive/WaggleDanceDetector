//------------------------------------------------------------------------
/**
\file		IImageProcessConfig.h
\brief		Definition of the IImageProcessConfig interface
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once

class GXIAPICPP_API IImageProcessConfig
{
public:
	//---------------------------------------------------------
	/**
	\brief Destructor
	*/
	//---------------------------------------------------------
	virtual ~IImageProcessConfig(){};

	//---------------------------------------------------------
	/**
	\brief       Special for more than 8 bits data device, to choose 8 bits data in all the bits for image process.
	\param       [in]emValidBits     The segment
	\return      void
	*/
	//---------------------------------------------------------
	virtual void SetValidBit(GX_VALID_BIT_LIST emValidBits) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of correcting defective pixel
	\param      [in]bEnable  True to enable; False to disable
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableDefectivePixelCorrect(bool bEnable) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of Sharpening
	\param      [in]bEnable  True to enable; False to disable
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableSharpen(bool bEnable) = 0;

	//---------------------------------------------------------
	/**
	\brief      Set sharpen value param.
	\param      [in]dParam   The sharpen value param
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetSharpenParam(double dParam) = 0;

	//---------------------------------------------------------
	/**
	\brief      Set contrast value param.
	\param      [in]nParam  The contrast value param  
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetContrastParam(int32_t nParam) = 0;


	//---------------------------------------------------------
	/**
	\brief      Set gamma value param.
	\param      [in]dParam  The gamma value param
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetGammaParam(double dParam) = 0;

	//---------------------------------------------------------
	/**
	\brief      Set lightness value param.
	\param      [in]nParam  The lightness value param
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetLightnessParam(int32_t nParam) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of noise reduction [Does not support the Mono camera]
	\param      [in]bEnable  True to enable; False to disable
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableDenoise(bool bEnable) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of color correction [Does not support the Mono camera]
	\param      [in]bEnable  True to enable; False to disable
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableColorCorrection(bool bEnable) = 0;

	//---------------------------------------------------------
	/**
	\brief      True if enable color correction [Does not support the Mono camera]
	\return     True if enable color correction
	*/
	//---------------------------------------------------------
	virtual bool IsColorCorrection() = 0;

	//---------------------------------------------------------
	/**
	\brief      Set saturation value param [Does not support the Mono camera]
	\param      [in]nParam   The saturation value param
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetSaturationParam(int32_t nParam) = 0;

	//---------------------------------------------------------
	/**
	\brief      Set convert type of image interpolation [Does not support the Mono camera]
	\param      [in]emConvertType   The convert type
	\return     void
	*/
	//---------------------------------------------------------
	virtual void SetConvertType(GX_BAYER_CONVERT_TYPE_LIST emConvertType) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of flip in image interpolation [Does not support the Mono camera]
	\param      [in]bFlip   If true to be flip, else not.
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableConvertFlip(bool bFlip) = 0;

	//---------------------------------------------------------
	/**
	\brief      The switch of process accelerate, rely on hardware's supporting.
	\return     void
	*/
	//---------------------------------------------------------
	virtual void EnableAccelerate(bool bAccelerate) = 0;

	//---------------------------------------------------------
	/**
	\brief       Special for more than 8 bits data image, that indicates which 8 bits should be processed.              
	\return      The segment bits
	*/
	//---------------------------------------------------------
	virtual GX_VALID_BIT_LIST GetValidBit() = 0;

	//---------------------------------------------------------
	/**
	\brief      True if enable defective pixel correction
	\return     True if enable defective pixel correction
	*/
	//---------------------------------------------------------
	virtual bool IsDefectivePixelCorrect() = 0;

	//---------------------------------------------------------
	/**
	\brief      True if enable sharpen
	\return     True if enable sharpen
	*/
	//---------------------------------------------------------
	virtual bool IsSharpen() = 0;

	//---------------------------------------------------------
	/**
	\brief      True if enable process accelerate
	\return     True if enable process accelerate
	*/
	//---------------------------------------------------------
	virtual bool IsAccelerate() = 0;

	//---------------------------------------------------------
	/**
	\brief      Get the current sharpen param
	\return     The current sharpen param
	*/
	//---------------------------------------------------------
	virtual double GetSharpenParam() = 0;

	//---------------------------------------------------------
	/**
	\brief      Get the current contrast param
	\return     The current contrast param
	*/
	//---------------------------------------------------------
	virtual int32_t GetContrastParam() = 0;


	//---------------------------------------------------------
	/**
	\brief      Get the gamma param
	\return     The the gamma param
	*/
	//---------------------------------------------------------
	virtual double GetGammaParam() = 0;

	//---------------------------------------------------------
	/**
	\brief      Get lightness param
	\return     The lightness param
	*/
	//---------------------------------------------------------
	virtual int32_t GetLightnessParam() = 0;

	//---------------------------------------------------------
	/**
	\brief      True if enable pixel reduction [Does not support the Mono camera]
	\return     True if enable pixel reduction 
	*/
	//---------------------------------------------------------
	virtual bool IsDenoise() = 0;

	//---------------------------------------------------------
	/**
	\brief     Get the current saturation param [Does not support the Mono camera]
	\return    The the current saturation param
	*/
	//---------------------------------------------------------
	virtual int32_t GetSaturationParam() = 0;

	//---------------------------------------------------------
	/**
	\brief      Get the current convert type for image interpolation [Does not support the Mono camera]
	\return     The the current convert type for image interpolation 
	*/
	//---------------------------------------------------------
	virtual GX_BAYER_CONVERT_TYPE_LIST GetConvertType() = 0;

	//---------------------------------------------------------
	/**
	\brief      Get the current flip mode for image interpolation. True means to flip, False not. [Does not support the Mono camera]
	\return     The the current flip mode for image interpolation. True means to flip, False not. 
	*/
	//---------------------------------------------------------
	virtual bool IsConvertFlip() = 0;

	//---------------------------------------------------------
	/**
	\brief      Reset all the params to the default params.
	\return     void
	*/
	//---------------------------------------------------------
	virtual void Reset() = 0;
};

template class GXIAPICPP_API  GXSmartPtr<IImageProcessConfig>;
typedef GXSmartPtr<IImageProcessConfig>  CImageProcessConfigPointer;