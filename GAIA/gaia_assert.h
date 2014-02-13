#ifndef		__GAIA_ASSERT_H__
#define		__GAIA_ASSERT_H__

namespace GAIA
{
	namespace DEBUG_MANAGEMENT
	{
		#define GAIA_AST(e) do{}while(GAIA::ALWAYSFALSE)
		#define GAIA_STATIC_ASSERT(e) do{typedef class GAIA_STATIC_ASSERT_STRUCT GAIA_STATIC_ASSERT_FAILED[(e) ? 1 : -1];}while(GAIA::ALWAYSFALSE)
	};
};
#endif
