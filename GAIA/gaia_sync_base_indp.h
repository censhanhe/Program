#ifndef 	__GAIA_SYNC_BASE_INDP_H__
#define 	__GAIA_SYNC_BASE_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#else
#	include <unistd.h>
#endif


namespace GAIA
{
	namespace SYNC
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U32 sleep(const GAIA::U32& uMilliSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::Sleep((GAIA::U32)uMilliSecond);
			return uMilliSecond;
		#else
			::sleep((GAIA::U32)uMilliSecond);
			return uMilliSecond;
		#endif
		}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::U64 usleep(const GAIA::U64& uMicroSecond)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::Sleep((GAIA::U32)uMicroSecond / 1000);
			return uMicroSecond;
		#else
			::usleep(uMicroSecond);
			return uMicroSecond;
		#endif
		}
	};
};

#endif
