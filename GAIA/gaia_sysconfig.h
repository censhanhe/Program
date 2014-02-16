#ifndef		__GAIA_SYS_CONFIG_H__
#define		__GAIA_SYS_CONFIG_H__


#define GAIA_VERSION_MAJOR		0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_RELEASE	0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_MINOR		0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_BUILD		0 // unsigned int type. 0 is not a valid version.

#define GINL inline

/* Debug mode. */
#define GAIA_DEBUG_SELFCHECKROUTINE
#define GAIA_DEBUG_INTERNALROUTINE
#define GAIA_DEBUG_WARNING
#define GAIA_DEBUG_CODING 
#define GAIA_DEBUG_AST
#define GAIA_DEBUG_STATICAST
//#define GAIA_DEBUG_CODEPURE

#ifdef GAIA_DEBUG_CODING
#	define GAIA_DEBUG_CONST
#else
#	define GAIA_DEBUG_CONST const
#endif

#ifdef GAIA_DEBUG_CODEPURE
#	define GAIA_DEBUG_CODEPURE_FUNC extern
#	define GAIA_DEBUG_CODEPURE_MEMFUNC
#else
#	define GAIA_DEBUG_CODEPURE_FUNC GINL
#	define GAIA_DEBUG_CODEPURE_MEMFUNC GINL
#endif

/* OS flag. */
#define GAIA_OS_WINDOWS 1
#define GAIA_OS_OSX 2
#define GAIA_OS_IOS 3
#define GAIA_OS_ANDROID 4
#define GAIA_OS_LINUX 5
#define GAIA_OS_UNIX 6
#ifdef _MSC_VER
#	define GAIA_OS GAIA_OS_WINDOWS
#else
#	define GAIA_OS 0
#endif

/* Language code flag. */
#define GAIA_CHARFMT_ANSI 1
#define GAIA_CHARFMT_UNICODE 2
#define GAIA_CHARFMT GAIA_CHARFMT_UNICODE

/* Machine bit count flag. */
#define GAIA_MACHINE32 32
#define	GAIA_MACHINE64 64
#define GAIA_MACHINE128 128
#define GAIA_MACHINE GAIA_MACHINE32

#if GAIA_MACHINE == GAIA_MACHINE32
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#elif GAIA_MACHINE == GAIA_MACHINE64
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFFFFFFFFFF
#else
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#endif

/* Enum helper. */
#define ENUM_BEGIN(name) enum name{name##_INVALID = 0,
#define ENUM_END(name) name##_FORCE=GAIA_MAX_UNSIGNED_INTEGER,};

/* Warning adjust. */
#ifdef GAIA_DEBUG_WARNING
#	if GAIA_OS == GAIA_OS_WINDOWS
#		pragma warning(disable : 4100)
#		pragma warning(disable : 4189)
#	else
#	endif
#endif

#endif
