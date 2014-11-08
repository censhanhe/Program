#ifndef		__T_GAIA_HEADER_H__
#define		__T_GAIA_HEADER_H__

#include "t_common.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_type(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_math_arithmatic_basic(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_arithmatic_lerp(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_arithmatic_random(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_math_cookies_argb(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_nrgb(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_vec2(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_vec3(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_vec4(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_mtx22(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_mtx33(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_mtx32(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_mtx44(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_mtx43(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_qua(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_aabb(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_math_cookies_aabr(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_algorithm_set(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_container_vari(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_buffer(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_ptr(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_ref(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_array(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_vector(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_arrayvector(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_stackstack(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_stack(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_stackqueue(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_queue(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_list(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_chars(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_string(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_charsstring(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_stackbitset(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_bitset(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_trietree(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_avltree(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_set(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_map(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_multiavltree(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_multiset(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_multimap(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_tree(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_orderless(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_book(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_graph(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_pool(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_storage(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_accesser(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_stringpool(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_staticstringpool(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_container_cooperate(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_print_printstring(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_time_time(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_sync_atomic(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_sync_event(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_sync_lock(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_sync_mutex(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_thread_thread(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_filesystem_file(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_filesystem_directory(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_log_log(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_network(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_dataphase_xml(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_locale(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_namespace(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_timer_timer(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_ui_message(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_ui_canvas(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	extern GAIA::N32 t_render_imagework(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_ddraw(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gdiplus(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_dx9(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_dx10(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_dx11(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gl1(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gl2(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gl3(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gles1(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gles2(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);
	extern GAIA::N32 t_render_gles3(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt);

	GINL GAIA::N32 t_all(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		GAIA::BL bOutputTime = GAIA::False;
		GAIA::U64 uTimeBegin = 0, uTimeEnd = 0;
		GAIA::CTN::AString str;

		// Every test procedure.
		GTLINE("[GAIA TEST BEGIN]");
		{
			GTLINE1("Type: Type test begin!"); nRet += t_type(file, prt); GTLINE1("End"); GTLINE("\t");

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
			GTLINE1("MathCookies: MTX32 test begin!"); nRet += t_math_cookies_mtx32(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX44 test begin!"); nRet += t_math_cookies_mtx44(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: MTX43 test begin!"); nRet += t_math_cookies_mtx43(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("MathCookies: QUA test begin!"); nRet += t_math_cookies_qua(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Algorithm: Set test begin!"); nRet += t_algorithm_set(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Container: Vari test begin!"); nRet += t_container_vari(file, prt); GTLINE1("End"); GTLINE("\t");
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
			GTLINE1("Container: CharsString test begin!"); nRet += t_container_charsstring(file, prt); GTLINE1("End"); GTLINE("\t");
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

			GTLINE1("Print: PrintString test begin!"); nRet += t_print_printstring(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Time: Time test begin!"); nRet += t_time_time(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Sync: Atomic test begin!"); nRet += t_sync_atomic(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Sync: Event test begin!"); nRet += t_sync_event(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Sync: Lock test begin!"); nRet += t_sync_lock(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Sync: Mutex test begin!"); nRet += t_sync_mutex(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Thread: Thread test begin!"); nRet += t_thread_thread(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("File: File test begin!"); nRet += t_filesystem_file(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("File: Directory test begin!"); nRet += t_filesystem_directory(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("File: Log test begin!"); nRet += t_log_log(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("File: Network test begin!"); nRet += t_network(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("DataPhase: XML test begin!"); nRet += t_dataphase_xml(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Locale test begin!"); nRet += t_locale(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Namespace test begin!"); nRet += t_namespace(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Timer: Timer test begin!"); nRet += t_timer_timer(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("UI: Message test begin!"); nRet += t_ui_message(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("UI: Canvas test begin!"); nRet += t_ui_canvas(file, prt); GTLINE1("End"); GTLINE("\t");

			GTLINE1("Render: ImageWork test begin!"); nRet += t_render_imagework(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: DDraw test begin!"); nRet += t_render_ddraw(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gdiplus test begin!"); nRet += t_render_gdiplus(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: dx9 test begin!"); nRet += t_render_dx9(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: dx10 test begin!"); nRet += t_render_dx10(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: dx11 test begin!"); nRet += t_render_dx11(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gl1 test begin!"); nRet += t_render_gl1(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gl2 test begin!"); nRet += t_render_gl2(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gl3 test begin!"); nRet += t_render_gl3(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gles1 test begin!"); nRet += t_render_gles1(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gles2 test begin!"); nRet += t_render_gles2(file, prt); GTLINE1("End"); GTLINE("\t");
			GTLINE1("Render: gles3 test begin!"); nRet += t_render_gles3(file, prt); GTLINE1("End"); GTLINE("\t");
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
