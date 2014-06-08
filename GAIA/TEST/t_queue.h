#ifndef		__T_QUEUE_H__
#define		__T_QUEUE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_queue(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::BasicQueue<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __QueueType;
		__QueueType q;
		q.reserve(100);
		if(q.capacity() != 100)
		{
			GTLINE2("Queue's capacity error!");
			++nRet;
		}
		if(q.size() != 0)
		{
			GTLINE2("New queue's size must been 0!");
			++nRet;
		}
		if(!q.empty())
		{
			GTLINE2("New queue must been empty!");
			++nRet;
		}
		__QueueType::it newit;
		__QueueType::const_it newcit;
		newit = q.front_it();
		if(!newit.empty())
		{
			GTLINE2("New queue front_it is not empty!");
			++nRet;
		}
		newit = q.back_it();
		if(!newit.empty())
		{
			GTLINE2("New queue back_it is not empty!");
			++nRet;
		}
		newcit = q.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New queue const_front_it is not empty!");
			++nRet;
		}
		newcit = q.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New queue const_back_it is not empty!");
			++nRet;
		}
		for(__QueueType::_sizetype x = 0; x < q.capacity(); ++x)
			q.push_back(x);
		if(q.size() != q.capacity())
		{
			GTLINE2("Full pushed queue's size must been capacity()!");
			++nRet;
		}
		for(__QueueType::_sizetype x = 0; x < q.size(); ++x)
		{
			if(q[x] != x)
			{
				GTLINE2("Queue's element value error!");
				++nRet;
				break;
			}
		}
		if(q.capacity() != 100)
		{
			GTLINE2("Queue's capacity must not changed!");
			++nRet;
		}
		__QueueType q1 = q;
		if(q1.capacity() != 100)
		{
			GTLINE2("Queue push_back multi element change the capacity error!");
			++nRet;
		}
		if(q1.size() != q1.capacity())
		{
			GTLINE2("Queue push_back multi element and the size error!");
			++nRet;
		}
		for(__QueueType::_sizetype x = 0; x < q1.size(); ++x)
		{
			if(q1[x] != x)
			{
				GTLINE2("Queue push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__QueueType::_sizetype x = 0; q.size() != 0; ++x)
		{
			if(q.front() != x)
			{
				GTLINE2("Queue back element is error!");
				++nRet;
				break;
			}
			q.pop_front();
		}
		if(!q.empty())
		{
			GTLINE2("Queue pop_front to empty failed!");
			++nRet;
		}
		q = q1;
		if(q.front() != q1.front())
		{
			GTLINE2("Queue's front element value not match!");
			++nRet;
		}
		q.resize(q.size() / 2);
		if(q.size() != q1.size() / 2)
		{
			GTLINE2("Queue resize operation failed!");
			++nRet;
		}
		for(__QueueType::_sizetype x = 0; x < q.size(); ++x)
		{
			if(q.count(x) != 1)
			{
				GTLINE2("Queue count operation failed!");
				++nRet;
				break;
			}
		}
		for(__QueueType::_sizetype x = 0; q.capacity() != q.size(); ++x)
			q.push_back(x);
		if(q.size() != q.capacity())
		{
			GTLINE2("Queue push_back element to capacity size failed!");
			++nRet;
		}
		q.resize(q1.size() / 2);
		for(__QueueType::_sizetype x = 0; q.capacity() != q.size(); ++x)
			q.push_back(x);
		if(q.size() != q.capacity())
		{
			GTLINE2("Queue push_back element to capacity size failed!");
			++nRet;
		}
		q1 = q;
		if(q > q1 || q < q1 || q != q1)
		{
			GTLINE2("Same queue compare > < != failed!");
			++nRet;
		}
		if(!(q >= q1 && q <= q1 && q == q1))
		{
			GTLINE2("Same queue compare !(>= <= ==) failed!");
			++nRet;
		}
		__QueueType::const_it cit = q.const_front_it();
		__QueueType::it it = q1.front_it();
		while(!it.empty())
		{
			*it = 10;
			++it;
		}
		it = q1.front_it();
		while(!cit.empty())
		{
			*it = *cit;
			++it;
			++cit;
		}
		if(q != q1)
		{
			GTLINE2("Queue iterator copy element failed!");
			++nRet;
		}
		__QueueType q2;
		q2 = q1;
		q2 += q1;
		q += q;
		if(q != q2)
		{
			GTLINE2("Queue operator += failed!");
			++nRet;
		}
		q = q1;
		cit = q.const_front_it();
		it = q.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("Queue const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("Queue iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - q.const_front_it() != 10)
		{
			GTLINE2("Queue const iterator += operator failed!");
			++nRet;
		}
		if(it - q.front_it() != 10)
		{
			GTLINE2("Queue iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("Queue const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("Queue iterator -= operator failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
