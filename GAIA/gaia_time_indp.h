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
		GINL GAIA::U64 clock_time()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			__time64_t time;
			_time64(&time);
			return (GAIA::U64)time * 1000 * 1000;
		#else
			timeval now;
			gettimeofday(&now, GNIL);
			return (GAIA::U64)now.tv_sec * 1000 * 1000 + (GAIA::U64)now.tv_usec;
		#endif
		}
		GINL GAIA::U64 tick_time()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return (GAIA::U64)clock() * 1000;
		#else
			timeval now;
			gettimeofday(&now, GNIL);
			return (GAIA::U64)now.tv_sec * 1000 * 1000 + (GAIA::U64)now.tv_usec;
		#endif
		}
		GINL GAIA::GVOID Time::systime()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			SYSTEMTIME st;
			::GetLocalTime(&st);
			y = (GAIA::U16)st.wYear;
			mo = (GAIA::U8)st.wMonth;
			d = (GAIA::U8)st.wDay;
			h = (GAIA::U8)st.wHour;
			mi = (GAIA::U8)st.wMinute;
			sec = (GAIA::U8)st.wSecond;
			msec = (GAIA::U16)st.wMilliseconds;
			usec = (GAIA::U16)0;
		#else
			time_t t;
			time(&t);
			struct tm* pTM = localtime(&t);
			y = GSCAST(GAIA::U16)(pTM->tm_year + 1900);
			mo = GSCAST(GAIA::U8)(pTM->tm_mon + 1);
			d = GSCAST(GAIA::U8)(pTM->tm_mday);
			h = GSCAST(GAIA::U8)(pTM->tm_hour);
			mi = GSCAST(GAIA::U8)(pTM->tm_min);
			sec = GSCAST(GAIA::U8)(pTM->tm_sec);
			timeval tv;
			gettimeofday(&tv, GNIL);
			msec = GSCAST(GAIA::U16)(tv.tv_usec / 1000);
			usec = GSCAST(GAIA::U16)(tv.tv_usec % 1000);
		#endif
		}
	}
};

#endif
