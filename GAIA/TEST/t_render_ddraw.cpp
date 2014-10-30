#include "preheader.h"
#include "t_header.h"
#include "t_render2d.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_render_ddraw(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render2DDDraw>(file, prt, GAIA::FWORK::CLSID_RENDER_2D_DDRAW);

		return nRet;
	}
};
