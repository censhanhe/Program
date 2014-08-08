#ifndef		__T_GAIA_HEADER_H__
#define		__T_GAIA_HEADER_H__

#include "t_common.h"
#include "t_algorithm_set.h"
#include "t_container_buffer.h"
#include "t_container_ptr.h"
#include "t_container_ref.h"
#include "t_container_array.h"
#include "t_container_vector.h"
#include "t_container_arrayvector.h"
#include "t_container_stackstack.h"
#include "t_container_stack.h"
#include "t_container_stackqueue.h"
#include "t_container_queue.h"
#include "t_container_list.h"
#include "t_container_chars.h"
#include "t_container_string.h"
#include "t_container_stackbitset.h"
#include "t_container_bitset.h"
#include "t_container_trietree.h"
#include "t_container_avltree.h"
#include "t_container_set.h"
#include "t_container_map.h"
#include "t_container_multiavltree.h"
#include "t_container_multiset.h"
#include "t_container_multimap.h"
#include "t_container_tree.h"
#include "t_container_orderless.h"
#include "t_container_graph.h"
#include "t_container_pool.h"
#include "t_container_storage.h"
#include "t_container_accesser.h"
#include "t_container_cooperate.h"
#include "t_locale.h"
#include "t_namespace.h"
#include "t_ui_canvas.h"

namespace GAIATEST
{
	GINL GAIA::N32 t_all(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CONTAINER::AString str;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("Algorithm: Set test begin!"); nRet += t_buffer(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Container: Buffer test begin!"); nRet += t_buffer(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Ptr test begin!"); nRet += t_ptr(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Ref test begin!"); nRet += t_ref(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Array test begin!"); nRet += t_array(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Vector test begin!"); nRet += t_vector(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: ArrayVector test begin!"); nRet += t_arrayvector(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackStack test begin!"); nRet += t_stackstack(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Stack test begin!"); nRet += t_stack(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackQueue test begin!"); nRet += t_stackqueue(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Queue test begin!"); nRet += t_queue(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: List test begin!"); nRet += t_list(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Chars test begin!"); nRet += t_chars(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: String test begin!"); nRet += t_string(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackBitset test begin!"); nRet += t_stackbitset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Bitset test begin!"); nRet += t_bitset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: TrieTree test begin!"); nRet += t_trietree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: AVLTree test begin!"); nRet += t_avltree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Set test begin!"); nRet += t_set(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Map test begin!"); nRet += t_map(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiAVLTree test begin!"); nRet += t_multiavltree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiSet test begin!"); nRet += t_multiset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiMap test begin!"); nRet += t_multimap(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Tree test begin!"); nRet += t_tree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Orderless test begin!"); nRet += t_orderless(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Pool test begin!"); nRet += t_pool(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Graph test begin!"); nRet += t_graph(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Storage test begin!"); nRet += t_storage(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Accesser test begin!"); nRet += t_accesser(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Cooperate test begin!"); nRet += t_cooperate(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Locale test begin!"); nRet += t_locale(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Namespace test begin!"); nRet += t_namespace(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("UI: Canvas test begin!"); nRet += t_ui_canvas(file, prt); GTLINE1("End"); GTLINE("\t");
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
