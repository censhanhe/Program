#ifndef		__T_STRING_H__
#define		__T_STRING_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_string(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::AString __AStrType;
		__AStrType str;
		if(!str.empty())
		{
			GTLINE2("New string is not empty!");
			++nRet;
		}
		str.destroy(); // Try to destroy new string.
		str = "Hello World!";
		if(str.empty())
		{
			GTLINE2("String initialized but empty!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World!"))
		{
			GTLINE2("String length error!");
			++nRet;
		}
		if(str.capacity() < str.size())
		{
			GTLINE2("String capacity below size!");
			++nRet;
		}
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
		str = (GAIA::N8)-123;
		if(str != "-123")
		{
			GTLINE2("String construct from GAIA::N8 failed!");
			++nRet;
		}
		str = (GAIA::U8)123;
		if(str != "123")
		{
			GTLINE2("String construct from GAIA::U8 failed!");
			++nRet;
		}
		str = (GAIA::N16)-12345;
		if(str != "-12345")
		{
			GTLINE2("String construct from GAIA::N16 failed!");
			++nRet;
		}
		str = (GAIA::U16)12345;
		if(str != "12345")
		{
			GTLINE2("String construct from GAIA::U16 failed!");
			++nRet;
		}
		str = (GAIA::N32)-123456789;
		if(str != "-123456789")
		{
			GTLINE2("String construct from GAIA::N32 failed!");
			++nRet;
		}
		str = (GAIA::U32)123456789;
		if(str != "123456789")
		{
			GTLINE2("String construct from GAIA::U32 failed!");
			++nRet;
		}
		str = (GAIA::N64)-123456789123456789;
		if(str != "-123456789123456789")
		{
			GTLINE2("String construct from GAIA::N64 failed!");
			++nRet;
		}
		str = (GAIA::U64)123456789123456789;
		if(str != "123456789123456789")
		{
			GTLINE2("String construct from GAIA::U64 failed!");
			++nRet;
		}
		str = (GAIA::F32)1234.567F;
		str.resize(8);
		if(str != "1234.567")
		{
			GTLINE2("String construct from GAIA::F32 failed!");
			++nRet;
		}
		str = (GAIA::F64)-1234567.12345;
		str.resize(14);
		if(str != "-1234567.12345")
		{
			GTLINE2("String construct from GAIA::F64 failed!");
			++nRet;
		}
		str = (GAIA::BL)GAIA::True;
		if(str != "1")
		{
			GTLINE2("String construct from GAIA::BL(GAIA::True) failed!");
			++nRet;
		}
		str = (GAIA::BL)GAIA::False;
		if(str != "0")
		{
			GTLINE2("String construct from GAIA::BL(GAIA::False) failed!");
			++nRet;
		}

		str = "HelloWorld" + str;
		return nRet;
	}
};

#endif