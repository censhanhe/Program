#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_cooperate(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		// Chars string cooperate.
		{
			typedef GAIA::CTN::BasicChars<GAIA::TCH, GAIA::N8, 64> __CharsType;
			typedef GAIA::CTN::BasicString<GAIA::TCH, GAIA::N32> __StringType;

			__CharsType chs = _T("Hello");
			__StringType str = _T("World");
			chs = str;
			if(chs != _T("World"))
			{
				GTLINE2("Chars operator = string failed!");
				++nRet;
			}
			chs.clear();
			chs = str;
			if(chs != _T("World"))
			{
				GTLINE2("Chars operator = string failed!");
				++nRet;
			}
			chs = _T("Hello");
			str = chs;
			if(str != _T("Hello"))
			{
				GTLINE2("String operator = chars failed!");
				++nRet;
			}
			str.destroy();
			str = chs;
			if(str != _T("Hello"))
			{
				GTLINE2("String operator = chars failed!");
				++nRet;
			}
			chs = _T("Hello");
			str = _T("World");
			chs += str;
			if(chs != _T("HelloWorld"))
			{
				GTLINE2("Chars += string failed!");
				++nRet;
			}
			chs = _T("World");
			str = _T("Hello");
			str += chs;
			if(str != _T("HelloWorld"))
			{
				GTLINE2("String += chars failed!");
				++nRet;
			}
			chs = _T("Hello");
			str = _T("World");
			__CharsType chs_res = chs + str;
			if(chs_res != _T("HelloWorld"))
			{
				GTLINE2("Chars + string failed!");
				++nRet;
			}
			str = _T("Hello");
			chs = _T("World");
			__StringType str_res = str + chs;
			if(str_res != _T("HelloWorld"))
			{
				GTLINE2("String + chars failed!");
				++nRet;
			}
		}

		return nRet;
	}
};
