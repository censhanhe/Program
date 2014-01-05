#ifndef		__GAIA_DATATRAFFIC_ROUTE_NET_H__
#define		__GAIA_DATATRAFFIC_ROUTE_NET_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class RouteNet : public Route
		{
		public:
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_ROUTE_NET;}
		};
	};
};

#endif