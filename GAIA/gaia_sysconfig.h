#ifndef		__GAIA_SYS_CONFIG_H__
#define		__GAIA_SYS_CONFIG_H__

#define GAIA_VERSION_MAJOR		0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_RELEASE	0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_MINOR		0 // unsigned int type. 0 is not a valid version.
#define GAIA_VERSION_BUILD		0 // unsigned int type. 0 is not a valid version.

#define GINL inline

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
#	define GAIA_OS GAIA_OS_OSX
#endif

/* Compiler profile. */
#define GAIA_PROFILE_DEBUG 1
#define GAIA_PROFILE_RELEASE 2
#if GAIA_OS == GAIA_OS_WINDOWS
#	ifdef _DEBUG
#		define GAIA_PROFILE GAIA_PROFILE_DEBUG
#	else
#		define GAIA_PROFILE GAIA_PROFILE_RELEASE
#	endif
#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
#	ifdef DEBUG
#		define GAIA_PROFILE GAIA_PROFILE_DEBUG
#	else
#		define GAIA_PROFILE GAIA_PROFILE_RELEASE
#	endif
#else
#	define GAIA_PROFILE GAIA_PROFILE_RELEASE
#endif

/* Compiler type. */
#define GAIA_COMPILER_CL 1
#define GAIA_COMPILER_GCC 2
#define GAIA_COMPILER_CLANG 3
#ifdef _MSC_VER
#	define GAIA_COMPILER GAIA_COMPILER_CL
#else
#	define GAIA_COMPILER GAIA_COMPILER_GCC
#endif

/* Compiler version. */
#define GAIA_COMPILER_CLVER_FIRST 0x0010
#define GAIA_COMPILER_CLVER_LATEST 0x0010
#define GAIA_COMPILER_CLVER GAIA_COMPILER_CLVER_LATEST

#define GAIA_COMPILER_GCCVER_FIRST 0x0010
#define GAIA_COMPILER_GCCVER_USESYNCXX 0x0080
#define GAIA_COMPILER_GCCVER_LATEST 0x0080
#define GAIA_COMPILER_GCCVER GAIA_COMPILER_GCCVER_LATEST

#define GAIA_COMPILER_CLANGVER_FIRST 0x0010
#define GAIA_COMPILER_CLANGVER_LATEST 0x0010
#define GAIA_COMPILER_CLANGVER GAIA_COMPILER_CLANGVER_LATEST

/* Language code flag. */
#define GAIA_CHARSET_ANSI 1
#define GAIA_CHARSET_UNICODE 2
#define GAIA_CHARSET GAIA_CHARSET_ANSI

/* Machine bit count flag. */
#define GAIA_MACHINE32 32
#define	GAIA_MACHINE64 64
#define GAIA_MACHINE128 128
#ifdef _MSC_VER
#	if defined(_WIN64)
#		define GAIA_MACHINE GAIA_MACHINE64
#	else
#		define GAIA_MACHINE GAIA_MACHINE32
#	endif
#else
#	define GAIA_MACHINE GAIA_MACHINE64
#endif

#if GAIA_MACHINE == GAIA_MACHINE32
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#elif GAIA_MACHINE == GAIA_MACHINE64
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFFFFFFFFFF
#else
#	define GAIA_MAX_UNSIGNED_INTEGER 0xFFFFFFFF
#endif

/* Debug mode. */
#define GAIA_DEBUG_SELFCHECKROUTINE
#define GAIA_DEBUG_INTERNALROUTINE
#define GAIA_DEBUG_WARNING
#define GAIA_DEBUG_CODING
#define GAIA_DEBUG_AST
#define GAIA_DEBUG_STATICAST
#define GAIA_DEBUG_MACHINELENGTH
#define GAIA_DEBUG_MEMORYLEAK
//#define GAIA_DEBUG_CODEPURE

#ifdef GAIA_DEBUG_CODING
#	define GAIA_DEBUG_CONST
#else
#	define GAIA_DEBUG_CONST const
#endif

#ifdef GAIA_DEBUG_CODEPURE
#	define GAIA_DEBUG_CODEPURE_FUNC extern
#	define GAIA_DEBUG_CODEPURE_MEMFUNC
#	define GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL virtual
#	define GAIA_DEBUG_CODEPURE_VIRTUALFUNCIMPL
#else
#	define GAIA_DEBUG_CODEPURE_FUNC GINL
#	define GAIA_DEBUG_CODEPURE_MEMFUNC GINL
#	define GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL virtual GINL
#	define GAIA_DEBUG_CODEPURE_VIRTUALFUNCIMPL GINL
#endif

/* Enum helper. */
#define GAIA_ENUM_BEGIN(name) enum name{name##_INVALID = 0,
#define GAIA_ENUM_END(name) name##_COUNT,name##_FORCEUNSIGNEDINTEGER=GAIA_MAX_UNSIGNED_INTEGER,};

/* Module setting. */
#define GAIA_MODULE_BASEDATATYPEONLY	// If define this macro, the macro's user will alloc object by GAIA_MALLOC but not new(c++ operator).
										// In that case, the buffer element will been base data type only.
										// If not, the constructor and destructor will not been called.

/* Warning adjust. */
#ifdef GAIA_DEBUG_WARNING
#	if GAIA_OS == GAIA_OS_WINDOWS
#		pragma warning(disable : 4100)
#		pragma warning(disable : 4189)
#	else
#	endif
#endif

/* Integration flag. */
#define GAIA_USESTL

#endif
