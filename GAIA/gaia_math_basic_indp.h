#ifndef		__GAIA_MATH_BASIC_INDP_H__
#define		__GAIA_MATH_BASIC_INDP_H__

#include <math.h>

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> _DataType xsin(const _DataType& v){return GSCAST(_DataType)(sin(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xcos(const _DataType& v){return GSCAST(_DataType)(cos(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xacos(const _DataType& v){return GSCAST(_DataType)(acos(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xasin(const _DataType& v){return GSCAST(_DataType)(asin(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xtan(const _DataType& v){return GSCAST(_DataType)(tan(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xsinh(const _DataType& v){return GSCAST(_DataType)(sinh(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xcosh(const _DataType& v){return GSCAST(_DataType)(cosh(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xatan(const _DataType& v){return GSCAST(_DataType)(atan(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xatan2(const _DataType& y, const _DataType& x){return GSCAST(_DataType)(atan2(GSCAST(GAIA::REAL)(y), GSCAST(GAIA::REAL)(x)));}
		template<typename _DataType> _DataType xpow(const _DataType& x, const _DataType& y){return GSCAST(_DataType)(pow(GSCAST(GAIA::REAL)(x), GSCAST(GAIA::REAL)(y)));}
		template<typename _DataType> _DataType xsqrt(const _DataType& v){return GSCAST(_DataType)(sqrt(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xlog(const _DataType& v){return GSCAST(_DataType)(log(GSCAST(GAIA::REAL)(v)));}
		template<typename _DataType> _DataType xlog10(const _DataType& v){return GSCAST(_DataType)(log10(GSCAST(GAIA::REAL)(v)));}
	};
};

#endif
