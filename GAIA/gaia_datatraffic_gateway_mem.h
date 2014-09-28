#ifndef		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayMem : public virtual Gateway
		{
		public:
			GatewayMem(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_GATEWAY_MEM;}
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
