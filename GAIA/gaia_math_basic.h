#ifndef		__GAIA_MATH_H__
#define		__GAIA_MATH_H__

namespace GAIA
{
	namespace MATH
	{
		template <typename _DataType1, typename _DataType2> GINL GAIA::BL equal(const _DataType1& t1, const _DataType2& t2)
		{
			if(GAIA::ALGORITHM::abs(t1 - t2) < (typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType)0.00001)
				return GAIA::True;
			return GAIA::False;
		}
		template <typename _DataType1, typename _DataType2, typename _DataType3> GINL GAIA::BL equal(const _DataType1& t1, const _DataType2& t2, const _DataType3& epsilon)
		{
			if(abs(t1 - t2) < epsilon)
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
