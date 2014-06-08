#ifndef		__T_STRING_H__
#define		__T_STRING_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_string(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::AString __AStrType;
		__AStrType str;
		{
			str.resize(10);
			if(str.size() != 10)
			{
				GTLINE2("String size operation failed!");
				++nRet;
			}
			if(str.capacity() != 10)
			{
				GTLINE2("String capacity operation failed!");
				++nRet;
			}
			str.reserve(20);
			if(str.size() != 0)
			{
				GTLINE2("String size operation failed!");
				++nRet;
			}
			if(str.capacity() != 20)
			{
				GTLINE2("String capacity operation failed!");
				++nRet;
			}
			str.resize(20);
			if(str.size() != 20)
			{
				GTLINE2("String size operation failed!");
				++nRet;
			}
			if(str.capacity() != 20)
			{
				GTLINE2("String capacity operation failed!");
				++nRet;
			}
			str.clear();
		}
		__AStrType::it newit;
		__AStrType::const_it newcit;
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
		str = "Hello World!";
		if(str.empty())
		{
			GTLINE2("String initialized but empty!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World!"))
		{
			GTLINE2("String length error!");
			++nRet;
		}
		if(str.capacity() < str.size())
		{
			GTLINE2("String capacity below size!");
			++nRet;
		}
		if(str != "Hello World!")
		{
			GTLINE2("String move or operator != error!");
			++nRet;
		}
		__AStrType str1 = str;
		if(str != str1)
		{
			GTLINE2("String copy construct error!");
			++nRet;
		}
		str = (GAIA::NM)-123456789;
		if(str != "-123456789")
		{
			GTLINE2("String construct from GAIA::NM failed!");
			++nRet;
		}
		if((GAIA::NM)str != -123456789)
		{
			GTLINE2("String operator GAIA::NM failed!");
			++nRet;
		}
		str = (GAIA::UM)123456789;
		if(str != "123456789")
		{
			GTLINE2("String construct from GAIA::UM failed!");
			++nRet;
		}
		if((GAIA::UM)str != 123456789)
		{
			GTLINE2("String operator GAIA::UM failed!");
			++nRet;
		}
		str = (GAIA::N8)-123;
		if(str != "-123")
		{
			GTLINE2("String construct from GAIA::N8 failed!");
			++nRet;
		}
		if((GAIA::N8)str != -123)
		{
			GTLINE2("String operator GAIA::N8 failed!");
			++nRet;
		}
		str = (GAIA::U8)123;
		if(str != "123")
		{
			GTLINE2("String construct from GAIA::U8 failed!");
			++nRet;
		}
		if((GAIA::U8)str != 123)
		{
			GTLINE2("String operator GAIA::U8 failed!");
			++nRet;
		}
		str = (GAIA::N16)-12345;
		if(str != "-12345")
		{
			GTLINE2("String construct from GAIA::N16 failed!");
			++nRet;
		}
		if((GAIA::N16)str != -12345)
		{
			GTLINE2("String operator GAIA::N16 failed!");
			++nRet;
		}
		str = (GAIA::U16)12345;
		if(str != "12345")
		{
			GTLINE2("String construct from GAIA::U16 failed!");
			++nRet;
		}
		if((GAIA::U16)str != 12345)
		{
			GTLINE2("String operator GAIA::U16 failed!");
			++nRet;
		}
		str = (GAIA::N32)-123456789;
		if(str != "-123456789")
		{
			GTLINE2("String construct from GAIA::N32 failed!");
			++nRet;
		}
		if((GAIA::N32)str != -123456789)
		{
			GTLINE2("String operator GAIA::N32 failed!");
			++nRet;
		}
		str = (GAIA::U32)123456789;
		if(str != "123456789")
		{
			GTLINE2("String construct from GAIA::U32 failed!");
			++nRet;
		}
		if((GAIA::U32)str != 123456789)
		{
			GTLINE2("String operator GAIA::U32 failed!");
			++nRet;
		}
		str = (GAIA::N64)-123456789123456789;
		if(str != "-123456789123456789")
		{
			GTLINE2("String construct from GAIA::N64 failed!");
			++nRet;
		}
		if((GAIA::N64)str != -123456789123456789)
		{
			GTLINE2("String operator GAIA::N64 failed!");
			++nRet;
		}
		str = (GAIA::U64)123456789123456789;
		if(str != "123456789123456789")
		{
			GTLINE2("String construct from GAIA::U64 failed!");
			++nRet;
		}
		if((GAIA::U64)str != 123456789123456789)
		{
			GTLINE2("String operator GAIA::U64 failed!");
			++nRet;
		}
		str = (GAIA::F32)1234.567F;
		str.resize(8);
		if(str != "1234.567")
		{
			GTLINE2("String construct from GAIA::F32 failed!");
			++nRet;
		}
		if((GAIA::F32)str != 1234.567F)
		{
			GTLINE2("String operator GAIA::F32 failed!");
			++nRet;
		}
		str = (GAIA::F64)-1234567.12345;
		str.resize(14);
		if(str != "-1234567.12345")
		{
			GTLINE2("String construct from GAIA::F64 failed!");
			++nRet;
		}
		if((GAIA::F64)str != -1234567.12345)
		{
			GTLINE2("String operator GAIA::F64 failed!");
			++nRet;
		}
		str = (GAIA::N32)(GAIA::BL)GAIA::True;
		if(str != "1")
		{
			GTLINE2("String construct from GAIA::BL(GAIA::True) failed!");
			++nRet;
		}
		if(!(GAIA::BL)str)
		{
			GTLINE2("String operator GAIA::BL failed!");
			++nRet;
		}
		str = (GAIA::N32)(GAIA::BL)GAIA::False;
		if(str != "0")
		{
			GTLINE2("String construct from GAIA::BL(GAIA::False) failed!");
			++nRet;
		}
		if(!(GAIA::BL)str)
		{
			GTLINE2("String operator GAIA::BL failed!");
			++nRet;
		}
		GAIA::X128 x128;
		GAIA::ALGORITHM::xmemset(&x128, 17, sizeof(x128));
		str = x128;
		if(str != "11111111111111111111111111111111")
		{
			GTLINE2("String construct from GAIA::X128 failed!");
			++nRet;
		}
		if((GAIA::X128)str != x128)
		{
			GTLINE2("String operator GAIA::X128 failed!");
			++nRet;
		}
		str = "HelloWorld";
		str1 = str;
		if(!(str1 == str && str1 >= str && str1 <= str))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(str1 != str || str1 > str || str1 < str)
		{
			GTLINE2("String compare != > < error!");
			++nRet;
		}
		if(!(str == "HelloWorld" && str >= "HelloWorld" && str <= "HelloWorld"))
		{
			GTLINE2("String compare == >= <= error!");
			++nRet;
		}
		if(str != "HelloWorld" || str > "HelloWorld" || str < "HelloWorld")
		{
			GTLINE2("String compare != > <!");
			++nRet;
		}
		str.resize(5);
		if(str != "Hello")
		{
			GTLINE2("String resize failed!");
			++nRet;
		}
		str.reserve(1000);
		if(!str.empty())
		{
			GTLINE2("String reserve failed!");
			++nRet;
		}
		str.destroy();
		str = "HelloWorld";
		str.insert('!', str.size());
		str.insert('%', str.size() / 2);
		str.insert('?', 0);
		if(str != "?Hello%World!")
		{
			GTLINE2("String insert element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("?Hello%World!"))
		{
			GTLINE2("String insert element failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("String insert element failed! The size is above capacity!");
			++nRet;
		}
		str = "HelloWorld";
		str.insert("Yes", str.size());
		str.insert("No", str.size() / 2);
		str.insert("Cancel", 0);
		if(str != "CancelHelloWNoorldYes")
		{
			GTLINE2("String insert element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element* failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("String insert element* failed! The size is above capacity!");
			++nRet;
		}
		str = "HelloWorld";
		str.insert((__AStrType)"Yes", str.size());
		str.insert((__AStrType)"No", str.size() / 2);
		str.insert((__AStrType)"Cancel", 0);
		if(str != "CancelHelloWNoorldYes")
		{
			GTLINE2("String inverse object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("CancelHelloWNoorldYes"))
		{
			GTLINE2("String insert element object failed! The size calculate error!");
			++nRet;
		}
		if(str.size() > str.capacity())
		{
			GTLINE2("String insert element object failed! The size is above capacity!");
			++nRet;
		}
		str = "HelloWorld";
		if(str.isallupper())
		{
			GTLINE2("String isallupper failed!");
			++nRet;
		}
		if(str.isalllower())
		{
			GTLINE2("String isalllower failed!");
			++nRet;
		}
		if(!str.isexistupper())
		{
			GTLINE2("String isexistupper failed!");
			++nRet;
		}
		if(!str.isexistlower())
		{
			GTLINE2("String isexistlower failed!");
			++nRet;
		}
		str.tolower();
		if(!str.isalllower())
		{
			GTLINE2("String tolower failed!");
			++nRet;
		}
		str.toupper();
		if(!str.isallupper())
		{
			GTLINE2("String to upper failed!");
			++nRet;
		}
		str = "HelloWorld";
		str1 = str + "HelloWorld";
		if(str1 != "HelloWorldHelloWorld")
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		if(str1.size() != GAIA::ALGORITHM::strlen("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator + failed!");
			++nRet;
		}
		str = "HelloWorld";
		str += "HelloWorld";
		if(str != "HelloWorldHelloWorld")
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorldHelloWorld"))
		{
			GTLINE2("String operator += failed!");
			++nRet;
		}
		str = "HelloWorld";
		str1.clear();
		str = str + str1;
		if(str != "HelloWorld")
		{
			GTLINE2("String operator + empty string failed!");
			++nRet;
		}
		str += str1;
		if(str != "HelloWorld")
		{
			GTLINE2("String operator += empty string failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String operator + or += empty string failed!");
			++nRet;
		}
		str = "HelloWorld";
		if(str[0] != 'H' ||
			str[1] != 'e' ||
			str[2] != 'l' ||
			str[3] != 'l' ||
			str[4] != 'o' ||
			str[5] != 'W' ||
			str[6] != 'o' ||
			str[7] != 'r' ||
			str[8] != 'l' ||
			str[9] != 'd')
		{
			GTLINE2("String operator [] failed!");
			++nRet;
		}
		str = "HelloWorld";
		const GAIA::GCH* cpsz = str;
		if(GAIA::ALGORITHM::strcmp(cpsz, "HelloWorld") != 0)
		{
			GTLINE2("String operator const _DataType* failed!");
			++nRet;
		}
		GAIA::GCH* psz = str;
		if(GAIA::ALGORITHM::strcmp(psz, "HelloWorld") != 0)
		{
			GTLINE2("String operator _DataType* failed!");
			++nRet;
		}
		str = "HelloWorld";
		str = "HelloWorld" + str;
		if(str != "HelloWorldHelloWorld")
		{
			GTLINE2("String global operator + failed!");
			++nRet;
		}
		str = "HelloWorld";
		if(*str.front_ptr() != 'H')
		{
			GTLINE2("String front_ptr failed!");
			++nRet;
		}
		if(*str.back_ptr() != 'd')
		{
			GTLINE2("String back_ptr failed");
			++nRet;
		}
		__AStrType::it itfront = str.front_it();
		__AStrType::it itback = str.back_it();
		__AStrType::const_it citfront = str.const_front_it();
		__AStrType::const_it citback = str.const_back_it();
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
			szTemp[citfront - str.const_front_it()] = *citfront;
			szTemp[citfront - str.const_front_it() + 1] = 0;
			++citfront;
		}
		if(str != szTemp)
		{
			GTLINE2("String const iterator element access exist error!");
			++nRet;
		}
		while(!itfront.empty())
		{
			szTemp[itfront - str.front_it()] = *itfront;
			szTemp[itfront - str.front_it() + 1] = 0;
			++itfront;
		}
		if(str != szTemp)
		{
			GTLINE2("String iterator element access exist error!");
			nRet++;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		citfront = str.const_front_it();
		itfront = str.front_it();
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
		if(citfront - str.const_front_it() != 10)
		{
			GTLINE2("String const iterator += operator failed!");
			++nRet;
		}
		if(itfront - str.front_it() != 10)
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
		str = "Hello World! I am gaia, i am all object's base!";
		str.erase_index(0);
		str.erase_index(str.size() - 1);
		str.erase_index(3);
		if(str != "ell World! I am gaia, i am all object's base")
		{
			GTLINE2("String erase_index element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("ell World! I am gaia, i am all object's base"))
		{
			GTLINE2("String erase_index element cause size failed!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		str.erase_index(6, 10);
		if(str != "Hello ! I am gaia, i am all object's base!")
		{
			GTLINE2("String erase_index multi elements failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello ! I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase_index multi elements cause size failed!");
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase('a', 0) != 6)
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(str != "Hello World! I m gi, i m ll object's bse!")
		{
			GTLINE2("String erase element from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World! I m gi, i m ll object's bse!"))
		{
			GTLINE2("String erase element from index cause size error!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase("am ", 1) != 2)
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(str != "Hello World! I gaia, i all object's base!")
		{
			GTLINE2("String erase element* from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element* from index cause size error!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase((__AStrType)"am ", 1) != 2)
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(str != "Hello World! I gaia, i all object's base!")
		{
			GTLINE2("String erase element object from index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World! I gaia, i all object's base!"))
		{
			GTLINE2("String erase element object from index cause size error!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase("Hello World! ", 0) != 1)
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(str != "I am gaia, i am all object's base!")
		{
			GTLINE2("String erase first part failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("I am gaia, i am all object's base!"))
		{
			GTLINE2("String erase first part cause size error!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase("base!", 0) != 1)
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(str != "Hello World! I am gaia, i am all object's ")
		{
			GTLINE2("String erase last part failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello World! I am gaia, i am all object's "))
		{
			GTLINE2("String erase last part cause size error!");
			++nRet;
		}
		str = "Hello World! I am gaia, i am all object's base!";
		if(str.erase("Hello World! I am gaia, i am all object's base!", 0) != 1)
		{
			GTLINE2("String erase full failed!");
			++nRet;
		}
		if(!str.empty())
		{
			GTLINE2("String erase full cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.left(5);
		if(str != "Hello")
		{
			GTLINE2("String left failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String left cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.right(4);
		if(str != "World")
		{
			GTLINE2("String right failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String right cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.mid(5, 6);
		if(str != "Wo")
		{
			GTLINE2("String mid failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Wo"))
		{
			GTLINE2("String mid cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.left(0);
		if(!str.empty())
		{
			GTLINE2("String full left failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.right(str.size() - 1);
		if(!str.empty())
		{
			GTLINE2("String full right failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.mid(0, 0);
		if(str != "H")
		{
			GTLINE2("String mid left failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.mid(str.size() - 1, str.size() - 1);
		if(str != "d")
		{
			GTLINE2("String mid right failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.mid(str.size() / 2, str.size() / 2);
		if(str != "W")
		{
			GTLINE2("String mid mid failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left(5);
		if(str != "World")
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left('H');
		if(str != "elloWorld")
		{
			GTLINE2("String trim_left by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("elloWorld"))
		{
			GTLINE2("String trim_left by element cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left('a');
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_left by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left("He");
		if(str != "lloWorld")
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("lloWorld"))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left("Ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_left by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left((__AStrType)"Hello");
		if(str != "World")
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_left((__AStrType)"Ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_left by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_left by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti('h');
		if(str != "elloWorld")
		{
			GTLINE2("String trim_lefti by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("elloWorld"))
		{
			GTLINE2("String trim_lefti by element cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti('a');
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_lefti by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti("he");
		if(str != "lloWorld")
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("lloWorld"))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti("ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_lefti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti((__AStrType)"hello");
		if(str != "World")
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("World"))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_lefti((__AStrType)"ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_lefti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_lefti by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right(4);
		if(str != "Hello")
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right('d');
		if(str != "HelloWorl")
		{
			GTLINE2("String trim_right by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorl"))
		{
			GTLINE2("String trim_right by element cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right('a');
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_right by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right("ld");
		if(str != "HelloWor")
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWor"))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right("Ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_right by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right((__AStrType)"World");
		if(str != "Hello")
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_right((__AStrType)"Ab");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_right by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_right by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti('D');
		if(str != "HelloWorl")
		{
			GTLINE2("String trim_righti by element failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorl"))
		{
			GTLINE2("String trim_righti by element cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti('a');
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_righti by index failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by index cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti("LD");
		if(str != "HelloWor")
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWor"))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti("AB");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_righti by element* failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by element* cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti((__AStrType)"WORLD");
		if(str != "Hello")
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("Hello"))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		str = "HelloWorld";
		str.trim_righti((__AStrType)"AB");
		if(str != "HelloWorld")
		{
			GTLINE2("String trim_righti by element object failed!");
			++nRet;
		}
		if(str.size() != GAIA::ALGORITHM::strlen("HelloWorld"))
		{
			GTLINE2("String trim_righti by element object cause size error!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		if(str.rfind('l', str.size() - 1) != 18)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(str.rfind('d', str.size() - 1) != 19)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(str.rfind('H', str.size() - 1) != 10)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(str.rfind('x', str.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element failed!");
			++nRet;
		}
		if(str.rfind("Hello", str.size() - 1) != 10)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(str.rfind("ld", str.size() - 1) != 18)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(str.rfind("HelloWorldH", str.size() - 1) != 0)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(str.rfind("rr", str.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element* failed!");
			++nRet;
		}
		if(str.rfind((__AStrType)"r", str.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__AStrType)"rl", str.size() - 1) != 17)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__AStrType)"ld", str.size() - 1) != 18)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__AStrType)"HelloWorldH", str.size() - 1) != 0)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		if(str.rfind((__AStrType)"rr", str.size() - 1) != GINVALID)
		{
			GTLINE2("String rfind element object failed!");
			++nRet;
		}
		str = "HelloWorld";
		str.replace('l', 'x');
		if(str != "HexxoWorxd")
		{
			GTLINE2("String replace element failed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace("Hello", "abc");
		if(str != "abcWorldabcWorld")
		{
			GTLINE2("String replace element* left failed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace("World", "abc");
		if(str != "HelloabcHelloabc")
		{
			GTLINE2("String replace element* rightfailed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace("oW", "ab");
		if(str != "HellaborldHellaborld")
		{
			GTLINE2("String replace element* mid failed");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace((__AStrType)"Hello", (__AStrType)"abc");
		if(str != "abcWorldabcWorld")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace((__AStrType)"World", (__AStrType)"abc");
		if(str != "HelloabcHelloabc")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace((__AStrType)"oW", (__AStrType)"ab");
		if(str != "HellaborldHellaborld")
		{
			GTLINE2("String replace element object right failed!");
			++nRet;
		}
		str = "HelloWorldHelloWorld";
		str.replace("Hello", "");
		if(str != "WorldWorld")
		{
			GTLINE2("String replace to empty string failed!");
			++nRet;
		}
		str = "Hello";
		str = 10 + str;
		if(str != "10Hello")
		{
			GTLINE2("String global operator + error!");
			++nRet;
		}
		str = "1234567890ABCDEF1234567890ABCDEF";
		if(str.type() != (GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID128))
		{
			GTLINE2("String type RID128 failed!");
			++nRet;
		}
		str = "Hello world 123.4F";
		if(str.type() != GAIA::STRING_TYPE_STRING)
		{
			GTLINE2("String type string failed!");
			++nRet;
		}
		str = "-123.4F";
		if(!(str.type() & GAIA::STRING_TYPE_REAL))
		{
			GTLINE2("String type real failed!");
			++nRet;
		}
		str = "+123123123123";
		if(!(str.type() & GAIA::STRING_TYPE_INTEGER))
		{
			GTLINE2("String type integer failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif
