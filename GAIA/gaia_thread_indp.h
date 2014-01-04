#ifndef		__GAIA_THREAD_INDP_H__
#define		__GAIA_THREAD_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif

namespace GAIA
{
	namespace THREAD
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static DWORD WINAPI thread_procedure(GAIA::GVOID* p){Thread* pThread = static_cast<Thread*>(p); pThread->WorkProcedure(); return 0;}
	#endif
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Run()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_pThread = ::CreateThread(GNULL, m_stacksize, thread_procedure, static_cast<GAIA::GVOID*>(this), 0, GNULL);
			if(m_pThread == GNULL)
				return GAIA::False;
			m_state = THREAD_STATE_RUNING;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Wait(const GAIA::U32& uWaitTimeInMilliSecond) const
		{
			if(m_pThread != GNULL)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				if(::WaitForSingleObject((HANDLE)m_pThread, uWaitTimeInMilliSecond) == WAIT_OBJECT_0)
					return GAIA::True;
			#endif
				return GAIA::False;
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Suspend()
		{
			if(m_pThread != GNULL)
			{
				if(m_state == THREAD_STATE_SUSPEND)
					return GAIA::True;
			#if GAIA_OS == GAIA_OS_WINDOWS
				if(::SuspendThread((HANDLE)m_pThread) != 0xFFFFFFFF)
				{
					m_state = THREAD_STATE_SUSPEND;
					return GAIA::True;
				}
			#endif
				return GAIA::False;
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Thread::Terminate()
		{
			if(m_pThread != GNULL)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				if(::TerminateThread((HANDLE)m_pThread, 0))
				{
					m_state = THREAD_STATE_INVALID;
					return GAIA::True;
				}
			#endif
				return GAIA::False;
			}
			return GAIA::False;
		}
	};
};

#endif