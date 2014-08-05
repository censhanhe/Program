#ifndef		__T_CONTAINER_TREE_H__
#define		__T_CONTAINER_TREE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_tree(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		static const GAIA::N32 ELEMENT_COUNT = 10;
		typedef GAIA::CONTAINER::BasicTree<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __TreeType;
		__TreeType tr;
		if(!tr.empty())
		{
			GTLINE2("New tree is not empty!");
			++nRet;
		}
		if(tr.size() != 0)
		{
			GTLINE2("New tree size is not zero!");
			++nRet;
		}
		if(tr.capacity() != 0)
		{
			GTLINE2("New tree capacity is not zero!");
			++nRet;
		}
		if(tr.root() != GNULL)
		{
			GTLINE2("New tree root is not GNULL!");
			++nRet;
		}
		if(static_cast<__TreeType*>(&tr)->root() != GNULL)
		{
			GTLINE2("New tree const root is not NULL!");
			++nRet;
		}
		__TreeType::it newit;
		__TreeType::const_it newcit;
		newit = tr.front_it();
		if(!newit.empty())
		{
			GTLINE2("New tree front_it is not empty!");
			++nRet;
		}
		newit = tr.back_it();
		if(!newit.empty())
		{
			GTLINE2("New tree back_it is not empty!");
			++nRet;
		}
		newcit = tr.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New tree const_front_it is not empty!");
			++nRet;
		}
		newcit = tr.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New tree const_back_it is not empty!");
			++nRet;
		}
		if(tr.insert(123, GNULL) == GNULL)
		{
			GTLINE2("Tree insert root failed!");
			++nRet;
		}
		if(tr.insert(321, GNULL) != GNULL)
		{
			GTLINE2("Tree insert root twice failed!");
			++nRet;
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			__TreeType::Node* pNode = tr.insert(x, tr.root());
			if(pNode == GNULL)
			{
				GTLINE2("Tree insert child node failed!");
				++nRet;
				break;
			}
			GAIA::BL bFailed = GAIA::False;
			for(GAIA::N32 y = 0; y < ELEMENT_COUNT; ++y)
			{
				__TreeType::Node* pChild = tr.insert(x + y, pNode);
				if(pChild == GNULL)
				{
					GTLINE2("Tree insert child child node failed!");
					++nRet;
					bFailed = GAIA::True;
					break;
				}
				GAIA::BL bFailedFailed = GAIA::False;
				for(GAIA::N32 z = 0; z < ELEMENT_COUNT; ++z)
				{
					__TreeType::Node* pChildChild = tr.insert(x + y + z, pChild);
					if(pChildChild == GNULL)
					{
						GTLINE2("Tree insert child child child node failed!");
						++nRet;
						bFailedFailed = GAIA::True;
						break;
					}
				}
				if(bFailedFailed)
				{
					bFailed = GAIA::True;
					break;
				}
			}
			if(bFailed)
				break;
		}
		__TreeType::_sizetype tTotalNodeCount = 1 + ELEMENT_COUNT + ELEMENT_COUNT * ELEMENT_COUNT + ELEMENT_COUNT * ELEMENT_COUNT * ELEMENT_COUNT;
		if(tr.size() != tTotalNodeCount)
		{
			GTLINE2("Tree insert failed! The node count is not match!");
			++nRet;
		}
		__TreeType::_sizetype tsize = 0;
		__TreeType::it it = tr.front_it();
		while(!it.empty())
		{
			++tsize;
			++it;
		}
		if(tsize != tTotalNodeCount)
		{
			GTLINE2("Tree front iterator can't scan all the elements!");
			++nRet;
		}
		tsize = 0;
		it = tr.back_it();
		while(!it.empty())
		{
			++tsize;
			--it;
		}
		if(tsize != tTotalNodeCount)
		{
			GTLINE2("Tree back iterator can't scan all the elements!");
			++nRet;
		}
		tsize = 0;
		__TreeType::const_it cit = tr.const_front_it();
		while(!cit.empty())
		{
			++tsize;
			++cit;
		}
		if(tsize != tTotalNodeCount)
		{
			GTLINE2("Tree const front iterator can't scan all the elements!");
			++nRet;
		}
		tsize = 0;
		cit = tr.const_back_it();
		while(!cit.empty())
		{
			++tsize;
			--cit;
		}
		if(tsize != tTotalNodeCount)
		{
			GTLINE2("Tree const back iterator can't scan all the elements!");
			++nRet;
		}
		if(tr.size() > tr.capacity())
		{
			GTLINE2("Tree capacity must above equal it's size!");
			++nRet;
		}
		__TreeType tr1 = tr;
		if(tr1.size() != tr.size() ||
			tr1.capacity() != tr.capacity() ||
			tr1.empty() != tr.empty())
		{
			GTLINE2("Tree copy construct failed!");
			++nRet;
		}
		it = tr.front_it();
		while(!it.empty())
		{
			__TreeType::it itnext = it;
			++itnext;
			__TreeType::Node* pNode = tr.tonode(it);
			GAIA_AST(pNode != GNULL);
			tr.erase(*pNode);
			if(tr.empty())
				break;
			it = itnext;
		}
		if(!tr.empty())
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.size() != 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.capacity() == 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		tr = tr1;
		it = tr.back_it();
		while(!it.empty())
		{
			__TreeType::it itprev = it;
			--itprev;
			__TreeType::Node* pNode = tr.tonode(it);
			GAIA_AST(pNode != GNULL);
			tr.erase(*pNode);
			if(tr.empty())
				break;
			it = itprev;
		}
		if(!tr.empty())
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.size() != 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.capacity() == 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		tr = tr1;
		tr.clear();
		tr.destroy();
		if(!tr.empty())
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.size() != 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		if(tr.capacity() != 0)
		{
			GTLINE2("Tree erase all element failed!");
			++nRet;
		}
		tr = tr1;
		tr1.clear();
		tr1.destroy();
		tr.clear();
		tr.destroy();
		__TreeType::_datatype tdata = 0;
		if(tr.insert(tdata++, GNULL) == GNULL)
		{
			GTLINE2("Tree insert root failed!");
			++nRet;
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			__TreeType::Node* pNode = tr.insert(tdata++, tr.root());
			if(pNode == GNULL)
			{
				GTLINE2("Tree insert child node failed!");
				++nRet;
				break;
			}
			GAIA::BL bFailed = GAIA::False;
			for(GAIA::N32 y = 0; y < ELEMENT_COUNT; ++y)
			{
				__TreeType::Node* pChild = tr.insert(tdata++, pNode);
				if(pChild == GNULL)
				{
					GTLINE2("Tree insert child child node failed!");
					++nRet;
					bFailed = GAIA::True;
					break;
				}
				GAIA::BL bFailedFailed = GAIA::False;
				for(GAIA::N32 z = 0; z < ELEMENT_COUNT; ++z)
				{
					__TreeType::Node* pChildChild = tr.insert(tdata++, pChild);
					if(pChildChild == GNULL)
					{
						GTLINE2("Tree insert child child child node failed!");
						++nRet;
						bFailedFailed = GAIA::True;
						break;
					}
				}
				if(bFailedFailed)
				{
					bFailed = GAIA::True;
					break;
				}
			}
			if(bFailed)
				break;
		}
		if(tr.size() != tTotalNodeCount)
		{
			GTLINE2("Tree insert failed! The node count is not match!");
			++nRet;
		}
		GAIA::CONTAINER::Vector<__TreeType::_datatype> listTemp;
		listTemp.reserve(tTotalNodeCount);
		it = tr.front_it();
		while(!it.empty())
		{
			listTemp.push_back(*it);
			++it;
		}
		if(!GAIA::ALGORITHM::issorted(listTemp.front_ptr(), listTemp.back_ptr()))
		{
			GTLINE2("Tree element data error!");
			++nRet;
		}
		GAIA::CONTAINER::Vector<__TreeType::_datatype>::it itback_v = listTemp.back_it();
		__TreeType::it itback = tr.back_it();
		while(!itback.empty())
		{
			if(*itback != *itback_v)
			{
				GTLINE2("Tree element data error!");
				++nRet;
				break;
			}
			--itback;
			--itback_v;
		}
		return nRet;
	}
};

#endif