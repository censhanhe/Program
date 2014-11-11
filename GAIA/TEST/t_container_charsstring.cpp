#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_charsstring(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::TCharsString __StrType;
		__StrType str;
		{
			str.resize(10);
			if(str.size() != 10)
			{
				GTLINE2("CharsString size operation failed!");
				++nRet;
			}
			str.reserve(20);
			if(str.size() != 0)
			{
				GTLINE2("CharsString size operation failed!");
				++nRet;
			}
			str.resize(20);
			if(str.size() != 20)
			{
				GTLINE2("CharsString size operation failed!");
				++nRet;
			}
			str.clear();
		}
		__StrType::it newit;
		__StrType::const_it newcit;
		newit = str.front_it();
		if(!newit.empty())
		{
			GTLINE2("New string front_it is not empty!");
			++nRet;
		}
		newit = str.back_it();
		if(!newit.empty())
		{
			GTLINE2("New string back_it is not empty!");
			++nRet;
		}
		newcit = str.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New string const_front_it is not empty!");
			++nRet;
		}
		newcit = str.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New string const_back_it is not empty!");
			++nRet;
		}
		if(!str.empty())
		{
			GTLINE2("New string is not empty!");
			++nRet;
		}
		str.destroy(); // Try to destroy new string.
		str = _T("Hello World!");
		if(str.empty())
		{
			GTLINE2("CharsString initialized but empty!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello World!")))
		{
			GTLINE2("CharsString length error!");
			++nRet;
		}
		if(str.capacity() < str.size())
		{
			GTLINE2("CharsString capacity below size!");
			++nRet;
		}
		if(str != _T("Hello World!"))
		{
			GTLINE2("CharsString move or operator != error!");
			++nRet;
		}
		__StrType str1 = str;
		if(str != str1)
		{
			GTLINE2("CharsString copy construct error!");
			++nRet;
		}
		str = (GAIA::NM)-123456789;
		if(str != _T("-123456789"))
		{
			GTLINE2("CharsString construct from GAIA::NM failed!");
			++nRet;
		}
		if((GAIA::NM)str != -123456789)
		{
			GTLINE2("CharsString operator GAIA::NM failed!");
			++nRet;
		}
		str = (GAIA::UM)123456789;
		if(str != _T("123456789"))
		{
			GTLINE2("CharsString construct from GAIA::UM failed!");
			++nRet;
		}
		if((GAIA::UM)str != 123456789)
		{
			GTLINE2("CharsString operator GAIA::UM failed!");
			++nRet;
		}
		str = (GAIA::N8)-123;
		if(str != _T("-123"))
		{
			GTLINE2("CharsString construct from GAIA::N8 failed!");
			++nRet;
		}
		if((GAIA::N8)str != -123)
		{
			GTLINE2("CharsString operator GAIA::N8 failed!");
			++nRet;
		}
		str = (GAIA::U8)123;
		if(str != _T("123"))
		{
			GTLINE2("CharsString construct from GAIA::U8 failed!");
			++nRet;
		}
		if((GAIA::U8)str != 123)
		{
			GTLINE2("CharsString operator GAIA::U8 failed!");
			++nRet;
		}
		str = (GAIA::N16)-12345;
		if(str != _T("-12345"))
		{
			GTLINE2("CharsString construct from GAIA::N16 failed!");
			++nRet;
		}
		if((GAIA::N16)str != -12345)
		{
			GTLINE2("CharsString operator GAIA::N16 failed!");
			++nRet;
		}
		str = (GAIA::U16)12345;
		if(str != _T("12345"))
		{
			GTLINE2("CharsString construct from GAIA::U16 failed!");
			++nRet;
		}
		if((GAIA::U16)str != 12345)
		{
			GTLINE2("CharsString operator GAIA::U16 failed!");
			++nRet;
		}
		str = (GAIA::N32)-123456789;
		if(str != _T("-123456789"))
		{
			GTLINE2("CharsString construct from GAIA::N32 failed!");
			++nRet;
		}
		if((GAIA::N32)str != -123456789)
		{
			GTLINE2("CharsString operator GAIA::N32 failed!");
			++nRet;
		}
		str = (GAIA::U32)123456789;
		if(str != _T("123456789"))
		{
			GTLINE2("CharsString construct from GAIA::U32 failed!");
			++nRet;
		}
		if((GAIA::U32)str != 123456789)
		{
			GTLINE2("CharsString operator GAIA::U32 failed!");
			++nRet;
		}
		str = (GAIA::N64)-123456789123456789;
		if(str != _T("-123456789123456789"))
		{
			GTLINE2("CharsString construct from GAIA::N64 failed!");
			++nRet;
		}
		if((GAIA::N64)str != -123456789123456789)
		{
			GTLINE2("CharsString operator GAIA::N64 failed!");
			++nRet;
		}
		str = (GAIA::U64)123456789123456789;
		if(str != _T("123456789123456789"))
		{
			GTLINE2("CharsString construct from GAIA::U64 failed!");
			++nRet;
		}
		if((GAIA::U64)str != 123456789123456789)
		{
			GTLINE2("CharsString operator GAIA::U64 failed!");
			++nRet;
		}
		str = (GAIA::F32)1234.567F;
		str.resize(8);
		if(str != _T("1234.567"))
		{
			GTLINE2("CharsString construct from GAIA::F32 failed!");
			++nRet;
		}
		if((GAIA::F32)str != 1234.567F)
		{
			GTLINE2("CharsString operator GAIA::F32 failed!");
			++nRet;
		}
		str = (GAIA::F64)-1234567.12345;
		str.resize(14);
		if(str != _T("-1234567.12345"))
		{
			GTLINE2("CharsString construct from GAIA::F64 failed!");
			++nRet;
		}
		if((GAIA::F64)str != -1234567.12345)
		{
			GTLINE2("CharsString operator GAIA::F64 failed!");
			++nRet;
		}
		str = GSCAST(GAIA::N32)(GSCAST(GAIA::BL)(GAIA::True));
		if(str != _T("1"))
		{
			GTLINE2("CharsString construct from GAIA::BL(GAIA::True) failed!");
			++nRet;
		}
		if(!(GAIA::BL)str)
		{
			GTLINE2("CharsString operator GAIA::BL failed!");
			++nRet;
		}
		str = GSCAST(GAIA::N32)(GSCAST(GAIA::BL)(GAIA::False));
		if(str != _T("0"))
		{
			GTLINE2("CharsString construct from GAIA::BL(GAIA::False) failed!");
			++nRet;
		}
		if(!(GAIA::BL)str)
		{
			GTLINE2("CharsString operator GAIA::BL failed!");
			++nRet;
		}
		GAIA::X128 x128;
		GAIA::ALGO::xmemset(&x128, 17, sizeof(x128));
		str = x128;
		if(str != _T("11111111111111111111111111111111"))
		{
			GTLINE2("CharsString construct from GAIA::X128 failed!");
			++nRet;
		}
		if((GAIA::X128)str != x128)
		{
			GTLINE2("CharsString operator GAIA::X128 failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str1 = str;
		if(!(str1 == str && str1 >= str && str1 <= str))
		{
			GTLINE2("CharsString compare == >= <= error!");
			++nRet;
		}
		if(str1 != str || str1 > str || str1 < str)
		{
			GTLINE2("CharsString compare != > < error!");
			++nRet;
		}
		if(!(str == _T("HelloWorld") && str >= _T("HelloWorld") && str <= _T("HelloWorld")))
		{
			GTLINE2("CharsString compare == >= <= error!");
			++nRet;
		}
		if(str != _T("HelloWorld") || str > _T("HelloWorld") || str < _T("HelloWorld"))
		{
			GTLINE2("CharsString compare != > <!");
			++nRet;
		}
		str.resize(5);
		if(str != _T("Hello"))
		{
			GTLINE2("CharsString resize failed!");
			++nRet;
		}
		str.reserve(1000);
		if(!str.empty())
		{
			GTLINE2("CharsString reserve failed!");
			++nRet;
		}
		str.destroy();
		str = _T("HelloWorld");
		str.insert(_T('!'), str.size());
		str.insert(_T('%'), str.size() / 2);
		str.insert(_T('?'), 0);
		if(str != _T("?Hello%World!"))
		{
			GTLINE2("CharsString insert element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("?Hello%World!")))
		{
			GTLINE2("CharsString insert element failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("CharsString insert element failed! The size is above capacity!");
			++nRet;
		}
		str = _T("HelloWorld";)
			str.insert(_T("Yes"), str.size());
		str.insert(_T("No"), str.size() / 2);
		str.insert(_T("Cancel"), 0);
		if(str != _T("CancelHelloWNoorldYes"))
		{
			GTLINE2("CharsString insert element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("CancelHelloWNoorldYes")))
		{
			GTLINE2("CharsString insert element* failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("CharsString insert element* failed! The size is above capacity!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.insert((__StrType)_T("Yes"), str.size());
		str.insert((__StrType)_T("No"), str.size() / 2);
		str.insert((__StrType)_T("Cancel"), 0);
		if(str != _T("CancelHelloWNoorldYes"))
		{
			GTLINE2("CharsString inverse object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("CancelHelloWNoorldYes")))
		{
			GTLINE2("CharsString insert element object failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("CharsString insert element object failed! The size is above capacity!");
			++nRet;
		}
		str = _T("HelloWorld");
		if(str.isallupper())
		{
			GTLINE2("CharsString isallupper failed!");
			++nRet;
		}
		if(str.isalllower())
		{
			GTLINE2("CharsString isalllower failed!");
			++nRet;
		}
		if(!str.isexistupper())
		{
			GTLINE2("CharsString isexistupper failed!");
			++nRet;
		}
		if(!str.isexistlower())
		{
			GTLINE2("CharsString isexistlower failed!");
			++nRet;
		}
		str.tolower();
		if(!str.isalllower())
		{
			GTLINE2("CharsString tolower failed!");
			++nRet;
		}
		str.toupper();
		if(!str.isallupper())
		{
			GTLINE2("CharsString to upper failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str1 = str + _T("HelloWorld");
		if(str1 != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("CharsString operator + failed!");
			++nRet;
		}
		if(str1.size() != GAIA::ALGO::strlen(_T("HelloWorldHelloWorld")))
		{
			GTLINE2("CharsString operator + failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str += _T("HelloWorld");
		if(str != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("CharsString operator += failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorldHelloWorld")))
		{
			GTLINE2("CharsString operator += failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str1.clear();
		str = str + str1;
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString operator + empty string failed!");
			++nRet;
		}
		str += str1;
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString operator += empty string failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString operator + or += empty string failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		if(str[0] != _T('H') ||
			str[1] != _T('e') ||
			str[2] != _T('l') ||
			str[3] != _T('l') ||
			str[4] != _T('o') ||
			str[5] != _T('W') ||
			str[6] != _T('o') ||
			str[7] != _T('r') ||
			str[8] != _T('l') ||
			str[9] != _T('d'))
		{
			GTLINE2("CharsString operator [] failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		const GAIA::TCH* cpsz = str;
		if(GAIA::ALGO::strcmp(cpsz, _T("HelloWorld")) != 0)
		{
			GTLINE2("CharsString operator const _DataType* failed!");
			++nRet;
		}
		GAIA::TCH* psz = str;
		if(GAIA::ALGO::strcmp(psz, _T("HelloWorld")) != 0)
		{
			GTLINE2("CharsString operator _DataType* failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str = _T("HelloWorld") + str;
		if(str != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("CharsString global operator + failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		if(*str.front_ptr() != _T('H'))
		{
			GTLINE2("CharsString front_ptr failed!");
			++nRet;
		}
		if(*str.back_ptr() != _T('d'))
		{
			GTLINE2("CharsString back_ptr failed");
			++nRet;
		}
		__StrType::it itfront = str.front_it();
		__StrType::it itback = str.back_it();
		__StrType::const_it citfront = str.const_front_it();
		__StrType::const_it citback = str.const_back_it();
		if(itfront.empty() || itback.empty() || citfront.empty() || citback.empty())
		{
			GTLINE2("CharsString front and back iterator(include const) exist error!");
			++nRet;
		}
		if(*itfront != _T('H'))
		{
			GTLINE2("CharsString front_it failed!");
			++nRet;
		}
		if(*itback != _T('d'))
		{
			GTLINE2("CharsString back_it failed!");
			++nRet;
		}
		if(*citfront != _T('H'))
		{
			GTLINE2("CharsString const_front_it failed!");
			++nRet;
		}
		if(*citback != _T('d'))
		{
			GTLINE2("CharsString const_back_it failed!");
			++nRet;
		}
		GAIA::TCH szTemp[128];
		for(; !citfront.empty(); ++citfront)
		{
			szTemp[citfront - str.const_front_it()] = *citfront;
			szTemp[citfront - str.const_front_it() + 1] = 0;
		}
		if(str != szTemp)
		{
			GTLINE2("CharsString const iterator element access exist error!");
			++nRet;
		}
		for(; !itfront.empty(); ++itfront)
		{
			szTemp[itfront - str.front_it()] = *itfront;
			szTemp[itfront - str.front_it() + 1] = 0;
		}
		if(str != szTemp)
		{
			GTLINE2("CharsString iterator element access exist error!");
			nRet++;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		citfront = str.const_front_it();
		itfront = str.front_it();
		if((citfront + 10) - citfront != 10)
		{
			GTLINE2("CharsString const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((itfront + 10) - itfront != 10)
		{
			GTLINE2("CharsString iterator's operator + index or - iterator failed!");
			++nRet;
		}
		citfront += 10;
		itfront += 10;
		if(citfront - str.const_front_it() != 10)
		{
			GTLINE2("CharsString const iterator += operator failed!");
			++nRet;
		}
		if(itfront - str.front_it() != 10)
		{
			GTLINE2("CharsString iterator += operator failed!");
			++nRet;
		}
		citfront -= 20;
		itfront -= 20;
		if(!citfront.empty())
		{
			GTLINE2("CharsString const iterator -= operator failed!");
			++nRet;
		}
		if(!itfront.empty())
		{
			GTLINE2("CharsString iterator -= operator failed!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		str.erase_index(0);
		str.erase_index(str.size() - 1);
		str.erase_index(3);
		if(str != _T("ell World! I am gaia, i am all object's base"))
		{
			GTLINE2("CharsString erase_index element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("ell World! I am gaia, i am all object's base")))
		{
			GTLINE2("CharsString erase_index element cause size failed!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		str.erase_index(6, 10);
		if(str != _T("Hello ! I am gaia, i am all object's base!"))
		{
			GTLINE2("CharsString erase_index multi elements failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello ! I am gaia, i am all object's base!")))
		{
			GTLINE2("CharsString erase_index multi elements cause size failed!");
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase(_T('a'), 0) != 6)
		{
			GTLINE2("CharsString erase element from index failed!");
			++nRet;
		}
		if(str != _T("Hello World! I m gi, i m ll object's bse!"))
		{
			GTLINE2("CharsString erase element from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello World! I m gi, i m ll object's bse!")))
		{
			GTLINE2("CharsString erase element from index cause size error!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase(_T("am "), 1) != 2)
		{
			GTLINE2("CharsString erase element* from index failed!");
			++nRet;
		}
		if(str != _T("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("CharsString erase element* from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("CharsString erase element* from index cause size error!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase((__StrType)_T("am "), 1) != 2)
		{
			GTLINE2("CharsString erase element object from index failed!");
			++nRet;
		}
		if(str != _T("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("CharsString erase element object from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("CharsString erase element object from index cause size error!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase(_T("Hello World! "), 0) != 1)
		{
			GTLINE2("CharsString erase first part failed!");
			++nRet;
		}
		if(str != _T("I am gaia, i am all object's base!"))
		{
			GTLINE2("CharsString erase first part failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("I am gaia, i am all object's base!")))
		{
			GTLINE2("CharsString erase first part cause size error!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase(_T("base!"), 0) != 1)
		{
			GTLINE2("CharsString erase last part failed!");
			++nRet;
		}
		if(str != _T("Hello World! I am gaia, i am all object's "))
		{
			GTLINE2("CharsString erase last part failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello World! I am gaia, i am all object's ")))
		{
			GTLINE2("CharsString erase last part cause size error!");
			++nRet;
		}
		str = _T("Hello World! I am gaia, i am all object's base!");
		if(str.erase(_T("Hello World! I am gaia, i am all object's base!"), 0) != 1)
		{
			GTLINE2("CharsString erase full failed!");
			++nRet;
		}
		if(!str.empty())
		{
			GTLINE2("CharsString erase full cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.left(5);
		if(str != _T("Hello"))
		{
			GTLINE2("CharsString left failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello")))
		{
			GTLINE2("CharsString left cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.right(4);
		if(str != _T("World"))
		{
			GTLINE2("CharsString right failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("World")))
		{
			GTLINE2("CharsString right cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.mid(5, 6);
		if(str != _T("Wo"))
		{
			GTLINE2("CharsString mid failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Wo")))
		{
			GTLINE2("CharsString mid cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.left(0);
		if(!str.empty())
		{
			GTLINE2("CharsString full left failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.right(str.size() - 1);
		if(!str.empty())
		{
			GTLINE2("CharsString full right failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.mid(0, 0);
		if(str != _T("H"))
		{
			GTLINE2("CharsString mid left failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.mid(str.size() - 1, str.size() - 1);
		if(str != _T("d"))
		{
			GTLINE2("CharsString mid right failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.mid(str.size() / 2, str.size() / 2);
		if(str != _T("W"))
		{
			GTLINE2("CharsString mid mid failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left_index(5);
		if(str != _T("World"))
		{
			GTLINE2("CharsString trim_left by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("World")))
		{
			GTLINE2("CharsString trim_left by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left(_T('H'));
		if(str != _T("elloWorld"))
		{
			GTLINE2("CharsString trim_left by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("elloWorld")))
		{
			GTLINE2("CharsString trim_left by element cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left(_T('a'));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_left by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_left by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left(_T("He"));
		if(str != _T("lloWorld"))
		{
			GTLINE2("CharsString trim_left by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("lloWorld")))
		{
			GTLINE2("CharsString trim_left by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left(_T("Ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_left by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_left by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left((__StrType)_T("Hello"));
		if(str != _T("World"))
		{
			GTLINE2("CharsString trim_left by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("World")))
		{
			GTLINE2("CharsString trim_left by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_left((__StrType)_T("Ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_left by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_left by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti(_T('h'));
		if(str != _T("elloWorld"))
		{
			GTLINE2("CharsString trim_lefti by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("elloWorld")))
		{
			GTLINE2("CharsString trim_lefti by element cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti(_T('a'));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_lefti by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_lefti by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti(_T("he"));
		if(str != _T("lloWorld"))
		{
			GTLINE2("CharsString trim_lefti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("lloWorld")))
		{
			GTLINE2("CharsString trim_lefti by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti(_T("ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_lefti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_lefti by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti((__StrType)_T("hello"));
		if(str != _T("World"))
		{
			GTLINE2("CharsString trim_lefti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("World")))
		{
			GTLINE2("CharsString trim_lefti by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_lefti((__StrType)_T("ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_lefti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_lefti by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right_index(4);
		if(str != _T("Hello"))
		{
			GTLINE2("CharsString trim_right by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello")))
		{
			GTLINE2("CharsString trim_right by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right(_T('d'));
		if(str != _T("HelloWorl"))
		{
			GTLINE2("CharsString trim_right by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorl")))
		{
			GTLINE2("CharsString trim_right by element cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right(_T('a'));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_right by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_right by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right(_T("ld"));
		if(str != _T("HelloWor"))
		{
			GTLINE2("CharsString trim_right by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWor")))
		{
			GTLINE2("CharsString trim_right by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right(_T("Ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_right by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_right by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right((__StrType)_T("World"));
		if(str != _T("Hello"))
		{
			GTLINE2("CharsString trim_right by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello")))
		{
			GTLINE2("CharsString trim_right by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_right((__StrType)_T("Ab"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_right by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_right by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti(_T('D'));
		if(str != _T("HelloWorl"))
		{
			GTLINE2("CharsString trim_righti by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorl")))
		{
			GTLINE2("CharsString trim_righti by element cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti(_T('a'));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_righti by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_righti by index cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti(_T("LD"));
		if(str != _T("HelloWor"))
		{
			GTLINE2("CharsString trim_righti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWor")))
		{
			GTLINE2("CharsString trim_righti by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti(_T("AB"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_righti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_righti by element* cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti((__StrType)_T("WORLD"));
		if(str != _T("Hello"))
		{
			GTLINE2("CharsString trim_righti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("Hello")))
		{
			GTLINE2("CharsString trim_righti by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.trim_righti((__StrType)_T("AB"));
		if(str != _T("HelloWorld"))
		{
			GTLINE2("CharsString trim_righti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGO::strlen(_T("HelloWorld")))
		{
			GTLINE2("CharsString trim_righti by element object cause size error!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		if(str.rfind(_T('l'), str.size() - 1) != 18)
		{
			GTLINE2("CharsString rfind element failed!");
			++nRet;
		}
		if(str.rfind(_T('d'), str.size() - 1) != 19)
		{
			GTLINE2("CharsString rfind element failed!");
			++nRet;
		}
		if(str.rfind(_T('H'), str.size() - 1) != 10)
		{
			GTLINE2("CharsString rfind element failed!");
			++nRet;
		}
		if(str.rfind(_T('x'), str.size() - 1) != GINVALID)
		{
			GTLINE2("CharsString rfind element failed!");
			++nRet;
		}
		if(str.rfind(_T("Hello"), str.size() - 1) != 10)
		{
			GTLINE2("CharsString rfind element* failed!");
			++nRet;
		}
		if(str.rfind(_T("ld"), str.size() - 1) != 18)
		{
			GTLINE2("CharsString rfind element* failed!");
			++nRet;
		}
		if(str.rfind(_T("HelloWorldH"), str.size() - 1) != 0)
		{
			GTLINE2("CharsString rfind element* failed!");
			++nRet;
		}
		if(str.rfind(_T("rr"), str.size() - 1) != GINVALID)
		{
			GTLINE2("CharsString rfind element* failed!");
			++nRet;
		}
		if(str.rfind((__StrType)_T("r"), str.size() - 1) != 17)
		{
			GTLINE2("CharsString rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__StrType)_T("rl"), str.size() - 1) != 17)
		{
			GTLINE2("CharsString rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__StrType)_T("ld"), str.size() - 1) != 18)
		{
			GTLINE2("CharsString rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__StrType)_T("HelloWorldH"), str.size() - 1) != 0)
		{
			GTLINE2("CharsString rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__StrType)_T("rr"), str.size() - 1) != GINVALID)
		{
			GTLINE2("CharsString rfind element object failed!");
			++nRet;
		}
		str = _T("HelloWorld");
		str.replace(_T('l'), _T('x'));
		if(str != _T("HexxoWorxd"))
		{
			GTLINE2("CharsString replace element failed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace(_T("Hello"), _T("abc"));
		if(str != _T("abcWorldabcWorld"))
		{
			GTLINE2("CharsString replace element* left failed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace(_T("World"), _T("abc"));
		if(str != _T("HelloabcHelloabc"))
		{
			GTLINE2("CharsString replace element* rightfailed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace(_T("oW"), _T("ab"));
		if(str != _T("HellaborldHellaborld"))
		{
			GTLINE2("CharsString replace element* mid failed");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace((__StrType)_T("Hello"), (__StrType)_T("abc"));
		if(str != _T("abcWorldabcWorld"))
		{
			GTLINE2("CharsString replace element object right failed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace((__StrType)_T("World"), (__StrType)_T("abc"));
		if(str != _T("HelloabcHelloabc"))
		{
			GTLINE2("CharsString replace element object right failed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace((__StrType)_T("oW"), (__StrType)_T("ab"));
		if(str != _T("HellaborldHellaborld"))
		{
			GTLINE2("CharsString replace element object right failed!");
			++nRet;
		}
		str = _T("HelloWorldHelloWorld");
		str.replace(_T("Hello"), _T(""));
		if(str != _T("WorldWorld"))
		{
			GTLINE2("CharsString replace to empty string failed!");
			++nRet;
		}
		str = _T("Hello");
		str = 10 + str;
		if(str != _T("10Hello"))
		{
			GTLINE2("CharsString global operator + error!");
			++nRet;
		}
		str = _T("1234567890ABCDEF1234567890ABCDEF");
		if(str.type() != (GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID128))
		{
			GTLINE2("CharsString type RID128 failed!");
			++nRet;
		}
		str = _T("Hello world 123.4F");
		if(str.type() != GAIA::STRING_TYPE_STRING)
		{
			GTLINE2("CharsString type string failed!");
			++nRet;
		}
		str = _T("-123.4F");
		if(!(str.type() & GAIA::STRING_TYPE_REAL))
		{
			GTLINE2("CharsString type real failed!");
			++nRet;
		}
		str = _T("+123123123123");
		if(!(str.type() & GAIA::STRING_TYPE_INTEGER))
		{
			GTLINE2("CharsString type integer failed!");
			++nRet;
		}

		return nRet;
	}
};