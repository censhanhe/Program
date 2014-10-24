#ifndef		__T_RENDER_DX9_H__
#define		__T_RENDER_DX9_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_dx9(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render3DDX9>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX9);
		nRet += t_render3d<GAIA::RENDER::Render3DDX9>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX9);

		return nRet;
	}
};

#endif