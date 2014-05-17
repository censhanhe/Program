#if defined(_MSC_VER) && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#   define  _CRTDBG_MAP_ALLOC
#   include <stdlib.h>
#   include <stdio.h>
#   include <crtdbg.h>
#   include <assert.h>
#   define HEAPCHECK assert(_CrtCheckMemory());
#else
#   define HEAPCHECK
#endif

#include "../GAIA/gaia.h"
#include "../GAIA/gaia_global_impl.h"
#include "prom.h"

#if GAIA_OS == GAIA_OS_WINDOWS
#   pragma comment(lib, "ws2_32.lib")
#endif

#ifdef GAIA_DEBUG_MEMORYLEAK
#   if GAIA_OS == GAIA_OS_WINDOWS && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#       define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#   endif
#endif


GAIA::N32 main(GAIA::N32 nargs, GAIA::GCH* args[])
{
	GAIA::PRINT::Print prt;

	/* Calculate all args length. */
	GAIA::N32 nLen = 1;
	for(GAIA::N32 x = 0; x < nargs; ++x)
		nLen += GAIA::ALGORITHM::strlen(args[x]) + 1;

	/* Combin args to single buffer. */
	GAIA::CONTAINER::Buffer buf;
	buf.reserve((nLen + 1) * sizeof(GAIA::GCH));
	for(GAIA::N32 x = 0; x < nargs; ++x)
	{
		buf.write(args[x], GAIA::ALGORITHM::strlen(args[x]) * sizeof(GAIA::GCH));
		buf.write((GAIA::GCH)' ');
	}

	/* Execute command. */

	return 0;
}
