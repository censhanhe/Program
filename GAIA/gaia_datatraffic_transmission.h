#ifndef		__GAIA_DATATRAFFIC_TRANSMISSION_H__
#define		__GAIA_DATATRAFFIC_TRANSMISSION_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Transmission : public GAIA::FRAMEWORK::Instance, public GAIA::THREAD::Thread
		{
		private:
			typedef GAIA::CONTAINER::Orderless<Route*, GNULL> OL_ROUTE;
		public:
			GINL virtual GAIA::BL RegistRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_ASSERT(pRoute != NULL);
				pRoute->Reference();
				m_routes.insert(pRoute);
				return GAIA::True;
			}
			GINL virtual GAIA::BL UnregistRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_ASSERT(pRoute != NULL);
				pRoute->Release();
				return m_routes.remove(pRoute);
			}
			GINL virtual GAIA::BL IsRegistedRoute(GAIA::DATATRAFFIC::Route* pRoute) const
			{
				GAIA_ASSERT(pRoute != NULL);
				if(m_routes.find(pRoute) == 0)
					return GAIA::False;
				return GAIA::True;
			}
			GINL virtual GAIA::BL CollectRegistedRoutes(GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>& listResult) const
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
		private:
			OL_ROUTE m_routes;
		};
	};
};

#endif