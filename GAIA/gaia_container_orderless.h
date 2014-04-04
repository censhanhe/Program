#ifndef		__GAIA_CONTAINER_ORDERLESS_H__
#define		__GAIA_CONTAINER_ORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Orderless : public BasicOrderless<_DataType, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif