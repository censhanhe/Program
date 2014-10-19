#ifndef		__GAIA_TIME_TIMER_H__
#define		__GAIA_TIME_TIMER_H__

namespace GAIA
{
	namespace TIMER
	{
		class Timer : public virtual GAIA::FWORK::Instance
		{
		public:
			friend class GAIA::TIMER::TimerMgr;

		public:
			typedef GAIA::N32 __FireTimesType;
			typedef GAIA::N64 __MicroSecType;
			typedef GAIA::CTN::Vector<Timer*> __TimerList;

		public:
			GAIA_ENUM_BEGIN(FIRE_REASON)
				FIRE_REASON_NORMAL,
				FIRE_REASON_REGIST,
				FIRE_REASON_UNREGIST,
				FIRE_REASON_PAUSE,
				FIRE_REASON_RESUME,
				FIRE_REASON_UPDATE,
			GAIA_ENUM_END(FIRE_REASON)

			class TimerFireDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					bRegistFire = GAIA::False;
					bUnregistFire = GAIA::False;
					bPauseFire = GAIA::False;
					bResumeFire = GAIA::False;
					bUpdate = GAIA::True;
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
				GAIA::U8 bRegistFire : 1; // Fired when regist timer to TimerMgr.
				GAIA::U8 bUnregistFire : 1; // Fired when unregist timer from TimerMgr.
				GAIA::U8 bPauseFire : 1; // Fired when pause the timer.
				GAIA::U8 bResumeFire : 1; // Fired when resume the timer.
				GAIA::U8 bUpdate : 1; // Fired when the time escape reached and update the TimerMgr.
			};
			class TimerDirDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					bGoFrontAble = GAIA::True;
					bGoBackAble = GAIA::False;
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
				GAIA::U8 bGoFrontAble : 1; // Specified the timer can go front. 
				GAIA::U8 bGoBackAble : 1; // Specified the timer can go back.
			};
			class TimerDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					descFire.reset();
					descDir.reset();
					nEscape = 0;
					nMaxFireTimes = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!deseFire.check())
						return GAIA::False;
					if(!descDir.check())
						return GAIA::False;
					if(nEscape == 0)
						return GAIA::False;
					if(nMaxFireTimes == 0)
						return GAIA::False;
					return GAIA::True;
				}
				TimerFireDesc descFire;
				TimerDirDesc descDir;
				__MicroSecType nEscape;
				__FireTimesType nMaxFireTimes;
			};

		public:
			GINL Timer(){this->init();}
			GINL ~Timer(){}

			GINL GAIA::BL Create(const GAIA::TIMER::Timer::TimerDesc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
				if(m_pTimerMgr != GNIL)
					m_pTimerMgr->Unregist(*this);
				GAIA_RELEASE_SAFE(m_pTimerMgr);
			}
			GINL const GAIA::TIMER::Timer::TimerDesc& GetDesc() const{return m_desc;}

			GINL const GAIA::TIMER::Timer::TimerFireDesc& GetFireDesc() const{return m_desc.descFire;}
			GINL GAIA::BL SetFireDesc(const GAIA::TIMER::Timer::TimerFireDesc& descFire){m_desc.descFire = descFire; reture GAIA::True;}

			GINL GAIA::TIMER::TimerMgr* GetTimerMgr() const
			{
				if(m_pTimerMgr != GNIL)
					m_pTimerMgr->Reference();
				return m_pTimerMgr;
			}
			GINL GAIA::BL IsRegisted() const{return m_pTimerMgr != GNIL;}

			GINL GAIA::BL Pause()
			{
				return GAIA::True;
			}
			GINL GAIA::BL Resume()
			{
				return GAIA::True;
			}

			virtual GAIA::BL Update(GAIA::TIMER::Timer::FIRE_REASON reason) = 0;

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_nRegistTime = 0;
				m_nLastFireTime = 0;
				m_nFireTimes = 0;
				m_pTimerMgr = GNIL;
			}
			GINL GAIA::GVOID SetTimerMgr(GAIA::TIMER::TimerMgr* pTimerMgr)
			{
				GAIA_RELEASE_SAFE(m_pTimerMgr);
				if(pTimerMgr != GNIL)
				{
					m_pTimerMgr = pTimerMgr;
					m_pTimerMgr->Reference();
				}
			}

		private:
			TimerDesc m_desc;
			__MicroSecType m_nRegistTime;
			__MicroSecType m_nLastFireTime;
			__FireTimesType m_nFireTimes;
			GAIA::TIMER::TimerMgr* m_pTimerMgr;
		};

		class TimerMgr : public virtual GAIA::FWORK::Instance
		{
		public:
			class TimerMgrDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					sGroupCount = 32;
				}
				virtual GAIA::BL check() const
				{
					if(sGroupCount <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sGroupCount;
			};

		public:
			GINL TimerMgr(){this->init();}
			GINL ~TimerMgr(){}

			GINL GAIA::BL Create(const GAIA::TIMER::TimerMgr::TimerMgrDesc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
			}
			GINL const GAIA::TIMER::TimerMgr::TimerMgrDesc& GetDesc() const{return m_desc;}

			GINL GAIA::BL Regist(GAIA::TIMER::Timer& timer)
			{
				if(this->IsRegisted(timer))
					return GAIA::False;

				return GAIA::True;
			}
			GINL GAIA::BL Unregist(GAIA::TIMER::Timer& timer)
			{
				if(!this->IsRegist(timer))
					return GAIA::False;

				return GAIA::True;
			}
			GINL GAIA::BL IsRegisted(GAIA::TIMER::Timer& timer) const
			{
				GAIA::TIMER::TimerMgr* pTimerMgr = timer.GetTimerMgr();
				if(pTimerMgr == GNIL)
					return GAIA::False;
				pTimerMgr->Release();
				if(pTimerMgr != this)
					return GAIA::False;
				return GAIA::True;
			}

			GINL GAIA::BL Update(const __MicroSecType& nEscape)
			{
				return GAIA::True;
			}

		private:
			class Group : public GAIA::Base
			{
			public:
				__MicroSecType nEscape;
				__MicroSecType nLastUpdate;
				__TimerList timers;
			};

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_nLastUpdateTime = 0;
			}
			GINL GAIA::GVOID init_groups()
			{
				GAIA_AST(m_groups.empty());
				m_groups.resize(x);
				for(GAIA::SIZE x = 0; x < m_desc.sGroupCount; ++x)
				{
					Group& g = m_groups[x];
					g.nEscape = x * x * 1000 * 1000; // The first group's escape must zero for always update.
					g.nLastUpdate = 0;
				}
			}

		private:
			typedef GAIA::CTN::Vector<Group> __GroupList;

		private:
			TimerMgrDesc m_desc;
			__GroupList m_groups;
			__MicroSecType m_nLastUpdateTime;
		};
	};
};

#endif
