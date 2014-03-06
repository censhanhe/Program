#ifndef		__GAIA_ASSERT_H__
#define		__GAIA_ASSERT_H__

namespace GAIA
{
	namespace DEBUG_MANAGEMENT
	{
#ifdef GAIA_DEBUG_AST
#	if GAIA_OS == GAIA_OS_WINDOWS
#		if GAIA_MACHINE == GAIA_MACHINE32 && defined(_DEBUG)
#			define GAIA_AST(e)	do{if(!(e)){__asm INT 03H}}while(0)
#		else
#			define GAIA_AST(e)
#		endif
#	else
#		define GAIA_AST(e)
#	endif
#else
#	define GAIA_AST(e)
#endif

#ifdef GAIA_DEBUG_STATICAST
#	define GAIA_STATIC_AST(e) do{typedef class GAIA_STATIC_ASSERT_STRUCT GAIA_STATIC_ASSERT_FAILED[(e) ? 1 : -1];}while(GAIA::ALWAYSFALSE)
#endif
	};
};
#endif
