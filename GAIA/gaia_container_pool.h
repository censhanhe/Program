#ifndef 	__GAIA_CONTAINER_POOL_H__
#define 	__GAIA_CONTAINER_POOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Pool : public BasicPool<_DataType, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> >{public:};
	};
};

#endif
