#ifndef		__GAIA_MVC_VIEW_H__
#define		__GAIA_MVC_VIEW_H__

namespace GAIA
{
	namespace MVC
	{
		class View : public virtual GAIA::FRAMEWORK::Instance
		{
		private:
			class ModelNode
			{
			public:
				GAIA::CONTAINER::TString strName;
				GAIA::MVC::Model* pModel;
			};
			class ControllerNode
			{
			public:
				GAIA::CONTAINER::TString strName;
				GAIA::MVC::Controller* pController;
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
			GINL GAIA::BL SetModel(const GAIA::TCH* pszName, GAIA::MVC::Model* pModel)
			{
				GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);
				pModel->Reference();
				ModelNode* pNode = this->GetModelByName(pszName);
				if(pNode != GNULL)
				{
					pNode->pModel->Release();
					pNode->pModel = pModel;
					return GAIA::True;
				}
				__ModelListType::it it = m_models.front_it();
				while(!it.empty())
				{
					ModelNode& n = *it;
					if(n.pModel == GNULL)
					{
						GAIA_AST(n.strName.empty());
						n.pModel = pModel;
						return GAIA::True;
					}
					GAIA_AST(!n.strName.empty());
					++it;
				}
				ModelNode n;
				m_models.push_back(n);
				m_models.back().strName = pszName;
				m_models.back().pModel = pModel;
				return GAIA::True;
			}
			GINL GAIA::MVC::Model* GetModel(const GAIA::TCH* pszName) const
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
			GINL GAIA::BL SetController(const GAIA::TCH* pszName, GAIA::MVC::Controller* pController)
			{
				GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);
				pController->Reference();
				ControllerNode* pNode = this->GetControllerByName(pszName);
				if(pNode != GNULL)
				{
					pNode->pController->Release();
					pNode->pController = pController;
					return GAIA::True;
				}
				__ControllerListType::it it = m_controllers.front_it();
				while(!it.empty())
				{
					ControllerNode& n = *it;
					if(n.pController == GNULL)
					{
						GAIA_AST(n.strName.empty());
						n.pController = pController;
						return GAIA::True;
					}
					GAIA_AST(!n.strName.empty());
					++it;
				}
				ControllerNode n;
				m_controllers.push_back(n);
				m_controllers.back().strName = pszName;
				m_controllers.back().pController = pController;
				return GAIA::True;
			}
			GINL GAIA::MVC::Controller* GetController(const GAIA::TCH* pszName) const
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
			GINL const ModelNode* GetModelByName(const GAIA::TCH* pszName) const{return const_cast<GAIA::MVC::View*>(this)->GetModelByName(pszName);}
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
			GINL const ControllerNode* GetControllerByName(const GAIA::TCH* pszName) const{return const_cast<GAIA::MVC::View*>(this)->GetControllerByName(pszName);}
		private:
			__ModelListType m_models;
			__ControllerListType m_controllers;
		};
	};
};

#endif