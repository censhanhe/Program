#ifndef		__GAIA_THREAD_H__
#define		__GAIA_THREAD_H__

namespace GAIA
{
	namespace THREAD
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::UM threadid();
		class Thread : public GAIA::Entity
		{
		public:
			GAIA_ENUM_BEGIN(THREAD_STATE)
				THREAD_STATE_RUNING,
			GAIA_ENUM_END(THREAD_STATE)
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Thread();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual ~Thread();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetStackSize(const GAIA::U32& size){m_stacksize = size;}
			GAIA_DEBUG_CODEPURE_MEMFUNC const GAIA::U32& GetStackSize() const{return m_stacksize;}
			GAIA_DEBUG_CODEPURE_MEMFUNC THREAD_STATE GetState() const{return m_state;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Run();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Wait() const;
			virtual GAIA::GVOID WorkProcedure() = 0;
		private:
			GAIA::U32 m_stacksize;
			THREAD_STATE m_state;
			GAIA::GVOID* m_pThread;
		};
	};
};

#include "gaia_thread_indp.h"

#endif
