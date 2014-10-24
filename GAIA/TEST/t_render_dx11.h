#ifndef		__T_RENDER_DX11_H__
#define		__T_RENDER_DX11_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_dx11(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render3DDX11>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX11);
		nRet += t_render3d<GAIA::RENDER::Render3DDX11>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_DX11);

		return nRet;
	}
};

#endif