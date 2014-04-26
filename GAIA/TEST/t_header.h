#ifndef		__T_HEADER_H__
#define		__T_HEADER_H__

#define GTLINE(sz) do{prt << sz << "\n"; file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINE1(sz) do{prt << "\t" << sz << "\n"; file.WriteText("\t"); file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINE2(sz) do{prt << "\t\t" << sz << "\n"; file.WriteText("\t\t"); file.WriteText(sz); file.WriteText("\r\n");}while(0)

#include "t_accesser.h"
#include "t_array.h"
#include "t_vector.h"
#include "t_stackstack.h"
#include "t_stack.h"
#include "t_stackqueue.h"
#include "t_queue.h"
#include "t_list.h"
#include "t_string.h"

namespace GAIATEST
{
	GINL GAIA::N32 t_all(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("Array test begin!"); nRet += t_array(file, prt); GTLINE1("Array test end!"); GTLINE1("\t");
			GTLINE1("Vector test begin!"); nRet += t_vector(file, prt); GTLINE1("Vector test end!"); GTLINE1("\t");
			GTLINE1("StackStack test begin!"); nRet += t_stackstack(file, prt); GTLINE1("StackStack test end!"); GTLINE1("\t");
			GTLINE1("Stack test begin!"); nRet += t_stack(file, prt); GTLINE1("Stack test end!"); GTLINE1("\t");
			GTLINE1("StackQueue test begin!"); nRet += t_stackqueue(file, prt); GTLINE1("StackQueue test end!"); GTLINE1("\t");
			GTLINE1("Queue test begin!"); nRet += t_queue(file, prt); GTLINE1("Queue test end!"); GTLINE1("\t");
			GTLINE1("List test begin!"); nRet += t_list(file, prt); GTLINE1("List test end!"); GTLINE1("\t");
			GTLINE1("String test begin!"); nRet += t_string(file, prt); GTLINE1("String test end!"); GTLINE1("\t");
			GTLINE1("Accesser test begin!"); nRet += t_accesser(file, prt); GTLINE1("Accesser test end!"); GTLINE1("\t");

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