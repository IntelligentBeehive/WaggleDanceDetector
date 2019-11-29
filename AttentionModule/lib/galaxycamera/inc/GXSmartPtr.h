//------------------------------------------------------------------------
/**
\file		GXSmartPtr.h
\brief		Definition of template GXSmartPtr
\Date       2019-01-04
\Version    1.1.1901.9041
*/
//------------------------------------------------------------------------
#ifndef GX_SMART_POINTER_H
#define GX_SMART_POINTER_H

#if defined (_WIN32)
#include "windows.h"
#endif

#pragma warning(push)
#pragma warning(disable: 4251) // class 'xxx' needs to have dll-interface to be used by clients of class 'yyy'
#pragma warning(disable: 4150)

#ifndef GXIAPICPP_EXPORTS
#pragma comment(lib, "GxIAPICPPEx.lib")
#endif 

/**
\brief A Reference Counting Class
*/
class GXSPCountedBase
{
private:
	GXSPCountedBase( GXSPCountedBase const & );
	GXSPCountedBase & operator= ( GXSPCountedBase const & );

	LONG m_nUseCount;        // #shared

public:

	/// Default constructor
	volatile GXSPCountedBase(): m_nUseCount(1)
	{
	}

	virtual ~GXSPCountedBase() // nothrow
	{
	}

	/// Count plus one, Thread Safety
	void AddRefCopy()
	{
		InterlockedIncrement(&m_nUseCount);
	}

	/// Count minus one, Thread Safety
	LONG Release() // nothrow
	{
		return InterlockedDecrement(&m_nUseCount);
	}

	LONG* GetUsePtr()
	{
		return &m_nUseCount;
	}

};

#pragma optimize("", off)
template<typename T>
class  GXSmartPtr
{
public:

	/// Default constructor
	explicit GXSmartPtr(T*p=0):m_ptr(p)
	{
		m_pUse = new GXSPCountedBase();
	}

	/// Constructor from GXSmartPtr ref type.
	GXSmartPtr(const GXSmartPtr& src):m_ptr(src.m_ptr),m_pUse(src.GetCountBasePtr())
	{		
#if defined (_WIN32)
		m_pUse->AddRefCopy();
#elif defined (__linux__)
		//Linux TODO
#else
#   error No/unknown platform thread support
#endif
	}

	///Assign GXSmartPtr Pointer
	GXSmartPtr&operator=(const GXSmartPtr&rhs)
	{
#if defined (_WIN32)
		rhs.GetCountBasePtr()->AddRefCopy();
#elif defined (__linux__)
		//Linux TODO
#else
#   error No/unknown platform thread support
#endif		
		decrUse();
		m_ptr=rhs.m_ptr;
		m_pUse=rhs.GetCountBasePtr();
		return *this;
	}

	/// Dereferencing
	T* operator->()
	{
		if(m_ptr)
		{
			return m_ptr;
		}
		else
		{
			throw CGalaxyException(GX_STATUS_ERROR,"Access through NULL pointer");
		}		
	}

	/// Dereferencing
	const T* operator->()const
	{
		if(m_ptr)
		{
			return m_ptr;
		}
		else
		{
			throw CGalaxyException(GX_STATUS_ERROR,"Access through NULL pointer");
		}		
	}

	/// Dereferencing
	T &operator*()
	{
		if(m_ptr)
		{
			return *m_ptr;
		}
		else
		{
			throw CGalaxyException(GX_STATUS_ERROR,"Access through NULL pointer");
		}		
	}

	/// Dereferencing
	const T &operator*()const
	{
		if(m_ptr)
		{
			return *m_ptr;
		}
		else
		{
			throw CGalaxyException(GX_STATUS_ERROR,"Access through NULL pointer");
		}		
	}

	/// Get the reference count
	LONG* getUse() const throw()
	{
		return m_pUse->GetUsePtr();
	}

	/// Get the underlying raw pointer
	T* getPtr() const throw()
	{
		return m_ptr;
	}
	
	/// true if the pointer is not valid
    bool IsNull(void) const
    {
        return m_ptr == NULL;
    }

	/// pointer equal
    bool operator == (const GXSmartPtr<T>& objAnother) const
    {
        return m_ptr == objAnother.m_ptr;
    }

	/// pointer equal
    bool operator == (const T* pT) const
    {
        return m_ptr == pT;
    }

	/// Destructor
	virtual ~GXSmartPtr()
	{
		decrUse();
	}

	template <class U>
	GXSmartPtr(const GXSmartPtr<U>& ptr, T* p) :
	m_pUse(ptr.GetCountBasePtr())
	{
#if defined (_WIN32)
		m_pUse->AddRefCopy();
#elif defined (__linux__)
		//Linux TODO
#else
#   error No/unknown platform thread support
#endif		
		m_ptr = p;   
	}

	template<class T, class U>
	friend GXSmartPtr<T> gxdynamic_pointer_cast(const GXSmartPtr<U>& ptr);

	GXSPCountedBase* GetCountBasePtr() const throw()
	{
		return m_pUse;
	}

private:
	void decrUse()
	{
#if defined (_WIN32)
		if(0 == m_pUse->Release())
		{
			delete m_ptr;
			m_ptr = NULL;
			delete m_pUse;
			m_pUse = NULL;
		}
#elif defined (__linux__)
		//Linux TODO
#else
#   error No/unknown platform thread support
#endif
	}

	T* m_ptr;				  ///< Underlying raw pointer
	GXSPCountedBase* m_pUse;  ///< The reference count
};
#pragma optimize("", on)
// dynamic cast of GXSmartPtr
template<class T, class U>
GXSmartPtr<T> gxdynamic_pointer_cast(const GXSmartPtr<U>& ptr) // never throws
{
	T* p = dynamic_cast<T*>(ptr.getPtr());
	if (NULL != p)
	{
		return GXSmartPtr<T>(ptr, p);
	}
	else
	{
		return GXSmartPtr<T>();
	}
}

#pragma warning(pop)

#endif //GX_SMART_POINTER_H