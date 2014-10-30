#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_sync_atomic(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::SYNC::Atomic a, a1;
		GAIA::N64 n = a;
		if(n != 0)
		{
			GTLINE2("Atomic init value is not zero!");
			++nRet;
		}
		if(a.Increase() != 1)
		{
			GTLINE2("Atomic increase error!");
			++nRet;
		}
		n = a;
		if(n != 1)
		{
			GTLINE2("Atomic increase error!");
			++nRet;
		}
		if(a.Increase() != 2)
		{
			GTLINE2("Atomic increase error!");
			++nRet;
		}
		n = a;
		if(n != 2)
		{
			GTLINE2("Atomic increase error!");
			++nRet;
		}
		if(a.Decrease() != 1)
		{
			GTLINE2("Atomic decrease error!");
			++nRet;
		}
		n = a;
		if(n != 1)
		{
			GTLINE2("Atomic decrease error!");
			++nRet;
		}
		if(a.Decrease() != 0)
		{
			GTLINE2("Atomic decrease error!");
			++nRet;
		}
		n = a;
		if(n != 0)
		{
			GTLINE2("Atomic decrease error!");
			++nRet;
		}
		a = 10;
		if((GAIA::N64)a != 10)
		{
			GTLINE2("Atomic operator = from GAIA::N64 error!");
			++nRet;
		}
		a1 = a;
		if((GAIA::N64)a1 != 10)
		{
			GTLINE2("Atomic operator = from Atomic obj error!");
			++nRet;
		}
		a = 12;
		if(a.Add(12) != 24)
		{
			GTLINE2("Atomic add from GAIA::N64 error!");
			++nRet;
		}
		if((GAIA::N64)a != 24)
		{
			GTLINE2("Atomic add from GAIA::N64 error!");
			++nRet;
		}
		if(a.Add(-14) != 10)
		{
			GTLINE2("Atomic add from GAIA::N64 error!");
			++nRet;
		}
		if((GAIA::N64)a != 10)
		{
			GTLINE2("Atomic add from GAIA::N64 error!");
			++nRet;
		}
		a = 13;
		a1 = 14;
		if(a.Add(a1) != 27)
		{
			GTLINE2("Atomic add from atomic error!");
			++nRet;
		}
		if((GAIA::N64)a != 27)
		{
			GTLINE2("Atomic add from atomic error!");
			++nRet;
		}
		a1 = -14;
		if(a.Add(a1) != 13)
		{
			GTLINE2("Atomic add from atomic error!");
			++nRet;
		}
		if((GAIA::N64)a != 13)
		{
			GTLINE2("Atomic add from atomic error!");
			++nRet;
		}

		return nRet;
	}
};
