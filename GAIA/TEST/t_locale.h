#ifndef		__T_LOCALE_H__
#define		__T_LOCALE_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_locale(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::WCH wszEnglishSrc[1024] = L"Hello World";
		GAIA::CH szEnglishDst[1024];
		GAIA::SIZE uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale calculate size from ansi multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale convert from ansi multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale calculate size from sys multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale convert from sys multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale calculate size from utf7 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale convert from utf7 multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Hello World");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, "Hello World") != 0)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale calculate size from utf8 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale convert from utf8 multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Kutal antik ahlak kalesi(muhteşem ışıl ışıl parlayan gökemli kılıç)");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szEnglishDst, L"Kutal antik ahlak kalesi(muhteşem ışıl ışıl parlayan gökemli kılıç)") == 0)
		{
			GTLINE2("Locale convert from wide char to ansi multi bytes cause content error!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale calculate size from ansi multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_ANSI) != uStringLen)
		{
			GTLINE2("Locale convert from ansi multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Kutal antik ahlak kalesi(muhteşem ışıl ışıl parlayan gökemli kılıç)");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale calculate size from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale convert from wide char to sys multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale calculate size from sys multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_SYS) != uStringLen)
		{
			GTLINE2("Locale convert from sys multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Kutal antik ahlak kalesi(muhteşem ışıl ışıl parlayan gökemli kılıç)");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_UTF7) == 0)
		{
			GTLINE2("Locale calculate size from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF7) == 0)
		{
			GTLINE2("Locale convert from wide char to utf7 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale calculate size from utf7 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF7) != uStringLen)
		{
			GTLINE2("Locale convert from utf7 multi bytes to wide char failed!");
			++nRet;
		}

		GAIA::ALGO::strcpy(wszEnglishSrc, L"Kutal antik ahlak kalesi(muhteşem ışıl ışıl parlayan gökemli kılıç)");
		uStringLen = GAIA::ALGO::strlen(wszEnglishSrc) + 1;
		if(GAIA::LOCALE::w2m(wszEnglishSrc, GNIL, 0, GAIA::CHARSET_TYPE_UTF8) == 0)
		{
			GTLINE2("Locale calculate size from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::w2m(wszEnglishSrc, szEnglishDst, 1024, GAIA::CHARSET_TYPE_UTF8) == 0)
		{
			GTLINE2("Locale convert from wide char to utf8 multi bytes failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, GNIL, 0, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale calculate size from utf8 multi bytes to wide char failed!");
			++nRet;
		}
		if(GAIA::LOCALE::m2w(szEnglishDst, wszEnglishSrc, 1024, GAIA::CHARSET_TYPE_UTF8) != uStringLen)
		{
			GTLINE2("Locale convert from utf8 multi bytes to wide char failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif
