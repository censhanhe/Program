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
		chs = T_("Hello World!");
		if(chs.empty())
		{
			GTLINE2("String initialized but empty!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello World!")))
		{
			GTLINE2("String length error!");
			++nRet;
		}
		if(chs.capacity() < chs.size())
		{
			GTLINE2("String capacity below size!");
			++nRet;
		}
		if(chs != T_("Hello World!"))
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
		if(chs != T_("-123456789"))
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
		if(chs != T_("123456789"))
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
		if(chs != T_("-123"))
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
		if(chs != T_("123"))
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
		if(chs != T_("-12345"))
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
		if(chs != T_("12345"))
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
		if(chs != T_("-123456789"))
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
		if(chs != T_("123456789"))
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
		if(chs != T_("-123456789123456789"))
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
		if(chs != T_("123456789123456789"))
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
		if(chs != T_("1234.567"))
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
		if(chs != T_("-1234567.12345"))
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
		if(chs != T_("1"))
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
		if(chs != T_("0"))
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
		if(chs != T_("11111111111111111111111111111111"))
		{
			GTLINE2("String construct from GAIA::X128 failed!");
			++nRet;
		}
		if((GAIA::X128)chs != x128)
		{
			GTLINE2("String operator GAIA::X128 failed!");
			++nRet;
		}
		chs = T_("HelloWorld";)
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
		if(!(chs == T_("HelloWorld") && chs >= T_("HelloWorld") && chs <= T_("HelloWorld")))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(chs != T_("HelloWorld") || chs > T_("HelloWorld") || chs < T_("HelloWorld"))
		{
			GTLINE2("String compare != > <!");
			++nRet;
		}
		chs.resize(5);
		if(chs != T_("Hello"))
		{
			GTLINE2("String resize failed!");
			++nRet;
		}
		chs.clear();
		chs = T_("HelloWorld");
		chs.insert('!', chs.size());
		chs.insert('%', chs.size() / 2);
		chs.insert('?', 0);
		if(chs != T_("?Hello%World!"))
		{
			GTLINE2("String insert element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("?Hello%World!")))
		{
			GTLINE2("String insert element failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element failed! The size is above capacity!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.insert(T_("Yes"), chs.size());
		chs.insert(T_("No"), chs.size() / 2);
		chs.insert(T_("Cancel"), 0);
		if(chs != T_("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("CancelHelloWNoorldYes")))
		{
			GTLINE2("String insert element* failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element* failed! The size is above capacity!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.insert((__TCharsType)T_("Yes"), chs.size());
		chs.insert((__TCharsType)T_("No"), chs.size() / 2);
		chs.insert((__TCharsType)T_("Cancel"), 0);
		if(chs != T_("CancelHelloWNoorldYes"))
		{
			GTLINE2("String inverse object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("CancelHelloWNoorldYes")))
		{
			GTLINE2("String insert element object failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element object failed! The size is above capacity!");
			++nRet;
		}
		chs = T_("HelloWorld");
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
		chs = T_("HelloWorld");
		chs1 = chs + T_("HelloWorld");
		if(chs1 != T_("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		if(chs1.size() != GAIA::ALGORITHM::strlen(T_("HelloWorldHelloWorld")))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs += T_("HelloWorld");
		if(chs != T_("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorldHelloWorld")))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs1.clear();
		chs = chs + chs1;
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String operator + empty string failed!");
			++nRet;
		}
		chs += chs1;
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String operator += empty string failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String operator + or += empty string failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
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
		chs = T_("HelloWorld");
		const GAIA::TCH* cpsz = chs;
		if(GAIA::ALGORITHM::strcmp(cpsz, T_("HelloWorld")) != 0)
		{
			GTLINE2("String operator const _DataType* failed!");
			++nRet;
		}
		GAIA::TCH* psz = chs;
		if(GAIA::ALGORITHM::strcmp(psz, T_("HelloWorld")) != 0)
		{
			GTLINE2("String operator _DataType* failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs = T_("HelloWorld") + chs;
		if(chs != T_("HelloWorldHelloWorld"))
		{
			GTLINE2("String global operator + failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
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
		chs = T_("Hello World! I am gaia, i am all object's base!");
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
		chs = T_("Hello World! I am gaia, i am all object's base!");
		chs.erase_index(0);
		chs.erase_index(chs.size() - 1);
		chs.erase_index(3);
		if(chs != T_("ell World! I am gaia, i am all object's base"))
		{
			GTLINE2("String erase_index element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("ell World! I am gaia, i am all object's base")))
		{
			GTLINE2("String erase_index element cause size failed!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		chs.erase_index(6, 10);
		if(chs != T_("Hello ! I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase_index multi elements failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello ! I am gaia, i am all object's base!")))
		{
			GTLINE2("String erase_index multi elements cause size failed!");
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase('a', 0) != 6)
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs != T_("Hello World! I m gi, i m ll object's bse!"))
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello World! I m gi, i m ll object's bse!")))
		{
			GTLINE2("String erase element from index cause size error!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(T_("am "), 1) != 2)
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs != T_("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("String erase element* from index cause size error!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase((__TCharsType)T_("am "), 1) != 2)
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs != T_("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello World! I gaia, i all object's base!")))
		{
			GTLINE2("String erase element object from index cause size error!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(T_("Hello World! "), 0) != 1)
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs != T_("I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("I am gaia, i am all object's base!")))
		{
			GTLINE2("String erase first part cause size error!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(T_("base!"), 0) != 1)
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs != T_("Hello World! I am gaia, i am all object's "))
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello World! I am gaia, i am all object's ")))
		{
			GTLINE2("String erase last part cause size error!");
			++nRet;
		}
		chs = T_("Hello World! I am gaia, i am all object's base!");
		if(chs.erase(T_("Hello World! I am gaia, i am all object's base!"), 0) != 1)
		{
			GTLINE2("String erase full failed!");
			++nRet;
		}
		if(!chs.empty())
		{
			GTLINE2("String erase full cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.left(5);
		if(chs != T_("Hello"))
		{
			GTLINE2("String left failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello")))
		{
			GTLINE2("String left cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.right(4);
		if(chs != T_("World"))
		{
			GTLINE2("String right failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("World")))
		{
			GTLINE2("String right cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.mid(5, 6);
		if(chs != T_("Wo"))
		{
			GTLINE2("String mid failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Wo")))
		{
			GTLINE2("String mid cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.left(0);
		if(!chs.empty())
		{
			GTLINE2("String full left failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.right(chs.size() - 1);
		if(!chs.empty())
		{
			GTLINE2("String full right failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.mid(0, 0);
		if(chs != T_("H"))
		{
			GTLINE2("String mid left failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.mid(chs.size() - 1, chs.size() - 1);
		if(chs != T_("d"))
		{
			GTLINE2("String mid right failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.mid(chs.size() / 2, chs.size() / 2);
		if(chs != T_("W"))
		{
			GTLINE2("String mid mid failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left(5);
		if(chs != T_("World"))
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("World")))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left(T_('H'));
		if(chs != T_("elloWorld"))
		{
			GTLINE2("String trim_left by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("elloWorld")))
		{
			GTLINE2("String trim_left by element cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left(T_('a'));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left(T_("He"));
		if(chs != T_("lloWorld"))
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("lloWorld")))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left(T_("Ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left((__TCharsType)T_("Hello"));
		if(chs != T_("World"))
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("World")))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_left((__TCharsType)T_("Ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti(T_('h'));
		if(chs != T_("elloWorld"))
		{
			GTLINE2("String trim_lefti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("elloWorld")))
		{
			GTLINE2("String trim_lefti by element cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti(T_('a'));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_lefti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_lefti by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti(T_("he"));
		if(chs != T_("lloWorld"))
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("lloWorld")))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti(T_("ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti((__TCharsType)T_("hello"));
		if(chs != T_("World"))
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("World")))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_lefti((__TCharsType)T_("ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right(4);
		if(chs != T_("Hello"))
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello")))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right(T_('d'));
		if(chs != T_("HelloWorl"))
		{
			GTLINE2("String trim_right by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorl")))
		{
			GTLINE2("String trim_right by element cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right(T_('a'));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right(T_("ld"));
		if(chs != T_("HelloWor"))
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWor")))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right(T_("Ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right((__TCharsType)T_("World"));
		if(chs != T_("Hello"))
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello")))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_right((__TCharsType)T_("Ab"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti(T_('D'));
		if(chs != T_("HelloWorl"))
		{
			GTLINE2("String trim_righti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorl")))
		{
			GTLINE2("String trim_righti by element cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti(T_('a'));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_righti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_righti by index cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti(T_("LD"));
		if(chs != T_("HelloWor"))
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWor")))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti(T_("AB"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti((__TCharsType)T_("WORLD"));
		if(chs != T_("Hello"))
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("Hello")))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.trim_righti((__TCharsType)T_("AB"));
		if(chs != T_("HelloWorld"))
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen(T_("HelloWorld")))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
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
		if(chs.rfind(T_("Hello"), chs.size() - 1) != 10)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(T_("ld"), chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(T_("HelloWorldH"), chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind(T_("rr"), chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)T_("r"), chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)T_("rl"), chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)T_("ld"), chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)T_("HelloWorldH"), chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__TCharsType)T_("rr"), chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		chs = T_("HelloWorld");
		chs.replace('l', 'x');
		if(chs != T_("HexxoWorxd"))
		{
			GTLINE2("String replace element failed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace(T_("Hello"), T_("abc"));
		if(chs != T_("abcWorldabcWorld"))
		{
			GTLINE2("String replace element* left failed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace(T_("World"), T_("abc"));
		if(chs != T_("HelloabcHelloabc"))
		{
			GTLINE2("String replace element* rightfailed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace(T_("oW"), T_("ab"));
		if(chs != T_("HellaborldHellaborld"))
		{
			GTLINE2("String replace element* mid failed");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace((__TCharsType)T_("Hello"), (__TCharsType)T_("abc"));
		if(chs != T_("abcWorldabcWorld"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace((__TCharsType)T_("World"), (__TCharsType)T_("abc"));
		if(chs != T_("HelloabcHelloabc"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace((__TCharsType)T_("oW"), (__TCharsType)T_("ab"));
		if(chs != T_("HellaborldHellaborld"))
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = T_("HelloWorldHelloWorld");
		chs.replace(T_("Hello"), T_(""));
		if(chs != T_("WorldWorld"))
		{
			GTLINE2("String replace to empty string failed!");
			++nRet;
		}
		chs = T_("Hello");
		chs = 10 + chs;
		if(chs != T_("10Hello"))
		{
			GTLINE2("String global operator + error!");
			++nRet;
		}
		chs = T_("1234567890ABCDEF1234567890ABCDEF");
		if(chs.type() != (GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID128))
		{
			GTLINE2("String type RID128 failed!");
			++nRet;
		}
		chs = T_("Hello world 123.4F");
		if(chs.type() != GAIA::STRING_TYPE_STRING)
		{
			GTLINE2("String type string failed!");
			++nRet;
		}
		chs = T_("-123.4F");
		if(!(chs.type() & GAIA::STRING_TYPE_REAL))
		{
			GTLINE2("String type real failed!");
			++nRet;
		}
		chs = T_("+123123123123");
		if(!(chs.type() & GAIA::STRING_TYPE_INTEGER))
		{
			GTLINE2("String type integer failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif
