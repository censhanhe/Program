#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_log_log(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		for(GAIA::SIZE x = 0; x < 10; ++x)
		{
			g_gaia_log << "Test log " << 
				(GAIA::U8)1 << " " <<
				(GAIA::U16)2 << " " <<
				(GAIA::U32)3 << " " <<
				(GAIA::U64)4 << " " <<
				(GAIA::N8)-5 << " " <<
				(GAIA::N16)+6 << " " <<
				(GAIA::N32)-7 << " " <<
				(GAIA::N64)+8 << " " <<
				(GAIA::UM)9 << " " <<
				(GAIA::NM)-10 << " " <<
				(GAIA::BL)GAIA::True << " " <<
				(GAIA::F32)11.12345678 << " " <<
				(GAIA::F64)12.12345678 << " " <<
				(GAIA::CH*)"ansi string" << " " <<
				(GAIA::WCH*)L"unicode string" << 
				g_gaia_log.End();
		}

		return nRet;
	}
};