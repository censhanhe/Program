#ifndef		__GAIA_CONTAINER_ORDERLESS_H__
#define		__GAIA_CONTAINER_ORDERLESS_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Orderless : public BasicOrderless<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
