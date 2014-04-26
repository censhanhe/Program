#ifndef		__T_ARRAY_H__
#define		__T_ARRAY_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_array(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CONTAINER::BasicArray<GAIA::N32, GAIA::N32, 100> __ArrayType;
		__ArrayType arr;
		if(arr.capacity() != 100)
		{
			GTLINE2("Array's capacity error!");
			++nRet;
		}
		if(arr.size() != 0)
		{
			GTLINE2("New array's size must been 0!");
			++nRet;
		}
		if(!arr.empty())
		{
			GTLINE2("New array must been empty!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr.capacity(); ++x)
		{
			if(!arr.push_back(x))
			{
				GTLINE2("array push_back return GAIA::False failed!");
				++nRet;
				break;
			}
		}
		if(arr.size() != arr.capacity())
		{
			GTLINE2("Full push_backed array's size must been capacity()!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr.size(); ++x)
		{
			if(arr[x] != x)
			{
				GTLINE2("Array's element value error!");
				++nRet;
				break;
			}
		}
		if(arr.capacity() != 100)
		{
			GTLINE2("Array's capacity must not changed!");
			++nRet;
		}
		__ArrayType arr1;
		arr1.push_back(arr.front_ptr(), arr.size());
		if(arr1.capacity() != 100)
		{
			GTLINE2("Array push_back multi element change the capacity error!");
			++nRet;
		}
		if(arr1.size() != arr1.capacity())
		{
			GTLINE2("Array push_back multi element and the size error!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr1.size(); ++x)
		{
			if(arr1[x] != x)
			{
				GTLINE2("Array push_back multi element and then the element value error!");
				++nRet;
				break;
			}
		}
		for(__ArrayType::_sizetype size = arr.size(); size > 0; --size)
		{
			if(arr.back() != size - 1)
			{
				GTLINE2("Array back element is error!");
				++nRet;
				break;
			}
			if(!arr.pop_back())
			{
				GTLINE2("Array pop_back failed!");
				++nRet;
				break;
			}
		}

		__ArrayType::_sizetype arrsize = arr1.size();
		__ArrayType::_datatype* pTemp = new __ArrayType::_datatype[arrsize];
		if(!arr1.pop_back(pTemp, arrsize))
		{
			GTLINE2("Array pop_back multi element failed!");
			++nRet;
		}
		if(!arr1.push_back(pTemp, arrsize))
		{
			GTLINE2("Array push_back multi element failed!");
			++nRet;
		}
		if(!arr.push_back(pTemp, arrsize))
		{
			GTLINE2("Array push_back multi element failed!");
			++nRet;
		}
		delete[] pTemp;
		pTemp = GNULL;
		if(arr1.size() != arrsize || 
			arr.size() != arrsize)
		{
			GTLINE2("Array push_back multi element size error!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr.size(); ++x)
		{
			if(arr[x] != arr1[x])
			{
				GTLINE2("Two array push_back multi element and element value error!");
				++nRet;
			}
		}
		if(arr.front() != arr1.front())
		{
			GTLINE2("Array's front element value not match!");
			++nRet;
		}
		if(!arr.resize(arr.size() / 2))
		{
			GTLINE2("Array resize operation failed!");
			++nRet;
		}
		if(arr.size() != arr1.size() / 2)
		{
			GTLINE2("Array resize operation failed!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr.size(); ++x)
		{
			if(arr.count(x) != 1)
			{
				GTLINE2("Array count operation failed!");
				++nRet;
				break;
			}
		}
		arr.reset(0);
		if(arr.size() != arr1.size() / 2)
		{
			GTLINE2("Array reset change the size error!");
			++nRet;
		}
		for(__ArrayType::_sizetype x = 0; x < arr.size(); ++x)
		{
			if(arr[x] != 0)
			{
				GTLINE2("Array reset change element value failed!");
				++nRet;
				break;
			}
		}
		for(__ArrayType::_sizetype x = 0; arr.capacity() != arr.size(); ++x)
			arr.push_back(x);
		if(arr.size() != arr.capacity())
		{
			GTLINE2("Array push_back element to capacity size failed!");
			++nRet;
		}
		arr.sort();
		if(!GAIA::ALGORITHM::issorted(arr.front_ptr(), arr.back_ptr()))
		{
			GTLINE2("Array sort failed!");
			++nRet;
		}
		if(arr.unique() != arr1.size() / 2)
		{
			GTLINE2("Array unique operation failed!");
			++nRet;
		}
		arr.resize(arr1.size() / 2);
		for(__ArrayType::_sizetype x = 0; arr.capacity() != arr.size(); ++x)
			arr.push_back(x);
		if(arr.size() != arr.capacity())
		{
			GTLINE2("Array push_back element to capacity size failed!");
			++nRet;
		}
		if(arr.unique_noorder() != arr1.size() / 2)
		{
			GTLINE2("Array unique_noorder operation failed!");
			++nRet;
		}
		arr.sort();
		if(!GAIA::ALGORITHM::issorted(arr.front_ptr(), arr.back_ptr()))
		{
			GTLINE2("Array sort failed!");
			++nRet;
		}
		__ArrayType::const_it cit = arr.const_front_it();
		while(!cit.empty())
		{
			if(arr.search(*cit) == GINVALID)
			{
				GTLINE2("Array search failed!");
				++nRet;
				break;
			}
			if(arr.find(*cit, 0) == GINVALID)
			{
				GTLINE2("Array find failed!");
				++nRet;
				break;
			}
			if(arr.rfind(*cit, arr.size() - 1) == GINVALID)
			{
				GTLINE2("Array rfind failed!");
				++nRet;
				break;
			}
			++cit;
		}
		arr.inverse();
		__ArrayType::it it = arr.front_it();
		while(!it.empty())
		{
			__ArrayType::it itt = it;
			++itt;
			if(!itt.empty())
			{
				if(*it <= *itt)
				{
					GTLINE2("Array inverse failed!");
					++nRet;
					break;
				}
			}
			++it;
		}
		arr1 = arr;
		if(!arr.insert(997, 0))
		{
			GTLINE2("Array insert failed!");
			++nRet;
		}
		__ArrayType::_sizetype insertindex1 = arr.size() / 2;
		if(!arr.insert(998, insertindex1))
		{
			GTLINE2("Array insert failed!");
			++nRet;
		}
		__ArrayType::_sizetype insertindex2 = arr.size();
		if(!arr.insert(999, insertindex2))
		{
			GTLINE2("Array insert failed!");
			++nRet;
		}
		if(arr[0] != 997)
		{
			GTLINE2("Array insert value check failed!");
			++nRet;
		}
		if(arr[insertindex1] != 998)
		{
			GTLINE2("Array insert value check failed!");
			++nRet;
		}
		if(arr[insertindex2] != 999)
		{
			GTLINE2("Array insert value check failed!");
			++nRet;
		}
		if(!arr.erase(insertindex2))
		{
			GTLINE2("Array erase tail element failed!");
			++nRet;
		}
		if(!arr.erase(insertindex1))
		{
			GTLINE2("Array erase middle element failed!");
			++nRet;
		}
		if(!arr.erase(0))
		{
			GTLINE2("Array erase first element failed!");
			++nRet;
		}
		if(arr > arr1 || arr < arr1 || arr != arr1)
		{
			GTLINE2("Same array compare > < != failed!");
			++nRet;
		}
		if(!(arr >= arr1 && arr <= arr1 && arr == arr1))
		{
			GTLINE2("Same array compare !(>= <= ==) faield!");
			++nRet;
		}
		it = arr.front_it();
		while(!it.empty())
		{
			__ArrayType::it itfinded = arr.lower_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("Array lower_bound failed!");
				++nRet;
				break;
			}
			itfinded = arr.upper_bound(*it);
			if(itfinded.empty())
			{
				GTLINE2("Array upper_bound failed!");
				++nRet;
				break;
			}
			++it;
		}
		const __ArrayType& arrc = arr;
		cit = arrc.const_front_it();
		while(!cit.empty())
		{
			__ArrayType::const_it citfinded = arrc.lower_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("Array lower_bound const failed!");
				++nRet;
				break;
			}
			citfinded = arrc.upper_bound(*cit);
			if(citfinded.empty())
			{
				GTLINE2("Array upper_bound const faield!");
				++nRet;
				break;
			}
			++cit;
		}
		arr.inverse();
		cit = arr.const_front_it();
		it = arr1.front_it();
		while(!cit.empty())
		{
			*it = *cit;
			++it;
			++cit;
		}
		if(arr != arr1)
		{
			GTLINE2("Array iterator copy element failed!");
			++nRet;
		}
		__ArrayType arr2;
		arr2 = arr1;
		arr2 += arr1;
		arr += arr1;
		if(arr != arr2)
		{
			GTLINE2("Array operator += faield!");
			++nRet;
		}
		return nRet;
	}
};

#endif