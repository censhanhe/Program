#ifndef 	__GAIA_MATH_RANDOM_INDP_H__
#define 	__GAIA_MATH_RANDOM_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::N32 xrandom(){return rand();}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID xrandom_seed(GAIA::N32 seed){srand(seed);}
	};
};

#endif
