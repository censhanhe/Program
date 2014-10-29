#ifndef		__T_THREAD_THREAD_H__
#define		__T_THREAD_THREAD_H__

namespace GAIA_TEST
{
	class Thd : public GAIA::THREAD::Thread
	{
	public:
		GINL Thd(){this->init();}
		virtual GAIA::GVOID WorkProcedure()
		{
			if(this->GetState() == GAIA::THREAD::Thread::THREAD_STATE_RUNING)
				m_sData = 1;
		}
		GINL GAIA::SIZE GetData() const{return m_sData;}
	private:
		GINL GAIA::GVOID init(){m_sData = 0;}
	private:
		GAIA::SIZE m_sData;
	};

	GINL GAIA::N32 t_thread_thread(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		Thd t;
		t.SetStackSize(1024);
		if(t.GetStackSize() != 1024)
		{
			GTLINE2("Thread stack size set failed!");
			++nRet;
		}
		if(t.GetState() != GAIA::THREAD::Thread::THREAD_STATE_INVALID)
		{
			GTLINE2("Thread state error!");
			++nRet;
		}
		t.Run();
		t.Wait();
		if(t.GetState() != GAIA::THREAD::Thread::THREAD_STATE_INVALID)
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

#endif