#ifndef		__T_DWARFS_HEADER_H__
#define		__T_DWARFS_HEADER_H__

#include "../../GAIA/TEST/t_common.h"
#include "t_textline.h"
#include "t_cmdparam.h"

namespace DWARFSTEST
{
	GINL GAIA::N32 t_all(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CONTAINER::AString str;

		// Every test procedure.
		GTLINE("[DWARFS TEST BEGIN]");
		{
			GTLINE1("TestLines test begin!"); nRet += t_textline(file, prt); GTLINE1("TestLines test end!"); GTLINE("\t");
			GTLINE1("CmdParam test begin!"); nRet += t_cmdparam(file, prt); GTLINE1("CmdParam test end!"); GTLINE("\t");
		}
		GTLINE("[DWARFS TEST END]");

		GTLINE("\t");

		// Statistics.
		if(nRet == 0)
			GTLINE("There is no error occurred!");
		else
		{
			str.clear();
			str = "There are ";
			str += nRet;
			str += " error occurred.";
			GTLINE(str.front_ptr());
		}
		return nRet;
	}
};

#endif
