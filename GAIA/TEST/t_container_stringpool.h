#ifndef 	__T_CONTAINER_STRINGPOOL_H__
#define 	__T_CONTAINER_STRINGPOOL_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_stringpool(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::StringPool<GAIA::TCH> __StringPoolType;

		__StringPoolType sp, sp1;
		GAIA::SIZE s1, s2, s11, s22;
		if(!sp.empty())
		{
			GTLINE2("New StringPool must empty!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("New StringPool size must 0!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("New StringPool capacity must 0!");
			++nRet;
		}
		sp.clear();
		if(!sp.empty())
		{
			GTLINE2("New StringPool must empty!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("New StringPool size must 0!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("New StringPool capacity must 0!");
			++nRet;
		}
		sp.destroy();
		if(!sp.empty())
		{
			GTLINE2("New StringPool must empty!");
			++nRet;
		}
		if(sp.size() != 0)
		{
			GTLINE2("New StringPool size must 0!");
			++nRet;
		}
		if(sp.capacity() != 0)
		{
			GTLINE2("New StringPool capacity must 0!");
			++nRet;
		}
		sp.reserve(100);
		if(sp.capacity() != 100)
		{
			GTLINE2("StringPool reserve error!");
			++nRet;
		}
		s1 = sp.request(_T("HelloWorld"));
		if(GAIA::ALGORITHM::strcmp(sp.string(s1), _T("HelloWorld")) != 0)
		{
			GTLINE2("StringPool request error!");
			++nRet;
		}
		s2 = sp.request(_T("HelloKitty"));
		if(GAIA::ALGORITHM::strcmp(sp.string(s2), _T("HelloKitty")) != 0)
		{
			GTLINE2("StringPool request error!");
			++nRet;
		}
		if(sp.empty())
		{
			GTLINE2("StringPool empty error!");
			++nRet;
		}
		if(sp.size() != 2)
		{
			GTLINE2("StringPool size error!");
			++nRet;
		}
		if(sp.capacity() < sp.size())
		{
			GTLINE2("StringPool capacity error!");
			++nRet;
		}
		if(sp == sp1)
		{
			GTLINE2("StringPool operator == error!");
			++nRet;
		}
		if(!(sp != sp1))
		{
			GTLINE2("StringPool operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StringPool operator >= error!");
			++nRet;
		}
		if(sp <= sp1)
		{
			GTLINE2("StringPool operator <= error!");
			++nRet;
		}
		if(!(sp > sp1))
		{
			GTLINE2("StringPool operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StringPool operator < error!");
			++nRet;
		}
		s11 = sp1.request(_T("ABC"));
		if(GAIA::ALGORITHM::strcmp(sp1.string(s11), _T("ABC")) != 0)
		{
			GTLINE2("StringPool request error!");
			++nRet;
		}
		s22 = sp1.request(_T("DEF"));
		if(GAIA::ALGORITHM::strcmp(sp1.string(s22), _T("DEF")) != 0)
		{
			GTLINE2("StringPool request error!");
			++nRet;
		}
		if(sp == sp1)
		{
			GTLINE2("StringPool operator == error!");
			++nRet;
		}
		if(!(sp != sp1))
		{
			GTLINE2("StringPool operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StringPool operator >= error!");
			++nRet;
		}
		if(sp <= sp1)
		{
			GTLINE2("StringPool operator <= error!");
			++nRet;
		}
		if(!(sp > sp1))
		{
			GTLINE2("StringPool operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StringPool operator < error!");
			++nRet;
		}
		sp1 = sp;
		if(!(sp == sp1))
		{
			GTLINE2("StringPool operator == error!");
			++nRet;
		}
		if(sp != sp1)
		{
			GTLINE2("StringPool operator != error!");
			++nRet;
		}
		if(!(sp >= sp1))
		{
			GTLINE2("StringPool operator >= error!");
			++nRet;
		}
		if(!(sp <= sp1))
		{
			GTLINE2("StringPool operator <= error!");
			++nRet;
		}
		if(sp > sp1)
		{
			GTLINE2("StringPool operator > error!");
			++nRet;
		}
		if(sp < sp1)
		{
			GTLINE2("StringPool operator < error!");
			++nRet;
		}
		if(sp.size() != 2)
		{
			GTLINE2("StringPool size error!");
			++nRet;
		}
		if(sp1.size() != 2)
		{
			GTLINE2("StringPool size error!");
			++nRet;
		}
		if(sp.capacity() < sp.size())
		{
			GTLINE2("StringPool capacity error!");
			++nRet;
		}
		if(sp1.capacity() < sp1.size())
		{
			GTLINE2("StringPool capacity error!");
			++nRet;
		}
		if(!sp.release(s1))
		{
			GTLINE2("StringPool release failed!");
			++nRet;
		}
		if(!sp.release(s2))
		{
			GTLINE2("StringPool release failed!");
			++nRet;
		}
		if(!sp1.release(s11))
		{
			GTLINE2("StringPool release failed!");
			++nRet;
		}
		if(!sp1.release(s22))
		{
			GTLINE2("StringPool release failed!");
			++nRet;
		}
		if(sp.practice_size() != 0)
		{
			GTLINE2("StringPool size must been 0 after release all elements failed!");
			++nRet;
		}
		if(sp1.practice_size() != 0)
		{
			GTLINE2("StringPool size must been 0 after release all elements failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
