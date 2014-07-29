#ifndef		__GAIA_GLOBAL_IMPL_H__
#define		__GAIA_GLOBAL_IMPL_H__

#ifndef GAIA_DEBUG_MEMORYLEAK
	GAIA::ALLOCATOR::AllocatorESG g_global_allocator;
#endif

	GAIA::SYNC::Lock g_localelock;
	GAIA::CHARSET_TYPE g_charsettype = GAIA::CHARSET_TYPE_SYS;

#endif
