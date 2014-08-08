#ifndef		__T_UI_CANVAS_H__
#define		__T_UI_CANVAS_H__

namespace GAIATEST
{
	class CanvasTestThread : public GAIA::THREAD::Thread
	{
	public:
		GINL CanvasTestThread(GAIA::UI::Canvas* pCanvas1, GAIA::UI::Canvas* pCanvas2){m_pCanvas1 = pCanvas1; m_pCanvas2 = pCanvas2; m_bResult = GAIA::True;}
		GINL GAIA::GVOID SetResult(GAIA::BL bResult){m_bResult = bResult;}
		GINL GAIA::BL GetResult() const{return m_bResult;}
		virtual GAIA::GVOID WorkProcedure()
		{
			static const GAIA::U32 SLEEP_TIME = 1000;
			GPCHR_NULL(m_pCanvas1);
			GPCHR_NULL(m_pCanvas2);
			
			/* Test position operation. */
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->Position(16))
				this->SetResult(GAIA::False);
			GAIA::UI::Canvas::__PosType pos = m_pCanvas1->Position();
			if(pos.x != 16 || pos.y != 16)
				this->SetResult(GAIA::False);

			/* Test size operation. */
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->Size(400))
				this->SetResult(GAIA::False);
			GAIA::UI::Canvas::__SizeType size = m_pCanvas1->Size();
			if(size.x != 400 || size.y != 400)
				this->SetResult(GAIA::False);

			/* Test show operation. */
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->Show(GAIA::False))
				this->SetResult(GAIA::False);
			if(m_pCanvas1->IsShow())
				this->SetResult(GAIA::False);
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->Show(GAIA::True))
				this->SetResult(GAIA::False);
			if(!m_pCanvas1->IsShow())
				this->SetResult(GAIA::False);

			/* Set caption text operation. */
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->SetCaptionText(_T("This is the canvas 1 !!!!!!!!!!")))
				this->SetResult(GAIA::False);
			if(!m_pCanvas2->SetCaptionText(_T("This is the canvas 2 !!!!!!!!!!")))
				this->SetResult(GAIA::False);

			/* Test quit operation. */
			GAIA::SYNC::xsleep(SLEEP_TIME);
			if(!m_pCanvas1->Quit())
				this->SetResult(GAIA::False);
			if(!m_pCanvas2->Quit())
				this->SetResult(GAIA::False);
		}
	private:
		GAIA::UI::Canvas* m_pCanvas1;
		GAIA::UI::Canvas* m_pCanvas2;
		GAIA::BL m_bResult;
	};

	GINL GAIA::N32 t_ui_canvas(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		/* Construct factory. */
		GAIA::FRAMEWORK::Factory fac;

		/* Construct canvas instance. */
		GAIA::UI::Canvas* pCanvas1 = dynamic_cast<GAIA::UI::Canvas*>(fac.CreateInstance(GAIA::FRAMEWORK::CLSID_CANVAS, GNULL));
		if(pCanvas1 == GNULL)
		{
			GTLINE2("Create canvas1 failed!");
			++nRet;
			return nRet;
		}
		GAIA::UI::Canvas* pCanvas2 = dynamic_cast<GAIA::UI::Canvas*>(fac.CreateInstance(GAIA::FRAMEWORK::CLSID_CANVAS, GNULL));
		if(pCanvas2 == GNULL)
		{
			GTLINE2("Create canvas2 failed!");
			++nRet;
			return nRet;
		}
		/* Create and show canvas. */
		GAIA::UI::Canvas::CanvasDesc desc;
		desc.pszCaptionText = _T("Test canvas 1");
		pCanvas1->Create(desc);
		pCanvas1->Show(GAIA::True);

		desc.pszCaptionText = _T("Test canvas 2");
		pCanvas2->Create(desc);
		pCanvas2->Show(GAIA::True);
		if(!pCanvas2->Position(400))
		{
			GTLINE2("Canvas set position failed!");
			++nRet;
		}
		if(!pCanvas2->Size(GAIA::UI::Canvas::__SizeType(400, 100)))
		{
			GTLINE2("Canvas set size failed!");
			++nRet;
		}

		/* Begin test thread. */
		CanvasTestThread th(pCanvas1, pCanvas2);
		th.Run();

		/* Dispatch message in main thread. */
		while(GAIA::UI::UpdateMessage(GAIA::True))
		{
		}

		/* Print the test result. */
		if(!th.GetResult())
		{
			GTLINE2("There are some error occured!");
			++nRet;
		}

		/* Wait the test thread end. */
		th.Wait();

		/* Release the canvas. */
		pCanvas1->Release();
		pCanvas2->Release();

		return nRet;
	}
};

#endif