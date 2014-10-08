#ifndef		__GAIA_STATE_DRIVER_H__
#define		__GAIA_STATE_DRIVER_H__

namespace GAIA
{
	namespace STATE
	{
		class StateDriver : public virtual GAIA::FWORK::Instance
		{
		public:
			class StateCtn : public virtual GAIA::FWORK::Instance
			{
			public:
				class StateCtnDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					GAIA::STATE::StateDriver* pDriver;
				};

			public:
				class State : public virtual GAIA::FWORK::Instance
				{
				public:
					class StateDesc : public virtual GAIA::FWORK::InstanceDesc
					{
					public:
						GAIA::STATE::StateDriver::StateCtn* pCtn;
					};

					class Condition : public GAIA::Base
					{
					public:
						class ConditionKey : public GAIA::Base
						{
						};
					public:
					};

				public:
					GINL State(){this->init();}
					GINL ~State(){}

					GINL GAIA::BL Create(const GAIA::STATE::StateDriver::StateCtn::State::StateDesc& desc);
					GINL GAIA::GVOID Destroy();
					GINL const StateDesc& GetDesc() const;

					GINL GAIA::SIZE InsertEnterCondition(const GAIA::SIZE& index, const GAIA::STATE::StateDriver::StateCtn::State::Condition& cond);
					GINL GAIA::BL DeleteEnterCondition(const GAIA::SIZE& index);
					GINL GAIA::GVOID DeleteEnterConditionAll();
					GINL GAIA::SIZE GetEnterConditionCount() const;
					GINL GAIA::STATE::StateDriver::StateCtn::State::Condition* GetEnterCondition(const GAIA::SIZE& index) const;

					GINL GAIA::SIZE InsertLeaveCondition(const GAIA::SIZE& index, const GAIA::STATE::StateDriver::StateCtn::State::Condition& cond);
					GINL GAIA::BL DeleteLeaveCondition(const GAIA::SIZE& index);
					GINL GAIA::GVOID DeleteLeaveConditionAll();
					GINL GAIA::SIZE GetLeaveConditionCount() const;
					GINL GAIA::STATE::StateDriver::StateCtn::State::Condition* GetLeaveCondition(const GAIA::SIZE& index) const;

					virtual GAIA::BL EnterState() = 0;
					virtual GAIA::BL LeaveState() = 0;
					virtual GAIA::BL UpdateState() = 0;

				private:
					GINL GAIA::GVOID init()
					{
					}

				private:
				};

			public:
				GINL StateCtn(){this->init();}
				GINL ~StateCtn(){}

				GINL GAIA::BL Create(const GAIA::STATE::StateDriver::StateCtn::StateCtnDesc& desc);
				GINL GAIA::GVOID Destroy();
				GINL const GAIA::STATE::StateDriver::StateCtn::StateCtnDesc& GetDesc() const;

				GINL GAIA::BL Begin();
				GINL GAIA::BL End();
				GINL GAIA::BL IsBegin() const;

				GINL State* Fire(const GAIA::STATE::StateDriver::StateCtn::State::Condition::ConditionKey& key);

				GINL GAIA::BL SetCurrentState(GAIA::STATE::StateDriver::StateCtn::State* pState) const;
				GINL GAIA::STATE::StateDriver::StateCtn::State* GetCurrentState() const;

			private:
				GINL GAIA::GVOID init()
				{
					m_pCurrentState = GNIL;
				}

			private:
				GAIA::STATE::StateDriver::StateCtn::State* m_pCurrentState;
			};

		public:
			GINL StateDriver(){this->init();}
			GINL ~StateDriver(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{}

			virtual GAIA::BL Update()
			{
				return GAIA::True;
			}

		private:
			GINL GAIA::GVOID init(){}

		private:

		};
	};
};

#endif