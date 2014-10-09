#ifndef		__GAIA_TIME_TIMER_H__
#define		__GAIA_TIME_TIMER_H__

namespace GAIA
{
	namespace TIMER
	{
		class Timer : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::N32 __FireTimesType;

		public:
			GAIA_ENUM_BEGIN(FIRE_REASON)
				FIRE_REASON_NORMAL,
				FIRE_REASON_REGIST,
				FIRE_REASON_UNREGIST,
				FIRE_REASON_PAUSE,
				FIRE_REASON_RESUME,
				FIRE_REASON_UPDATE,
			GAIA_ENUM_END(FIRE_REASON)

			class TimerDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
				GAIA::N64 m_nEscapeInMicroSec;
				__FireTimesType m_nMaxFireTimes;
				GAIA::U8 m_bRegistFire : 1;
				GAIA::U8 m_bUnregistFire : 1;
				GAIA::U8 m_bPauseFire : 1;
				GAIA::U8 m_bResumeFire : 1;
				GAIA::U8 m_bGoFrontAble : 1;
				GAIA::U8 m_bGoBackAble : 1;
				GAIA::U8 m_bUpdate : 1;
			};

		public:
			GINL Timer(){this->init();}
			GINL ~Timer(){}

			GINL GAIA::BL Create(const GAIA::TIMER::Timer::TimerDesc& desc);
			GINL GAIA::GVOID Destroy();
			GINL const GAIA::TIMER::Timer::TimerDesc& GetDesc() const{return m_desc;}

			GINL GAIA::TIMER::TimerMgr* GetTimerMgr() const;

			GINL GAIA::BL Pause();
			GINL GAIA::BL Resume();

			virtual GAIA::BL Update(GAIA::TIMER::Timer::FIRE_REASON reason) = 0;

		private:
			GINL GAIA::GVOID init(){}

		private:
			TimerDesc m_desc;
			GAIA::N64 m_nRegistTime;
			GAIA::N64 m_nLastFireTime;
			__FireTimesType m_nFireTimes;
		};

		class TimerMgr : public virtual GAIA::FWORK::Instance
		{
		public:
			class TimerMgrDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
			};

		public:
			GINL TimerMgr(){this->init();}
			GINL ~TimerMgr(){}

			GINL GAIA::BL Create(const GAIA::TIMER::TimerMgr::TimerMgrDesc& desc);
			GINL GAIA::GVOID Destroy();
			GINL const GAIA::TIMER::TimerMgr::TimerMgrDesc& GetDesc() const;

			GINL GAIA::BL Regist(GAIA::TIMER::Timer* pTimer);
			GINL GAIA::BL Unregist(GAIA::TIMER::Timer* pTimer);
			GINL GAIA::BL IsRegisted(GAIA::TIMER::Timer* pTimer) const;

			GINL GAIA::BL Update(const GAIA::N64& nEscapeInMicroSec);

		private:
			GINL GAIA::GVOID init()
			{
			}

		private:
		};
	};
};

#endif