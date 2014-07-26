#ifndef		__T_CHARS_H__
#define		__T_CHARS_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_chars(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::TChars __TCharsType;
		__TCharsType chs;
		{
			chs.resize(10);
			if(chs.size() != 10)
			{
				GTLINE2("String size operation failed!");
				++nRet;
			}
			chs.resize(20);
			if(chs.size() != 20)
			{
				GTLINE2("String size operation failed!");
				++nRet;
			}
			chs.clear();
		}
		if(!chs.empty())
		{
			GTLINE2("New string is not empty!");
			++nRet;
		}
		__TCharsType::it newit;
		__TCharsType::const_it newcit;
		newit = chs.front_it();
		if(!newit.empty())
		{
			GTLINE2("New chs front_it is not empty!");
			++nRet;
		}
		newit = chs.back_it();
		if(!newit.empty())
		{
			GTLINE2("New chs back_it is not empty!");
			++nRet;
		}
		newcit = chs.const_front_it();
		if(!newcit.empty())
		{
			GTLINE2("New chs const_front_it is not empty!");
			++nRet;
		}
		newcit = chs.const_back_it();
		if(!newcit.empty())
		{
			GTLINE2("New chs const_back_it is not empty!");
			++nRet;
		}
		chs.clear();
		chs = _T("Hello World!");
		if(chs.empty())
		{
			GTLINE2("String initialized but empty!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello World!")))
		{
			GTLINE2("String length error!");
			++nRet;
		}
		if(chs.capacity() < chs.size())
		{
			GTLINE2("String capacity below size!");
			++nRet;
		}
		if(chs != _T("Hello World!"))
		{
			GTLINE2("String move or operator != error!");
			++nRet;
		}
		__TCharsType chs1 = chs;
		if(chs != chs1)
		{
			GTLINE2("String copy construct error!");
			++nRet;
		}
		chs = (GAIA::NM)-123456789;
		if(chs != _T("-123456789"))
		{
			GTLINE2("String construct from GAIA::NM failed!");
			++nRet;
		}
		if((GAIA::NM)chs != -123456789)
		{
			GTLINE2("String operator GAIA::NM failed!");
			++nRet;
		}
		chs = (GAIA::UM)123456789;
		if(chs != _T("123456789"))
		{
			GTLINE2("String construct from GAIA::UM failed!");
			++nRet;
		}
		if((GAIA::UM)chs != 123456789)
		{
			GTLINE2("String operator GAIA::UM failed!");
			++nRet;
		}
		chs = (GAIA::N8)-123;
		if(chs != _T("-123"))
		{
			GTLINE2("String construct from GAIA::N8 failed!");
			++nRet;
		}
		if((GAIA::N8)chs != -123)
		{
			GTLINE2("String operator GAIA::N8 failed!");
			++nRet;
		}
		chs = (GAIA::U8)123;
		if(chs != _T("123"))
		{
			GTLINE2("String construct from GAIA::U8 failed!");
			++nRet;
		}
		if((GAIA::U8)chs != 123)
		{
			GTLINE2("String operator GAIA::U8 failed!");
			++nRet;
		}
		chs = (GAIA::N16)-12345;
		if(chs != _T("-12345"))
		{
			GTLINE2("String construct from GAIA::N16 failed!");
			++nRet;
		}
		if((GAIA::N16)chs != -12345)
		{
			GTLINE2("String operator GAIA::N16 failed!");
			++nRet;
		}
		chs = (GAIA::U16)12345;
		if(chs != _T("12345"))
		{
			GTLINE2("String construct from GAIA::U16 failed!");
			++nRet;
		}
		if((GAIA::U16)chs != 12345)
		{
			GTLINE2("String operator GAIA::U16 failed!");
			++nRet;
		}
		chs = (GAIA::N32)-123456789;
		if(chs != _T("-123456789"))
		{
			GTLINE2("String construct from GAIA::N32 failed!");
			++nRet;
		}
		if((GAIA::N32)chs != -123456789)
		{
			GTLINE2("String operator GAIA::N32 failed!");
			++nRet;
		}
		chs = (GAIA::U32)123456789;
		if(chs != _T("123456789"))
		{
			GTLINE2("String construct from GAIA::U32 failed!");
			++nRet;
		}
		if((GAIA::U32)chs != 123456789)
		{
			GTLINE2("String operator GAIA::U32 failed!");
			++nRet;
		}
		chs = (GAIA::N64)-123456789123456789;
		if(chs != _T("-123456789123456789"))
		{
			GTLINE2("String construct from GAIA::N64 failed!");
			++nRet;
		}
		if((GAIA::N64)chs != -123456789123456789)
		{
			GTLINE2("String operator GAIA::N64 failed!");
			++nRet;
		}
		chs = (GAIA::U64)123456789123456789;
		if(chs != _T("123456789123456789"))
		{
			GTLINE2("String construct from GAIA::U64 failed!");
			++nRet;
		}
		if((GAIA::U64)chs != 123456789123456789)
		{
			GTLINE2("String operator GAIA::U64 failed!");
			++nRet;
		}
		chs = (GAIA::F32)1234.567F;
		chs.resize(8);
		if(chs != _T("1234.567"))
		{
			GTLINE2("String construct from GAIA::F32 failed!");
			++nRet;
		}
		if((GAIA::F32)chs != 1234.567F)
		{
			GTLINE2("String operator GAIA::F32 failed!");
			++nRet;
		}
		chs = (GAIA::F64)-1234567.12345;
		chs.resize(14);
		if(chs != _T("-1234567.12345"))
		{
			GTLINE2("String construct from GAIA::F64 failed!");
			++nRet;
		}
		if((GAIA::F64)chs != -1234567.12345)
		{
			GTLINE2("String operator GAIA::F64 failed!");
			++nRet;
		}
		chs = (GAIA::N32)(GAIA::BL)GAIA::True;
		if(chs != _T("1"))
		{
			GTLINE2("String construct from GAIA::BL(GAIA::True) failed!");
			++nRet;
		}
		if(!(GAIA::BL)chs)
		{
			GTLINE2("String operator GAIA::BL failed!");
			++nRet;
		}
		chs = (GAIA::N32)(GAIA::BL)GAIA::False;
		if(chs != _T("0"))
		{
			GTLINE2("String construct from GAIA::BL(GAIA::False) failed!");
			++nRet;
		}
		if(!(GAIA::BL)chs)
		{
			GTLINE2("String operator GAIA::BL failed!");
			++nRet;
		}
		GAIA::X128 x128;
		GAIA::ALGORITHM::xmemset(&x128, 17, sizeof(x128));
		chs = x128;
		if(chs != _T("11111111111111111111111111111111"))
		{
			GTLINE2("String construct from GAIA::X128 failed!");
			++nRet;
		}
		if((GAIA::X128)chs != x128)
		{
			GTLINE2("String operator GAIA::X128 failed!");
			++nRet;
		}
		chs = _T("HelloWorld";)
		chs1 = chs;
		if(!(chs1 == chs && chs1 >= chs && chs1 <= chs))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(chs1 != chs || chs1 > chs || chs1 < chs)
		{
			GTLINE2("String compare != > < error!");
			++nRet;
		}
		if(!(chs == _T("HelloWorld") && chs >= _T("HelloWorld") && chs <= _T("HelloWorld")))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(chs != _T("HelloWorld") || chs > _T("HelloWorld") || chs < _T("HelloWorld"))
		{
			GTLINE2("String compare != > <!");
			++nRet;
		}
		chs.resize(5);
		if(chs != _T("Hello"))
		{
			GTLINE2("String resize failed!");
			++nRet;
		}
		chs.clear();
		chs = _T("HelloWorld");
		chs.insert('!', chs.size());
		chs.insert('%', chs.size() / 2);
		chs.insert('?', 0);
		if(chs != _T("?Hello%World!"))
		{
			GTLINE2("String insert element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("?Hello%World!")))
		{
			GTLINE2("String insert element failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element failed! The size is above capacity!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.insert(_T("Yes"), chs.size());
		chs.insert(_T("No"), chs.size() / 2);
		chs.insert(_T("Cancel"), 0);
		if(chs != _T("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("CancelHelloWNoorldYes")))
		{
			GTLINE2("String insert element* failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element* failed! The size is above capacity!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.insert((__TCharsType)_T("Yes"), chs.size());
		chs.insert((__TCharsType)_T("No"), chs.size() / 2);
		chs.insert((__TCharsType)_T("Cancel"), 0);
		if(chs != _T("CancelHelloWNoorldYes"))
		{
			GTLINE2("String inverse object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("CancelHelloWNoorldYes")))
		{
			GTLINE2("String insert element object failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element object failed! The size is above capacity!");
			++nRet;
		}
		chs = _T("HelloWorld");
		if(chs.isallupper())
		{
			GTLINE2("String isallupper failed!");
			++nRet;
		}
		if(chs.isalllower())
		{
			GTLINE2("String isalllower failed!");
			++nRet;
		}
		if(!chs.isexistupper())
		{
			GTLINE2("String isexistupper failed!");
			++nRet;
		}
		if(!chs.isexistlower())
		{
			GTLINE2("String isexistlower failed!");
			++nRet;
		}
		chs.tolower();
		if(!chs.isalllower())
		{
			GTLINE2("String tolower failed!");
			++nRet;
		}
		chs.toupper();
		if(!chs.isallupper())
		{
			GTLINE2("String to upper failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs1 = chs + _T("HelloWorld");
		if(chs1 != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		if(chs1.size() != GAIA::ALGORITHM::strlen(_T("HelloWorldHelloWorld")))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs += _T("HelloWorld");
		if(chs != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorldHelloWorld")))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs1.clear();
		chs = chs + chs1;
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String operator + empty string failed!");
			++nRet;
		}
		chs += chs1;
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String operator += empty string failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String operator + or += empty string failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		if(chs[0] != 'H' ||
			chs[1] != 'e' ||
			chs[2] != 'l' ||
			chs[3] != 'l' ||
			chs[4] != 'o' ||
			chs[5] != 'W' ||
			chs[6] != 'o' ||
			chs[7] != 'r' ||
			chs[8] != 'l' ||
			chs[9] != 'd')
		{
			GTLINE2("String operator [] failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		const GAIA::TCH* cpsz = chs;
		if(GAIA::ALGORITHM::strcmp(cpsz, _T("HelloWorld")) != 0)
		{
			GTLINE2("String operator const _DataType* failed!");
			++nRet;
		}
		GAIA::TCH* psz = chs;
		if(GAIA::ALGORITHM::strcmp(psz, _T("HelloWorld")) != 0)
		{
			GTLINE2("String operator _DataType* failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs = _T("HelloWorld") + chs;
		if(chs != _T("HelloWorldHelloWorld"))
		{
			GTLINE2("String global operator + failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		if(*chs.front_ptr() != 'H')
		{
			GTLINE2("String front_ptr failed!");
			++nRet;
		}
		if(*chs.back_ptr() != 'd')
		{
			GTLINE2("String back_ptr failed");
			++nRet;
		}
		__TCharsType::it itfront = chs.front_it();
		__TCharsType::it itback = chs.back_it();
		__TCharsType::const_it citfront = chs.const_front_it();
		__TCharsType::const_it citback = chs.const_back_it();
		if(itfront.empty() || itback.empty() || citfront.empty() || citback.empty())
		{
			GTLINE2("String front and back iterator(include const) exist error!");
			++nRet;
		}
		if(*itfront != 'H')
		{
			GTLINE2("String front_it failed!");
			++nRet;
		}
		if(*itback != 'd')
		{
			GTLINE2("String back_it failed!");
			++nRet;
		}
		if(*citfront != 'H')
		{
			GTLINE2("String const_front_it failed!");
			++nRet;
		}
		if(*citback != 'd')
		{
			GTLINE2("String const_back_it failed!");
			++nRet;
		}
		GAIA::TCH szTemp[128];
		while(!citfront.empty())
		{
			szTemp[citfront - chs.const_front_it()] = *citfront;
			szTemp[citfront - chs.const_front_it() + 1] = 0;
			++citfront;
		}
		if(chs != szTemp)
		{
			GTLINE2("String const iterator element access exist error!");
			++nRet;
		}
		while(!itfront.empty())
		{
			szTemp[itfront - chs.front_it()] = *itfront;
			szTemp[itfront - chs.front_it() + 1] = 0;
			++itfront;
		}
		if(chs != szTemp)
		{
			GTLINE2("String iterator element access exist error!");
			nRet++;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		citfront = chs.const_front_it();
		itfront = chs.front_it();
		if((citfront + 10) - citfront != 10)
		{
			GTLINE2("String const iterator's operator + index or - iterator failed!");
			++nRet;
		}
		if((itfront + 10) - itfront != 10)
		{
			GTLINE2("String iterator's operator + index or - iterator failed!");
			++nRet;
		}
		citfront += 10;
		itfront += 10;
		if(citfront - chs.const_front_it() != 10)
		{
			GTLINE2("String const iterator += operator failed!");
			++nRet;
		}
		if(itfront - chs.front_it() != 10)
		{
			GTLINE2("String iterator += operator failed!");
			++nRet;
		}
		citfront -= 20;
		itfront -= 20;
		if(!citfront.empty())
		{
			GTLINE2("String const iterator -= operator failed!");
			++nRet;
		}
		if(!itfront.empty())
		{
			GTLINE2("String iterator -= operator failed!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		chs.erase_index(0);
		chs.erase_index(chs.size() - 1);
		chs.erase_index(3);
		if(chs != _T("ell World! I am gaia, i am all object's base"))
		{
			GTLINE2("String erase_index element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("ell World! I am gaia, i am all object's base")))
		{
			GTLINE2("String erase_index element cause size failed!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		chs.erase_index(6, 10);
		if(chs != _T("Hello ! I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase_index multi elements failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello ! I am gaia, i am all object's base!")))
		{
			GTLINE2("String erase_index multi elements cause size failed!");
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase('a', 0) != 6)
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs != _T("Hello World! I m gi, i m ll object's bse!"))
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello World! I m gi, i m ll object's bse!")))
		{
			GTLINE2("String erase element from index cause size error!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(_T("am "), 1) != 2)
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs != _T("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("String erase element* from index cause size error!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase((__TCharsType)_T("am "), 1) != 2)
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs != _T("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("String erase element object from index cause size error!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(_T("Hello World! "), 0) != 1)
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs != _T("I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("I am gaia, i am all object's base!")))
		{
			GTLINE2("String erase first part cause size error!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(_T("base!"), 0) != 1)
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs != _T("Hello World! I am gaia, i am all object's "))
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello World! I am gaia, i am all object's ")))
		{
			GTLINE2("String erase last part cause size error!");
			++nRet;
		}
		chs = _T("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(_T("Hello World! I am gaia, i am all object's base!"), 0) != 1)
		{
			GTLINE2("String erase full failed!");
			++nRet;
		}
		if(!chs.empty())
		{
			GTLINE2("String erase full cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.left(5);
		if(chs != _T("Hello"))
		{
			GTLINE2("String left failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello")))
		{
			GTLINE2("String left cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.right(4);
		if(chs != _T("World"))
		{
			GTLINE2("String right failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("World")))
		{
			GTLINE2("String right cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.mid(5, 6);
		if(chs != _T("Wo"))
		{
			GTLINE2("String mid failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Wo")))
		{
			GTLINE2("String mid cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.left(0);
		if(!chs.empty())
		{
			GTLINE2("String full left failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.right(chs.size() - 1);
		if(!chs.empty())
		{
			GTLINE2("String full right failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.mid(0, 0);
		if(chs != _T("H"))
		{
			GTLINE2("String mid left failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.mid(chs.size() - 1, chs.size() - 1);
		if(chs != _T("d"))
		{
			GTLINE2("String mid right failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.mid(chs.size() / 2, chs.size() / 2);
		if(chs != _T("W"))
		{
			GTLINE2("String mid mid failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left(5);
		if(chs != _T("World"))
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("World")))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left(_T('H'));
		if(chs != _T("elloWorld"))
		{
			GTLINE2("String trim_left by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("elloWorld")))
		{
			GTLINE2("String trim_left by element cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left(_T('a'));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left(_T("He"));
		if(chs != _T("lloWorld"))
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("lloWorld")))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left(_T("Ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left((__TCharsType)_T("Hello"));
		if(chs != _T("World"))
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("World")))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_left((__TCharsType)_T("Ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti(_T('h'));
		if(chs != _T("elloWorld"))
		{
			GTLINE2("String trim_lefti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("elloWorld")))
		{
			GTLINE2("String trim_lefti by element cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti(_T('a'));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_lefti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_lefti by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti(_T("he"));
		if(chs != _T("lloWorld"))
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("lloWorld")))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti(_T("ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti((__TCharsType)_T("hello"));
		if(chs != _T("World"))
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("World")))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_lefti((__TCharsType)_T("ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right(4);
		if(chs != _T("Hello"))
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello")))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right(_T('d'));
		if(chs != _T("HelloWorl"))
		{
			GTLINE2("String trim_right by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorl")))
		{
			GTLINE2("String trim_right by element cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right(_T('a'));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right(_T("ld"));
		if(chs != _T("HelloWor"))
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWor")))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right(_T("Ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right((__TCharsType)_T("World"));
		if(chs != _T("Hello"))
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello")))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_right((__TCharsType)_T("Ab"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti(_T('D'));
		if(chs != _T("HelloWorl"))
		{
			GTLINE2("String trim_righti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorl")))
		{
			GTLINE2("String trim_righti by element cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti(_T('a'));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_righti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_righti by index cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti(_T("LD"));
		if(chs != _T("HelloWor"))
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWor")))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti(_T("AB"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti((__TCharsType)_T("WORLD"));
		if(chs != _T("Hello"))
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("Hello")))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.trim_righti((__TCharsType)_T("AB"));
		if(chs != _T("HelloWorld"))
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(_T("HelloWorld")))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		if(chs.rfind('l', chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(chs.rfind('d', chs.size() - 1) != 19)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(chs.rfind('H', chs.size() - 1) != 10)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(chs.rfind('x', chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(chs.rfind(_T("Hello"), chs.size() - 1) != 10)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(_T("ld"), chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(_T("HelloWorldH"), chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(_T("rr"), chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)_T("r"), chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)_T("rl"), chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)_T("ld"), chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)_T("HelloWorldH"), chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)_T("rr"), chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		chs = _T("HelloWorld");
		chs.replace('l', 'x');
		if(chs != _T("HexxoWorxd"))
		{
			GTLINE2("String replace element failed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace(_T("Hello"), _T("abc"));
		if(chs != _T("abcWorldabcWorld"))
		{
			GTLINE2("String replace element* left failed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace(_T("World"), _T("abc"));
		if(chs != _T("HelloabcHelloabc"))
		{
			GTLINE2("String replace element* rightfailed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace(_T("oW"), _T("ab"));
		if(chs != _T("HellaborldHellaborld"))
		{
			GTLINE2("String replace element* mid failed");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace((__TCharsType)_T("Hello"), (__TCharsType)_T("abc"));
		if(chs != _T("abcWorldabcWorld"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace((__TCharsType)_T("World"), (__TCharsType)_T("abc"));
		if(chs != _T("HelloabcHelloabc"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace((__TCharsType)_T("oW"), (__TCharsType)_T("ab"));
		if(chs != _T("HellaborldHellaborld"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = _T("HelloWorldHelloWorld");
		chs.replace(_T("Hello"), _T(""));
		if(chs != _T("WorldWorld"))
		{
			GTLINE2("String replace to empty string failed!");
			++nRet;
		}
		chs = _T("Hello");
		chs = 10 + chs;
		if(chs != _T("10Hello"))
		{
			GTLINE2("String global operator + error!");
			++nRet;
		}
		chs = _T("1234567890ABCDEF1234567890ABCDEF");
		if(chs.type() != (GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID128))
		{
			GTLINE2("String type RID128 failed!");
			++nRet;
		}
		chs = _T("Hello world 123.4F");
		if(chs.type() != GAIA::STRING_TYPE_STRING)
		{
			GTLINE2("String type string failed!");
			++nRet;
		}
		chs = _T("-123.4F");
		if(!(chs.type() & GAIA::STRING_TYPE_REAL))
		{
			GTLINE2("String type real failed!");
			++nRet;
		}
		chs = _T("+123123123123");
		if(!(chs.type() & GAIA::STRING_TYPE_INTEGER))
		{
			GTLINE2("String type integer failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif
