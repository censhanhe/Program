#ifndef		__GAIA_GLOBAL_IMPL_H__
#define		__GAIA_GLOBAL_IMPL_H__

/* Global allocator. */
#ifndef GAIA_DEBUG_MEMORYLEAK
	GAIA::ALLOCATOR::AllocatorESG g_gaia_globalallocator;
#endif

/* Platform. */
GAIA::Platform g_gaia_platform;

/* Log. */
GAIA::LOG::Log g_gaia_log;
DefaultGAIALogCallBack g_gaia_log_callback;

/* Global canvas list. */
#if GAIA_OS == GAIA_OS_WINDOWS
	GAIA::SYNC::Lock g_gaia_windowlistlock;
	GAIA::CTN::Set<GAIA::CTN::Ref<GAIA::UI::Canvas> > g_gaia_windowlist;
#endif

#endif
