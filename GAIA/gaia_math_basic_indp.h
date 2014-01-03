#ifndef		__GAIA_MATH_BASIC_INDP_H__
#define		__GAIA_MATH_BASIC_INDP_H__

#include	<math.h>

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_INL static REAL xsin(const REAL& v){return (REAL)sin((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xcos(const REAL& v){return (REAL)cos((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xacos(const REAL& v){return (REAL)acos((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xasin(const REAL& v){return (REAL)asin((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xtan(const REAL& v){return (REAL)tan((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xsinh(const REAL& v){return (REAL)sinh((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xcosh(const REAL& v){return (REAL)cosh((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xatan(const REAL& v){return (REAL)atan((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xatan2(const REAL& y, const REAL& x){return (REAL)atan2((REAL)x, (REAL)y);}
		GAIA_DEBUG_CODEPURE_INL static REAL xpow(const REAL& x, const REAL& y){return (REAL)pow((REAL)x, (REAL)y);}
		GAIA_DEBUG_CODEPURE_INL static REAL xsqrt(const REAL& v){return (REAL)sqrt((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xlog(const REAL& v){return (REAL)log((REAL)v);}
		GAIA_DEBUG_CODEPURE_INL static REAL xlog10(const REAL& v){return (REAL)log10((REAL)v);}
	};
};

#endif