#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 tp_compiler(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		GAIA::STREAM::StringStream s;

		s << "[TYPE SIZE]\n";
		s << "bool size = " << sizeof(bool) << "\r\n";
		s << "char size = " << sizeof(char) << "\r\n";
		s << "wchar_t size = " << sizeof(wchar_t) << "\r\n";
		s << "short size = " << sizeof(short) << "\r\n";
		s << "int size = " << sizeof(int) << "\r\n";
		s << "long size = " << sizeof(long) << "\r\n";
		s << "long int size = " << sizeof(long int) << "\r\n";
		s << "long long int size = " << sizeof(long long int) << "\r\n";
		s << "float size = " << sizeof(float) << "\r\n";
		s << "double size = " << sizeof(double) << "\r\n";
		s << "size_t size = " << sizeof(size_t) << "\r\n";

		s << "\r\n[TYPE NAME]\r\n";
		s << "bool type name = " << typeid(bool).name() << "\r\n";
		s << "char type name = " << typeid(char).name() << "\r\n";
		s << "wchar_t type name = " << typeid(wchar_t).name() << "\r\n";
		s << "short type name = " << typeid(short).name() << "\r\n";
		s << "int type name = " << typeid(int).name() << "\r\n";
		s << "long type name = " << typeid(long).name() << "\r\n";
		s << "long int type name = " << typeid(long int).name() << "\r\n";
		s << "long long int type name = " << typeid(long long int).name() << "\r\n";
		s << "float type name = " << typeid(float).name() << "\r\n";
		s << "double type name = " << typeid(double).name() << "\r\n";
		s << "size_t type name = " << typeid(size_t).name() << "\r\n";

		GAIA::FSYS::File f;
		static const GAIA::TCH* FILENAME = _T("../TESTRES/compilerinfo.txt");
		if(!f.Open(FILENAME, GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
		{
			GTLINE2("Compiler : open file failed!\n");
			++nRet;
			return nRet;
		}
		f.WriteText(s.GetString());
		f.Close();

		return nRet;
	}
};