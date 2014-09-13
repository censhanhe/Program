#ifndef 	__T_CONTAINER_STATICSTRINGPOOL_H__
#define 	__T_CONTAINER_STATICSTRINGPOOL_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_staticstringpool(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::StaticStringPool<GAIA::TCH> __StaticStringPoolType;
		__StaticStringPoolType sp, sp1;
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
		sp.request(_T("HelloWorld"));
		sp.request(_T("HelloKitty"));
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
		sp1.request(_T("ABC"));
		sp1.request(_T("EFG"));
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
		if(sp.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")) + 1 + GAIA::ALGORITHM::strlen(_T("HelloKitty")) + 1)
		{
			GTLINE2("StaticStringPool request cause size error");
			++nRet;
		}
		if(sp.capacity() < sp.size())
		{
			GTLINE2("StaticStringPool request cause capacity error");
			++nRet;
		}
		if(sp.string_size() != 2)
		{
			GTLINE2("StaticStringPool string_size error");
			++nRet;
		}
		if(sp.string(0) == GNULL)
		{ 
			GTLINE2("StaticStringPool string error");
			++nRet;
		}
		if(GAIA::ALGORITHM::strcmp(sp.string(0), _T("HelloWorld")) != 0)
		{
			GTLINE2("StaticStringPool string content error");
			++nRet;
		}
		if(sp.string(1) == GNULL)
		{
			GTLINE2("StaticStringPool string error");
			++nRet;
		}
		if(GAIA::ALGORITHM::strcmp(sp.string(1), _T("HelloKitty")) != 0)
		{
			GTLINE2("StaticStringPool string content error");
			++nRet;
		}
		sp.clear();
		__StaticStringPoolType::_sizetype s1 = sp.request(_T("HelloKitty"));
		__StaticStringPoolType::_sizetype s2 = sp.request(_T("HelloKitty"));
		if(s1 != s2)
		{
			GTLINE2("StaticStringPool same string must at same position!");
			++nRet;
		}
		return nRet;
	}
};

#endif
