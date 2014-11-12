#include "../venus.h"
#include "gaia_global_impl.h"

static GAIA::BL FrameLoop(VENUS::Render::Context& ctx, VENUS::Render* pRender)
{
	// Clear.
	GAIA::MATH::ARGB<GAIA::REAL> crClear;
	crClear.fromu32(0xFF8080FF);
	crClear.torealmode();
	pRender->ClearTarget(ctx, 0, crClear);

	// Flush.
	pRender->Flush(ctx, GAIA::True);

	return GAIA::True;
}

int main()
{
	GAIA::FWORK::Factory fac;

	// New canvas instance.
	GAIA::UI::Canvas* pCanvas = GDCAST(GAIA::UI::Canvas*)(fac.CreateInstance(GAIA::FWORK::CLSID_UI_CANVAS, GNIL));
	if(pCanvas == GNIL)
		return -1;

	// Create canvas.
	GAIA::UI::Canvas::Desc descCanvas;
	descCanvas.reset();
	descCanvas.pszCaptionText = _T("Hello Venus!");
	pCanvas->Create(descCanvas);
	pCanvas->Show(GAIA::True);

	//
	VENUS::Initialize(fac);
	{
		// Alloc render instance.
		VENUS::Render* pRender = GDCAST(VENUS::Render*)(fac.CreateInstance(VENUS::CLSID_VENUS_RENDERGL, GNIL));
		if(pRender == GNIL)
		{
			VENUS::Release(fac);
			pCanvas->Release();
			return -1;
		}

		// Create render.
		VENUS::Render::Desc descRender;
		descRender.reset();
		descRender.pCanvas = pCanvas;
		pRender->Create(descRender);

		// Create context.
		VENUS::Render::Context* pContext = pRender->CreateContext();

		// 
		for(;;)
		{
			GAIA::BL bExistMsg;
			if(!GAIA::UI::UpdateMessage(GAIA::False, bExistMsg))
				break;
			if(!bExistMsg)
				FrameLoop(*pContext, pRender);
		}

		// Release context.
		pContext->Release();

		// Destroy render.
		pRender->Destroy();

		// Release render instance.
		pRender->Release();
	}
	VENUS::Release(fac);

	// Release canvas instance.
	pCanvas->Release();
	
	return 0;
}