#ifndef		__GAIA_SYNC_BASE_H__
#define		__GAIA_SYNC_BASE_H__

namespace GAIA
{
	namespace SYNC
	{
		GINL GAIA::U32 xsleep(const GAIA::U32& uMilliSecond);
		GINL GAIA::U64 xusleep(const GAIA::U64& uMicroSecond);
	};
};

#include "gaia_sync_base_indp.h"

#endif
