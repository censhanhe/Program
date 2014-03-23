#ifndef		__GAIA_THREAD_H__
#define		__GAIA_THREAD_H__

namespace GAIA
{
	namespace THREAD
	{
		class Thread : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(THREAD_STATE)
				THREAD_STATE_RUNING,
			GAIA_ENUM_END(THREAD_STATE)
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Thread();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual ~Thread();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetStackSize(const GAIA::UM& size){m_stacksize = size;}
			GAIA_DEBUG_CODEPURE_MEMFUNC const GAIA::UM& GetStackSize() const{return m_stacksize;}
			GAIA_DEBUG_CODEPURE_MEMFUNC THREAD_STATE GetState() const{return m_state;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Run();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Wait() const;
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
