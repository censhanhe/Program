#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_staticstringpool(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::StaticStringPool<GAIA::TCH> __StaticStringPoolType;
		__StaticStringPoolType sp, sp1;

		__StaticStringPoolType::_sizetype s1;
		__StaticStringPoolType::_sizetype s2;

		if(!sp.empty())
		{
			GTLINE2("New StaticStringPool must been empty!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("New StaticStringPool size must been zero!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("New StaticStringPool capacity must been zero!");
			++nRet;
		}
		if(sp.string_size() != 0)
		{
			GTLINE2("New StaticStringPool string_size must been zero!");
			++nRet;
		}
		sp.clear();
		if(!sp.empty())
		{
			GTLINE2("StaticStringPool clear cause empty error!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("StaticStringPool clear cause size error!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("StaticStringPool clear cause capacity error!");
			++nRet;
		}
		if(sp.string_size() != 0)
		{
			GTLINE2("StaticStringPool clear cause string_size error!");
			++nRet;
		}
		sp.destroy();
		if(!sp.empty())
		{
			GTLINE2("StaticStringPool destroy cause empty error!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("StaticStringPool destroy cause size error!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("StaticStringPool destroy cause capacity error!");
			++nRet;
		}
		if(sp.string_size() != 0)
		{
			GTLINE2("StaticStringPool destroy cause string_size error!");
			++nRet;
		}
		sp1.clear();
		sp = sp1;
		if(!(sp == sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator == error!");
			++nRet;
		}
		if(sp != sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator >= error!");
			++nRet;
		}
		if(!(sp <= sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator <= error!");
			++nRet;
		}
		if(sp > sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator < error!");
			++nRet;
		}
		s1 = sp.alloc(_T("HelloWorld"));
		if(GAIA::ALGO::strcmp(sp.get(s1), _T("HelloWorld")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		s2 = sp.alloc(_T("HelloKitty"));
		if(GAIA::ALGO::strcmp(sp.get(s2), _T("HelloKitty")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		if(sp == sp1)
		{
			GTLINE2("StaticStringPool operator == error!");
			++nRet;
		}
		if(!(sp != sp1))
		{
			GTLINE2("StaticStringPool operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StaticStringPool operator >= error!");
			++nRet;
		}
		if(sp <= sp1)
		{
			GTLINE2("StaticStringPool operator <= error!");
			++nRet;
		}
		if(!(sp > sp1))
		{
			GTLINE2("StaticStringPool operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StaticStringPool operator < error!");
			++nRet;
		}
		s1 = sp1.alloc(_T("ABC"));
		if(GAIA::ALGO::strcmp(sp1.get(s1), _T("ABC")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		s2 = sp1.alloc(_T("EFG"));
		if(GAIA::ALGO::strcmp(sp1.get(s2), _T("EFG")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		if(sp == sp1)
		{
			GTLINE2("StaticStringPool operator == error!");
			++nRet;
		}
		if(!(sp != sp1))
		{
			GTLINE2("StaticStringPool operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StaticStringPool operator >= error!");
			++nRet;
		}
		if(sp <= sp1)
		{
			GTLINE2("StaticStringPool operator <= error!");
			++nRet;
		}
		if(!(sp > sp1))
		{
			GTLINE2("StaticStringPool operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StaticStringPool operator < error!");
			++nRet;
		}
		sp1 = sp;
		if(!(sp == sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator == error!");
			++nRet;
		}
		if(sp != sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator >= error!");
			++nRet;
		}
		if(!(sp <= sp1))
		{
			GTLINE2("StaticStringPool operator = cause operator <= error!");
			++nRet;
		}
		if(sp > sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StaticStringPool operator = cause operator < error!");
			++nRet;
		}
		if(sp.size() != GAIA::ALGO::strlen(_T("HelloWorld")) + 1 + GAIA::ALGO::strlen(_T("HelloKitty")) + 1)
		{
			GTLINE2("StaticStringPool alloc cause size error");
			++nRet;
		}
		if(sp.capacity() < sp.size())
		{
			GTLINE2("StaticStringPool alloc cause capacity error");
			++nRet;
		}
		if(sp.string_size() != 2)
		{
			GTLINE2("StaticStringPool string_size error");
			++nRet;
		}
		if(sp.get(0) == GNIL)
		{ 
			GTLINE2("StaticStringPool string error");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(sp.get(0), _T("HelloWorld")) != 0)
		{
			GTLINE2("StaticStringPool string content error");
			++nRet;
		}
		if(sp.get(1) == GNIL)
		{
			GTLINE2("StaticStringPool string error");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(sp.get(1), _T("HelloKitty")) != 0)
		{
			GTLINE2("StaticStringPool string content error");
			++nRet;
		}
		sp.clear();
		s1 = sp.alloc(_T("HelloWorld"));
		if(GAIA::ALGO::strcmp(sp.get(s1), _T("HelloWorld")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		s2 = sp.alloc(_T("HelloKitty"));
		if(GAIA::ALGO::strcmp(sp.get(s2), _T("HelloKitty")) != 0)
		{
			GTLINE2("StaticStringPool alloc error!");
			++nRet;
		}
		if(s1 == s2)
		{
			GTLINE2("StaticStringPool different string must at different position!");
			++nRet;
		}
		s2 = sp.alloc(_T("HelloWorld"));
		if(s1 != s2)
		{
			GTLINE2("StaticStringPool same string must at same position!");
			++nRet;
		}
		return nRet;
	}
};
