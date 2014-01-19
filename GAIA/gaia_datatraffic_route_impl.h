#ifndef		__GAIA_DATATRAFFIC_ROUTE_IMPL_H__
#define		__GAIA_DATATRAFFIC_ROUTE_IMPL_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		GINL GAIA::BL Route::Connect(Route* pRoute)
		{
			GAIA_ASSERT(pRoute != GNULL);
			pRoute->Reference();
			m_routes.insert(pRoute);
			return GAIA::True;
		}
		GINL GAIA::BL Route::Disconnect(Route* pRoute)
		{
			GAIA_ASSERT(pRoute != GNULL);
			pRoute->Release();
			return m_routes.erase(pRoute);
		}
		GINL GAIA::GVOID Route::DisconnectAll()
		{
			for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
			{
				if(m_routes[x] != GNULL)
					m_routes[x]->Release();
			}
			m_routes.destroy();
		}
		GINL GAIA::BL Route::IsConnected(Route* pRoute) const
		{
			GAIA_ASSERT(pRoute != GNULL);
			if(m_routes.find(pRoute) == 0)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Route::CollectConnections(GAIA::CONTAINER::Vector<Route*>& listResult) const
		{
			GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>::_sizetype oldsize = listResult.size();
			for(OL_ROUTE::_sizetype x = 0; x < m_routes.size(); ++x)
			{
				Route* pRoute = m_routes[x];
				if(pRoute != GNULL)
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
			GAIA_ASSERT(pGateway != GNULL);
			pGateway->Reference();
			m_gateways.insert(pGateway);
			return GAIA::True;
		}
		GINL GAIA::BL Route::RemoveGateway(Gateway* pGateway)
		{
			GAIA_ASSERT(pGateway != GNULL);
			pGateway->Release();
			return m_gateways.erase(pGateway);
		}
		GINL GAIA::GVOID Route::RemoveGatewayAll()
		{
			for(OL_GATEWAY::_sizetype x = 0; x < m_gateways.size(); ++x)
			{
				if(m_gateways[x] != GNULL)
					m_gateways[x]->Release();
			}
			m_gateways.destroy();
		}
		GINL GAIA::BL Route::IsExistGateway(Gateway* pGateway) const
		{
			GAIA_ASSERT(pGateway != GNULL);
			if(m_gateways.find(pGateway) == 0)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Route::CollectGateways(GAIA::CONTAINER::Vector<Gateway*>& listResult) const
		{
			GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Gateway*>::_sizetype oldsize = listResult.size();
			for(OL_ROUTE::_sizetype x = 0; x < m_gateways.size(); ++x)
			{
				Gateway* pGateway = m_gateways[x];
				if(pGateway != GNULL)
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