#ifndef		__GAIA_CONTAINER_MAP_H__
#define		__GAIA_CONTAINER_MAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _KeyType> class Map : public BasicMap<_DataType, _KeyType, GAIA::SIZE, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
