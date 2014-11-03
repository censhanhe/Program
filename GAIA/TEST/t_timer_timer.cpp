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

	extern GAIA::N32 t_timer_timer(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::FWORK::Factory fac;

		GAIA::TIMER::TimerMgr* pTimerMgr = GDCAST(GAIA::TIMER::TimerMgr*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMERMGR, GNIL));
		GAIA::TIMER::Timer* pTimer1 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));
		GAIA::TIMER::Timer* pTimer2 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));

		GAIA::TIMER::TimerMgr::Desc descTimerMgr;
		descTimerMgr.reset();
		pTimerMgr->Create(descTimerMgr);

		GAIA::SYNC::Lock l;
		GAIA::TIMER::Timer::__UpdateTimesType sum = 0;
		TimerCallBack1 cb1;
		cb1.SetLock(l);
		cb1.SetUpdateTimeSum(sum);
		TimerCallBack2 cb2;
		cb2.SetLock(l);
		cb2.SetUpdateTimeSum(sum);

		GAIA::TIMER::Timer::Desc descTimer;
		descTimer.reset();

		descTimer.nEscapeUSec = 1000 * 100;
		descTimer.nMaxUpdateTimes = 10;
		descTimer.pCallBack = &cb1;
		if(!pTimer1->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		descTimer.nEscapeUSec = 1000 * 20;
		descTimer.nMaxUpdateTimes = 50;
		descTimer.pCallBack = &cb2;
		if(!pTimer2->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

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

		GAIA::TIMER::Timer::__MicroSecType tDelta = 0;
		GAIA::TIMER::Timer::__MicroSecType t = GAIA::TIME::tick_time();
		for(;;)
		{
			GAIA::TIMER::Timer::__MicroSecType tNew = GAIA::TIME::tick_time();
			pTimerMgr->Update(tNew - t);
			tDelta += tNew - t;
			t = tNew;
			if(tDelta > 2000 * 1000)
				break;
		}
		pTimerMgr->Update(0);

		if(sum != 60)
		{
			GTLINE2("Timer update failed!");
			++nRet;
		}

		GAIA_RELEASE_SAFE(pTimerMgr);

		return nRet;
	}
};