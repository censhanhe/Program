#ifndef 	__GAIA_SYNC_ATOMIC_INDP_H__
#define 	__GAIA_SYNC_ATOMIC_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
#	include <libkern/OSAtomic.h>
#else
#	include <asm/atomic_32.h>
#endif

namespace GAIA
{
	namespace SYNC
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Atomic::Increase()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			#if GAIA_MACHINE == GAIA_MACHINE64
				return InterlockedIncrement(&m_n);
			#else
				return InterlockedIncrement((volatile GAIA::NM*)&m_n);
			#endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			return OSAtomicIncrement64(&m_n);
		#else
			return atomic_inc_return((GAIA::N32*)&m_n);
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Atomic::Decrease()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			#if GAIA_MACHINE == GAIA_MACHINE64
				return InterlockedDecrement(&m_n);
			#else
				return InterlockedDecrement((volatile GAIA::NM*)&m_n);
			#endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			return OSAtomicDecrement64(&m_n);
		#else
			return atomic_dec_return((GAIA::N32*)&m_n);
		#endif
		}
	};
};

#endif
