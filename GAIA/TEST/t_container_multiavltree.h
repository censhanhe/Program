#ifndef		__T_CONTAINER_MULTIAVLTREE_H__
#define		__T_CONTAINER_MULTIAVLTREE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_multiavltree(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ELEMENT_SIZE = 100;
		typedef GAIA::CTN::BasicMultiAVLTree<GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::U32> > __MultiAVLType;
		__MultiAVLType mavl;
		if(!mavl.empty())
		{
			GTLINE2("New mavl is not empty!");
			++nRet;
		}
		if(mavl.size() != 0)
		{
			GTLINE2("New mavl size not 0!");
			++nRet;
		}
		if(mavl.capacity() != 0)
		{
			GTLINE2("New mavl capacity not 0!");
			++nRet;
		}
		__MultiAVLType::it newit;
		__MultiAVLType::const_it newcit;
		newit = mavl.front_it();
		if(!newit.empty())
		{
			GTLINE2("New multiavl front_it is not empty!");
			++nRet;
		}
		newit = mavl.back_it();
		if(!newit.empty())
		{
			GTLINE2("New multiavl back_it is not empty!");
			++nRet;
		}
		newcit = mavl.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New multiavl const_front_it is not empty!");
			++nRet;
		}
		newcit = mavl.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New multiavl const_back_it is not empty!");
			++nRet;
		}
		mavl.clear();
		mavl.destroy();
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.insert(x))
			{
				GTLINE2("MultiAVL insert failed!");
				++nRet;
				break;
			}
		}
		if(mavl.empty())
		{
			GTLINE2("MultiAVL empty error!");
			++nRet;
		}
		if(mavl.size() != ELEMENT_SIZE)
		{
			GTLINE2("MultiAVL size error!");
			++nRet;
		}
		if(mavl.capacity() < ELEMENT_SIZE)
		{
			GTLINE2("MultiAVL capacity error!");
			++nRet;
		}
		if(!GAIA::ALGO::issorted(mavl.front_it(), mavl.back_it()))
		{
			GTLINE2("MultiAVL element not sorted!");
			++nRet;
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.insert(x))
			{
				GTLINE2("MultiAVL insert element twice must not successful");
				++nRet;
				break;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(mavl.find(x) == GNULL)
			{
				GTLINE2("MultiAVL find element failed!");
				++nRet;
				break;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if((*(const __MultiAVLType*)&mavl).find(x) == GNULL)
			{
				GTLINE2("MultiAVL const find element failed!");
				++nRet;
				break;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.erase(x))
			{
				GTLINE2("MultiAVL erase element failed!");
				++nRet;
				break;
			}
		}
		if(!mavl.empty())
		{
			GTLINE2("MultiAVL erase element cause empty failed!");
			++nRet;
		}
		if(mavl.size() != 0)
		{
			GTLINE2("MultiAVL erase element cause size failed!");
			++nRet;
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.insert(x))
			{
				GTLINE2("MultiAVL insert element failed!");
				++nRet;
				break;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(x % 10 == 1)
			{
				if(!mavl.erase(x))
				{
					GTLINE2("MultiAVL erase element failed!");
					++nRet;
					break;
				}
			}
		}
		if(mavl.empty())
		{
			GTLINE2("MultiAVL erase element cause empty failed!");
			++nRet;
		}
		if(mavl.size() != ELEMENT_SIZE - 10)
		{
			GTLINE2("MultiAVL erase element cause size failed!");
			++nRet;
		}
		__MultiAVLType::_datatype* pMin = mavl.minimize();
		if(pMin == GNULL)
		{
			GTLINE2("MultiAVL minimize failed!");
			++nRet;
		}
		if(*pMin != 0)
		{
			GTLINE2("MultiAVL minimize value error!");
			++nRet;
		}
		__MultiAVLType::_datatype* pMax = mavl.maximize();
		if(pMax == GNULL)
		{
			GTLINE2("MultiAVL maximize failed!");
			++nRet;
		}
		if(*pMax != 99)
		{
			GTLINE2("MultiAVL maximize value error!");
			++nRet;
		}
		mavl.destroy();
		pMin = mavl.minimize();
		if(pMin != GNULL)
		{
			GTLINE2("MultiAVL minimize failed!");
			++nRet;
		}
		if(pMin != GNULL)
		{
			GTLINE2("MultiAVL maximize failed!");
			++nRet;
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.insert(x))
			{
				GTLINE2("MultiAVL insert failed!");
				++nRet;
				break;
			}
		}
		__MultiAVLType::it frontit = mavl.front_it();
		__MultiAVLType::const_it cfrontit = mavl.const_front_it();
		__MultiAVLType::it backit = mavl.back_it();
		__MultiAVLType::const_it cbackit = mavl.const_back_it();
		GAIA::N32 tdata = 0;
		for(; !frontit.empty(); ++frontit)
		{
			if(*frontit != tdata)
			{
				GTLINE2("MultiAVL iterator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE)
		{
			GTLINE2("MultiAVL iterator ++ faield!");
			++nRet;
		}
		tdata = 0;
		for(; !cfrontit.empty(); ++cfrontit)
		{
			if(*cfrontit != tdata)
			{
				GTLINE2("MultiAVL const iterator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE)
		{
			GTLINE2("MultiAVL const iterator ++ failed!");
			++nRet;
		}
		tdata = ELEMENT_SIZE - 1;
		for(; !backit.empty(); --backit)
		{
			if(tdata != *backit)
			{
				GTLINE2("MultiAVL iterator -- failed!");
				++nRet;
				break;
			}
			--tdata;
		}
		if(tdata != -1)
		{
			GTLINE2("MultiAVL iterator -- failed!");
			++nRet;
		}
		tdata = ELEMENT_SIZE - 1;
		for(; !cbackit.empty(); --cbackit)
		{
			if(tdata != *cbackit)
			{
				GTLINE2("MultiAVL const iterator -- failed!");
				++nRet;
				break;
			}
			--tdata;
		}
		if(tdata != -1)
		{
			GTLINE2("MultiAVL const iterator -- failed!");
			++nRet;
		}
		mavl.clear();
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!mavl.insert(x))
			{
				GTLINE2("MultiAVL insert failed!");
				++nRet;
				break;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			__MultiAVLType::it it_l = mavl.lower_bound(x);
			__MultiAVLType::const_it cit_l = (*(const __MultiAVLType*)&mavl).lower_bound(x);
			__MultiAVLType::it it_u = mavl.upper_bound(x);
			__MultiAVLType::const_it cit_u = (*(const __MultiAVLType*)&mavl).upper_bound(x);
			if(*it_l != *cit_l ||
				*it_l != *it_u ||
				*it_l != *cit_u)
			{
				GTLINE2("MultiAVL lower_bound and upper_bound failed!");
				++nRet;
				break;
			}
			if(mavl.count(x) != 1)
			{
				GTLINE2("MultiAVL count failed!");
				++nRet;
			}
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			GAIA::BL bFailed = GAIA::False;
			for(GAIA::N32 t = 0; t < 10; ++t)
			{
				if(!mavl.insert(x))
				{
					GTLINE2("MultiAVL insert failed!");
					++nRet;
					bFailed = GAIA::True;
					break;
				}
			}
			if(bFailed)
				break;
		}
		for(__MultiAVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(mavl.count(x) != 11)
			{
				GTLINE2("MultiAVL insert or count failed!");
				++nRet;
				break;
			}
		}
		frontit = mavl.front_it();
		cfrontit = mavl.const_front_it();
		backit = mavl.back_it();
		cbackit = mavl.const_back_it();
		tdata = 0;
		for(; !frontit.empty(); ++frontit)
		{
			if(*frontit != tdata / 11)
			{
				GTLINE2("MultiAVL element value error or iterator operator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE * 11)
		{
			GTLINE2("MultiAVL iterator failed when multi elements!");
			++nRet;
		}
		tdata = 0;
		for(; !cfrontit.empty(); ++cfrontit)
		{
			if(*cfrontit != tdata / 11)
			{
				GTLINE2("MultiAVL element value error or iterator const operator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE * 11)
		{
			GTLINE2("MultiAVL const iterator failed when multi elements!");
			++nRet;
		}
		tdata = 0;
		for(; !backit.empty(); --backit)
		{
			if(*backit != ELEMENT_SIZE - tdata / 11 - 1)
			{
				GTLINE2("MultiAVL element value error or iterator operator -- failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE * 11)
		{
			GTLINE2("MultiAVL iterator failed when multi elements!");
			++nRet;
		}
		tdata = 0;
		for(; !cbackit.empty(); --cbackit)
		{
			if(*cbackit != ELEMENT_SIZE - tdata / 11 - 1)
			{
				GTLINE2("MultiAVL element value error or iterator const operator -- failed!");
				++nRet;
				break;
			}
			++tdata;
		}
		if(tdata != ELEMENT_SIZE * 11)
		{
			GTLINE2("MultiAVL const iterator failed when multi elements!");
			++nRet;
		}
		__MultiAVLType mavl1 = mavl;
		if(mavl1.size() != mavl.size())
		{
			GTLINE2("MultiAVL operator = cause size error!");
			++nRet;
		}
		if(mavl1.empty() != mavl.empty())
		{
			GTLINE2("MultiAVL operator = cause empty error!");
			++nRet;
		}
		{
			__MultiAVLType::it it = mavl.front_it();
			__MultiAVLType::const_it cit = mavl.const_front_it();
			__MultiAVLType::it it_b = mavl.back_it();
			__MultiAVLType::const_it cit_b = mavl.const_back_it();
			if(!(it_b >= it && it_b > it && it_b != it))
			{
				GTLINE2("MultiAVL iterator >= > != failed!");
				++nRet;
			}
			if(it_b <= it || it_b < it || it_b == it)
			{
				GTLINE2("MultiAVL iterator <= < == failed!");
				++nRet;
			}
			if(!(cit_b >= cit && cit_b > cit && cit_b != cit))
			{
				GTLINE2("MultiAVL const iterator >= > != failed!");
				++nRet;
			}
			if(cit_b <= cit || cit_b < cit || cit_b == cit)
			{
				GTLINE2("MultiAVL const iterator <= < == failed!");
				++nRet;
			}
			if((it + 10) - mavl.front_it() != 10)
			{
				GTLINE2("MultiAVL iterator operator + or - failed!");
				++nRet;
			}
			if((cit + 10) - mavl.const_front_it() != 10)
			{
				GTLINE2("MultiAVL const iterator operator + or - failed!");
				++nRet;
			}
			if(mavl.back_it() - (it_b - 10) != 10)
			{
				GTLINE2("MultiAVL iterator operator - failed!");
				++nRet;
			}
			if(mavl.const_back_it() - (cit_b - 10) != 10)
			{
				GTLINE2("MultiAVL const iterator operator - failed!");
				++nRet;
			}
		}
		if(mavl > mavl1 || mavl < mavl1 || mavl != mavl1)
		{
			GTLINE2("Same avltree compare > < != failed!");
			++nRet;
		}
		if(!(mavl >= mavl1 && mavl <= mavl1 && mavl == mavl1))
		{
			GTLINE2("Same avltree compare !(>= <= ==) failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
