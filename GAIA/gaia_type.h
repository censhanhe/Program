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

	class N128
	{
	public:
	private:
	};

	class U128
	{
	public:
	private:
	};

	/* Float type declaration. */
	typedef float F32;
	typedef double F64;
	typedef float REAL;

	/* Char type declaration. */
	typedef char CHAR;
	typedef wchar_t WCHAR;
#if GAIA_CHARFMT == GAIA_CHARFMT_UNICODE
	typedef wchar_t TCHAR;
#else
	typedef char TCHAR;
#endif

	/* Bool enum. */
	static const BL True = 1;
	static const BL False = 0;

	/* Common constants. */
	#define NULL 0

	/* Void. */
	typedef void VOID;

	/* Undefine origin type. */
#ifdef GAIA_DEBUG_CODEPURE
#	define bool 1
#	define true 1
#	define false 1
#	define char 1
#	define short 1
#	define int 1
#	define long 1
#	define float 1
#	define double 1
#	define wchar_t 1
#	define __wchar_t 1
#	define unsigned 1
#endif
}


#endif