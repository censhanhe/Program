#ifndef		__T_FILESYSTEM_FILE_H__
#define		__T_FILESYSTEM_FILE_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_filesystem_file(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::FSYS::File __FileType;
		typedef GAIA::FSYS::Directory __DirType;

		static const GAIA::TCH TEST_FILE_NAME[] = _T("../TESTRES/filetest.txt");

		__DirType dir;
		__FileType tfile;
		if(!tfile.Open(TEST_FILE_NAME, __FileType::OPEN_TYPE_WRITE | __FileType::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.IsOpen())
		{
			GTLINE2("IsOpen error!");
			++nRet;
		}
		if(tfile.Size() != 0)
		{
			GTLINE2("File size error!");
			++nRet;
		}
		if(!dir.ExistFile(TEST_FILE_NAME))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.Close())
		{
			GTLINE2("Close file failed!");
			++nRet;
		}
		if(!dir.ExistFile(TEST_FILE_NAME))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.Open(TEST_FILE_NAME, __FileType::OPEN_TYPE_READ))
		{
			GTLINE2("Open exist empty file failed!");
			++nRet;
		}
		if(!tfile.IsOpen())
		{
			GTLINE2("IsOpen error!");
			++nRet;
		}
		if(tfile.Size() != 0)
		{
			GTLINE2("File size error!");
			++nRet;
		}
		if(!dir.ExistFile(TEST_FILE_NAME))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.Close())
		{
			GTLINE2("Close exist empty file failed!");
			++nRet;
		}
		if(!dir.ExistFile(TEST_FILE_NAME))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.Open(TEST_FILE_NAME, __FileType::OPEN_TYPE_WRITE | __FileType::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Create new file failed!");
			++nRet;
		}
		if(!tfile.IsOpen())
		{
			GTLINE2("IsOpen error!");
			++nRet;
		}
		if(tfile.Write("Hello World", GAIA::ALGO::strlen("Hello World")) != GAIA::ALGO::strlen("Hello World"))
		{
			GTLINE2("Write file failed!");
			++nRet;
		}
		if(tfile.Size() != GAIA::ALGO::strlen("Hello World"))
		{
			GTLINE2("File size error!");
			++nRet;
		}
		GAIA::U32 uData = 123456789;
		if(!tfile.Write(uData))
		{
			GTLINE2("Write file failed!");
			++nRet;
		}
		if(tfile.Size() != (GAIA::FSYS::File::__FileSizeType)(GAIA::ALGO::strlen("Hello World") + sizeof(uData)))
		{
			GTLINE2("File size error!");
			++nRet;
		}
		if(!tfile.WriteText("Hello Kitty"))
		{
			GTLINE2("Write file failed!");
			++nRet;
		}
		if(tfile.Size() != (GAIA::FSYS::File::__FileSizeType)(GAIA::ALGO::strlen("Hello World") + sizeof(uData) + GAIA::ALGO::strlen("Hello Kitty")))
		{
			GTLINE2("File size error!");
			++nRet;
		}
		if(!tfile.Close())
		{
			GTLINE2("Close file failed!");
			++nRet;
		}
		if(!tfile.Open(TEST_FILE_NAME, __FileType::OPEN_TYPE_READ))
		{
			GTLINE2("Open file for read failed!");
			++nRet;
		}
		if(!tfile.IsOpen())
		{
			GTLINE2("IsOpen error!");
			++nRet;
		}
		if(tfile.Size() != (GAIA::FSYS::File::__FileSizeType)(GAIA::ALGO::strlen("Hello World") + sizeof(uData) + GAIA::ALGO::strlen("Hello Kitty")))
		{
			GTLINE2("File size error!");
			++nRet;
		}
		GAIA::CH szText[128];
		if(tfile.Read(szText, GAIA::ALGO::strlen("Hello World")) != GAIA::ALGO::strlen("Hello World"))
		{
			GTLINE2("Read file content failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szText, "Hello World", GAIA::ALGO::strlen("Hello World")) != 0)
		{
			GTLINE2("Read file content failed!");
			++nRet;			
		}
		uData = 0;
		if(!tfile.Read(uData))
		{
			GTLINE2("Read file content failed!");
			++nRet;
		}
		if(uData != 123456789)
		{
			GTLINE2("Read file content failed!");
			++nRet;
		}
		if(tfile.Read(szText, GAIA::ALGO::strlen("Hello Kitty")) != GAIA::ALGO::strlen("Hello Kitty"))
		{
			GTLINE2("Read file content failed!");
			++nRet;
		}
		if(GAIA::ALGO::strcmp(szText, "Hello Kitty", GAIA::ALGO::strlen("Hello Kitty")) != 0)
		{
			GTLINE2("Read file content failed!");
			++nRet;			
		}
		if(!tfile.Close())
		{
			GTLINE2("Close file failed!");
			++nRet;
		}
		if(!dir.RemoveFile(TEST_FILE_NAME))
		{
			GTLINE2("Remove file failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif