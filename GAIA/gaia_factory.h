#ifndef		__GAIA_FRAMEWORK_FACTORY_H__
#define		__GAIA_FRAMEWORK_FACTORY_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class Factory;
		class FactoryCreateCallBack : public GAIA::Entity
		{
		public:
			GINL FactoryCreateCallBack(){}
			virtual Instance* Create(GAIA::FRAMEWORK::Factory* pFactory, const ClsID& cid) = 0;
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
			GINL virtual Instance* CreateInstance(const ClsID& cid, GAIA::GVOID* pParameter)
			{
				if(cid.IsInvalid())
					return GNIL;
				Instance* pRet = GNIL;
				if(GAIA::ALWAYSFALSE){}
				else if(cid == GAIA::FRAMEWORK::CLSID_GATEWAY_MEM)
					pRet = new GAIA::DATATRAFFIC::GatewayMem;
				else if(cid == GAIA::FRAMEWORK::CLSID_GATEWAY_SHAREMEM)
					pRet = new GAIA::DATATRAFFIC::GatewayShareMem;
				else if(cid == GAIA::FRAMEWORK::CLSID_GATEWAY_FILE)
					pRet = new GAIA::DATATRAFFIC::GatewayFile;
				else if(cid == GAIA::FRAMEWORK::CLSID_ROUTE_MEM)
					pRet = new GAIA::DATATRAFFIC::RouteMem;
				else if(cid == GAIA::FRAMEWORK::CLSID_ROUTE_NET)
					pRet = new GAIA::DATATRAFFIC::RouteNet;
				else if(cid == GAIA::FRAMEWORK::CLSID_TRANSMISSION_IDM)
					pRet = new GAIA::DATATRAFFIC::TransmissionIDM;
				else if(cid == GAIA::FRAMEWORK::CLSID_FILEIO)
					pRet = new GAIA::IO::FileIO;
				else if(cid == GAIA::FRAMEWORK::CLSID_MEMIO)
					pRet = new GAIA::IO::MemIO;
				else if(cid == GAIA::FRAMEWORK::CLSID_SCREENIO)
					pRet = new GAIA::IO::ScreenIO;
				else if(cid == GAIA::FRAMEWORK::CLSID_SERIALIZER)
					pRet = new GAIA::SERIALIZER::Serializer;
				else if(cid == GAIA::FRAMEWORK::CLSID_CANVAS)
					pRet = new GAIA::UI::Canvas;
				if(pRet == GNIL)
				{
					for(LIST_CREATECALLBACK::_sizetype x = 0; x < m_listCreateCB.size(); ++x)
					{
						FactoryCreateCallBack* pCallBack = m_listCreateCB[x];
						pRet = pCallBack->Create(this, cid);
						if(pRet != GNIL)
							break;
					}
				}
				if(pRet != GNIL)
				{
					if(!pRet->Begin(pParameter))
					{
						pRet->Release();
						pRet = GNIL;
					}
				}
				return pRet;
			}
			GINL virtual Instance* RequestInstance(const ClsID& cid, GAIA::GVOID* pParameter)
			{
				return GNIL;
			}
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

