#ifndef		__GAIA_TIME_H__
#define		__GAIA_TIME_H__

namespace GAIA
{
	namespace TIME
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U32 clock_time();
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_time_indp.h"
#endif

#endif
