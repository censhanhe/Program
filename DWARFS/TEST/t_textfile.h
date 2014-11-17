#ifndef		__T_TEXTFILE_H__
#define		__T_TEXTFILE_H__

namespace DWARFSTEST
{
	GINL GAIA::N32 t_textfile(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::FSYS::File textfileori;
		DWARFS_MISC::TextFile textfile;

		/* Ansi file test. */
		if(!textfileori.Open(_T("../TESTRES/ansi.cpp"), GAIA::FSYS::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open ansi.cpp failed!");
			++nRet;
		}
		if(!textfile.load(textfileori))
		{
			GTLINE2("Load ansi.cpp failed!");
			++nRet;
		}
		if(textfile.charset_type() != GAIA::CHARSET_TYPE_ASCII)
		{
			GTLINE2("File ansi charset error!");
			++nRet;
		}
		if(!textfileori.Open(_T("../TESTRES/ansi.cpp"), GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Open ansi.cpp failed!");
			++nRet;
		}
		if(!textfile.save(textfileori))
		{
			GTLINE2("Save ansi.cpp failed!");
			++nRet;
		}
		textfile.clear();

		/* Sys file test. */
		if(!textfileori.Open(_T("../TESTRES/sys.cpp"), GAIA::FSYS::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open sys.cpp failed!");
			++nRet;
		}
		if(!textfile.load(textfileori))
		{
			GTLINE2("Load sys.cpp failed!");
			++nRet;
		}
		if(textfile.charset_type() != GAIA::CHARSET_TYPE_SYS)
		{
			GTLINE2("File sys charset error!");
			++nRet;
		}
		if(!textfileori.Open(_T("../TESTRES/sys.cpp"), GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Open sys.cpp failed!");
			++nRet;
		}
		if(!textfile.save(textfileori))
		{
			GTLINE2("Save sys.cpp failed!");
			++nRet;
		}
		textfile.clear();

		/* UTF8 file test. */
		if(!textfileori.Open(_T("../TESTRES/utf8.cpp"), GAIA::FSYS::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open utf8.cpp failed!");
			++nRet;
		}
		if(!textfile.load(textfileori))
		{
			GTLINE2("Load utf8.cpp failed!");
			++nRet;
		}
		if(textfile.charset_type() != GAIA::CHARSET_TYPE_UTF8)
		{
			GTLINE2("File utf8 charset error!");
			++nRet;
		}
		if(!textfileori.Open(_T("../TESTRES/utf8.cpp"), GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Open utf8.cpp failed!");
			++nRet;
		}
		if(!textfile.save(textfileori))
		{
			GTLINE2("Save utf8.cpp failed!");
			++nRet;
		}
		textfile.clear();

		/* utf16le file test. */
		if(!textfileori.Open(_T("../TESTRES/utf16le.cpp"), GAIA::FSYS::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open utf16le.cpp failed!");
			++nRet;
		}
		if(!textfile.load(textfileori))
		{
			GTLINE2("Load utf16le.cpp failed!");
			++nRet;
		}
		if(textfile.charset_type() != GAIA::CHARSET_TYPE_UTF16LE)
		{
			GTLINE2("File utf16le charset error!");
			++nRet;
		}
		if(!textfileori.Open(_T("../TESTRES/utf16le.cpp"), GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Open utf16le.cpp failed!");
			++nRet;
		}
		if(!textfile.save(textfileori))
		{
			GTLINE2("Save utf16le.cpp failed!");
			++nRet;
		}
		textfile.clear();

		/* utf16be file test. */
		if(!textfileori.Open(_T("../TESTRES/utf16be.cpp"), GAIA::FSYS::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open utf16be.cpp failed!");
			++nRet;
		}
		if(!textfile.load(textfileori))
		{
			GTLINE2("Load utf16be.cpp failed!");
			++nRet;
		}
		if(textfile.charset_type() != GAIA::CHARSET_TYPE_UTF16BE)
		{
			GTLINE2("File utf16be charset error!");
			++nRet;
		}
		if(!textfileori.Open(_T("../TESTRES/utf16be.cpp"), GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Open utf16be.cpp failed!");
			++nRet;
		}
		if(!textfile.save(textfileori))
		{
			GTLINE2("Save utf16be.cpp failed!");
			++nRet;
		}
		textfile.clear();

		return nRet;
	}
};

#endif
