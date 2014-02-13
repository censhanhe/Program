#ifndef		__GAIA_CONTAINER_MAP_H__
#define		__GAIA_CONTAINER_MAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _KeyType> class Map : public BasicMap<_DataType, _KeyType, GAIA::NM, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>, 1000>{public:};
	};
};

#endif