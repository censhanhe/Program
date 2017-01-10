#ifndef		__GAIA_SYNC_LOCK_H__
#define		__GAIA_SYNC_LOCK_H__

namespace GAIA
{
	namespace SYNC
	{
		class Lock : public GAIA::Base
		{
		public:
			GINL Lock();
			GINL ~Lock();
			GINL GAIA::GVOID Enter();
			GINL GAIA::GVOID Leave();
		private:
			GINL Lock(const Lock& src){}
		private:
		#if GAIA_OS == GAIA_OS_WINDOWS
			CRITICAL_SECTION m_cs;
		#else
			pthread_mutex_t m_mutex;
		#endif
		};
	};
};

#include "gaia_sync_lock_indp.h"

#endif
