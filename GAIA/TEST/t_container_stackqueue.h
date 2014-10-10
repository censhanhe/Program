#ifndef		__T_CONTAINER_STACKQUEUE_H__
#define		__T_CONTAINER_STACKQUEUE_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_container_stackqueue(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CTN::BasicStackQueue<GAIA::N32, GAIA::N32, 100> __StackQueueType;
		__StackQueueType sq;
		if(sq.capacity() != 100)
		{
			GTLINE2("StackQueue's capacity error!");
			++nRet;
		}
		if(sq.size() != 0)
		{
			GTLINE2("New stackqueue's size must been 0!");
			++nRet;
		}
		if(!sq.empty())
		{
			GTLINE2("New stackqueue must been empty!");
			++nRet;
		}
		__StackQueueType::it newit;
		__StackQueueType::const_it newcit;
		newit = sq.front_it();
		if(!newit.empty())
		{
			GTLINE2("New stackqueue front_it is not empty!");
			++nRet;
		}
		newit = sq.back_it();
		if(!newit.empty())
		{
			GTLINE2("New stackqueue back_it is not empty!");
			++nRet;
		}
		newcit = sq.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New stackqueue const_front_it is not empty!");
			++nRet;
		}
		newcit = sq.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New stackqueue const_back_it is not empty!");
			++nRet;
		}
		for(__StackQueueType::_sizetype x = 0; x < sq.capacity(); ++x)
		{
			if(!sq.push_back(x))
			{
				GTLINE2("stackqueue push_back return GAIA::False failed!");
				++nRet;
				break;
			}
		}
		if(sq.size() != sq.capacity())
		{
			GTLINE2("Full pushed stackqueue's size must been capacity()!");
			++nRet;
		}
		for(__StackQueueType::_sizetype x = 0; x < sq.size(); ++x)
		{
			if(sq[x] != x)
			{
				GTLINE2("StackQueue's element value error!");
				++nRet;
				break;
			}
		}
		if(sq.capacity() != 100)
		{
			GTLINE2("StackQueue's capacity must not changed!");
			++nRet;
		}
		__StackQueueType sq1 = sq;
		if(sq1.capacity() != 100)
		{
			GTLINE2("StackQueue push_back multi element change the capacity error!");
			++nRet;
		}
		if(sq1.size() != sq1.capacity())
		{
			GTLINE2("StackQueue push_back multi element and the size error!");
			++nRet;
		}
		for(__StackQueueType::_sizetype x = 0; x < sq1.size(); ++x)
		{
			if(sq1[x] != x)
			{
				GTLINE2("StackQueue push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__StackQueueType::_sizetype x = 0; sq.size() != 0; ++x)
		{
			if(sq.front() != x)
			{
				GTLINE2("StackQueue back element is error!");
				++nRet;
				break;
			}
			sq.pop_front();
		}
		if(!sq.empty())
		{
			GTLINE2("StackQueue pop_front to empty failed!");
			++nRet;
		}
		sq = sq1;
		if(sq.front() != sq1.front())
		{
			GTLINE2("StackQueue's front element value not match!");
			++nRet;
		}
		if(!sq.resize(sq.size() / 2))
		{
			GTLINE2("StackQueue resize operation failed!");
			++nRet;
		}
		if(sq.size() != sq1.size() / 2)
		{
			GTLINE2("StackQueue resize operation failed!");
			++nRet;
		}
		for(__StackQueueType::_sizetype x = 0; x < sq.size(); ++x)
		{
			if(sq.count(x) != 1)
			{
				GTLINE2("StackQueue count operation failed!");
				++nRet;
				break;
			}
		}
		for(__StackQueueType::_sizetype x = 0; sq.capacity() != sq.size(); ++x)
			sq.push_back(x);
		if(sq.size() != sq.capacity())
		{
			GTLINE2("StackQueue push_back element to capacity size failed!");
			++nRet;
		}
		sq.resize(sq1.size() / 2);
		for(__StackQueueType::_sizetype x = 0; sq.capacity() != sq.size(); ++x)
			sq.push_back(x);
		if(sq.size() != sq.capacity())
		{
			GTLINE2("StackQueue push_back element to capacity size failed!");
			++nRet;
		}
		sq1 = sq;
		if(sq > sq1 || sq < sq1 || sq != sq1)
		{
			GTLINE2("Same stackqueue compare > < != failed!");
			++nRet;
		}
		if(!(sq >= sq1 && sq <= sq1 && sq == sq1))
		{
			GTLINE2("Same stackqueue compare !(>= <= ==) failed!");
			++nRet;
		}
		__StackQueueType::const_it cit = sq.const_front_it();
		__StackQueueType::it it = sq1.front_it();
		for(; !it.empty(); ++it)
			*it = 10;
		it = sq1.front_it();
		for(; !cit.empty(); ++cit, ++it)
			*it = *cit;
		if(sq != sq1)
		{
			GTLINE2("StackQueue iterator copy element failed!");
			++nRet;
		}
		__StackQueueType sq2;
		sq2 = sq1;
		sq2 += sq1;
		sq += sq;
		if(sq != sq2)
		{
			GTLINE2("StackQueue operator += failed!");
			++nRet;
		}
		sq = sq1;
		cit = sq.const_front_it();
		it = sq.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("StackQueue const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("StackQueue iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - sq.const_front_it() != 10)
		{
			GTLINE2("StackQueue const iterator += operator failed!");
			++nRet;
		}
		if(it - sq.front_it() != 10)
		{
			GTLINE2("StackQueue iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("StackQueue const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("StackQueue iterator -= operator failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
