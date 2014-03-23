#ifndef		__GAIA_TYPE_IMPL_H__
#define		__GAIA_TYPE_IMPL_H__

namespace GAIA
{
#ifndef GAIA_DEBUG_MEMORYLEAK
#	if GAIA_OS == GAIA_OS_WINDOWS
	GINL GAIA::GVOID* Base::operator new(size_t size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
	GINL GAIA::GVOID* Base::operator new[](size_t size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
#	else
	GINL GAIA::GVOID* Base::operator new(GAIA::UM size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
	GINL GAIA::GVOID* Base::operator new[](GAIA::UM size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
#	endif
	GINL GAIA::GVOID Base::operator delete(GAIA::GVOID* p){return g_global_allocator.memory_release(p);}
	GINL GAIA::GVOID Base::operator delete[](GAIA::GVOID* p){return g_global_allocator.memory_release(p);}
#endif
};

#endif