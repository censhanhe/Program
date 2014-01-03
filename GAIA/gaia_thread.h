#ifndef		__GAIA_THREAD_H__
#define		__GAIA_THREAD_H__

namespace GAIA
{
	namespace THREAD
	{
		class Thread
		{
		public:
			ENUM_BEGIN(THREAD_STATE)
				THREAD_STATE_RUNING,
				THREAD_STATE_SUSPEND, 
			ENUM_END

		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Thread(){m_stacksize = 1024 * 1024; m_state = THREAD_STATE_INVALID; m_pThread = GNULL;}
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual ~Thread(){}

			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetStackSize(const GAIA::UM& size){m_stacksize = size;}
			GAIA_DEBUG_CODEPURE_MEMFUNC const GAIA::UM& GetStackSize() const{return m_stacksize;}
			GAIA_DEBUG_CODEPURE_MEMFUNC THREAD_STATE GetState() const{return m_state;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Run();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Wait(const GAIA::U32& uWaitTimeInMilliSecond) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Suspend();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Terminate();

			virtual GAIA::GVOID WorkProcedure() = 0;

		private:
			GAIA::UM m_stacksize;
			THREAD_STATE m_state;
			GAIA::GVOID* m_pThread;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_thread_indp.h"
#endif

#endif