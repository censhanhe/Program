#ifndef		__T_RENDER_GDIPLUS_H__
#define		__T_RENDER_GDIPLUS_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_render_gdiplus(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		/* Create factory. */
		GAIA::FWORK::Factory fac;
		typedef GAIA::RENDER::Render2DGDIPlus __RenderType;

		/* Create convas. */
		GAIA::UI::Canvas* pCanvas = dynamic_cast<GAIA::UI::Canvas*>(fac.CreateInstance(GAIA::FWORK::CLSID_CANVAS, GNIL));
		GAIA_AST(pCanvas != GNIL);

		/* Create render. */
		__RenderType* p = dynamic_cast<__RenderType*>(fac.CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS, GNIL));
		GAIA_AST(p != GNIL);

		/* Initialize render. */

		/* Release render. */

		/* Delete render. */
		p->Release();
		p = GNIL;

		/* Delete canvas. */
		pCanvas->Release();
		pCanvas = GNIL;

		return nRet;
	}
};

#endif