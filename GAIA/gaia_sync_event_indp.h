#ifndef 	__GAIA_SYNC_EVENT_INDP_H__
#define 	__GAIA_SYNC_EVENT_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <pthread.h>
#	include <sys/time.h>
#	include <sys/errno.h>
#endif

namespace GAIA
{
	namespace SYNC
	{
		GINL Event::Event()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_hEvent = ::CreateEvent(GNIL, FALSE, FALSE, GNIL);
		#else
			pthread_mutex_init(&m_mutex, GNIL);
			pthread_cond_init(&m_cond, GNIL);
			m_waitcnt = 0;
		#endif
		}
		GINL Event::~Event()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CloseHandle(m_hEvent);
		#else
			pthread_mutex_destroy(&m_mutex);
			pthread_cond_destroy(&m_cond);
		#endif
		}
		GINL GAIA::GVOID Event::Fire()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SetEvent(m_hEvent);
		#else
			pthread_mutex_lock(&m_mutex);
			{
				if(m_waitcnt > 0)
					pthread_cond_signal(&m_cond);
				--m_waitcnt;
			}
			pthread_mutex_unlock(&m_mutex);
		#endif
		}
		GINL GAIA::BL Event::Wait(GAIA::U32 uMilliSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::WaitForSingleObject(m_hEvent, uMilliSecond) == WAIT_OBJECT_0)
				return GAIA::True;
			return GAIA::False;
		#else
			GAIA::BL ret = GAIA::False;
			pthread_mutex_lock(&m_mutex);
			{
				++m_waitcnt;
				if(m_waitcnt > 0)
				{
					if(uMilliSecond == 0xFFFFFFFF)
					{
						if(pthread_cond_wait(&m_cond, &m_mutex) == 0)
							ret = GAIA::True;
					}
					else
					{
						timeval now;
						gettimeofday(&now, GNIL);
						timespec abstime;
						abstime.tv_nsec = now.tv_usec * 1000 + (uMilliSecond % 1000) * 1000 * 1000;
						abstime.tv_sec = now.tv_sec + uMilliSecond / 1000;
						abstime.tv_sec += abstime.tv_nsec / (1000 * 1000 * 1000);
						abstime.tv_nsec = abstime.tv_nsec % (1000 * 1000 * 1000);
						GAIA::N32 nWaitResult = pthread_cond_timedwait(&m_cond, &m_mutex, &abstime);
						if(nWaitResult == ETIMEDOUT)
							--m_waitcnt;
						else if(nWaitResult == 0)
							ret = GAIA::True;
					}
				}
				else
					ret = GAIA::True;
			}
			pthread_mutex_unlock(&m_mutex);
			return ret;
		#endif
		}
	};
};

#endif
