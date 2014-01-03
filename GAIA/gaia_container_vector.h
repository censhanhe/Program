#ifndef		__GAIA_CONTAINER_VECTOR_H__
#define		__GAIA_CONTAINER_VECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType> class Vector : public BasicVector<_DataType, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<U32>>
		{
		public:
			GINL Vector(){}
			GINL ~Vector(){}
		};
	};
};

#endif