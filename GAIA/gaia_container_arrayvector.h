#ifndef		__GAIA_CONTAINER_ARRAYVECTOR_H__
#define		__GAIA_CONTAINER_ARRAYVECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, GAIA::SIZE _Size> class ArrayVector : public BasicArrayVector<_DataType, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE>, _Size>{public:};
	};
};

#endif