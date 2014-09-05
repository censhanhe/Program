#ifndef		__GAIA_MATH_H__
#define		__GAIA_MATH_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> _DataType xabs(const _DataType& t)
		{
			if(t < 0)
				return -t;
			return t;
		}
		template<typename _DataType> _DataType xsign(const _DataType& t)
		{
			if(t < (_DataType)0)
				return (_DataType)-1;
			else if(t > (_DataType)0)
				return (_DataType)+1;
			else
				return (_DataType)0;
		}
		template<typename _DataType, typename _ParamType1, typename _ParamType2> _DataType xclamp(const _DataType& src, const _ParamType1& limitlow, const _ParamType2& limithigh)
		{
			GAIA_AST(limitlow <= limithigh);
			_DataType ret = src;
			if(ret < limitlow)
				ret = (_DataType)limitlow;
			if(ret > limithigh)
				ret = (_DataType)limithigh;
			return ret;
		}
		template<typename _DataType> _DataType xsaturate(const _DataType& src)
		{
			return xclamp(src, (_DataType)0, (_DataType)1);
		}
		template<typename _DataType> _DataType xfloor(const _DataType& src)
		{
			_DataType tinteger = (_DataType)(GAIA::N64)src;
			_DataType t = src - tinteger;
			if(t == (_DataType)0)
				return src;
			return tinteger;
		}
		template<typename _DataType> _DataType xceil(const _DataType& src)
		{
			_DataType tinteger = (_DataType)(GAIA::N64)src;
			_DataType t = src - tinteger;
			if(t == (_DataType)0)
				return src;
			return tinteger + (_DataType)1;
		}
		template<typename _DataType1, typename _DataType2> GAIA::BL xequal(const _DataType1& t1, const _DataType2& t2)
		{
			if(GAIA::MATH::xabs(t1 - t2) <= (typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType)0.00001)
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType1, typename _DataType2, typename _DataType3> GAIA::BL xequal(const _DataType1& t1, const _DataType2& t2, const _DataType3& epsilon)
		{
			if(xabs(t1 - t2) < epsilon)
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType> _DataType xavg2(_DataType t1, _DataType t2)
		{
			return (t1 + t2) / (_DataType)2;
		}
		template<typename _DataType> _DataType xavg3(_DataType t1, _DataType t2, _DataType t3)
		{
			return (t1 + t2 + t3) / (_DataType)3;
		}
		template<typename _DataType> _DataType xavg4(_DataType t1, _DataType t2, _DataType t3, _DataType t4)
		{
			return (t1 + t2 + t3 + t4) / (_DataType)4;
		}
		template<typename _DataType, typename _ResultType> GAIA::GVOID xavgs(_DataType pBegin, _DataType pEnd, _ResultType& res)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			res = (_ResultType)0;
			_DataType p = pBegin;
			while(p != pEnd)
			{
				res += *p;
				++p;
			}
			res += *p;
			res /= (pEnd - pBegin + 1);
		}
		template<typename _DataType> _DataType xcos(const _DataType& v);
		template<typename _DataType> _DataType xsin(const _DataType& v);
		template<typename _DataType> _DataType xacos(const _DataType& v);
		template<typename _DataType> _DataType xasin(const _DataType& v);
		template<typename _DataType> _DataType xtan(const _DataType& v);
		template<typename _DataType> _DataType xsinh(const _DataType& v);
		template<typename _DataType> _DataType xcosh(const _DataType& v);
		template<typename _DataType> _DataType xatan(const _DataType& v);
		template<typename _DataType> _DataType xatan2(const _DataType& y, const _DataType& x);
		template<typename _DataType> _DataType xpow(const _DataType& x, const _DataType& y);
		template<typename _DataType> _DataType xsqrt(const _DataType& v);
		template<typename _DataType> _DataType xlog(const _DataType& v);
		template<typename _DataType> _DataType xlog10(const _DataType& v);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_basic_indp.h"
#endif

#endif
