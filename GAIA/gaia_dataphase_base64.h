#ifndef		__GAIA_DATAPHASE_BASE64_H__
#define		__GAIA_DATAPHASE_BASE64_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		GINL GAIA::SIZE Char2Base64(GAIA::CH* pDst, GAIA::SIZE dstlen, const GAIA::CH* pSrc, GAIA::SIZE srclen)
		{
			GPCHR_NULL_RET(pDst, 0);
			GPCHR_NULL_RET(pSrc, 0);
			GPCHR_NULL_RET(dstlen, 0);
			GPCHR_NULL_RET(srclen, 0);
			GAIA_AST(dstlen >= srclen * 2 + 4);
			if(dstlen < srclen * 2 + 4)
				return 0;
			static const GAIA::CH BASE64ENCODE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			GAIA::CH* pOldDst = pDst;
			GAIA::N32 point = 2;
			GAIA::N32 index = 0;
			GAIA::CH n = 0;
			for(GAIA::SIZE x = 0;x < srclen;x++)
			{
				if(point == 2)
					index = ((*pSrc) >> point) & 0x3F;
				else if (point == 4)
					index = ((*pSrc) >> point) & 0xF;
				else if(point == 6)
					index = ((*pSrc) >> point) & 0x3;
				index += n;
				*pDst++ = BASE64ENCODE[index];
				n = ((*pSrc) << (6 - point));
				n = n & 0x3f;
				point += 2;
				if(point == 8)
				{
					index = (*pSrc) & 0x3F;
					*pDst++ = BASE64ENCODE[index];
					n = 0;
					point = 2;
				}
				pSrc++;
			}
			if(n != 0)
				*pDst++ = BASE64ENCODE[n];
			if(srclen % 3 == 2)
				*pDst++ = '=';
			else if(srclen % 3 == 1)
			{
				*pDst++ = '=';
				*pDst++ = '=';
			}
			return (GAIA::SIZE)(pDst - pOldDst);
		}
	};
};

#endif