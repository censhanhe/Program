#ifndef		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayMem : public Gateway
		{
		public:
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_GATEWAY_MEM;}
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::UM& size)
			{
				return GAIA::True;
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::UM& size)
			{
				return GAIA::True;
			}
		};
	};
};

#endif