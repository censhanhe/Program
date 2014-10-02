#ifndef		__T_RENDER_GDIPLUS_H__
#define		__T_RENDER_GDIPLUS_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_render_gdiplus(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		/* Create factory. */
		GAIA::FWORK::Factory fac;
		typedef GAIA::RENDER::Render2DGDIPlus __RenderType;
		typedef GAIA::RENDER::Render2D __BaseRenderType;

		/* Create convas instance. */
		GAIA::UI::Canvas* pCanvas = dynamic_cast<GAIA::UI::Canvas*>(fac.CreateInstance(GAIA::FWORK::CLSID_UI_CANVAS, GNIL));
		GAIA_AST(pCanvas != GNIL);
		GAIA::UI::Canvas::CanvasDesc descCanvas;
		descCanvas.reset();
		descCanvas.pszCaptionText = _T("Render test");
		pCanvas->Create(descCanvas);
		pCanvas->Show(GAIA::True);

		/* Create render instance. */
		__RenderType* pRender = dynamic_cast<__RenderType*>(fac.CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS, GNIL));
		GAIA_AST(pRender != GNIL);

		/* Create render. */
		__RenderType::RenderDesc descRender;
		descRender.pCanvas = pCanvas;
		pRender->Create(descRender);

		/* Clear screen. */
		GAIA::MATH::ARGB<GAIA::REAL> crClear;
		crClear.r = crClear.g = crClear.b = 0.5F;
		crClear.a = 1.0F;
		pRender->ClearColor(crClear);
		pRender->Flush();

		/* Set anti-alias state. */
		pRender->SetQuality2DState(
			__RenderType::QUALITY2D_STATE_ANTIALIAS, 
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]);

		/* Create resource. */
		__RenderType::Pen::PenDesc descPen;
		descPen.reset();
		__BaseRenderType::Pen* pPen = pRender->CreatePen(descPen);
		if(pPen == GNIL)
		{
			GTLINE2("Render create pen failed!");
			++nRet;
		}

		__RenderType::Brush::BrushDesc descBrush;
		descBrush.reset();
		__BaseRenderType::Brush* pBrush = pRender->CreateBrush(descBrush);
		if(pBrush == GNIL)
		{
			GTLINE2("Render create brush failed!");
			++nRet;
		}

		/* Draw text. */

		/* Draw line. */

		/* Draw rect. */

		/* Draw texture. */

		/* Release resource. */
		GAIA_RELEASE_SAFE(pPen);
		GAIA_RELEASE_SAFE(pBrush);

		/* Destroy render. */
		pRender->Destroy();

		/* Release render instance. */
		pRender->Release();
		pRender = GNIL;

		/* Release canvas instance. */
		pCanvas->Release();
		pCanvas = GNIL;

		return nRet;
	}
};

#endif