#ifndef		__GAIA_THREAD_H__
#define		__GAIA_THREAD_H__

namespace GAIA
{
	namespace THREAD
	{
		GINL GAIA::UM threadid();
		class Thread : public GAIA::Entity
		{
		public:
			GAIA_ENUM_BEGIN(STATE)
				STATE_RUNNING,
			GAIA_ENUM_END(STATE)
		public:
			GINL Thread(){this->init();}
			GINL virtual ~Thread();
			GINL GAIA::GVOID SetStackSize(const GAIA::U32& size)
			{
			#ifdef GAIA_DEBUG_PLATFORM
				GAIA_AST(m_stacksize % 1024 == 0);
				GAIA_AST(m_stacksize / 1024 >= 10);
			#endif
				m_stacksize = size;
			}
			GINL const GAIA::U32& GetStackSize() const{return m_stacksize;}
			GINL STATE GetState() const{return m_state;}
			GINL GAIA::BL Run();
			GINL GAIA::BL Wait() const;
			virtual GAIA::GVOID WorkProcedure() = 0;
		private:
			GINL GAIA::GVOID init(){m_stacksize = 1024 * 1024; m_state = STATE_INVALID; m_pThread = GNIL;}
		private:
			GAIA::U32 m_stacksize;
			STATE m_state;
			GAIA::GVOID* m_pThread;
		};
	};
};

#include "gaia_thread_indp.h"

#endif
