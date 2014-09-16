#ifndef 	__GAIA_CONTAINER_POOL_H__
#define 	__GAIA_CONTAINER_POOL_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Pool : public BasicPool<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
