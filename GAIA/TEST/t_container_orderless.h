#ifndef		__T_CONTAINER_ORDERLESS_H__
#define		__T_CONTAINER_ORDERLESS_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_orderless(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		static const GAIA::SIZE SAMPLE_COUNT = 100;
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::TString __StrType;
		typedef GAIA::CTN::Orderless<__StrType> __OrderlessType;

		__OrderlessType ol;
		if(ol.size() != 0)
		{
			GTLINE2("New orderless size must been zero!");
			++nRet;
		}
		if(ol.capacity() != 0)
		{
			GTLINE2("New orderless capacity must been zero!");
			++nRet;
		}
		if(!ol.empty())
		{
			GTLINE2("New orderless must been empty!");
			++nRet;
		}
		ol.clear();
		if(ol.size() != 0)
		{
			GTLINE2("Orderless clean error!");
			++nRet;
		}
		if(ol.capacity() != 0)
		{
			GTLINE2("Orderless clean error!");
			++nRet;
		}
		if(!ol.empty())
		{
			GTLINE2("Orderless clean error!");
			++nRet;
		}
		ol.destroy();
		if(ol.size() != 0)
		{
			GTLINE2("Orderless destroy error!");
			++nRet;
		}
		if(ol.capacity() != 0)
		{
			GTLINE2("Orderless destroy error!");
			++nRet;
		}
		if(!ol.empty())
		{
			GTLINE2("Orderless destroy error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CTN::TString str = x;
			str = _T("HelloWorld") + str;
			if(ol.insert(str) != x)
			{
				GTLINE2("Orderless insert failed!");
				++nRet;
				break;
			}
		}
		if(ol.size() != SAMPLE_COUNT)
		{
			GTLINE2("Orderless insert cause size error!");
			++nRet;
		}
		if(ol.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Orderless insert cause capacity error!");
			++nRet;
		}
		if(ol.empty())
		{
			GTLINE2("Orderless insert cause empty error!");
			++nRet;
		}
		ol.clear();
		ol.destroy();
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CTN::TString str = x;
			str = _T("HelloWorld") + str;
			if(ol.insert(str) != x)
			{
				GTLINE2("Orderless insert(twice) failed!");
				++nRet;
				break;
			}
		}
		if(ol.find(_T("HelloWorld")) != GINVALID)
		{
			GTLINE2("Orderless find failed!");
			++nRet;
		}
		if(ol.find(_T("HelloWorld0")) == GINVALID)
		{
			GTLINE2("Orderless find failed!");
			++nRet;
		}
		if(ol.find(_T("HelloWorld1")) == GINVALID)
		{
			GTLINE2("Orderless find failed!");
			++nRet;
		}
		GAIA::CTN::TString strTemp = SAMPLE_COUNT - 1;
		strTemp = _T("HelloWorld") + strTemp;
		if(ol.find(strTemp) == GINVALID)
		{
			GTLINE2("Orderless find failed!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < ol.size(); ++x)
		{
			if(!ol.exist(x))
			{
				GTLINE2("Orderless exist failed!");
				++nRet;
				break;
			}
		}
		if(!ol.erase_index(0))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.find(_T("HelloWorld0")) != GINVALID)
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.exist(0))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(!ol.erase_index(1))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.find(_T("HelloWorld1")) != GINVALID)
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.exist(1))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(!ol.erase_index(10))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.find(_T("HelloWorld10")) != GINVALID)
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.exist(10))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(!ol.erase_index(SAMPLE_COUNT - 1))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.find(strTemp) != GINVALID)
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		if(ol.exist(SAMPLE_COUNT - 1))
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		GAIA::SIZE uExistCount = 0;
		for(GAIA::SIZE x = 0; x < ol.size(); ++x)
		{
			if(ol.exist(x))
				++uExistCount;
		}
		if(uExistCount != SAMPLE_COUNT - 4)
		{
			GTLINE2("Orderless erase_index failed!");
			++nRet;
		}
		ol.destroy();
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CTN::TString str = x;
			str = _T("HelloWorld") + str;
			if(ol.insert(str) != x)
			{
				GTLINE2("Orderless insert(twice) failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CTN::TString str = x;
			str = _T("HelloWorld") + str;
			if(ol.insert(str) != x + SAMPLE_COUNT)
			{
				GTLINE2("Orderless insert(twice) failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CTN::TString str = x;
			str = _T("HelloWorld") + str;
			if(!ol.erase(str))
			{
				GTLINE2("Orderless erase failed!");
				++nRet;
				break;
			}
		}
		if(ol.size() != SAMPLE_COUNT * 2)
		{
			GTLINE2("Orderless erase cause size error!");
			++nRet;
		}
		if(ol.practice_size() != 0)
		{
			GTLINE2("Orderless erase cause practice_size error!");
			++nRet;
		}
		if(ol.capacity() == 0)
		{
			GTLINE2("Orderless erase cause capacity error!");
			++nRet;
		}
		if(!ol.empty())
		{
			GTLINE2("Orderless erase cause empty error!");
			++nRet;
		}
		return nRet;
	}
};

#endif
