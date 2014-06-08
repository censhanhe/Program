#ifndef		__GAIA_MATH_H__
#define		__GAIA_MATH_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> GINL _DataType xabs(const _DataType& t)
		{
			if(t < 0)
				return -t;
			return t;
		}
		template<typename _DataType> GINL _DataType xsign(const _DataType& t)
		{
			if(t < (_DataType)0)
				return (_DataType)-1;
			else if(t > (_DataType)0)
				return (_DataType)+1;
			else
				return (_DataType)0;
		}
		template<typename _DataType, typename _ParamType1, typename _ParamType2> GINL _DataType xclamp(const _DataType& src, const _ParamType1& limitlow, const _ParamType2& limithigh)
		{
			GAIA_AST(limitlow <= limithigh);
			_DataType ret = src;
			if(ret < limitlow)
				ret = (_DataType)limitlow;
			if(ret > limithigh)
				ret = (_DataType)limithigh;
			return ret;
		}
		template<typename _DataType> GINL _DataType xsaturate(const _DataType& src)
		{
			return xclamp(src, (_DataType)0, (_DataType)1);
		}
		template<typename _DataType> GINL _DataType xfloor(const _DataType& src)
		{
		}
		template<typename _DataType> GINL _DataType xceil(const _DataType& src)
		{
		}
		template<typename _DataType1, typename _DataType2> GINL GAIA::BL xequal(const _DataType1& t1, const _DataType2& t2)
		{
			if(GAIA::MATH::xabs(t1 - t2) < (typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType)0.00001)
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType1, typename _DataType2, typename _DataType3> GINL GAIA::BL xequal(const _DataType1& t1, const _DataType2& t2, const _DataType3& epsilon)
		{
			if(xabs(t1 - t2) < epsilon)
				return GAIA::True;
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_FUNC REAL xcos(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xsin(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xacos(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xasin(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xtan(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xsinh(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xcosh(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xatan(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xatan2(const REAL& y, const REAL& x);
		GAIA_DEBUG_CODEPURE_FUNC REAL xpow(const REAL& x, const REAL& y);
		GAIA_DEBUG_CODEPURE_FUNC REAL xsqrt(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xlog(const REAL& v);
		GAIA_DEBUG_CODEPURE_FUNC REAL xlog10(const REAL& v);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_basic_indp.h"
#endif

#endif
