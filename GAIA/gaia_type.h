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

	/* Bool enum. */
	static const BL True = 1;
	static const BL False = 0;

	/* Void. */
	typedef void GVOID;

	/* X128 */
	class X128
	{
	public:
		GINL X128& operator = (const X128& src){u0 = src.u0; u1 = src.u1; u2 = src.u2; u3 = src.u3;return *this;}
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
		GINL BL operator == (const X128& src) const
		{
			if(u0 == src.u0 && u1 == src.u1 && u2 == src.u2 && u3 == src.u3)
				return GAIA::True;
			return GAIA::False;
		}
		GINL BL operator != (const X128& src) const{return !this->operator == (src);}
		GINL BL operator <= (const X128& src) const
		{
			if(u0 < src.u0)
				return GAIA::True;
			else if(u0 > src.u0)
				return GAIA::False;
			if(u1 < src.u1)
				return GAIA::True;
			else if(u1 > src.u1)
				return GAIA::False;
			if(u2 < src.u2)
				return GAIA::True;
			else if(u2 > src.u2)
				return GAIA::False;
			if(u3 < src.u3)
				return GAIA::True;
			else if(u3 > src.u3)
				return GAIA::False;
			return GAIA::True;
		}
		GINL BL operator >= (const X128& src) const
		{
			if(u0 > src.u0)
				return GAIA::True;
			else if(u0 < src.u0)
				return GAIA::False;
			if(u1 > src.u1)
				return GAIA::True;
			else if(u1 < src.u1)
				return GAIA::False;
			if(u2 > src.u2)
				return GAIA::True;
			else if(u2 < src.u2)
				return GAIA::False;
			if(u3 > src.u3)
				return GAIA::True;
			else if(u3 < src.u3)
				return GAIA::False;
			return GAIA::True;
		}
		GINL BL operator < (const X128& src) const{return !this->operator >= (src);}
		GINL BL operator > (const X128& src) const{return !this->operator <= (src);}
		union
		{
			class
			{
			public:
				GAIA::U32 u0;
				GAIA::U32 u1;
				GAIA::U32 u2;
				GAIA::U32 u3;
			};
			GAIA::U32 u[4];
		};
	};

	/* Global constants. */
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSTRUE = GAIA::True;
	static GAIA_DEBUG_CONST GAIA::BL ALWAYSFALSE = GAIA::False;

	/* Common constants. */
	#define GNULL 0
	#define GINVALID (~0)

	/* Undefine origin type. */
	#ifdef GAIA_DEBUG_CODEPURE
	#	ifndef GAIA_NOCANCEL_ORIGINTYPE
	#		define bool 1
	#		define true 1
	#		define false 1
	#		define char 1
	#		define short 1
	#		define int 1
	#		define long 1
	#		define float 1
	#		define double 1
	#		define wchar_t 1
	#		define __wchar_t 1
	#		define unsigned 1
	#	endif
	#endif

	/* Class Base. All class's parent. */
	class Base
	{
	public:
		GAIA_ENUM_BEGIN(BASE_FEATURE)
			BASE_FEATURE_CAPACITY,
			BASE_FEATURE_SIZE,
		GAIA_ENUM_END(BASE_FEATURE)
	public:
		virtual GAIA::BL base_statistics(BASE_FEATURE of, GAIA::GVOID* pResult) const{return GAIA::False;}
		virtual GAIA::BL base_optimize(BASE_FEATURE of, GAIA::GVOID* pResult){return GAIA::False;}
	};

	/* Class Object. It's the all class's base(except high-performance container and math class. */
	class Object : public Base
	{
	public:
		virtual ~Object(){}
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
		volatile GAIA::NM m_nRef;
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

	/* Seek type. */
	GAIA_ENUM_BEGIN(SEEK_TYPE)
		SEEK_TYPE_BEGIN,
		SEEK_TYPE_END,
		SEEK_TYPE_FORWARD,
		SEEK_TYPE_BACKWARD,
	GAIA_ENUM_END(SEEK_TYPE)
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_type_indp.h"
#endif

#endif
