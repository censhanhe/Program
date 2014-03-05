#ifndef		__GAIA_CONTAINER_ORDERLESS_H__
#define		__GAIA_CONTAINER_ORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, _DataType _DefaultValue> class Orderless : public BasicOrderless<_DataType, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>, _DefaultValue>{public:};
	};
};

#endif