#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_multimap(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_SIZE = 33;
		typedef GAIA::CTN::BasicMultiMap<GAIA::N32, GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32> > __MultiMapType;
		__MultiMapType mm;
		if(!mm.empty())
		{
			GTLINE2("New multimap is not empty!");
			++nRet;
		}
		if(mm.size() != 0)
		{
			GTLINE2("New multimap size must zero!");
			++nRet;
		}
		if(mm.capacity() != 0)
		{
			GTLINE2("New multimap capacity is not zero!");
			++nRet;
		}
		mm.clear();
		mm.destroy();
		__MultiMapType::it newit;
		__MultiMapType::const_it newcit;
		newit = mm.front_it();
		if(!newit.empty())
		{
			GTLINE2("New multimap front_it is not empty!");
			++nRet;
		}
		newit = mm.back_it();
		if(!newit.empty())
		{
			GTLINE2("New multimap back_it is not empty!");
			++nRet;
		}
		newcit = mm.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New multimap const_front_it is not empty!");
			++nRet;
		}
		newcit = mm.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New multimap const_back_it is not empty!");
			++nRet;
		}
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			for(GAIA::N32 t = 0; t < 10; ++t)
				mm.insert(x, x);
		}
		__MultiMapType::__DataListType listResult;
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(mm.find(x) == GNIL)
			{
				GTLINE2("MultiMap find element failed!");
				++nRet;
				break;
			}
			if(static_cast<const __MultiMapType*>(&mm)->find(x) == GNIL)
			{
				GTLINE2("MultiMap const find element failed!");
				++nRet;
				break;
			}
			listResult.clear();
			if(!mm.find(x, listResult))
			{
				GTLINE2("MultiMap find multi element failed!");
				++nRet;
				break;
			}
			if(listResult.size() != 10)
			{
				GTLINE2("MultiMap find multi element failed!");
				++nRet;
				break;
			}
			if(mm.count(x) != 10)
			{
				GTLINE2("MultiMap count failed!");
				++nRet;
				break;
			}
			__MultiMapType::it it_l = mm.lower_bound(x);
			if(it_l.empty())
			{
				GTLINE2("MultiMap lower_bound failed!");
				++nRet;
				break;
			}
			__MultiMapType::const_it cit_l = static_cast<const __MultiMapType*>(&mm)->lower_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("MultiMap const lower_bound failed!");
				++nRet;
				break;
			}
			__MultiMapType::it it_u = mm.upper_bound(x);
			if(it_l.empty())
			{
				GTLINE2("MultiMap upper_bound failed!");
				++nRet;
				break;
			}
			__MultiMapType::const_it cit_u = static_cast<const __MultiMapType*>(&mm)->upper_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("MultiMap const upper_bound failed!");
				++nRet;
				break;
			}
		}
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mm.erase(GAIA::CTN::Pair<GAIA::N32, GAIA::U32>(x, 0)))
			{
				GTLINE2("MultiMap erase single element failed!");
				++nRet;
				break;;
			}
			if(mm.count(x) != 9)
			{
				GTLINE2("MultiMap erase single element failed!");
				++nRet;
				break;
			}
			if(!mm.erase(x))
			{
				GTLINE2("MultiMap erase element by key failed!");
				++nRet;
				break;
			}
			if(mm.count(x) != 0)
			{
				GTLINE2("MultiMap erase element by key failed!");
				++nRet;
				break;
			}
		}
		mm.destroy();
		if(!mm.empty())
		{
			GTLINE2("MultiMap destroy failed!");
			++nRet;
		}
		if(mm.size() != 0)
		{
			GTLINE2("MultiMap destroy failed!");
			++nRet;
		}
		if(mm.capacity() != 0)
		{
			GTLINE2("MultiMap destroy failed!");
			++nRet;
		}
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
			mm.insert(x, x);
		__MultiMapType::it itfront = mm.front_it();
		__MultiMapType::const_it citfront = mm.const_front_it();
		__MultiMapType::it itback = mm.back_it();
		__MultiMapType::const_it citback = mm.const_back_it();
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(itfront.empty() ||
				citfront.empty() ||
				itback.empty() ||
				citback.empty())
			{
				GTLINE2("MultiMap iterator exist error!");
				++nRet;
				break;
			}
			if(*itfront != x ||
				*citfront != x ||
				*itback != ELEMENT_SIZE - x - 1 ||
				*citback != ELEMENT_SIZE - x - 1)
			{
				GTLINE2("MultiMap iterator exist error!");
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
			GTLINE2("MultiMap iterator ++ -- exist error!");
			++nRet;
		}
		mm.clear();
		if(!mm.empty())
		{
			GTLINE2("MultiMap clear failed!");
			++nRet;
		}
		if(mm.size() != 0)
		{
			GTLINE2("MultiMap clear failed!");
			++nRet;
		}
		if(mm.capacity() == 0)
		{
			GTLINE2("MultiMap clear failed!");
			++nRet;
		}
		itfront = mm.front_it();
		citfront = mm.const_front_it();
		itback = mm.back_it();
		citback = mm.const_back_it();
		if(!itfront.empty() ||
			!citfront.empty() ||
			!itback.empty() ||
			!citback.empty())
		{
			GTLINE2("MultiMap iterator not empty when multimap is empty!");
			++nRet;
		}
		if(itfront != itback)
		{
			GTLINE2("MultiMap iterator exist error!");
			++nRet;
		}
		if(citfront != citback)
		{
			GTLINE2("MultiMap iterator exist error!");
			++nRet;
		}
		for(__MultiMapType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
			mm.insert(x, x);
		__MultiMapType mm1 = mm;
		if(!(mm1 == mm && mm1 >= mm && mm1 <= mm))
		{
			GTLINE2("MultiMap operator == >= <= failed!");
			++nRet;
		}
		if(mm1 != mm || mm1 > mm || mm1 < mm)
		{
			GTLINE2("MultiMap operator != > < failed!");
			++nRet;
		}
		itfront = mm1.front_it();
		citfront = mm1.const_front_it();
		itback = mm1.back_it();
		citback = mm1.const_back_it();
		if(itfront >= itback || itfront > itback || itfront == itback ||
			citfront >= citback || citfront > citback || citfront == citback)
		{
			GTLINE2("MultiMap iterator operator >= > == failed!");
			++nRet;
		}
		if(!(itfront <= itback && itfront < itback && itfront != itback &&
			citfront <= citback && citfront < citback && citfront != citback))
		{
			GTLINE2("MultiMap iterator operator <= < != failed!");
			++nRet;
		}
		if((itfront + 10) - 10 != mm1.front_it() ||
			(citfront + 10) - 10 != mm1.const_front_it())
		{
			GTLINE2("MultiMap iterator operator + or - failed!");
			++nRet;
		}
		if(itfront + 10 - mm1.front_it() != 10 ||
			citfront + 10 - mm1.const_front_it() != 10)
		{
			GTLINE2("MultiMap iterator operator + or - failed!");
			++nRet;
		}
		itfront += ELEMENT_SIZE - 1;
		itback -= ELEMENT_SIZE - 1;
		citfront += ELEMENT_SIZE - 1;
		citback -= ELEMENT_SIZE - 1;
		if(itfront != mm1.back_it() ||
			itback != mm1.front_it() ||
			citfront != mm1.const_back_it() ||
			citback != mm1.const_front_it())
		{
			GTLINE2("MultiMap iterator += or -= error!");
			++nRet;
		}
		return nRet;
	}
};
