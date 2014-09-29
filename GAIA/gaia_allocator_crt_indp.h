#ifndef		__GAIA_ALLOCATOR_CRT_INDP_H__
#define		__GAIA_ALLOCATOR_CRT_INDP_H__

#include <stdlib.h>

namespace GAIA
{
	namespace ALLOCATOR
	{
		GINL GAIA::GVOID* AllocatorCRT::memory_alloc(const GAIA::UM& uSize)
		{
			GAIA_AST(uSize > 0);
			GAIA::GVOID* pRet = new GAIA::U8[uSize + sizeof(GAIA::UM)];
			*(GSCAST(GAIA::UM*)(pRet)) = uSize;
			m_capacity.Add(uSize + sizeof(GAIA::UM));
			m_usesize.Add(uSize);
			m_piecesize.Increase();
			m_alloctimes.Increase();
			return (GSCAST(GAIA::UM*)(pRet)) + 1;
		}
		GINL GAIA::GVOID AllocatorCRT::memory_release(GAIA::GVOID* p)
		{
			GAIA_AST(!!p);
			m_capacity.Add(-(GAIA::N64)this->memory_size(p) - (GAIA::N64)sizeof(GAIA::UM));
			m_usesize.Add(-(GAIA::N64)this->memory_size(p));
			m_piecesize.Decrease();
			delete[] GRCAST(GAIA::U8*)(GSCAST(GAIA::UM*)(p) - 1);
		}
		GINL GAIA::UM AllocatorCRT::memory_size(GAIA::GVOID* p)
		{
			GAIA_AST(!!p);
			return *(GSCAST(GAIA::UM*)(p) - 1);
		}
		GINL GAIA::UM AllocatorCRT::capacity()
		{
			return m_capacity;
		}
		GINL GAIA::UM AllocatorCRT::size()
		{
			return m_capacity;
		}
		GINL GAIA::UM AllocatorCRT::use_size()
		{
			return m_usesize;
		}
		GINL GAIA::UM AllocatorCRT::piece_size()
		{
			return m_piecesize;
		}
		GINL GAIA::U64 AllocatorCRT::alloc_times()
		{
			return m_alloctimes;
		}
	};
};

#endif
