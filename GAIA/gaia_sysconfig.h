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

/* Language code flag. */
#define GAIA_CHARFMT_ANSI 1
#define GAIA_CHARFMT_UNICODE 2
#define GAIA_CHARFMT GAIA_CHARFMT_UNICODE

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

/* Enum helper. */
#define GAIA_ENUM_BEGIN(name) enum name{name##_INVALID = 0,
#define GAIA_ENUM_END(name) name##_COUNT,name##_FORCEUNSIGNEDINTEGER=GAIA_MAX_UNSIGNED_INTEGER,};

/* Class helper. */
#define GAIA_CLASS_OPERATOR_COMPARE(self, another, anothertype) \
			GINL GAIA::BL operator == (const anothertype& src) const{return (self) == (src.another);}\
			GINL GAIA::BL operator != (const anothertype& src) const{return (self) != (src.another);}\
			GINL GAIA::BL operator >= (const anothertype& src) const{return (self) >= (src.another);}\
			GINL GAIA::BL operator <= (const anothertype& src) const{return (self) <= (src.another);}\
			GINL GAIA::BL operator > (const anothertype& src) const{return (self) > (src.another);}\
			GINL GAIA::BL operator < (const anothertype& src) const{return (self) < (src.another);}

#define GAIA_CLASS_OPERATOR_COMPARE2(self, another, self2, another2, anothertype) \
			GINL GAIA::BL operator == (const anothertype& src) const\
			{\
				if(self == src.another && self2 == src.another2)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator != (const anothertype& src) const\
			{\
				if(self != src.another || self2 != src.another2)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator >= (const anothertype& src) const\
			{\
				if(self > src.another)\
					return GAIA::True;\
				else if(self < src.another)\
					return GAIA::False;\
				else\
				{\
					if(self2 >= src.another2)\
						return GAIA::True;\
					else\
						return GAIA::False;\
				}\
			}\
			GINL GAIA::BL operator <= (const anothertype& src) const\
			{\
				if(self < src.another)\
					return GAIA::True;\
				else if(self > src.another)\
					return GAIA::False;\
				else\
				{\
					if(self2 <= src.another2)\
						return GAIA::True;\
					else\
						return GAIA::False;\
				}\
			}\
			GINL GAIA::BL operator > (const anothertype& src) const{return !(*this <= src);}\
			GINL GAIA::BL operator < (const anothertype& src) const{return !(*this >= src);}

/* Warning adjust. */
#ifdef GAIA_DEBUG_WARNING
#	if GAIA_OS == GAIA_OS_WINDOWS
#		pragma warning(disable : 4100)
#		pragma warning(disable : 4189)
#	else
#	endif
#endif

#endif
