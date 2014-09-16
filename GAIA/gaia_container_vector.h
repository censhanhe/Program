#ifndef		__GAIA_CONTAINER_VECTOR_H__
#define		__GAIA_CONTAINER_VECTOR_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Vector : public BasicVector<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
