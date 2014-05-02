#ifndef		__T_HEADER_H__
#define		__T_HEADER_H__

#define GTLINE(sz) do{prt << sz << "\n"; file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINEI(sz) do{prt << "\t\t" << sz << "\n"; file.WriteText("\t\t"); file.WriteText(sz); file.WriteText("\r\n");}while(0)
#define GTLINE1(sz) do{if(!bOutputTime)\
							uTimeBegin = GAIA::TIME::tick_time();\
						else\
						{\
							uTimeEnd = GAIA::TIME::tick_time();\
							str.clear();\
							str += "Timelost ";\
							str += (GAIA::F64)(uTimeEnd - uTimeBegin) / 1000.0;\
							str += "(MS)";\
							GTLINEI(str.front_ptr());\
						}\
						bOutputTime = !bOutputTime;\
						prt << "\t" << sz << "\n"; file.WriteText("\t"); file.WriteText(sz); file.WriteText("\r\n");\
					}while(0)
#define GTLINE2(sz) do{prt << "\t\t" << sz << " " << __FILE__ << "(" << __LINE__ << ")" << "\n";\
						GAIA::CONTAINER::AString temp;\
						temp = sz;\
						temp += " ";\
						temp += __FILE__;\
						temp += "(";\
						temp += __LINE__;\
						temp += ")";\
						file.WriteText("\t\t"); file.WriteText(temp.front_ptr()); file.WriteText("\r\n");}while(0)

#include "t_buffer.h"
#include "t_ptr.h"
#include "t_ref.h"
#include "t_array.h"
#include "t_vector.h"
#include "t_arrayvector.h"
#include "t_stackstack.h"
#include "t_stack.h"
#include "t_stackqueue.h"
#include "t_queue.h"
#include "t_list.h"
#include "t_chars.h"
#include "t_string.h"
#include "t_stackbitset.h"
#include "t_bitset.h"
#include "t_trietree.h"
#include "t_avltree.h"
#include "t_set.h"
#include "t_map.h"
#include "t_multiavltree.h"
#include "t_multiset.h"
#include "t_multimap.h"
#include "t_graph.h"
#include "t_storage.h"
#include "t_accesser.h"
#include "t_namespace.h"

namespace GAIATEST
{
	GINL GAIA::N32 t_all(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CONTAINER::AString str;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("Buffer test begin!"); nRet += t_buffer(file, prt); GTLINE1("Buffer test end!"); GTLINE("\t");
			GTLINE1("Ptr test begin!"); nRet += t_ptr(file, prt); GTLINE1("Ptr test end!"); GTLINE("\t");
			GTLINE1("Ref test begin!"); nRet += t_ref(file, prt); GTLINE1("Ref test end!"); GTLINE("\t");
			GTLINE1("Array test begin!"); nRet += t_array(file, prt); GTLINE1("Array test end!"); GTLINE("\t");
			GTLINE1("Vector test begin!"); nRet += t_vector(file, prt); GTLINE1("Vector test end!"); GTLINE("\t");
			GTLINE1("ArrayVector test begin!"); nRet += t_arrayvector(file, prt); GTLINE1("ArrayVector test end!"); GTLINE("\t");
			GTLINE1("StackStack test begin!"); nRet += t_stackstack(file, prt); GTLINE1("StackStack test end!"); GTLINE("\t");
			GTLINE1("Stack test begin!"); nRet += t_stack(file, prt); GTLINE1("Stack test end!"); GTLINE("\t");
			GTLINE1("StackQueue test begin!"); nRet += t_stackqueue(file, prt); GTLINE1("StackQueue test end!"); GTLINE("\t");
			GTLINE1("Queue test begin!"); nRet += t_queue(file, prt); GTLINE1("Queue test end!"); GTLINE("\t");
			GTLINE1("List test begin!"); nRet += t_list(file, prt); GTLINE1("List test end!"); GTLINE("\t");
			GTLINE1("Chars test begin!"); nRet += t_chars(file, prt); GTLINE1("Chars test end!"); GTLINE("\t");
			GTLINE1("String test begin!"); nRet += t_string(file, prt); GTLINE1("String test end!"); GTLINE("\t");
			GTLINE1("StackBitset test begin!"); nRet += t_stackbitset(file, prt); GTLINE1("StackBitset test end!"); GTLINE("\t");
			GTLINE1("Bitset test begin!"); nRet += t_bitset(file, prt); GTLINE1("Bitset test end!"); GTLINE("\t");
			GTLINE1("TrieTree test begin!"); nRet += t_trietree(file, prt); GTLINE1("TrieTree test end!"); GTLINE("\t");
			GTLINE1("AVLTree test begin!"); nRet += t_avltree(file, prt); GTLINE1("AVLTree test end!"); GTLINE("\t");

			GTLINE1("Set test begin!"); nRet += t_set(file, prt); GTLINE1("Set test end!"); GTLINE("\t");
			GTLINE1("Map test begin!"); nRet += t_map(file, prt); GTLINE1("Map test end!"); GTLINE("\t");
			GTLINE1("MultiAVLTree test begin!"); nRet += t_multiavltree(file, prt); GTLINE1("MultiAVLTree test end!"); GTLINE("\t");
			GTLINE1("MultiSet test begin!"); nRet += t_multiset(file, prt); GTLINE1("MultiSet test end!"); GTLINE("\t");
			GTLINE1("MultiMap test begin!"); nRet += t_multimap(file, prt); GTLINE1("MultiMap test end!"); GTLINE("\t");
			GTLINE1("Graph test begin!"); nRet += t_graph(file, prt); GTLINE1("Graph test end!"); GTLINE("\t");
			GTLINE1("Storage test begin!"); nRet += t_storage(file, prt); GTLINE1("Storage test end!"); GTLINE("\t");

			GTLINE1("Accesser test begin!"); nRet += t_accesser(file, prt); GTLINE1("Accesser test end!"); GTLINE("\t");
			GTLINE1("Namespace test begin!"); nRet += t_namespace(file, prt); GTLINE1("Namespace test end!"); GTLINE("\t");
		}
		GTLINE("[GAIA TEST END]");

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