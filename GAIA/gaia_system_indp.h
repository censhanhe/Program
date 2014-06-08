#ifndef		__GAIA_SYSTEM_INDP_H__
#define		__GAIA_SYSTEM_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace SYSTEM
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL command_line(const GAIA::GCH* pszCmd)
		{
			if(GAIA::ALWAYSFALSE){}
			else if(GAIA_INTERNAL_NAMESPACE::strcmp(pszCmd, "clear") == 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				system("cls");
			#else
				system("clear");
			#endif
			}
			else
				return GAIA::False;
			return GAIA::True;
		}
	};
};

#endif
