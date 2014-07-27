#ifndef		__GAIA_ALGORITHM_MEMORY_H__
#define		__GAIA_ALGORITHM_MEMORY_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _SizeType> GAIA::GVOID* xmemcpy(GAIA::GVOID* dst, const GAIA::GVOID* src, const _SizeType& size)
		{
			GAIA_AST(!!dst);
			GAIA_AST(!!src);
			GAIA_AST(size > 0);
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
		template<typename _SizeType> GAIA::GVOID* xmemcpy(GAIA::GVOID* dst, const GAIA::GVOID* src, const _SizeType& dst_stride, const _SizeType& src_stride, const _SizeType& size, const _SizeType& count)
		{
			GAIA_AST(!!dst);
			GAIA_AST(!!src);
			GAIA_AST(dst_stride > 0);
			GAIA_AST(src_stride > 0);
			GAIA_AST(dst_stride <= src_stride);
			GAIA_AST(size > 0);
			GAIA_AST(count > 0);
			GAIA::U8* pDst = (GAIA::U8*)dst;
			const GAIA::U8* pSrc = (const GAIA::U8*)src;
			while(count > 0)
			{
				GAIA::ALGORITHM::xmemcpy(pDst, pSrc, size);
				pDst += dst_stride;
				pSrc += src_stride;
				--count;
			}
			return dst;
		}
		template<typename _FillType, typename _SizeType> GAIA::GVOID* xmemset(GAIA::GVOID* dst, const _FillType& ch, const _SizeType& size)
		{
			GAIA_AST(!!dst);
			GAIA_AST(size > 0);
			GAIA::UM clean = 0;
			for(GAIA::U32 c = 0; c < sizeof(GAIA::UM) / sizeof(GAIA::N8); c++)
				clean |= (((GAIA::UM)ch) << (c * 8));
			_SizeType sizet = size;
			GAIA::GVOID* pRet = dst;
			while(sizet > sizeof(GAIA::UM))
			{
				*(GAIA::UM*)dst = (GAIA::UM)clean;
				dst = ((GAIA::UM*)dst) + 1;
				sizet = sizet - (_SizeType)sizeof(GAIA::UM);
			}
			while(sizet > 0)
			{
				*(GAIA::U8*)dst = (GAIA::U8)ch;
				dst = ((GAIA::U8*)dst) + 1;
				sizet = sizet - (_SizeType)sizeof(GAIA::U8);
			}
			return pRet;
		}
		template<typename _FillType, typename _SizeType> GAIA::GVOID* xmemset(GAIA::GVOID* dst, const _FillType& ch, const _SizeType& stride, const _SizeType& size, const _SizeType& count)
		{
			GAIA_AST(!!dst);
			GAIA_AST(stride > 0);
			GAIA_AST(size > 0);
			GAIA_AST(count > 0);
			GAIA::U8* p = (GAIA::U8*)dst;
			while(count > 0)
			{
				GAIA::ALGORITHM::xmemset(p, ch, size);
				p += stride;
				--count;
			}
			return dst;
		}
		template<typename _CheckType, typename _SizeType> GAIA::N32 xmemcheck(const GAIA::GVOID* p, const _CheckType& ch, const _SizeType& size)
		{
			GAIA_AST(!!p);
			GAIA_AST(size > 0);
			GAIA::UM clean = 0;
			for(GAIA::U32 c = 0; c < sizeof(GAIA::UM) / sizeof(GAIA::N8); c++)
				clean |= (((GAIA::UM)ch) << (c * 8));
			_SizeType sizet = size;
			while(sizet > sizeof(GAIA::UM))
			{
				if(*(GAIA::UM*)p < (GAIA::UM)clean)
					return -1;
				else if(*(GAIA::UM*)p > (GAIA::UM)clean)
					return +1;
				p = ((GAIA::UM*)p) + 1;
				sizet = sizet - (_SizeType)sizeof(GAIA::UM);
			}
			while(sizet > 0)
			{
				if(*(GAIA::U8*)p < (GAIA::U8)ch)
					return -1;
				else if(*(GAIA::U8*)p > (GAIA::U8)ch)
					return +1;
				p = ((GAIA::U8*)p) + 1;
				sizet = sizet - (_SizeType)sizeof(GAIA::U8);
			}
			return 0;
		}
		template<typename _CheckType, typename _SizeType> GAIA::N32 xmemcheck(const GAIA::GVOID* p, const _CheckType& ch, const _SizeType& stride, const _SizeType& size, const _SizeType& count)
		{
			GAIA_AST(!!p);
			GAIA_AST(stride > 0);
			GAIA_AST(size > 0);
			GAIA_AST(count > 0);
			const GAIA::U8* pTemp = (const GAIA::U8*)p;
			while(count > 0)
			{
				GAIA::N32 res = GAIA::ALGORITHM::xmemcheck(pTemp, ch, size);
				if(res != 0)
					return res;
				pTemp += stride;
				--count;
			}
			return 0;
		}
		template<typename _SizeType> GAIA::N32 xmemcmp(const GAIA::GVOID* p1, const GAIA::GVOID* p2, const _SizeType& size)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			GAIA_AST(size > 0);
			_SizeType sizet = size;
			while(sizet > sizeof(GAIA::UM))
			{
				if(*((GAIA::UM*)p1) < *((GAIA::UM*)p2))
					return +1;
				else if(*((GAIA::UM*)p1) > *((GAIA::UM*)p2))
					return -1;
				p1 = ((GAIA::UM*)p1) + 1;
				p2 = ((GAIA::UM*)p2) + 1;
				sizet -= sizeof(GAIA::UM);
			}
			while(sizet > sizeof(GAIA::U8))
			{
				if(*((GAIA::U8*)p1) < *((GAIA::U8*)p2))
					return +1;
				else if(*((GAIA::U8*)p1) > *((GAIA::U8*)p2))
					return -1;
				p1 = ((GAIA::U8*)p1) + 1;
				p2 = ((GAIA::U8*)p2) + 1;
				sizet -= sizeof(GAIA::U8);
			}
			return 0;
		}
		template<typename _SizeType> GAIA::N32 xmemcmp(const GAIA::GVOID* p1, const GAIA::GVOID* p2, const _SizeType& p1_stride, const _SizeType& p2_stride, const _SizeType& size, const _SizeType& count)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			GAIA_AST(p1_stride > 0);
			GAIA_AST(p2_stride > 0);
			GAIA_AST(size > 0);
			GAIA_AST(count > 0);
			const GAIA::U8* pA = (const GAIA::U8*)p1;
			const GAIA::U8* pB = (const GAIA::U8*)p2;
			while(count > 0)
			{
				GAIA::N32 nCmp = GAIA::ALGORITHM::xmemcmp(pA, pB, size);
				if(nCmp != 0)
					return nCmp;
				pA += p1_stride;
				pB += p2_stride;
				--count;
			}
			return 0;
		}
	}
};

#endif
