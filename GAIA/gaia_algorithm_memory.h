#ifndef		__GAIA_ALGORITHM_MEMORY_H__
#define		__GAIA_ALGORITHM_MEMORY_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _SizeType> GINL GAIA::GVOID* memcpy(GAIA::GVOID* dst, const GAIA::GVOID* src, const _SizeType& size)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			GAIA_ASSERT(size != 0);
			GAIA::GVOID* pRet = dst;
			while(size > sizeof(GAIA::UM))
			{
				*(GAIA::UM*)dst = *(GAIA::UM*)src;
				dst = ((GAIA::UM*)dst) + 1;
				src = ((GAIA::UM*)src) + 1;
				size -= sizeof(GAIA::UM);
			}
			while(size > 0)
			{
				*(GAIA::U8*)dst = *(GAIA::U8*)src;
				dst = ((GAIA::U8*)dst) + 1;
				src = ((GAIA::U8*)src) + 1;
				size -= sizeof(GAIA::U8);
			}
			return pRet;
		}
		template <typename _SizeType> GINL GAIA::GVOID* memset(GAIA::GVOID* dst, GAIA::N8 ch, const _SizeType& size)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			GAIA_ASSERT(size != 0);
			GAIA::UM clean = 0;
			for(N32 c = 0; c < sizeof(GAIA::UM) / sizeof(GAIA::N8); c++)
				clean |= (ch << (c * 8));
			GAIA::GVOID* pRet = dst;
			while(size > sizeof(GAIA::UM))
			{
				*(GAIA::UM*)dst = (GAIA::UM)clean;
				dst = ((GAIA::UM*)dst) + 1;
				size -= sizeof(GAIA::UM);
			}
			while(size > 0)
			{
				*(GAIA::U8*)dst = (GAIA::U8)clean;
				dst = ((GAIA::U8*)dst) + 1;
				size -= sizeof(GAIA::U8);
			}
			return pRet;
		}
		template <typename _SizeType> GINL GAIA::N32 memcmp(const GAIA::GVOID* p1, const GAIA::GVOID* p2, const _SizeType& size)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			GAIA_ASSERT(size != 0);
			while(size > sizeof(GAIA::UM))
			{
				if(*((GAIA::UM*)p1) < *((GAIA::UM*)p2))
					return +1;
				else if(*((GAIA::UM*)p1) > *((GAIA::UM*)p2))
					return -1;
				size -= sizeof(GAIA::UM);
			}
			while(size > sizeof(GAIA::U8))
			{
				if(*((GAIA::U8*)p1) < *((GAIA::U8*)p2))
					return +1;
				else if(*((GAIA::U8*)p1) > *((GAIA::U8*)p2))
					return -1;			
				size -= sizeof(GAIA::U8);
			}
			return 0;
		}
	}
};

#endif
