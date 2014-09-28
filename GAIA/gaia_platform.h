#ifndef		__GAIA_PLATFORM_H__
#define		__GAIA_PLATFORM_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	ifdef GAIA_PLATFORM_NETWORK
#		include <winsock2.h>
#		pragma comment(lib, "ws2_32.lib")
#	endif
#	ifdef GAIA_PLATFORM_GDIPLUS
#		include <comdef.h>
#		include <gdiplus.h>
#		pragma comment(lib, "gdiplus.lib")
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
				::WSAStartup(MAKEWORD(2, 2), &wsadata);
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS
				Gdiplus::Status gdi_startup_result = Gdiplus::GdiplusStartup(&m_GDIPlusToken, &GdiplusStartupInput, &m_GDIPlusOutput);
				GAIA_AST(gdi_startup_result == Gdiplus::Ok);
		#	endif
		#	ifdef GAIA_PLATFORM_COM
				::CoInitializeEx(GNIL, COINIT_MULTITHREADED);
		#	endif
		#else
		#endif
		}
		GINL ~Platform()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	ifdef GAIA_PLATFORM_NETWORK
				::WSACleanup();
		#	endif
		#	ifdef GAIA_PLATFORM_GDIPLUS
				Gdiplus::GdiplusShutdown(&m_GDIPlusToken);
		#	endif
		#	ifdef GAIA_PLATFORM_COM
				::CoUninitialize();
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