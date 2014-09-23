#ifndef		__GAIA_DATATRAFFIC_TRANSMISSION_H__
#define		__GAIA_DATATRAFFIC_TRANSMISSION_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Transmission : public virtual GAIA::FWORK::Instance, public virtual GAIA::THREAD::Thread
		{
		private:
			typedef GAIA::CTN::Orderless<Route*> OL_ROUTE;
		public:
			GINL ~Transmission(){this->RemoveRouteAll();}
			GINL virtual GAIA::BL AddRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_AST(!!pRoute);
				pRoute->Reference();
				m_routes.insert(pRoute);
				return GAIA::True;
			}
			GINL virtual GAIA::BL RemoveRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_AST(!!pRoute);
				pRoute->Release();
				return m_routes.erase(pRoute);
			}
			GINL virtual GAIA::GVOID RemoveRouteAll()
			{
				for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
				{
					if(m_routes[x] != GNIL)
						m_routes[x]->Release();
				}
				m_routes.destroy();
			}
			GINL virtual GAIA::BL IsExistRoute(GAIA::DATATRAFFIC::Route* pRoute) const
			{
				GAIA_AST(!!pRoute);
				if(m_routes.find(pRoute) == 0)
					return GAIA::False;
				return GAIA::True;
			}
			GINL virtual GAIA::BL CollectRegistedRoutes(GAIA::CTN::Vector<GAIA::DATATRAFFIC::Route*>& listResult) const
			{
				GAIA::CTN::Vector<GAIA::DATATRAFFIC::Route*>::_sizetype oldsize = listResult.size();
				for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
				{
					Route* pRoute = m_routes[x];
					if(pRoute != GNIL)
					{
						pRoute->Reference();
						listResult.push_back(pRoute);
					}
				}
				if(listResult.size() == oldsize)
					return GAIA::False;
				return GAIA::True;
			}
		private:
			OL_ROUTE m_routes;
		};
	};
};

#endif
