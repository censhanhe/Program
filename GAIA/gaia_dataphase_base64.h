#ifndef		__GAIA_DATAPHASE_BASE64_H__
#define		__GAIA_DATAPHASE_BASE64_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _DataType, typename _SizeType> _SizeType Char2Base64(_DataType* pDst, _SizeType dstlen, const _DataType* pSrc, _SizeType srclen)
		{
			GPCHR_NULL_RET(pDst, 0);
			GPCHR_NULL_RET(pSrc, 0);
			GPCHR_NULL_RET(dstlen, 0);
			GPCHR_NULL_RET(srclen, 0);
			GAIA_AST(dstlen >= srclen * 2 + 4);
			if(dstlen < srclen * 2 + 4)
				return 0;
			static const _DataType BASE64ENCODE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			_DataType* pOldDst = pDst;
			GAIA::N32 point = 2;
			GAIA::N32 index = 0;
			_DataType n = 0;
			for(_SizeType x = 0;x < srclen;x++)
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
				n = n & 0x3F;
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
			return (_SizeType)(pDst - pOldDst);
		}
	};
};

#endif
