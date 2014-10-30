#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	class Thd : public GAIA::THREAD::Thread
	{
	public:
		GINL Thd(){this->init();}
		virtual GAIA::GVOID WorkProcedure()
		{
			if(this->GetState() == GAIA::THREAD::Thread::STATE_RUNNING)
				m_sData = 1;
		}
		GINL GAIA::SIZE GetData() const{return m_sData;}
	private:
		GINL GAIA::GVOID init(){m_sData = 0;}
	private:
		GAIA::SIZE m_sData;
	};

	extern GAIA::N32 t_thread_thread(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		Thd t;
		t.SetStackSize(1024 * 128);
		if(t.GetStackSize() != 1024 * 128)
		{
			GTLINE2("Thread stack size set failed!");
			++nRet;
		}
		if(t.GetState() != GAIA::THREAD::Thread::STATE_INVALID)
		{
			GTLINE2("Thread state error!");
			++nRet;
		}
		if(!t.Run())
		{
			GTLINE2("Thread run failed!");
			++nRet;
		}
		if(!t.Wait())
		{
			GTLINE2("Thread wait failed!");
			++nRet;
		}
		if(t.GetState() != GAIA::THREAD::Thread::STATE_INVALID)
		{
			GTLINE2("Thread state error!");
			++nRet;
		}
		if(t.GetData() != 1)
		{
			GTLINE2("Thread test failed!");
			++nRet;
		}

		return nRet;
	}
};
