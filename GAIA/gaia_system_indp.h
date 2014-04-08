#ifndef		__GAIA_SYSTEM_INDP_H__
#define		__GAIA_SYSTEM_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace SYSTEM
	{
		namespace GAIA_INTERNAL_NAMESPACE
		{
			template<typename _DataType> GINL GAIA::N32 commandlinecmp(const _DataType* p1, const _DataType* p2)
			{
				while(GAIA::ALWAYSTRUE)
				{
					if(*p1 < *p2)
						return -1;
					else if(*p1 > *p2)
						return +1;
					else
					{
						if(*p1 == 0)
							return 0;
						++p1;
						++p2;
					}
				}
				return 0;
			}
		}

		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL command_line(const GAIA::GCH* pszCmd)
		{
			if(GAIA::ALWAYSFALSE){}
			else if(GAIA_INTERNAL_NAMESPACE::commandlinecmp(pszCmd, "clear") == 0)
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