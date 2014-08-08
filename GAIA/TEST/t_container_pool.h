#ifndef		__T_CONTAINER_POOL_H__
#define		__T_CONTAINER_POOL_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_pool(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::SIZE SAMPLE_COUNT = 100;
		typedef GAIA::CONTAINER::Pool<GAIA::CONTAINER::TString> __PoolType;
		__PoolType pl;
		__PoolType parentpl;
		__PoolType parentparentpl;
		GAIA::CONTAINER::Vector<GAIA::CONTAINER::TString*> listTemp;
		__PoolType::__IndexListType listIndex;

BIND_POOL:
		if(!pl.empty())
		{
			GTLINE2("New pool must empty!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("New pool size must zero!");
			++nRet;
		}
		if(pl.capacity() != 0)
		{
			GTLINE2("New pool capacity must zero!");
			++nRet;
		}
		pl.clear();
		if(!pl.empty())
		{
			GTLINE2("New pool must empty after call clear!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("New pool size must zero after call clear!");
			++nRet;
		}
		if(pl.capacity() != 0)
		{
			GTLINE2("New pool capacity must zero after call clear!");
			++nRet;
		}
		pl.destroy();
		if(!pl.empty())
		{
			GTLINE2("New pool must empty after call destroy!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("New pool size must zero after call destroy!");
			++nRet;
		}
		if(pl.capacity() != 0)
		{
			GTLINE2("New pool capacity must zero after call destroy!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CONTAINER::TString* p = pl.alloc();
			GAIA_AST(p != GNULL);
			listTemp.push_back(p);
		}
		if(pl.empty())
		{
			GTLINE2("Pool empty error caused by alloc!");
			++nRet;
		}
		if(pl.size() != SAMPLE_COUNT)
		{
			GTLINE2("Pool size error caused by alloc!");
			++nRet;
		}
		if(pl.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Pool capacity error caused by alloc!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CONTAINER::TString* p = listTemp[x];
			GAIA_AST(p != GNULL);
			if(!pl.release(p))
			{
				GTLINE2("Pool release failed!");
				++nRet;
				break;
			}
		}
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by release!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by release!");
			++nRet;
		}
		if(pl.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Pool capacity error caused by release!");
			++nRet;
		}
		pl.clear();
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by clear!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by clear!");
			++nRet;
		}
		if(pl.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Pool capacity error caused by clear!");
			++nRet;
		}
		pl.destroy();
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by destroy!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by destroy!");
			++nRet;
		}
		if(pl.capacity() != 0)
		{
			GTLINE2("Pool capacity error caused by destroy!");
			++nRet;
		}
		listTemp.clear();
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CONTAINER::TString* p = pl.alloc();
			GAIA_AST(p != GNULL);
			listTemp.push_back(p);
		}
		pl.clear();
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by clear!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by clear!");
			++nRet;
		}
		if(pl.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Pool capacity error caused by clear!");
			++nRet;
		}
		pl.destroy();
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by destroy!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by destroy!");
			++nRet;
		}
		if(pl.capacity() != 0)
		{
			GTLINE2("Pool capacity error caused by destroy!");
			++nRet;
		}
		listTemp.clear();
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::CONTAINER::TString* p = pl.alloc();
			GAIA_AST(p != GNULL);
			listTemp.push_back(p);
		}
		pl.collect_valid_index_list(listIndex);
		if(listIndex.size() != SAMPLE_COUNT)
		{
			GTLINE2("Pool collect_valid_index_list error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < listIndex.size(); ++x)
		{
			GAIA::SIZE index = listIndex[x];
			GAIA::CONTAINER::TString& str = pl[index];
			GAIA::BL bExist = GAIA::False;
			for(GAIA::SIZE y = 0; y < listTemp.size(); ++y)
			{
				if(listTemp[y] == &str)
				{
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
			{
				GTLINE2("Pool collect_valid_index_list specified instance pointer error!");
				++nRet;
				break;
			}
		}
		for(GAIA::SIZE x = 0; x < listTemp.size(); ++x)
		{
			GAIA::BL bExist = GAIA::False;
			for(GAIA::SIZE y = 0; y < listIndex.size(); ++y)
			{
				if(listTemp[y] == &pl[listIndex[y]])
				{
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
			{
				GTLINE2("Pool collect_valid_index_list specified instance not match the allocs!");
				++nRet;
				break;
			}
		}
		if(listTemp.unique_noorder() != 0)
		{
			GTLINE2("Pool alloc result exist same elements!");
			++nRet;
		}
		listTemp.clear();
		for(GAIA::SIZE x = 0; x < listIndex.size(); ++x)
			listTemp.push_back(&pl[listIndex[x]]);
		if(listTemp.unique_noorder() != 0)
		{
			GTLINE2("Pool collect_valid_index_list's result include the same elements!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < listTemp.size(); ++x)
		{
			if(!pl.release(listTemp[x]))
			{
				GTLINE2("Pool release failed!");
				++nRet;
				break;
			}
		}
		if(!pl.empty())
		{
			GTLINE2("Pool empty error caused by release!");
			++nRet;
		}
		if(pl.size() != 0)
		{
			GTLINE2("Pool size error caused by release!");
			++nRet;
		}
		if(pl.capacity() < SAMPLE_COUNT)
		{
			GTLINE2("Pool capacity error caused by release!");
			++nRet;
		}
		pl.destroy();
		if(pl.bind() == GNULL)
		{
			if(!pl.bind(&parentpl))
			{
				GTLINE2("Pool bind failed!");
				++nRet;
			}
			if(!parentpl.bind(&parentparentpl))
			{
				GTLINE2("Pool bind failed!");
				++nRet;
			}

			pl.destroy();
			parentpl.destroy();
			parentparentpl.destroy();
			listTemp.destroy();
			listIndex.destroy();

			goto BIND_POOL;
		}
		else
		{
			if(!parentpl.empty())
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
			if(parentpl.size() != 0)
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
			if(parentpl.capacity() < SAMPLE_COUNT)
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
			if(parentparentpl.empty())
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
			if(parentparentpl.size() == 0)
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
			if(parentparentpl.capacity() < SAMPLE_COUNT)
			{
				GTLINE2("Pool work on bind mode error!");
				++nRet;
			}
		}
		return nRet;
	}
};

#endif
