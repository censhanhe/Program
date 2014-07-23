#ifndef		__GAIA_LOCALE_H__
#define		__GAIA_LOCALE_H__

namespace GAIA
{
	namespace LOCALE
	{
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::GCH* strlocale(const GAIA::GCH* pszLocalName); // If pszLocalName == "", will set the default locale.
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::GCH* strlocale();
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE str2wcs(const GAIA::GCH* pszSrc, GAIA::GWCH* pszDst, GAIA::SIZE dst_size_in_wchar);
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE str2mbs(const GAIA::GWCH* pszSrc, GAIA::GCH* pszDst, GAIA::SIZE dst_size_in_bytes);
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_basic_indp.h"
#endif

#endif