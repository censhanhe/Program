#ifndef		__GAIA_DATATRAFFIC_TRANSMISSION_IDM_H__
#define		__GAIA_DATATRAFFIC_TRANSMISSION_IDM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class TransmissionIDM : public virtual Transmission // IDM means immediately-data-mode.
		{
		public:
			GINL TransmissionIDM(){m_bBegin = GAIA::False;}
			GINL ~TransmissionIDM(){}
			GINL virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_TRANSMISSION_IDM;}
			virtual GAIA::GVOID WorkProcedure(){}
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
