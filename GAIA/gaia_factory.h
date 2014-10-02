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
			GINL Factory(){}
			GINL ~Factory(){}
			GINL GAIA::BL RegistCreateCallBack(FactoryCreateCallBack* pCallBack)
			{
				if(m_listCreateCB.find(pCallBack, 0) != (LIST_CREATECALLBACK::_sizetype)-1)
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
				if(t == (LIST_CREATECALLBACK::_sizetype)-1)
					return GAIA::False;
				m_listCreateCB.erase(t);
				return GAIA::True;
			}
			GINL GAIA::BL IsRegistedCreateCallBack(FactoryCreateCallBack* pCallBack) const
			{
				GAIA_AST(!!pCallBack);
				if(pCallBack == GNIL)
					return GAIA::False;
				if(m_listCreateCB.find(pCallBack, 0) == (LIST_CREATECALLBACK::_sizetype)-1)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID CollectCreateCallBack(GAIA::CTN::Vector<FactoryCreateCallBack*>& listResult) const{listResult = m_listCreateCB;}
			GINL virtual Instance* CreateInstance(const ClsID& cid, GAIA::GVOID* pParameter);
			GINL virtual Instance* RequestInstance(const ClsID& cid, GAIA::GVOID* pParameter);
		private:
			GINL virtual GAIA::GVOID CacheInstance(Instance* pInstance)
			{
			}
		private:
			LIST_CREATECALLBACK m_listCreateCB;
		};
	};
};

#endif

