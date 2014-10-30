#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	class ThdLock : public GAIA::THREAD::Thread
	{
	public:
		GINL ThdLock(){this->init();}
		virtual GAIA::GVOID WorkProcedure()
		{
			for(GAIA::SIZE x = 0; x < 100000; ++x)
			{
				if(m_p == GNIL)
					return;
				GAIA::SYNC::AutoLock al(*m_pLock);
				*m_p += 1;
			}
			if(this->GetState() == GAIA::THREAD::Thread::STATE_RUNNING)
				m_sData = 1;
		}
		GINL GAIA::GVOID SetParam(GAIA::SYNC::Lock* pLock, GAIA::U32* p){m_pLock = pLock; m_p = p;}
		GINL GAIA::SIZE GetData() const{return m_sData;}
	private:
		GINL GAIA::GVOID init(){m_sData = 0; m_pLock = GNIL; m_p = GNIL;}
	private:
		GAIA::SIZE m_sData;
		GAIA::SYNC::Lock* m_pLock;
		GAIA::U32* m_p;
	};


	extern GAIA::N32 t_sync_lock(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::U32 THREAD_COUNT = 10;
		GAIA::SYNC::Lock l;
		GAIA::U32 u = 0;
		ThdLock t[THREAD_COUNT];
		
		for(GAIA::SIZE x = 0; x < THREAD_COUNT; ++x)
			t[x].SetParam(&l, &u);
		for(GAIA::SIZE x = 0; x < THREAD_COUNT; ++x)
			t[x].Run();
		for(GAIA::SIZE x = 0; x < THREAD_COUNT; ++x)
		{
			t[x].Wait();
			if(t[x].GetData() != 1)
			{
				GTLINE2("Lock test failed!");
				++nRet;
				break;
			}
		}
		if(u != 1000000)
		{
			GTLINE2("Lock test failed!");
			++nRet;
		}

		return nRet;
	}
};
