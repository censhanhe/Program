#ifndef		__GAIA_PROCESS_INDP_H__
#define		__GAIA_PROCESS_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <unistd.h>
#endif

namespace GAIA
{
	namespace PROCESS
	{
		GINL GAIA::UM processid()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return (GAIA::UM)::GetCurrentProcessId();
		#else
			return (GAIA::UM)getpid();
		#endif
		}
	};
};

#endif
