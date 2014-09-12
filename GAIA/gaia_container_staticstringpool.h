#ifndef 	__GAIA_CONTAINER_STATICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_STATICSTRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class StaticStringPool : public GAIA::CONTAINER::BasicStaticStringPool<_DataType, GAIA::SIZE, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
