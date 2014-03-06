#ifndef 	__GAIA_TIME_INDP_H__
#define 	__GAIA_TIME_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <time.h>
#else
#	include <sys/time.h>
#endif

namespace GAIA
{
	namespace TIME
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U64 clock_time()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return (GAIA::U64)clock() * 1000;
		#else
			timeval now;
			gettimeofday(&now, GNULL);
			return (GAIA::U64)now.tv_sec * 1000 * 1000 + (GAIA::U64)now.tv_usec;
		#endif
		}
	}
};

#endif
