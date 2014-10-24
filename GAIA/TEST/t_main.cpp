//#define GAIA_PLATFORM_NETWORK
//#define GAIA_PLATFORM_GDIPLUS
//#define GAIA_PLATFORM_DDRAW
//#define GAIA_PLATFORM_OPENGL1
//#define GAIA_PLATFORM_OPENGL2
//#define GAIA_PLATFORM_OPENGL3
//#define GAIA_PLATFORM_OPENGLES1
//#define GAIA_PLATFORM_OPENGLES2
//#define GAIA_PLATFORM_OPENGLES3
//#define GAIA_PLATFORM_DX9
//#define GAIA_PLATFORM_DX10
//#define GAIA_PLATFORM_DX11
//#define GAIA_PLATFORM_COM

#include "preheader.h"

#include "../gaia_sysconfig.h"
#if GAIA_COMPILER == GAIA_COMPILER_CL && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#	define	_CRTDBG_MAP_ALLOC
#	include	<stdlib.h>
#	include	<stdio.h>
#	include	<crtdbg.h>
#	include <assert.h>
#	define HEAPCHECK assert(_CrtCheckMemory());
#else
#	define HEAPCHECK
#endif

#ifdef GAIA_DEBUG_MEMORYLEAK
#	if GAIA_OS == GAIA_OS_WINDOWS && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#		define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#	endif
#endif

#include "../gaia.h"
#include "../gaia_global_impl.h"
#include "t_header.h"

int main()
{
#if GAIA_OS == GAIA_OS_WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	GAIA::FSYS::File file;
	file.Open(_T("../gaia_test.txt"), GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE);
	GAIA::PRINT::Print prt;
	GAIA_TEST::t_all(file, prt);
	return 0;
}
