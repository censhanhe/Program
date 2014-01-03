#ifndef		__GAIA_MATH_H__
#define		__GAIA_MATH_H__

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_INL static REAL xcos(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xsin(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xacos(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xasin(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xtan(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xsinh(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xcosh(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xatan(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xatan2(const REAL& y, const REAL& x);
		GAIA_DEBUG_CODEPURE_INL static REAL xpow(const REAL& x, const REAL& y);
		GAIA_DEBUG_CODEPURE_INL static REAL xsqrt(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xlog(const REAL& v);
		GAIA_DEBUG_CODEPURE_INL static REAL xlog10(const REAL& v);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_basic_indp.h"
#endif

#endif