#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_stringpool(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::StringPool<GAIA::TCH> __StringPoolType;

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
		s1 = sp.alloc(_T("HelloWorld"));
		if(GAIA::ALGO::strcmp(sp.get(s1), _T("HelloWorld")) != 0)
		{
			GTLINE2("StringPool alloc error!");
			++nRet;
		}
		s2 = sp.alloc(_T("HelloKitty"));
		if(GAIA::ALGO::strcmp(sp.get(s2), _T("HelloKitty")) != 0)
		{
			GTLINE2("StringPool alloc error!");
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
		s11 = sp1.alloc(_T("ABC"));
		if(GAIA::ALGO::strcmp(sp1.get(s11), _T("ABC")) != 0)
		{
			GTLINE2("StringPool alloc error!");
			++nRet;
		}
		s22 = sp1.alloc(_T("DEF"));
		if(GAIA::ALGO::strcmp(sp1.get(s22), _T("DEF")) != 0)
		{
			GTLINE2("StringPool alloc error!");
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
