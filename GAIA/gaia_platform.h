#ifndef		__GAIA_PLATFORM_H__
#define		__GAIA_PLATFORM_H__

namespace GAIA
{
	class Platform
	{
	public:
		GINL Platform()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_PLATFORM_NETWORK
				WSAData wsadata;
				WSAStartup(MAKEWORD(2, 2), &wsadata);
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS

		#	endif
		#	ifdef GAIA_PLATFORM_COM

		#	endif
		#else
		#endif
		}
		GINL ~Platform()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_PLATFORM_NETWORK
				WSACleanup();
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS

		#	endif
		#	ifdef GAIA_PLATFORM_COM

		#	endif
		#else
		#endif
		}
	};
};

#endif