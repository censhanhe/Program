#ifndef		__GAIA_SYNC_EVENT_H__
#define		__GAIA_SYNC_EVENT_H__

namespace GAIA
{
	namespace SYNC
	{
		class Event : public GAIA::Base
		{
		public:
			GINL Event();
			GINL ~Event();
			GINL GAIA::GVOID Fire();
			GINL GAIA::BL Wait(GAIA::U32 uMilliSecond);
		private:
			GINL Event(const Event& src){}
		private:
		#if GAIA_OS == GAIA_OS_WINDOWS
			HANDLE m_hEvent;
		#else
			pthread_mutex_t m_mutex;
			pthread_cond_t m_cond;
			GAIA::NM m_waitcnt;
		#endif
		};
	};
};

#include "gaia_sync_event_indp.h"

#endif
