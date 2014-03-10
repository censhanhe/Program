#ifndef 	__GAIA_MATH_RANDOM_H__
#define 	__GAIA_MATH_RANDOM_H__

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::N32 random();
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID random_seed(GAIA::N32 seed);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_random_indp.h"
#endif

#endif
