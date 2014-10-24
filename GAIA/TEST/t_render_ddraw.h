#ifndef		__T_RENDER_DDRAW_H__
#define		__T_RENDER_DDRAW_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_ddraw(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render2DDDraw>(file, prt, GAIA::FWORK::CLSID_RENDER_2D_DDRAW);

		return nRet;
	}
};

#endif