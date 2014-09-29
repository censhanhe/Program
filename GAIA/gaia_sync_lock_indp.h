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
			::InitializeCriticalSection((CRITICAL_SECTION*)m_head);
		#else
			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);
			pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
			pthread_mutex_init((pthread_mutex_t*)m_head, &attr);
			pthread_mutexattr_destroy(&attr);
		#endif
		}
		GINL Lock::~Lock()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::DeleteCriticalSection((CRITICAL_SECTION*)m_head);
		#else
			pthread_mutex_destroy((pthread_mutex_t*)m_head);
		#endif
		}
		GINL GAIA::GVOID Lock::Enter()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::EnterCriticalSection((CRITICAL_SECTION*)m_head);
		#else
			pthread_mutex_lock((pthread_mutex_t*)m_head);
		#endif
		}
		GINL GAIA::GVOID Lock::Leave()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::LeaveCriticalSection((CRITICAL_SECTION*)m_head);
		#else
			pthread_mutex_unlock((pthread_mutex_t*)m_head);
		#endif
		}
	};
};

#endif
