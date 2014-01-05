#ifndef		__GAIA_DATATRAFFIC_GATEWAY_H__
#define		__GAIA_DATATRAFFIC_GATEWAY_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Gateway : public GAIA::FRAMEWORK::Instance
		{
		public:
			virtual GAIA::BL Push(const GAIA::GVOID* p, const GAIA::UM& size) = 0;

		protected: // Interface for derived class callback.
			virtual GAIA::BL Pop(const GAIA::GVOID* p, const GAIA::UM& size) = 0;
		};
	};
};

#endif