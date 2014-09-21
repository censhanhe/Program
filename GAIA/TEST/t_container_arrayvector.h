#ifndef		__T_CONTAINER_ARRAYVECTOR_H__
#define		__T_CONTAINER_ARRAYVECTOR_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_arrayvector(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CTN::BasicArrayVector<GAIA::N32, GAIA::N32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32>, 3> __ArrayVectorType;
		__ArrayVectorType av;
		av.reserve(100);
		if(av.capacity() != 100)
		{
			GTLINE2("ArrayVector's capacity error!");
			++nRet;
		}
		if(av.size() != 0)
		{
			GTLINE2("New arrayvector's size must been 0!");
			++nRet;
		}
		if(!av.empty())
		{
			GTLINE2("New arrayvector must been empty!");
			++nRet;
		}
		__ArrayVectorType::it newit;
		__ArrayVectorType::const_it newcit;
		newit = av.front_it();
		if(!newit.empty())
		{
			GTLINE2("New arrayvector front_it is not empty!");
			++nRet;
		}
		newit = av.back_it();
		if(!newit.empty())
		{
			GTLINE2("New arrayvector back_it is not empty!");
			++nRet;
		}
		newcit = av.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New arrayvector const_front_it is not empty!");
			++nRet;
		}
		newcit = av.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New arrayvector const_back_it is not empty!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.capacity(); ++x)
			av.push_back(x);
		if(av.size() != av.capacity())
		{
			GTLINE2("Full push_backed arrayvector's size must been capacity()!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.size(); ++x)
		{
			if(av[x] != x)
			{
				GTLINE2("ArrayVector's element value error!");
				++nRet;
				break;
			}
		}
		if(av.capacity() != 100)
		{
			GTLINE2("ArrayVector's capacity must not changed!");
			++nRet;
		}
		av.clear();
		for(__ArrayVectorType::_sizetype x = 0; x < av.capacity(); ++x)
		{
			if(!av.insert(x, x))
			{
				GTLINE2("ArrayVector insert element failed!");
				++nRet;
				break;
			}
		}
		if(av.size() != av.capacity())
		{
			GTLINE2("Full push_backed arrayvector's size must been capacity()!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.size(); ++x)
		{
			if(av[x] != x)
			{
				GTLINE2("ArrayVector's element value error!");
				++nRet;
				break;
			}
		}
		if(av.capacity() != 100)
		{
			GTLINE2("ArrayVector's capacity must not changed!");
			++nRet;
		}
		__ArrayVectorType av1;
		av1.push_back(av.front_ptr(), av.size());
		if(av1.capacity() != 100)
		{
			GTLINE2("ArrayVector push_back multi element change the capacity error!");
			++nRet;
		}
		if(av1.size() != av1.capacity())
		{
			GTLINE2("ArrayVector push_back multi element and the size error!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av1.size(); ++x)
		{
			if(av1[x] != x)
			{
				GTLINE2("ArrayVector push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__ArrayVectorType::_sizetype size = av.size(); size > 0; --size)
		{
			if(av.back() != size - 1)
			{
				GTLINE2("ArrayVector back element is error!");
				++nRet;
				break;
			}
			if(!av.pop_back())
			{
				GTLINE2("ArrayVector pop_back failed!");
				++nRet;
				break;
			}
		}

		__ArrayVectorType::_sizetype arrsize = av1.size();
		__ArrayVectorType::_datatype* pTemp = new __ArrayVectorType::_datatype[arrsize];
		if(!av1.pop_back(pTemp, arrsize))
		{
			GTLINE2("ArrayVector pop_back multi element failed!");
			++nRet;
		}
		av1.push_back(pTemp, arrsize);
		av.push_back(pTemp, arrsize);

		delete[] pTemp;
		pTemp = GNIL;
		if(av1.size() != arrsize ||
			av.size() != arrsize)
		{
			GTLINE2("ArrayVector push_back multi element size error!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.size(); ++x)
		{
			if(av[x] != av1[x])
			{
				GTLINE2("Two arrayvector push_back multi element and element value error!");
				++nRet;
			}
		}
		if(av.front() != av1.front())
		{
			GTLINE2("ArrayVector's front element value not match!");
			++nRet;
		}
		av.resize(av.size() / 2);
		if(av.size() != av1.size() / 2)
		{
			GTLINE2("ArrayVector resize operation failed!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.size(); ++x)
		{
			if(av.count(x) != 1)
			{
				GTLINE2("ArrayVector count operation failed!");
				++nRet;
				break;
			}
		}
		av.reset(0);
		if(av.size() != av1.size() / 2)
		{
			GTLINE2("ArrayVector reset change the size error!");
			++nRet;
		}
		for(__ArrayVectorType::_sizetype x = 0; x < av.size(); ++x)
		{
			if(av[x] != 0)
			{
				GTLINE2("ArrayVector reset change element value failed!");
				++nRet;
				break;
			}
		}
		for(__ArrayVectorType::_sizetype x = 0; av.capacity() != av.size(); ++x)
			av.push_back(x);
		if(av.size() != av.capacity())
		{
			GTLINE2("ArrayVector push_back element to capacity size failed!");
			++nRet;
		}
		av.sort();
		if(!GAIA::ALGO::issorted(av.front_ptr(), av.back_ptr()))
		{
			GTLINE2("ArrayVector sort failed!");
			++nRet;
		}
		if(av.unique() != av1.size() / 2)
		{
			GTLINE2("ArrayVector unique operation failed!");
			++nRet;
		}
		av.resize(av1.size() / 2);
		for(__ArrayVectorType::_sizetype x = 0; av.capacity() != av.size(); ++x)
			av.push_back(x);
		if(av.size() != av.capacity())
		{
			GTLINE2("ArrayVector push_back element to capacity size failed!");
			++nRet;
		}
		if(av.unique_noorder() != av1.size() / 2)
		{
			GTLINE2("ArrayVector unique_noorder operation failed!");
			++nRet;
		}
		av.sort();
		if(!GAIA::ALGO::issorted(av.front_ptr(), av.back_ptr()))
		{
			GTLINE2("ArrayVector sort failed!");
			++nRet;
		}
		__ArrayVectorType::const_it cit = av.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			if(av.search(*cit) == GINVALID)
			{
				GTLINE2("ArrayVector search failed!");
				++nRet;
				break;
			}
			if(av.find(*cit, 0) == GINVALID)
			{
				GTLINE2("ArrayVector find failed!");
				++nRet;
				break;
			}
			if(av.rfind(*cit, av.size() - 1) == GINVALID)
			{
				GTLINE2("ArrayVector rfind failed!");
				++nRet;
				break;
			}
		}
		av.inverse();
		__ArrayVectorType::it it = av.front_it();
		for(; !it.empty(); ++it)
		{
			__ArrayVectorType::it itt = it;
			++itt;
			if(!itt.empty())
			{
				if(*it <= *itt)
				{
					GTLINE2("ArrayVector inverse failed!");
					++nRet;
					break;
				}
			}
		}
		av1 = av;
		if(!av.insert(997, 0))
		{
			GTLINE2("ArrayVector insert failed!");
			++nRet;
		}
		__ArrayVectorType::_sizetype insertindex1 = av.size() / 2;
		if(!av.insert(998, insertindex1))
		{
			GTLINE2("ArrayVector insert failed!");
			++nRet;
		}
		__ArrayVectorType::_sizetype insertindex2 = av.size();
		if(!av.insert(999, insertindex2))
		{
			GTLINE2("ArrayVector insert failed!");
			++nRet;
		}
		if(av[0] != 997)
		{
			GTLINE2("ArrayVector insert value check failed!");
			++nRet;
		}
		if(av[insertindex1] != 998)
		{
			GTLINE2("ArrayVector insert value check failed!");
			++nRet;
		}
		if(av[insertindex2] != 999)
		{
			GTLINE2("ArrayVector insert value check failed!");
			++nRet;
		}
		if(!av.erase(insertindex2))
		{
			GTLINE2("ArrayVector erase tail element failed!");
			++nRet;
		}
		if(!av.erase(insertindex1))
		{
			GTLINE2("ArrayVector erase middle element failed!");
			++nRet;
		}
		if(!av.erase(0))
		{
			GTLINE2("ArrayVector erase first element failed!");
			++nRet;
		}
		if(av > av1 || av < av1 || av != av1)
		{
			GTLINE2("Same arrayvector compare > < != failed!");
			++nRet;
		}
		if(!(av >= av1 && av <= av1 && av == av1))
		{
			GTLINE2("Same arrayvector compare !(>= <= ==) failed!");
			++nRet;
		}
		it = av.front_it();
		for(; !it.empty(); ++it)
		{
			__ArrayVectorType::it itfinded = av.lower_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("ArrayVector lower_bound failed!");
				++nRet;
				break;
			}
			itfinded = av.upper_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("ArrayVector upper_bound failed!");
				++nRet;
				break;
			}
		}
		const __ArrayVectorType& arrc = av;
		cit = arrc.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			__ArrayVectorType::const_it citfinded = arrc.lower_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("ArrayVector lower_bound const failed!");
				++nRet;
				break;
			}
			citfinded = arrc.upper_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("ArrayVector upper_bound const failed!");
				++nRet;
				break;
			}
		}
		av.inverse();
		cit = av.const_front_it();
		it = av1.front_it();
		for(; !cit.empty(); ++cit, ++it)
			*it = *cit;
		if(av != av1)
		{
			GTLINE2("ArrayVector iterator copy element failed!");
			++nRet;
		}
		__ArrayVectorType av2;
		av2 = av1;
		av2 += av1;
		av += av1;
		if(av != av2)
		{
			GTLINE2("ArrayVector operator += failed!");
			++nRet;
		}
		av = av1;
		cit = av.const_front_it();
		it = av.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("ArrayVector const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("ArrayVector iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - av.const_front_it() != 10)
		{
			GTLINE2("ArrayVector const iterator += operator failed!");
			++nRet;
		}
		if(it - av.front_it() != 10)
		{
			GTLINE2("ArrayVector iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("ArrayVector const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("ArrayVector iterator -= operator failed!");
			++nRet;
		}
		av.clear();
		if(av == av1)
		{
			GTLINE2("ArrayVector clear exist error!");
			++nRet;
		}
		av.destroy();
		if(av == av1)
		{
			GTLINE2("ArrayVector destroy exist error!");
			++nRet;
		}
		av1.clear();
		if(av != av1)
		{
			GTLINE2("ArrayVector clear exist error!");
			++nRet;
		}
		av1.destroy();
		if(av != av1)
		{
			GTLINE2("ArrayVector destroy exist error!");
			++nRet;
		}
		return nRet;
	}
};

#endif
