#ifndef		__GAIA_CONTAINER_LIST_H__
#define		__GAIA_CONTAINER_LIST_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class List : public BasicList<_DataType, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> >{public:};
	}
};

#endif
