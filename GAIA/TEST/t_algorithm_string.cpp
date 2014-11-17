#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_algorithm_string(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		/* Hex convert. */
		{
			GAIA::U64 u = 0x1234567890ABCDEF;
			GAIA::TCH szTemp[32];
			GAIA::ALGO::hex2str(GRCAST(const GAIA::U8*)((GAIA::GVOID*)&u), sizeof(u), szTemp);
			if(GAIA::ALGO::strcmp(szTemp, _T("1234567890ABCDEF")) != 0)
			{
				GTLINE2("Algorithm string hex2str failed!");
				++nRet;
			}
			u = 0;
			GAIA::ALGO::str2hex(szTemp, sizeof(u), GRCAST(GAIA::U8*)(&u));
			if(u != 0x1234567890ABCDEF)
			{
				GTLINE2("Algorithm string str2hex failed!");
				++nRet;
			}
		}

		return nRet;
	}
};
