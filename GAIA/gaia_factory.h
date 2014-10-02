#ifndef		__GAIA_FRAMEWORK_FACTORY_H__
#define		__GAIA_FRAMEWORK_FACTORY_H__

namespace GAIA
{
	namespace FWORK
	{
		class FactoryCreateCallBack : public GAIA::Entity
		{
		public:
			GINL FactoryCreateCallBack(){}
			virtual Instance* Create(GAIA::FWORK::Factory* pFactory, const ClsID& cid) = 0;
		};
		class Factory : public Object
		{
		private: // Helper type declaration here for internal use.
			typedef GAIA::CTN::Vector<FactoryCreateCallBack*> LIST_CREATECALLBACK;
		public:
			GINL Factory(){this->init();}
			GINL ~Factory(){}
			GINL GAIA::BL RegistCreateCallBack(FactoryCreateCallBack* pCallBack)
			{
				if(m_listCreateCB.find(pCallBack, 0) != GINVALID)
					return GAIA::False;
				m_listCreateCB.push_back(pCallBack);
				return GAIA::True;
			}
			GINL GAIA::BL UnregistCreateCallBack(FactoryCreateCallBack* pCallBack)
			{
				GAIA_AST(!!pCallBack);
				if(pCallBack == GNIL)
					return GAIA::False;
				LIST_CREATECALLBACK::_sizetype t = m_listCreateCB.find(pCallBack, 0);
				if(t == GINVALID)
					return GAIA::False;
				m_listCreateCB.erase(t);
				return GAIA::True;
			}
			GINL GAIA::BL IsRegistedCreateCallBack(FactoryCreateCallBack* pCallBack) const
			{
				GAIA_AST(!!pCallBack);
				if(pCallBack == GNIL)
					return GAIA::False;
				if(m_listCreateCB.find(pCallBack, 0) == GINVALID)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL BeginRegistClsID()
			{
				if(this->IsBeginRegistClsID())
					return GAIA::False;
				GAIA_AST(m_PrepareRegClsIDSet.empty());
				__ClsIDListType::it it = m_RegClsIDList.front_it();
				for(; !it.empty(); ++it)
					m_PrepareRegClsIDSet.insert(*it);
				m_RegClsIDList.clear();
				m_bBeginRegClsID = GAIA::True;
				return GAIA::True;
			}
			GINL GAIA::BL EndRegistClsID()
			{
				if(!this->IsBeginRegistClsID())
					return GAIA::False;
				GAIA_AST(m_RegClsIDList.empty());
				__ClsIDSetType::it it = m_PrepareRegClsIDSet.front_it();
				for(; !it.empty(); ++it)
					m_RegClsIDList.push_back(*it);
				m_PrepareRegClsIDSet.clear();
				m_bBeginRegClsID = GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL IsBeginRegistClsID() const
			{
				return m_bBeginRegClsID;
			}
			GINL GAIA::BL RegistClsID(const GAIA::FWORK::ClsID& cid)
			{
				GAIA_AST(!cid.IsInvalid());
				if(cid.IsInvalid())
					return GAIA::False;
				if(this->IsRegistedClsID(cid))
					return GAIA::False;
				CLSIDNODE node;
				node.cid = cid;
				if(this->IsBeginRegistClsID())
				{
					if(!m_PrepareRegClsIDSet.insert(node))
					{
						GAIA_AST(GAIA::False);
						return GAIA::False;
					}
				}
				else
				{
					__ClsIDListType::it it = m_RegClsIDList.lower_bound(node);
					if(it.empty())
						m_RegClsIDList.push_back(node);
					else
					{
						if(!m_RegClsIDList.insert(node, it - m_RegClsIDList.front_it()))
						{
							GAIA_AST(GAIA::False);
							return GAIA::False;
						}
					}
				}
				return GAIA::True;
			}
			GINL GAIA::BL UnregistClsID(const GAIA::FWORK::ClsID& cid)
			{
				GAIA_AST(!cid.IsInvalid());
				if(cid.IsInvalid())
					return GAIA::False;
				if(!this->IsRegistedClsID(cid))
					return GAIA::False;
				CLSIDNODE node;
				node.cid = cid;
				if(this->IsBeginRegistClsID())
				{
					if(!m_PrepareRegClsIDSet.erase(node))
					{
						GAIA_AST(GAIA::False);
						return GAIA::False;
					}
				}
				else
				{
					__ClsIDListType::_sizetype index = m_RegClsIDList.search(node);
					GAIA_AST(index != GINVALID);
					if(!m_RegClsIDList.erase(index))
					{
						GAIA_AST(GAIA::False);
						return GAIA::False;
					}
				}
				return GAIA::True;
			}
			GINL GAIA::BL IsRegistedClsID(const GAIA::FWORK::ClsID& cid) const
			{
				CLSIDNODE finder;
				finder.cid = cid;
				if(this->IsBeginRegistClsID())
				{
					if(m_PrepareRegClsIDSet.find(finder) != GNIL)
						return GAIA::True;
				}
				else
				{
					if(m_RegClsIDList.search(finder) != GINVALID)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::GVOID CollectCreateCallBack(GAIA::CTN::Vector<FactoryCreateCallBack*>& listResult) const{listResult = m_listCreateCB;}
			GINL virtual Instance* CreateInstance(const ClsID& cid, GAIA::GVOID* pParameter);
			GINL virtual Instance* RequestInstance(const ClsID& cid, GAIA::GVOID* pParameter);
		public:
			class CLSIDNODE
			{
			public:
				GINL CLSIDNODE(){this->init();}
				GINL CLSIDNODE& operator = (const CLSIDNODE& src)
				{
					cid = src.cid;
					proc = src.proc;
					return *this;
				}
				GAIA_CLASS_OPERATOR_COMPARE(cid, cid, CLSIDNODE);
			private:
				GINL GAIA::GVOID init(){cid.Invalid(); proc = GNIL;}
			public:
				GAIA::FWORK::ClsID cid;
				GAIA::FWORK::INSTCREATOR::CREATE_INSTANCE_PROC proc;
			};
		private:
			GINL GAIA::GVOID init()
			{
				m_bBeginRegClsID = GAIA::False;

				this->BeginRegistClsID();
				{
					for(GAIA::SIZE x = 0; x < sizeofarray(GAIA::FWORK::CLSID_LIST); ++x)
					{
						if(!this->RegistClsID(GAIA::FWORK::CLSID_LIST[x]))
							GAIA_AST(GAIA::False);
					}
				}
				this->EndRegistClsID();

				this->GenerateCreator();
			}
			GINL GAIA::GVOID GenerateCreator();
			GINL virtual GAIA::GVOID CacheInstance(Instance* pInstance)
			{
				GAIA_AST(pInstance != GNIL);
			}
		private:
			typedef GAIA::CTN::Vector<CLSIDNODE> __ClsIDListType;
			typedef GAIA::CTN::Set<CLSIDNODE> __ClsIDSetType;
		private:
			LIST_CREATECALLBACK m_listCreateCB;
			__ClsIDListType m_RegClsIDList;
			__ClsIDSetType m_PrepareRegClsIDSet;
			GAIA::BL m_bBeginRegClsID;
		};
	};
};

#endif

