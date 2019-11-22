#include "stdafx.h"
#include "FileVersion.h"

CFileVersion::CFileVersion(CString strPath)
{
	m_strPath = strPath;
}

CFileVersion::~CFileVersion()
{
}

//--------------------------------------------------------------
/**
\brief   Get all files version information,The information is separated by \n

\return  strRet   all versions information
*/
//--------------------------------------------------------------
CString CFileVersion::GetFullVersion()
{
	CString strRet;
	strRet = "FileVersion: " + GetFileVersion() + "\n"; 
	strRet += "Description: " + GetFileDescription() +"\n";
	strRet += "Copyright: " + GetLegalCopyright() +"\n";
	strRet += "Comments: " + GetComments() + "\n";
	strRet += "ProductVersion: " + GetProductVersion() +"\n";
	strRet += "ProductName: " + GetProductName() +"\n";
	strRet += "PrivateBuild Description: " + GetPrivateBuild() +"\n";
	strRet += "CompanyName: " + GetCompanyName() +"\n";
	strRet += "LegalTrademarks: " + GetLegalTrademarks() +"\n";
	strRet += "InternalName: " + GetInternalName() +"\n";
	strRet += "SpecialBuild Description: " + GetSpecialBuild() +"\n";
	strRet += "OriginalFilename: " + GetOriginalFilename() +"\n";	
	return strRet;
}

//--------------------------------------------------------------
/**
\brief    Get Comments

\return   Comments
*/
//--------------------------------------------------------------
CString CFileVersion::GetComments()
{
	return GetVer("Comments");
}

//--------------------------------------------------------------
/**
\brief    Get InternalName

\return   InternalName
*/
//--------------------------------------------------------------
CString CFileVersion::GetInternalName()
{
	return GetVer("InternalName");
}

//--------------------------------------------------------------
/**
\brief    Get ProductName

\return   ProductName
*/
//--------------------------------------------------------------
CString CFileVersion::GetProductName()
{
	return GetVer("ProductName");
}

//--------------------------------------------------------------
/**
\brief    Get CompanyName

\return   CompanyName
*/
//--------------------------------------------------------------
CString CFileVersion::GetCompanyName()
{
	return GetVer("CompanyName");
}

//--------------------------------------------------------------
/**
\brief   Get Copyright

\return   Copyright
*/
//--------------------------------------------------------------
CString CFileVersion::GetLegalCopyright()
{
	return GetVer("LegalCopyright");
}

//--------------------------------------------------------------
/**
\brief    Get ProductVersion

\return   ProductVersion
*/
//--------------------------------------------------------------
CString CFileVersion::GetProductVersion()
{
	return GetVer("ProductVersion");
}

//--------------------------------------------------------------
/**
\brief    Get file description

\return   file description
*/
//--------------------------------------------------------------
CString CFileVersion::GetFileDescription()
{
	return GetVer("FileDescription");
}

//--------------------------------------------------------------
/**
\brief    Get legal trademarks

\return   legal trademarks
*/
//--------------------------------------------------------------
CString CFileVersion::GetLegalTrademarks()
{
	return GetVer("LegalTrademarks");
}

//--------------------------------------------------------------
/**
\brief    Get private build description

\return   private build description
*/
//--------------------------------------------------------------
CString CFileVersion::GetPrivateBuild()
{
	return GetVer("PrivateBuild");
}

//--------------------------------------------------------------
/**
\brief    Get file version

\return   file version
*/
//--------------------------------------------------------------
CString CFileVersion::GetFileVersion()
{
	return GetVer("FileVersion");
}

//--------------------------------------------------------------
/**
\brief    Get original filename

\return   original filename
*/
//--------------------------------------------------------------
CString CFileVersion::GetOriginalFilename()
{
	return GetVer("OriginalFilename");
}

//--------------------------------------------------------------
/**
\brief    Get special  build description

\return   special  build description
*/
//--------------------------------------------------------------
CString CFileVersion::GetSpecialBuild()
{
	return GetVer("SpecialBuild");
}

//--------------------------------------------------------------
/**
\brief    Get version information
\param    strSubBlock    Get version 

\return   version information
*/
//--------------------------------------------------------------
CString CFileVersion::GetVer(CString strSubBlock)
{
	struct LANGANDCODEPAGE 
	{
		WORD wLanguage;
		WORD wCodePage;
	}*lpTranslate;
	
	int     i             = 0;
	CString strRet        = "";
	DWORD   dwHandle      = 0;
	DWORD   dwInfoSize    = 0;
	UINT    cbTranslate   = 0;
	UINT    dwBytes       = 0;
	char    chBlock[256]  = {0};
	char*   pBuffer       = NULL;
	char*   pData         = NULL;

	// Get file version information length
	dwInfoSize = GetFileVersionInfoSize((char*)(LPCTSTR)m_strPath, &dwHandle);

	if(dwInfoSize != 0)
	{
		// Get version information
		pData = new char[dwInfoSize];
		if( GetFileVersionInfo((char*)(LPCTSTR)m_strPath, 0, dwInfoSize, pData))
		{
			
			VerQueryValue(pData, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &cbTranslate);

			for(i = 0; i <(int)(cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++)
			{
				wsprintf(chBlock, 
					     TEXT("\\StringFileInfo\\%04x%04x\\%s"),
					     lpTranslate[i].wLanguage,
					     lpTranslate[i].wCodePage,
					     strSubBlock);		
				
				VerQueryValue(pData, 
					         chBlock, 
					         (LPVOID*)&pBuffer, 
				          	 &dwBytes); 
				
				strRet.Format("%s", pBuffer);

				break; //only retrieve the first language and code page
			}
		}
		if (pData != NULL)
		{
			delete []pData;
			pData = NULL;
		}
	}

	return strRet;
}