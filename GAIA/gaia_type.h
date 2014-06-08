#ifndef		__GAIA_TYPE_H__
#define		__GAIA_TYPE_H__

namespace GAIA
{
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
	typedef float F32;
	typedef double F64;
	typedef float REAL;

	/* Char type declaration. */
	typedef char GCH;
	typedef wchar_t GWCH;
#if GAIA_CHARFMT == GAIA_CHARFMT_UNICODE
	typedef wchar_t GTCH;
#else
	typedef char GTCH;
#endif

	/* GAIA size. */
	typedef GAIA::N32 SIZE;
	static const GAIA::SIZE MINSIZE = (GAIA::SIZE)N32MINSIZE;
	static const GAIA::SIZE MAXSIZE = (GAIA::SIZE)N32MAXSIZE;

	/* Bool enum. */
	static const BL True = true;
	static const BL False = false;

	/* Void. */
	typedef void GVOID;

	/* X128 */
	class X128
	{
	public:
		GINL GAIA::BL empty() const{return u64_0 == 0 && u64_1 == 0;}
		GINL GAIA::GVOID clear(){u64_0 = u64_1 = 0;}
		GINL X128& operator = (const X128& src){u64_0 = src.u64_0; u64_1 = src.u64_1; return *this;}
		template<typename _DataType> GINL X128& operator = (const _DataType* p)
		{
			u0 = u1 = u2 = u3 = 0;
			for(GAIA::U32 x = 0; x < 32; ++x)
			{
				GAIA::U32 uIndex = x / 8;
				if(p[x] >= '0' && p[x] <= '9')
					u[uIndex] |= p[x] - '0';
				else if(p[x] >= 'a' && p[x] <= 'f')
					u[uIndex] |= p[x] - 'a' + 10;
				else if(p[x] >= 'A' && p[x] <= 'F')
					u[uIndex] |= p[x] - 'A' + 10;
				if((x % 8) != 7)
					u[uIndex] = u[uIndex] << 4;
			}
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE2(u64_0, u64_0, u64_1, u64_1, X128);
	public:
		union
		{
			GAIA::U32 u[4];
			class
			{
			public:
				GAIA::U32 u0;
				GAIA::U32 u1;
				GAIA::U32 u2;
				GAIA::U32 u3;
			};
			class
			{
			public:
				GAIA::U64 u64_0;
				GAIA::U64 u64_1;
			};
		};
	};

	/* Other global constants. */
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSTRUE = GAIA::True;
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSFALSE = GAIA::False;

	/* Common constants. */
	#define GNULL 0
	#define GINVALID (~0)

	/* Undefine origin type. */
	#define GAIA_INVALID_ORIGINTYPE 1
	#ifdef GAIA_DEBUG_CODEPURE
	#	ifndef GAIA_NOCANCEL_ORIGINTYPE
	#		define bool GAIA_INVALID_ORIGINTYPE
	#		define true GAIA_INVALID_ORIGINTYPE
	#		define false GAIA_INVALID_ORIGINTYPE
	#		define char GAIA_INVALID_ORIGINTYPE
	#		define short GAIA_INVALID_ORIGINTYPE
	#		define int GAIA_INVALID_ORIGINTYPE
	#		define long GAIA_INVALID_ORIGINTYPE
	#		define float GAIA_INVALID_ORIGINTYPE
	#		define double GAIA_INVALID_ORIGINTYPE
	#		define wchar_t GAIA_INVALID_ORIGINTYPE
	#		define __wchar_t GAIA_INVALID_ORIGINTYPE
	#		define unsigned GAIA_INVALID_ORIGINTYPE
	#	endif
	#endif

	/* Common operation. */
	#define sizeofarray(arr) (sizeof(arr) / sizeof((arr)[0]))

	/* Class Base. All class's parent. */
	class Base
	{
	public:
		GAIA_ENUM_BEGIN(BASE_FEATURE)
			BASE_FEATURE_CAPACITY,
			BASE_FEATURE_SIZE,
		GAIA_ENUM_END(BASE_FEATURE)
	public:
		virtual ~Base(){}
		virtual GAIA::BL base_statistics(BASE_FEATURE of, GAIA::GVOID* pResult) const{return GAIA::False;}
		virtual GAIA::BL base_optimize(BASE_FEATURE of, GAIA::GVOID* pResult){return GAIA::False;}
	public:
	#ifndef GAIA_DEBUG_MEMORYLEAK
	#	if GAIA_OS == GAIA_OS_WINDOWS
			GINL GAIA::GVOID* operator new(size_t size);
			GINL GAIA::GVOID* operator new[] (size_t size);
	#	else
			GINL GAIA::GVOID* operator new(GAIA::UM size);
			GINL GAIA::GVOID* operator new[](GAIA::UM size);
	#	endif
		GINL GAIA::GVOID operator delete(GAIA::GVOID* p);
		GINL GAIA::GVOID operator delete[](GAIA::GVOID* p);
	#endif
	};

	/* Class Object. It's the all class's base(except high-performance container and math class. */
	class Object : public Base
	{
	public:
	};

	/* Class RefObject. If a class need a reference function, it will derived from here. */
	class RefObject : public Object
	{
	public:
		GINL RefObject(){m_nRef = 1; m_bDestructing = GAIA::False;}
		GINL ~RefObject(){}
		GINL GAIA::NM Reference();
		GINL GAIA::NM Release();
		GINL GAIA::NM GetRef() const{return m_nRef;}
	protected:
		virtual GAIA::GVOID Destruct(){}
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
		TYPEID_GCH,
		TYPEID_GWCH,
	GAIA_ENUM_END(TYPEID)

	static const GAIA::GCH* TYPEID_ANAME[] =
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
		"GCH",
		"GWCH",
	};

	static const GAIA::GWCH* TYPEID_WNAME[] =
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
		L"GCH",
		L"GWCH",
	};

	GINL TYPEID nametotype(const GAIA::GCH* psz);
	GINL TYPEID nametotype(const GAIA::GWCH* psz);

	/* Common type. */
	GAIA_ENUM_BEGIN(SEEK_TYPE)
		SEEK_TYPE_BEGIN,
		SEEK_TYPE_END,
		SEEK_TYPE_FORWARD,
		SEEK_TYPE_BACKWARD,
	GAIA_ENUM_END(SEEK_TYPE)

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
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_type_indp.h"
#endif

#ifndef GAIA_DEBUG_MEMORYLEAK
	namespace GAIA{namespace ALLOCATOR{class AllocatorESG;};};
	extern GAIA::ALLOCATOR::AllocatorESG g_global_allocator;
#	define GAIA_MALLOC(type, size) (type*)g_global_allocator.memory_alloc(sizeof(type) * size)
#	define GAIA_MRELEASE(p) g_global_allocator.memory_release(p)
#else
#	define GAIA_MALLOC(type, size) new type[size]
#	define GAIA_MRELEASE(p) delete[] p;
#endif

#endif
