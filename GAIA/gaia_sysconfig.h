#ifndef		__GAIA_SYS_CONFIG_H__
#define		__GAIA_SYS_CONFIG_H__

#define GINL inline

/* System codepage. */
#define GAIA_SYS_CODEPAGE "GBK"

/* OS flag. */
#define GAIA_OS_WINDOWS 1
#define GAIA_OS_OSX 2
#define GAIA_OS_IOS 3
#define GAIA_OS_ANDROID 4
#define GAIA_OS_LINUX 5
#define GAIA_OS_UNIX 6
#ifdef _MSC_VER
#	define GAIA_OS GAIA_OS_WINDOWS
#elif defined(__LINUX__)
#	define GAIA_OS GAIA_OS_LINUX
#elif defined(__OSX__)
#	define GAIA_OS GAIA_OS_OSX
#elif defined(__IOS__)
#	define GAIA_OS GAIA_OS_IOS
#elif defined(__ANDROID__)
#	define GAIA_OS GAIA_OS_ANDROID
#else
#	define GAIA_OS GAIA_OS_LINUX
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
#ifdef __UNICODE__
#	define GAIA_CHARSET GAIA_CHARSET_UNICODE
#elif defined(__ANSI__)
#	define GAIA_CHARSET GAIA_CHARSET_ANSI
#else
#	define GAIA_CHARSET GAIA_CHARSET_UNICODE
#endif

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
#elif __X32__
#	define GAIA_MACHINE GAIA_MACHINE32
#elif __X64__
#	define GAIA_MACHINE GAIA_MACHINE64
#elif __X128__
#	define GAIA_MACHINE GAIA_MACHINE128
#else
#	define GAIA_MACHINE GAIA_MACHINE32
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
//#define GAIA_DEBUG_ASTDEBUG
#define GAIA_DEBUG_STATICAST
#define GAIA_DEBUG_MACHINELENGTH
#define GAIA_DEBUG_MEMORYLEAK
#define GAIA_DEBUG_PLATFORM

#ifdef GAIA_DEBUG_CODING
#	define GAIA_DEBUG_CONST
#else
#	define GAIA_DEBUG_CONST const
#endif

/* Enum helper. */
#define GAIA_ENUM_BEGIN(enumname) enum enumname{enumname##_INVALID = 0,
#define GAIA_ENUM_END(enumname) enumname##_MAXENUMCOUNT,enumname##_FORCEUNSIGNEDINTEGER=GAIA_MAX_UNSIGNED_INTEGER,};
#define GAIA_ENUM_VALID(enumname, name) (((name) > enumname##_INVALID) && ((name) < enumname##_MAXENUMCOUNT))

/* Module setting. */
#define GAIA_MODULE_BASEDATATYPEONLY	// If define this macro, the macro's user will alloc object by GAIA_MALLOC but not new(c++ operator).
										// In that case, the buffer element will been base data type only.
										// If not, the constructor and destructor will not been called.

/* Warning adjust. */
#ifdef GAIA_DEBUG_WARNING
#	if GAIA_COMPILER == GAIA_COMPILER_CL
#		pragma warning(disable : 4100)
#		pragma warning(disable : 4189)
#		pragma warning(disable : 4996)
#		pragma warning(disable : 4127)
#		pragma warning(disable : 4201)
#		pragma warning(disable : 4800)
#		pragma warning(disable : 4244)
#	else
#	endif
#endif

/* Real type. */
#define GAIA_REAL_F32 1
#define GAIA_REAL_F64 2
#define GAIA_REAL GAIA_REAL_F32

/* Function call type. */
#if GAIA_OS == GAIA_OS_WINDOWS
#	define GAIA_BASEAPI __stdcall
#else
#	define GAIA_BASEAPI
#endif

/* Integration flag. */
#define GAIA_USESTL

/* Line break flag. */
#define GAIA_FILELINEBREAK_RN "\r\n"
#define GAIA_FILELINEBREAK_R "\r"
#define GAIA_FILELINEBREAK_N "\n"
#define GAIA_FILELINEBREAK GAIA_FILELINEBREAK_RN

#endif
