#ifndef		__GAIA_SYNC_EVENT_H__
#define		__GAIA_SYNC_EVENT_H__

namespace GAIA
{
	namespace SYNC
	{
		class Event : public GAIA::Base
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
				GAIA::GCH m_head[4];
		#	else
				GAIA::GCH m_head[8];
		#	endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			GAIA::GCH m_head[48];
			GAIA::GCH m_headmutex[64];
			GAIA::NM m_waitcnt;
		#else
			GAIA::GCH m_head[64];
			GAIA::GCH m_headmutex[64];
			GAIA::NM m_waitcnt;
		#endif
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_sync_event_indp.h"
#endif

#endif
