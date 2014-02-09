#ifndef 	__GAIA_SYNC_EVENT_INDP_H__
#define 	__GAIA_SYNC_EVENT_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#else
#	include <pthread.h>
#	include <sys/time.h>
#endif

namespace GAIA
{
	namespace SYNC
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC Event::Event()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			*(HANDLE*)m_head = ::CreateEvent(GNULL, FALSE, FALSE, GNULL);
		#else
			pthread_mutex_init((pthread_mutex_t*)m_headmutex, GNULL);
			pthread_cond_init((pthread_cond_t*)m_head, GNULL);
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Event::~Event()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CloseHandle(*(HANDLE*)m_head);
		#else
			pthread_mutex_destroy((pthread_mutex_t*)m_headmutex);
			pthread_cond_destroy((pthread_cond_t*)m_head);
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Event::Fire()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SetEvent(*(HANDLE*)m_head);
		#else
			pthread_mutex_lock((pthread_mutex_t*)m_headmutex);
			{
				if(m_waitcnt > 0)
					pthread_cond_signal((pthread_cond_t*)m_head);
				--m_waitcnt;
			}
			pthread_mutex_unlock((pthread_mutex_t*)m_headmutex);
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Event::Wait(GAIA::U32 uMilliSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::WaitForSingleObject(*(HANDLE*)m_head, uMilliSecond) == WAIT_OBJECT_0)
				return GAIA::True;
			return GAIA::False;
		#else
			GAIA::BL ret = GAIA::False;
			pthread_mutex_lock((pthread_mutex_t*)m_headmutex);
			{
				++m_waitcnt;
				if(m_waitcnt > 0)
				{
					if(uMilliSecond == 0xFFFFFFFF)
					{
						if(pthread_cond_wait((pthread_cond_t*)m_head, (pthread_mutex_t*)m_headmutex) == 0)
							ret = GAIA::True;
					}
					else
					{
						timeval now;
						gettimeofday(&now, GNULL);
						timespec abstime;
						abstime.tv_nsec = now.tv_usec * 1000 + (uMilliSecond % 1000) * 1000000;
						abstime.tv_sec = now.tv_sec + uMilliSecond / 1000;
						if(pthread_cond_timedwait((pthread_cond_t*)m_head, (pthread_mutex_t*)m_headmutex, &abstime) == 0)
							ret = GAIA::True;
					}	
				}
				else
					ret = GAIA::True;
			}
			pthread_mutex_unlock((pthread_mutex_t*)m_headmutex);
			return ret;
		#endif
		}
	};
};

#endif
