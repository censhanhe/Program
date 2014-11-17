#ifndef		__GAIA_LOCALE_INDP_H__
#define		__GAIA_LOCALE_INDP_H__

#include <locale.h>
#if GAIA_OS == GAIA_OS_WINDOWS
#	include <xlocale>
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
			if(charset_type == GAIA::CHARSET_TYPE_ANSI)
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
			
		#endif

		}
		GINL GAIA::SIZE w2m(const GAIA::WCH* pszSrc, GAIA::CH* pszDst, GAIA::SIZE dst_size_in_bytes, GAIA::CHARSET_TYPE charset_type)
		{
			GAIA_AST(charset_type < GAIA::CHARSET_TYPE_MAXENUMCOUNT);
			if(charset_type >= GAIA::CHARSET_TYPE_MAXENUMCOUNT)
				return 0;
			if(charset_type == GAIA::CHARSET_TYPE_ANSI)
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
			
		#endif
		}
	};
};

#endif
