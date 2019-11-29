//------------------------------------------------------------------------
/**
\file		GXDeviceInfoVector.h
\brief		Portable CGXDeviceInfo vector implementation
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------

#pragma once

#ifndef _WIN32
#    include <stdint.h>
#endif

#if defined ( __GNUC__ ) && defined ( __linux__)
#    include <cstddef>
#endif

#if defined (_WIN32) || (defined (__GNUC__) && (defined (__linux__) || defined (__APPLE__)))

// conversion from 'uintptr_t' to 'void *' of greater size
// This is a portability warning
#pragma warning( disable : 4312 )

namespace std
{
	template <class T> class allocator;
	template <class T, class Allocator > class vector;
}

class CGXDeviceInfo;
namespace GxIAPICPP
{
	/**
	\brief     A vector of CGXDeviceInfo object
	*/
	class GXIAPICPP_API TList_vector
	{
		typedef CGXDeviceInfo T;
		// Nested types
		// ---------------------------------------------------------------------------
	public:
		class GXIAPICPP_API const_iterator
		{
			// iterator traits
			// ------------------------------------------------------------------------
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

			// Ctor / Dtor
			// -------------------------------------------------------------------------
		public:
			const_iterator    ( T *pPtr = 0 );

			// Operators
			// -------------------------------------------------------------------------
		public:
			const T &        operator *        ( void )                  const;
			const_iterator &        operator ++       ( void );
			const_iterator          operator ++       ( int );
			const_iterator &        operator --       ( void );
			const_iterator          operator --       ( int );
			const_iterator &        operator +=       ( intptr_t iInc );
			const_iterator          operator +=       ( intptr_t iInc )         const;
			const_iterator          operator +        ( intptr_t iInc )         const;
			const_iterator &        operator -=       ( intptr_t iDec );
			const_iterator          operator -=       ( intptr_t iDec )         const;
			intptr_t                operator -        ( const const_iterator &iter ) const;
			const_iterator          operator -        ( intptr_t iDec )         const;
			const T &        operator []       ( intptr_t iIndex )       const;
			bool                    operator ==       ( const const_iterator &iter ) const;
			bool                    operator !=       ( const const_iterator &iter ) const;
			bool                    operator <        ( const const_iterator &iter ) const;
			bool                    operator >        ( const const_iterator &iter ) const;
			bool                    operator <=       ( const const_iterator &iter ) const;
			bool                    operator >=       ( const const_iterator &iter ) const;
			GXIAPICPP_API
				friend const_iterator   operator +        ( intptr_t iInc, const const_iterator &iter);

			// Member
			// -------------------------------------------------------------------------
		protected:
			T *              _ps;
		};

		class GXIAPICPP_API iterator :
			public const_iterator
		{
		public:
			// iterator traits
			// -------------------------------------------------------------------------
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef const_iterator::difference_type difference_type;
			typedef const_iterator::pointer pointer;
			typedef const_iterator::reference reference;
			// Ctor / Dtor
			// -------------------------------------------------------------------------
		public:
			iterator          ( T *pPtr = 0 );

			// Operators
			// -------------------------------------------------------------------------
		public:
			T &              operator *        ( void )                  const;
			iterator &              operator ++       ( void );
			iterator                operator ++       ( int );
			iterator &              operator --       ( void );
			iterator                operator --       ( int );
			iterator &              operator +=       ( intptr_t iInc );
			iterator                operator +=       ( intptr_t iInc )         const;
			iterator                operator +        ( intptr_t iInc )         const;
			iterator &              operator -=       ( intptr_t iDec );
			iterator                operator -=       ( intptr_t iDec )         const;
			intptr_t                operator -        ( const iterator &iter )  const;
			iterator                operator -        ( intptr_t iDec )         const;
			T &              operator []       ( intptr_t iIndex )       const;
			GXIAPICPP_API
				friend iterator         operator +        ( intptr_t iInc, const iterator &iter);
		};

		// Ctor / Dtor
		// ---------------------------------------------------------------------------
	public:
		TList_vector   ( void );
		explicit                  TList_vector   ( size_t uiSize);
		TList_vector   ( const TList_vector &obj);
		virtual                   ~TList_vector  ( void );

		// Element access
		// ---------------------------------------------------------------------------
	public:
		virtual void              assign            ( size_t n, const T &obj );
		virtual void              clear             ( void );
		virtual iterator          erase             ( iterator pos );
		virtual T &               at                ( size_t uiIndex );
		virtual const T &         at                ( size_t uiIndex )        const;
		virtual T &               back              ( void );
		virtual const T &         back              ( void )                  const;
		virtual iterator          begin             ( void );
		virtual const_iterator    begin             ( void )                  const;
		virtual size_t            capacity          ( void )                  const;
		virtual iterator          end               ( void );
		virtual const_iterator    end               ( void )                  const;
		virtual T &               front             ( void );
		virtual const T &         front             ( void )                  const;
		virtual size_t            max_size          ( void )                  const;
		virtual size_t            size              ( void )                  const;
		virtual iterator          insert            ( iterator pos,  const T& val) ;
		virtual bool              empty             ( void )                  const;
		virtual void              pop_back          ( void );
		virtual void              push_back         ( const T &val );
		virtual void              resize            ( size_t uiSize, const T &val );
		virtual void              reserve           ( size_t uiSize );


		// Do not use - only left in for backwards compatibility!
		virtual void              erase             (size_t uiIndex);
		virtual void              insert            (size_t uiIndex, const T &val);

		// Operators
		// ---------------------------------------------------------------------------
	public:
		TList_vector &         operator =        ( const TList_vector &obj );
		T &                operator []       ( size_t uiIndex );
		const T &          operator []       ( size_t uiIndex )        const;
		void                      operator delete   ( void *pWhere );
		void *                    operator new      ( size_t uiSize );

		// Member
		// ---------------------------------------------------------------------------
	private:
		typedef std::vector<T, std::allocator<T> > vector_t;
		vector_t *_pv;
	};

	//! a list of DeviceInfo references
	typedef TList_vector gxdeviceinfo_vector;
}


#else
#   error No known support for shared libraries
#endif


