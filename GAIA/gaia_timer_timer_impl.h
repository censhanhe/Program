#ifndef		__GAIA_TIMER_TIMER_IMPL_H__
#define		__GAIA_TIMER_TIMER_IMPL_H__

namespace GAIA
{
	namespace TIMER
	{
		GINL GAIA::GVOID Timer::Destroy()
		{
			if(m_pTimerMgr != GNIL)
				m_pTimerMgr->Unregist(*this);
			GAIA_RELEASE_SAFE(m_pTimerMgr);
		}
		GINL GAIA::TIMER::TimerMgr* Timer::GetTimerMgr() const
		{
			if(m_pTimerMgr != GNIL)
				m_pTimerMgr->Reference();
			return m_pTimerMgr;
		}
		GINL GAIA::GVOID Timer::SetTimerMgr(GAIA::TIMER::TimerMgr* pTimerMgr)
		{
			GAIA_RELEASE_SAFE(m_pTimerMgr);
			if(pTimerMgr != GNIL)
			{
				m_pTimerMgr = pTimerMgr;
				m_pTimerMgr->Reference();
			}
		}
	};
};

#endif