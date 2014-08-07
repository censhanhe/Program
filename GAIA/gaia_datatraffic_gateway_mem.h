#ifndef		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_MEM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class GatewayMem : public Gateway
		{
		public:
			GatewayMem(){m_bBegin = GAIA::False;}
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::CLSID_GATEWAY_MEM;}
			virtual GAIA::BL Send(const GAIA::GVOID* p, const GAIA::U32& size)
			{
				return GAIA::True;
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const GAIA::GVOID* p, const GAIA::U32& size)
			{
				return GAIA::True;
			}
		protected:
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter){m_bBegin = GAIA::True; return GAIA::True;}
			virtual GAIA::BL End(){m_bBegin = GAIA::False; return GAIA::True;}
			virtual GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GAIA::BL m_bBegin;
		};
	};
};

#endif
