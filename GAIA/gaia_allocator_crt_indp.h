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
			m_capacity.Add(uSize + sizeof(GAIA::UM));
			m_usesize.Add(uSize);
			m_piecesize.Increase();
			return ((GAIA::UM*)pRet) + 1;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID AllocatorCRT::memory_release(GAIA::GVOID* p)
		{
			GAIA_AST(!!p);
			m_capacity.Add(-(GAIA::N64)this->memory_size(p) - (GAIA::N64)sizeof(GAIA::UM));
			m_usesize.Add(-(GAIA::N64)this->memory_size(p));
			m_piecesize.Decrease();
			delete[] (GAIA::U8*)((GAIA::UM*)p - 1);
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::memory_size(GAIA::GVOID* p)
		{
			GAIA_AST(!!p);
			return *((GAIA::UM*)p - 1);
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::capacity()
		{
			return m_capacity;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::size()
		{
			return m_capacity;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::use_size()
		{
			return m_usesize;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorCRT::piece_size()
		{
			return m_piecesize;
		}
	};
};

#endif
