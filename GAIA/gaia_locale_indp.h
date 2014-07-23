#ifndef		__GAIA_LOCALE_INDP_H__
#define		__GAIA_LOCALE_INDP_H__

#include <locale.h>
#include <xlocale>

namespace GAIA
{
	namespace LOCALE
	{
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::GCH* strlocale(const GAIA::GCH* pszLocalName){GAIA_AST(pszLocalName != GNULL); return setlocale(LC_ALL, pszLocalName);}
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::GCH* strlocale(){return setlocale(LC_ALL, NULL);}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE m2w(const GAIA::GCH* pszSrc, GAIA::GWCH* pszDst, GAIA::SIZE dst_size_in_wchar){return mbstowcs(pszDst, pszSrc, dst_size_in_wchar);}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE w2m(const GAIA::GWCH* pszSrc, GAIA::GCH* pszDst, GAIA::SIZE dst_size_in_bytes){return wcstombs(pszDst, pszSrc, dst_size_in_bytes);}
	};
};

#endif