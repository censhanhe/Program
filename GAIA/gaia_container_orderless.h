#ifndef		__GAIA_CONTAINER_ORDERLESS_H__
#define		__GAIA_CONTAINER_ORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, _DataType _DefaultValue> class Orderless : public BasicOrderless<_DataType, GAIA::UM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::UM>, _DefaultValue>{public:};
	};
};

#endif