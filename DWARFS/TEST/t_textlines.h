#ifndef		__T_TEXTLINES_H__
#define		__T_TEXTLINES_H__

namespace DWARFSTEST
{
	GINL GAIA::N32 t_textlines(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

static const GAIA::GCH FILECONTENT[] = "\
#include <iostream>\r\n\
using namespace std;\r\n\
int main(int argc, char* argv[])\r\n\
{\r\n\
	cout << \"HelloWorld\" << endl;\r\n\
	return 0;\r\n\
}";
		static const GAIA::GCH TESTFILENAME[] = "textlines.txt";
		static const GAIA::GCH TESTFILENAMEDST[] = "textlines1.txt";
		GAIA::FILESYSTEM::File tfile;
		if(!tfile.Open(TESTFILENAME, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
		{
			GTLINE2("Create textlines source file failed!");
			++nRet;
		}
		if(tfile.Write(FILECONTENT, sizeof(FILECONTENT) - 1) != sizeof(FILECONTENT) - 1)
		{
			GTLINE2("Write textlines source file failed!");
			++nRet;
		}
		tfile.Close();
		DWARFS_MISC::TextLines tl;
		tl.lineflag("\r\n");
		if(tl.size() != 0)
		{
			GTLINE2("New textlines's size not zero!");
			++nRet;
		}
		if(!tfile.Open(TESTFILENAME, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
		{
			GTLINE2("Open textlines source file failed!");
			++nRet;
		}
		if(!tl.load(&tfile))
		{
			GTLINE2("TextLines load failed!");
			++nRet;
		}
		tfile.Close();
		for(GAIA::SIZE x = 0; x < tl.size(); ++x)
		{
			const GAIA::GCH* p = tl.get_line(x);
			if(p == GNULL)
			{
				GTLINE2("TextLines load cause get_line failed!");
				++nRet;
				break;
			}
			if(	x == 0 && GAIA::ALGORITHM::strcmp(p, "#include <iostream>\r\n") != 0 || 
				x == 1 && GAIA::ALGORITHM::strcmp(p, "using namespace std;\r\n") != 0 || 
				x == 2 && GAIA::ALGORITHM::strcmp(p, "int main(int argc, char* argv[])\r\n") != 0 || 
				x == 3 && GAIA::ALGORITHM::strcmp(p, "{\r\n") != 0 || 
				x == 4 && GAIA::ALGORITHM::strcmp(p, "	cout << \"HelloWorld\" << endl;\r\n") != 0 || 
				x == 5 && GAIA::ALGORITHM::strcmp(p, "	return 0;\r\n") != 0 || 
				x == 6 && GAIA::ALGORITHM::strcmp(p, "}\r\n") != 0)
			{
				GTLINE2("TextLine content error!");
				++nRet;
				break;
			}
		}
		const GAIA::GCH* szNew[] = {"// TEST COMPLETE!\r\n", "// END.\r\n"};
		tl.insert_lines(7, (const GAIA::GCH**)&szNew, 2);
		tl.erase_lines(0, 1);
		tfile.Open(TESTFILENAMEDST, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE);
		if(!tl.save(&tfile))
		{
			GTLINE2("TextLines save failed!");
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
