#ifndef		__GAIA_SYNC_EVENT_H__
#define		__GAIA_SYNC_EVENT_H__

namespace GAIA
{
	namespace SYNC
	{
		class Event : public GAIA::Entity
		{
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Event();
			GAIA_DEBUG_CODEPURE_MEMFUNC ~Event();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Fire();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Wait(GAIA::U32 uMilliSecond);
		private:
			GINL Event(const Event& src){}
		private:
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_MACHINE == GAIA_MACHINE32
				GAIA::N8 m_head[4];
		#	else
				GAIA::N8 m_head[8];
		#	endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			GAIA::N8 m_head[48];
			GAIA::N8 m_headmutex[64];
			GAIA::NM m_waitcnt;
		#else
			GAIA::N8 m_head[64];
			GAIA::N8 m_headmutex[64];
			GAIA::NM m_waitcnt;
		#endif
		};
	};
};

#include "gaia_sync_event_indp.h"

#endif
