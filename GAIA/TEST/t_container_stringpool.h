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
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		sp.clear();
		if(!sp.empty())
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		sp.destroy();
		if(!sp.empty())
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		sp.reserve(100);
		if(sp.capacity() != 100)
		{
		}
		s1 = sp.request(_T("HelloWorld"));
		if(GAIA::ALGORITHM::strcmp(sp.string(s1), _T("HelloWorld")) != 0)
		{
		}
		s2 = sp.request(_T("HelloKitty"));
		if(GAIA::ALGORITHM::strcmp(sp.string(s2), _T("HelloKitty")) != 0)
		{
		}
		if(sp.empty())
		{
		}
		if(sp.size() != 2)
		{
		}
		if(sp.capacity() < sp.size())
		{
		}
		if(sp == sp1)
		{
		}
		if(!(sp != sp1))
		{
		}
		if(!(sp >= sp1))
		{
		}
		if(sp <= sp1)
		{
		}
		if(!(sp > sp1))
		{
		}
		if(sp < sp1)
		{
		}
		s11 = sp1.request(_T("ABC"));
		if(GAIA::ALGORITHM::strcmp(sp1.string(s11), _T("ABC")) != 0)
		{
		}
		s22 = sp1.request(_T("DEF"));
		if(GAIA::ALGORITHM::strcmp(sp1.string(s22), _T("DEF")) != 0)
		{
		}
		if(sp == sp1)
		{
		}
		if(!(sp != sp1))
		{
		}
		if(!(sp >= sp1))
		{
		}
		if(sp <= sp1)
		{
		}
		if(!(sp > sp1))
		{
		}
		if(sp < sp1)
		{
		}
		sp1 = sp;
		if(!(sp == sp1))
		{
		}
		if(sp != sp1)
		{
		}
		if(!(sp >= sp1))
		{
		}
		if(!(sp <= sp1))
		{
		}
		if(sp > sp1)
		{
		}
		if(sp < sp1)
		{
		}
		if(sp.size() != 2)
		{
		}
		if(sp1.size() != 2)
		{
		}
		if(sp.capacity() < sp.size())
		{
		}
		if(sp1.capacity() < sp1.size())
		{
		}
		if(!sp.release(s1))
		{
		}
		if(!sp.release(s2))
		{
		}
		if(sp.release(s1))
		{
		}
		if(sp.release(s2))
		{
		}
		if(!sp1.release(s11))
		{
		}
		if(!sp1.release(s22))
		{
		}
		if(sp1.release(s11))
		{
		}
		if(sp1.release(s22))
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp1.size() != 0)
		{
		}
		return nRet;
	}
};

#endif
