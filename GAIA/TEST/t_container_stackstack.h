#ifndef		__T_CONTAINER_STACKSTACK_H__
#define		__T_CONTAINER_STACKSTACK_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_stackstack(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::BasicStackStack<GAIA::N32, GAIA::N32, 100> __StackStackType;
		__StackStackType ss;
		if(ss.capacity() != 100)
		{
			GTLINE2("StackStack's capacity error!");
			++nRet;
		}
		if(ss.size() != 0)
		{
			GTLINE2("New stackstack's size must been 0!");
			++nRet;
		}
		if(!ss.empty())
		{
			GTLINE2("New stackstack must been empty!");
			++nRet;
		}
		__StackStackType::it newit;
		__StackStackType::const_it newcit;
		newit = ss.front_it();
		if(!newit.empty())
		{
			GTLINE2("New stackstack front_it is not empty!");
			++nRet;
		}
		newit = ss.back_it();
		if(!newit.empty())
		{
			GTLINE2("New stackstack back_it is not empty!");
			++nRet;
		}
		newcit = ss.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New stackstack const_front_it is not empty!");
			++nRet;
		}
		newcit = ss.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New stackstack const_back_it is not empty!");
			++nRet;
		}
		for(__StackStackType::_sizetype x = 0; x < ss.capacity(); ++x)
		{
			if(!ss.push_back(x))
			{
				GTLINE2("stackstack push_back return GAIA::False failed!");
				++nRet;
				break;
			}
		}
		if(ss.size() != ss.capacity())
		{
			GTLINE2("Full pushed stackstack's size must been capacity()!");
			++nRet;
		}
		for(__StackStackType::_sizetype x = 0; x < ss.size(); ++x)
		{
			if(ss[x] != x)
			{
				GTLINE2("StackStack's element value error!");
				++nRet;
				break;
			}
		}
		if(ss.capacity() != 100)
		{
			GTLINE2("StackStack's capacity must not changed!");
			++nRet;
		}
		__StackStackType ss1 = ss;
		if(ss1.capacity() != 100)
		{
			GTLINE2("StackStack push_back multi element change the capacity error!");
			++nRet;
		}
		if(ss1.size() != ss1.capacity())
		{
			GTLINE2("StackStack push_back multi element and the size error!");
			++nRet;
		}
		for(__StackStackType::_sizetype x = 0; x < ss1.size(); ++x)
		{
			if(ss1[x] != x)
			{
				GTLINE2("StackStack push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__StackStackType::_sizetype size = ss.size(); size > 0; --size)
		{
			if(ss.back() != size - 1)
			{
				GTLINE2("StackStack back element is error!");
				++nRet;
				break;
			}
			ss.pop_back();
		}
		if(!ss.empty())
		{
			GTLINE2("StackStack pop_back to empty failed!");
			++nRet;
		}
		ss = ss1;
		if(ss.front() != ss1.front())
		{
			GTLINE2("StackStack's front element value not match!");
			++nRet;
		}
		if(!ss.resize(ss.size() / 2))
		{
			GTLINE2("StackStack resize operation failed!");
			++nRet;
		}
		if(ss.size() != ss1.size() / 2)
		{
			GTLINE2("StackStack resize operation failed!");
			++nRet;
		}
		for(__StackStackType::_sizetype x = 0; x < ss.size(); ++x)
		{
			if(ss.count(x) != 1)
			{
				GTLINE2("StackStack count operation failed!");
				++nRet;
				break;
			}
		}
		for(__StackStackType::_sizetype x = 0; ss.capacity() != ss.size(); ++x)
			ss.push_back(x);
		if(ss.size() != ss.capacity())
		{
			GTLINE2("StackStack push_back element to capacity size failed!");
			++nRet;
		}
		ss.resize(ss1.size() / 2);
		for(__StackStackType::_sizetype x = 0; ss.capacity() != ss.size(); ++x)
			ss.push_back(x);
		if(ss.size() != ss.capacity())
		{
			GTLINE2("StackStack push_back element to capacity size failed!");
			++nRet;
		}
		ss1 = ss;
		if(ss > ss1 || ss < ss1 || ss != ss1)
		{
			GTLINE2("Same stackstack compare > < != failed!");
			++nRet;
		}
		if(!(ss >= ss1 && ss <= ss1 && ss == ss1))
		{
			GTLINE2("Same stackstack compare !(>= <= ==) failed!");
			++nRet;
		}
		__StackStackType::const_it cit = ss.const_front_it();
		__StackStackType::it it = ss1.front_it();
		while(!it.empty())
		{
			*it = 10;
			++it;
		}
		it = ss1.front_it();
		while(!cit.empty())
		{
			*it = *cit;
			++it;
			++cit;
		}
		if(ss != ss1)
		{
			GTLINE2("StackStack iterator copy element failed!");
			++nRet;
		}
		__StackStackType ss2;
		ss2 = ss1;
		ss2 += ss1;
		ss += ss;
		if(ss != ss2)
		{
			GTLINE2("StackStack operator += failed!");
			++nRet;
		}
		ss = ss1;
		cit = ss.const_front_it();
		it = ss.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("StackStack const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("StackStack iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - ss.const_front_it() != 10)
		{
			GTLINE2("StackStack const iterator += operator failed!");
			++nRet;
		}
		if(it - ss.front_it() != 10)
		{
			GTLINE2("StackStack iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("StackStack const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("StackStack iterator -= operator failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
