#ifndef		__T_TRIETREE_H__
#define		__T_TRIETREE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_trietree(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::BasicTrieTree<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __TrieType;
		__TrieType t;
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
		t.clear();
		t.destroy();
		return nRet;
	}
};

#endif