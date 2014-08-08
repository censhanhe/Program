#ifndef		__GAIA_UI_CONVAS_MSGDISP_H__
#define		__GAIA_UI_CONVAS_MSGDISP_H__

namespace GAIA
{
	namespace UI
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL UpdateMessage(GAIA::BL bWaitForMessage);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_ui_canvasmsgdisp_indp.h"
#endif

#endif