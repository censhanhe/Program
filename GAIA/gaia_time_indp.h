#ifndef 	__GAIA_TIME_INDP_H__
#define 	__GAIA_TIME_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <time.h>
#else
#	include <time.h>
#endif

namespace GAIA
{
	namespace TIME
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U32 clock_time(){return (GAIA::U32)clock();}
	}
};

#endif
