#ifndef		__T_RENDER_GL2_H__
#define		__T_RENDER_GL2_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_gl2(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render3DGL2>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_GL2);
		nRet += t_render3d<GAIA::RENDER::Render3DGL2>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_GL2);

		return nRet;
	}
};

#endif