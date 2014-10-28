		/* Clear screen. */
		GAIA::MATH::ARGB<GAIA::REAL> crClear;
		crClear.r = crClear.g = crClear.b = R(0.5);
		crClear.a = 1;
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
		cr.r = cr.g = 0;
		cr.b = 0;
		cr.a = R(0.4);
		pBrush->SetColor(cr);
		GAIA::MATH::AABR<GAIA::REAL> aabr;
		aabr.pmin = R(100.0);
		aabr.pmax = R(400.0);
		pRender->SetBrush(*pContext, pBrush);
		pRender->SetFontPainter(*pContext, pFontPainter);
		pRender->SetFontFormat(*pContext, pFontFormat);
		pRender->DrawFontPainter(*pContext, _T("Hello World!"), aabr);
		DEBUG_FLUSH;

		/* Draw line. */
		pPen->SetWidth(4);
		cr.r = R(1.0);
		cr.g = R(0.5);
		cr.b = R(0.2);
		cr.a = R(0.5);
		pPen->SetColor(cr);
		pRender->SetPen(*pContext, pPen);
		GAIA::MATH::VEC2<GAIA::REAL> s, e;
		s = R(100.0);
		e = R(200.0);
		e.x += R(100.0);
		pRender->DrawLine(*pContext, s, e);
		DEBUG_FLUSH;

		/* Draw rect. */
		aabr.pmin = R(200.0);
		aabr.pmax = R(300.0);
		aabr.pmin.x += R(200.0);
		aabr.pmax.x += R(400.0);
		pRender->DrawRect(*pContext, aabr);
		DEBUG_FLUSH;

		/* Draw triangle. */
		GAIA::MATH::VEC2<GAIA::REAL> tri[3];
		tri[0].x = R(240.0);
		tri[0].y = R(120.0);
		tri[1].x = R(240.0) - R(64.0);
		tri[2].x = R(240.0) + R(64.0);
		tri[1].y = R(120.0) + R(64.0);
		tri[2].y = R(120.0) + R(64.0);
		pRender->DrawTriangle(*pContext, tri[0], tri[1], tri[2]);
		DEBUG_FLUSH;

		/* Draw texture. */
		aabr.pmin.x = R(10.0);
		aabr.pmin.y = R(10.0);
		aabr.pmax = aabr.pmin;
		aabr.pmax += R(128.0);
		GAIA::MATH::MTX33<GAIA::REAL> mtx;
		pRender->SetTexture(*pContext, 0, pTexture);
		pRender->DrawTexture(*pContext, aabr, mtx);
		DEBUG_FLUSH;

		/* Draw texture file. */
		aabr.pmin += R(200.0);
		aabr.pmax = aabr.pmin + GAIA::MATH::VEC2<GAIA::REAL>(pFileTexture->GetDesc().uWidth, pFileTexture->GetDesc().uHeight);
		pRender->SetTexture(*pContext, 0, pFileTexture);
		pRender->DrawTexture(*pContext, aabr, mtx);
		DEBUG_FLUSH;

		/* Release resource. */
