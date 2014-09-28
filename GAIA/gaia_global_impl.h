#ifndef		__GAIA_GLOBAL_IMPL_H__
#define		__GAIA_GLOBAL_IMPL_H__

#ifndef GAIA_DEBUG_MEMORYLEAK
	GAIA::ALLOCATOR::AllocatorESG g_gaia_globalallocator;
#endif

	GAIA::Platform g_gaia_platform;
	GAIA::SYNC::Lock g_gaia_localelock;
	GAIA::CHARSET_TYPE g_gaia_charsettype = GAIA::CHARSET_TYPE_SYS;

#if GAIA_OS == GAIA_OS_WINDOWS
	GAIA::SYNC::Lock g_gaia_windowlistlock;
	GAIA::CTN::Set<GAIA::CTN::Ref<GAIA::UI::Canvas> > g_gaia_windowlist;
#endif

#endif
