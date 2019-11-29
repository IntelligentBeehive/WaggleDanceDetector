//------------------------------------------------------------------------
/**
\file		GXStringCPP.h
\brief		A string class which is a clone of std::string.
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------
#pragma once

#pragma warning(push)
#pragma warning(disable: 4251) // class 'xxx' needs to have dll-interface to be used by clients of class 'yyy'
#include <string>
#include <iostream>
#include "GXIAPIBase.h"

#pragma pack(push, 8)

#define GXSTRING_NPOS size_t(-1)

namespace GxIAPICPP
{
	/// A string class which is a clone of std::string
	class GXIAPICPP_API gxstring
	{
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
		/// Helper class for returning wchar_t* on the stack
		class GXIAPICPP_API gxwchar 
		{
		public:
			/// Constructor taking ownership of the memory block allocated with new on the heap
			explicit gxwchar( const wchar_t *pBuffer = NULL );

			/// copy constructor taking ownership
			gxwchar( gxwchar& _gwchar );

			/// cast operator to (wchar_t*)
			operator const wchar_t *() const;

			/// destructor
			~gxwchar();
		protected:
			/// the memory block owned by this class
			const wchar_t *m_pBuffer;

		private:
			/// no assignment constructor
			gxwchar& operator=( const gxwchar& );

		};

#endif

		// Ctor / Dtor
		// -------------------------------------------------------------------------
	public:
		gxstring                ();
		gxstring                ( const char *pc );
		gxstring                ( size_t count, char ch );
		gxstring                ( const gxstring &str );
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
		explicit gxstring   ( const wchar_t *pBufferUTF16 );
#endif
		virtual  ~gxstring      ( void );

		// Data access
		// -------------------------------------------------------------------------
	public:
		virtual gxstring &  append                ( const gxstring &str );
		virtual gxstring &  append                ( size_t count, char ch );
		virtual gxstring &  assign                ( const gxstring &str );
		virtual gxstring &  assign                ( size_t count, char ch );
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
		virtual gxstring &  assign            ( const wchar_t *pStringUTF16 );
#endif
		virtual int         compare               ( const gxstring &str )   const;
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
		virtual gxwchar w_str                 ( void )                  const;
#endif
		virtual const char *c_str                 ( void )                  const;
		virtual bool        empty                 ( void )                  const;
		virtual size_t      find                  ( char ch, size_t offset = 0 ) const;
		virtual size_t      find                  ( const gxstring &str, size_t offset = 0 ) const;
		virtual size_t      find                  ( const gxstring &str, size_t offset, size_t count ) const;
		virtual size_t      find                  ( const char* pc, size_t offset = 0) const;
		virtual size_t      find                  ( const char* pc, size_t offset, size_t count ) const;
		virtual size_t      length                ( void )                  const;
		virtual size_t      size                  ( void )                  const;
		virtual void        resize                ( size_t n );
		virtual size_t      max_size              ( )                       const;
		virtual    gxstring    substr             ( size_t offset = 0, size_t count = GXSTRING_NPOS ) const;
		virtual size_t find_first_of              ( const gxstring &str, size_t offset = 0 ) const;
		virtual size_t find_first_not_of          ( const gxstring &str, size_t offset = 0 ) const;
		static size_t      _npos                  ( void );
		virtual void        swap                  ( gxstring &Right );


		// Operators
		// -------------------------------------------------------------------------
	public:
		bool                operator !=           ( const gxstring &str )   const;
		bool                operator !=           ( const char *pc )        const;
		gxstring &          operator +=           ( const gxstring &str );
		gxstring            operator +=           ( const gxstring &str )   const;
		gxstring &          operator +=           ( char ch );
		gxstring            operator +=           ( char ch )               const;
		gxstring &          operator =            ( const gxstring &str );
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
		gxstring &          operator =        ( const wchar_t *pStringUTF16 );
#endif
		bool                operator ==           ( const gxstring &str )   const;
		bool                operator ==           ( const char *pc )        const;
		bool                operator <            ( const gxstring &str )   const;
		bool                operator >            ( const gxstring &str )   const;
		operator const char * ( void )                  const;
		void                operator delete       ( void *pWhere );
		void                operator delete       ( void *pWhere, void *pNewWhere );
		void *              operator new          ( size_t uiSize );
		void *              operator new          ( size_t uiSize, void *pWhere );
		GXIAPICPP_API
			friend gxstring     operator +        ( const gxstring &left, const gxstring &right );
		GXIAPICPP_API
			friend gxstring     operator +        ( const gxstring &left, const char *right );
		GXIAPICPP_API
			friend gxstring     operator +        ( const char *left, const gxstring &right );

		// Member
		// -------------------------------------------------------------------------
	private:
		// redundant pointer to make the possible to see the contents of the string in the debugger
		const char* m_psz;
		// actual std::string object
		uint8_t m_opaqueData[64];

		const std::string& GetInternalString() const;
		std::string& GetInternalString();

		// Constants
		// -------------------------------------------------------------------------
	public:
		// Beware : this static member prevents delay loading
		// use _npos() instead
		static const size_t npos;
	};

	GXIAPICPP_API
		std::istream &  getline ( std::istream& is, GxIAPICPP::gxstring& str );
	GXIAPICPP_API
		std::istream &  getline ( std::istream& is, GxIAPICPP::gxstring& str, char delim );
}

///STL operator out
inline std::ostream & operator <<(std::ostream &ostr, const GxIAPICPP::gxstring &str) { return ostr << str.c_str(); }

/// STL operator in
inline std::istream & operator >>(std::istream &istr, GxIAPICPP::gxstring &str)
{
	std::string tmp;
	istr >> tmp;
	str = tmp.c_str();
	return istr;
}

#pragma pack(pop)
#pragma warning(pop)

