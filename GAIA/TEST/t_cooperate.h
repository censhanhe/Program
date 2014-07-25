#ifndef		__T_COOPERATE_H__
#define		__T_COOPERATE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_cooperate(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		// Chars string cooperate.
		{
			typedef GAIA::CONTAINER::BasicChars<GAIA::CH, GAIA::N8, 64> __CharsType;
			typedef GAIA::CONTAINER::BasicString<GAIA::CH, GAIA::N32> __StringType;

			__CharsType chs = "Hello";
			__StringType str = "World";
			chs = str;
			if(chs != "World")
			{
				GTLINE2("Chars operator = string failed!");
				++nRet;
			}
			chs.clear();
			chs = str;
			if(chs != "World")
			{
				GTLINE2("Chars operator = string failed!");
				++nRet;
			}
			chs = "Hello";
			str = chs;
			if(str != "Hello")
			{
				GTLINE2("String operator = chars failed!");
				++nRet;
			}
			str.destroy();
			str = chs;
			if(str != "Hello")
			{
				GTLINE2("String operator = chars failed!");
				++nRet;
			}
			chs = "Hello";
			str = "World";
			chs += str;
			if(chs != "HelloWorld")
			{
				GTLINE2("Chars += string failed!");
				++nRet;
			}
			chs = "World";
			str = "Hello";
			str += chs;
			if(str != "HelloWorld")
			{
				GTLINE2("String += chars failed!");
				++nRet;
			}
			chs = "Hello";
			str = "World";
			__CharsType chs_res = chs + str;
			if(chs_res != "HelloWorld")
			{
				GTLINE2("Chars + string failed!");
				++nRet;
			}
			str = "Hello";
			chs = "World";
			__StringType str_res = str + chs;
			if(str_res != "HelloWorld")
			{
				GTLINE2("String + chars failed!");
				++nRet;
			}
		}

		return nRet = 0;
	}
};

#endif
