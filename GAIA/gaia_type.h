#ifndef		__GAIA_TYPE_H__
#define		__GAIA_TYPE_H__

namespace GAIA
{
#ifdef GRCAST
#	undef GRCAST
#endif

#ifdef GSCAST
#	undef GSCAST
#endif

#ifdef GDCAST
#	undef GDCAST
#endif

#ifdef GCCAST
#	undef GCCAST
#endif

#define GRCAST(type) reinterpret_cast<type>
#define GSCAST(type) static_cast<type>
#define GDCAST(type) dynamic_cast<type>
#define GCCAST(type) const_cast<type>

	/* Integer type declaration. */
	typedef long NM;
	typedef unsigned long UM;
	typedef bool BL;
	typedef char N8;
	typedef unsigned char U8;
	typedef short N16;
	typedef unsigned short U16;
	typedef int N32;
	typedef unsigned int U32;
	typedef long long N64;
	typedef unsigned long long U64;
#if GAIA_COMPILER == GAIA_COMPILER_CL
#	pragma warning(disable : 4310)
#endif
	static const GAIA::N8 N8MINSIZE = (GAIA::N8)0x80;
	static const GAIA::N8 N8MAXSIZE = (GAIA::N8)0x7F;
	static const GAIA::U8 U8MINSIZE = (GAIA::U8)0x00;
	static const GAIA::U8 U8MAXSIZE = (GAIA::U8)0xFF;
	static const GAIA::N16 N16MINSIZE = (GAIA::N16)0x8000;
	static const GAIA::N16 N16MAXSIZE = (GAIA::N16)0x7FFF;
	static const GAIA::U16 U16MINSIZE = (GAIA::U16)0x0000;
	static const GAIA::U16 U16MAXSIZE = (GAIA::U16)0xFFFF;
	static const GAIA::N32 N32MINSIZE = (GAIA::N32)0x80000000;
	static const GAIA::N32 N32MAXSIZE = (GAIA::N32)0x7FFFFFFF;
	static const GAIA::U32 U32MINSIZE = (GAIA::U32)0x00000000;
	static const GAIA::U32 U32MAXSIZE = (GAIA::U32)0xFFFFFFFF;
	static const GAIA::N64 N64MINSIZE = (GAIA::N64)0x8000000000000000;
	static const GAIA::N64 N64MAXSIZE = (GAIA::N64)0x7FFFFFFFFFFFFFFF;
	static const GAIA::U64 U64MINSIZE = (GAIA::U64)0x0000000000000000;
	static const GAIA::U64 U64MAXSIZE = (GAIA::U64)0xFFFFFFFFFFFFFFFF;
#if GAIA_COMPILER == GAIA_COMPILER_CL
#	pragma warning(default : 4310)
#endif
	/* Float type declaration. */
	typedef float F32; // Variable will have a 'f' prefix.
	typedef double F64; // Variable will have a 'd' prefix.
#if GAIA_REAL == GAIA_REAL_F32
	typedef F32 REAL; // variable will have a 'r' prefix.
#	define R(x) x##F
#elif GAIA_REAL == GAIA_REAL_F64
	typedef F64 REAL;
#	define R(x) x
#endif

	typedef N32 EN;

	/* Char type declaration. */
	typedef char CH;
	typedef wchar_t WCH;
#if GAIA_CHARSET == GAIA_CHARSET_UNICODE
	typedef wchar_t TCH;
#	ifndef _T
#		ifndef __T
#			define __T(x)      L##x
#		endif
#		define _T(x) __T(x)
#	endif
#else
	typedef char TCH;
#	ifndef _T
#		define _T(x) x
#	endif
#endif

	/* GAIA size. */
	typedef GAIA::N32 SIZE; // The variable will have a 's' prefix.
	static const GAIA::SIZE MINSIZE = (GAIA::SIZE)N32MINSIZE;
	static const GAIA::SIZE MAXSIZE = (GAIA::SIZE)N32MAXSIZE;

	/* Bool enum. */
	static const BL True = true;
	static const BL False = false;

	/* Void. */
	typedef void GVOID;

	/* Other global constants. */
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSTRUE = GAIA::True;
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSFALSE = GAIA::False;

	/* Common constants. */
	#define GNIL 0
	#define GNILSTR ""
	#define GNILWSTR L""
	#define GNILTSTR _T("")
	#define GINVALID (~0)

	/* Common operation. */
	#define sizeofarray(arr) ((GAIA::NM)(sizeof(arr) / sizeof((arr)[0])))
	#define sizeofarray2(arr) ((GAIA::NM)(sizeof(arr) / sizeof((arr)[0][0])))

	/* X128 */
	class X128
	{
	public:
		GINL X128(){}
		GINL X128(const X128& src){this->operator = (src);}
		template<typename _DataType> X128(const _DataType* p){this->operator = (p);}
		GINL GAIA::BL empty() const{return u64_0 == 0 && u64_1 == 0;}
		GINL GAIA::GVOID clear(){u64_0 = u64_1 = 0;}
		template<typename _ParamDataType> GAIA::GVOID fromstring(const _ParamDataType* psz);
		template<typename _ParamDataType> GAIA::GVOID tostring(_ParamDataType* psz) const;
		GINL X128& operator = (const X128& src){u64_0 = src.u64_0; u64_1 = src.u64_1; return *this;}
		template<typename _DataType> X128& operator = (const _DataType* p)
		{
			u32_0 = u32_1 = u32_2 = u32_3 = 0;
			for(GAIA::U32 x = 0; x < 32; ++x)
			{
				GAIA::U32 uIndex = x / 8;
				if(p[x] >= '0' && p[x] <= '9')
					u32[uIndex] |= p[x] - '0';
				else if(p[x] >= 'a' && p[x] <= 'f')
					u32[uIndex] |= p[x] - 'a' + 10;
				else if(p[x] >= 'A' && p[x] <= 'F')
					u32[uIndex] |= p[x] - 'A' + 10;
				if((x % 8) != 7)
					u32[uIndex] = u32[uIndex] << 4;
			}
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE2(u64_0, u64_0, u64_1, u64_1, X128);
	public:
		union
		{
			GAIA::U32 u32[4];
			GAIA::U8 u8[16];
			class
			{
			public:
				GAIA::U32 u32_0;
				GAIA::U32 u32_1;
				GAIA::U32 u32_2;
				GAIA::U32 u32_3;
			};
			class
			{
			public:
				GAIA::U64 u64_0;
				GAIA::U64 u64_1;
			};
		};
	};

	/* Class Base. All class's parent. */
	class Base
	{
	public:
	#ifndef GAIA_DEBUG_MEMORYLEAK
	#	if GAIA_MACHINE == GAIA_MACHINE32
			GINL GAIA::GVOID* operator new(GAIA::U32 size);
			GINL GAIA::GVOID* operator new[](GAIA::U32 size);
	#	elif GAIA_MACHINE == GAIA_MACHINE64
			GINL GAIA::GVOID* operator new(GAIA::U64 size);
			GINL GAIA::GVOID* operator new[](GAIA::U64 size);
	#	endif
		GINL GAIA::GVOID operator delete(GAIA::GVOID* p);
		GINL GAIA::GVOID operator delete[](GAIA::GVOID* p);
	#endif
	};

	/* Entity can been dispatch by virtual table and have a virtual destructor. */
	class Entity : public GAIA::Base
	{
	public:
		GAIA_ENUM_BEGIN(FEATURE)
			FEATURE_CAPACITY,
			FEATURE_SIZE,
		GAIA_ENUM_END(FEATURE)
	public:
		virtual ~Entity(){}
		virtual GAIA::BL base_statistics(FEATURE of, GAIA::GVOID* pResult) const{return GAIA::False;}
		virtual GAIA::BL base_optimize(FEATURE of, GAIA::GVOID* pResult){return GAIA::False;}
	};

	/* Class Object. It's the all class's base(except high-performance container and math class. */
	class Object : public GAIA::Entity
	{
	public:
	};

	/* Class RefObject. If a class need a reference function, it will derived from here. */
	class RefObject : public GAIA::Object
	{
	public:
		GINL RefObject(){m_nRef = 1; m_bDestructing = GAIA::False;}
		GINL ~RefObject(){}
		GINL GAIA::NM Reference();
		GINL GAIA::NM Release();
		GINL GAIA::NM GetRef() const{return m_nRef;}
	protected:
		virtual GAIA::GVOID RefObjectDestruct(){}
	private:
		GINL RefObject& operator = (const RefObject& src){return *this;}
	private:
	#if GAIA_OS == GAIA_OS_WINDOWS
	#	if GAIA_MACHINE == GAIA_MACHINE64
			volatile GAIA::N64 m_nRef;
	#	else
			volatile GAIA::NM m_nRef;
	#	endif
	#elif GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
		#if GAIA_MACHINE == GAIA_MACHINE64
			volatile GAIA::N64 m_nRef;
		#else
			volatile GAIA::N32 m_nRef;
		#endif
	#else
		volatile GAIA::N32 m_nRef;
	#endif
		GAIA::U8 m_bDestructing : 1;
	};

	/* Type id declaration. */
	GAIA_ENUM_BEGIN(TYPEID)
		TYPEID_NM,
		TYPEID_UM,
		TYPEID_BL,
		TYPEID_N8,
		TYPEID_U8,
		TYPEID_N16,
		TYPEID_U16,
		TYPEID_N32,
		TYPEID_U32,
		TYPEID_N64,
		TYPEID_U64,
		TYPEID_X128,
		TYPEID_F32,
		TYPEID_F64,
		TYPEID_POINTER,
		TYPEID_CONSTPOINTER,
	GAIA_ENUM_END(TYPEID)

	static const GAIA::CH* TYPEID_ANAME[] =
	{
		"Invalid",
		"NM",
		"UM",
		"BL",
		"N8",
		"U8",
		"N16",
		"U16",
		"N32",
		"U32",
		"N64",
		"U64",
		"X128",
		"F32",
		"F64",
		"Pointer",
		"ConstPointer",
	};

	static const GAIA::WCH* TYPEID_WNAME[] =
	{
		L"Invalid",
		L"NM",
		L"UM",
		L"BL",
		L"N8",
		L"U8",
		L"N16",
		L"U16",
		L"N32",
		L"U32",
		L"N64",
		L"U64",
		L"X128",
		L"F32",
		L"F64",
		L"Pointer",
		L"ConstPointer",
	};

	GINL TYPEID nametotype(const GAIA::CH* psz);
	GINL TYPEID nametotype(const GAIA::WCH* psz);

	/* Common type. */
	GAIA_ENUM_BEGIN(SEEK_TYPE)
		SEEK_TYPE_BEGIN,
		SEEK_TYPE_END,
		SEEK_TYPE_FORWARD,
		SEEK_TYPE_BACKWARD,
	GAIA_ENUM_END(SEEK_TYPE)

	GAIA_ENUM_BEGIN(RELATION_TYPE)
		RELATION_TYPE_EQUAL,
		RELATION_TYPE_NOTEQUAL,
		RELATION_TYPE_ABOVE,
		RELATION_TYPE_BELOW,
		RELATION_TYPE_ABOVEEQUAL,
		RELATION_TYPE_BELOWEQUAL,
		RELATION_TYPE_TRUE,
		RELATION_TYPE_FALSE,
	GAIA_ENUM_END(RELATION_TYPE)

	GAIA_ENUM_BEGIN(STRING_TYPE)
		STRING_TYPE_STRING	= 1 << 0,

		STRING_TYPE_INTEGER	= 1 << 1,
		STRING_TYPE_N8		= 1 << 2,	// Not supported!
		STRING_TYPE_U8		= 1 << 3,	// Not supported!
		STRING_TYPE_N16		= 1 << 4,	// Not supported!
		STRING_TYPE_U16		= 1 << 5,	// Not supported!
		STRING_TYPE_N32		= 1 << 6,	// Not supported!
		STRING_TYPE_U32		= 1 << 7,	// Not supported!
		STRING_TYPE_N64		= 1 << 8,	// Not supported!
		STRING_TYPE_U64		= 1 << 9,	// Not supported!

		STRING_TYPE_REAL	= 1 << 10,
		STRING_TYPE_F32		= 1 << 11,	// Not supported!
		STRING_TYPE_F64		= 1 << 12,	// Not supported!

		STRING_TYPE_X128	= 1 << 20,
		STRING_TYPE_RID		= 1 << 20,
		STRING_TYPE_RID64	= 1 << 21,
		STRING_TYPE_RID128	= 1 << 22,
	GAIA_ENUM_END(STRING_TYPE)

	GAIA_ENUM_BEGIN(CHARSET_TYPE) // If you change the sequence of the enum item, you must change CHARSET_CODEPAGE array element's sequence.
		CHARSET_TYPE_SYS,
		CHARSET_TYPE_ASCII,
		CHARSET_TYPE_UTF7,
		CHARSET_TYPE_UTF8,
		CHARSET_TYPE_UTF16LE,
		CHARSET_TYPE_UTF16BE,
	GAIA_ENUM_END(CHARSET_TYPE)

	static const GAIA::U32 CHARSET_CODEPAGE[] =
	{
		0,		// CHARSET_INVALID
		1,		// CHARSET_TYPE_SYS
		2,		// CHARSET_TYPE_ASCII
		65000,	// CHARSET_TYPE_UTF7
		65001,	// CHARSET_TYPE_UTF8
		1200,	// CHARSET_TYPE_UTF16LE
		1201,	// CHARSET_TYPE_UTF16BE
	};

	static const GAIA::CH* CHARSET_CODEPAGE_NAMEA[] =
	{
		"invalid",			// CHARSET_INVALID
		GAIA_SYS_CODEPAGE,	// CHARSET_TYPE_SYS
		"ASCII",			// CHARSET_TYPE_ASCII
		"UTF-7",			// CHARSET_TYPE_UTF7
		"UTF-8",			// CHARSET_TYPE_UTF8
		"UTF-16LE",			// CHARSET_TYPE_UTF16LE
		"UTF-16BE",			// CHARSET_TYPE_UTF16BE
	};

	static const GAIA::U8 UTF8_FILEHEAD[3] = {0xEF, 0xBB, 0xBF};
	static const GAIA::U8 UTF16LE_FILEHEAD[2] = {0xFF, 0xFE};
	static const GAIA::U8 UTF16BE_FILEHEAD[2] = {0xFE, 0xFF};

	GAIA_ENUM_BEGIN(INTERSECT_TYPE)
		INTERSECT_TYPE_IN,
		INTERSECT_TYPE_OUT,
		INTERSECT_TYPE_INTERSECT,
	GAIA_ENUM_END(INTERSECT_TYPE)
};

#include "gaia_type_indp.h"

#ifndef GAIA_DEBUG_MEMORYLEAK
	namespace GAIA{namespace ALLOCATOR{class AllocatorESG;};};
	extern GAIA::ALLOCATOR::AllocatorESG g_gaia_globalallocator;
#	define GAIA_MALLOC(type, size) (type*)g_gaia_globalallocator.memory_alloc(sizeof(type) * (size))
#	define GAIA_MFREE(p) g_gaia_globalallocator.memory_release((GAIA::GVOID*)(p))
#	define GAIA_MFREE_SAFE(p) if((p) != GNIL){GAIA_MFREE(p); (p) = GNIL;}
#else
#	define GAIA_MALLOC(type, size) new type[(size)]
#	define GAIA_MFREE(p) delete[] (p);
#	define GAIA_MFREE_SAFE(p) do{if((p) != GNIL){GAIA_MFREE(p); (p) = GNIL;}}while(0)
#endif

#define GAIA_DELETE_SAFE(p) do{if((p) != GNIL){delete (p); (p) = GNIL;}}while(0)
#define GAIA_DELETEARRAY_SAFE(p) do{if((p) != GNIL){delete[] (p); (p) = GNIL;}}while(0)
#define GAIA_RELEASE_SAFE(p) do{if((p) != GNIL){(p)->Release(); (p) = GNIL;}}while(0)

#endif
