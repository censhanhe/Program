#ifndef		__GAIA_LOCALE_H__
#define		__GAIA_LOCALE_H__

namespace GAIA
{
	namespace LOCALE
	{
		GINL GAIA::SIZE m2w(const GAIA::CH* pszSrc, GAIA::WCH* pszDst, GAIA::SIZE dst_size_in_wchar, GAIA::CHARSET_TYPE charset_type); // Return the practice dst_size_in_wchar(include '\0').
		GINL GAIA::SIZE w2m(const GAIA::WCH* pszSrc, GAIA::CH* pszDst, GAIA::SIZE dst_size_in_bytes, GAIA::CHARSET_TYPE charset_type); // Return the practice dst_size_in_bytes(include '\0').
	};
};

#include "gaia_locale_indp.h"

#endif
