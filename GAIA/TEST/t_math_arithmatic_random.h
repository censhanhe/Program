#ifndef		__T_MATH_ARITHMATIC_RANDOM_H__
#define		__T_MATH_ARITHMATIC_RANDOM_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_math_arithmatic_random(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		static const GAIA::SIZE SAMPLE_COUNT = 100;

		GAIA::N32 nRet = 0;
		GAIA::CTN::Vector<GAIA::SIZE> listRandom;

		GAIA::MATH::xrandom_seed(0);
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
			listRandom.push_back(GAIA::MATH::xrandom());
		GAIA::MATH::xrandom_seed(0);
		for(GAIA::SIZE x = 0; x < SAMPLE_COUNT; ++x)
		{
			if(GAIA::MATH::xrandom() != listRandom[x])
			{
				GTLINE2("Random seed error!");
				++nRet;
				break;
			}
		}
		listRandom.sort();
		GAIA::SIZE sDropCount = listRandom.unique();
		if(sDropCount + 1 >= SAMPLE_COUNT)
		{
			GTLINE2("Random value error!");
			++nRet;
		}

		return nRet;
	}
};

#endif