#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_trietree(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::BasicTrieTree<GAIA::N32, GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::U32> > __TrieType;
		static const GAIA::N32 COUNTX = 10;
		static const GAIA::N32 COUNTZ = 10;
		__TrieType::_datatype SAMPLES[COUNTZ][COUNTX];
		for(__TrieType::_datatype z = 0; z < COUNTZ; ++z)
			for(__TrieType::_datatype x = 0; x < COUNTX; ++x)
				SAMPLES[z][x] = z * COUNTX + x;
		__TrieType t;
		__TrieType::it it;
		__TrieType::const_it cit;
		if(!t.empty())
		{
			GTLINE2("New trie is not empty!");
			++nRet;
		}
		if(t.size())
		{
			GTLINE2("New trie size is not zero!");
			++nRet;
		}
		if(t.count(t.root()) != 0)
		{
			GTLINE2("Trie root's count not zero!");
			++nRet;
		}
		if(t.catagory_count(t.root()) != 0)
		{
			GTLINE2("Trie root's catagory_count not zero!");
			++nRet;
		}
		if(t.full_count(t.root()) != 0)
		{
			GTLINE2("Trie root's full_count not zero!");
			++nRet;
		}
		__TrieType::it newit;
		__TrieType::const_it newcit;
		newit = t.front_it();
		if(!newit.empty())
		{
			GTLINE2("New trietree front_it is not empty!");
			++nRet;
		}
		newit = t.back_it();
		if(!newit.empty())
		{
			GTLINE2("New trietree back_it is not empty!");
			++nRet;
		}
		newcit = t.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New trietree const_front_it is not empty!");
			++nRet;
		}
		newcit = t.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New trietree const_back_it is not empty!");
			++nRet;
		}
		t.clear();
		t.destroy();
		for(__TrieType::_datatype z = 0; z < COUNTZ; ++z)
			t.insert(SAMPLES[z], COUNTX);
		if(t.empty())
		{
			GTLINE2("Trie insert failed!");
			++nRet;
		}
		if(t.size() != COUNTX * COUNTZ)
		{
			GTLINE2("Trie insert failed!");
			++nRet;
		}
		it = t.front_it();
		__TrieType::_sizetype uCount = 0;
		for(; !it.empty(); ++it)
			++uCount;
		if(uCount != 100)
		{
			GTLINE2("Trie iterator operator ++ failed!");
			++nRet;
		}
		cit = t.const_front_it();
		uCount = 0;
		for(; !cit.empty(); ++cit)
			++uCount;
		if(uCount != 100)
		{
			GTLINE2("Trie const iterator operator ++ failed!");
			++nRet;
		}
		it = t.back_it();
		uCount = 0;
		for(; !it.empty(); --it)
			++uCount;
		if(uCount != 100)
		{
			GTLINE2("Trie iterator operator -- failed!");
			++nRet;
		}
		cit = t.const_back_it();
		uCount = 0;
		for(; !cit.empty(); --cit)
			++uCount;
		if(uCount != 100)
		{
			GTLINE2("Trie const iterator operator -- failed!");
			++nRet;
		}
		t.destroy();
		if(!t.empty())
		{
			GTLINE2("Trie destroy failed!");
			++nRet;
		}
		t.clear();
		if(!t.empty())
		{
			GTLINE2("Trie clear failed!");
			++nRet;
		}
		for(__TrieType::_datatype z = 0; z < COUNTZ; ++z)
			t.insert(SAMPLES[z], COUNTX);
		for(__TrieType::_datatype z = 0; z < COUNTZ; ++z)
		{
			if(!t.exist(SAMPLES[z], COUNTX))
			{
				GTLINE2("Trie exist failed!");
				++nRet;
				break;
			}

			if(!t.erase(SAMPLES[z], COUNTX))
			{
				GTLINE2("Trie erase failed!");
				++nRet;
				break;
			}
		}
		if(!t.empty())
		{
			GTLINE2("Trie erase cause empty failed!");
			++nRet;
		}
		if(t.size() != 0)
		{
			GTLINE2("Trie erase cause size failed!");
			++nRet;
		}
		t.clear();
		for(__TrieType::_datatype z = 0; z < COUNTZ; ++z)
			t.insert(SAMPLES[z], COUNTX);
		__TrieType::_sizetype uLeafCount = 0;
		it = t.front_it();
		for(; !it.empty(); ++it)
		{
			if(t.leaf(it))
				++uLeafCount;
		}
		if(uLeafCount != COUNTZ)
		{
			GTLINE2("Trie leaf count error!");
			++nRet;
		}
		uLeafCount = 0;
		cit = t.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			if(t.leaf(cit))
				++uLeafCount;
		}
		if(uLeafCount != COUNTZ)
		{
			GTLINE2("Trie leaf count error!");
			++nRet;
		}
		it = t.front_it();
		for(; !it.empty(); ++it)
		{
			if(t.root(it))
			{
				GTLINE2("Trie root a iterator failed!");
				++nRet;
				break;
			}
		}
		it = t.back_it();
		for(; !it.empty(); --it)
		{
			if(t.root(it))
			{
				GTLINE2("Trie root a iterator failed!");
				++nRet;
				break;
			}
		}
		it = t.front_it();
		for(; !it.empty(); ++it)
		{
			if(t.leaf(it))
			{
				__TrieType::it itt = it;
				__TrieType::_sizetype uParentTimes = 0;
				while(!itt.empty() && itt != t.root_it())
				{
					++uParentTimes;
					itt = t.parent_it(itt);
				}
				if(uParentTimes != COUNTX)
				{
					GTLINE2("Trie parent_it error!");
					++nRet;
					break;
				}
			}
		}
		cit = t.const_front_it();
		for(; !cit.empty(); ++cit)
		{
			if(t.leaf(cit))
			{
				__TrieType::const_it citt = cit;
				__TrieType::_sizetype uParentTimes = 0;
				while(!citt.empty() && citt != static_cast<const __TrieType*>(&t)->root_it())
				{
					++uParentTimes;
					citt = t.parent_it(citt);
				}
				if(uParentTimes != COUNTX)
				{
					GTLINE2("Trie parent_it error!");
					++nRet;
					break;
				}
			}
		}
		__TrieType t1 = t;
		if(!(t1 == t && t1 >= t && t1 <= t))
		{
			GTLINE2("Trie operator == >= <= failed!");
			++nRet;
		}
		if(t1 != t || t1 > t || t1 < t)
		{
			GTLINE2("Trie operator != > < failed!");
			++nRet;
		}
		it = t1.front_it();
		cit = t1.const_front_it();
		for(; !it.empty(); ++it, ++cit)
		{
			__TrieType::_datatype arr[COUNTX];
			__TrieType::_sizetype index = 0;
			__TrieType::it ittemp = it;
			while(!ittemp.empty() && it != t1.root_it())
			{
				arr[index++] = *ittemp;
				ittemp = t1.parent_it(ittemp);
			}
			if(index == 0)
			{
				GTLINE2("Trie iterator path to root failed!");
				++nRet;
				break;
			}
			GAIA::ALGO::inverse(arr, arr + index - 1);
			__TrieType::it itfind_l = t1.lower_bound(arr, index);
			__TrieType::const_it citfind_l = static_cast<const __TrieType*>(&t1)->lower_bound(arr, index);
			__TrieType::it itfind_u = t1.upper_bound(arr, index);
			__TrieType::const_it citfind_u = static_cast<const __TrieType*>(&t1)->upper_bound(arr, index);
			if(itfind_l != itfind_u || itfind_l != it)
			{
				GTLINE2("Trie lower_bound failed!");
				++nRet;
				break;
			}
			if(citfind_l != citfind_u || citfind_l != cit)
			{
				GTLINE2("Trie upper_bound failed!");
				++nRet;
				break;
			}
			index = 0;
			for(__TrieType::_datatype x = *it + 1; x < COUNTX; ++x)
				arr[index++] = x;
			if(index > 0)
			{
				__TrieType::Node* pFinded = t1.find(t1.tonode(it), arr, index);
				if(pFinded == GNIL)
				{
					GTLINE2("Trie find failed!");
					++nRet;
					break;
				}
				__TrieType::it itfind = t1.toit(*pFinded);
				if(itfind.empty())
				{
					GTLINE2("Trie find failed!");
					++nRet;
					break;
				}
				if(!t1.leaf(itfind))
				{
					GTLINE2("Trie find failed!");
					++nRet;
					break;
				}
			}
		}
		{
			__TrieType::it it = t1.front_it();
			__TrieType::const_it cit = t1.const_front_it();
			__TrieType::it it_b = t1.back_it();
			__TrieType::const_it cit_b = t1.const_back_it();
			if(!(it_b != it))
			{
				GTLINE2("Trie iterator >= > != failed!");
				++nRet;
			}
			if(it_b == it)
			{
				GTLINE2("Trie iterator <= < == failed!");
				++nRet;
			}
			if(!(cit_b != cit))
			{
				GTLINE2("Trie const iterator >= > != failed!");
				++nRet;
			}
			if(cit_b == cit)
			{
				GTLINE2("Trie const iterator <= < == failed!");
				++nRet;
			}
			if((it + 10) - t1.front_it() != 10)
			{
				GTLINE2("Trie iterator operator + or - failed!");
				++nRet;
			}
			if((cit + 10) - t1.const_front_it() != 10)
			{
				GTLINE2("Trie const iterator operator + or - failed!");
				++nRet;
			}
			if(t1.back_it() - (it_b - 10) != 10)
			{
				GTLINE2("Trie iterator operator - failed!");
				++nRet;
			}
			if(t1.const_back_it() - (cit_b - 10) != 10)
			{
				GTLINE2("Trie const iterator operator - failed!");
				++nRet;
			}
		}
		it = t1.front_it();
		cit = t1.const_front_it();
		for(__TrieType::_sizetype x = 0; x < t1.size(); ++x)
		{
			if(it.empty())
			{
				GTLINE2("Trie iterator ++ failed!");
				++nRet;
				break;
			}
			if(cit.empty())
			{
				GTLINE2("Trie const iterator ++ failed!");
				++nRet;
				break;
			}
			__TrieType::Node* pNode = t1.tonode(it);
			if(pNode == GNIL)
			{
				GTLINE2("Trie tonode failed!");
				++nRet;
				break;
			}
			__TrieType::it ittemp = t1.toit(*pNode);
			if(ittemp != it)
			{
				GTLINE2("Trie tonode or toit failed!");
				++nRet;
				break;
			}
			const __TrieType::Node* pConstNode = static_cast<const __TrieType*>(&t1)->tonode(cit);
			if(pConstNode == GNIL)
			{
				GTLINE2("Trie const tonode failed!");
				++nRet;
				break;
			}
			__TrieType::const_it cittemp = static_cast<const __TrieType*>(&t1)->toit(*pConstNode);
			if(cittemp != cit)
			{
				GTLINE2("Trie const tonode or toit failed!");
				++nRet;
				break;
			}
			if(t1.leaf(it))
			{
				if(t1.count(*pNode) != 1)
				{
					GTLINE2("Trie count calculate error!");
					++nRet;
					break;
				}
			}
			else
			{
				if(t1.count(*pNode) != 0)
				{
					GTLINE2("Trie count calculate error!");
					++nRet;
					break;
				}
			}
			if(t1.catagory_count(*pNode) != 1)
			{
				GTLINE2("Trie catagory_count error!");
				++nRet;
				break;
			}
			if(t1.full_count(*pNode) != 1)
			{
				GTLINE2("Trie full_count error!");
				++nRet;
				break;
			}
			if(!t1.leaf(cit))
			{
				if(t1.childsize(*pNode) != 1)
				{
					GTLINE2("Trie childsize failed!");
					++nRet;
					break;
				}
				__TrieType::__NodeTreeType::it c_itfront = t1.child_front_it(*pNode);
				if(c_itfront.empty())
				{
					GTLINE2("Trie child_const_front_it failed!");
					++nRet;
					break;
				}
				__TrieType::__NodeTreeType::it c_itback = t1.child_back_it(*pNode);
				if(c_itback.empty())
				{
					GTLINE2("Trie child_const_back_it failed");
					++nRet;
					break;
				}
				if(c_itfront != c_itback)
				{
					GTLINE2("Trie node child list error!");
					++nRet;
					break;
				}
				__TrieType::Node* pChildNodeFront = t1.tonode(c_itfront);
				__TrieType::Node* pChildNodeBack = t1.tonode(c_itback);
				if(pChildNodeFront == GNIL || pChildNodeFront != pChildNodeBack)
				{
					GTLINE2("Trie tonode by childlist iterator failed!");
					++nRet;
					break;
				}
				__TrieType::__NodeTreeType::const_it c_citfront = t1.child_const_front_it(*pNode);
				if(c_citfront.empty())
				{
					GTLINE2("Trie child_const_front_it failed!");
					++nRet;
					break;
				}
				__TrieType::__NodeTreeType::const_it c_citback = t1.child_const_back_it(*pNode);
				if(c_citback.empty())
				{
					GTLINE2("Trie child_const_back_it failed");
					++nRet;
					break;
				}
				if(c_citfront != c_citback)
				{
					GTLINE2("Trie node child list error!");
					++nRet;
					break;
				}
				const __TrieType::Node* pConstChildNodeFront = t1.tonode(c_citfront);
				const __TrieType::Node* pConstChildNodeBack = t1.tonode(c_citback);
				if(pConstChildNodeFront == GNIL || pConstChildNodeFront != pConstChildNodeBack)
				{
					GTLINE2("Trie tonode by childlist const iterator failed!");
					++nRet;
					break;
				}
			}
			++it;
			++cit;
		}
		return nRet;
	}
};
