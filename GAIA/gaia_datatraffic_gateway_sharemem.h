#ifndef		__GAIA_DATATRAFFIC_GATEWAY_SHAREMEM_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_SHAREMEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayShareMem : public virtual Gateway
		{
		public:
			GatewayShareMem(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_DATATRAFFIC_GATEWAYSHAREMEM;}
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
