#ifndef		__GAIA_SYNC_LOCK_H__
#define		__GAIA_SYNC_LOCK_H__

namespace GAIA
{
	namespace SYNC
	{
		class Lock : public GAIA::Entity
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
		#	if GAIA_MACHINE == GAIA_MACHINE32
				GAIA::N8 m_head[24];
		#	else
				GAIA::N8 m_head[48];
		#	endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			GAIA::N8 m_head[64];
		#else
			GAIA::N8 m_head[64];
		#endif
		};
	};
};

#include "gaia_sync_lock_indp.h"

#endif
