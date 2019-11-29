//------------------------------------------------------------------------
/**
\file		GXStringVector.h
\brief		A vector of gxstrings which is a clone of std::vector<std::string>
\Date       2016-8-09
\Version    1.1.1608.9091
*/
//------------------------------------------------------------------------

#pragma once
#include "GXStringCPP.h"

#pragma pack(push, 8)


#if defined (_WIN32) || (defined (__GNUC__) && (defined (__linux__) || defined(__APPLE__)))


namespace std
{
    template <class T> class allocator;
    template <class T, class Allocator > class vector;
}

namespace GxIAPICPP
{

    /**
    \brief A vector of gxstrings which is a clone of std::vector<std::string>
    */
  class GXIAPICPP_API gxstring_vector
  {
  // Nested types
  // ---------------------------------------------------------------------------
  public:
    class GXIAPICPP_API const_iterator
    {
    // Ctor / Dtor
    // -------------------------------------------------------------------------
    public:
                              const_iterator    ( gxstring *pStr = 0 );

    // Operators
    // -------------------------------------------------------------------------
    public:
      const gxstring &        operator *        ( void )                  const;
      const gxstring *        operator ->       ( void )                  const;
      const_iterator &        operator ++       ( void );
      const_iterator          operator ++       ( int );
      const_iterator &        operator --       ( void );
      const_iterator          operator --       ( int );
      const_iterator &        operator +=       ( intptr_t iInc );
      const_iterator          operator +        ( intptr_t iInc )         const;
      const_iterator &        operator -=       ( intptr_t iDec );
      intptr_t                operator -        ( const const_iterator &iter ) const;
      const_iterator          operator -        ( intptr_t iDec )         const;
      const gxstring &        operator []       ( intptr_t iIndex )       const;
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
      gxstring *              _ps;
    };

    class GXIAPICPP_API iterator :
      public const_iterator
    {
    // Ctor / Dtor
    // -------------------------------------------------------------------------
    public:
                              iterator          ( gxstring *pStr = 0 );

    // Operators
    // -------------------------------------------------------------------------
    public:
      gxstring &              operator *        ( void )                  const;
      gxstring *              operator ->       ( void )                  const;
      iterator &              operator ++       ( void );
      iterator                operator ++       ( int );
      iterator &              operator --       ( void );
      iterator                operator --       ( int );
      iterator &              operator +=       ( intptr_t iInc );
      iterator                operator +        ( intptr_t iInc )         const;
      iterator &              operator -=       ( intptr_t iDec );
      intptr_t                operator -        ( const iterator &iter )  const;
      iterator                operator -        ( intptr_t iDec )         const;
      gxstring &              operator []       ( intptr_t iIndex )       const;
      GXIAPICPP_API
      friend iterator         operator +        ( intptr_t iInc, const iterator &iter);
  };

  // Ctor / Dtor
  // ---------------------------------------------------------------------------
  public:
                              gxstring_vector   ( void );
    explicit                  gxstring_vector   ( size_t uiSize, const gxstring &str = gxstring() );
                              gxstring_vector   ( const gxstring_vector &obj);
    virtual                   ~gxstring_vector  ( void );

  // Element access
  // ---------------------------------------------------------------------------
  public:
    virtual void              assign            ( size_t n, const gxstring &val);
    virtual void              clear             ( void );
    virtual iterator          erase             ( iterator pos );
    virtual gxstring &        at                ( size_t uiIndex );
    virtual const gxstring &  at                ( size_t uiIndex )        const;
    virtual gxstring &        back              ( void );
    virtual const gxstring &  back              ( void )                  const;
    virtual iterator          begin             ( void );
    virtual const_iterator    begin             ( void )                  const;
    virtual size_t            capacity          ( void )                  const;
    virtual iterator          end               ( void );
    virtual const_iterator    end               ( void )                  const;
    virtual gxstring &        front             ( void );
    virtual const gxstring &  front             ( void )                  const;
    virtual size_t            max_size          ( void )                  const;
    virtual size_t            size              ( void )                  const;
    virtual iterator          insert            ( iterator pos, const gxstring &str );
    virtual bool              empty             ( void )                  const;
    virtual void              pop_back          ( void );
    virtual void              push_back         ( const gxstring &str );
    virtual void              resize            ( size_t uiSize, const gxstring &str = gxstring() );
    virtual void              reserve           ( size_t uiSize );

    // Do not use the methods below - they only exist for
    // backwards compatibility
    virtual gxstring_vector & assign            ( const gxstring_vector &obj );
    virtual void              erase             ( size_t uiIndex );
    virtual void              insert            ( size_t uiIndex, const gxstring &str );


  // Operators
  // ---------------------------------------------------------------------------
  public:
    gxstring_vector &         operator =        ( const gxstring_vector &obj );
    gxstring &                operator []       ( size_t uiIndex );
    const gxstring &          operator []       ( size_t uiIndex )        const;
    void                      operator delete   ( void *pWhere );
    void *                    operator new      ( size_t uiSize );

  // Member
  // ---------------------------------------------------------------------------
  private:
      std::vector<gxstring, std::allocator<gxstring> > * const _pv;
  };
}


#else
#   error No known support for shared libraries
#endif

#pragma pack(pop)

