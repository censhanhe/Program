#ifndef 	__GAIA_MATH_RANDOM_INDP_H__
#define 	__GAIA_MATH_RANDOM_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::N32 random(){return rand();}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID random_seed(GAIA::N32 seed){srand(seed);}
	};
};

#endif
