#ifndef		__T_STACK_H__
#define		__T_STACK_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_stack(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __StackType;
		__StackType ss;
		ss.reserve(100);
		if(ss.capacity() != 100)
		{
			GTLINE2("Stack's capacity error!");
			++nRet;
		}
		if(ss.size() != 0)
		{
			GTLINE2("New stack's size must been 0!");
			++nRet;
		}
		if(!ss.empty())
		{
			GTLINE2("New stack must been empty!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < ss.capacity(); ++x)
			ss.push_back(x);
		if(ss.size() != ss.capacity())
		{
			GTLINE2("Full pushed stack's size must been capacity()!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < ss.size(); ++x)
		{
			if(ss[x] != x)
			{
				GTLINE2("Stack's element value error!");
				++nRet;
				break;
			}
		}
		if(ss.capacity() != 100)
		{
			GTLINE2("Stack's capacity must not changed!");
			++nRet;
		}
		__StackType ss1 = ss;
		if(ss1.capacity() != 100)
		{
			GTLINE2("Stack push_back multi element change the capacity error!");
			++nRet;
		}
		if(ss1.size() != ss1.capacity())
		{
			GTLINE2("Stack push_back multi element and the size error!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < ss1.size(); ++x)
		{
			if(ss1[x] != x)
			{
				GTLINE2("Stack push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__StackType::_sizetype size = ss.size(); size > 0; --size)
		{
			if(ss.back() != size - 1)
			{
				GTLINE2("Stack back element is error!");
				++nRet;
				break;
			}
			ss.pop_back();
		}
		if(!ss.empty())
		{
			GTLINE2("Stack pop_back to empty failed!");
			++nRet;
		}
		ss = ss1;
		if(ss.front() != ss1.front())
		{
			GTLINE2("Stack's front element value not match!");
			++nRet;
		}
		ss.resize(ss.size() / 2);
		if(ss.size() != ss1.size() / 2)
		{
			GTLINE2("Stack resize operation failed!");
			++nRet;
		}
		for(__StackType::_sizetype x = 0; x < ss.size(); ++x)
		{
			if(ss.count(x) != 1)
			{
				GTLINE2("Stack count operation failed!");
				++nRet;
				break;
			}
		}
		for(__StackType::_sizetype x = 0; ss.capacity() != ss.size(); ++x)
			ss.push_back(x);
		if(ss.size() != ss.capacity())
		{
			GTLINE2("Stack push_back element to capacity size failed!");
			++nRet;
		}
		ss.resize(ss1.size() / 2);
		for(__StackType::_sizetype x = 0; ss.capacity() != ss.size(); ++x)
			ss.push_back(x);
		if(ss.size() != ss.capacity())
		{
			GTLINE2("Stack push_back element to capacity size failed!");
			++nRet;
		}
		ss1 = ss;
		if(ss > ss1 || ss < ss1 || ss != ss1)
		{
			GTLINE2("Same stack compare > < != failed!");
			++nRet;
		}
		if(!(ss >= ss1 && ss <= ss1 && ss == ss1))
		{
			GTLINE2("Same stack compare !(>= <= ==) failed!");
			++nRet;
		}
		__StackType::const_it cit = ss.const_front_it();
		__StackType::it it = ss1.front_it();
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
			GTLINE2("Stack iterator copy element failed!");
			++nRet;
		}
		__StackType ss2;
		ss2 = ss1;
		ss2 += ss1;
		ss += ss1;
		if(ss != ss2)
		{
			GTLINE2("Stack operator += failed!");
			++nRet;
		}
		ss = ss1;
		cit = ss.const_front_it();
		it = ss.front_it();
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
		if(cit - ss.const_front_it() != 10)
		{
			GTLINE2("Stack const iterator += operator failed!");
			++nRet;
		}
		if(it - ss.front_it() != 10)
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