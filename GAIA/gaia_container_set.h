#ifndef 	__GAIA_CONTAINER_SET_H__
#define 	__GAIA_CONTAINER_SET_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Set : public BasicSet<_DataType, GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
