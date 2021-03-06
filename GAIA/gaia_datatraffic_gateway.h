#ifndef		__GAIA_DATATRAFFIC_GATEWAY_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Gateway : public virtual GAIA::FWORK::Instance
		{
		private:
			typedef GAIA::CTN::Orderless<Route*> OL_ROUTE;
		public:
			GINL ~Gateway(){this->RemoveRouteAll();}
			GINL virtual GAIA::BL AddRoute(Route* pRoute); // Single direction connection.
			GINL virtual GAIA::BL RemoveRoute(Route* pRoute);
			GINL virtual GAIA::GVOID RemoveRouteAll();
			GINL virtual GAIA::BL IsExistRoute(Route* pRoute) const;
			GINL virtual GAIA::BL CollectRoutes(GAIA::CTN::Vector<Route*>& listResult) const;
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::U32& size) = 0;
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::U32& size) = 0;
		private:
			OL_ROUTE m_routes;
		};
	};
};

#endif
