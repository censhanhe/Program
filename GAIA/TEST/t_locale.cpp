#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_locale(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		GAIA::WCH wszEnglishSrc[1024] = L"Hello World";
		GAIA::CH szEnglishDst[1024];

		/* ASCII coding. */
		GAIA::SIZE sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_ASCII) != sLen)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_ASCII) != sLen)
		{
			GTLINE2("Locale convert from ansi multi bytes to wide char failed!");
			++nRet;
		}

		/* System coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_SYS) != sLen)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_SYS) != sLen)
		{
			GTLINE2("Locale convert from sys multi bytes to wide char failed!");
			++nRet;
		}

		/* UTF7 coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF7) != sLen)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF7) != sLen)
		{
			GTLINE2("Locale convert from utf7 multi bytes to wide char failed!");
			++nRet;
		}

		/* UTF8 coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF8) != sLen)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF8) != sLen)
		{
			GTLINE2("Locale convert from utf8 multi bytes to wide char failed!");
			++nRet;
		}

		/* ASCII coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"你好，世界！");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_ASCII) != sLen)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, L"你好，世界！") == 0)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_ASCII) != sLen)
		{
			GTLINE2("Locale convert from ansi multi bytes to wide char failed!");
			++nRet;
		}

		/* System coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"你好，世界！");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_SYS) == 0)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_SYS) != sLen)
		{
			GTLINE2("Locale convert from sys multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(wszEnglishSrc, L"你好，世界！") != 0)
		{
			GTLINE2("Locale convert back from sys multi bytes failed!");
			++nRet;
		}

		/* UTF7 coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"你好，世界！");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF7) == 0)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF7) != sLen)
		{
			GTLINE2("Locale convert from utf7 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(wszEnglishSrc, L"你好，世界！") != 0)
		{
			GTLINE2("Locale convert back from utf7 multi bytes bytes failed!");
			++nRet;
		}

		/* UTF8 coding. */
		GAIA::ALGO::strcpy(wszEnglishSrc, L"你好，世界！");
		sLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF8) == 0)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF8) != sLen)
		{
			GTLINE2("Locale convert from utf8 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(wszEnglishSrc, L"你好，世界！") != 0)
		{
			GTLINE2("Locale convert back from utf8 multi bytes failed!");
			++nRet;
		}

		return nRet;
	}
};
