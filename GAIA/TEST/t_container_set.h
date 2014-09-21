#ifndef		__T_CONTAINER_SET_H__
#define		__T_CONTAINER_SET_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_set(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_SIZE = 100;
		typedef GAIA::CTN::BasicSet<GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32> > __SetType;
		__SetType s;
		if(!s.empty())
		{
			GTLINE2("New set is not empty!");
			++nRet;
		}
		if(s.size() != 0)
		{
			GTLINE2("New set size must zero!");
			++nRet;
		}
		if(s.capacity() != 0)
		{
			GTLINE2("New set capacity is not zero!");
			++nRet;
		}
		__SetType::it newit;
		__SetType::const_it newcit;
		newit = s.front_it();
		if(!newit.empty())
		{
			GTLINE2("New set front_it is not empty!");
			++nRet;
		}
		newit = s.back_it();
		if(!newit.empty())
		{
			GTLINE2("New set back_it is not empty!");
			++nRet;
		}
		newcit = s.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New set const_front_it is not empty!");
			++nRet;
		}
		newcit = s.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New set const_back_it is not empty!");
			++nRet;
		}
		s.clear();
		s.destroy();
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!s.insert(x))
			{
				GTLINE2("Set insert element failed!");
				++nRet;
				break;
			}
		}
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(s.find(x) == GNIL)
			{
				GTLINE2("Set find element failed!");
				++nRet;
				break;
			}
			if(static_cast<const __SetType*>(&s)->find(x) == GNIL)
			{
				GTLINE2("Set const find element failed!");
				++nRet;
				break;
			}
			__SetType::it it_l = s.lower_bound(x);
			if(it_l.empty())
			{
				GTLINE2("Set lower_bound failed!");
				++nRet;
				break;
			}
			__SetType::const_it cit_l = static_cast<const __SetType*>(&s)->lower_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("Set const lower_bound failed!");
				++nRet;
				break;
			}
			__SetType::it it_u = s.upper_bound(x);
			if(it_l.empty())
			{
				GTLINE2("Set upper_bound failed!");
				++nRet;
				break;
			}
			__SetType::const_it cit_u = static_cast<const __SetType*>(&s)->upper_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("Set const upper_bound failed!");
				++nRet;
				break;
			}
		}
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!s.erase(x))
			{
				GTLINE2("Set erase element failed!");
				++nRet;
				break;
			}
		}
		s.destroy();
		if(!s.empty())
		{
			GTLINE2("Set destroy failed!");
			++nRet;
		}
		if(s.size() != 0)
		{
			GTLINE2("Set destroy failed!");
			++nRet;
		}
		if(s.capacity() != 0)
		{
			GTLINE2("Set destroy failed!");
			++nRet;
		}
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!s.insert(x))
			{
				GTLINE2("Set insert element failed!");
				++nRet;
				break;
			}
		}
		__SetType::it itfront = s.front_it();
		__SetType::const_it citfront = s.const_front_it();
		__SetType::it itback = s.back_it();
		__SetType::const_it citback = s.const_back_it();
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(itfront.empty() ||
				citfront.empty() ||
				itback.empty() ||
				citback.empty())
			{
				GTLINE2("Set iterator exist error!");
				++nRet;
				break;
			}
			if(*itfront != x ||
				*citfront != x ||
				*itback != ELEMENT_SIZE - x - 1 ||
				*citback != ELEMENT_SIZE - x - 1)
			{
				GTLINE2("Set iterator exist error!");
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
			GTLINE2("Set iterator ++ -- exist error!");
			++nRet;
		}
		s.clear();
		if(!s.empty())
		{
			GTLINE2("Set clear failed!");
			++nRet;
		}
		if(s.size() != 0)
		{
			GTLINE2("Set clear failed!");
			++nRet;
		}
		if(s.capacity() == 0)
		{
			GTLINE2("Set clear failed!");
			++nRet;
		}
		itfront = s.front_it();
		citfront = s.const_front_it();
		itback = s.back_it();
		citback = s.const_back_it();
		if(!itfront.empty() ||
			!citfront.empty() ||
			!itback.empty() ||
			!citback.empty())
		{
			GTLINE2("Set iterator not empty when set is empty!");
			++nRet;
		}
		if(itfront != itback)
		{
			GTLINE2("Set iterator exist error!");
			++nRet;
		}
		if(citfront != citback)
		{
			GTLINE2("Set iterator exist error!");
			++nRet;
		}
		for(__SetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!s.insert(x))
			{
				GTLINE2("Set insert element failed!");
				++nRet;
				break;
			}
		}
		__SetType s1 = s;
		if(!(s1 == s && s1 >= s && s1 <= s))
		{
			GTLINE2("Set operator == >= <= failed!");
			++nRet;
		}
		if(s1 != s || s1 > s || s1 < s)
		{
			GTLINE2("Set operator != > < failed!");
			++nRet;
		}
		itfront = s1.front_it();
		citfront = s1.const_front_it();
		itback = s1.back_it();
		citback = s1.const_back_it();
		if(itfront >= itback || itfront > itback || itfront == itback ||
			citfront >= citback || citfront > citback || citfront == citback)
		{
			GTLINE2("Set iterator operator >= > == failed!");
			++nRet;
		}
		if(!(itfront <= itback && itfront < itback && itfront != itback &&
			citfront <= citback && citfront < citback && citfront != citback))
		{
			GTLINE2("Set iterator operator <= < != failed!");
			++nRet;
		}
		if((itfront + 10) - 10 != s1.front_it() ||
			(citfront + 10) - 10 != s1.const_front_it())
		{
			GTLINE2("Set iterator operator + or - failed!");
			++nRet;
		}
		if(itfront + 10 - s1.front_it() != 10 ||
			citfront + 10 - s1.const_front_it() != 10)
		{
			GTLINE2("Set iterator operator + or - failed!");
			++nRet;
		}
		itfront += ELEMENT_SIZE - 1;
		itback -= ELEMENT_SIZE - 1;
		citfront += ELEMENT_SIZE - 1;
		citback -= ELEMENT_SIZE - 1;
		if(itfront != s1.back_it() ||
			itback != s1.front_it() ||
			citfront != s1.const_back_it() ||
			citback != s1.const_front_it())
		{
			GTLINE2("Set iterator += or -= error!");
			++nRet;
		}
		return nRet;
	}
};

#endif
