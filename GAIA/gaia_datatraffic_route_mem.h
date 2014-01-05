#ifndef		__GAIA_DATATRAFFIC_ROUTE_MEM_H__
#define		__GAIA_DATATRAFFIC_ROUTE_MEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class RouteMem : public Route
		{
		public:
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_ROUTE_MEM;}
		};
	};
};

#endif