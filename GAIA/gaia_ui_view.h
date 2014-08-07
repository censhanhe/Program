#ifndef		__GAIA_UI_VIEW_H__
#define		__GAIA_UI_VIEW_H__

namespace GAIA
{
	namespace UI
	{
		class View : public GAIA::FRAMEWORK::Instance
		{
		private:
			class ModelNode
			{
			public:
				GAIA::CONTAINER::TString strName;
				GAIA::MODEL::Model* pModel;
			};
			class ControllerNode
			{
			public:
				GAIA::CONTAINER::TString strName;
				GAIA::CONTROLLER::Controller* pController;
			};
		public:
			typedef GAIA::CONTAINER::Vector<ModelNode> __ModelListType;
			typedef GAIA::CONTAINER::Vector<ControllerNode> __ControllerListType;
		public:
			GINL View(){this->init();}
			GINL ~View()
			{
				this->DeleteControllerAll();
				this->DeleteModelAll();
			}
			GINL GAIA::BL SetModel(const GAIA::TCH* pszName, GAIA::MODEL::Model* pModel)
			{
				GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);
				pModel->Reference();
				ModelNode* pNode = this->GetModelByName(pszName);
				if(pNode == GNULL)
				{
					ModelNode n;
					m_models.push_back(n);
					pNode = &m_models.back();
					pNode->strName = pszName;
				}
				pNode->pModel = pModel;
				return GAIA::True;
			}
			GINL GAIA::MODEL::Model* GetModel(const GAIA::TCH* pszName) const
			{
				GPCHR_NULLSTRPTR_RET(pszName, GNULL);
				const ModelNode* pNode = this->GetModelByName(pszName);
				if(pNode == GNULL)
					return GNULL;
				pNode->pModel->Reference();
				return pNode->pModel;
			}
			GINL GAIA::GVOID DeleteModelAll()
			{
				__ModelListType::it it = m_models.front_it();
				while(!it.empty())
				{
					ModelNode& n = *it;
					if(n.pModel == GNULL)
					{
						GAIA_AST(n.strName.empty());
						continue;
					}
					GAIA_AST(!n.strName.empty());
					n.pModel->Release();
					n.pModel = GNULL;
					n.strName.destroy();
					++it;
				}
				m_models.destroy();
			}
			GINL GAIA::BL SetController(const GAIA::TCH* pszName, GAIA::CONTROLLER::Controller* pController)
			{
				GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);
				pController->Reference();
				ControllerNode* pNode = this->GetControllerByName(pszName);
				if(pNode == GNULL)
				{
					ControllerNode n;
					m_controllers.push_back(n);
					pNode = &m_controllers.back();
					pNode->strName = pszName;
				}
				pNode->pController = pController;
				return GAIA::True;
			}
			GINL GAIA::CONTROLLER::Controller* GetController(const GAIA::TCH* pszName) const
			{
				GPCHR_NULLSTRPTR_RET(pszName, GNULL);
				const ControllerNode* pNode = this->GetControllerByName(pszName);
				if(pNode == GNULL)
					return GNULL;
				pNode->pController->Reference();
				return pNode->pController;
			}
			GINL GAIA::GVOID DeleteControllerAll()
			{
				__ControllerListType::it it = m_controllers.front_it();
				while(!it.empty())
				{
					ControllerNode& n = *it;
					if(n.pController == GNULL)
					{
						GAIA_AST(n.strName.empty());
						continue;
					}
					GAIA_AST(!n.strName.empty());
					n.pController->Release();
					n.pController = GNULL;
					n.strName.destroy();
					++it;
				}
				m_controllers.destroy();
			}
		public:
			virtual GINL GAIA::BL Create() = 0;
			virtual GINL GAIA::BL Destroy() = 0;
			virtual GINL GAIA::BL IsCreated() const = 0;
		private:
			GINL GAIA::GVOID init(){}
			GINL ModelNode* GetModelByName(const GAIA::TCH* pszName)
			{
				__ModelListType::it it  = m_models.front_it();
				while(!it.empty())
				{
					ModelNode& n = (*it);
					if(n.strName == pszName)
						return &n;
					++it;
				}
				return GNULL;
			}
			GINL const ModelNode* GetModelByName(const GAIA::TCH* pszName) const{return const_cast<GAIA::UI::View*>(this)->GetModelByName(pszName);}
			GINL ControllerNode* GetControllerByName(const GAIA::TCH* pszName)
			{
				__ControllerListType::it it = m_controllers.front_it();
				while(!it.empty())
				{
					ControllerNode& n = (*it);
					if(n.strName == pszName)
						return &n;
					++it;
				}
				return GNULL;
			}
			GINL const ControllerNode* GetControllerByName(const GAIA::TCH* pszName) const{return const_cast<GAIA::UI::View*>(this)->GetControllerByName(pszName);}
		private:
			__ModelListType m_models;
			__ControllerListType m_controllers;
		};
	};
};

#endif