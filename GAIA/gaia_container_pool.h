#ifndef 	__GAIA_CONTAINER_POOL_H__
#define 	__GAIA_CONTAINER_POOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, GAIA::UM _GroupElementSize> class Pool : public BasicPool<_DataType, GAIA::UM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::UM>, _GroupElementSize>{public:};
	};
};

#endif
