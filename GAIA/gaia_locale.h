#ifndef		__GAIA_LOCALE_H__
#define		__GAIA_LOCALE_H__

namespace GAIA
{
	namespace LOCALE
	{
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::CH* strlocale(const GAIA::CH* pszLocalName); // If pszLocalName == "", will set the default locale.
		GAIA_DEBUG_CODEPURE_FUNC const GAIA::CH* strlocale();
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE m2w(const GAIA::CH* pszSrc, GAIA::WCH* pszDst, GAIA::SIZE dst_size_in_wchar); // Return the practice dst_size_in_wchar.
		GAIA_DEBUG_CODEPURE_FUNC GAIA::SIZE w2m(const GAIA::WCH* pszSrc, GAIA::CH* pszDst, GAIA::SIZE dst_size_in_bytes); // Return the practice dst_size_in_bytes.
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_locale_indp.h"
#endif

#endif
