#ifndef		__GAIA_DATATRAFFIC_GATEWAY_FILE_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_FILE_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayFile : public Gateway
		{
		public:
			GINL GatewayFile(){m_bBegin = GAIA::False;}
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_GATEWAY_FILE;}
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::UM& size)
			{
				return GAIA::True;
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::UM& size)
			{
				return GAIA::True;
			}
		protected:
			virtual GAIA::BL Begin(){m_bBegin = GAIA::True; return GAIA::True;}
			virtual GAIA::BL End(){m_bBegin = GAIA::False; return GAIA::True;}
			virtual GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GAIA::BL m_bBegin;
		};
	};
};

#endif