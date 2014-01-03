#ifndef		__GAIA_SYS_CONFIG_H__
#define		__GAIA_SYS_CONFIG_H__

#define GINL inline

/* Debug mode. */
#define GAIA_DEBUG_CODEPURE
#ifdef GAIA_DEBUG_CODEPURE
#	define GAIA_DEBUG_CODEPURE_INL
#else
#	define GAIA_DEBUG_CODEPURE_INL GINL
#endif

/* OS flag. */
#define GAIA_OS_WINDOWS 1
#define GAIA_OS_OSX 2
#define GAIA_OS_IOS 3
#define GAIA_OS_ANDROID 4
#define GAIA_OS_LINUX 5
#define GAIA_OS_UNIX 6
#define GAIA_OS GAIA_OS_WINDOWS

/* Language code flag. */
#define GAIA_CHARFMT_ANSI 1
#define GAIA_CHARFMT_UNICODE 2
#define GAIA_CHARFMT GAIA_CHARFMT_UNICODE

/* Machine bit count flag. */
#define GAIA_MACHINE32 32
#define	GAIA_MACHINE64 64
#define GAIA_MACHINE GAIA_MACHINE32

#if GAIA_MACHINE == GAIA_MACHINE32
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#elif GAIA_MACHINE == GAIA_MACHINE64
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFFFFFFFFFF
#else
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#endif

/* Enum helper. */
#define ENUM_BEGIN(name) enum name{
#define ENUM_END name##_FORCE##=GAIA_MAX_UNSIGNED_INTEGER,};

#endif