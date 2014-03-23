#ifndef		__GAIA_TIME_H__
#define		__GAIA_TIME_H__

namespace GAIA
{
	namespace TIME
	{
		class Time : public GAIA::Base
		{
		public:
			GAIA::N16 y; // Year.
			GAIA::N8 mo; // Month.
			GAIA::N8 d; // Day.
			GAIA::N8 h; // Hour.
			GAIA::N8 mi; // Minute.
			GAIA::N8 sec; // Second.
			GAIA::N16 msec; // MilliSecond.
			GAIA::N16 usec; // MicroSecond.
		};
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U64 clock_time(); // return value is micro second.
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_time_indp.h"
#endif

#endif
