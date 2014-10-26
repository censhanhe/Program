#ifndef		__T_RENDER2D_H__
#define		__T_RENDER2D_H__

namespace GAIA_TEST
{
	template<typename _RenderType> GAIA::N32 t_render2d(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt, const GAIA::FWORK::ClsID& cid)
	{
		GAIA::N32 nRet = 0;

	#define DEBUG_FLUSH pRender->EndStatePipeline(); pRender->Flush(GAIA::True); pRender->BeginStatePipeline(); pRender->ClearColor(crClear);

		/* Create factory. */
		GAIA::FWORK::Factory fac;
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
		_RenderType* pRender = dynamic_cast<_RenderType*>(fac.CreateInstance(cid, GNIL));
		GAIA_AST(pRender != GNIL);

		/* Create render. */
		_RenderType::RenderDesc descRender;
		descRender.pCanvas = pCanvas;
		pRender->Create(descRender);

		/* Create context. */
		_RenderType::Context::ContextDesc descContext;
		descContext.reset();
		__RootRenderType::Context* pContext = pRender->CreateContext(descContext);
		if(pContext == GNIL)
		{
			GTLINE2("Render create context failed!");
			++nRet;
		}

		/* Create resource. */
		_RenderType::Pen::PenDesc descPen;
		descPen.reset();
		__BaseRenderType::Pen* pPen = pRender->CreatePen(*pContext, descPen);
		if(pPen == GNIL)
		{
			GTLINE2("Render create pen failed!");
			++nRet;
		}

		_RenderType::Brush::BrushDesc descBrush;
		descBrush.reset();
		__BaseRenderType::Brush* pBrush = pRender->CreateBrush(*pContext, descBrush);
		if(pBrush == GNIL)
		{
			GTLINE2("Render create brush failed!");
			++nRet;
		}

		_RenderType::FontFamily::FontFamilyDesc descFontFamily;
		descFontFamily.reset();
		descFontFamily.strFontName = _T("Arial");
		__BaseRenderType::FontFamily* pFontFamily = pRender->CreateFontFamily(*pContext, descFontFamily);
		if(pFontFamily == GNIL)
		{
			GTLINE2("Render create fontfamily failed!");
			++nRet;
		}

		_RenderType::FontPainter::FontPainterDesc descFontPainter;
		descFontPainter.reset();
		descFontPainter.pFontFamily = pFontFamily;
		__BaseRenderType::FontPainter* pFontPainter = pRender->CreateFontPainter(*pContext, descFontPainter);
		if(pFontPainter == GNIL)
		{
			GTLINE2("Render create fontpainter failed!");
			++nRet;
		}

		_RenderType::FontFormat::FontFormatDesc descFontFormat;
		descFontFormat.reset();
		__BaseRenderType::FontFormat* pFontFormat = pRender->CreateFontFormat(*pContext, descFontFormat);
		if(pFontFormat == GNIL)
		{
			GTLINE2("Render create fontformat failed!");
			++nRet;
		}

		_RenderType::Texture::TextureDesc descTexture;
		descTexture.reset();
		descTexture.uWidth = 128;
		descTexture.uHeight = 128;
		__BaseRenderType::Texture* pTexture = pRender->CreateTexture(*pContext, descTexture);
		if(pTexture == GNIL)
		{
			GTLINE2("Render create texture failed!");
			++nRet;
		}

		descTexture.reset();
		descTexture.pszFileName = _T("../TESTRES/car.jpg");
		__BaseRenderType::Texture* pFileTexture = pRender->CreateTexture(*pContext, descTexture);
		if(pFileTexture == GNIL)
		{
			GTLINE2("Render create texture from file failed!");
			++nRet;
		}

		/* Generate texture. */
		_RenderType::Texture::FetchData::FetchDataDesc descFetchData;
		descFetchData.reset();
		descFetchData.pTexture = pTexture;
		descFetchData.sOffsetX = 0;
		descFetchData.sOffsetY = 0;
		descFetchData.sSizeX = pTexture->GetDesc().uWidth;
		descFetchData.sSizeY = pTexture->GetDesc().uHeight;
		GAIA::FAVO::FetchData* pFetchData = pTexture->CreateFetchData(*pContext, descFetchData);
		GAIA::FAVO::FetchData2* pFetchData2 = GDCAST(GAIA::FAVO::FetchData2*)(pFetchData);
		if(pFetchData2 == GNIL)
		{
			GTLINE2("Render create fetch data failed!");
			++nRet;
		}
		else
		{
			if(pFetchData2->GetSize() != 128 * 128 * 4)
			{
				GTLINE2("Render create fetch data failed!");
				++nRet;
			}
			else
			{
				GAIA::MATH::ARGB<GAIA::U8>* pColor = new GAIA::MATH::ARGB<GAIA::U8>[pTexture->GetDesc().uWidth * pTexture->GetDesc().uHeight];
				GAIA::MATH::VEC2<GAIA::REAL> center(pTexture->GetDesc().uWidth / 2, pTexture->GetDesc().uHeight / 2);
				for(GAIA::SIZE x = 0; x < (GAIA::SIZE)pTexture->GetDesc().uWidth; ++x)
				{
					for(GAIA::SIZE y = 0; y < (GAIA::SIZE)pTexture->GetDesc().uHeight; ++y)
					{
						GAIA::MATH::VEC2<GAIA::REAL> t(x, y);
						GAIA::MATH::ARGB<GAIA::U8>& cr = pColor[y * pTexture->GetDesc().uWidth + x];
						GAIA::REAL rLen = (t - center).length() / (GAIA::REAL)(pTexture->GetDesc().uWidth / 2);
						rLen = 1.0F - GAIA::MATH::xclamp(rLen, 0, 1);
						cr = rLen * 255;
						cr.a = 255;
					}
				}
				pFetchData2->Set(pColor, pTexture->GetDesc().uWidth * pTexture->GetDesc().uHeight * 4, 4 * 8, 0);
				GAIA_DELETE_SAFE(pColor);
				pFetchData->Release();
				pFetchData = GNIL;
				pFetchData2 = GNIL;
			}
		}

		/* Begin state pipeline. */
		pRender->BeginStatePipeline();

		/* Clear screen. */
		GAIA::MATH::ARGB<GAIA::REAL> crClear;
		crClear.r = crClear.g = crClear.b = 0.5F;
		crClear.a = 1.0F;
		DEBUG_FLUSH;

		/* Set anti-alias state. */
		pRender->SetQuality2DState(*pContext, 
			GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS, 
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]);
		pRender->SetQuality2DState(*pContext, 
			GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS,
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]);

		/* Set render2d state. */
		pRender->SetRender2DState(*pContext, 
			GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND, 
			GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]);

		/* Draw text. */
		GAIA::MATH::ARGB<GAIA::REAL> cr;
		cr.r = cr.g = 0.0F;
		cr.b = 0.0F;
		cr.a = 0.4F;
		pBrush->SetColor(cr);
		GAIA::MATH::AABR<GAIA::REAL> aabr;
		aabr.pmin = 100.0F;
		aabr.pmax = 400.0F;
		pRender->SetBrush(*pContext, pBrush);
		pRender->SetFontPainter(*pContext, pFontPainter);
		pRender->SetFontFormat(*pContext, pFontFormat);
		pRender->DrawFontPainter(*pContext, _T("Hello World!"), aabr);
		DEBUG_FLUSH;

		/* Draw line. */
		pPen->SetWidth(4.0F);
		cr.r = 1.0F;
		cr.g = 0.5F;
		cr.b = 0.2F;
		cr.a = 0.5F;
		pPen->SetColor(cr);
		pRender->SetPen(*pContext, pPen);
		GAIA::MATH::VEC2<GAIA::REAL> s, e;
		s = 100.0F;
		e = 200.0F;
		e.x += 100.0F;
		pRender->DrawLine(*pContext, s, e);
		DEBUG_FLUSH;

		/* Draw rect. */
		aabr.pmin = 200.0F;
		aabr.pmax = 300.0F;
		aabr.pmin.x += 200.0F;
		aabr.pmax.x += 400.0F;
		pRender->DrawRect(*pContext, aabr);
		DEBUG_FLUSH;

		/* Draw triangle. */
		GAIA::MATH::VEC2<GAIA::REAL> tri[3];
		tri[0].x = 240.0F;
		tri[0].y = 120.0F;
		tri[1].x = 240.0F - 64.0F;
		tri[2].x = 240.0F + 64.0F;
		tri[1].y = 120.0F + 64.0F;
		tri[2].y = 120.0F + 64.0F;
		pRender->DrawTriangle(*pContext, tri[0], tri[1], tri[2]);
		DEBUG_FLUSH;

		/* Draw texture. */
		aabr.pmin.x = 10.0F;
		aabr.pmin.y = 10.0F;
		aabr.pmax = aabr.pmin;
		aabr.pmax += 128.0F;
		GAIA::MATH::MTX33<GAIA::REAL> mtx;
		pRender->SetTexture(*pContext, 0, pTexture);
		pRender->DrawTexture(*pContext, aabr, mtx);
		DEBUG_FLUSH;

		/* Draw texture file. */
		aabr.pmin += 200.0F;
		aabr.pmax = aabr.pmin + GAIA::MATH::VEC2<GAIA::REAL>(pFileTexture->GetDesc().uWidth, pFileTexture->GetDesc().uHeight);
		pRender->SetTexture(*pContext, 0, pFileTexture);
		pRender->DrawTexture(*pContext, aabr, mtx);
		DEBUG_FLUSH;

		/* Flush. */
		pRender->EndStatePipeline();
		pRender->Flush(GAIA::True);

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