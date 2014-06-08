#ifndef		__T_AVLTREE_H__
#define		__T_AVLTREE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_avltree(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ELEMENT_SIZE = 100;
		typedef GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __AVLType;
		__AVLType avl;
		if(!avl.empty())
		{
			GTLINE2("New avl is not empty!");
			++nRet;
		}
		if(avl.size() != 0)
		{
			GTLINE2("New avl size not 0!");
			++nRet;
		}
		if(avl.capacity() != 0)
		{
			GTLINE2("New avl capacity not 0!");
			++nRet;
		}
		avl.clear();
		avl.destroy();
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!avl.insert(x))
			{
				GTLINE2("AVL insert failed!");
				++nRet;
				break;
			}
		}
		if(avl.empty())
		{
			GTLINE2("AVL empty error!");
			++nRet;
		}
		if(avl.size() != ELEMENT_SIZE)
		{
			GTLINE2("AVL size error!");
			++nRet;
		}
		if(avl.capacity() < ELEMENT_SIZE)
		{
			GTLINE2("AVL capacity error!");
			++nRet;
		}
		if(!GAIA::ALGORITHM::issorted(avl.front_it(), avl.back_it()))
		{
			GTLINE2("AVL element not sorted!");
			++nRet;
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(avl.insert(x))
			{
				GTLINE2("AVL insert element twice must not successful");
				++nRet;
				break;
			}
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(avl.find(x) == GNULL)
			{
				GTLINE2("AVL find element failed!");
				++nRet;
				break;
			}
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if((*(const __AVLType*)&avl).find(x) == GNULL)
			{
				GTLINE2("AVL const find element failed!");
				++nRet;
				break;
			}
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!avl.erase(x))
			{
				GTLINE2("AVL erase element failed!");
				++nRet;
				break;
			}
		}
		if(!avl.empty())
		{
			GTLINE2("AVL erase element cause empty failed!");
			++nRet;
		}
		if(avl.size() != 0)
		{
			GTLINE2("AVL erase element cause size failed!");
			++nRet;
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!avl.insert(x))
			{
				GTLINE2("AVL insert element failed!");
				++nRet;
				break;
			}
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(x % 10 == 1)
			{
				if(!avl.erase(x))
				{
					GTLINE2("AVL erase element failed!");
					++nRet;
					break;
				}
			}
		}
		if(avl.empty())
		{
			GTLINE2("AVL erase element cause empty failed!");
			++nRet;
		}
		if(avl.size() != ELEMENT_SIZE - 10)
		{
			GTLINE2("AVL erase element cause size failed!");
			++nRet;
		}
		__AVLType::_datatype* pMin = avl.minimize();
		if(pMin == GNULL)
		{
			GTLINE2("AVL minimize failed!");
			++nRet;
		}
		if(*pMin != 0)
		{
			GTLINE2("AVL minimize value error!");
			++nRet;
		}
		__AVLType::_datatype* pMax = avl.maximize();
		if(pMax == GNULL)
		{
			GTLINE2("AVL maximize failed!");
			++nRet;
		}
		if(*pMax != 99)
		{
			GTLINE2("AVL maximize value error!");
			++nRet;
		}
		avl.destroy();
		pMin = avl.minimize();
		if(pMin != GNULL)
		{
			GTLINE2("AVL minimize failed!");
			++nRet;
		}
		if(pMin != GNULL)
		{
			GTLINE2("AVL maximize failed!");
			++nRet;
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!avl.insert(x))
			{
				GTLINE2("AVL insert failed!");
				++nRet;
				break;
			}
		}
		__AVLType::it frontit = avl.front_it();
		__AVLType::const_it cfrontit = avl.const_front_it();
		__AVLType::it backit = avl.back_it();
		__AVLType::const_it cbackit = avl.const_back_it();
		GAIA::N32 tdata = 0;
		while(!frontit.empty())
		{
			if(*frontit != tdata)
			{
				GTLINE2("AVL iterator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
			++frontit;
		}
		if(tdata != ELEMENT_SIZE)
		{
			GTLINE2("AVL iterator ++ faield!");
			++nRet;
		}
		tdata = 0;
		while(!cfrontit.empty())
		{
			if(*cfrontit != tdata)
			{
				GTLINE2("AVL const iterator ++ failed!");
				++nRet;
				break;
			}
			++tdata;
			++cfrontit;
		}
		if(tdata != ELEMENT_SIZE)
		{
			GTLINE2("AVL const iterator ++ failed!");
			++nRet;
		}
		tdata = ELEMENT_SIZE - 1;
		while(!backit.empty())
		{
			if(tdata != *backit)
			{
				GTLINE2("AVL iterator -- failed!");
				++nRet;
				break;
			}
			--tdata;
			--backit;
		}
		if(tdata != -1)
		{
			GTLINE2("AVL iterator -- failed!");
			++nRet;
		}
		tdata = ELEMENT_SIZE - 1;
		while(!cbackit.empty())
		{
			if(tdata != *cbackit)
			{
				GTLINE2("AVL const iterator -- failed!");
				++nRet;
				break;
			}
			--tdata;
			--cbackit;
		}
		if(tdata != -1)
		{
			GTLINE2("AVL const iterator -- failed!");
			++nRet;
		}
		avl.clear();
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			if(!avl.insert(x))
			{
				GTLINE2("AVL insert failed!");
				++nRet;
				break;
			}
		}
		for(__AVLType::_datatype x = 0; x < ELEMENT_SIZE; ++x)
		{
			__AVLType::it it_l = avl.lower_bound(x);
			__AVLType::const_it cit_l = (*(const __AVLType*)&avl).lower_bound(x);
			__AVLType::it it_u = avl.upper_bound(x);
			__AVLType::const_it cit_u = (*(const __AVLType*)&avl).upper_bound(x);
			if(*it_l != *cit_l ||
				*it_l != *it_u ||
				*it_l != *cit_u)
			{
				GTLINE2("AVL lower_bound and upper_bound failed!");
				++nRet;
				break;
			}
		}
		__AVLType avl1 = avl;
		if(avl1.size() != avl.size())
		{
			GTLINE2("AVL operator = cause size error!");
			++nRet;
		}
		if(avl1.empty() != avl.empty())
		{
			GTLINE2("AVL operator = cause empty error!");
			++nRet;
		}
		{
			__AVLType::it it = avl.front_it();
			__AVLType::const_it cit = avl.const_front_it();
			__AVLType::it it_b = avl.back_it();
			__AVLType::const_it cit_b = avl.const_back_it();
			if(!(it_b >= it && it_b > it && it_b != it))
			{
				GTLINE2("AVL iterator >= > != failed!");
				++nRet;
			}
			if(it_b <= it || it_b < it || it_b == it)
			{
				GTLINE2("AVL iterator <= < == failed!");
				++nRet;
			}
			if(!(cit_b >= cit && cit_b > cit && cit_b != cit))
			{
				GTLINE2("AVL const iterator >= > != failed!");
				++nRet;
			}
			if(cit_b <= cit || cit_b < cit || cit_b == cit)
			{
				GTLINE2("AVL const iterator <= < == failed!");
				++nRet;
			}
			if((it + 10) - avl.front_it() != 10)
			{
				GTLINE2("AVL iterator operator + or - failed!");
				++nRet;
			}
			if((cit + 10) - avl.const_front_it() != 10)
			{
				GTLINE2("AVL const iterator operator + or - failed!");
				++nRet;
			}
			if(avl.back_it() - (it_b - 10) != 10)
			{
				GTLINE2("AVL iterator operator - failed!");
				++nRet;
			}
			if(avl.const_back_it() - (cit_b - 10) != 10)
			{
				GTLINE2("AVL const iterator operator - failed!");
				++nRet;
			}
		}
		if(avl > avl1 || avl < avl1 || avl != avl1)
		{
			GTLINE2("Same avltree compare > < != failed!");
			++nRet;
		}
		if(!(avl >= avl1 && avl <= avl1 && avl == avl1))
		{
			GTLINE2("Same avltree compare !(>= <= ==) failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
