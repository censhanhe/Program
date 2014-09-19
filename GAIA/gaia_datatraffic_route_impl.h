#ifndef		__GAIA_DATATRAFFIC_ROUTE_IMPL_H__
#define		__GAIA_DATATRAFFIC_ROUTE_IMPL_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		GINL GAIA::BL Route::Connect(Route* pRoute)
		{
			GAIA_AST(!!pRoute);
			pRoute->Reference();
			m_routes.insert(pRoute);
			return GAIA::True;
		}
		GINL GAIA::BL Route::Disconnect(Route* pRoute)
		{
			GAIA_AST(!!pRoute);
			pRoute->Release();
			return m_routes.erase(pRoute);
		}
		GINL GAIA::GVOID Route::DisconnectAll()
		{
			for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
			{
				if(m_routes[x] != GNIL)
					m_routes[x]->Release();
			}
			m_routes.destroy();
		}
		GINL GAIA::BL Route::IsConnected(Route* pRoute) const
		{
			GAIA_AST(!!pRoute);
			if(m_routes.find(pRoute) == 0)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Route::CollectConnections(GAIA::CTN::Vector<Route*>& listResult) const
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
		GINL GAIA::BL Route::AddGateway(Gateway* pGateway)
		{
			GAIA_AST(!!pGateway);
			pGateway->Reference();
			m_gateways.insert(pGateway);
			return GAIA::True;
		}
		GINL GAIA::BL Route::RemoveGateway(Gateway* pGateway)
		{
			GAIA_AST(!!pGateway);
			pGateway->Release();
			return m_gateways.erase(pGateway);
		}
		GINL GAIA::GVOID Route::RemoveGatewayAll()
		{
			for(OL_GATEWAY::_sizetype x = 0; x < m_gateways.size(); ++x)
			{
				if(m_gateways[x] != GNIL)
					m_gateways[x]->Release();
			}
			m_gateways.destroy();
		}
		GINL GAIA::BL Route::IsExistGateway(Gateway* pGateway) const
		{
			GAIA_AST(!!pGateway);
			if(m_gateways.find(pGateway) == 0)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Route::CollectGateways(GAIA::CTN::Vector<Gateway*>& listResult) const
		{
			GAIA::CTN::Vector<GAIA::DATATRAFFIC::Gateway*>::_sizetype oldsize = listResult.size();
			for(OL_ROUTE::_sizetype x = 0; x < m_gateways.size(); ++x)
			{
				Gateway* pGateway = m_gateways[x];
				if(pGateway != GNIL)
				{
					pGateway->Reference();
					listResult.push_back(pGateway);
				}
			}
			if(listResult.size() == oldsize)
				return GAIA::False;
			return GAIA::True;
		}
	};
};

#endif
