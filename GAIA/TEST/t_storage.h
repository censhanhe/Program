#ifndef		__T_STORAGE_H__
#define		__T_STORAGE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_storage(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::Storage<GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>, 32> __StorageType;
		__StorageType st;
		if(st.capacity() != 0)
		{
			GTLINE2("New storage capacity not zero!");
			++nRet;
		}
		if(st.size() != 0)
		{
			GTLINE2("New storage size not zero!");
			++nRet;
		}
		if(!st.empty())
		{
			GTLINE2("New storage must empty!");
			++nRet;
		}
		st.clear();
		st.destroy();
		if(st.capacity() != 0)
		{
			GTLINE2("New storage capacity not zero!");
			++nRet;
		}
		if(st.size() != 0)
		{
			GTLINE2("New storage size not zero!");
			++nRet;
		}
		if(!st.empty())
		{
			GTLINE2("New storage must empty!");
			++nRet;
		}
		st.increase_reserve(10000, 1024 * 1024 * __StorageType::_pagesize);
		if(!st.empty())
		{
			GTLINE2("Storage increase_reserve failed!");
			++nRet;
		}
		if(st.capacity() == 0)
		{
			GTLINE2("Storage increase_reserve failed!");
			++nRet;
		}
		if(st.size() != 0)
		{
			GTLINE2("Storage increase_reserve failed!");
			++nRet;
		}
		__StorageType::Node n;
		if(!st.insert(40, n))
		{
			GTLINE2("Storage insert failed!");
			++nRet;
		}
		if(st.capacity() != 1024 * 1024 * __StorageType::_pagesize)
		{
			GTLINE2("Storage insert cause capacity error!");
			++nRet;
		}
		if(st.size() != 64)
		{
			GTLINE2("Storage insert cause size error!");
			++nRet;
		}
		if(!st.erase(n.head()))
		{
			GTLINE2("Storage erase failed!");
			++nRet;
		}
		if(st.capacity() != 1024 * 1024 * __StorageType::_pagesize)
		{
			GTLINE2("Storage erase cause capacity error!");
			++nRet;
		}
		if(st.size() != 0)
		{
			GTLINE2("Storage erase cause size error!");
			++nRet;
		}
		st.destroy();
		if(!st.empty())
		{
			GTLINE2("Storage destroy cause empty failed!");
			++nRet;
		}
		if(st.capacity() != 0)
		{
			GTLINE2("Storage destroy cause capacity failed!");
			++nRet;
		}
		if(st.size() != 0)
		{
			GTLINE2("Storage destroy cause size failed!");
			++nRet;
		}
		st.increase_reserve(10000, 1024 * 1024 * __StorageType::_pagesize);
		typedef GAIA::CONTAINER::Vector<GAIA::NM> __VectorType;
		__VectorType vt;
		static const GAIA::N32 SAMPLE_COUNT = 100;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::N32 nSize = GAIA::MATH::xrandom() % 256 + 1;
			if(!st.insert(nSize, n))
			{
				GTLINE2("Storage insert failed!");
				++nRet;
				break;
			}
			vt.push_back(n.head());
		}
		__StorageType st1 = st;
		for(__VectorType::_sizetype x = 0; x < vt.size(); x += 2)
		{
			if(st.find(vt[x]) == GNULL)
			{
				GTLINE2("Storage find failed!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype x = 0; x < vt.size(); x += 2)
		{
			if(!st.erase(vt[x]))
			{
				GTLINE2("Storage erase failed!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype x = 1; x < vt.size(); x += 2)
		{
			if(!st.erase(vt[x]))
			{
				GTLINE2("Storage erase failed!");
				break;
			}
		}
		for(__VectorType::_sizetype x = 0; x < vt.size(); x += 2)
		{
			if(st1.find(vt[x]) == GNULL)
			{
				GTLINE2("Storage find failed!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype x = 0; x < vt.size(); x += 2)
		{
			if(!st1.erase(vt[x]))
			{
				GTLINE2("Storage erase failed!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype x = 1; x < vt.size(); x += 2)
		{
			if(!st1.erase(vt[x]))
			{
				GTLINE2("Storage erase failed!");
				break;
			}
		}
		return nRet;
	}
};

#endif