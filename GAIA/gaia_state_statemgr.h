#ifndef		__GAIA_STATE_H__
#define		__GAIA_STATE_H__

namespace GAIA
{
	namespace STATE
	{
		class State : public virtual GAIA::FWORK::Instance
		{
		public:
			class StateDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					pCtn = GNIL;
				}
				virtual GAIA::BL check() const
				{
					if(pCtn == GNIL)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::STATE::StateCtn* pCtn;
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
			GINL ~State(){this->Destroy();}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_STATE_STATE;}

			GINL GAIA::BL Create(const GAIA::STATE::State::StateDesc& desc)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
			}
			GINL const StateDesc& GetDesc() const
			{
				return m_desc;
			}
			GINL GAIA::SIZE InsertEnterCondition(const GAIA::SIZE& index, const GAIA::STATE::State::Condition& cond)
			{
				return GINVALID;
			}
			GINL GAIA::BL DeleteEnterCondition(const GAIA::SIZE& index)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID DeleteEnterConditionAll()
			{
			}
			GINL GAIA::SIZE GetEnterConditionCount() const
			{
				return GINVALID;
			}
			GINL GAIA::STATE::State::Condition* GetEnterCondition(const GAIA::SIZE& index) const
			{
				return GNIL;
			}
			GINL GAIA::SIZE InsertLeaveCondition(const GAIA::SIZE& index, const GAIA::STATE::State::Condition& cond)
			{
				return GINVALID;
			}
			GINL GAIA::BL DeleteLeaveCondition(const GAIA::SIZE& index)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID DeleteLeaveConditionAll()
			{
			}
			GINL GAIA::SIZE GetLeaveConditionCount() const
			{
				return GINVALID;
			}
			GINL GAIA::STATE::State::Condition* GetLeaveCondition(const GAIA::SIZE& index) const
			{
				return GNIL;
			}
			virtual GAIA::BL EnterState()
			{
				return GAIA::True;
			}
			virtual GAIA::BL LeaveState()
			{
				return GAIA::True;
			}
			virtual GAIA::BL UpdateState()
			{
				return GAIA::True;
			}

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
			}

		private:
			GAIA::STATE::State::StateDesc m_desc;
		};

		class StateCtn : public virtual GAIA::FWORK::Instance
		{
		public:
			class StateCtnDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					pMgr = GNIL;
				}
				virtual GAIA::BL check() const
				{
					if(pMgr == GNIL)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::STATE::StateMgr* pMgr;
			};

		public:
			GINL StateCtn(){this->init();}
			GINL ~StateCtn(){this->Destroy();}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_STATE_STATECTN;}

			GINL GAIA::BL Create(const GAIA::STATE::StateCtn::StateCtnDesc& desc)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
			}
			GINL const GAIA::STATE::StateCtn::StateCtnDesc& GetDesc() const
			{
				return m_desc;
			}

			GINL GAIA::BL Begin()
			{
				if(this->IsBegin())
					return GAIA::False;
				m_bBegin = GAIA::True;
				return GAIA::True;
			}
			GINL GAIA::BL End()
			{
				if(!this->IsBegin())
					return GAIA::False;
				m_bBegin = GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
			GINL State* Fire(const GAIA::STATE::State::Condition::ConditionKey& key)
			{
				return GNIL;
			}
			GINL GAIA::BL SetCurrentState(GAIA::STATE::State* pState) const
			{
				return GAIA::True;
			}
			GINL GAIA::STATE::State* GetCurrentState() const
			{
				return GNIL;
			}

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_pCurrentState = GNIL;
				m_bBegin = GAIA::False;
			}

		private:
			GAIA::STATE::StateCtn::StateCtnDesc m_desc;
			GAIA::STATE::State* m_pCurrentState;
			GAIA::U8 m_bBegin : 1;
		};

		class StateMgr : public virtual GAIA::FWORK::Instance
		{
		public:
			class StateMgrDesc : public GAIA::FWORK::InstanceDesc
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
			GINL StateMgr(){this->init();}
			GINL ~StateMgr(){this->Destroy();}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_STATE_STATEMGR;}

			GINL GAIA::BL Create(const GAIA::STATE::StateMgr::StateMgrDesc& desc)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
			}
			GINL const GAIA::STATE::StateMgr::StateMgrDesc& GetDesc() const
			{
				return m_desc;
			}
			virtual GAIA::BL Update()
			{
				return GAIA::True;
			}

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
			}

		private:
			GAIA::STATE::StateMgr::StateMgrDesc m_desc;
		};
	};
};

#endif