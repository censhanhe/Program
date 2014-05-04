#ifndef		__T_STACK_H__
#define		__T_STACK_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_stack(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __StackType;
		__StackType s;
		s.reserve(100);
		if(s.capacity() != 100)
		{
			GTLINE2("Stack's capacity error!");
			++nRet;
		}
		if(s.size() != 0)
		{
			GTLINE2("New stack's size must been 0!");
			++nRet;
		}
		if(!s.empty())
		{
			GTLINE2("New stack must been empty!");
			++nRet;
		}
		__StackType::it newit;
		__StackType::const_it newcit;
		newit = s.front_it();
		if(!newit.empty())
		{
			GTLINE2("New stack front_it is not empty!");
			++nRet;
		}
		newit = s.back_it();
		if(!newit.empty())
		{
			GTLINE2("New stack back_it is not empty!");
			++nRet;
		}
		newcit = s.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New stack const_front_it is not empty!");
			++nRet;
		}
		newcit = s.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New stack const_back_it is not empty!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < s.capacity(); ++x)
			s.push_back(x);
		if(s.size() != s.capacity())
		{
			GTLINE2("Full pushed stack's size must been capacity()!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < s.size(); ++x)
		{
			if(s[x] != x)
			{
				GTLINE2("Stack's element value error!");
				++nRet;
				break;
			}
		}
		if(s.capacity() != 100)
		{
			GTLINE2("Stack's capacity must not changed!");
			++nRet;
		}
		__StackType s1 = s;
		if(s1.capacity() != 100)
		{
			GTLINE2("Stack push_back multi element change the capacity error!");
			++nRet;
		}
		if(s1.size() != s1.capacity())
		{
			GTLINE2("Stack push_back multi element and the size error!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < s1.size(); ++x)
		{
			if(s1[x] != x)
			{
				GTLINE2("Stack push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__StackType::_sizetype size = s.size(); size > 0; --size)
		{
			if(s.back() != size - 1)
			{
				GTLINE2("Stack back element is error!");
				++nRet;
				break;
			}
			s.pop_back();
		}
		if(!s.empty())
		{
			GTLINE2("Stack pop_back to empty failed!");
			++nRet;
		}
		s = s1;
		if(s.front() != s1.front())
		{
			GTLINE2("Stack's front element value not match!");
			++nRet;
		}
		s.resize(s.size() / 2);
		if(s.size() != s1.size() / 2)
		{
			GTLINE2("Stack resize operation failed!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < s.size(); ++x)
		{
			if(s.count(x) != 1)
			{
				GTLINE2("Stack count operation failed!");
				++nRet;
				break;
			}
		}
		for(__StackType::_sizetype x = 0; s.capacity() != s.size(); ++x)
			s.push_back(x);
		if(s.size() != s.capacity())
		{
			GTLINE2("Stack push_back element to capacity size failed!");
			++nRet;
		}
		s.resize(s1.size() / 2);
		for(__StackType::_sizetype x = 0; s.capacity() != s.size(); ++x)
			s.push_back(x);
		if(s.size() != s.capacity())
		{
			GTLINE2("Stack push_back element to capacity size failed!");
			++nRet;
		}
		s1 = s;
		if(s > s1 || s < s1 || s != s1)
		{
			GTLINE2("Same stack compare > < != failed!");
			++nRet;
		}
		if(!(s >= s1 && s <= s1 && s == s1))
		{
			GTLINE2("Same stack compare !(>= <= ==) failed!");
			++nRet;
		}
		__StackType::const_it cit = s.const_front_it();
		__StackType::it it = s1.front_it();
		while(!it.empty())
		{
			*it = 10;
			++it;
		}
		it = s1.front_it();
		while(!cit.empty())
		{
			*it = *cit;
			++it;
			++cit;
		}
		if(s != s1)
		{
			GTLINE2("Stack iterator copy element failed!");
			++nRet;
		}
		__StackType s2;
		s2 = s1;
		s2 += s1;
		s += s;
		if(s != s2)
		{
			GTLINE2("Stack operator += failed!");
			++nRet;
		}
		s = s1;
		cit = s.const_front_it();
		it = s.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("Stack const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("Stack iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - s.const_front_it() != 10)
		{
			GTLINE2("Stack const iterator += operator failed!");
			++nRet;
		}
		if(it - s.front_it() != 10)
		{
			GTLINE2("Stack iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("Stack const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("Stack iterator -= operator failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif