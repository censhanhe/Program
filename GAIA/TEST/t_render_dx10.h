#ifndef		__T_RENDER_DX10_H__
#define		__T_RENDER_DX10_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_dx10(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render3DDX10>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX10);
		nRet += t_render3d<GAIA::RENDER::Render3DDX10>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX10);

		return nRet;
	}
};

#endif