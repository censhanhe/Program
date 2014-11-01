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
			m_desc.reset();
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
		GINL GAIA::GVOID Timer::Update(GAIA::TIMER::Timer::FIRE_REASON reason)
		{
			this->Reference();
			{
				/* Get timer manager. */
				GAIA::TIMER::TimerMgr* pTimerMgr = this->GetTimerMgr();

				/* Update last update time. */
				this->SetLastUpdateTime(pTimerMgr->GetLastUpdateTime());

				/* Update update times. */
				this->SetUpdateTimes(this->GetUpdateTimes() + 1);

				/* Update. */
				if(m_desc.pCallBack != GNIL)
					m_desc.pCallBack->UpdateTimer(this, reason);

				/* If complete, unregist and release(if user specified. */
				if(this->GetUpdateTimes() == this->GetDesc().nMaxUpdateTimes)
				{
					if(this->IsRegisted())
					{
						GAIA::BL bUnregistRes = pTimerMgr->Unregist(*this);
						GAIA_AST(bUnregistRes);
					}
					if(this->GetDesc().bAutoRelease)
					{
						if(this->GetRef() > 1)
							this->Release();
					}
				}

				/* Release timer manager. */
				pTimerMgr->Release();
			}
			this->Release();
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