#ifndef 	__GAIA_CONTAINER_STATICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_STATICSTRINGPOOL_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class StaticStringPool : public GAIA::CTN::BasicStaticStringPool<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
