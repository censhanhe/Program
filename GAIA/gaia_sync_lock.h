#ifndef		__GAIA_SYNC_LOCK_H__
#define		__GAIA_SYNC_LOCK_H__

namespace GAIA
{
	namespace SYNC
	{
		class Lock : public GAIA::Base
		{
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Lock();
			GAIA_DEBUG_CODEPURE_MEMFUNC ~Lock();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Enter();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Leave();
		private:
			GINL Lock(const Lock& src){}
		private:
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_MACHINE == GAIA_MACHINE32
				GAIA::GCH m_head[24];
		#	else
				GAIA::GCH m_head[48];
		#	endif
		#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
			GAIA::GCH m_head[64];
		#else
			GAIA::GCH m_head[64];
		#endif
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_sync_lock_indp.h"
#endif

#endif
