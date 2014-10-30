#include "preheader.h"
#include "t_header.h"

#include "../gaia_using_namespace.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_namespace(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
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
			p = GNIL;
		}
		{
			GAIA::TCH szTemp[32] = _T("HelloWorld");
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
		{
			Factory fac;
			Canvas* pCanvas = dynamic_cast<Canvas*>(fac.CreateInstance(CLSID_UI_CANVAS, GNIL));
			if(pCanvas != GNIL)
			{
				Canvas::CanvasDesc desc;
				desc.reset();
				desc.pszCaptionText = _T("Hello World");
				if(!pCanvas->Create(desc))
				{
					GTLINE2("Canvas create failed!");
					++nRet;
				}
				if(!pCanvas->Destroy())
				{
					GTLINE2("Canvas destroy failed!");
					++nRet;
				}
				pCanvas->Release();
				pCanvas = GNIL;
			}
		}
		return nRet = 0;
	}
};
