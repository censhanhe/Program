#ifndef		__T_CHARS_H__
#define		__T_CHARS_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_chars(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::AChars __ACharsType;
		__ACharsType chs;
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
		__ACharsType::it newit;
		__ACharsType::const_it newcit;
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
		chs = "Hello World!";
		if(chs.empty())
		{
			GTLINE2("String initialized but empty!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello World!"))
		{
			GTLINE2("String length error!");
			++nRet;
		}
		if(chs.capacity() < chs.size())
		{
			GTLINE2("String capacity below size!");
			++nRet;
		}
		if(chs != "Hello World!")
		{
			GTLINE2("String move or operator != error!");
			++nRet;
		}
		__ACharsType chs1 = chs;
		if(chs != chs1)
		{
			GTLINE2("String copy construct error!");
			++nRet;
		}
		chs = (GAIA::NM)-123456789;
		if(chs != "-123456789")
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
		if(chs != "123456789")
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
		if(chs != "-123")
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
		if(chs != "123")
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
		if(chs != "-12345")
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
		if(chs != "12345")
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
		if(chs != "-123456789")
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
		if(chs != "123456789")
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
		if(chs != "-123456789123456789")
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
		if(chs != "123456789123456789")
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
		if(chs != "1234.567")
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
		if(chs != "-1234567.12345")
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
		if(chs != "1")
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
		if(chs != "0")
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
		if(chs != "11111111111111111111111111111111")
		{
			GTLINE2("String construct from GAIA::X128 failed!");
			++nRet;
		}
		if((GAIA::X128)chs != x128)
		{
			GTLINE2("String operator GAIA::X128 failed!");
			++nRet;
		}
		chs = "HelloWorld";
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
		if(!(chs == "HelloWorld" && chs >= "HelloWorld" && chs <= "HelloWorld"))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(chs != "HelloWorld" || chs > "HelloWorld" || chs < "HelloWorld")
		{
			GTLINE2("String compare != > <!");
			++nRet;
		}
		chs.resize(5);
		if(chs != "Hello")
		{
			GTLINE2("String resize failed!");
			++nRet;
		}
		chs.clear();
		chs = "HelloWorld";
		chs.insert('!', chs.size());
		chs.insert('%', chs.size() / 2);
		chs.insert('?', 0);
		if(chs != "?Hello%World!")
		{
			GTLINE2("String insert element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("?Hello%World!"))
		{
			GTLINE2("String insert element failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element failed! The size is above capacity!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.insert("Yes", chs.size());
		chs.insert("No", chs.size() / 2);
		chs.insert("Cancel", 0);
		if(chs != "CancelHelloWNoorldYes")
		{
			GTLINE2("String insert element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element* failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element* failed! The size is above capacity!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.insert((__ACharsType)"Yes", chs.size());
		chs.insert((__ACharsType)"No", chs.size() / 2);
		chs.insert((__ACharsType)"Cancel", 0);
		if(chs != "CancelHelloWNoorldYes")
		{
			GTLINE2("String inverse object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element object failed! The size calculate error!");
			++nRet;
		}
		if(chs.size() > chs.capacity())
		{
			GTLINE2("String insert element object failed! The size is above capacity!");
			++nRet;
		}
		chs = "HelloWorld";
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
		chs = "HelloWorld";
		chs1 = chs + "HelloWorld";
		if(chs1 != "HelloWorldHelloWorld")
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		if(chs1.size() != GAIA::ALGORITHM::strlen("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs += "HelloWorld";
		if(chs != "HelloWorldHelloWorld")
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs1.clear();
		chs = chs + chs1;
		if(chs != "HelloWorld")
		{
			GTLINE2("String operator + empty string failed!");
			++nRet;
		}
		chs += chs1;
		if(chs != "HelloWorld")
		{
			GTLINE2("String operator += empty string failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String operator + or += empty string failed!");
			++nRet;
		}
		chs = "HelloWorld";
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
		chs = "HelloWorld";
		const GAIA::GCH* cpsz = chs;
		if(GAIA::ALGORITHM::strcmp(cpsz, "HelloWorld") != 0)
		{
			GTLINE2("String operator const _DataType* failed!");
			++nRet;
		}
		GAIA::GCH* psz = chs;
		if(GAIA::ALGORITHM::strcmp(psz, "HelloWorld") != 0)
		{
			GTLINE2("String operator _DataType* failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs = "HelloWorld" + chs;
		if(chs != "HelloWorldHelloWorld")
		{
			GTLINE2("String global operator + failed!");
			++nRet;
		}
		chs = "HelloWorld";
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
		__ACharsType::it itfront = chs.front_it();
		__ACharsType::it itback = chs.back_it();
		__ACharsType::const_it citfront = chs.const_front_it();
		__ACharsType::const_it citback = chs.const_back_it();
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
		GAIA::GCH szTemp[128];
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
		chs = "Hello World! I am gaia, i am all object's base!";
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
		chs = "Hello World! I am gaia, i am all object's base!";
		chs.erasei(0);
		chs.erasei(chs.size() - 1);
		chs.erasei(3);
		if(chs != "ell World! I am gaia, i am all object's base")
		{
			GTLINE2("String erasei element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("ell World! I am gaia, i am all object's base"))
		{
			GTLINE2("String erasei element cause size failed!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		chs.erasei(6, 10);
		if(chs != "Hello ! I am gaia, i am all object's base!")
		{
			GTLINE2("String erasei multi elements failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello ! I am gaia, i am all object's base!"))
		{
			GTLINE2("String erasei multi elements cause size failed!");
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase('a', 0) != 6)
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs != "Hello World! I m gi, i m ll object's bse!")
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello World! I m gi, i m ll object's bse!"))
		{
			GTLINE2("String erase element from index cause size error!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase("am", 1) != 2)
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs != "Hello World! I  gaia, i  all object's base!")
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello World! I  gaia, i  all object's base!"))
		{
			GTLINE2("String erase element* from index cause size error!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase((__ACharsType)"am", 1) != 2)
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs != "Hello World! I  gaia, i  all object's base!")
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello World! I  gaia, i  all object's base!"))
		{
			GTLINE2("String erase element object from index cause size error!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase("Hello World! ", 0) != 1)
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs != "I am gaia, i am all object's base!")
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase first part cause size error!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase("base!", 0) != 1)
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs != "Hello World! I am gaia, i am all object's ")
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello World! I am gaia, i am all object's "))
		{
			GTLINE2("String erase last part cause size error!");
			++nRet;
		}
		chs = "Hello World! I am gaia, i am all object's base!";
		if(chs.erase("Hello World! I am gaia, i am all object's base!", 0) != 1)
		{
			GTLINE2("String erase full failed!");
			++nRet;
		}
		if(!chs.empty())
		{
			GTLINE2("String erase full cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.left(5);
		if(chs != "Hello")
		{
			GTLINE2("String left failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String left cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.right(4);
		if(chs != "World")
		{
			GTLINE2("String right failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String right cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.mid(5, 6);
		if(chs != "Wo")
		{
			GTLINE2("String mid failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Wo"))
		{
			GTLINE2("String mid cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.left(0);
		if(!chs.empty())
		{
			GTLINE2("String full left failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.right(chs.size() - 1);
		if(!chs.empty())
		{
			GTLINE2("String full right failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.mid(0, 0);
		if(chs != "H")
		{
			GTLINE2("String mid left failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.mid(chs.size() - 1, chs.size() - 1);
		if(chs != "d")
		{
			GTLINE2("String mid right failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.mid(chs.size() / 2, chs.size() / 2);
		if(chs != "W")
		{
			GTLINE2("String mid mid failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left(5);
		if(chs != "World")
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left('H');
		if(chs != "elloWorld")
		{
			GTLINE2("String trim_left by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("elloWorld"))
		{
			GTLINE2("String trim_left by element cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left('a');
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left("He");
		if(chs != "lloWorld")
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("lloWorld"))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left("Ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left((__ACharsType)"Hello");
		if(chs != "World")
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_left((__ACharsType)"Ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti('h');
		if(chs != "elloWorld")
		{
			GTLINE2("String trim_lefti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("elloWorld"))
		{
			GTLINE2("String trim_lefti by element cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti('a');
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_lefti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti("he");
		if(chs != "lloWorld")
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("lloWorld"))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti("ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti((__ACharsType)"hello");
		if(chs != "World")
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_lefti((__ACharsType)"ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right(4);
		if(chs != "Hello")
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right('d');
		if(chs != "HelloWorl")
		{
			GTLINE2("String trim_right by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorl"))
		{
			GTLINE2("String trim_right by element cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right('a');
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right("ld");
		if(chs != "HelloWor")
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWor"))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right("Ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right((__ACharsType)"World");
		if(chs != "Hello")
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_right((__ACharsType)"Ab");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti('D');
		if(chs != "HelloWorl")
		{
			GTLINE2("String trim_righti by element failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorl"))
		{
			GTLINE2("String trim_righti by element cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti('a');
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_righti by index failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by index cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti("LD");
		if(chs != "HelloWor")
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWor"))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti("AB");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti((__ACharsType)"WORLD");
		if(chs != "Hello")
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.trim_righti((__ACharsType)"AB");
		if(chs != "HelloWorld")
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(chs.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
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
		if(chs.rfind("Hello", chs.size() - 1) != 10)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind("ld", chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind("HelloWorldH", chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind("rr", chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(chs.rfind((__ACharsType)"r", chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__ACharsType)"rl", chs.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__ACharsType)"ld", chs.size() - 1) != 18)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__ACharsType)"HelloWorldH", chs.size() - 1) != 0)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(chs.rfind((__ACharsType)"rr", chs.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		chs = "HelloWorld";
		chs.replace('l', 'x');
		if(chs != "HexxoWorxd")
		{
			GTLINE2("String replace element failed!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace("Hello", "abc");
		if(chs != "abcWorldabcWorld")
		{
			GTLINE2("String replace element* left failed!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace("World", "abc");
		if(chs != "HelloabcHelloabc")
		{
			GTLINE2("String replace element* rightfailed!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace("oW", "ab");
		if(chs != "HellaborldHellaborld")
		{
			GTLINE2("String replace element* mid failed");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace((__ACharsType)"Hello", (__ACharsType)"abc");
		if(chs != "abcWorldabcWorld")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace((__ACharsType)"World", (__ACharsType)"abc");
		if(chs != "HelloabcHelloabc")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = "HelloWorldHelloWorld";
		chs.replace((__ACharsType)"oW", (__ACharsType)"ab");
		if(chs != "HellaborldHellaborld")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		chs = "Hello";
		chs = 10 + chs;
		if(chs != "10Hello")
		{
			GTLINE2("String global operator + error!");
			++nRet;
		}

		return nRet;
	}
};

#endif
