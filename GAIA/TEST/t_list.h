#ifndef		__T_LIST_H__
#define		__T_LIST_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_list(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_SIZE = 100;
		typedef GAIA::CONTAINER::BasicList<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __ListType;
		__ListType l;
		if(!l.empty())
		{
			GTLINE2("New list not empty!");
			++nRet;
		}
		if(l.size() != 0)
		{
			GTLINE2("New list size error!");
			++nRet;
		}
		l.destroy();
		if(!l.empty())
		{
			GTLINE2("List destroy failed!");
			++nRet;
		}
		if(l.size() != 0)
		{
			GTLINE2("List destroy failed!");
			++nRet;
		}
		l.clear();
		if(!l.empty())
		{
			GTLINE2("List clear failed!");
			++nRet;
		}
		if(l.size() != 0)
		{
			GTLINE2("List clear failed!");
			++nRet;
		}
		__ListType::it newit;
		__ListType::const_it newcit;
		newit = l.front_it();
		if(!newit.empty())
		{
			GTLINE2("New list front_it is not empty!");
			++nRet;
		}
		newit = l.back_it();
		if(!newit.empty())
		{
			GTLINE2("New list back_it is not empty!");
			++nRet;
		}
		newcit = l.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New list const_front_it is not empty!");
			++nRet;
		}
		newcit = l.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New list const_back_it is not empty!");
			++nRet;
		}
		__ListType::it it = l.front_it();
		for(GAIA::N32 x = 0; x < ELEMENT_SIZE; ++x)
			l.insert(it, x);
		if(l.empty())
		{
			GTLINE2("List insert failed!");
			++nRet;
		}
		if(l.size() != ELEMENT_SIZE)
		{
			GTLINE2("List insert failed!");
			++nRet;
		}
		GAIA::N32 nIndex = 0;
		__ListType::const_it cit = l.const_front_it();
		while(!cit.empty())
		{
			if(*cit != nIndex)
			{
				GTLINE2("List insert element value error!");
				++nRet;
				break;
			}
			++cit;
			++nIndex;
		}
		it = l.front_it();
		if(!l.erase(it))
		{
			GTLINE2("List erase first element failed!");
			++nRet;
		}
		it = l.back_it();
		if(!l.erase(it))
		{
			GTLINE2("List erase last element failed!");
			++nRet;
		}
		while(!l.empty())
		{
			it = l.front_it();
			if(!l.erase(it))
			{
				GTLINE2("List erase all by first element failed!");
				++nRet;
				break;
			}
		}
		if(!l.empty())
		{
			GTLINE2("List erase failed!");
			++nRet;
		}
		if(l.size() != 0)
		{
			GTLINE2("List erase failed!");
			++nRet;
		}
		l.destroy();
		it = l.back_it();
		for(GAIA::N32 x = 0; x < ELEMENT_SIZE; ++x)
			l.insert(it, x);
		it = l.front_it();
		while(!it.empty())
			l.erase(it);
		if(!l.empty())
		{
			GTLINE2("List erase failed!");
			++nRet;
		}
		if(l.size() != 0)
		{
			GTLINE2("List erase by iterator increase failed!");
			++nRet;
		}
		l.destroy();
		for(GAIA::N32 x = 0; x < ELEMENT_SIZE; ++x)
			l.push_back(x);
		if(l.empty())
		{
			GTLINE2("List push_back by iterator increase failed!");
			++nRet;
		}
		if(l.size() != ELEMENT_SIZE)
		{
			GTLINE2("List push_back failed!");
			++nRet;
		}
		cit = l.const_front_it();
		nIndex = 0;
		while(!cit.empty())
		{
			if(*cit != nIndex)
			{
				GTLINE2("List push_back element value error!");
				++nRet;
				break;
			}
			++cit;
			++nIndex;
		}
		while(!l.empty())
		{
			--nIndex;
			if(l.back() != nIndex)
			{
				GTLINE2("List pop_back failed!");
				++nRet;
				break;
			}
			l.pop_back();
		}
		l.destroy();
		for(GAIA::N32 x = 0; x < ELEMENT_SIZE; ++x)
			l.push_front(x);
		if(l.empty())
		{
			GTLINE2("List push_front failed!");
			++nRet;
		}
		if(l.size() != ELEMENT_SIZE)
		{
			GTLINE2("List push_front failed!");
			++nRet;
		}
		cit = l.const_back_it();
		nIndex = 0;
		while(!cit.empty())
		{
			if(*cit != nIndex)
			{
				GTLINE2("List push_front element value error!");
				++nRet;
				break;
			}
			--cit;
			++nIndex;
		}
		while(!l.empty())
		{
			--nIndex;
			if(l.front() != nIndex)
			{
				GTLINE2("List pop_front failed!");
				++nRet;
				break;
			}
			l.pop_front();
		}
		l.clear();
		for(GAIA::N32 x = 0; x < ELEMENT_SIZE; ++x)
			l.push_front(x);
		__ListType l1;
		l1 = l;
		if(l > l1 || l < l1 || l != l1)
		{
			GTLINE2("Same list compare > < != failed!");
			++nRet;
		}
		if(!(l >= l1 && l <= l1 && l == l1))
		{
			GTLINE2("Same list compare !(>= <= ==) failed!");
			++nRet;
		}
		l += l;
		if(l.size() != ELEMENT_SIZE * 2)
		{
			GTLINE2("List operator += self failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif