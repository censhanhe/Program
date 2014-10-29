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
		t.Run();
		t.Wait();
		if(t.GetData() != 1)
		{
			GTLINE2("Thread test failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif