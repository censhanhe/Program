#ifndef		__GAIA_THREAD_INDP_H__
#define		__GAIA_THREAD_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#else
#	include <pthread.h>
#endif

namespace GAIA
{
	namespace THREAD
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static DWORD WINAPI thread_procedure(GAIA::GVOID* p){Thread* pThread = static_cast<Thread*>(p); pThread->WorkProcedure(); return 0;}
	#else
		static GAIA::GVOID* thread_procedure(GAIA::GVOID* p){Thread* pThread = static_cast<Thread*>(p); pThread->WorkProcedure(); pthread_exit(0);}
	#endif
		GAIA_DEBUG_CODEPURE_MEMFUNC Thread::Thread(){m_stacksize = 1024 * 1024; m_state = THREAD_STATE_INVALID; m_pThread = GNULL;}
		GAIA_DEBUG_CODEPURE_MEMFUNC Thread::~Thread()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_pThread != GNULL)
			{
				::WaitForSingleObject((HANDLE)m_pThread, INFINITE);
				::CloseHandle((HANDLE)m_pThread);
			}
		#else
			if(m_pThread != GNULL)
			{
				pthread_join(*(pthread_t*)m_pThread, GNULL);
				delete (pthread_t*)m_pThread;
			}
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Run()
		{
			if(m_pThread != GNULL)
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_pThread = ::CreateThread(GNULL, m_stacksize, thread_procedure, static_cast<GAIA::GVOID*>(this), 0, GNULL);
			if(m_pThread == GNULL)
				return GAIA::False;
			m_state = THREAD_STATE_RUNING;
			return GAIA::True;
		#else
			pthread_attr_t attr;
			if(pthread_attr_init(&attr) != 0)
				return GAIA::False;
			if(pthread_attr_setstacksize(&attr, m_stacksize) != 0)
				return GAIA::False;
			m_pThread = new pthread_t;
			if(pthread_create((pthread_t*)m_pThread, &attr, thread_procedure, static_cast<GAIA::GVOID*>(this)) != 0)
				return GAIA::False;
			pthread_attr_destroy(&attr);
			m_state = THREAD_STATE_RUNING;
			return GAIA::True;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Wait() const
		{
			if(m_pThread != GNULL)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				if(m_pThread != GNULL)
				{
					if(::WaitForSingleObject((HANDLE)m_pThread, INFINITE) == WAIT_OBJECT_0)
					{
						::CloseHandle((HANDLE)m_pThread);
						(const_cast<Thread*>(this))->m_pThread = GNULL;
						(const_cast<Thread*>(this))->m_state = THREAD_STATE_INVALID;
						return GAIA::True;
					}
				}
			#else
				if(m_pThread != GNULL)
				{
					pthread_join(*(pthread_t*)m_pThread, GNULL);
					delete (pthread_t*)(const_cast<Thread*>(this))->m_pThread;
					(const_cast<Thread*>(this))->m_pThread = GNULL;
					(const_cast<Thread*>(this))->m_state = THREAD_STATE_INVALID;
					return GAIA::True;
				}
			#endif
			}
			return GAIA::False;
		}
	};
};

#endif
