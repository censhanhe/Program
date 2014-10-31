#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	class TimerCallBack1 : public GAIA::TIMER::Timer::CallBack
	{
	public:
		GINL TimerCallBack1(GAIA::SYNC::Lock& lock){this->init(); m_l = &lock;}
		virtual GAIA::BL UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(*m_l);
			return GAIA::True;
		}
	private:
		GINL GAIA::GVOID init(){m_l = GNIL;}
	private:
		GAIA::SYNC::Lock* m_l;
	};

	class TimerCallBack2 : public GAIA::TIMER::Timer::CallBack
	{
	public:
		GINL TimerCallBack2(GAIA::SYNC::Lock& lock){this->init(); m_l = &lock;}
		virtual GAIA::BL UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			GAIA::SYNC::AutoLock al(*m_l);
			return GAIA::True;
		}
	private:
		GINL GAIA::GVOID init(){m_l = GNIL;}
	private:
		GAIA::SYNC::Lock* m_l;
	};

	extern GAIA::N32 t_timer_timer(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::FWORK::Factory fac;

		GAIA::TIMER::TimerMgr* pTimerMgr = GDCAST(GAIA::TIMER::TimerMgr*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMERMGR, GNIL));
		GAIA::TIMER::Timer* pTimer1 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));
		GAIA::TIMER::Timer* pTimer2 = GDCAST(GAIA::TIMER::Timer*)(fac.CreateInstance(GAIA::FWORK::CLSID_TIMER_TIMER, GNIL));

		GAIA::SYNC::Lock l;
		TimerCallBack1 cb1(l);
		TimerCallBack2 cb2(l);

		GAIA::TIMER::Timer::TimerDesc descTimer;
		descTimer.reset();

		descTimer.nEscapeUSec = 1000 * 1000;
		descTimer.pCallBack = &cb1;
		if(!pTimer1->Create(descTimer))
		{
			GTLINE2("Timer create failed!");
			++nRet;
		}

		descTimer.nEscapeUSec = 1000 * 200;
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

		GAIA_RELEASE_SAFE(pTimerMgr);
		GAIA_RELEASE_SAFE(pTimer1);
		GAIA_RELEASE_SAFE(pTimer2);

		return nRet;
	}
};