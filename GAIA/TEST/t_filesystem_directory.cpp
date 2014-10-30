#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_filesystem_directory(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::FSYS::File __FileType;
		typedef GAIA::FSYS::Directory __DirType;

		__FileType tfile;
		__DirType dir;

		static const GAIA::TCH TEST_DIR[] = _T("../TESTRES/TESTDIR/");
		static const GAIA::TCH TEST_DIR_CHILD[] = _T("../TESTRES/TestDir/ChildDir/");
		static const GAIA::TCH TEST_DIR_CHILD_CHILD[] = _T("../TESTRES/TestDir/ChildDir/ChildChildDir/");

		if(!dir.Create(TEST_DIR, GAIA::False))
		{
			GTLINE2("Create dir failed!");
			++nRet;
		}
		if(!dir.Exist(TEST_DIR))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Remove(TEST_DIR, GAIA::False))
		{
			GTLINE2("Remove dir failed!");
			++nRet;
		}
		if(dir.Exist(TEST_DIR))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Create(TEST_DIR_CHILD_CHILD, GAIA::True))
		{
			GTLINE2("Create dir failed!");
			++nRet;
		}
		if(!dir.Exist(TEST_DIR_CHILD_CHILD))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Exist(TEST_DIR_CHILD))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Exist(TEST_DIR))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Remove(TEST_DIR_CHILD_CHILD, GAIA::False))
		{
			GTLINE2("Remove dir failed!");
			++nRet;
		}
		if(dir.Exist(TEST_DIR_CHILD_CHILD))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Remove(TEST_DIR_CHILD, GAIA::False))
		{
			GTLINE2("Remove dir failed!");
			++nRet;
		}
		if(dir.Exist(TEST_DIR_CHILD))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Remove(TEST_DIR, GAIA::False))
		{
			GTLINE2("Remove dir failed!");
			++nRet;
		}
		if(dir.Exist(TEST_DIR))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		if(!dir.Create(TEST_DIR_CHILD_CHILD, GAIA::True))
		{
			GTLINE2("Create dir failed!");
			++nRet;
		}
		if(!dir.Remove(TEST_DIR, GAIA::True))
		{
			GTLINE2("Remove dir failed!");
			++nRet;
		}
		if(dir.Exist(TEST_DIR))
		{
			GTLINE2("Exist dir failed!");
			++nRet;
		}
		return nRet;
	}
};
