#ifndef		__GAIA_DATATRAFFIC_ROUTE_MEM_H__
#define		__GAIA_DATATRAFFIC_ROUTE_MEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class RouteMem : public virtual Route
		{
		public:
			RouteMem(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_ROUTE_MEM;}
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::U32& size)
			{
				return GAIA::True;
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::U32& size)
			{
				return GAIA::True;
			}
		};
	};
};

#endif
