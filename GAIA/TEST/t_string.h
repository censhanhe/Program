#ifndef		__T_STRING_H__
#define		__T_STRING_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_string(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::AString __AStrType;
		__AStrType str;
		str = "Hello World!";
		if(str != "Hello World!")
		{
			GTLINE2("String move or operator != error!");
			++nRet;
		}
		__AStrType str1 = str;
		if(str != str1)
		{
			GTLINE2("String copy construct error!");
			++nRet;
		}
		str = (GAIA::NM)123456789;
		if(str != "123456789")
		{
			GTLINE2("String construct from GAIA::NM failed!");
			++nRet;
		}
		str = (GAIA::UM)123456789;
		if(str != "123456789")
		{
			GTLINE2("String construct from GAIA::UM failed!");
			++nRet;
		}
		str = (GAIA::N8)123;
		if(str != "123")
		{
			GTLINE2("String construct from GAIA::N8 failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif