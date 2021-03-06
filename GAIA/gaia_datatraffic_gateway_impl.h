#ifndef		__GAIA_DATATRAFFIC_GATEWAY_IMPL_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_IMPL_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		GINL GAIA::BL Gateway::AddRoute(Route* pRoute)
		{
			GAIA_AST(!!pRoute);
			pRoute->Reference();
			m_routes.insert(pRoute);
			return GAIA::True;
		}
		GINL GAIA::BL Gateway::RemoveRoute(Route* pRoute)
		{
			GAIA_AST(!!pRoute);
			pRoute->Release();
			return m_routes.erase(pRoute);
		}
		GINL GAIA::GVOID Gateway::RemoveRouteAll()
		{
			for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
			{
				if(m_routes[x] != GNIL)
					m_routes[x]->Release();
			}
			m_routes.destroy();
		}
		GINL GAIA::BL Gateway::IsExistRoute(Route* pRoute) const
		{
			GAIA_AST(!!pRoute);
			if(m_routes.find(pRoute) == 0)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Gateway::CollectRoutes(GAIA::CTN::Vector<Route*>& listResult) const
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
	};
};

#endif
