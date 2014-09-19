#ifndef		__T_TEXTLINE_H__
#define		__T_TEXTLINE_H__

namespace DWARFSTEST
{
	GINL GAIA::N32 t_textline(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

static const GAIA::TCH FILECONTENT[] = _T("\
#include <iostream>\r\n\
using namespace std;\r\n\
int main(int argc, char* argv[])\r\n\
{\r\n\
	cout << \"HelloWorld\" << endl;\r\n\
	return 0;\r\n\
}");
		static const GAIA::TCH TESTFILENAME[] = _T("textline.txt");
		static const GAIA::TCH TESTFILENAMEDST[] = _T("textline1.txt");
		GAIA::FILESYSTEM::File tfile;
		if(!tfile.Open(TESTFILENAME, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
		{
			GTLINE2("Create textline source file failed!");
			++nRet;
		}
		tfile.Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
		if(tfile.Write(FILECONTENT, sizeof(FILECONTENT) - sizeof(FILECONTENT[0])) != sizeof(FILECONTENT) - sizeof(FILECONTENT[0]))
		{
			GTLINE2("Write textline source file failed!");
			++nRet;
		}
		tfile.Close();
		DWARFS_MISC::TextLine tl;
		tl.lineflag(_T("\r\n"));
		if(tl.size() != 0)
		{
			GTLINE2("New textline's size not zero!");
			++nRet;
		}
		if(!tfile.Open(TESTFILENAME, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open textline source file failed!");
			++nRet;
		}
		if(!tl.load(tfile))
		{
			GTLINE2("TextLine load failed!");
			++nRet;
		}
		tfile.Close();
		for(GAIA::SIZE x = 0; x < tl.size(); ++x)
		{
			const GAIA::TCH* p = tl.get_line(x);
			if(p == GNIL)
			{
				GTLINE2("TextLine load cause get_line failed!");
				++nRet;
				break;
			}
			if(	(x == 0 && GAIA::ALGO::strcmp(p, _T("#include <iostream>\r\n")) != 0) ||
				(x == 1 && GAIA::ALGO::strcmp(p, _T("using namespace std;\r\n")) != 0) ||
				(x == 2 && GAIA::ALGO::strcmp(p, _T("int main(int argc, char* argv[])\r\n")) != 0) ||
				(x == 3 && GAIA::ALGO::strcmp(p, _T("{\r\n")) != 0) ||
				(x == 4 && GAIA::ALGO::strcmp(p, _T("	cout << \"HelloWorld\" << endl;\r\n")) != 0) ||
				(x == 5 && GAIA::ALGO::strcmp(p, _T("	return 0;\r\n")) != 0) ||
				(x == 6 && GAIA::ALGO::strcmp(p, _T("}\r\n")) != 0))
			{
				GTLINE2("TextLine content error!");
				++nRet;
				break;
			}
		}
		const GAIA::TCH* szNew[] = {_T("// TEST COMPLETE!\r\n"), _T("// END.\r\n")};
		tl.insert_lines(7, (const GAIA::TCH**)&szNew, 2);
		tl.erase_lines(0, 1);
		tfile.Open(TESTFILENAMEDST, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE);
		if(!tl.save(tfile))
		{
			GTLINE2("TextLine save failed!");
			++nRet;
		}
		tfile.Close();
		GAIA::FILESYSTEM::Directory dir;
		dir.RemoveFile(TESTFILENAME);
		dir.RemoveFile(TESTFILENAMEDST);

		return nRet;
	}
};

#endif
