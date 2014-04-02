#ifndef		__GAIA_ALLOCATOR_CRT_INDP_H__
#define		__GAIA_ALLOCATOR_CRT_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace ALLOCATOR
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID* AllocatorCRT::memory_alloc(const GAIA::UM& uSize)
		{
			GAIA_AST(uSize > 0);
			GAIA::GVOID* pRet = new GAIA::U8[uSize + sizeof(GAIA::UM)];
			*((GAIA::UM*)pRet) = uSize;
			return ((GAIA::UM*)pRet) + 1;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID AllocatorCRT::memory_release(GAIA::GVOID* p)
		{
			GAIA_AST(p != GNULL);
			delete[] (GAIA::U8*)((GAIA::UM*)p - 1);
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::memory_size(GAIA::GVOID* p)
		{
			GAIA_AST(p != GNULL);
			return *((GAIA::UM*)p - 1);
		}
	};
};

#endif
