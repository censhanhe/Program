#ifndef		__GAIA_TYPE_IMPL_H__
#define		__GAIA_TYPE_IMPL_H__

namespace GAIA
{
#ifndef GAIA_DEBUG_MEMORYLEAK
	GINL GAIA::GVOID* Base::operator new(size_t size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
	GINL GAIA::GVOID Base::operator delete(GAIA::GVOID* p){return g_global_allocator.memory_release(p);}
	GINL GAIA::GVOID* Base::operator new[] (size_t size){return g_global_allocator.memory_alloc((GAIA::UM)size);}
	GINL GAIA::GVOID Base::operator delete[](GAIA::GVOID* p){return g_global_allocator.memory_release(p);}
#endif
};

#endif