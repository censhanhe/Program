#ifndef		__T_HEADER_H__
#define		__T_HEADER_H__

#define GTLINE(sz) do{prt << sz << "\n"; file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINE1(sz) do{prt << "\t" << sz << "\n"; file.WriteText("\t"); file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINE2(sz) do{prt << "\t\t" << sz << "\n"; file.WriteText("\t\t"); file.WriteText(sz); file.WriteText("\r\n");}while(0)


#include	"t_accesser.h"

namespace GAIATEST
{
	GINL GAIA::N32 t_all(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("\tAccesser test begin!"); nRet += t_accesser(file, prt); GTLINE1("\tAccesser test end!"); GTLINE1("\t");
		}
		GTLINE("[GAIA TEST END]");
		GTLINE("\t");

		// Statistics.
		if(nRet == 0)
			GTLINE("There is no error occurred!");
		else
		{
			GAIA::CONTAINER::AString str;
			str = "There are ";
			str += nRet;
			str += " error occurred.";
			GTLINE(str.front_ptr());
		}
		return nRet;
	}
};

#endif