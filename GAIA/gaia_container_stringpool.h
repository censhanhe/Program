#ifndef 	__GAIA_CONTAINER_STRINGPOOL_H__
#define 	__GAIA_CONTAINER_STRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class StringPool : public GAIA::CONTAINER::BasicStringPool<_DataType, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
