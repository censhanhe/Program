#ifndef		__GAIA_SYNC_BASE_H__
#define		__GAIA_SYNC_BASE_H__

namespace GAIA
{
	namespace SYNC
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U32 sleep(const GAIA::U32& uMilliSecond);
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U64 usleep(const GAIA::U64& uMicroSecond);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_sync_base_indp.h"
#endif

#endif