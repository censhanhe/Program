#ifndef		__GAIA_TIME_REALTIMER_H__
#define		__GAIA_TIME_REALTIMER_H__

namespace GAIA
{
	namespace TIMER
	{
		class RealTimer : public virtual GAIA::FWORK::Instance
		{
		public:
			class RealTimerDesc : public virtual GAIA::FWORK::InstanceDesc
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
			GINL RealTimer(){this->init();}
			GINL ~RealTimer(){this->Destroy();}

			GINL GAIA::BL Create(const GAIA::TIMER::RealTimer::RealTimerDesc& desc);
			GINL GAIA::GVOID Destroy(){}
			GINL const GAIA::TIMER::RealTimer::RealTimerDesc& GetDesc() const{return m_desc;}

		private:
			GINL GAIA::GVOID init()
			{
			}

		private:
			GAIA::TIMER::RealTimer::RealTimerDesc m_desc;
		};

		class RealTimerMgr : public virtual GAIA::FWORK::Instance
		{
		public:
			class RealTimerMgrDesc : public virtual GAIA::FWORK::InstanceDesc
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
			GINL RealTimerMgr(){this->init();}
			GINL ~RealTimerMgr(){this->Destroy();}

			GINL GAIA::BL Create(const GAIA::TIMER::RealTimerMgr::RealTimerMgrDesc& desc);
			GINL GAIA::GVOID Destroy(){}
			GINL const GAIA::TIMER::RealTimerMgr::RealTimerMgrDesc& GetDesc() const{return m_desc;}

			GINL GAIA::BL Regist(GAIA::TIMER::RealTimer* pRealTimer);
			GINL GAIA::BL Unregist(GAIA::TIMER::RealTimer* pRealTimer);
			GINL GAIA::BL IsRegisted(GAIA::TIMER::RealTimer* pRealTimer) const;

			GINL GAIA::BL Update(const GAIA::TIME::Time& t);

		private:
			GINL GAIA::GVOID init()
			{
			}

		private:
			GAIA::TIMER::RealTimerMgr::RealTimerMgrDesc m_desc;
		};
	};
};

#endif