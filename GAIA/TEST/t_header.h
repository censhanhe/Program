#ifndef		__T_GAIA_HEADER_H__
#define		__T_GAIA_HEADER_H__

#include "t_common.h"

#include "t_math_arithmatic_basic.h"
#include "t_math_arithmatic_lerp.h"
#include "t_math_arithmatic_random.h"

#include "t_math_cookies_argb.h"
#include "t_math_cookies_nrgb.h"
#include "t_math_cookies_vec2.h"
#include "t_math_cookies_vec3.h"
#include "t_math_cookies_vec4.h"
#include "t_math_cookies_mtx22.h"
#include "t_math_cookies_mtx33.h"
#include "t_math_cookies_mtx44.h"
#include "t_math_cookies_mtx43.h"
#include "t_math_cookies_qua.h"
#include "t_math_cookies_aabb.h"
#include "t_math_cookies_aabr.h"

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
#include "t_container_book.h"
#include "t_container_graph.h"
#include "t_container_pool.h"
#include "t_container_storage.h"
#include "t_container_accesser.h"
#include "t_container_stringpool.h"
#include "t_container_staticstringpool.h"
#include "t_container_cooperate.h"

#include "t_time_time.h"

#include "t_filesystem_file.h"
#include "t_filesystem_directory.h"

#include "t_network.h"

#include "t_dataphase_xml.h"

#include "t_locale.h"
#include "t_namespace.h"
#include "t_ui_canvas.h"

#include "t_render_imagework.h"
#include "t_render2d.h"
#include "t_render3d.h"
#include "t_render_ddraw.h"
#include "t_render_gdiplus.h"
#include "t_render_dx9.h"
#include "t_render_dx10.h"
#include "t_render_dx11.h"
#include "t_render_gl1.h"
#include "t_render_gl2.h"
#include "t_render_gl3.h"
#include "t_render_gles1.h"
#include "t_render_gles2.h"
#include "t_render_gles3.h"

namespace GAIA_TEST
{
	GINL GAIA::N32 t_all(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CTN::AString str;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("MathArithmatic: Basic test begin!"); nRet += t_math_arithmatic_basic(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathArithmatic: Lerp test begin!"); nRet += t_math_arithmatic_lerp(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathArithmatic: Random test begin!"); nRet += t_math_arithmatic_random(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("MathCookies: ARGB test begin!"); nRet += t_math_cookies_argb(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: NRGB test begin!"); nRet += t_math_cookies_nrgb(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: AABB test begin!"); nRet += t_math_cookies_aabb(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: AABR test begin!"); nRet += t_math_cookies_aabr(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: VEC2 test begin!"); nRet += t_math_cookies_vec2(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: VEC3 test begin!"); nRet += t_math_cookies_vec3(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: VEC4 test begin!"); nRet += t_math_cookies_vec4(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX22 test begin!"); nRet += t_math_cookies_mtx22(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX33 test begin!"); nRet += t_math_cookies_mtx33(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX44 test begin!"); nRet += t_math_cookies_mtx44(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX43 test begin!"); nRet += t_math_cookies_mtx43(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: QUA test begin!"); nRet += t_math_cookies_qua(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Algorithm: Set test begin!"); nRet += t_algorithm_set(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Container: Buffer test begin!"); nRet += t_container_buffer(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Ptr test begin!"); nRet += t_container_ptr(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Ref test begin!"); nRet += t_container_ref(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Array test begin!"); nRet += t_container_array(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Vector test begin!"); nRet += t_container_vector(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: ArrayVector test begin!"); nRet += t_container_arrayvector(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackStack test begin!"); nRet += t_container_stackstack(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Stack test begin!"); nRet += t_container_stack(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackQueue test begin!"); nRet += t_container_stackqueue(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Queue test begin!"); nRet += t_container_queue(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: List test begin!"); nRet += t_container_list(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Chars test begin!"); nRet += t_container_chars(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: String test begin!"); nRet += t_container_string(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StackBitset test begin!"); nRet += t_container_stackbitset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Bitset test begin!"); nRet += t_container_bitset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: TrieTree test begin!"); nRet += t_container_trietree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: AVLTree test begin!"); nRet += t_container_avltree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Set test begin!"); nRet += t_container_set(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Map test begin!"); nRet += t_container_map(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiAVLTree test begin!"); nRet += t_container_multiavltree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiSet test begin!"); nRet += t_container_multiset(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: MultiMap test begin!"); nRet += t_container_multimap(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Tree test begin!"); nRet += t_container_tree(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Orderless test begin!"); nRet += t_container_orderless(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Book test begin!"); nRet += t_container_book(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Pool test begin!"); nRet += t_container_pool(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Graph test begin!"); nRet += t_container_graph(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Storage test begin!"); nRet += t_container_storage(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: Accesser test begin!"); nRet += t_container_accesser(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StringPool test begin!"); nRet += t_container_stringpool(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Container: StaticStringPool test begin!"); nRet += t_container_staticstringpool(file, prt); GTLINE1("End"); GTLINE("\t");	
			GTLINE1("Container: Cooperate test begin!"); nRet += t_container_cooperate(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Time: Time test begin!"); nRet += t_time_time(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("File: File test begin!"); nRet += t_filesystem_file(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("File: Directory test begin!"); nRet += t_filesystem_directory(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("File: Network test begin!"); nRet += t_network(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("DataPhase: XML test begin!"); nRet += t_dataphase_xml(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Locale test begin!"); nRet += t_locale(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Namespace test begin!"); nRet += t_namespace(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("UI: Canvas test begin!"); nRet += t_ui_canvas(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Render: ImageWork test begin!"); nRet += t_render_imagework(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: DDraw test begin!"); nRet += t_render_ddraw(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gdiplus test begin!"); nRet += t_render_gdiplus(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: dx9 test begin!"); nRet += t_render_dx9(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: dx10 test begin!"); nRet += t_render_dx10(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: dx11 test begin!"); nRet += t_render_dx11(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gl1 test begin!"); nRet += t_render_gl1(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gl2 test begin!"); nRet += t_render_gl2(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gl3 test begin!"); nRet += t_render_gl3(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gles1 test begin!"); nRet += t_render_gles1(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gles2 test begin!"); nRet += t_render_gles2(file, prt); GTLINE1("End"); GTLINE("\t");
			//GTLINE1("Render: gles3 test begin!"); nRet += t_render_gles3(file, prt); GTLINE1("End"); GTLINE("\t");
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
