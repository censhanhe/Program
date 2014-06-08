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
#	if GAIA_COMPILER != GAIA_COMPILER_GCC || GAIA_COMPILER_GCCVER < GAIA_COMPILER_GCCVER_USESYNCXX
#		include <asm/atomic.h>
#	endif
#endif

namespace GAIA
{
	GINL GAIA::NM RefObject::Reference()
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
	#	if GAIA_MACHINE == GAIA_MACHINE64
			return InterlockedIncrement64(&m_nRef);
	#	else
			return InterlockedIncrement(&m_nRef);
	#	endif
	#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
	#	if GAIA_MACHINE == GAIA_MACHINE64
			return OSAtomicIncrement64(&m_nRef);
	#	else
			return OSAtomicIncrement32(&m_nRef);
	#	endif
	#else
	#	if GAIA_COMPILER == GAIA_COMPILER_GCC && GAIA_COMPILER_GCCVER >= GAIA_COMPILER_GCCVER_USESYNCXX
			return __sync_add_and_fetch(&m_nRef, 1);
	#	else
			return atomic_inc_return(&m_nRef);
	#	endif
	#endif
	}
	GINL GAIA::NM RefObject::Release()
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
	#	if GAIA_MACHINE == GAIA_MACHINE64
			GAIA::NM nNew = InterlockedDecrement64(&m_nRef);
	#	else
			GAIA::NM nNew = InterlockedDecrement(&m_nRef);
	#	endif
	#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
	#	if GAIA_MACHINE == GAIA_MACHINE64
			GAIA::NM nNew = OSAtomicDecrement64(&m_nRef);
	#	else
			GAIA::NM nNew = OSAtomicDecrement32(&m_nRef);
	#	endif
	#else
	#	if GAIA_COMPILER == GAIA_COMPILER_GCC && GAIA_COMPILER_GCCVER >= GAIA_COMPILER_GCCVER_USESYNCXX
			GAIA::NM nNew = __sync_sub_and_fetch(&m_nRef, 1);
	#	else
			GAIA::NM nNew = atomic_dec_return(&m_nRef);
	#	endif
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
