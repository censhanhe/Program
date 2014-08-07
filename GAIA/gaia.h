#ifndef		__GAIA_H__
#define		__GAIA_H__

/* Include file header. */
#include	"gaia_sysconfig.h"
#include	"gaia_macrohelper.h"
#include	"gaia_type.h"
#include	"gaia_type_convert.h"
#include	"gaia_type_traits2.h"
#include	"gaia_internal.h"

#include	"gaia_print_format.h"
#include	"gaia_print.h"
#include	"gaia_assert.h"
#include	"gaia_error.h"

#include	"gaia_system.h"

#include	"gaia_sync_base.h"
#include	"gaia_sync_atomic.h"
#include	"gaia_sync_lock.h"
#include 	"gaia_sync_autolock.h"
#include	"gaia_sync_event.h"
#include	"gaia_sync_mutex.h"

#include	"gaia_locale.h"

#include	"gaia_math_basic.h"
#include 	"gaia_math_random.h"
#include 	"gaia_math_lerp.h"

#include	"gaia_allocator.h"
#include	"gaia_allocator_crt.h"
#include	"gaia_allocator_esg.h"

#include	"gaia_type_impl.h"

#include	"gaia_iterator.h"

#include	"gaia_algorithm_base.h"
#include	"gaia_algorithm_compare.h"
#include	"gaia_algorithm_memory.h"
#include	"gaia_algorithm_sizeincreaser.h"
#include	"gaia_algorithm_string.h"
#include 	"gaia_algorithm_search.h"
#include 	"gaia_algorithm_sort.h"
#include 	"gaia_algorithm_unique.h"
#include	"gaia_algorithm_replace.h"
#include	"gaia_algorithm_set.h"

#include 	"gaia_container_datarecord.h"
#include 	"gaia_container_ref.h"
#include	"gaia_container_ptr.h"
#include	"gaia_container_pair.h"
#include 	"gaia_container_basicstackbitset.h"
#include 	"gaia_container_stackbitset.h"
#include 	"gaia_container_basicbitset.h"
#include 	"gaia_container_bitset.h"
#include 	"gaia_container_basicchars.h"
#include 	"gaia_container_chars.h"
#include	"gaia_container_basicstring.h"
#include	"gaia_container_wstring.h"
#include	"gaia_container_astring.h"
#include	"gaia_container_tstring.h"
#include 	"gaia_container_basicstackstack.h"
#include	"gaia_container_stackstack.h"
#include	"gaia_container_basicstack.h"
#include	"gaia_container_stack.h"
#include	"gaia_container_basicarray.h"
#include	"gaia_container_array.h"
#include	"gaia_container_basicvector.h"
#include	"gaia_container_vector.h"
#include	"gaia_container_basicarrayvector.h"
#include	"gaia_container_arrayvector.h"
#include	"gaia_container_basicstackqueue.h"
#include	"gaia_container_stackqueue.h"
#include	"gaia_container_basicqueue.h"
#include	"gaia_container_queue.h"
#include	"gaia_container_basicbuffer.h"
#include 	"gaia_container_buffer.h"
#include	"gaia_container_basicorderless.h"
#include	"gaia_container_orderless.h"
#include 	"gaia_container_basicpool.h"
#include 	"gaia_container_pool.h"
#include 	"gaia_container_basiclist.h"
#include 	"gaia_container_list.h"
#include 	"gaia_container_basicavltree.h"
#include	"gaia_container_basicmultiavltree.h"
#include 	"gaia_container_basictrietree.h"
#include 	"gaia_container_basickdtree.h"
#include 	"gaia_container_basicksvdtree.h"
#include 	"gaia_container_basictree.h"
#include 	"gaia_container_basicpriqueue.h"
#include	"gaia_container_basicmultipriqueue.h"
#include 	"gaia_container_basicset.h"
#include 	"gaia_container_set.h"
#include	"gaia_container_basicmap.h"
#include 	"gaia_container_map.h"
#include	"gaia_container_basicmultiset.h"
#include	"gaia_container_multiset.h"
#include	"gaia_container_basicmultimap.h"
#include	"gaia_container_multimap.h"
#include	"gaia_container_basicgraph.h"
#include 	"gaia_container_basicnet.h"
#include	"gaia_container_basicdictionary.h"
#include	"gaia_container_basicheap.h"
#include	"gaia_container_storage.h"
#include 	"gaia_container_vari.h"
#include	"gaia_container_cooperation.h"

#include	"gaia_time.h"

#include	"gaia_thread.h"
#include 	"gaia_thread_pool.h"
#include	"gaia_process.h"

#include 	"gaia_math_rid.h"
#include	"gaia_math_coord.h"

#include	"gaia_math_vec2.h"
#include	"gaia_math_vec3.h"
#include	"gaia_math_vec4.h"
#include	"gaia_math_qua.h"
#include	"gaia_math_mtx22.h"
#include	"gaia_math_mtx33.h"
#include	"gaia_math_mtx34.h"
#include	"gaia_math_mtx44.h"
#include	"gaia_math_plane.h"
#include	"gaia_math_aabr.h"
#include	"gaia_math_aabb.h"
#include	"gaia_math_argb.h"
#include	"gaia_math_rgb.h"

#include	"gaia_datamodel.h"
#include	"gaia_linkmodel.h"

#include	"gaia_file.h"
#include	"gaia_directory.h"
#include	"gaia_log.h"

#include	"gaia_container_accesser.h"

#include	"gaia_dataphase_xml.h"
#include 	"gaia_dataphase_bdiff.h"
#include 	"gaia_dataphase_tdiff.h"
#include 	"gaia_dataphase_crc.h"
#include	"gaia_dataphase_base64.h"

#include	"gaia_network.h"

#include	"gaia_framework.h"
#include	"gaia_id.h"
#include	"gaia_hd.h"
#include	"gaia_clsid.h"
#include	"gaia_instance.h"

#include 	"gaia_io_io.h"
#include 	"gaia_io_fileio.h"
#include 	"gaia_io_memio.h"
#include	"gaia_io_screenio.h"

#include	"gaia_serialize_serializeproc.h"
#include 	"gaia_serialize_serializer.h"
#include	"gaia_serialize_serializeproc_impl.h"

#include	"gaia_datatraffic_gateway.h"
#include	"gaia_datatraffic_route.h"
#include	"gaia_datatraffic_transmission.h"
#include	"gaia_datatraffic_gateway_impl.h"
#include	"gaia_datatraffic_route_impl.h"

#include	"gaia_datatraffic_gateway_mem.h"
#include	"gaia_datatraffic_gateway_file.h"
#include	"gaia_datatraffic_gateway_sharemem.h"
#include	"gaia_datatraffic_route_mem.h"
#include	"gaia_datatraffic_route_net.h"
#include	"gaia_datatraffic_transmission_idm.h"

#include 	"gaia_render_vertexbuffer.h"
#include 	"gaia_render_indexbuffer.h"
#include 	"gaia_render_texture.h"
#include	"gaia_render_target.h"
#include	"gaia_render_context.h"
#include 	"gaia_render_render.h"
#include 	"gaia_render_gl1.h"
#include 	"gaia_render_gl2.h"
#include 	"gaia_render_gl3.h"
#include 	"gaia_render_dx9.h"
#include 	"gaia_render_dx10.h"
#include 	"gaia_render_dx11.h"
#include	"gaia_render_gdiplus.h"
#include	"gaia_render_ddraw.h"

#include	"gaia_mvc_viewlinker.h"
#include	"gaia_mvc_model.h"
#include	"gaia_mvc_controller.h"
#include	"gaia_mvc_view.h"
#include	"gaia_mvc_viewlinker_impl.h"

#include	"gaia_collisioner.h"

#include	"gaia_ui_convas.h"
#include	"gaia_ui_convasmsgdisp.h"

#include	"gaia_painter.h"

#include	"gaia_ui_form.h"
#include	"gaia_ui_pushbutton.h"
#include	"gaia_ui_checkbutton.h"
#include	"gaia_ui_radiobutton.h"
#include	"gaia_ui_label.h"
#include	"gaia_ui_edit.h"
#include	"gaia_ui_document.h"
#include	"gaia_ui_progressbar.h"

#include	"gaia_layout_widget.h"
#include	"gaia_layout.h"

#include	"gaia_factory.h"

/*
*	The following header files will been included by gaia's user manually.
*	The user will include these header files by his choose.
*
*	[gaia_global_impl.h]
*		gaia is designed as a header file based source code
*		library, so gaia not exist any global variables. but unfortunately,
*		gaia need some basic global variable, for example : global-allocator.
*		So, if you want use this function, include this header file after
*		include gaia.h, or will change gaia's source code for compile errors.
*
*	[gaia_using_namespace.h]
*		include this file will cause all gaia namespace been used.
*		WARNING! gaia's namespace will protect gaia source code
*		library's symbol been declaration as unique symbol. if you
*		want to implement a high quality program, please NOT include
*		this header file(RECOMMANDED).
*/

#endif
