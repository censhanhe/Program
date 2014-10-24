#ifndef		__GAIA_PLATFORM_H__
#define		__GAIA_PLATFORM_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	ifdef GAIA_PLATFORM_NETWORK
#		include <winsock2.h>
#		pragma comment(lib, "ws2_32.lib")
#	endif
#	ifdef GAIA_PLATFORM_GDIPLUS
#		include <winsock2.h>
#		include <ws2tcpip.h>
#		include <windows.h>
#		include <gdiplus.h>
#		pragma comment(lib, "gdiplus.lib")
#	endif
#	ifdef GAIA_PLATFORM_OPENGL
#		pragma comment(lib, "opengl32.lib")
#	endif
#	ifdef GAIA_PLATFORM_COM
#		include <objbase.h>
#		pragma comment(lib, "ole32.lib")
#	endif
#else
#endif

namespace GAIA
{
	class Platform
	{
	public:
		GINL Platform()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	ifdef GAIA_PLATFORM_NETWORK
				::WSAData wsadata;
				if(::WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
					throw 0;
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS
				if(Gdiplus::GdiplusStartup(&m_GDIPlusToken, &m_GDIPlusInput, &m_GDIPlusOutput) != Gdiplus::Ok)
					throw 0;
		#	endif
		#	ifdef GAIA_PLATFORM_COM
				if(CoInitialize(GNIL) != S_OK)
					throw 0;
		#	endif
		#else
		#endif
		}
		GINL ~Platform()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	ifdef GAIA_PLATFORM_NETWORK
				if(::WSACleanup() != 0)
					throw 0;
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS
				Gdiplus::GdiplusShutdown(m_GDIPlusToken);
		#	endif
		#	ifdef GAIA_PLATFORM_COM
				CoUninitialize();
		#	endif
		#else
		#endif
		}
	private:
	#if GAIA_OS == GAIA_OS_WINDOWS
	#	ifdef GAIA_PLATFORM_GDIPLUS
			ULONG_PTR m_GDIPlusToken;
			Gdiplus::GdiplusStartupInput m_GDIPlusInput;
			Gdiplus::GdiplusStartupOutput m_GDIPlusOutput;
	#	endif
	#else
	#endif
	};
};

#endif