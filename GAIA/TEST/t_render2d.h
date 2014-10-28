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

			/* End state pipeline. */
			pRender->EndStatePipeline();

			/* Flush. */
			pRender->Flush(GAIA::True);

			++nFrameCount;
		}



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