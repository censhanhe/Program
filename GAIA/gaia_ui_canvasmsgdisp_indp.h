#ifndef		__GAIA_UI_CANVASMSGDISP_INDP_H__
#define		__GAIA_UI_CANVASMSGDISP_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#endif

namespace GAIA
{
	namespace UI
	{
		GINL GAIA::BL UpdateMessage(GAIA::BL bWaitForMessage)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			MSG msg;
			if(bWaitForMessage)
			{
				if(::GetMessage(&msg, GNIL, 0, 0))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					return GAIA::True;
				}
			}
			else
			{
				if(::PeekMessage(&msg, GNIL, 0, 0, PM_REMOVE))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					return GAIA::True;
				}
			}
			return GAIA::False;
		#else
			return GAIA::False;
		#endif
		}
	};
};

#endif