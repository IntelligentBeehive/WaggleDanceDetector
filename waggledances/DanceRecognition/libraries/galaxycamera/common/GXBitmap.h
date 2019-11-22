//------------------------------------------------------------------------
/**
\file		GXBitmap.h
\brief		This class is mainly used for image display and storage.Image display and storage can be adaptive black and white camera and color camera.
            the image can be stored as BMP or RAW format

*/
//------------------------------------------------------------------------
#pragma once

#include "GalaxyIncludes.h"

class CGXBitmap
{
public:
	/// construction
	CGXBitmap(CGXDevicePointer& objCGXDevicePointer,CWnd* pWnd);

	/// destruction
	~CGXBitmap(void);
	
	 /// Display image
	 void Show(CImageDataPointer& objCImageDataPointer);

	 /// Display image and frame rate
	 void Show(CImageDataPointer& objCImageDataPointer,char* strDeviceSNFPS);

	 /// Process and Display the image
	 void ShowImageProcess(CImageProcessConfigPointer& objCfg,CImageDataPointer& objCImageDataPointer);

	 /// the image are stored as BMP format
	 void SaveBmp(CImageDataPointer& objCImageDataPointer,const std::string& strFilePath);

	 /// the image are stored as Raw format
	 void SaveRaw(CImageDataPointer& objCImageDataPointer,const std::string& strFilePath);

	 /// Get the best Bit by GX_PIXEL_FORMAT_ENTRY
	 GX_VALID_BIT_LIST GetBestValudBit(GX_PIXEL_FORMAT_ENTRY emPixelFormatEntry);
private:
	/// Check whether the PixelFormat is 8 bit
	bool __IsPixelFormat8(GX_PIXEL_FORMAT_ENTRY emPixelFormatEntry);

	/// Prepare resources for displaying color camera images
	void __ColorPrepareForShowImg();

	/// Prepare resources for displaying black and white camera images
	void __MonoPrepareForShowImg();

	/// whether compatible
	bool __IsCompatible(BITMAPINFO *pBmpInfo, uint64_t nWidth, uint64_t nHeight);

	/// Update Bitmap information
	void __UpdateBitmap(CImageDataPointer& objCImageDataPointer);

	/// Display image to UI
	void __DrawImg(BYTE* pBuffer);

	/// Display image and frame rate to UI
	void __DrawImg(BYTE* pBuffer, char* strDeviceSNFPS);

	/// Calculate the number of bytes occupied by width
	int64_t __GetStride(int64_t nWidth, bool bIsColor);


private:
	CWnd*              m_pWnd;                           ///< The pointer for display image form
	bool               m_bIsColor ;                      ///< The flag indicates whether the color camera 
	int64_t            m_nImageHeight;                   ///< Original image height
	int64_t            m_nImageWidth;                    ///< Original image width 
	BITMAPINFO         *m_pBmpInfo;	                     ///< BITMAPINFO Structure pointer
	char               m_chBmpBuf[2048];	             ///< BIMTAPINFO Memory buffer
	HDC                m_hDC;                            ///< DC handle for draw image
	BYTE               *m_pImageBuffer;                  ///< Save the flipped image for display
private:
	CGXBitmap& operator=(const CGXBitmap&);
	CGXBitmap(const CGXBitmap&);
};

