#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_multiset(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_SIZE = 33;
		typedef GAIA::CTN::BasicMultiSet<GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32> > __MultiSetType;
		__MultiSetType ms;
		if(!ms.empty())
		{
			GTLINE2("New multiset is not empty!");
			++nRet;
		}
		if(ms.size() != 0)
		{
			GTLINE2("New multiset size must zero!");
			++nRet;
		}
		if(ms.capacity() != 0)
		{
			GTLINE2("New multiset capacity is not zero!");
			++nRet;
		}
		__MultiSetType::it newit;
		__MultiSetType::const_it newcit;
		newit = ms.front_it();
		if(!newit.empty())
		{
			GTLINE2("New multiset front_it is not empty!");
			++nRet;
		}
		newit = ms.back_it();
		if(!newit.empty())
		{
			GTLINE2("New multiset back_it is not empty!");
			++nRet;
		}
		newcit = ms.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New multiset const_front_it is not empty!");
			++nRet;
		}
		newcit = ms.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New multiset const_back_it is not empty!");
			++nRet;
		}
		ms.clear();
		ms.destroy();
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			for(GAIA::N32 t = 0; t < 10; ++t)
			{
				if(!ms.insert(x))
				{
					GTLINE2("MultiSet insert element failed!");
					++nRet;
					break;
				}
			}
		}
		__MultiSetType::__DataListType listResult;
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(ms.find(x) == GNIL)
			{
				GTLINE2("MultiSet find element failed!");
				++nRet;
				break;
			}
			if(static_cast<const __MultiSetType*>(&ms)->find(x) == GNIL)
			{
				GTLINE2("MultiSet const find element failed!");
				++nRet;
				break;
			}
			listResult.clear();
			if(!ms.find(x, listResult))
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
			if(ms.count(x) != 10)
			{
				GTLINE2("MultiSet count failed!");
				++nRet;
				break;
			}
			__MultiSetType::it it_l = ms.lower_bound(x);
			if(it_l.empty())
			{
				GTLINE2("MultiSet lower_bound failed!");
				++nRet;
				break;
			}
			__MultiSetType::const_it cit_l = static_cast<const __MultiSetType*>(&ms)->lower_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("MultiSet const lower_bound failed!");
				++nRet;
				break;
			}
			__MultiSetType::it it_u = ms.upper_bound(x);
			if(it_l.empty())
			{
				GTLINE2("MultiSet upper_bound failed!");
				++nRet;
				break;
			}
			__MultiSetType::const_it cit_u = static_cast<const __MultiSetType*>(&ms)->upper_bound(x);
			if(cit_l.empty())
			{
				GTLINE2("MultiSet const upper_bound failed!");
				++nRet;
				break;
			}
		}
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!ms.erase(GAIA::CTN::Pair<GAIA::N32, GAIA::U32>(x, 0)))
			{
				GTLINE2("MultiSet erase single element failed!");
				++nRet;
				break;;
			}
			if(ms.count(x) != 9)
			{
				GTLINE2("MultiSet erase single element failed!");
				++nRet;
				break;
			}
			if(!ms.erase(x))
			{
				GTLINE2("MultiSet erase element by key failed!");
				++nRet;
				break;
			}
			if(ms.count(x) != 0)
			{
				GTLINE2("MultiSet erase element by key failed!");
				++nRet;
				break;
			}
		}
		ms.destroy();
		if(!ms.empty())
		{
			GTLINE2("MultiSet destroy failed!");
			++nRet;
		}
		if(ms.size() != 0)
		{
			GTLINE2("MultiSet destroy failed!");
			++nRet;
		}
		if(ms.capacity() != 0)
		{
			GTLINE2("MultiSet destroy failed!");
			++nRet;
		}
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!ms.insert(x))
			{
				GTLINE2("MultiSet insert element failed!");
				++nRet;
				break;
			}
		}
		__MultiSetType::it itfront = ms.front_it();
		__MultiSetType::const_it citfront = ms.const_front_it();
		__MultiSetType::it itback = ms.back_it();
		__MultiSetType::const_it citback = ms.const_back_it();
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(itfront.empty() ||
				citfront.empty() ||
				itback.empty() ||
				citback.empty())
			{
				GTLINE2("MultiSet iterator exist error!");
				++nRet;
				break;
			}
			if(*itfront != x ||
				*citfront != x ||
				*itback != ELEMENT_SIZE - x - 1 ||
				*citback != ELEMENT_SIZE - x - 1)
			{
				GTLINE2("MultiSet iterator exist error!");
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
			GTLINE2("MultiSet iterator ++ -- exist error!");
			++nRet;
		}
		ms.clear();
		if(!ms.empty())
		{
			GTLINE2("MultiSet clear failed!");
			++nRet;
		}
		if(ms.size() != 0)
		{
			GTLINE2("MultiSet clear failed!");
			++nRet;
		}
		if(ms.capacity() == 0)
		{
			GTLINE2("MultiSet clear failed!");
			++nRet;
		}
		itfront = ms.front_it();
		citfront = ms.const_front_it();
		itback = ms.back_it();
		citback = ms.const_back_it();
		if(!itfront.empty() ||
			!citfront.empty() ||
			!itback.empty() ||
			!citback.empty())
		{
			GTLINE2("MultiSet iterator not empty when multiset is empty!");
			++nRet;
		}
		if(itfront != itback)
		{
			GTLINE2("MultiSet iterator exist error!");
			++nRet;
		}
		if(citfront != citback)
		{
			GTLINE2("MultiSet iterator exist error!");
			++nRet;
		}
		for(__MultiSetType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!ms.insert(x))
			{
				GTLINE2("MultiSet insert element failed!");
				++nRet;
				break;
			}
		}
		__MultiSetType ms1 = ms;
		if(!(ms1 == ms && ms1 >= ms && ms1 <= ms))
		{
			GTLINE2("MultiSet operator == >= <= failed!");
			++nRet;
		}
		if(ms1 != ms || ms1 > ms || ms1 < ms)
		{
			GTLINE2("MultiSet operator != > < failed!");
			++nRet;
		}
		itfront = ms1.front_it();
		citfront = ms1.const_front_it();
		itback = ms1.back_it();
		citback = ms1.const_back_it();
		if(itfront >= itback || itfront > itback || itfront == itback ||
			citfront >= citback || citfront > citback || citfront == citback)
		{
			GTLINE2("MultiSet iterator operator >= > == failed!");
			++nRet;
		}
		if(!(itfront <= itback && itfront < itback && itfront != itback &&
			citfront <= citback && citfront < citback && citfront != citback))
		{
			GTLINE2("MultiSet iterator operator <= < != failed!");
			++nRet;
		}
		if((itfront + 10) - 10 != ms1.front_it() ||
			(citfront + 10) - 10 != ms1.const_front_it())
		{
			GTLINE2("MultiSet iterator operator + or - failed!");
			++nRet;
		}
		if(itfront + 10 - ms1.front_it() != 10 ||
			citfront + 10 - ms1.const_front_it() != 10)
		{
			GTLINE2("MultiSet iterator operator + or - failed!");
			++nRet;
		}
		itfront += ELEMENT_SIZE - 1;
		itback -= ELEMENT_SIZE - 1;
		citfront += ELEMENT_SIZE - 1;
		citback -= ELEMENT_SIZE - 1;
		if(itfront != ms1.back_it() ||
			itback != ms1.front_it() ||
			citfront != ms1.const_back_it() ||
			citback != ms1.const_front_it())
		{
			GTLINE2("MultiSet iterator += or -= error!");
			++nRet;
		}
		return nRet;
	}
};
