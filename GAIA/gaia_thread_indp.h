#ifndef		__GAIA_THREAD_INDP_H__
#define		__GAIA_THREAD_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <pthread.h>
#endif

namespace GAIA
{
	namespace THREAD
	{
		GINL GAIA::UM threadid()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return GSCAST(GAIA::UM)(::GetCurrentThreadId());
		#else
			return GSCAST(GAIA::UM)(pthread_self());
		#endif
		}
	#if GAIA_OS == GAIA_OS_WINDOWS
		static DWORD WINAPI thread_procedure(GAIA::GVOID* p){Thread* pThread = static_cast<Thread*>(p); pThread->WorkProcedure(); return 0;}
	#else
		static GAIA::GVOID* thread_procedure(GAIA::GVOID* p){Thread* pThread = static_cast<Thread*>(p); pThread->WorkProcedure(); pthread_exit(0);}
	#endif
		GINL Thread::~Thread()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_hThread != GNIL)
			{
				::WaitForSingleObject(m_hThread, INFINITE);
				::CloseHandle(m_hThread);
			}
		#else
			if(m_bCreated)
				pthread_join(m_thread, GNIL);
		#endif
		}
		GINL GAIA::BL Thread::Run()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_hThread != GNIL)
				return GAIA::False;
			m_state = STATE_RUNNING;
			m_hThread = ::CreateThread(GNIL, m_stacksize, thread_procedure, static_cast<GAIA::GVOID*>(this), 0, GNIL);
			if(m_hThread == GNIL)
				return GAIA::False;
			return GAIA::True;
		#else
			if(m_bCreated)
				return GAIA::False;
			pthread_attr_t attr;
			if(pthread_attr_init(&attr) != 0)
				return GAIA::False;
			if(pthread_attr_setstacksize(&attr, m_stacksize) != 0)
				return GAIA::False;
			m_state = STATE_RUNNING;
			if(pthread_create(&m_thread, &attr, thread_procedure, static_cast<GAIA::GVOID*>(this)) != 0)
				return GAIA::False;
			pthread_attr_destroy(&attr);
			m_bCreated = GAIA::True;
			return GAIA::True;
		#endif
		}
		GINL GAIA::BL Thread::Wait() const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_hThread != GNIL)
			{
				if(::WaitForSingleObject(m_hThread, INFINITE) == WAIT_OBJECT_0)
				{
					::CloseHandle(m_hThread);
					(const_cast<Thread*>(this))->m_hThread = GNIL;
					(const_cast<Thread*>(this))->m_state = STATE_INVALID;
					return GAIA::True;
				}
			}
		#else
			if(m_bCreated)
			{
				pthread_join(m_thread, GNIL);
				(const_cast<Thread*>(this))->m_bCreated = GAIA::False;
				(const_cast<Thread*>(this))->m_state = STATE_INVALID;
				return GAIA::True;
			}
		#endif
			return GAIA::False;
		}
	};
};

#endif
