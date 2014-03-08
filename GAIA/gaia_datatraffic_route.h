#ifndef		__GAIA_DATATRAFFIC_ROUTE_H__
#define		__GAIA_DATATRAFFIC_ROUTE_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Route : public GAIA::FRAMEWORK::Instance
		{
		private:
			typedef GAIA::CONTAINER::Orderless<Route*> OL_ROUTE;
			typedef GAIA::CONTAINER::Orderless<Gateway*> OL_GATEWAY;
		public:
			GINL ~Route(){this->DisconnectAll(); this->RemoveGatewayAll();}
			GINL virtual GAIA::BL Connect(Route* pRoute); // Single direction connection.
			GINL virtual GAIA::BL Disconnect(Route* pRoute);
			GINL virtual GAIA::GVOID DisconnectAll();
			GINL virtual GAIA::BL IsConnected(Route* pRoute) const;
			GINL virtual GAIA::BL CollectConnections(GAIA::CONTAINER::Vector<Route*>& listResult) const;
			GINL virtual GAIA::BL AddGateway(Gateway* pGateway); // Single direction connection.
			GINL virtual GAIA::BL RemoveGateway(Gateway* pGateway);
			GINL virtual GAIA::GVOID RemoveGatewayAll();
			GINL virtual GAIA::BL IsExistGateway(Gateway* pGateway) const;
			GINL virtual GAIA::BL CollectGateways(GAIA::CONTAINER::Vector<Gateway*>& listResult) const;
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::UM& size) = 0;
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::UM& size) = 0;
		private:
			OL_ROUTE m_routes;
			OL_GATEWAY m_gateways;
		};
	};
};

#endif