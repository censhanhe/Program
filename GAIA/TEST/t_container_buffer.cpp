#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_buffer(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::BasicBuffer<GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::U32> > __BufferType;
		__BufferType b;
		if(!b.empty())
		{
			GTLINE2("New buffer is not empty!");
			++nRet;
		}
		if(b.read_size() != 0)
		{
			GTLINE2("New buffer read_size is not zero!");
			++nRet;
		}
		if(b.write_size() != 0)
		{
			GTLINE2("New buffer write_size is not zero!");
			++nRet;
		}
		if(b.capacity() != 0)
		{
			GTLINE2("New buffer capacity is not zero!");
			++nRet;
		}
		if(b.front_ptr() != GNIL || b.back_ptr() != GNIL)
		{
			GTLINE2("New buffer front_ptr or back_ptr is not GNIL!");
			++nRet;
		}
		if(b.read_ptr() != GNIL || b.write_ptr() != GNIL)
		{
			GTLINE2("New buffer read_ptr or write_ptr is not GNIL!");
			++nRet;
		}
		if(static_cast<const __BufferType*>(&b)->front_ptr() != GNIL || static_cast<const __BufferType*>(&b)->back_ptr() != GNIL)
		{
			GTLINE2("New buffer front_ptr or back_ptr is not GNIL!");
			++nRet;
		}
		if(static_cast<const __BufferType*>(&b)->read_ptr() != GNIL || static_cast<const __BufferType*>(&b)->write_ptr() != GNIL)
		{
			GTLINE2("New buffer read_ptr or write_ptr is not GNIL!");
			++nRet;
		}
		b.reserve(100);
		if(b.read_size() != 0 || b.write_size() != 0)
		{
			GTLINE2("Buffer reserve failed!");
			++nRet;
		}
		if(!b.empty())
		{
			GTLINE2("Buffer reserve failed!");
			++nRet;
		}
		b.resize(50);
		if(b.read_size() != 0 || b.write_size() != 50)
		{
			GTLINE2("Buffer resize failed!");
			++nRet;
		}
		b.clear();
		if(b.read_size() != 0 || b.write_size() != 0)
		{
			GTLINE2("Buffer clear failed!");
			++nRet;
		}
		if(b.capacity() == 0)
		{
			GTLINE2("Buffer clear failed!");
			++nRet;
		}
		b.destroy();
		if(b.read_size() != 0 || b.write_size() != 0)
		{
			GTLINE2("Buffer destroy failed!");
			++nRet;
		}
		if(b.capacity() != 0)
		{
			GTLINE2("Buffer destory failed!");
			++nRet;
		}
		b.resize(100);
		if(b.read_size() != 0 || b.write_size() == 0)
		{
			GTLINE2("Buffer resize faile!");
			++nRet;
		}
		b.write(_T("HelloWorld"), GAIA::ALGO::strlen(_T("HelloWorld")) * sizeof(GAIA::TCH) + sizeof(GAIA::TCH));
		if(b.write_size() != 100 + GAIA::ALGO::strlen(_T("HelloWorld")) * sizeof(GAIA::TCH) + sizeof(GAIA::TCH))
		{
			GTLINE2("Buffer write cause write_size failed");
			++nRet;
		}
		if(b.read_size() != 0)
		{
			GTLINE2("Buffer write cause read_size error!");
			++nRet;
		}
		if(b.capacity() < b.write_size())
		{
			GTLINE2("Buffer capacity below write_size error!");
			++nRet;
		}
		GAIA::U8 arr[100];
		if(!b.read(arr, sizeof(arr)))
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		GAIA::TCH sz[100];
		if(!b.read(sz))
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(sz, _T("HelloWorld")) != 0)
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		if(b.read_size() != b.write_size())
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		if(!b.seek_write(0, GAIA::SEEK_TYPE_BEGIN))
		{
			GTLINE2("Buffer seek_write failed!");
			++nRet;
		}
		if(!b.seek_read(0, GAIA::SEEK_TYPE_BEGIN))
		{
			GTLINE2("Buffer seek_read failed!");
			++nRet;
		}
		GAIA::ALGO::xmemset(arr, 0xFF, sizeof(arr));
		b.write(arr, sizeof(arr));
		b.seek_read(b.write_size(), GAIA::SEEK_TYPE_BEGIN);
		if(!b.read(sz))
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(sz, _T("HelloWorld")) != 0)
		{
			GTLINE2("Buffer write cause content error!");
			++nRet;
		}
		if(b.read_size() <= b.write_size())
		{
			GTLINE2("Buffer read cause read_size error!");
			++nRet;
		}
		b.seek_read(b.write_size(), GAIA::SEEK_TYPE_BEGIN);
		GAIA::ALGO::xmemset(sz, 0xFF, sizeof(sz));
		if(!b.read(sz, GAIA::ALGO::strlen(_T("HelloWorld")) * sizeof(GAIA::TCH) + sizeof(GAIA::TCH)))
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(sz, _T("HelloWorld")) != 0)
		{
			GTLINE2("Buffer read failed!");
			++nRet;
		}
		b.destroy();
		b.write(_T("HelloWorld"));
		__BufferType b1 = b;
		GAIA::ALGO::xmemset(sz, 0xFF, sizeof(sz));
		b1.read(sz);
		if(GAIA::ALGO::strcmp(sz, _T("HelloWorld")) != 0)
		{
			GTLINE2("Buffer operator = failed!");
			++nRet;
		}
		if(!(b == b1))
		{
			GTLINE2("Buffer operator == failed!");
			++nRet;
		}
		if(!(b >= b1))
		{
			GTLINE2("Buffer operator >= failed!");
			++nRet;
		}
		if(!(b <= b1))
		{
			GTLINE2("Buffer operator <= failed!");
			++nRet;
		}
		if(b != b1)
		{
			GTLINE2("Buffer operator != failed!");
			++nRet;
		}
		if(b > b1)
		{
			GTLINE2("Buffer operator > failed!");
			++nRet;
		}
		if(b < b1)
		{
			GTLINE2("Buffer operator < failed!");
			++nRet;
		}
		if(!(b1 == b && b1 >= b && b1 <= b))
		{
			GTLINE2("Buffer operator == >= <= failed!");
			++nRet;
		}
		if(b1 != b || b1 > b || b1 < b)
		{
			GTLINE2("Buffer operator != > < failed!");
			++nRet;
		}
		return nRet;
	}
};
