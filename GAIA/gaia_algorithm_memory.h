#ifndef		__GAIA_ALGORITHM_MEMORY_H__
#define		__GAIA_ALGORITHM_MEMORY_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _SizeType> GINL GAIA::GVOID* memcpy(GAIA::GVOID* dst, const GAIA::GVOID* src, _SizeType size)
		{
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
		template <typename _SizeType> GINL GAIA::GVOID* memset(GAIA::GVOID* dst, GAIA::N8 ch, _SizeType size)
		{
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
	}
};

#endif