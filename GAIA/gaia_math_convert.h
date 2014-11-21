#ifndef		__GAIA_MATH_CONVERT_H__
#define		__GAIA_MATH_CONVERT_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> _DataType degree(const _DataType& radius){return radius / GAIA::MATH::PI * (_DataType)180;}
		template<typename _DataType> _DataType radius(const _DataType& degree){return degree / (_DataType)180 * GAIA::MATH::PI;}
	};
};

#endif