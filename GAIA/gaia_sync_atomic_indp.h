#ifndef 	__GAIA_SYNC_ATOMIC_INDP_H__
#define 	__GAIA_SYNC_ATOMIC_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
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
	namespace SYNC
	{
		GINL GAIA::N64 Atomic::Increase()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			#if GAIA_MACHINE == GAIA_MACHINE64
				return InterlockedIncrement64(&m_n);
			#else
				return InterlockedIncrement((volatile GAIA::NM*)&m_n);
			#endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			return OSAtomicIncrement64(&m_n);
		#else
		#	if GAIA_COMPILER == GAIA_COMPILER_GCC && GAIA_COMPILER_GCCVER >= GAIA_COMPILER_GCCVER_USESYNCXX
				return __sync_add_and_fetch((GAIA::N32*)&m_n, 1) + 1;
		#	else
				return atomic_inc_return((GAIA::N32*)&m_n);
		#	endif
		#endif
		}
		GINL GAIA::N64 Atomic::Decrease()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			#if GAIA_MACHINE == GAIA_MACHINE64
				return InterlockedDecrement64(&m_n);
			#else
				return InterlockedDecrement((volatile GAIA::NM*)&m_n);
			#endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			return OSAtomicDecrement64(&m_n);
		#else
		#	if GAIA_COMPILER == GAIA_COMPILER_GCC && GAIA_COMPILER_GCCVER >= GAIA_COMPILER_GCCVER_USESYNCXX
				return __sync_sub_and_fetch((GAIA::N32*)&m_n, 1) - 1;
		#	else
				return atomic_dec_return((GAIA::N32*)&m_n);
		#	endif
		#endif
		}
		GINL GAIA::N64 Atomic::Add(const GAIA::N64& src)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			#if GAIA_MACHINE == GAIA_MACHINE64
				return InterlockedExchangeAdd64(&m_n, src) + src;
			#else
				return InterlockedExchangeAdd((volatile GAIA::NM*)&m_n, (GAIA::NM)src) + src;
			#endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			return OSAtomicAdd64(src, &m_n);
		#else
		#	if GAIA_COMPILER == GAIA_COMPILER_GCC && GAIA_COMPILER_GCCVER >= GAIA_COMPILER_GCCVER_USESYNCXX
				return __sync_add_and_fetch((GAIA::N32*)&m_n, (GAIA::N32)src) + src;
		#	else
				return atomic_add_return((GAIA::N32)src, (GAIA::N32*)&m_n);
		#	endif
		#endif
		}
		GINL GAIA::N64 Atomic::Add(const Atomic& src){return this->Add((GAIA::N64)src);}
	};
};

#endif
