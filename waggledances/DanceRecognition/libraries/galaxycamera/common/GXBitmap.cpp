//------------------------------------------------------------------------
/**
\file		GXBitmap.cpp
\brief		This class is mainly used for image display and storage.Image display and storage can be adaptive black and white camera and color camera.
            the image can be stored as BMP or RAW format
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "GXBitmap.h"


//---------------------------------------------------------------------------------
/**
\brief   The construction function
\param   objCGXDevicePointer[in]     the pointer for device
\param   pWnd[in]                    Form pointer
\return  void
*/
//----------------------------------------------------------------------------------
CGXBitmap::CGXBitmap(CGXDevicePointer& objCGXDevicePointer,CWnd* pWnd)
:m_pWnd(pWnd)
,m_hDC(NULL)
,m_bIsColor(false)
,m_nImageHeight(0)
,m_nImageWidth(0)
,m_pBmpInfo(NULL)
,m_pImageBuffer(NULL)
{
	if ((objCGXDevicePointer.IsNull())||(NULL == pWnd))
	{
		throw std::runtime_error("Argument is error");
	}

	HWND hWnd = pWnd->m_hWnd;
	if (!::IsWindow(hWnd))
	{
		throw std::runtime_error("The HWND must be form");
	}

	m_hDC  = ::GetDC(m_pWnd->m_hWnd);
	memset(m_chBmpBuf,0,sizeof(m_chBmpBuf));
	gxstring strValue = "";

	//Get the image width and height
	m_nImageWidth = (int64_t)objCGXDevicePointer->GetRemoteFeatureControl()->GetIntFeature("Width")->GetValue();
	m_nImageHeight = (int64_t)objCGXDevicePointer->GetRemoteFeatureControl()->GetIntFeature("Height")->GetValue();

	//Check whether the color camera
	if (objCGXDevicePointer->GetRemoteFeatureControl()->IsImplemented("PixelColorFilter"))
	{
		strValue = objCGXDevicePointer->GetRemoteFeatureControl()->GetEnumFeature("PixelColorFilter")->GetValue();

		if ("None" != strValue)
		{
			m_bIsColor = true;
		}
	}

	if (m_bIsColor)
	{
		__ColorPrepareForShowImg();
	} 
	else
	{
		__MonoPrepareForShowImg();
	}
}

//---------------------------------------------------------------------------------
/**
\brief  The destruction function 

\return  void
*/
//----------------------------------------------------------------------------------
CGXBitmap::~CGXBitmap(void)
{
	//Release resource
	::ReleaseDC(m_pWnd->m_hWnd, m_hDC);
}

//----------------------------------------------------------------------------------
/**
\brief     Check whether the PixelFormat is 8 bit
\param     emPixelFormatEntry[in]  Image format
\return    true:  is 8 bit,   false:  is not 8 bit
*/
//----------------------------------------------------------------------------------
bool CGXBitmap::__IsPixelFormat8(GX_PIXEL_FORMAT_ENTRY emPixelFormatEntry)
{
	bool bIsPixelFormat8 = false;
	const unsigned  PIXEL_FORMATE_BIT = 0x00FF0000;  
	unsigned uiPixelFormatEntry = (unsigned)emPixelFormatEntry;
	if ((uiPixelFormatEntry & PIXEL_FORMATE_BIT) == GX_PIXEL_8BIT)
	{
		bIsPixelFormat8 = true;
	}
	return bIsPixelFormat8;
}


//----------------------------------------------------------------------------------
/**
\brief     Get the best Bit by GX_PIXEL_FORMAT_ENTRY
\param     emPixelFormatEntry[in]   Image format
\return    the best Bit
*/
//----------------------------------------------------------------------------------
GX_VALID_BIT_LIST CGXBitmap::GetBestValudBit(GX_PIXEL_FORMAT_ENTRY emPixelFormatEntry)
{
	GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
	switch (emPixelFormatEntry)
	{
	case GX_PIXEL_FORMAT_MONO8:
	case GX_PIXEL_FORMAT_BAYER_GR8:
	case GX_PIXEL_FORMAT_BAYER_RG8:
	case GX_PIXEL_FORMAT_BAYER_GB8:
	case GX_PIXEL_FORMAT_BAYER_BG8:
		{
			emValidBits = GX_BIT_0_7;
			break;
		}
	case GX_PIXEL_FORMAT_MONO10:
	case GX_PIXEL_FORMAT_BAYER_GR10:
	case GX_PIXEL_FORMAT_BAYER_RG10:
	case GX_PIXEL_FORMAT_BAYER_GB10:
	case GX_PIXEL_FORMAT_BAYER_BG10:
		{
			emValidBits = GX_BIT_2_9;
			break;
		}
	case GX_PIXEL_FORMAT_MONO12:
	case GX_PIXEL_FORMAT_BAYER_GR12:
	case GX_PIXEL_FORMAT_BAYER_RG12:
	case GX_PIXEL_FORMAT_BAYER_GB12:
	case GX_PIXEL_FORMAT_BAYER_BG12:
		{
			emValidBits = GX_BIT_4_11;
			break;
		}
	case GX_PIXEL_FORMAT_MONO14:
		{
			//There is no such data format 
			break;
		}
	case GX_PIXEL_FORMAT_MONO16:
	case GX_PIXEL_FORMAT_BAYER_GR16:
	case GX_PIXEL_FORMAT_BAYER_RG16:
	case GX_PIXEL_FORMAT_BAYER_GB16:
	case GX_PIXEL_FORMAT_BAYER_BG16:
		{
			//There is no such data format 
			break;
		}
	default:
		break;
	}
	return emValidBits;
}

//---------------------------------------------------------------------------------
/**
\brief   Prepare resources for displaying color camera images

\return  void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::__ColorPrepareForShowImg()
{
	//--------------------------------------------------------------------
	//---------------------------Initialize bitmap header---------------------------
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth			= (LONG)m_nImageWidth;
	m_pBmpInfo->bmiHeader.biHeight			= (LONG)m_nImageHeight;

	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount        = 24;
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;
}

//---------------------------------------------------------------------------------
/**
\brief   Prepare resources for displaying black and white images

\return  void 
*/
//----------------------------------------------------------------------------------
void CGXBitmap::__MonoPrepareForShowImg()
{
	//---------------------------------------------------------------------
	//----------------------Initialize bitmap---------------------------------
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth			= (LONG)m_nImageWidth;
	m_pBmpInfo->bmiHeader.biHeight			= (LONG)m_nImageHeight;	

	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount		= 8; // black and white image is 8
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;

	// black and white image need initialize palette
	for(int i=0;i<256;i++)
	{
		m_pBmpInfo->bmiColors[i].rgbBlue	=i;
		m_pBmpInfo->bmiColors[i].rgbGreen	=i;
		m_pBmpInfo->bmiColors[i].rgbRed		=i;
		m_pBmpInfo->bmiColors[i].rgbReserved=i;
	}

	//Allocate space for the flipped image data
	if (m_pImageBuffer != NULL)
	{
		delete m_pImageBuffer;
		m_pImageBuffer = NULL;
	}

	m_pImageBuffer = new BYTE[(size_t)(m_nImageWidth * m_nImageHeight)];
	if (m_pImageBuffer == NULL)
	{
		throw std::runtime_error("Fail to allocate memory");
	}
}

//----------------------------------------------------------------------------------
/**
\brief     whether compatible
\param     pBmpInfo[in]    BITMAPINFO pointer
\param     nWidth[in]      Image width
\param     nHeight[in]     Image height
\return    true: compatible , false: not compatible
*/
//----------------------------------------------------------------------------------
bool CGXBitmap::__IsCompatible(BITMAPINFO *pBmpInfo, uint64_t nWidth, uint64_t nHeight)
{
	if (pBmpInfo == NULL
		|| pBmpInfo->bmiHeader.biHeight != nHeight
		|| pBmpInfo->bmiHeader.biWidth != nWidth
		)
	{
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------------
/**
\brief     Update Bitmap information
\param     objCImageDataPointer  Image data
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::__UpdateBitmap(CImageDataPointer& objCImageDataPointer)
{
	if (!__IsCompatible(m_pBmpInfo, objCImageDataPointer->GetWidth(), objCImageDataPointer->GetHeight()))
	{
		m_nImageWidth = objCImageDataPointer->GetWidth();
		m_nImageHeight = objCImageDataPointer->GetHeight();
		if (m_bIsColor)
		{
			__ColorPrepareForShowImg();
		} 
		else
		{
			__MonoPrepareForShowImg();
		}
	}
}

//---------------------------------------------------------------------------------
/**
\brief   Display image
\param   pBuffer[in]   Image data Buffer pointer
\return  void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::__DrawImg(BYTE* pBuffer)
{
	int nWndWidth  = 0;
	int nWndHeight = 0;

	// Prepare for drawing images
	RECT objRect;
	m_pWnd->GetClientRect(&objRect);	
	nWndWidth  = objRect.right - objRect.left;
	nWndHeight = objRect.bottom - objRect.top;

	::SetStretchBltMode(m_hDC, COLORONCOLOR);
	::StretchDIBits(m_hDC,
		0,						
		0,
		nWndWidth,
		nWndHeight,
		0,
		0,
		(int)m_nImageWidth,
		(int)m_nImageHeight,
		pBuffer,
		m_pBmpInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);
}

//---------------------------------------------------------------------------------
/**
\brief   Display image and frame rate to UI
\param   pBuffer[in]         Image data Buffer pointer
\param   strDeviceSNFPS[in]  frame rate
\return  void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::__DrawImg(BYTE* pBuffer, char* strDeviceSNFPS)
{
	
	int nWndWidth  = 0;
	int nWndHeight = 0;

	// Prepare for drawing images
	RECT objRect;
	m_pWnd->GetClientRect(&objRect);	
	nWndWidth  = objRect.right - objRect.left;
	nWndHeight = objRect.bottom - objRect.top;

	HDC      objMemDC = ::CreateCompatibleDC(m_hDC);
	HBITMAP  objMemBmp= CreateCompatibleBitmap(m_hDC, nWndWidth, nWndHeight);
	::SelectObject(objMemDC,objMemBmp);

	::SetStretchBltMode(objMemDC, COLORONCOLOR);
	::StretchDIBits(objMemDC,
		0,						
		0,
		nWndWidth,
		nWndHeight,
		0,
		0,
		(int)m_nImageWidth,
		(int)m_nImageHeight,
		pBuffer,
		m_pBmpInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);

	TextOut(objMemDC,0,0,strDeviceSNFPS,(int)strlen(strDeviceSNFPS));
	StretchBlt(m_hDC,
		0,
		0,
		nWndWidth,
		nWndHeight,
		objMemDC,
		0,
		0,
		nWndWidth,
		nWndHeight,
		SRCCOPY);

	::DeleteDC(objMemDC);
	DeleteObject(objMemBmp);
}
//----------------------------------------------------------------------------------
/**
\brief     Calculate the number of bytes occupied by width
\param     nWidth[in]      Image width
\param     bIsColor[in]    Whether is a color camera
\return    The number of bytes of an image line
*/
//----------------------------------------------------------------------------------
int64_t CGXBitmap::__GetStride(int64_t nWidth, bool bIsColor)
{
	return bIsColor ? nWidth * 3 : nWidth;
}

//----------------------------------------------------------------------------------
/**
\brief     Display image
\param     objCImageDataPointer[in]   Image data pointer
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::Show(CImageDataPointer& objCImageDataPointer)
{
	GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
	BYTE* pBuffer = NULL;

	if (objCImageDataPointer.IsNull())
	{
		throw std::runtime_error("NULL pointer dereferenced");
	}

	//Check whether update bitmap information
	__UpdateBitmap(objCImageDataPointer);

	emValidBits = GetBestValudBit(objCImageDataPointer->GetPixelFormat());
	if (m_bIsColor)
	{
		pBuffer = (BYTE*)objCImageDataPointer->ConvertToRGB24(emValidBits, GX_RAW2RGB_NEIGHBOUR, true);
		__DrawImg(pBuffer);
	}
	else
	{
		if (__IsPixelFormat8(objCImageDataPointer->GetPixelFormat()))
		{
			pBuffer = (BYTE*)objCImageDataPointer->GetBuffer();
		}
		else
		{
			pBuffer = (BYTE*)objCImageDataPointer->ConvertToRaw8(emValidBits);
		}
		// The black and white camera needs to flip the data after display
		for(int i =0;i <m_nImageHeight;i++)
		{
			memcpy(m_pImageBuffer+i*m_nImageWidth, pBuffer+(m_nImageHeight-i-1)*m_nImageWidth,(size_t)m_nImageWidth);
		}

		__DrawImg(m_pImageBuffer);
	}
	
}

//----------------------------------------------------------------------------------
/**
\brief     Display image and frame rate
\param     objCImageDataPointer[in]  Image data pointer
\param     strDeviceSNFPS[in]        frame rate
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::Show(CImageDataPointer& objCImageDataPointer,char* strDeviceSNFPS)
{
	GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
	BYTE* pBuffer = NULL;

	if (objCImageDataPointer.IsNull())
	{
		throw std::runtime_error("NULL pointer dereferenced");
	}

	//Check whether update bitmap information
	__UpdateBitmap(objCImageDataPointer);

	emValidBits = GetBestValudBit(objCImageDataPointer->GetPixelFormat());
	if (m_bIsColor)
	{
		pBuffer = (BYTE*)objCImageDataPointer->ConvertToRGB24(emValidBits, GX_RAW2RGB_NEIGHBOUR, true);
		__DrawImg(pBuffer,strDeviceSNFPS);
	}
	else
	{
		if (__IsPixelFormat8(objCImageDataPointer->GetPixelFormat()))
		{
			pBuffer = (BYTE*)objCImageDataPointer->GetBuffer();
		}
		else
		{
			pBuffer = (BYTE*)objCImageDataPointer->ConvertToRaw8(emValidBits);
		}

		// The black and white camera needs to flip the data after display
		for(int i =0;i <m_nImageHeight;i++)
		{
			memcpy(m_pImageBuffer + i * m_nImageWidth, pBuffer + (m_nImageHeight - i -1) * m_nImageWidth,(size_t)m_nImageWidth);
		}

		__DrawImg(m_pImageBuffer,strDeviceSNFPS);
	}
	
}

//----------------------------------------------------------------------------------
/**
\brief     Process and Display the image
\param     objCfg[in]                 Image processing adjustment parameter object
\param     objCImageDataPointer[in]   Image data pointer
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::ShowImageProcess(CImageProcessConfigPointer& objCfg,CImageDataPointer& objCImageDataPointer)
{
	if ((objCfg.IsNull())||(objCImageDataPointer.IsNull()))
	{
		throw std::runtime_error("NULL pointer dereferenced");
	}

	//Check whether update bitmap information
	__UpdateBitmap(objCImageDataPointer);

	BYTE* pBuffer = (BYTE*)objCImageDataPointer->ImageProcess(objCfg);

	if (m_bIsColor)
	{
		__DrawImg(pBuffer);
	}
	else
	{
		// The black and white camera needs to flip the data after display
		for(int i =0;i <m_nImageHeight;i++)
		{
			memcpy(m_pImageBuffer + i * m_nImageWidth, pBuffer + (m_nImageHeight - i -1) * m_nImageWidth,(size_t)m_nImageWidth);
		}

		__DrawImg(m_pImageBuffer);
	}
}

//----------------------------------------------------------------------------------
/**
\brief     the image are stored as BMP format
\param     objCImageDataPointer[in]  Image data pointer
\param     strFilePath[in]           file name
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::SaveBmp(CImageDataPointer& objCImageDataPointer,const std::string& strFilePath)
{
	GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
	BYTE* pBuffer = NULL;

	if ((objCImageDataPointer.IsNull())||(strFilePath == ""))
	{
		throw std::runtime_error("Argument is error");
	}

	//Check whether update bitmap information
	__UpdateBitmap(objCImageDataPointer);

	emValidBits = GetBestValudBit(objCImageDataPointer->GetPixelFormat());

	if (m_bIsColor)
	{
		pBuffer = (BYTE*)objCImageDataPointer->ConvertToRGB24(emValidBits, GX_RAW2RGB_NEIGHBOUR, true);
	}
	else
	{
		if (__IsPixelFormat8(objCImageDataPointer->GetPixelFormat()))
		{
			pBuffer = (BYTE*)objCImageDataPointer->GetBuffer();
		}
		else
		{
			pBuffer = (BYTE*)objCImageDataPointer->ConvertToRaw8(emValidBits);
		}
		// The black and white camera needs to flip the data after display
		for(int i =0;i < m_nImageHeight;i++)
		{
			memcpy(m_pImageBuffer + i * m_nImageWidth, pBuffer + (m_nImageHeight - i -1) * m_nImageWidth,(size_t)m_nImageWidth);
		}
		pBuffer = m_pImageBuffer;
	}

	DWORD		         dwImageSize = (DWORD)(__GetStride(m_nImageWidth,m_bIsColor) * m_nImageHeight);
	BITMAPFILEHEADER     stBfh	     = {0};
	DWORD		         dwBytesRead = 0;

	stBfh.bfType	= (WORD)'M' << 8 | 'B';			 //Define file type
	stBfh.bfOffBits = m_bIsColor ?sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		:sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (256 * 4);
	stBfh.bfSize	= stBfh.bfOffBits + dwImageSize; //File size

	DWORD dwBitmapInfoHeader = m_bIsColor ?sizeof(BITMAPINFOHEADER)
		:sizeof(BITMAPINFOHEADER) + (256 * 4);

	//Create file
	HANDLE hFile = ::CreateFile(strFilePath.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,														
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
	{
		throw std::runtime_error("Handle is invalid");
	}

	::WriteFile(hFile, &stBfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL);
	::WriteFile(hFile, m_pBmpInfo, dwBitmapInfoHeader, &dwBytesRead, NULL);
	::WriteFile(hFile, pBuffer, dwImageSize, &dwBytesRead, NULL);

	CloseHandle(hFile);
}

//----------------------------------------------------------------------------------
/**
\brief     the image are stored as Raw format
\param     objCImageDataPointer[in]  Image data pointer
\param     strFilePath[in]           File name
\return    void
*/
//----------------------------------------------------------------------------------
void CGXBitmap::SaveRaw(CImageDataPointer& objCImageDataPointer,const std::string& strFilePath)
{
	if ((objCImageDataPointer.IsNull())||(strFilePath == ""))
	{
		throw std::runtime_error("Argument is error");
	}

	__UpdateBitmap(objCImageDataPointer);

	DWORD   dwImageSize = (DWORD)objCImageDataPointer->GetPayloadSize();  // Write the length of the file
	DWORD   dwBytesRead = 0;                // Read the length of the file

	BYTE* pbuffer = (BYTE*)objCImageDataPointer->GetBuffer();
	if (!m_bIsColor)
	{
		// The black and white camera needs to flip the data after display
		for(int i =0;i < m_nImageHeight;i++)
		{
			memcpy(m_pImageBuffer + i * m_nImageWidth, pbuffer + (m_nImageHeight - i -1) * m_nImageWidth,(size_t)m_nImageWidth);
		}
		pbuffer = m_pImageBuffer;
	}

	// Create file
	HANDLE hFile = ::CreateFile(strFilePath.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,														
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)     // If the creation fails, it will return
	{
		throw std::runtime_error("Handle is invalid");
	}
	else                                 // Save Raw image         
	{ 
		::WriteFile(hFile, pbuffer, dwImageSize, &dwBytesRead, NULL);
		CloseHandle(hFile);
	}
}