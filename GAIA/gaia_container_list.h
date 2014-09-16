#ifndef		__GAIA_CONTAINER_LIST_H__
#define		__GAIA_CONTAINER_LIST_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class List : public BasicList<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	}
};

#endif
