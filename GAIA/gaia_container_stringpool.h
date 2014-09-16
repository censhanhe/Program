#ifndef 	__GAIA_CONTAINER_STRINGPOOL_H__
#define 	__GAIA_CONTAINER_STRINGPOOL_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class StringPool : public GAIA::CTN::BasicStringPool<_DataType, GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
