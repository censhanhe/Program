#ifndef		__GAIA_DATATRAFFIC_GATEWAY_FILE_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_FILE_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayFile : public virtual Gateway
		{
		public:
			GINL GatewayFile(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_DATATRAFFIC_GATEWAYFILE;}
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
