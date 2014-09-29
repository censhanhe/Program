#ifndef 	__GAIA_MATH_RANDOM_H__
#define 	__GAIA_MATH_RANDOM_H__

namespace GAIA
{
	namespace MATH
	{
		GINL GAIA::N32 xrandom();
		GINL GAIA::GVOID xrandom_seed(GAIA::N32 seed);
	};
};

#include "gaia_math_random_indp.h"

#endif
