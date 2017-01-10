#ifndef		__GAIA_SYNC_LOCK_INDP_H__
#define		__GAIA_SYNC_LOCK_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <pthread.h>
#endif

namespace GAIA
{
	namespace SYNC
	{
		GINL Lock::Lock()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::InitializeCriticalSection(&m_cs);
		#else
			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);
			pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
			pthread_mutex_init(&m_mutex, &attr);
			pthread_mutexattr_destroy(&attr);
		#endif
		}
		GINL Lock::~Lock()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::DeleteCriticalSection(&m_cs);
		#else
			pthread_mutex_destroy(&m_mutex);
		#endif
		}
		GINL GAIA::GVOID Lock::Enter()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::EnterCriticalSection(&m_cs);
		#else
			pthread_mutex_lock(&m_mutex);
		#endif
		}
		GINL GAIA::GVOID Lock::Leave()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::LeaveCriticalSection(&m_cs);
		#else
			pthread_mutex_unlock(&m_mutex);
		#endif
		}
	};
};

#endif
