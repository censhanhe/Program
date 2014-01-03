#ifndef		__GAIA_MATH_H__
#define		__GAIA_MATH_H__

namespace GAIA
{
	namespace MATH
	{
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