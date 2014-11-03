#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	class TimerCallBackBase : public GAIA::Base
	{
	public:
		GINL TimerCallBackBase(){this->init();}
		GINL GAIA::GVOID SetLock(GAIA::SYNC::Lock& lock){m_pLock = &lock;}
		GINL GAIA::SYNC::Lock& GetLock() const{return *m_pLock;}
		GINL GAIA::GVOID SetUpdateTimeSum(GAIA::TIMER::Timer::__UpdateTimesType& nSum){m_pSum = &nSum;}
		GINL GAIA::TIMER::Timer::__UpdateTimesType& GetUpdateTimeSum() const{return *m_pSum;}
	private:
		GINL GAIA::GVOID init()
		{
			m_pLock = GNIL;
			m_pSum = GNIL;
		}
	private:
		GAIA::SYNC::Lock* m_pLock;
		GAIA::TIMER::Timer::__UpdateTimesType* m_pSum;
	};
	class TimerCallBack1 : public GAIA::TIMER::Timer::CallBack, public TimerCallBackBase
	{
	public:
		GINL TimerCallBack1(){this->init();}
		virtual GAIA::GVOID UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(this->GetLock());
			++this->GetUpdateTimeSum();
		}
	private:
		GINL GAIA::GVOID init(){}
	};

	class TimerCallBack2 : public GAIA::TIMER::Timer::CallBack, public TimerCallBackBase
	{
	public:
		GINL TimerCallBack2(){this->init();}
		virtual GAIA::GVOID UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(this->GetLock());
			++this->GetUpdateTimeSum();
		}
	private:
		GINL GAIA::GVOID init(){}
	};

	class TimerCallBack3 : public GAIA::TIMER::Timer::CallBack, public TimerCallBackBase
	{
	public:
		GINL TimerCallBack3(){this->init();}
		virtual GAIA::GVOID UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(this->GetLock());
			++this->GetUpdateTimeSum();
		}
	private:
		GINL GAIA::GVOID init(){}
	};

	class TimerCallBack4 : public GAIA::TIMER::Timer::CallBack, public TimerCallBackBase
	{
	public:
		GINL TimerCallBack4(){this->init();}
		virtual GAIA::GVOID UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(this->GetLock());
		}
	private:
		GINL GAIA::GVOID init(){}
	};

	extern GAIA::N32 t_timer_timer(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		/* Create common object. */
		GAIA::FWORK::Factory fac;
		GAIA::SYNC::Lock l;
		GAIA::TIMER::Timer::__UpdateTimesType sum = 0;
		GAIA::TIMER::Timer::Desc descTimer;

		/* Create instance. */
		GAIA::TIMER::TimerMgr* pTimerMgr = GDCAST(GAIA::TIMER::TimerMgr*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMERMGR, GNIL));
		GAIA::TIMER::Timer* pTimer1 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));
		GAIA::TIMER::Timer* pTimer2 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));
		GAIA::TIMER::Timer* pTimer3 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));
		GAIA::TIMER::Timer* pTimer4 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));

		/* Create timer manager. */
		GAIA::TIMER::TimerMgr::Desc descTimerMgr;
		descTimerMgr.reset();
		pTimerMgr->Create(descTimerMgr);

		/* Create callback. */
		TimerCallBack1 cb1;
		cb1.SetLock(l);
		cb1.SetUpdateTimeSum(sum);

		TimerCallBack2 cb2;
		cb2.SetLock(l);
		cb2.SetUpdateTimeSum(sum);

		TimerCallBack2 cb3;
		cb3.SetLock(l);
		cb3.SetUpdateTimeSum(sum);

		TimerCallBack4 cb4;
		cb4.SetLock(l);
		cb4.SetUpdateTimeSum(sum);

		/* Create timer. */
		descTimer.reset();
		descTimer.nEscapeUSec = 1000 * 100;
		descTimer.nMaxUpdateTimes = 10;
		descTimer.pCallBack = &cb1;
		if(!pTimer1->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		descTimer.reset();
		descTimer.nEscapeUSec = 1000 * 20;
		descTimer.nMaxUpdateTimes = 50;
		descTimer.pCallBack = &cb2;
		if(!pTimer2->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		descTimer.reset();
		descTimer.nEscapeUSec = 1000 * 1100;
		descTimer.nMaxUpdateTimes = 2;
		descTimer.pCallBack = &cb3;
		descTimer.bAutoRelease = GAIA::False;
		if(!pTimer3->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		descTimer.reset();
		descTimer.nEscapeUSec = 0;
		descTimer.nMaxUpdateTimes = GAIA::N32MAXSIZE;
		descTimer.pCallBack = &cb4;
		descTimer.bAutoRelease = GAIA::True;
		if(!pTimer4->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		/* Regist timer. */
		if(!pTimerMgr->Regist(*pTimer1))
		{
			GTLINE2("Timer regist failed!");
			++nRet;
		}

		if(!pTimerMgr->Regist(*pTimer2))
		{
			GTLINE2("Timer regist failed!");
			++nRet;
		}

		if(!pTimerMgr->Regist(*pTimer3))
		{
			GTLINE2("Timer regist failed!");
			++nRet;
		}

		if(!pTimerMgr->Regist(*pTimer4))
		{
			GTLINE2("Timer regist failed!");
			++nRet;
		}

		/* Update. */
		GAIA::TIMER::Timer::__MicroSecType tDelta = 0;
		GAIA::TIMER::Timer::__MicroSecType t = GAIA::TIME::tick_time();
		for(;;)
		{
			GAIA::TIMER::Timer::__MicroSecType tNew = GAIA::TIME::tick_time();
			pTimerMgr->Update(tNew - t);
			tDelta += tNew - t;
			t = tNew;
			if(tDelta > 4000 * 1000)
				break;
		}
		pTimerMgr->Update(0);

		/* Check result. */
		if(sum != 62)
		{
			GTLINE2("Timer update time sum failed!");
			++nRet;
		}

		if(pTimer3->GetUpdateTimes() != 2)
		{
			GTLINE2("Timer3 update times error!");
			++nRet;
		}

		/* Release instance. */
		GAIA_RELEASE_SAFE(pTimerMgr);
		GAIA_RELEASE_SAFE(pTimer3);

		return nRet;
	}
};