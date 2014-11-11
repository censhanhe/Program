#include "preheader.h"
#include "t_header.h"
#include "t_render2d.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_render_gdiplus(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render2DGDIPlus>(file, prt, GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS);

		return nRet;
	}
};
