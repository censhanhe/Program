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

#if GAIA_OS == GAIA_OS_WINDOWS
#	pragma comment(lib, "ws2_32.lib")
#endif

int main()
{
#if GAIA_OS == GAIA_OS_WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	{
		GAIA::FRAMEWORK::Factory fac;
		GAIA::UI::Convas* pConvas = (GAIA::UI::Convas*)fac.CreateInstance(GAIA::FRAMEWORK::CLSID_CONVAS, GNULL);
		if(pConvas != GNULL)
		{
			GAIA::UI::Convas::ConvasDesc desc;
			desc.pszCaptionText = _T("Hello World");
			pConvas->Create(desc);
		}
		pConvas->Show(GAIA::True);

		while(GAIA::ALWAYSTRUE)
		{
			if(!GAIA::UI::UpdateMessage(GAIA::True))
				break;
		}

		pConvas->Release();
		pConvas = GNULL;
	}

	GAIA::FILESYSTEM::File file;
	file.Open(_T("../gaia_test.txt"), GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE);
	GAIA::PRINT::Print prt;
	GAIATEST::t_all(file, prt);
	return 0;
}
