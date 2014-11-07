#ifndef		__GAIA_INTERNAL_H__
#define		__GAIA_INTERNAL_H__

namespace GAIA_INTERNAL_NAMESPACE
{
	template<typename _SizeType> GAIA::GVOID* memcpy(GAIA::GVOID* dst, const GAIA::GVOID* src, const _SizeType& size)
	{
		_SizeType sizet = size;
		GAIA::GVOID* pRet = dst;
		while(sizet > sizeof(GAIA::UM))
		{
			*(GAIA::UM*)dst = *(GAIA::UM*)src;
			dst = ((GAIA::UM*)dst) + 1;
			src = ((GAIA::UM*)src) + 1;
			sizet -= sizeof(GAIA::UM);
		}
		while(sizet > 0)
		{
			*(GAIA::U8*)dst = *(GAIA::U8*)src;
			dst = ((GAIA::U8*)dst) + 1;
			src = ((GAIA::U8*)src) + 1;
			sizet -= sizeof(GAIA::U8);
		}
		return pRet;
	}
	template<typename _DataType> GAIA::SIZE strlen(const _DataType* p){GAIA::SIZE ret = 0; while(p[ret] != 0) ret++; return ret;}
	template<typename _DataType> _DataType* strcpy(_DataType* dst, const _DataType* src)
	{
		_DataType* ret = dst;
		while(*src != 0)
		{
			*dst = *src;
			++dst;
			++src;
		}
		*dst = 0;
		return ret;
	}
	template<typename _DataType> GAIA::N32 strcmp(const _DataType* p1, const _DataType* p2)
	{
		for(;;)
		{
			if(*p1 < *p2)
				return -1;
			else if(*p1 > *p2)
				return +1;
			else
			{
				if(*p1 == 0)
					return 0;
				++p1;
				++p2;
			}
		}
	#if GAIA_COMPILER != GAIA_COMPILER_CL // For CL C4702 Warning.
		return 0;
	#endif
	}
};

#endif
