#ifndef		__T_TIME_TIME_H__
#define		__T_TIME_TIME_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_time_time(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::TIME::Time t, t1;
		t.reset();
		if(t.check())
		{
			GTLINE2("Time check failed!");
			++nRet;
		}
		t1 = t;
		if(t1.check())
		{
			GTLINE2("Time check failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif