#ifndef		__GAIA_TIMER_TIMER_IMPL_H__
#define		__GAIA_TIMER_TIMER_IMPL_H__

namespace GAIA
{
	namespace TIMER
	{
		GINL GAIA::GVOID Timer::Destroy()
		{
			if(this->IsRegisted())
				m_pTimerMgr->Unregist(*this);
			GAIA_RELEASE_SAFE(m_pTimerMgr);
		}
		GINL GAIA::TIMER::TimerMgr* Timer::GetTimerMgr() const
		{
			if(m_pTimerMgr != GNIL)
				m_pTimerMgr->Reference();
			return m_pTimerMgr;
		}
		GINL GAIA::BL Timer::Pause()
		{
			/* Pause. */
			m_bPaused = GAIA::True;

			/* Pause fire. */
			if(m_desc.descFire.bPauseFire)
				this->Update(GAIA::TIMER::Timer::FIRE_REASON_PAUSE);

			return GAIA::True;
		}
		GINL GAIA::BL Timer::Resume()
		{
			/* Resume. */
			m_bPaused = GAIA::False;

			/* Resume fire. */
			if(m_desc.descFire.bResumeFire)
				this->Update(GAIA::TIMER::Timer::FIRE_REASON_RESUME);

			return GAIA::True;
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