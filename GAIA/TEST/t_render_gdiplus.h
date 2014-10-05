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
		typedef GAIA::RENDER::Render __RootRenderType;

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

		/* Create context. */
		__RenderType::Context::ContextDesc descContext;
		descContext.reset();
		__RootRenderType::Context* pContext = pRender->CreateContext(descContext);
		if(pContext == GNIL)
		{
			GTLINE2("Render create context failed!");
			++nRet;
		}

		/* Set anti-alias state. */
		pRender->SetQuality2DState(pContext, 
			GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS, 
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]);
		pRender->SetQuality2DState(pContext, 
			GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS,
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]);

		/* Create resource. */
		__RenderType::Pen::PenDesc descPen;
		descPen.reset();
		__BaseRenderType::Pen* pPen = pRender->CreatePen(pContext, descPen);
		if(pPen == GNIL)
		{
			GTLINE2("Render create pen failed!");
			++nRet;
		}

		__RenderType::Brush::BrushDesc descBrush;
		descBrush.reset();
		__BaseRenderType::Brush* pBrush = pRender->CreateBrush(pContext, descBrush);
		if(pBrush == GNIL)
		{
			GTLINE2("Render create brush failed!");
			++nRet;
		}

		__RenderType::FontFamily::FontFamilyDesc descFontFamily;
		descFontFamily.reset();
		descFontFamily.strFontName = _T("Arial");
		__BaseRenderType::FontFamily* pFontFamily = pRender->CreateFontFamily(pContext, descFontFamily);
		if(pFontFamily == GNIL)
		{
			GTLINE2("Render create fontfamily failed!");
			++nRet;
		}

		__RenderType::FontPainter::FontPainterDesc descFontPainter;
		descFontPainter.reset();
		descFontPainter.pFontFamily = pFontFamily;
		__BaseRenderType::FontPainter* pFontPainter = pRender->CreateFontPainter(pContext, descFontPainter);
		if(pFontPainter == GNIL)
		{
			GTLINE2("Render create fontpainter failed!");
			++nRet;
		}

		__RenderType::FontFormat::FontFormatDesc descFontFormat;
		descFontFormat.reset();
		__BaseRenderType::FontFormat* pFontFormat = pRender->CreateFontFormat(pContext, descFontFormat);
		if(pFontFormat == GNIL)
		{
			GTLINE2("Render create fontformat failed!");
			++nRet;
		}

		__RenderType::Texture::TextureDesc descTexture;
		descTexture.reset();
		descTexture.uWidth = 128;
		descTexture.uHeight = 128;
		__BaseRenderType::Texture* pTexture = pRender->CreateTexture(pContext, descTexture);
		if(pTexture == GNIL)
		{
			GTLINE2("Render create texture failed!");
			++nRet;
		}

		descTexture.reset();
		descTexture.pszFileName = _T("../TESTRES/car.jpg");
		__BaseRenderType::Texture* pFileTexture = pRender->CreateTexture(pContext, descTexture);
		if(pFileTexture == GNIL)
		{
			GTLINE2("Render create texture from file failed!");
			++nRet;
		}

		/* Set render2d state. */
		pRender->SetRender2DState(pContext, 
			GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND, 
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]);

		/* Draw text. */
		GAIA::MATH::ARGB<GAIA::REAL> cr;
		cr.r = cr.g = 0.0F;
		cr.b = 1.0F;
		cr.a = 0.4F;
		pBrush->SetColor(cr);
		GAIA::MATH::AABR<GAIA::REAL> aabr;
		aabr.pmin = 100.0F;
		aabr.pmax = 400.0F;
		pRender->DrawFontPainter(pContext, _T("Hello World!"), aabr, pFontPainter, pBrush, pFontFormat);
		pRender->Flush();

		/* Draw line. */
		pPen->SetWidth(4.0F);
		cr.r = 1.0F;
		cr.g = 0.5F;
		cr.b = 0.2F;
		cr.a = 0.5F;
		pPen->SetColor(cr);
		GAIA::MATH::VEC2<GAIA::REAL> s, e;
		s = 100.0F;
		e = 200.0F;
		e.x += 100.0F;
		pRender->DrawLine(pContext, s, e, pPen);
		pRender->Flush();

		/* Draw rect. */
		aabr.pmin = 200.0F;
		aabr.pmax = 300.0F;
		aabr.pmin.x += 200.0F;
		aabr.pmax.x += 400.0F;
		pRender->DrawRect(pContext, aabr, pBrush);
		pRender->Flush();

		/* Draw triangle. */
		GAIA::MATH::VEC2<GAIA::REAL> tri[3];
		tri[0].x = 240.0F;
		tri[0].y = 120.0F;
		tri[1].x = 240.0F - 64.0F;
		tri[2].x = 240.0F + 64.0F;
		tri[1].y = 120.0F + 64.0F;
		tri[2].y = 120.0F + 64.0F;
		pRender->DrawTriangle(pContext, tri[0], tri[1], tri[2], pBrush);
		pRender->Flush();

		/* Draw texture. */
		pRender->Flush();

		/* Draw texture file. */
		pRender->Flush();

		/* Release resource. */
		GAIA_RELEASE_SAFE(pPen);
		GAIA_RELEASE_SAFE(pBrush);
		GAIA_RELEASE_SAFE(pFontPainter);
		GAIA_RELEASE_SAFE(pFontFamily);
		GAIA_RELEASE_SAFE(pFontFormat);
		GAIA_RELEASE_SAFE(pTexture);
		GAIA_RELEASE_SAFE(pFileTexture);

		/* Release context. */
		pContext->Release();
		pContext = GNIL;

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