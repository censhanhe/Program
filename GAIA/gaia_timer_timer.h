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
			typedef GAIA::N32 __UpdateTimesType;
			typedef GAIA::N64 __MicroSecType;
			typedef GAIA::CTN::Book<Timer*> __TimerList;

		public:
			GAIA_ENUM_BEGIN(FIRE_REASON)
				FIRE_REASON_NORMAL,
				FIRE_REASON_REGIST,
				FIRE_REASON_UNREGIST,
				FIRE_REASON_PAUSE,
				FIRE_REASON_RESUME,
				FIRE_REASON_UPDATE,
			GAIA_ENUM_END(FIRE_REASON)

		public:
			class CallBack : public GAIA::Base
			{
			public:
				GINL CallBack(){}
				virtual GAIA::GVOID UpdateTimer(GAIA::TIMER::Timer* pTimer, GAIA::TIMER::Timer::FIRE_REASON reason) = 0;
			};

			class FireDesc : public virtual GAIA::FWORK::InstanceDesc
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
			class DirDesc : public virtual GAIA::FWORK::InstanceDesc
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
			class Desc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					descFire.reset();
					descDir.reset();
					nEscapeUSec = 0;
					nMaxUpdateTimes = 0;
					pCallBack = GNIL;
					bAutoRelease = GAIA::True;
					bMultiCallBack = GAIA::True;
				}
				virtual GAIA::BL check() const
				{
					if(!descFire.check())
						return GAIA::False;
					if(!descDir.check())
						return GAIA::False;
					if(nEscapeUSec < 0)
						return GAIA::False;
					if(nMaxUpdateTimes <= 0)
						return GAIA::False;
					if(pCallBack == GNIL)
						return GAIA::False;
					return GAIA::True;
				}
				FireDesc descFire;
				DirDesc descDir;
				__MicroSecType nEscapeUSec;
				__UpdateTimesType nMaxUpdateTimes;
				CallBack* pCallBack;
				GAIA::U8 bAutoRelease : 1; // If the timer update times equal to max update times, the timer instance will released automatically.
				GAIA::U8 bMultiCallBack : 1; // If the timer will be callback many times in single frame.
			};

		public:
			GINL Timer(){this->init();}
			GINL ~Timer(){this->Destroy();}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_TIMER_TIMER;}
			GINL GAIA::BL Create(const GAIA::TIMER::Timer::Desc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				m_desc = desc;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy();
			GINL const GAIA::TIMER::Timer::Desc& GetDesc() const{return m_desc;}

			GINL const GAIA::TIMER::Timer::FireDesc& GetFireDesc() const{return m_desc.descFire;}
			GINL GAIA::BL SetFireDesc(const GAIA::TIMER::Timer::FireDesc& descFire){m_desc.descFire = descFire; return GAIA::True;}

			GINL GAIA::TIMER::TimerMgr* GetTimerMgr() const;
			GINL GAIA::BL IsRegisted() const{return m_pTimerMgr != GNIL;}
			GINL const __MicroSecType& GetRegistTime() const{return m_nRegistTime;}
			GINL const __MicroSecType& GetLastUpdateTime() const{return m_nLastUpdateTime;}
			GINL const __UpdateTimesType& GetUpdateTimes() const{return m_nUpdateTimes;}

			GINL GAIA::BL Pause();
			GINL GAIA::BL Resume();
			GINL GAIA::BL IsPaused() const{return m_bPaused;}
			GINL GAIA::GVOID Update(GAIA::TIMER::Timer::FIRE_REASON reason);

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_nRegistTime = 0;
				m_nLastUpdateTime = 0;
				m_nUpdateTimes = 0;
				m_pTimerMgr = GNIL;
				m_sGroupIndex = GINVALID;
				m_sIndex = GINVALID;
				m_bPaused = GAIA::False;
			}
			GINL GAIA::GVOID SetTimerMgr(GAIA::TIMER::TimerMgr* pTimerMgr);
			GINL GAIA::GVOID SetRegistTime(const __MicroSecType& t){m_nRegistTime = t;}
			GINL GAIA::GVOID SetLastUpdateTime(const __MicroSecType& t){m_nLastUpdateTime = t;}
			GINL GAIA::GVOID SetUpdateTimes(const __UpdateTimesType& t){m_nUpdateTimes = t;}
			GINL GAIA::GVOID SetGroupIndex(const GAIA::SIZE& index){m_sGroupIndex = index;}
			GINL const GAIA::SIZE& GetGroupIndex() const{return m_sGroupIndex;}
			GINL GAIA::GVOID SetIndex(const GAIA::SIZE& index){m_sIndex = index;}
			GINL const GAIA::SIZE& GetIndex() const{return m_sIndex;}

		private:
			Desc m_desc;
			__MicroSecType m_nRegistTime;
			__MicroSecType m_nLastUpdateTime;
			__UpdateTimesType m_nUpdateTimes;
			GAIA::TIMER::TimerMgr* m_pTimerMgr;
			GAIA::SIZE m_sGroupIndex;
			GAIA::SIZE m_sIndex;
			GAIA::U8 m_bPaused : 1;
		};

		class TimerMgr : public virtual GAIA::FWORK::Instance
		{
		public:
			class Desc : public virtual GAIA::FWORK::InstanceDesc
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
			GINL ~TimerMgr(){this->Destroy();}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_TIMER_TIMERMGR;}
			GINL GAIA::BL Create(const GAIA::TIMER::TimerMgr::Desc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				this->init_groups();
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
				for(GAIA::SIZE x = 0; x < m_groups.size(); ++x)
				{
					Group& g = m_groups[x];
					GAIA::TIMER::Timer::__TimerList::it it = g.timers.front_it();
					for(; !it.empty(); ++it)
					{
						GAIA::TIMER::Timer* pTimer = *it;
						GAIA_RELEASE_SAFE(pTimer);
					}
				}
				m_nLastUpdateTime = 0;
				m_desc.reset();
			}
			GINL const GAIA::TIMER::TimerMgr::Desc& GetDesc() const{return m_desc;}

			GINL GAIA::BL Regist(GAIA::TIMER::Timer& timer)
			{
				if(this->IsRegisted(timer))
					return GAIA::False;

				/* Add reference. */
				timer.Reference();

				/* Regist. */
				GAIA::SIZE sGroupIndex = this->GetGroupIndexByTime(timer.GetDesc().nEscapeUSec);
				if(sGroupIndex >= m_groups.size())
					sGroupIndex = m_groups.size() - 1;
				Group& g = m_groups[sGroupIndex];
				GAIA::SIZE sUsedIndex = g.timers.set(&timer);
				timer.SetTimerMgr(this);
				timer.SetRegistTime(this->GetLastUpdateTime());
				timer.SetLastUpdateTime(this->GetLastUpdateTime());
				timer.SetGroupIndex(sGroupIndex);
				timer.SetIndex(g.timers.fixedindex(sUsedIndex));

				/* Regist fire. */
				if(timer.GetDesc().descFire.bRegistFire)
					timer.Update(GAIA::TIMER::Timer::FIRE_REASON_REGIST);

				return GAIA::True;
			}
			GINL GAIA::BL Unregist(GAIA::TIMER::Timer& timer)
			{
				if(!this->IsRegisted(timer))
					return GAIA::False;

				/* Unregist fire. */
				if(timer.GetDesc().descFire.bUnregistFire)
					timer.Update(GAIA::TIMER::Timer::FIRE_REASON_UNREGIST);

				/* Unregist. */
				GAIA::SIZE sGroupIndex = timer.GetGroupIndex();
				GAIA::SIZE sFixedIndex = timer.GetIndex();
				GAIA_AST(sGroupIndex != GINVALID);
				GAIA_AST(sFixedIndex != GINVALID);
				Group& g = m_groups[sGroupIndex];
				GAIA::SIZE sUsedIndex = g.timers.usedindex(sFixedIndex);
				if(!g.timers.erase(sUsedIndex))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				timer.SetTimerMgr(GNIL);
				timer.SetGroupIndex(GINVALID);
				timer.SetIndex(GINVALID);

				/* Release. */
				timer.Release();

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
				GAIA_AST(timer.GetGroupIndex() != GINVALID);
				GAIA_AST(timer.GetGroupIndex() < m_groups.size());
				const Group& g = m_groups[timer.GetGroupIndex()];
				GAIA::SIZE sUseIndex = g.timers.usedindex(timer.GetIndex());
				GAIA_AST(sUseIndex != GINVALID);
				GAIA_AST(g.timers[sUseIndex] == &timer);
				return GAIA::True;
			}

			GINL GAIA::GVOID Update(const GAIA::TIMER::Timer::__MicroSecType& nEscape)
			{
				m_nLastUpdateTime += nEscape;
				for(GAIA::SIZE x = 0; x < m_groups.size(); ++x)
				{
					Group& g = m_groups[x];
					if(x == 0)
					{
						GAIA::TIMER::Timer::__TimerList::it it = g.timers.front_it();
						for(; !it.empty(); ++it)
						{
							GAIA::TIMER::Timer* pTimer = *it;
							GAIA_AST(pTimer != GNIL);
							pTimer->SetLastUpdateTime(this->GetLastUpdateTime());
							pTimer->Update(GAIA::TIMER::Timer::FIRE_REASON_UPDATE);
						}
						g.nLastUpdate = this->GetLastUpdateTime();
					}
					else
					{
						/* Get need update for current group. */
						GAIA::BL bNeedUpdate = GAIA::False;
						GAIA::TIMER::Timer::__MicroSecType nGroupOffsetTime = this->GetLastUpdateTime() - g.nLastUpdate;
						if(nGroupOffsetTime > m_groups[x - 1].nEscape)
							bNeedUpdate = GAIA::True;

						/* If current group need update, update it. */
						if(bNeedUpdate)
						{
							GAIA::TIMER::Timer::__TimerList::it it = g.timers.front_it();
							for(; !it.empty(); ++it)
							{
								GAIA::TIMER::Timer* pTimer = *it;
								GAIA::TIMER::Timer::__MicroSecType nOffsetTime = this->GetLastUpdateTime() - pTimer->GetLastUpdateTime();
								const GAIA::TIMER::Timer::Desc& descTimer = pTimer->GetDesc();
								if(nOffsetTime > descTimer.nEscapeUSec)
								{
									if(pTimer->GetDesc().bMultiCallBack)
									{
										while(this->GetLastUpdateTime() - pTimer->GetLastUpdateTime() > descTimer.nEscapeUSec)
										{
											pTimer->SetLastUpdateTime(pTimer->GetLastUpdateTime() + pTimer->GetDesc().nEscapeUSec);
											pTimer->Update(GAIA::TIMER::Timer::FIRE_REASON_UPDATE);
										}
									}
									else
									{
										GAIA::TIMER::Timer::__MicroSecType nFireTimes = nOffsetTime / descTimer.nEscapeUSec;
										pTimer->SetLastUpdateTime(pTimer->GetLastUpdateTime() + nFireTimes * pTimer->GetDesc().nEscapeUSec);
										pTimer->Update(GAIA::TIMER::Timer::FIRE_REASON_UPDATE);
									}
								}
								this->SwitchTimerToNewGroup(*pTimer);
							}
						}
					}
				}
			}
			GINL const GAIA::TIMER::Timer::__MicroSecType& GetLastUpdateTime() const{return m_nLastUpdateTime;}

		private:
			class Group : public GAIA::Base
			{
			public:
				GAIA::TIMER::Timer::__MicroSecType nEscape;
				GAIA::TIMER::Timer::__MicroSecType nLastUpdate;
				GAIA::TIMER::Timer::__TimerList timers;
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
				m_groups.resize(m_desc.sGroupCount);
				for(GAIA::SIZE x = 0; x < m_desc.sGroupCount; ++x)
				{
					Group& g = m_groups[x];
					g.nEscape = x * x * 1000 * 1000; // The first group's escape must zero for always update.
					g.nLastUpdate = 0;
				}
				m_groups.back().nEscape = GAIA::N64MAXSIZE;
			}

			GINL GAIA::SIZE GetGroupIndexByTime(const GAIA::TIMER::Timer::__MicroSecType& nEscapeUSec) const
			{
				if(nEscapeUSec == 0)
					return 0;
				GAIA::F64 fGroupIndex = GAIA::MATH::xsqrt(GSCAST(GAIA::F64)(nEscapeUSec) / 1000.0 / 1000.0);
				return GSCAST(GAIA::SIZE)(GAIA::MATH::xceil(fGroupIndex));
			}
			GINL GAIA::GVOID SwitchTimerToNewGroup(GAIA::TIMER::Timer& timer)
			{
				GAIA_AST(timer.IsRegisted());
				GAIA::TIMER::Timer::__MicroSecType nOffsetTime = this->GetLastUpdateTime() - timer.GetLastUpdateTime();
				GAIA::SIZE sNewGroupIndex = this->GetGroupIndexByTime(nOffsetTime);
				if(sNewGroupIndex != timer.GetGroupIndex())
				{
					GAIA_AST(sNewGroupIndex < m_groups.size());

					/* Erase from old group. */
					Group& gold = m_groups[timer.GetGroupIndex()];
					GAIA::SIZE sOldUsedIndex = gold.timers.usedindex(timer.GetIndex());
					gold.timers.erase(sOldUsedIndex);

					/* Add to new group. */
					Group& gnew = m_groups[sNewGroupIndex];
					GAIA::SIZE sNewUsedIndex = gnew.timers.set(&timer);
					GAIA::SIZE sNewFixedIndex = gnew.timers.fixedindex(sNewUsedIndex);

					/* Update index. */
					timer.SetGroupIndex(sNewGroupIndex);
					timer.SetIndex(sNewUsedIndex);
				}
			}
		private:
			typedef GAIA::CTN::Vector<Group> __GroupList;

		private:
			Desc m_desc;
			__GroupList m_groups;
			GAIA::TIMER::Timer::__MicroSecType m_nLastUpdateTime;
		};
	};
};

#endif
