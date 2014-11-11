#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_vector(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CTN::BasicVector<GAIA::N32, GAIA::N32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32> > __VectorType;
		__VectorType vec;
		vec.reserve(100);
		if(vec.capacity() != 100)
		{
			GTLINE2("Vector's capacity error!");
			++nRet;
		}
		if(vec.size() != 0)
		{
			GTLINE2("New vector's size must been 0!");
			++nRet;
		}
		if(!vec.empty())
		{
			GTLINE2("New vector must been empty!");
			++nRet;
		}
		__VectorType::it newit;
		__VectorType::const_it newcit;
		newit = vec.front_it();
		if(!newit.empty())
		{
			GTLINE2("New vector front_it is not empty!");
			++nRet;
		}
		newit = vec.back_it();
		if(!newit.empty())
		{
			GTLINE2("New vector back_it is not empty!");
			++nRet;
		}
		newcit = vec.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New vector const_front_it is not empty!");
			++nRet;
		}
		newcit = vec.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New vector const_back_it is not empty!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.capacity(); ++x)
			vec.push_back(x);
		if(vec.size() != vec.capacity())
		{
			GTLINE2("Full push_backed vector's size must been capacity()!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.size(); ++x)
		{
			if(vec[x] != x)
			{
				GTLINE2("Vector's element value error!");
				++nRet;
				break;
			}
		}
		if(vec.capacity() != 100)
		{
			GTLINE2("Vector's capacity must not changed!");
			++nRet;
		}
		vec.clear();
		for(__VectorType::_sizetype x = 0; x < vec.capacity(); ++x)
		{
			if(!vec.insert(x, x))
			{
				GTLINE2("Vector insert element failed!");
				++nRet;
				break;
			}
		}
		if(vec.size() != vec.capacity())
		{
			GTLINE2("Full push_backed vector's size must been capacity()!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.size(); ++x)
		{
			if(vec[x] != x)
			{
				GTLINE2("Vector's element value error!");
				++nRet;
				break;
			}
		}
		if(vec.capacity() != 100)
		{
			GTLINE2("Vector's capacity must not changed!");
			++nRet;
		}
		__VectorType vec1;
		vec1.push_back(vec.front_ptr(), vec.size());
		if(vec1.capacity() != 100)
		{
			GTLINE2("Vector push_back multi element change the capacity error!");
			++nRet;
		}
		if(vec1.size() != vec1.capacity())
		{
			GTLINE2("Vector push_back multi element and the size error!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec1.size(); ++x)
		{
			if(vec1[x] != x)
			{
				GTLINE2("Vector push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype size = vec.size(); size > 0; --size)
		{
			if(vec.back() != size - 1)
			{
				GTLINE2("Vector back element is error!");
				++nRet;
				break;
			}
			if(!vec.pop_back())
			{
				GTLINE2("Vector pop_back failed!");
				++nRet;
				break;
			}
		}

		__VectorType::_sizetype arrsize = vec1.size();
		__VectorType::_datatype* pTemp = new __VectorType::_datatype[arrsize];
		if(!vec1.pop_back(pTemp, arrsize))
		{
			GTLINE2("Vector pop_back multi element failed!");
			++nRet;
		}
		vec1.push_back(pTemp, arrsize);
		vec.push_back(pTemp, arrsize);

		delete[] pTemp;
		pTemp = GNIL;
		if(vec1.size() != arrsize ||
			vec.size() != arrsize)
		{
			GTLINE2("Vector push_back multi element size error!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.size(); ++x)
		{
			if(vec[x] != vec1[x])
			{
				GTLINE2("Two vector push_back multi element and element value error!");
				++nRet;
			}
		}
		if(vec.front() != vec1.front())
		{
			GTLINE2("Vector's front element value not match!");
			++nRet;
		}
		vec.resize(vec.size() / 2);
		if(vec.size() != vec1.size() / 2)
		{
			GTLINE2("Vector resize operation failed!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.size(); ++x)
		{
			if(vec.count(x) != 1)
			{
				GTLINE2("Vector count operation failed!");
				++nRet;
				break;
			}
		}
		vec.reset(0);
		if(vec.size() != vec1.size() / 2)
		{
			GTLINE2("Vector reset change the size error!");
			++nRet;
		}
		for(__VectorType::_sizetype x = 0; x < vec.size(); ++x)
		{
			if(vec[x] != 0)
			{
				GTLINE2("Vector reset change element value failed!");
				++nRet;
				break;
			}
		}
		for(__VectorType::_sizetype x = 0; vec.capacity() != vec.size(); ++x)
			vec.push_back(x);
		if(vec.size() != vec.capacity())
		{
			GTLINE2("Vector push_back element to capacity size failed!");
			++nRet;
		}
		vec.sort();
		if(!GAIA::ALGO::issorted(vec.front_ptr(), vec.back_ptr()))
		{
			GTLINE2("Vector sort failed!");
			++nRet;
		}
		if(vec.unique() != vec1.size() / 2)
		{
			GTLINE2("Vector unique operation failed!");
			++nRet;
		}
		vec.resize(vec1.size() / 2);
		for(__VectorType::_sizetype x = 0; vec.capacity() != vec.size(); ++x)
			vec.push_back(x);
		if(vec.size() != vec.capacity())
		{
			GTLINE2("Vector push_back element to capacity size failed!");
			++nRet;
		}
		if(vec.unique_noorder() != vec1.size() / 2)
		{
			GTLINE2("Vector unique_noorder operation failed!");
			++nRet;
		}
		vec.sort();
		if(!GAIA::ALGO::issorted(vec.front_ptr(), vec.back_ptr()))
		{
			GTLINE2("Vector sort failed!");
			++nRet;
		}
		__VectorType::const_it cit = vec.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			if(vec.search(*cit) == GINVALID)
			{
				GTLINE2("Vector search failed!");
				++nRet;
				break;
			}
			if(vec.find(*cit, 0) == GINVALID)
			{
				GTLINE2("Vector find failed!");
				++nRet;
				break;
			}
			if(vec.rfind(*cit, vec.size() - 1) == GINVALID)
			{
				GTLINE2("Vector rfind failed!");
				++nRet;
				break;
			}
		}
		vec.inverse();
		__VectorType::it it = vec.front_it();
		for(; !it.empty(); ++it)
		{
			__VectorType::it itt = it;
			++itt;
			if(!itt.empty())
			{
				if(*it <= *itt)
				{
					GTLINE2("Vector inverse failed!");
					++nRet;
					break;
				}
			}
		}
		vec1 = vec;
		if(!vec.insert(997, 0))
		{
			GTLINE2("Vector insert failed!");
			++nRet;
		}
		__VectorType::_sizetype insertindex1 = vec.size() / 2;
		if(!vec.insert(998, insertindex1))
		{
			GTLINE2("Vector insert failed!");
			++nRet;
		}
		__VectorType::_sizetype insertindex2 = vec.size();
		if(!vec.insert(999, insertindex2))
		{
			GTLINE2("Vector insert failed!");
			++nRet;
		}
		if(vec[0] != 997)
		{
			GTLINE2("Vector insert value check failed!");
			++nRet;
		}
		if(vec[insertindex1] != 998)
		{
			GTLINE2("Vector insert value check failed!");
			++nRet;
		}
		if(vec[insertindex2] != 999)
		{
			GTLINE2("Vector insert value check failed!");
			++nRet;
		}
		if(!vec.erase(insertindex2))
		{
			GTLINE2("Vector erase tail element failed!");
			++nRet;
		}
		if(!vec.erase(insertindex1))
		{
			GTLINE2("Vector erase middle element failed!");
			++nRet;
		}
		if(!vec.erase(0))
		{
			GTLINE2("Vector erase first element failed!");
			++nRet;
		}
		if(vec > vec1 || vec < vec1 || vec != vec1)
		{
			GTLINE2("Same vector compare > < != failed!");
			++nRet;
		}
		if(!(vec >= vec1 && vec <= vec1 && vec == vec1))
		{
			GTLINE2("Same vector compare !(>= <= ==) failed!");
			++nRet;
		}
		vec.sort();
		it = vec.front_it();
		for(; !it.empty(); ++it)
		{
			__VectorType::it itfinded = vec.lower_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("Vector lower_bound failed!");
				++nRet;
				break;
			}
			itfinded = vec.upper_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("Vector upper_bound failed!");
				++nRet;
				break;
			}
		}
		const __VectorType& arrc = vec;
		cit = arrc.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			__VectorType::const_it citfinded = arrc.lower_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("Vector lower_bound const failed!");
				++nRet;
				break;
			}
			citfinded = arrc.upper_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("Vector upper_bound const failed!");
				++nRet;
				break;
			}
		}
		vec.inverse();
		cit = vec.const_front_it();
		it = vec1.front_it();
		for(; !cit.empty(); ++cit, ++it)
			*it = *cit;
		if(vec != vec1)
		{
			GTLINE2("Vector iterator copy element failed!");
			++nRet;
		}
		__VectorType vec2;
		vec2 = vec1;
		vec2 += vec1;
		vec += vec;
		if(vec != vec2)
		{
			GTLINE2("Vector operator += failed!");
			++nRet;
		}
		vec = vec1;
		cit = vec.const_front_it();
		it = vec.front_it();
		if((cit + 10) - cit != 10)
		{
			GTLINE2("Vector const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((it + 10) - it != 10)
		{
			GTLINE2("Vector iterator's operator + index or - iterator failed!");
			++nRet;
		}
		cit += 10;
		it += 10;
		if(cit - vec.const_front_it() != 10)
		{
			GTLINE2("Vector const iterator += operator failed!");
			++nRet;
		}
		if(it - vec.front_it() != 10)
		{
			GTLINE2("Vector iterator += operator failed!");
			++nRet;
		}
		cit -= 20;
		it -= 20;
		if(!cit.empty())
		{
			GTLINE2("Vector const iterator -= operator failed!");
			++nRet;
		}
		if(!it.empty())
		{
			GTLINE2("Vector iterator -= operator failed!");
			++nRet;
		}
		vec.clear();
		if(vec == vec1)
		{
			GTLINE2("Vector clear exist error!");
			++nRet;
		}
		vec.destroy();
		if(vec == vec1)
		{
			GTLINE2("Vector destroy exist error!");
			++nRet;
		}
		vec1.clear();
		if(vec != vec1)
		{
			GTLINE2("Vector clear exist error!");
			++nRet;
		}
		vec1.destroy();
		if(vec != vec1)
		{
			GTLINE2("Vector destroy exist error!");
			++nRet;
		}
		return nRet;
	}
};
