#ifndef		__GAIA_DATATRAFFIC_ROUTE_H__
#define		__GAIA_DATATRAFFIC_ROUTE_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Route : public GAIA::FRAMEWORK::Instance
		{
		public:
			virtual GAIA::BL Connect(Route* pRoute) = 0;
			virtual GAIA::BL Disconnect(Route* pRoute) const = 0;
			virtual GAIA::BL IsConnected(Route* pRoute) const = 0;
			virtual GAIA::BL CollectConnections(GAIA::CONTAINER::Vector<Route*>& listResult) const = 0;

			virtual GAIA::BL AddGateway(Gateway* pGateway) = 0;
			virtual GAIA::BL RemoveGateway(Gateway* pGateway) = 0;
			virtual GAIA::BL IsExistGateway(Gateway* pGateway) const = 0;
			virtual GAIA::BL CollectGateways(GAIA::CONTAINER::Vector<Gateway*>& listResult) const = 0;

			virtual GAIA::BL Push(const GAIA::GVOID* p, const GAIA::UM& size) = 0;

		protected: // Interface for derived class callback.
			virtual GAIA::BL Pop(const GAIA::GVOID* p, const GAIA::UM& size) = 0;

		private: // Interface for ITransmission call.

		};
	};
};

#endif