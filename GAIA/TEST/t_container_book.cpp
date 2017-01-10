#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_book(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::SIZE SAMPLE_COUNT = 100;
		typedef GAIA::CTN::Book<GAIA::SIZE> __BookType;

		__BookType bt, bt1;
		if(!bt.empty())
		{
			GTLINE2("New book is not empty!");
			++nRet;
		}
		if(bt.size() != 0)
		{
			GTLINE2("New book's size is not zero!");
			++nRet;
		}
		if(bt.capacity() != 0)
		{
			GTLINE2("New book's capacity is not zero!");
			++nRet;
		}
		bt.clear();
		bt.destroy();
		if(!bt.empty())
		{
			GTLINE2("New book is not empty after clear and destroy!");
			++nRet;
		}
		if(bt.size() != 0)
		{
			GTLINE2("New book's size is not zero after clear and destroy!");
			++nRet;
		}
		if(bt.capacity() != 0)
		{
			GTLINE2("New book's capacity is not zero after clear and destroy!");
			++nRet;
		}
		if(!(bt == bt1))
		{
			GTLINE2("Empty book operator == error!");
			++nRet;
		}
		if(bt != bt1)
		{
			GTLINE2("Empty book operator != error!");
			++nRet;
		}
		if(!(bt >= bt1))
		{
			GTLINE2("Empty book operator >= error!");
			++nRet;
		}
		if(!(bt <= bt1))
		{
			GTLINE2("Empty book operator <= error!");
			++nRet;
		}
		if(bt > bt1)
		{
			GTLINE2("Empty book operator > error!");
			++nRet;
		}
		if(bt < bt1)
		{
			GTLINE2("Empty book operator < error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::SIZE sUsedIndex = bt.set(x);
			if(sUsedIndex != x)
			{
				GTLINE2("Book set error!");
				break;
			}
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::SIZE sFixedIndex = bt.fixedindex(x);
			if(sFixedIndex != x)
			{
				GTLINE2("Book get fixedindex error!");
				++nRet;
				break;
			}
			GAIA::SIZE sUsedIndex = bt.usedindex(sFixedIndex);
			if(sUsedIndex != x)
			{
				GTLINE2("Book get usedindex error!");
				++nRet;
				break;
			}
			if(bt.find(x) != sUsedIndex)
			{
				GTLINE2("Book find error!");
				++nRet;
				break;
			}
		}
		bt1 = bt;
		if(bt.capacity() < bt.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		if(bt1.capacity() < bt1.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		if(!(bt == bt1))
		{
			GTLINE2("Book operator == error!");
			++nRet;
		}
		if(bt != bt1)
		{
			GTLINE2("Book operator != error!");
			++nRet;
		}
		if(!(bt >= bt1))
		{
			GTLINE2("Book operator >= error!");
			++nRet;
		}
		if(!(bt <= bt1))
		{
			GTLINE2("Book operator <= error!");
			++nRet;
		}
		if(bt > bt1)
		{
			GTLINE2("Book operator > error!");
			++nRet;
		}
		if(bt < bt1)
		{
			GTLINE2("Book operator < error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; x += 10)
		{
			GAIA::SIZE usedindex = bt.usedindex(x);
			if(usedindex == GINVALID)
			{
				GTLINE2("Book erase error!");
				++nRet;
				break;
			}
			if(!bt.erase(usedindex))
			{
				GTLINE2("Book erase error!");
				++nRet;
				break;
			}
		}
		if(bt.size() != SAMPLE_COUNT - SAMPLE_COUNT / 10)
		{
			GTLINE2("Book erase error!");
			++nRet;
		}
		if(bt.capacity() < bt.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::SIZE usedindex = bt.usedindex(x);
			if(usedindex == GINVALID)
				continue;
			if(usedindex >= SAMPLE_COUNT - SAMPLE_COUNT / 10)
			{
				GTLINE2("Book erase error!");
				++nRet;
				break;
			}
		}
		if(bt1.capacity() < bt1.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		if(bt == bt1)
		{
			GTLINE2("Book operator == error!");
			++nRet;
		}
		if(!(bt != bt1))
		{
			GTLINE2("Book operator != error!");
			++nRet;
		}
		if(bt >= bt1)
		{
			GTLINE2("Book operator >= error!");
			++nRet;
		}
		if(!(bt <= bt1))
		{
			GTLINE2("Book operator <= error!");
			++nRet;
		}
		if(bt > bt1)
		{
			GTLINE2("Book operator > error!");
			++nRet;
		}
		if(!(bt < bt1))
		{
			GTLINE2("Book operator < error!");
			++nRet;
		}

		bt1 = bt;
		if(bt.capacity() < bt.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		if(bt1.capacity() < bt1.size())
		{
			GTLINE2("Book capacity error!");
			++nRet;
		}
		if(!(bt == bt1))
		{
			GTLINE2("Book operator == error!");
			++nRet;
		}
		if(bt != bt1)
		{
			GTLINE2("Book operator != error!");
			++nRet;
		}
		if(!(bt >= bt1))
		{
			GTLINE2("Book operator >= error!");
			++nRet;
		}
		if(!(bt <= bt1))
		{
			GTLINE2("Book operator <= error!");
			++nRet;
		}
		if(bt > bt1)
		{
			GTLINE2("Book operator > error!");
			++nRet;
		}
		if(bt < bt1)
		{
			GTLINE2("Book operator < error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT - SAMPLE_COUNT / 10; ++x)
		{
			if(!bt.erase(0))
			{
				GTLINE2("Book erase error!");
				++nRet;
				break;
			}
		}
		if(!bt.empty())
		{
			GTLINE2("Book erase error!");
			++nRet;
		}
		if(bt.size() != 0)
		{
			GTLINE2("Book erase error!");
			++nRet;
		}
		if(bt.capacity() <= 0)
		{
			GTLINE2("Book erase error!");
			++nRet;
		}
		bt.clear();
		bt.destroy();

		{
			GAIA::SIZE u1 = bt.set(0);
			GAIA::SIZE f1 = bt.fixedindex(u1);
			GAIA::SIZE u2 = bt.set(1);
			GAIA::SIZE f2 = bt.fixedindex(u2);
			if(!bt.erase(bt.usedindex(f1)))
			{
				GTLINE2("Book erase error!");
				++nRet;
			}
			u2 = bt.usedindex(f2);
			if(u2 == GINVALID)
			{
				GTLINE2("Book usedindex error!");
				++nRet;
			}
		}

		return nRet;
	}
};
