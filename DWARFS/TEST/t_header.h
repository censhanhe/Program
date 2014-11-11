#ifndef		__T_DWARFS_HEADER_H__
#define		__T_DWARFS_HEADER_H__

#include "../../GAIA/TEST/t_common.h"
#include "t_textfile.h"
#include "t_textline.h"
#include "t_cmdparam.h"
#include "t_sendmail.h"

namespace DWARFSTEST
{
	GINL GAIA::N32 t_all(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CTN::AString str;

		// Every test procedure.
		GTLINE("[DWARFS TEST BEGIN]");
		{
			GTLINE1("TextFile test begin!"); nRet += t_textfile(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("TextLine test begin!"); nRet += t_textline(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("CmdParam test begin!"); nRet += t_cmdparam(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("SendMail test begin!"); nRet += t_sendmail(file, prt); GTLINE1("End"); GTLINE("\t");
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
