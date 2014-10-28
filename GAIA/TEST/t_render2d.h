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
		GAIA::RENDER::Render2D* pRender = dynamic_cast<GAIA::RENDER::Render2D*>(fac.CreateInstance(cid, GNIL));
		GAIA_AST(pRender != GNIL);

		/* Create render. */
		typename _RenderType::RenderDesc descRender;
		descRender.pCanvas = pCanvas;
		pRender->Create(descRender);

		/* Create context. */
		typename _RenderType::Context::ContextDesc descContext;
		descContext.reset();
		__RootRenderType::Context* pContext = pRender->CreateContext(descContext);
		if(pContext == GNIL)
		{
			GTLINE2("Render create context failed!");
			++nRet;
		}

		/* Create resource. */
		typename _RenderType::Pen::PenDesc descPen;
		descPen.reset();
		__BaseRenderType::Pen* pGridPen = pRender->CreatePen(*pContext, descPen);
		if(pGridPen == GNIL)
		{
			GTLINE2("Render create pen failed!");
			++nRet;
		}

		descPen.reset();
		__BaseRenderType::Pen* pLinePen = pRender->CreatePen(*pContext, descPen);
		if(pLinePen == GNIL)
		{
			GTLINE2("Render create pen failed!");
			++nRet;
		}

		typename _RenderType::Brush::BrushDesc descBrush;
		descBrush.reset();
		__BaseRenderType::Brush* pBrush = pRender->CreateBrush(*pContext, descBrush);
		if(pBrush == GNIL)
		{
			GTLINE2("Render create brush failed!");
			++nRet;
		}

		typename _RenderType::FontFamily::FontFamilyDesc descFontFamily;
		descFontFamily.reset();
		descFontFamily.strFontName = _T("Arial");
		__BaseRenderType::FontFamily* pFontFamily = pRender->CreateFontFamily(*pContext, descFontFamily);
		if(pFontFamily == GNIL)
		{
			GTLINE2("Render create fontfamily failed!");
			++nRet;
		}

		typename _RenderType::FontPainter::FontPainterDesc descFontPainter;
		descFontPainter.reset();
		descFontPainter.pFontFamily = pFontFamily;
		descFontPainter.rSize = 12;
		__BaseRenderType::FontPainter* pFontPainter = pRender->CreateFontPainter(*pContext, descFontPainter);
		if(pFontPainter == GNIL)
		{
			GTLINE2("Render create fontpainter failed!");
			++nRet;
		}

		typename _RenderType::FontFormat::FontFormatDesc descFontFormat;
		descFontFormat.reset();
		__BaseRenderType::FontFormat* pFontFormat = pRender->CreateFontFormat(*pContext, descFontFormat);
		if(pFontFormat == GNIL)
		{
			GTLINE2("Render create fontformat failed!");
			++nRet;
		}

		/* Test context. */
		GAIA::MATH::VEC2<GAIA::REAL> l1, l2, ld1, ld2;
		l1 = 0.0F;
		l2 = 0.0F;
		ld1 = 0.0F;
		ld2 = 0.0F;

		/**/
		GAIA::N64 nFrameCount = 0;
		for(;;)
		{
			GAIA::BL bExistMsg;
			if(!GAIA::UI::UpdateMessage(GAIA::False, bExistMsg))
				break;

			/* Begin state pipeline. */
			pRender->BeginStatePipeline();

			/* Clear screen. */
			GAIA::MATH::ARGB<GAIA::REAL> crClear;
			crClear.r = crClear.g = crClear.b = R(0.5);
			crClear.a = 1;
			pRender->ClearColor(crClear);

			/* Helper. */
			static const GAIA::SIZE BLOCKCNTX = 4;
			static const GAIA::SIZE BLOCKCNTY = 4;
			const GAIA::UI::Canvas::__SizeType& sizeCanvas = pCanvas->Size();

			// Draw grid.
			{
				pRender->SetPen(*pContext, pGridPen);
				GAIA::MATH::VEC2<GAIA::REAL> p1, p2;
				for(GAIA::SIZE x = 0; x < BLOCKCNTX; ++x)
				{
					p1.y = 0;
					p2.y = sizeCanvas.y;
					p1.x = p2.x = (GAIA::REAL)x / (GAIA::REAL)BLOCKCNTX * sizeCanvas.x;
					pRender->DrawLine(*pContext, p1, p2);
				}
				for(GAIA::SIZE y = 0; y < BLOCKCNTY; ++y)
				{
					p1.x = 0;
					p2.x = sizeCanvas.x;
					p1.y = p2.y = (GAIA::REAL)y / (GAIA::REAL)BLOCKCNTY * sizeCanvas.y;
					pRender->DrawLine(*pContext, p1, p2);
				}
			}

			// Draw frame.
			{
				GAIA::MATH::AABR<GAIA::REAL> aabr;
				aabr.pmin.x = sizeCanvas.x - 128;
				aabr.pmin.y = 0;
				aabr.pmax = aabr.pmin;
				aabr.pmax += R(128.0);
				pRender->SetBrush(*pContext, pBrush);
				pRender->SetFontFamily(*pContext, pFontFamily);
				pRender->SetFontPainter(*pContext, pFontPainter);
				pRender->SetFontFormat(*pContext, pFontFormat);
				GAIA::CTN::TChars strTemp = _T("Frame = ");
				strTemp += nFrameCount;
				pRender->DrawFontPainter(*pContext, strTemp, aabr);
			}

			// Line test.
			{
				GAIA::SIZE BLOCKINDEX = 0;
				GAIA::SIZE BLOCKSIZEX = sizeCanvas.x / BLOCKCNTX;
				GAIA::SIZE BLOCKSIZEY = sizeCanvas.y / BLOCKCNTY;
				GAIA::SIZE BLOCKINDEXX = BLOCKINDEX % BLOCKCNTX;
				GAIA::SIZE BLOCKINDEXY = BLOCKINDEX / BLOCKCNTX;
				GAIA::REAL rBlockWeightX = (GAIA::REAL)BLOCKINDEXX / (GAIA::REAL)BLOCKCNTX;
				GAIA::REAL rBlockWeightY = (GAIA::REAL)BLOCKINDEXY / (GAIA::REAL)BLOCKCNTY;
				GAIA::MATH::AABR<GAIA::REAL> aabr;
				aabr.pmin.x = rBlockWeightX * sizeCanvas.x;
				aabr.pmin.y = rBlockWeightY * sizeCanvas.y;
				aabr.pmax = aabr.pmin;
				aabr.pmax.x += BLOCKSIZEX;
				aabr.pmax.y += BLOCKSIZEY;

				GAIA::MATH::VEC2<GAIA::REAL> center = aabr.center();
				GAIA::REAL rLen = GAIA::MATH::xsqrt((GAIA::REAL)(BLOCKSIZEX * BLOCKSIZEX + BLOCKSIZEY * BLOCKSIZEY));

				if(l1 == 0)
					l1 = center;
				if(l2 == 0)
					l2 = center;
				if(ld1 == 0)
				{
					ld1.x = GAIA::MATH::xsin((GAIA::REAL)GAIA::MATH::xrandom() / (GAIA::REAL)GAIA::MATH::xrandom_max() * GAIA::MATH::PI);
					ld1.y = GAIA::MATH::xcos((GAIA::REAL)GAIA::MATH::xrandom() / (GAIA::REAL)GAIA::MATH::xrandom_max() * GAIA::MATH::PI);
					ld1.normalize();
				}
				if(ld2 == 0)
				{
					ld2.x = GAIA::MATH::xsin((GAIA::REAL)GAIA::MATH::xrandom() / (GAIA::REAL)GAIA::MATH::xrandom_max() * GAIA::MATH::PI);
					ld2.y = GAIA::MATH::xcos((GAIA::REAL)GAIA::MATH::xrandom() / (GAIA::REAL)GAIA::MATH::xrandom_max() * GAIA::MATH::PI);
					ld2.normalize();
				}
				if(aabr.clamp(l1))
				{
					if(l1.x == aabr.pmin.x || l1.x == aabr.pmax.x)
						ld1.x = -ld1.x;
					if(l1.y == aabr.pmin.y || l1.y == aabr.pmax.y)
						ld1.y = -ld1.y;
				}
				if(aabr.clamp(l2))
				{
					if(l2.x == aabr.pmin.x || l2.x == aabr.pmax.x)
						ld2.x = -ld2.x;
					if(l2.y == aabr.pmin.y || l2.y == aabr.pmax.y)
						ld2.y = -ld2.y;
				}
				l1 += ld1;
				l2 += ld2;
				pRender->SetPen(*pContext, pLinePen);
				pLinePen->SetWidth(R(4.0));
				GAIA::MATH::ARGB<GAIA::REAL> argb;
				argb.r = R(1.0);
				argb.g = argb.b = R(0.0);
				argb.a = R(0.5);
				pLinePen->SetColor(argb);
				pRender->DrawLine(*pContext, l1, l2);
			}

			/* End state pipeline. */
			pRender->EndStatePipeline();

			/* Flush. */
			pRender->Flush(GAIA::True);

			++nFrameCount;
		}

		/* Release resource. */
		GAIA_RELEASE_SAFE(pGridPen);
		GAIA_RELEASE_SAFE(pLinePen);
		GAIA_RELEASE_SAFE(pBrush);
		GAIA_RELEASE_SAFE(pFontPainter);
		GAIA_RELEASE_SAFE(pFontFamily);
		GAIA_RELEASE_SAFE(pFontFormat);

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