#ifndef		__GAIA_MATH_BASIC_INDP_H__
#define		__GAIA_MATH_BASIC_INDP_H__

#include <math.h>

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> _DataType xsin(const _DataType& v){return (_DataType)sin((GAIA::REAL)v);}
		template<typename _DataType> _DataType xcos(const _DataType& v){return (_DataType)cos((GAIA::REAL)v);}
		template<typename _DataType> _DataType xacos(const _DataType& v){return (_DataType)acos((GAIA::REAL)v);}
		template<typename _DataType> _DataType xasin(const _DataType& v){return (_DataType)asin((GAIA::REAL)v);}
		template<typename _DataType> _DataType xtan(const _DataType& v){return (_DataType)tan((GAIA::REAL)v);}
		template<typename _DataType> _DataType xsinh(const _DataType& v){return (_DataType)sinh((GAIA::REAL)v);}
		template<typename _DataType> _DataType xcosh(const _DataType& v){return (_DataType)cosh((GAIA::REAL)v);}
		template<typename _DataType> _DataType xatan(const _DataType& v){return (_DataType)atan((GAIA::REAL)v);}
		template<typename _DataType> _DataType xatan2(const _DataType& y, const _DataType& x){return (_DataType)atan2((GAIA::REAL)y, (GAIA::REAL)x);}
		template<typename _DataType> _DataType xpow(const _DataType& x, const _DataType& y){return (_DataType)pow((GAIA::REAL)x, (GAIA::REAL)y);}
		template<typename _DataType> _DataType xsqrt(const _DataType& v){return (_DataType)sqrt((GAIA::REAL)v);}
		template<typename _DataType> _DataType xlog(const _DataType& v){return (_DataType)log((GAIA::REAL)v);}
		template<typename _DataType> _DataType xlog10(const _DataType& v){return (_DataType)log10((GAIA::REAL)v);}
	};
};

#endif
