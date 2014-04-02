#ifndef 	__GAIA_CONTAINER_SET_H__
#define 	__GAIA_CONTAINER_SET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Set : public BasicSet<_DataType, GAIA::NM, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> >{public:};
	};
};

#endif
