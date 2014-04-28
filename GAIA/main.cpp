#if defined(_MSC_VER) && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#	define	_CRTDBG_MAP_ALLOC
#	include	<stdlib.h>
#	include	<stdio.h>
#	include	<crtdbg.h>
#	include <assert.h>
#	define HEAPCHECK assert(_CrtCheckMemory());
#else
#	define HEAPCHECK
#endif

#include "gaia.h"
#include "gaia_global_impl.h"
#include "TEST/t_header.h"

#if GAIA_OS == GAIA_OS_WINDOWS
#	pragma comment(lib, "ws2_32.lib")
#endif

#ifdef GAIA_DEBUG_MEMORYLEAK
#	if GAIA_OS == GAIA_OS_WINDOWS && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#		define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#	endif
#endif

int main()
{
	GAIA::FILESYSTEM::File file;
	file.Open("../gaia_test.txt", GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE);
	GAIA::PRINT::Print prt;
	GAIATEST::t_all(file, prt);
	return 0;
}