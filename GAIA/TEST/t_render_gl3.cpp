#include "preheader.h"
#include "t_header.h"
#include "t_render2d.h"
#include "t_render3d.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_render_gl3(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		nRet += t_render2d<GAIA::RENDER::Render3DGL3>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_GL3);
		nRet += t_render3d<GAIA::RENDER::Render3DGL3>(file, prt, GAIA::FWORK::CLSID_RENDER_3D_GL3);

		return nRet;
	}
};
