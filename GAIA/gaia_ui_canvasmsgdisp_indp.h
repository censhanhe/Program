#ifndef		__GAIA_UI_CANVASMSGDISP_INDP_H__
#define		__GAIA_UI_CANVASMSGDISP_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <windows.h>
#else
#endif

namespace GAIA
{
	namespace UI
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL UpdateMessage(GAIA::BL bWaitForMessage)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			MSG msg;
			if(bWaitForMessage)
			{
				if(::GetMessage(&msg, GNULL, 0, 0))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					return GAIA::True;
				}
			}
			else
			{
				if(::PeekMessage(&msg, GNULL, 0, 0, PM_REMOVE))
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