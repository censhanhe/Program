#ifndef 	__GAIA_SYNC_BASE_INDP_H__
#define 	__GAIA_SYNC_BASE_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <unistd.h>
#endif


namespace GAIA
{
	namespace SYNC
	{
		GINL GAIA::U32 xsleep(const GAIA::U32& uMilliSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::Sleep((GAIA::U32)uMilliSecond);
			return uMilliSecond;
		#else
			::usleep(GSCAST(useconds_t)(uMilliSecond * 1000));
			return uMilliSecond;
		#endif
		}
		GINL GAIA::U64 xusleep(const GAIA::U64& uMicroSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::Sleep((GAIA::U32)uMicroSecond / 1000);
			return uMicroSecond;
		#else
			::usleep((useconds_t)uMicroSecond);
			return uMicroSecond;
		#endif
		}
	};
};

#endif
