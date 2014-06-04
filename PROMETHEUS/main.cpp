#if GAIA_COMPILER == GAIA_COMPILER_CL && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#   define  _CRTDBG_MAP_ALLOC
#   include <stdlib.h>
#   include <stdio.h>
#   include <crtdbg.h>
#   include <assert.h>
#   define HEAPCHECK assert(_CrtCheckMemory());
#else
#   define HEAPCHECK
#endif

#ifdef GAIA_DEBUG_MEMORYLEAK
#   if GAIA_OS == GAIA_OS_WINDOWS && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#       define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#   endif
#endif

#include "../GAIA/gaia.h"
#include "../GAIA/gaia_global_impl.h"
#include "prom.h"

#if GAIA_OS == GAIA_OS_WINDOWS
#   pragma comment(lib, "ws2_32.lib")
#endif

GAIA::N32 main(GAIA::N32 nargs, GAIA::GCH* args[])
{
#if GAIA_OS == GAIA_OS_WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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
	buf.write((GAIA::GCH)'\0');

	/* Find first command. */
	GAIA::SIZE first_command_index = 0;
	for(GAIA::SIZE x = 0; x < buf.write_size(); ++x)
	{
		if(buf[x] == ' ')
		{
			first_command_index = x + 1;
			break;
		}
		if(buf[x] == '\0')
		{
			first_command_index = x;
			break;
		}
	}
	for(; first_command_index < buf.write_size(); ++first_command_index)
	{
		if(buf[first_command_index] != '\n' && 
			buf[first_command_index] != '\r' && 
			buf[first_command_index] != ' ' && 
			buf[first_command_index] != '\t')
			break;
	}
	if(first_command_index + 1 == buf.write_size())
	{
		GAIA::CONTAINER::AString strCombin;
		prt << "Enter the command here : ";
		GAIA::GCH szParam[1024];
		while(GAIA::ALWAYSTRUE)
		{
			prt >> szParam;
			GAIA::GCH* p = GAIA::ALGORITHM::strch(szParam, ';');
			if(p != GNULL)
			{
				if(p != szParam)
				{
					*p = '\0';
					if(!strCombin.empty())
						strCombin += " ";
					strCombin += szParam;
				}
				break;
			}
			else
			{
				if(!strCombin.empty())
					strCombin += " ";
				strCombin += szParam;
			}
		}
		if(strCombin.empty())
			return 0;
		buf.resize((strCombin.size() + 1) * sizeof(GAIA::CONTAINER::AString::_datatype));
		GAIA::ALGORITHM::xmemcpy(buf.front_ptr(), strCombin.front_ptr(), (strCombin.size() + 1) * sizeof(GAIA::CONTAINER::AString::_datatype));
		first_command_index = 0;
	}

	/* Execute command. */
	PROM::Prom prom;
	prom.Command((GAIA::GCH*)buf.front_ptr() + first_command_index, prt);

	return 0;
}
