#ifndef		__GAIA_MATH_BASIC_INDP_H__
#define		__GAIA_MATH_BASIC_INDP_H__

#include <math.h>

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_FUNC REAL xsin(const REAL& v){return (REAL)sin((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xcos(const REAL& v){return (REAL)cos((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xacos(const REAL& v){return (REAL)acos((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xasin(const REAL& v){return (REAL)asin((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xtan(const REAL& v){return (REAL)tan((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xsinh(const REAL& v){return (REAL)sinh((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xcosh(const REAL& v){return (REAL)cosh((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xatan(const REAL& v){return (REAL)atan((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xatan2(const REAL& y, const REAL& x){return (REAL)atan2((REAL)x, (REAL)y);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xpow(const REAL& x, const REAL& y){return (REAL)pow((REAL)x, (REAL)y);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xsqrt(const REAL& v){return (REAL)sqrt((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xlog(const REAL& v){return (REAL)log((REAL)v);}
		GAIA_DEBUG_CODEPURE_FUNC REAL xlog10(const REAL& v){return (REAL)log10((REAL)v);}
	};
};

#endif
