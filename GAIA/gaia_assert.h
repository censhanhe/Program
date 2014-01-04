#ifndef		__GAIA_ASSERT_H__
#define		__GAIA_ASSERT_H__

namespace GAIA
{
	namespace DEBUG_MANAGEMENT
	{
		#define GAIA_ASSERT(e) do{}while(GAIA::ALWAYSFALSE)
		#define GAIA_STATIC_ASSERT(e) do{typedef struct GAIA_STATIC_ASSERT_STRUCT GAIA_STATIC_ASSERT_FAILED[(e) ? 1 : -1];}while(GAIA::ALWAYSFALSE)
	};
};
#endif