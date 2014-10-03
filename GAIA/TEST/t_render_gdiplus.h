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

		__RenderType::FontFamily::FontFamilyDesc descFontFamily;
		descFontFamily.reset();
		descFontFamily.strFontName = _T("Times New Roman");
		__BaseRenderType::FontFamily* pFontFamily = pRender->CreateFontFamily(descFontFamily);
		if(pFontFamily == GNIL)
		{
			GTLINE2("Render create fontfamily failed!");
			++nRet;
		}

		__RenderType::FontPainter::FontPainterDesc descFontPainter;
		descFontPainter.reset();
		descFontPainter.pFontFamily = pFontFamily;
		descFontPainter.rSize = 32.0F;
		__BaseRenderType::FontPainter* pFontPainter = pRender->CreateFontPainter(descFontPainter);
		if(pFontPainter == GNIL)
		{
			GTLINE2("Render create fontpainer failed!");
			++nRet;
		}

		/* Draw text. */
		GAIA::MATH::AABR<GAIA::REAL> aabr;
		aabr.pmin = 100.0F;
		aabr.pmax = 400.0F;
		pRender->DrawFontPainter(_T("Hello World"), aabr, pFontPainter, pBrush, GNIL);
		pRender->Flush();

		/* Draw line. */
		GAIA::MATH::VEC2<GAIA::REAL> s, e;
		s = 100.0F;
		e = 200.0F;
		e.x += 100.0F;
		pRender->DrawLine(s, e, pPen);
		pRender->Flush();

		/* Draw rect. */
		aabr.pmin = 200.0F;
		aabr.pmax = 300.0F;
		aabr.pmin.x += 200.0F;
		aabr.pmax.x += 400.0F;
		pRender->DrawRect(aabr, pBrush);
		pRender->Flush();

		/* Draw texture. */
		pRender->Flush();

		/* Release resource. */
		GAIA_RELEASE_SAFE(pPen);
		GAIA_RELEASE_SAFE(pBrush);
		GAIA_RELEASE_SAFE(pFontPainter);
		GAIA_RELEASE_SAFE(pFontFamily);

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