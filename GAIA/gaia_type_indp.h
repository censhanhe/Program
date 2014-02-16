#ifndef		__GAIA_TYPE_INDP_H__
#define		__GAIA_TYPE_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
#	include <libkern/OSAtomic.h>
#else
#	include <asm/atomic.h>
#endif

namespace GAIA
{
	GINL GAIA::NM RefObject::Reference()
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		return InterlockedIncrement(&m_nRef);
	#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
		#if GAIA_MACHINE == GAIA_MACHINE64
			return OSAtomicIncrement64(&m_nRef);
		#else
			return OSAtomicIncrement32(&m_nRef);
		#endif
	#else
		return atomic_inc_return(&m_nRef);
	#endif
	}
	GINL GAIA::NM RefObject::Release()
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		GAIA::NM nNew = InterlockedIncrement(&m_nRef);
	#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
		#if GAIA_MACHINE == GAIA_MACHINE64
			GAIA::NM nNew = OSAtomicDecrement64(&m_nRef);
		#else
			GAIA::NM nNew = OSAtomicDecrement32(&m_nRef);
		#endif
	#else
		GAIA::NM nNew = atomic_dec_return(&m_nRef);
	#endif
		if(nNew == 0 && !m_bDestructing)
		{
			m_bDestructing = true;
			this->Destruct();
			delete this;
		}
		return nNew;
	}
};

#endif