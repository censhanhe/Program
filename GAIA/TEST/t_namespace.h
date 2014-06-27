#ifndef		__T_NAMESPACE_H__
#define		__T_NAMESPACE_H__

#include	"../gaia_using_namespace.h"

namespace GAIATEST
{
	GINL GAIA::N32 t_namespace(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		{
			GAIA::N32* p = GAIA_MALLOC(GAIA::N32, 1024);
			for(GAIA::N32 x = 0; x < 1024; ++x)
				p[x] = xrandom();
			qsort(p, p + 1024 - 1);
			GAIA::N32* pEnd = unique_order(p, p + 1024 - 1);
			xmemset(p, (GAIA::N8)17, sizeof(GAIA::N32) * 1024);
			xmemcpy(p, p + 1, sizeof(GAIA::N32));
			xmemcmp(p, p + 1, sizeof(GAIA::N32));
			GAIA_MFREE(p);
			p = GNULL;
		}
		{
			GAIA::GCH szTemp[32] = "HelloWorld";
			tolower(szTemp[0]);
			isalpha(szTemp[0]);
			isdigit(szTemp[0]);
			strlen(szTemp);
			strcmp(szTemp, szTemp);
			strstr(szTemp, szTemp);
		}
		{
			xusleep(0);
			xsleep(0);
		}
		return nRet = 0;
	}
};

#endif
