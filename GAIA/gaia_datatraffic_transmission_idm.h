#ifndef		__GAIA_DATATRAFFIC_TRANSMISSION_IDM_H__
#define		__GAIA_DATATRAFFIC_TRANSMISSION_IDM_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class TransmissionIDM : public virtual Transmission // IDM means immediately-data-mode.
		{
		public:
			GINL TransmissionIDM(){}
			GINL ~TransmissionIDM(){}
			GINL virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_TRANSMISSION_IDM;}
			virtual GAIA::GVOID WorkProcedure(){}
		};
	};
};

#endif
