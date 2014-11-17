#include "../../GAIA/preheader.h"
#include "../../GAIA/gaia_sysconfig.h"
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

#include "../../GAIA/gaia.h"
#include "../../GAIA/gaia_global_impl.h"
#include "../MISC/textfile.h"
#include "../MISC/textline.h"
#include "../MISC/cmdparam.h"
#include "../MISC/sendmail.h"
#include "../MISC/express.h"
#include "../MISC/portscanner.h"
#include "t_header.h"

int main()
{
#if GAIA_OS == GAIA_OS_WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	GAIA::FSYS::File file;
	file.Open(_T("../gaia_test.txt"), GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE);
	GAIA::STREAM::STDStream stm;
	DWARFSTEST::t_all(file, stm);
	return 0;
}
