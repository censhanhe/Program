#ifndef		__T_TREE_H__
#define		__T_TREE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_tree(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

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

		return nRet;
	}
};

#endif