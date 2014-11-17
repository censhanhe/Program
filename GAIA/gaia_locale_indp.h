#ifndef		__GAIA_LOCALE_INDP_H__
#define		__GAIA_LOCALE_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <xlocale>
#else
#	include <iconv.h>
#endif

namespace GAIA
{
	namespace LOCALE
	{
		GINL GAIA::SIZE m2w(const GAIA::CH* pszSrc, GAIA::WCH* pszDst, GAIA::SIZE dst_size_in_wchar, GAIA::CHARSET_TYPE charset_type)
		{
			GAIA_AST(charset_type < GAIA::CHARSET_TYPE_MAXENUMCOUNT);
			if(charset_type >= GAIA::CHARSET_TYPE_MAXENUMCOUNT)
				return 0;
			if(charset_type == GAIA::CHARSET_TYPE_ASCII)
			{
				GAIA::SIZE ret = 0;
				for(;;)
				{
					if(pszDst != GNIL && dst_size_in_wchar != 0)
					{
						if(ret >= dst_size_in_wchar)
							break;
						pszDst[ret] = GSCAST(GAIA::WCH)(pszSrc[ret]);
					}
					if(pszSrc[ret] == '\0')
					{
						++ret;
						break;
					}
					++ret;
				}
				return ret;
			}
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::U32 uCodePage;
			if(charset_type == GAIA::CHARSET_TYPE_SYS)
				uCodePage = CP_OEMCP;
			else
				uCodePage = GAIA::CHARSET_CODEPAGE[charset_type];
			return ::MultiByteToWideChar(uCodePage, 0, pszSrc, -1, pszDst, dst_size_in_wchar);
		#else
			iconv_t cv = iconv_open(GAIA::CHARSET_CODEPAGE_NAMEA[GAIA::CHARSET_TYPE_UTF16LE], GAIA::CHARSET_CODEPAGE_NAMEA[charset_type]);
			if(cv == (iconv_t)-1)
				return 0;

			GAIA::CH* pTempSrc = (GAIA::CH*)pszSrc;
			GAIA::CH* pTempDst = (GAIA::CH*)pszDst;
		#	if GAIA_MACHINE == GAIA_MACHINE32
			GAIA::U32 uSrcSize = GAIA_INTERNAL_NAMESPACE::strlen(pszSrc);
			GAIA::U32 uDstSize = dst_size_in_wchar * sizeof(GAIA::WCH);
		#	elif GAIA_MACHINE == GAIA_MACHINE64
			GAIA::U64 uSrcSize = GAIA_INTERNAL_NAMESPACE::strlen(pszSrc);
			GAIA::U64 uDstSize = dst_size_in_wchar * sizeof(GAIA::WCH);
		#	endif

			if(iconv(cv, &pTempSrc, &uSrcSize, &pTempDst, &uDstSize) == -1)
				return 0;

			if(iconv_close(cv) == -1)
				return 0;

			GAIA::SIZE sByteCount = dst_size_in_wchar * sizeof(GAIA::WCH) - uDstSize;
			GAIA_AST(sByteCount % sizeof(GAIA::WCH) == 0);
			GAIA::SIZE sCharCount = sByteCount / sizeof(GAIA::WCH);
			pszDst[sCharCount] = '\0';
			return sCharCount + 1;
		#endif
		}
		GINL GAIA::SIZE w2m(const GAIA::WCH* pszSrc, GAIA::CH* pszDst, GAIA::SIZE dst_size_in_bytes, GAIA::CHARSET_TYPE charset_type)
		{
			GAIA_AST(charset_type < GAIA::CHARSET_TYPE_MAXENUMCOUNT);
			if(charset_type >= GAIA::CHARSET_TYPE_MAXENUMCOUNT)
				return 0;
			if(charset_type == GAIA::CHARSET_TYPE_ASCII)
			{
				GAIA::SIZE ret = 0;
				for(;;)
				{
					if(pszDst != GNIL && dst_size_in_bytes != 0)
					{
						if(ret >= dst_size_in_bytes)
							break;
						pszDst[ret] = GSCAST(GAIA::CH)(pszSrc[ret]);
					}
					if(pszSrc[ret] == '\0')
					{
						++ret;
						break;
					}
					++ret;
				}
				return ret;
			}
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::U32 uCodePage;
			if(charset_type == GAIA::CHARSET_TYPE_SYS)
				uCodePage = CP_OEMCP;
			else
				uCodePage = GAIA::CHARSET_CODEPAGE[charset_type];
			return ::WideCharToMultiByte(uCodePage, 0, pszSrc, -1, pszDst, dst_size_in_bytes, GNIL, GNIL);
		#else
			iconv_t cv = iconv_open(GAIA::CHARSET_CODEPAGE_NAMEA[charset_type], GAIA::CHARSET_CODEPAGE_NAMEA[GAIA::CHARSET_TYPE_UTF16LE]);
			if(cv == (iconv_t)-1)
				return 0;

			GAIA::CH* pTempSrc = (GAIA::CH*)pszSrc;
			GAIA::CH* pTempDst = (GAIA::CH*)pszDst;
		#	if GAIA_MACHINE == GAIA_MACHINE32
			GAIA::U32 uSrcSize = GAIA_INTERNAL_NAMESPACE::strlen(pszSrc) * sizeof(GAIA::WCH);
			GAIA::U32 uDstSize = dst_size_in_bytes;
		#	elif GAIA_MACHINE == GAIA_MACHINE64
			GAIA::U64 uSrcSize = GAIA_INTERNAL_NAMESPACE::strlen(pszSrc) * sizeof(GAIA::WCH);
			GAIA::U64 uDstSize = dst_size_in_bytes;
		#	endif

			if(iconv(cv, &pTempSrc, &uSrcSize, &pTempDst, &uDstSize) == -1)
				return 0;

			if(iconv_close(cv) == -1)
				return 0;

			GAIA::SIZE sByteCount = dst_size_in_bytes - uDstSize;
			pszDst[sByteCount] = '\0';
			return sByteCount + 1;
		#endif
		}
	};
};

#endif
