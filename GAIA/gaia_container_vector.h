#ifndef		__GAIA_CONTAINER_VECTOR_H__
#define		__GAIA_CONTAINER_VECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Vector : public BasicVector<_DataType, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
