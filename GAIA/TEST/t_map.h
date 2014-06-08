#ifndef		__T_MAP_H__
#define		__T_MAP_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_map(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_SIZE = 100;
		typedef GAIA::CONTAINER::BasicMap<GAIA::N32, GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MapType;
		__MapType m;
		if(!m.empty())
		{
			GTLINE2("New map is not empty!");
			++nRet;
		}
		if(m.size() != 0)
		{
			GTLINE2("New map size must zero!");
			++nRet;
		}
		if(m.capacity() != 0)
		{
			GTLINE2("New map capacity is not zero!");
			++nRet;
		}
		__MapType::it newit;
		__MapType::const_it newcit;
		newit = m.front_it();
		if(!newit.empty())
		{
			GTLINE2("New map front_it is not empty!");
			++nRet;
		}
		newit = m.back_it();
		if(!newit.empty())
		{
			GTLINE2("New map back_it is not empty!");
			++nRet;
		}
		newcit = m.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New map const_front_it is not empty!");
			++nRet;
		}
		newcit = m.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New map const_back_it is not empty!");
			++nRet;
		}
		m.clear();
		m.destroy();
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
			m.insert(x, x);
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(m.find(x) == GNULL)
			{
				GTLINE2("Map find element failed!");
				++nRet;
				break;
			}
			if(static_cast<const __MapType*>(&m)->find(x) == GNULL)
			{
				GTLINE2("Map const find element failed!");
				++nRet;
				break;
			}
			__MapType::it it_l = m.lower_bound(x);
			if(it_l.empty())
			{
				GTLINE2("Map lower_bound failed!");
				++nRet;
				break;
			}
			__MapType::const_it cit_l = static_cast<const __MapType*>(&m)->lower_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("Map const lower_bound failed!");
				++nRet;
				break;
			}
			__MapType::it it_u = m.upper_bound(x);
			if(it_l.empty())
			{
				GTLINE2("Map upper_bound failed!");
				++nRet;
				break;
			}
			__MapType::const_it cit_u = static_cast<const __MapType*>(&m)->upper_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("Map const upper_bound failed!");
				++nRet;
				break;
			}
		}
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!m.erase(x))
			{
				GTLINE2("Map erase element failed!");
				++nRet;
				break;
			}
		}
		m.destroy();
		if(!m.empty())
		{
			GTLINE2("Map destroy failed!");
			++nRet;
		}
		if(m.size() != 0)
		{
			GTLINE2("Map destroy failed!");
			++nRet;
		}
		if(m.capacity() != 0)
		{
			GTLINE2("Map destroy failed!");
			++nRet;
		}
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
			m.insert(x, x);
		__MapType::it itfront = m.front_it();
		__MapType::const_it citfront = m.const_front_it();
		__MapType::it itback = m.back_it();
		__MapType::const_it citback = m.const_back_it();
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(itfront.empty() ||
				citfront.empty() ||
				itback.empty() ||
				citback.empty())
			{
				GTLINE2("Map iterator exist error!");
				++nRet;
				break;
			}
			if(*itfront != x ||
				*citfront != x ||
				*itback != ELEMENT_SIZE - x - 1 ||
				*citback != ELEMENT_SIZE - x - 1)
			{
				GTLINE2("Map iterator exist error!");
				++nRet;
				break;
			}
			++itfront;
			++citfront;
			--itback;
			--citback;
		}
		if(!itfront.empty() ||
			!citfront.empty() ||
			!itback.empty() ||
			!citback.empty())
		{
			GTLINE2("Map iterator ++ -- exist error!");
			++nRet;
		}
		m.clear();
		if(!m.empty())
		{
			GTLINE2("Map clear failed!");
			++nRet;
		}
		if(m.size() != 0)
		{
			GTLINE2("Map clear failed!");
			++nRet;
		}
		if(m.capacity() == 0)
		{
			GTLINE2("Map clear failed!");
			++nRet;
		}
		itfront = m.front_it();
		citfront = m.const_front_it();
		itback = m.back_it();
		citback = m.const_back_it();
		if(!itfront.empty() ||
			!citfront.empty() ||
			!itback.empty() ||
			!citback.empty())
		{
			GTLINE2("Map iterator not empty when map is empty!");
			++nRet;
		}
		if(itfront != itback)
		{
			GTLINE2("Map iterator exist error!");
			++nRet;
		}
		if(citfront != citback)
		{
			GTLINE2("Map iterator exist error!");
			++nRet;
		}
		for(__MapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
			m.insert(x, x);
		__MapType m1 = m;
		if(!(m1 == m && m1 >= m && m1 <= m))
		{
			GTLINE2("Map operator == >= <= failed!");
			++nRet;
		}
		if(m1 != m || m1 > m || m1 < m)
		{
			GTLINE2("Map operator != > < failed!");
			++nRet;
		}
		itfront = m1.front_it();
		citfront = m1.const_front_it();
		itback = m1.back_it();
		citback = m1.const_back_it();
		if(itfront >= itback || itfront > itback || itfront == itback ||
			citfront >= citback || citfront > citback || citfront == citback)
		{
			GTLINE2("Map iterator operator >= > == failed!");
			++nRet;
		}
		if(!(itfront <= itback && itfront < itback && itfront != itback &&
			citfront <= citback && citfront < citback && citfront != citback))
		{
			GTLINE2("Map iterator operator <= < != failed!");
			++nRet;
		}
		if((itfront + 10) - 10 != m1.front_it() ||
			(citfront + 10) - 10 != m1.const_front_it())
		{
			GTLINE2("Map iterator operator + or - failed!");
			++nRet;
		}
		if(itfront + 10 - m1.front_it() != 10 ||
			citfront + 10 - m1.const_front_it() != 10)
		{
			GTLINE2("Map iterator operator + or - failed!");
			++nRet;
		}
		itfront += ELEMENT_SIZE - 1;
		itback -= ELEMENT_SIZE - 1;
		citfront += ELEMENT_SIZE - 1;
		citback -= ELEMENT_SIZE - 1;
		if(itfront != m1.back_it() ||
			itback != m1.front_it() ||
			citfront != m1.const_back_it() ||
			citback != m1.const_front_it())
		{
			GTLINE2("Map iterator += or -= error!");
			++nRet;
		}
		return nRet;
	}
};

#endif
