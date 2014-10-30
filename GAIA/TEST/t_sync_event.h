#ifndef		__T_SYNC_EVENT_H__
#define		__T_SYNC_EVENT_H__

namespace GAIA_TEST
{
	class ThdEvent : public GAIA::THREAD::Thread
	{
	public:
		GINL ThdEvent(GAIA::SYNC::Event* pEvent){this->init(); m_pEvent = pEvent;}
		virtual GAIA::GVOID WorkProcedure()
		{
			m_pEvent->Wait((GAIA::U32)GINVALID);
			if(this->GetState() == GAIA::THREAD::Thread::STATE_RUNNING)
				m_sData = 1;
		}
		GINL GAIA::SIZE GetData() const{return m_sData;}
	private:
		GINL GAIA::GVOID init(){m_sData = 0; m_pEvent = GNIL;}
	private:
		GAIA::SIZE m_sData;
		GAIA::SYNC::Event* m_pEvent;
	};

	GINL GAIA::N32 t_sync_event(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::SYNC::Event e;
		if(e.Wait(10))
		{
			GTLINE2("Event wait error!");
			++nRet;
		}
		e.Fire();
		if(!e.Wait((GAIA::U32)GINVALID))
		{
			GTLINE2("Event wait error!");
			++nRet;
		}

		ThdEvent t(&e);
		e.Fire();
		if(!t.Run())
		{
			GTLINE2("Event thread run error!");
			++nRet;
		}
		if(!t.Wait())
		{
			GTLINE2("Event thread wait error!");
			++nRet;
		}
		if(t.GetData() != 1)
		{
			GTLINE2("Event error!");
			++nRet;
		}

		return nRet;
	}
};

#endif