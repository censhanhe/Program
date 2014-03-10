#if defined(_MSC_VER) && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#	define	_CRTDBG_MAP_ALLOC
#	include	<stdlib.h>
#	include	<stdio.h>
#	include	<crtdbg.h>
#	include <assert.h>
#	define HEAPCHECK assert(_CrtCheckMemory());
#else
#	define HEAPCHECK
#endif

#define PERFORMANCE_COMPARE
#ifdef PERFORMANCE_COMPARE
#	include <vector>
#	include <set>
#	include <algorithm>
#	include <iostream>
#	define PERF_PRINT_LINE(name) std::cout<<(name)<<std::endl;
#	define PERF_PRINT_TIME std::cout<<'\t'<<"TIME-LOST="<<(GAIA::F64)(uPerfEnd - uPerfStart) * 0.001<<"(MS)"<<std::endl;
#	define PERF_PRINT_TYPE(type) std::cout<<(type);
#	define PERF_PRINT_TEXT(text) std::cout<<text;
#else
#	define PERF_PRINT_LINE(name)
#	define PERF_PRINT_TIME
#	define PERF_PRINT_TYPE(type)
#	define PERF_PRINT_TEXT(text)
#endif

#define TEST_CURRENT			""
#define TEST_BEGIN(name)		if(GAIA::ALGORITHM::strcmp(TEST_CURRENT, "") == 0 || GAIA::ALGORITHM::strcmp((name), TEST_CURRENT) == 0)\
								{\
									PERF_PRINT_LINE(name);\
									do\
									{\
										logfile.WriteText(name);\
										logfile.WriteText("\r\n");\
									}\
									while(0);\
									PERF_START("TIME-LOST");
#define TEST_END					PERF_END;\
									PERF_PRINT_TIME;\
									do\
									{\
										logfile.WriteText("\r\n\r\n");\
									}\
									while(0);\
								}
#define TEST_FILE_LINE(text)	do{logfile.WriteText("\t");logfile.WriteText(text);logfile.WriteText("\r\n"); PERF_PRINT_LINE(text);}while(0)
#define TEST_FILE_TEXT(text)	do{logfile.WriteText(text); PERF_PRINT_TEXT(text);}while(0)
#define PERF_START(name)		uPerfStart = GAIA::TIME::clock_time(); GAIA::ALGORITHM::strcpy(szPerfName, name);
#define PERF_END 				if(szPerfName[0] != 0)\
								{\
									uPerfEnd = GAIA::TIME::clock_time();\
									sprintf(szPerf, "%f(MS)", (GAIA::F64)(uPerfEnd - uPerfStart) * 0.001);\
									TEST_FILE_TEXT("\t");\
									TEST_FILE_TEXT(szPerfName);\
									TEST_FILE_LINE(szPerf);\
									szPerfName[0] = 0;\
								}

#include "gaia.h"

#if GAIA_OS == GAIA_OS_WINDOWS
#	pragma comment(lib, "ws2_32.lib")
#endif

#if GAIA_OS == GAIA_OS_WINDOWS && GAIA_PROFILE == GAIA_PROFILE_DEBUG
#	define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

GINL GAIA::GVOID LanguageInfo()
{
	GAIA::CONTAINER::AString strFileName;
#if GAIA_OS == GAIA_OS_WINDOWS
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_windows_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_windows_64.txt";
#	endif
#elif GAIA_OS == GAIA_OS_OSX
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_osx_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_osx_64.txt";
#	endif
#elif GAIA_OS == GAIA_OS_IOS
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_ios_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_ios_64.txt";
#	endif
#elif GAIA_OS == GAIA_OS_ANDROID
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_android_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_android_64.txt";
#	endif
#elif GAIA_OS == GAIA_OS_LINUX
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_linux_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_linux_64.txt";
#	endif
#elif GAIA_OS == GAIA_OS_UNIX
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_unix_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_unix_64.txt";
#	endif
#else
#	if GAIA_MACHINE == GAIA_MACHINE32
		strFileName = "../li/li_other_32.txt";
#	elif GAIA_MACHINE == GAIA_MACHINE64
		strFileName = "../li/li_other_64.txt";
#	endif
#endif
	if(strFileName.empty())
		return;
	GAIA::FILESYSTEM::File file;
	if(!file.Open(strFileName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE))
		return;

#define WRITE_TEXT(name, size) {\
	GAIA::CONTAINER::AString str;\
	str = (name);\
	file.WriteText(str.front_ptr());\
	str = (int)size;\
	file.WriteText(str.front_ptr());\
	file.WriteText("\r\n");}
	file.WriteText("[Basic Type Size]\r\n");
	WRITE_TEXT("    BL=", sizeof(GAIA::BL));
	WRITE_TEXT("    N8=", sizeof(GAIA::N8));
	WRITE_TEXT("    U8=", sizeof(GAIA::U8));
	WRITE_TEXT("   N16=", sizeof(GAIA::N16));
	WRITE_TEXT("   U16=", sizeof(GAIA::U16));
	WRITE_TEXT("   N32=", sizeof(GAIA::N32));
	WRITE_TEXT("   U32=", sizeof(GAIA::U32));
	WRITE_TEXT("   N64=", sizeof(GAIA::N64));
	WRITE_TEXT("   U64=", sizeof(GAIA::U64));
	WRITE_TEXT("    NM=", sizeof(GAIA::NM));
	WRITE_TEXT("    UM=", sizeof(GAIA::UM));
	WRITE_TEXT("   GCH=", sizeof(GAIA::GCH));
	WRITE_TEXT("  GWCH=", sizeof(GAIA::GWCH));
	WRITE_TEXT("GVOID*=", sizeof(GAIA::GVOID*));
	WRITE_TEXT("   F32=", sizeof(GAIA::F32));
	WRITE_TEXT("   F64=", sizeof(GAIA::F64));
	file.WriteText("\r\n");

	file.WriteText("[GAIA Basic Type Size]\r\n");
	WRITE_TEXT("  Vector<N32>=", sizeof(GAIA::CONTAINER::Vector<GAIA::N32>));
	WRITE_TEXT("   Stack<N32>=", sizeof(GAIA::CONTAINER::Stack<GAIA::N32>));
	WRITE_TEXT("   Queue<N32>=", sizeof(GAIA::CONTAINER::Queue<GAIA::N32>));
	WRITE_TEXT("    List<N32>=", sizeof(GAIA::CONTAINER::List<GAIA::N32>));
	WRITE_TEXT("    Pool<N32>=", sizeof(GAIA::CONTAINER::Pool<GAIA::N32>));
	file.WriteText("\r\n");

	file.WriteText("[GAIA Advance Type Size]\r\n");
	file.WriteText("\r\n");
#undef WRITE_TEXT
	file.Close();
}

template<typename _DataType> class SNode
{
public:
	typedef _DataType _datatype;
public:
	typedef SNode<_DataType> __MyType;
public:
	GINL SNode(){}
	GINL SNode(const __MyType& src){this->operator = (src);}
	GINL SNode(const _DataType& src){this->operator = (src);}
	GINL ~SNode(){}
	GINL GAIA::BL operator == (const __MyType& src) const{return m_data == src.m_data;}
	GINL GAIA::BL operator != (const __MyType& src) const{return m_data != src.m_data;}
	GINL GAIA::BL operator >= (const __MyType& src) const{return m_data >= src.m_data;}
	GINL GAIA::BL operator <= (const __MyType& src) const{return m_data <= src.m_data;}
	GINL GAIA::BL operator > (const __MyType& src) const{return m_data > src.m_data;}
	GINL GAIA::BL operator < (const __MyType& src) const{return m_data < src.m_data;}
	GINL _DataType& operator * (){return m_data;}
	GINL const _DataType& operator * () const{return m_data;}
	GINL __MyType& operator = (const __MyType& src){m_data = src.m_data; return *this;}
	GINL __MyType& operator = (const _DataType& src){m_data = src; return *this;}
private:
	_DataType m_data;
};

class MyThread : public GAIA::THREAD::Thread
{
public:
	MyThread(){m_bRuned = GAIA::False;}
	~MyThread(){}

	virtual GAIA::GVOID WorkProcedure()
	{
		GAIA::N32 nDebug = 0;
		nDebug = 0;
		m_bRuned = GAIA::True;
	}

	GAIA::BL IsRuned() const{return m_bRuned;}

private:
	GAIA::BL m_bRuned;
};

class MyNetworkHandle : public GAIA::NETWORK::NetworkHandle
{
public:
	GINL virtual GAIA::GVOID LostConnection(GAIA::BL bRecvTrueSendFalse)
	{
		PERF_PRINT_LINE("NetworkHandle : LostConnection CallBack!");
	}
};

static GAIA::NETWORK::NetworkHandle* s_pNH = GNULL;
class MyNetworkListener : public GAIA::NETWORK::NetworkListener
{
public:
	virtual GAIA::BL Accept(GAIA::NETWORK::NetworkHandle& h)
	{
		PERF_PRINT_LINE("NetworkListener : Accept CallBack!");
		if(s_pNH == GNULL)
		{
			h.Reference();
			s_pNH = &h;
		}
		return GAIA::True;
	}
};

class MyNetworkReceiver : public GAIA::NETWORK::NetworkReceiver
{
public:
	virtual GAIA::BL Receive(GAIA::NETWORK::NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size)
	{
		PERF_PRINT_LINE("NetworkReceiver : Receive CallBack!");
		for(GAIA::U32 x = 0; x < size; ++x)
		{
			PERF_PRINT_TYPE((GAIA::GCH)p[x]);
			PERF_PRINT_TYPE(" ");
		}
		return GAIA::True;
	}
};

GAIA::N32 main()
{
#if defined(_MSC_VER) && GAIA_PROFILE == GAIA_PROFILE_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	LanguageInfo();

#if GAIA_PROFILE == GAIA_PROFILE_DEBUG
	static const GAIA::N32 SAMPLE_COUNT = 10000;
#else
	static const GAIA::N32 SAMPLE_COUNT = 100000;
#endif

	GAIA::BL bFunctionSuccess = GAIA::True;

	//
	GAIA::MATH::random_seed((GAIA::U32)(GAIA::TIME::clock_time() / 1000));

	//
	GAIA::GCH szPerf[256];
	GAIA::GCH szPerfName[256];
	GAIA::U64 uPerfStart = 0, uPerfEnd = 0;
	GAIA::FILESYSTEM::File logfile;
	logfile.Open("../gaia_test_result.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
	
#if GAIA_PROFILE == GAIA_PROFILE_DEBUG
	logfile.WriteText("[GAIA TEST BEGIN(DEBUG)]\r\n\r\n");
#else
	logfile.WriteText("[GAIA TEST BEGIN(RELEASE)]\r\n\r\n");
#endif

	// Real number float equal test.
	{
		TEST_BEGIN("<Float equal function test>");
		{
			GAIA::BL bEqual = GAIA::MATH::equal(0.1F, 0.100001F);
			if(bEqual)
				TEST_FILE_LINE("equal(2) convert SUCCESSFULLY!");
			else
				TEST_FILE_LINE("equal(2) convert FAILED!");

			bEqual = GAIA::MATH::equal(0.1F, 0.11F, 0.1F);
			if(bEqual)
				TEST_FILE_LINE("equal(3) convert SUCCESSFULLY!");
			else
				TEST_FILE_LINE("equal(3) convert FAILED!");
		}
		TEST_END;
	}

	// X128 test.
	{
		TEST_BEGIN("<X128 test>");
		{
			GAIA::X128 id;
			id = "0123456789ABCDEF0123456789ABCDEF";
			GAIA::X128 tid;
			tid.u0 = 0x01234567;
			tid.u1 = 0x89ABCDEF;
			tid.u2 = 0x01234567;
			tid.u3 = 0x89ABCDEF;
			if(tid == id)
				TEST_FILE_LINE("X128 type convert and compare SUCCESSFULLY!");
			else
				TEST_FILE_LINE("X128 type convert and compare FAILED!");
		}
		TEST_END;
	}

	// Unique test.
	{
		TEST_BEGIN("<Unique algorithm test>");
		{
			GAIA::N32 listNum[] = {3,1,4,5,2,1,6,8,1,3,2,6,4,9,7,0};
			GAIA::N32* pNew = GAIA::ALGORITHM::unique_noorder(listNum, &listNum[sizeof(listNum) / sizeof(listNum[0]) - 1]);
			GAIA::N64 nCount = pNew - listNum + 1;
			if(nCount != 10)
				TEST_FILE_LINE("unique_noorder FAILED!");
		}
		TEST_END;
	}

	// String algorithm.
	{
		TEST_BEGIN("<String algorithm function test>");
		{
			bFunctionSuccess = GAIA::True;
			if(GAIA::ALGORITHM::strwrd("Hello World!", "lo") != GNULL)
				bFunctionSuccess = GAIA::False;
			if(GAIA::ALGORITHM::strwrd("Hello World!", "d") != GNULL)
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("String algorithm function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("String algorithm function test FAILED!");
		}
		TEST_END;
	}
	
	// String convert function test.
	{
		TEST_BEGIN("<String convert function test>");
		{
			GAIA::NM n;
			GAIA::ALGORITHM::str2int("-123456789", n);
			if(n != -123456789)
				TEST_FILE_LINE("str2int convert FAILED!");
			else
				TEST_FILE_LINE("str2int convert SUCCESSFULLY!");

			GAIA::REAL r;
			GAIA::ALGORITHM::str2real("-.1234", r);
			if(!GAIA::MATH::equal(r, -0.1234))
				TEST_FILE_LINE("str2real convert FAILED!");
			else
				TEST_FILE_LINE("str2real convert SUCCESSFULLY!");

			bFunctionSuccess = GAIA::True;
			n = -1234;
			GAIA::GTCH szTemp[1024];
			GAIA::ALGORITHM::int2str(n, szTemp);
			if(GAIA::ALGORITHM::strcmp(szTemp, L"-1234") != 0)
				bFunctionSuccess = GAIA::False;
			n = 0;
			GAIA::ALGORITHM::int2str(n, szTemp);
			if(GAIA::ALGORITHM::strcmp(szTemp, L"0") != 0)
				bFunctionSuccess = GAIA::False;
			if(!bFunctionSuccess)
				TEST_FILE_LINE("int2str convert FAILED!");
			else
				TEST_FILE_LINE("int2str convert SUCCESSFULLY!");

			bFunctionSuccess = GAIA::True;
			r = -1.2F;
			GAIA::ALGORITHM::real2str(r, szTemp);
			if(GAIA::ALGORITHM::strmch(szTemp, L"-1.2") != szTemp)
				bFunctionSuccess = GAIA::False;
			r = 0;
			GAIA::ALGORITHM::real2str(r, szTemp);
			if(GAIA::ALGORITHM::strcmp(szTemp, L"0.0") != 0)
				bFunctionSuccess = GAIA::False;
			if(!bFunctionSuccess)
				TEST_FILE_LINE("real2str convert FAILED!");
			else
				TEST_FILE_LINE("real2str convert SUCCESSFULLY!");

			n = GAIA::ALGORITHM::string_cast<GAIA::U8>("-124.456");
			r = GAIA::ALGORITHM::string_cast<GAIA::REAL>("-123.456");
			n = GAIA::ALGORITHM::string_autocast("-123.456");
			r = GAIA::ALGORITHM::string_autocast("-123.456");

			n = 0;
		}
		TEST_END;
	}

	// Pair test.
	{
		TEST_BEGIN("<Pair test>");
		{
			GAIA::CONTAINER::Pair<const GAIA::GCH*, GAIA::N32> pair("abc", 123);
			GAIA::CONTAINER::Pair<const GAIA::GCH*, GAIA::N32> newpair = pair;
			if(newpair != pair)
				TEST_FILE_LINE("Pair equal function test FAILED!");
			GAIA::N32 nDebug = 0;
			nDebug++;
		}
		TEST_END;
	}

	// Ptr test.
	{
		TEST_BEGIN("<Ptr test>");
		{
			GAIA::CONTAINER::Ptr<SNode<GAIA::N32> > pn1, pn2;
			SNode<GAIA::N32> n1, n2;
			pn1 = &n1;
			pn2 = &n2;
			GAIA::BL b = pn1 == pn2;
			b = pn1 != pn2;
			b = pn1 >= pn2;
			b = pn1 <= pn2;
			b = pn1 > pn2;
			b = pn1 < pn2;
			b = GAIA::False;
		}
		TEST_END;
	}

	// Ref test.
	{
		TEST_BEGIN("<Ref test>");
		{
			GAIA::CONTAINER::Ref<SNode<GAIA::N32> > rn1, rn2;
			SNode<GAIA::N32> n1, n2;
			rn1 = &n1;
			rn2 = &n2;
			GAIA::BL b = rn1 == rn2;
			b = rn1 != rn2;
			b = rn1 >= rn2;
			b = rn1 <= rn2;
			b = rn1 > rn2;
			b = rn1 < rn2;
			b = GAIA::False;
		}
		TEST_END;
	}

	// Basic stack bitset test.
	{
		TEST_BEGIN("<Basic stack bitset test>");
		{
			bFunctionSuccess = GAIA::True;
			GAIA::CONTAINER::BasicStackBitset<GAIA::U32, 32> bs;
			bs.clear();
			bs = 16;
			bs += 48;
			if(bs == 16 && bs == 48){}
			else
				bFunctionSuccess = GAIA::False;
			bs.clear();
			if(bs.capacity() != 32)
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("multi and operation test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("multi and operation test FAILED!");
			bs.clear();

			bs = 0;
			bs = 1;
			bs = 2;
			bs = 3;
			bs = 4;
			bs = 5;
			bs = 6;
			bs = 7;

			bs = 48;
			bs.inverse(48);
			if(bs == 48)
				TEST_FILE_LINE("inverse operation test FAILED!");
			else
				TEST_FILE_LINE("inverse operation test SUCCESSFULLY!");
		}
		TEST_END;
	}

	// Basic array test
	{
		TEST_BEGIN("<Basic array test>");
		{
			GAIA::CONTAINER::BasicArray<GAIA::U32, GAIA::U32, 100> ba;
			for(GAIA::CONTAINER::BasicArray<GAIA::U32, GAIA::U32, 100>::_sizetype x = 0; x < ba.capacity(); ++x)
				ba << GAIA::MATH::random();
			ba.sort();
			ba.erase(0);
			ba.clear();
			
			{
				typedef GAIA::CONTAINER::BasicArray<GAIA::N64, GAIA::N64, 10000> __ArrayType;
				__ArrayType v;
				for(GAIA::N64 x = 0; x < 10000; ++x)
					v.push_back(GAIA::MATH::random() % 100);
				v.sort();
				GAIA::N64 nDrop = v.unique();
				nDrop = 0;
				v.sort();
			}
		}
		TEST_END;
	};

	// Array test.
	{
		TEST_BEGIN("<Basic array test>");
		{
			GAIA::CONTAINER::Array<GAIA::N32, 32> temp;
			temp[0] = 10;
		}
		TEST_END;
	}

	// Basic vector test.
	{
		TEST_BEGIN("<Basic vector test>");
		{
			GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > bv;
			bv.push_back(10);
			bv.push_back(20);
			GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> >::it iter = bv.front_it();
			while(!iter.empty())
				++iter;
			bv.clear();
			bv.insert(0, 10);
			bv.insert(0, 20);
			bv.insert(2, 30);
			bv.erase(1);
			bv.clear();

			bv.clear();
			bv.push_back(0);
			bv.push_back(1);
			bv.push_back(2);
			bv.push_back(4);
			bv.push_back(2);
			bv.push_back(3);
			bv.sort();
			GAIA::U32 uDropCount = bv.unique();
			uDropCount = 0;

			{
				typedef GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __VectorType;
				__VectorType v;
				for(GAIA::N32 x = 0; x < 10000; ++x)
				{
					v.push_back(GAIA::MATH::random()%100);
				}
				v.sort();
				GAIA::N32 nDrop = v.unique();
				nDrop = 0;
				v.sort();
			}
		}
		TEST_END;
	}

	// Basic stack test.
	{
		TEST_BEGIN("<Basic stack test>");
		{
			typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __StackType;
			__StackType bs;
			bs.push(10);
			bs.push(20);
			GAIA::N32 n = bs.top();
			bs.pop();
			n = bs.top();
			bs.pop();
			GAIA::U32 uSize = bs.size();
			uSize = 0;
			__StackType::it fit = bs.front_it();
			__StackType::const_it cfit = bs.const_front_it();
			__StackType::it bit = bs.back_it();
			__StackType::const_it cbit = bs.const_back_it();
			++fit;
			--fit;
			++cfit;
			--cfit;
			++bit;
			--bit;
			++cbit;
			--cbit;
		}
		TEST_END;
	}

	// BasicBuffer test.
	{
		TEST_BEGIN("<Basic buffer test>");
		{
			GAIA::N32 arr[32];
			for(GAIA::N32 x = 0; x < sizeof(arr) / sizeof(GAIA::N32); ++x)
				arr[x] = x;

			GAIA::CONTAINER::BasicBuffer<GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > buf;
			buf.write(arr);
			buf.write(48);
			GAIA::U32 size = buf.write_size();
			size = 0;
		}
		TEST_END;
	}

	// String algorithm test.
	{
		TEST_BEGIN("<String algorithm test>");
		{
			GAIA::GTCH ch = GAIA::ALGORITHM::tolower('A');
			ch = 0;
			GAIA::GTCH sz[128] = L"abcdefgABCDEFG1234567!@#$%^&";
			GAIA::UM uLen = GAIA::ALGORITHM::strlen(sz);
			uLen = 0;
			GAIA::ALGORITHM::tolower(sz);
			sz[0] = 0;
			GAIA::N32 nCompare = GAIA::ALGORITHM::strcmp(L"Hello world", L"Hello kitty!");
			nCompare = 0;

			GAIA::ALGORITHM::strcpy(sz, L"Helloword");
			GAIA::ALGORITHM::strcat(sz, L"My name is arm!");
			GAIA::N32 nCmp = GAIA::ALGORITHM::strcmp(sz, L"Helloxitty");
			nCmp = GAIA::ALGORITHM::strcmp(sz, sz);
			GAIA::ALGORITHM::strcpy(sz, L"Helloworld");
			GAIA::GTCH* pResult = GAIA::ALGORITHM::strstr(sz, L"lo");
			pResult = GAIA::ALGORITHM::strmch(sz, L"Hel");
			sz[0] = 0;
		}
		TEST_END;
	}

	// Chars class test.
	{
		TEST_BEGIN("<Chars class test>");
		{
			GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::UM, 128> chars;
			chars = "abc";
			chars += "123";
			chars = 123.456F;
			GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::UM, 128> chars1;
			chars1 = "3.4";
			GAIA::UM u = chars.find('3', 0);
			u = chars.find(chars1, 0);
			u = chars.rfind('4', chars.size() - 1);
			chars.clear();
			chars1.clear();

			bFunctionSuccess = GAIA::True;
			chars = "abc";
			chars.insert('m', 1);
			if(chars != "ambc")
				bFunctionSuccess = GAIA::False;
			chars.clear();
			chars.insert('a', 0);
			if(chars != "a")
				bFunctionSuccess = GAIA::False;
			chars.insert('b', 1);
			if(chars != "ab")
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("insert test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("insert test FAILED!");
		}
		TEST_END;
	}

	// String class test.
	{
		TEST_BEGIN("<String class test>");
		{
			GAIA::CONTAINER::BasicString<GAIA::GTCH, GAIA::UM> str;
			str = L"Hello world!";
			str += L" Hello kitty!";
			str = 32;
			str = 123.456;
			GAIA::UM u = str.find('2', 0);
			u = str.find(L"3.4", 0);
			GAIA::CONTAINER::BasicString<GAIA::GTCH, GAIA::UM> str1 = L"3.4";
			u = str.find(str1, 0);
			GAIA::REAL r = str;
			r = 0.0F;

			bFunctionSuccess = GAIA::True;
			str = L"abc";
			str.insert('m', 1);
			if(str != L"ambc")
				bFunctionSuccess = GAIA::False;
			str.clear();
			str.insert('a', 0);
			if(str != L"a")
				bFunctionSuccess = GAIA::False;
			str.insert('b', 1);
			if(str != L"ab")
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("insert test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("insert test FAILED!");
		}
		TEST_END;
	}

	// BasicQueue test.
	{
		TEST_BEGIN("<Basic queue test>");
		{
			typedef GAIA::CONTAINER::BasicQueue<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __QueueType;
			__QueueType que;
			for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
				que.push(x);
			for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
				que.pop();
			que.push(10);
			que.front();
			GAIA_AST(que.size() == 1);
			__QueueType newque = que;

			__QueueType::it fit = newque.front_it();
			__QueueType::const_it cfit = newque.const_front_it();
			__QueueType::it bit = newque.back_it();
			__QueueType::const_it cbit = newque.const_back_it();
			++fit;
			--fit;
			++cfit;
			--cfit;
			++bit;
			--bit;
			++cbit;
			--cbit;
		}
		TEST_END;
	}

	// BasicOrderless test.
	{
		TEST_BEGIN("<Basic orderless test>");
		{
			GAIA::CONTAINER::BasicOrderless<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > ol;
			GAIA::U32 u0 = ol.insert(32);
			GAIA::U32 u1 = ol.insert(48);
			ol.erase(u0);
			ol.erase(u1);
		}
		TEST_END;
	}

	// BasicPool test.
	{
		TEST_BEGIN("<Basic pool test>");
		{
			GAIA::CONTAINER::BasicPool<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > pool;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				pool.alloc();
			pool.clear();
			pool.destroy();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				pool.alloc();
		}
		TEST_END;
	}

	// GAIA sort algorithm test.
	{
		TEST_BEGIN("<Sort algorithm test>");
		{
			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < 100; ++x)
				listGAIA.push_back(GAIA::MATH::random());
			GAIA::ALGORITHM::bsort(&listGAIA[0], &listGAIA[listGAIA.size() - 1]);
			GAIA::N32 nOldValue = -1;
			for(GAIA::N32 x = 0; x < 100; ++x)
			{
				if(nOldValue > listGAIA[x])
				{
					bFunctionSuccess = GAIA::False;
					break;
				}
				nOldValue = listGAIA[x];
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("GAIA bsort is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("GAIA bsort is FAILED!");

			GAIA::CONTAINER::BasicArray<GAIA::N32, GAIA::N32, 2> arrGAIA;
			arrGAIA.push_back(2);
			arrGAIA.push_back(1);
			arrGAIA.sort();
			arrGAIA.clear();
			arrGAIA.push_back(1);
			arrGAIA.push_back(2);
			arrGAIA.sort();
			arrGAIA.clear();
			arrGAIA.push_back(1);
			arrGAIA.push_back(1);
			arrGAIA.sort();
		}
		TEST_END;
	}

	// GAIA sort and search function test.
	{
		TEST_BEGIN("<Sort function test>");
		{
			bFunctionSuccess = GAIA::True;
			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				listGAIA.push_back(GAIA::MATH::random());
			listGAIA.sort();
			GAIA::N32 nOldValue = -1;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				if(nOldValue > listGAIA[x])
				{
					bFunctionSuccess = GAIA::False;
					break;
				}
				nOldValue = listGAIA[x];
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("GAIA vector's sort is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("GAIA vector's sort is FAILED!");
		}
		TEST_END;

		TEST_BEGIN("<Search function test>");
		{
			bFunctionSuccess = GAIA::True;
			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				listGAIA.push_back(x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				if(listGAIA.search(x) != x)
				{
					bFunctionSuccess = GAIA::False;
					break;
				}
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("GAIA search is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("GAIA search is FAILED!");
		}
		TEST_END;
	}

	// Sort and search function performance compare.
	{
#ifdef PERFORMANCE_COMPARE
		TEST_BEGIN("<Sort function performance>");
		{
			std::vector<GAIA::N32> listSTL;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				listSTL.push_back(GAIA::MATH::random());
			PERF_START("STL sort use");
			std::sort(listSTL.begin(), listSTL.end());
			PERF_END;

			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				listGAIA.push_back(GAIA::MATH::random());
			PERF_START("GAIA sort use");
			if(!listGAIA.empty())
				GAIA::ALGORITHM::sort(&listGAIA[0], &listGAIA[listGAIA.size() - 1]);
			PERF_END;

			PERF_START("STL bsearch use");
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				binary_search(listSTL.begin(), listSTL.end(), listSTL[x]);
			PERF_END;

			PERF_START("GAIA bsearch use");
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				GAIA::ALGORITHM::search(&listGAIA[0], &listGAIA[listGAIA.size() - 1], listGAIA[x]);
			PERF_END;
		}
		TEST_END;
#endif
	}

	// BasicList function test.
	{
		TEST_BEGIN("<BasicList Function Test>");
		{
			typedef GAIA::CONTAINER::BasicList<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __ListType;
			__ListType list;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.push_back(x);
			__ListType::it iter = list.front_it();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.erase(iter);
			list.destroy();
			list.clear();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.push_front(x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.pop_front();
			if(!list.empty())
				TEST_FILE_LINE("list front push pop operator FAILED!");
			iter = list.front_it();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.insert(iter, x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.pop_back();
			if(!list.empty())
				TEST_FILE_LINE("list back push pop operator FAILED!");
		}
		TEST_END;
	}
	
	// BasicAVLTree test.
	{
		TEST_BEGIN("<BasicAVLTree Function Test>");
		{
			GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > btr;

			bFunctionSuccess = GAIA::True;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				GAIA::BL bResult = btr.insert(x);
				GAIA_AST(bResult);
				if(!bResult)
					bFunctionSuccess = GAIA::False;
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("Insert by key operator is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Insert by key operator is FAILED!");
			GAIA::BL bCheckParent = btr.dbg_check_parent();
			bCheckParent = true;
			GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::U32, GAIA::U16,GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> >::it iter = btr.front_it();
			while(!iter.empty())
			{
				GAIA::N32 n = *iter;
				n = 0;
				++iter;
			}
			iter = btr.back_it();
			while(!iter.empty())
			{
				GAIA::N32 n = *iter;
				n = 0;
				--iter;
			}

			bFunctionSuccess = GAIA::True;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				GAIA::N32* pFinded = btr.find(x);
				GAIA_AST(pFinded != GNULL);
				if(pFinded == GNULL)
					bFunctionSuccess = GAIA::False;
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("Exist by key operator is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Exist by key operator is FAILED!");

			bFunctionSuccess = GAIA::True;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				GAIA::BL bResult = btr.erase(x);
				GAIA_AST(bResult);
				bResult = GAIA::True;
				if(!bResult)
					bFunctionSuccess = GAIA::False;
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("Erase element by key operator is SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Erase element by key operator is FAILED!");

			btr.clear();
			GAIA::CONTAINER::Vector<GAIA::N32> listSample;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				GAIA::N32 nRand = GAIA::MATH::random();
				btr.insert(nRand);
				listSample.push_back(nRand);
			}
			bFunctionSuccess = GAIA::True;
			for(GAIA::N32 x = 0; x < listSample.size(); ++x)
			{
				if(btr.find(listSample[x]) == GNULL)
					bFunctionSuccess = GAIA::False;
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("Random data insertion and find AVL-Tree function check SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Random data insertion and find AVL-Tree function check FAILED!");

			for(GAIA::N32 x = 0; x < listSample.size(); x += 10)
				btr.erase(listSample[x]);

			if(btr.dbg_check_balance())
				TEST_FILE_LINE("Check AVL-Tree balance SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Check AVL-Tree balance FAILED!");

			if(btr.dbg_check_parent())
				TEST_FILE_LINE("Check AVL-Tree parent SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Check AVL-Tree parent FAILED!");

			for(GAIA::N32 x = 0; x < listSample.size(); x += 10)
				btr.insert(listSample[x]);

			listSample.sort();
			bFunctionSuccess = GAIA::True;
			GAIA::N32 n = -1;
			for(GAIA::N32 x = 0; x < listSample.size(); ++x)
			{
				if(listSample[x] == n)
					continue;
				if(!btr.erase(listSample[x]))
					bFunctionSuccess = GAIA::False;
				n = listSample[x];
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("Random data insertion and erase AVL-Tree function check SUCCESSFULLY!");
			else
				TEST_FILE_LINE("Random data insertion and erase AVL-Tree function check FAILED!");

			{
				typedef GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __AVLTreeType;
				__AVLTreeType av;
				for(GAIA::N32 x = 0; x < 100; ++x)
					av.insert(x);
				__AVLTreeType::it iter = av.lower_bound(32);
				GAIA::N32 nCount = 0;
				while(!iter.empty())
				{
					++iter;
					++nCount;
				}
				if(nCount != 68)
					TEST_FILE_LINE("Lower bound function FAILED!");
				iter = av.upper_bound(32);
				nCount = 0;
				while(!iter.empty())
				{
					--iter;
					++nCount;
				}
				if(nCount != 33)
					TEST_FILE_LINE("Upper bound function FAILED!");
			}
		}
		TEST_END;
	}

	// BasicAVLTree performance compare.
	{
#ifdef PERFORMANCE_COMPARE
		TEST_BEGIN("<BasicAVLTree performance>");
		{
			PERF_START("STL set use");
			std::set<GAIA::N32> setSTL;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				setSTL.insert(GAIA::MATH::random());
			PERF_END;

			PERF_START("GAIA BasicAVLTree use");
			GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > avltree;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				avltree.insert(GAIA::MATH::random());
			PERF_END;
		}
		TEST_END;
#endif
	}
	
	// BasicMultiAVLTree function test.
	{
		TEST_BEGIN("<BasicMultiAVLTree function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMultiAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MAVLTreeType;
			__MAVLTreeType mavlt;
			if(!mavlt.insert(32))
				bFunctionSuccess = GAIA::False;
			if(!mavlt.insert(32))
				bFunctionSuccess = GAIA::False;
			if(mavlt.empty())
				bFunctionSuccess = GAIA::False;
			if(mavlt.size() != 2)
				bFunctionSuccess = GAIA::False;
			if(mavlt.capacity() == 0)
				bFunctionSuccess = GAIA::False;
			if(mavlt.find(32) == GNULL)
				bFunctionSuccess = GAIA::False;
			if(!mavlt.erase(32))
				bFunctionSuccess = GAIA::False;
			if(mavlt.erase(32))
				bFunctionSuccess = GAIA::False;
			mavlt.clear();
			mavlt.destroy();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				if(!mavlt.insert(x))
					bFunctionSuccess = GAIA::False;
				if(!mavlt.insert(x))
					bFunctionSuccess = GAIA::False;
			}
			GAIA::N32* pMinimize = mavlt.minimize();
			if(pMinimize == GNULL)
				bFunctionSuccess = GAIA::False;
			GAIA::N32* pMaximize = mavlt.maximize();
			if(pMaximize == GNULL)
				bFunctionSuccess = GAIA::False;
			__MAVLTreeType::it iter = mavlt.front_it();
			if(iter.empty())
				bFunctionSuccess = GAIA::False;
			while(!iter.empty())
				++iter;
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicMultiAVLTree function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicMultiAVLTree function test FAILED!");
		}
		TEST_END;
	}

	// BasicTrieTree function test.
	{
		TEST_BEGIN("<BasicTrieTree function test>");
		{
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __TrieTree;
			__TrieTree tt;
			tt.insert("hello", 5);
			tt.insert("world", 5);
			tt.insert("kitty", 5);
			{
				__TrieTree::it fit = tt.front_it(); ++fit; --fit;
				__TrieTree::it bit = tt.back_it(); ++bit; --bit;
				__TrieTree::const_it cfit = tt.const_front_it(); ++cfit; --cfit;
				__TrieTree::const_it cbit = tt.const_back_it(); ++cbit; --cbit;
				__TrieTree::it lb_it = tt.lower_bound("he", 2);
				__TrieTree::it ub_it = tt.upper_bound("he", 2);
				__TrieTree::const_it clb_it = (*(const __TrieTree*)&tt).lower_bound("he", 2);
				__TrieTree::const_it cub_it = (*(const __TrieTree*)&tt).upper_bound("he", 2);
			}
			GAIA::BL bErase = tt.erase("hello", 5);
			GAIA::BL bExist = tt.exist("hello", 5);
			__TrieTree::Node* pNode = tt.find(GNULL, "hello", 5);
			__TrieTree::__PathListType result_paths;
			tt.paths(GNULL, "hello", 5, result_paths);
			tt.empty();
			tt.size();
			tt.capacity();
			tt.clear();
			tt.destroy();
			bErase = GAIA::True;
			bExist = GAIA::True;
			pNode = GNULL;
			{
				__TrieTree::it fit = tt.front_it(); ++fit; --fit;
				__TrieTree::it bit = tt.back_it(); ++bit; --bit;
				__TrieTree::const_it cfit = tt.const_front_it(); ++cfit; --cfit;
				__TrieTree::const_it cbit = tt.const_back_it(); ++cbit; --cbit;
				__TrieTree::it lb_it = tt.lower_bound("he", 2);
				__TrieTree::it ub_it = tt.upper_bound("he", 2);
				__TrieTree::const_it clb_it = (*(const __TrieTree*)&tt).lower_bound("he", 2);
				__TrieTree::const_it cub_it = (*(const __TrieTree*)&tt).upper_bound("he", 2);
			}
			tt.destroy();
			tt.insert("hello", 5);
			tt.insert("world", 5);
			tt.insert("you", 3);
			tt.insert("are", 3);
			tt.insert("not", 3);
			tt.insert("prepared", 8);
			tt.insert("pre", 3);
			tt.insert("product", 7);
			__TrieTree::it iter = tt.upper_bound("product", 7);
			while(!iter.empty())
			{
				__TrieTree::it itertemp = iter;
				GAIA::GCH szTemp[240];
				GAIA::GCH* p = szTemp;
				while(!itertemp.empty())
				{
					*p++ = *itertemp;
					itertemp = tt.parent_it(itertemp);
				}
				GAIA::ALGORITHM::inverse(szTemp, p - 1);
				szTemp[p - szTemp] = 0;
				PERF_PRINT_LINE(szTemp);
				--iter;
			}
		}
		TEST_END;
	}

	// BasicTrieTree performance test.
	{
	#ifdef PERFORMANCE_COMPARE
		TEST_BEGIN("<BasicTrieTree performance test>");
		{
			typedef GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::N64>, GAIA::N64, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U64> > __StringList;
			__StringList listString;
			GAIA::FILESYSTEM::File file;
			if(file.Open("main.cpp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ))
			{
				GAIA::N64 nSize = file.Size();
				if(nSize > 0)
				{
					GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::N64> str;
					str.resize(nSize);
					file.Read(str.front_ptr(), nSize);
					while(GAIA::ALWAYSTRUE)
					{
						while(GAIA::ALWAYSTRUE)
						{
							GAIA::BL bMatch = GAIA::True;
							while(str.trim_left("\r\n"))
								bMatch = GAIA::False;
							while(str.trim_left(' '))
								bMatch = GAIA::False;
							while(str.trim_left('\t'))
								bMatch = GAIA::False;
							if(bMatch)
								break;
						}
						GAIA::N64 index = 0;
						while(GAIA::ALWAYSTRUE)
						{
							if(	str[index] == 0 || 
								str[index] == ' ' || 
								str[index] == '\t' || 
								str[index] == '\n' || 
								str[index] == '\r')
								break;
							++index;
						}
						if(index == 0)
							break;
						GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::N64> strTemp = str;
						strTemp.left(index);
						str.trim_left(index);
						listString.push_back(strTemp);
					}
				}
				file.Close();
			}

			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __TrieTree;
			__TrieTree tt;

			PERF_START("TrieTree Insert");
			{
				for(__StringList::_sizetype x = 0; x < listString.size(); ++x)
					tt.insert(listString[x].front_ptr(), (GAIA::N32)listString[x].size() * sizeof(__StringList::_datatype::_datatype));
			}
			PERF_END;

			PERF_START("TrieTree find and count test.");
			{
				for(__StringList::_sizetype x = 0; x < listString.size(); ++x)
				{
					__TrieTree::Node* pNode = tt.find(GNULL, listString[x].front_ptr(), (GAIA::N32)listString[x].size() * sizeof(__StringList::_datatype::_datatype));
					if(pNode != GNULL)
					{
						__TrieTree::_sizetype c = tt.count(*pNode);
						__TrieTree::_sizetype cc = tt.catagory_count(*pNode);
						__TrieTree::_sizetype fc = tt.full_count(*pNode);
						c = cc = fc = 0;
					}
					else
						GAIA_AST(GAIA::False);
				}
			}
			PERF_END;
		}
		TEST_END;
	#endif
	}

	// BasicTree function test.
	{
		TEST_BEGIN("<BasicTree function test>");
		{
			typedef GAIA::CONTAINER::BasicTree<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > _MyTreeType;
			_MyTreeType tree;
			_MyTreeType::Node* pNode = tree.insert(10, GNULL);
			tree.insert(20, pNode);
			_MyTreeType::Node* pChildNode = tree.insert(30, pNode);
			tree.insert(40, pNode);
			_MyTreeType::Node* pChildChild = tree.insert(40, pChildNode);
			_MyTreeType::__NodeListType listResult;

			tree.find(GNULL, 40, listResult);
			if(listResult.size() == 2)
				TEST_FILE_LINE("basic tree find SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic tree find FAILED!");

			GAIA::BL bResult = tree.link(*pNode, *pChildChild);
			if(bResult)
				TEST_FILE_LINE("basic tree link function SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic tree link function FAILED!");

			bResult = tree.unlink(*pNode, *pChildChild);
			if(bResult)
				TEST_FILE_LINE("basic tree unlink function SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic tree unlink function FAILED!");

			bResult = tree.islinked(*pNode, *pChildChild);
			if(!bResult)
				TEST_FILE_LINE("basic tree islinked function SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic tree islinked function FAILED!");

			bResult = tree.link(*pNode, *pChildChild);
			if(bResult)
				TEST_FILE_LINE("basic tree link function SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic tree link function FAILED!");

			tree.erase(*pChildChild);
			tree.erase(*pNode);
			_MyTreeType::it fit = tree.front_it(); ++fit; --fit;
			_MyTreeType::it bit = tree.back_it(); ++bit; --bit;
			_MyTreeType::const_it cfit = tree.const_front_it(); ++cfit; --cfit;
			_MyTreeType::const_it cbit = tree.const_back_it(); ++cbit; --cbit;
		}
		TEST_END;
	}
	
	// BasicPriQueue function test.
	{
		TEST_BEGIN("<BasicPriQueue function test>");
		{
			typedef GAIA::CONTAINER::BasicPriQueue<SNode<GAIA::N32>, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __PriQueueType;
			typedef GAIA::CONTAINER::BasicVector<SNode<GAIA::N32>, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __VectorType;
			__PriQueueType pq;
			__VectorType vr;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				__PriQueueType::_datatype t;
				*t = x;
				pq.insert(t);
				vr.push_back(t);
			}
			bFunctionSuccess = GAIA::True;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				if(pq.front() != vr[x])
					bFunctionSuccess = GAIA::False;
				pq.pop_front();
			}
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicPriQueue insert and pop_front SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicPriQueue insert and pop_front FAILED!");
		}
		TEST_END;
	}
	
	// BasicSet function test.
	{
		TEST_BEGIN("<BasicSet function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicSet<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __SetType;
			__SetType st;
			if(!st.insert(1))
				bFunctionSuccess = GAIA::False;
			if(!st.insert(2))
				bFunctionSuccess = GAIA::False;
			if(!st.insert(3))
				bFunctionSuccess = GAIA::False;
			if(st.insert(1))
				bFunctionSuccess = GAIA::False;
			GAIA::N32 n = *st.find(1);
			if(n != 1)
				bFunctionSuccess = GAIA::False;
			n = *st.find(2);
			if(n != 2)
				bFunctionSuccess = GAIA::False;
			n = *st.find(3);
			if(n != 3)
				bFunctionSuccess = GAIA::False;
			n = 0;
			st.clear();
			st.insert(1);
			st.insert(5);
			st.insert(12);
			st.insert(2);
			st.insert(3);
			__SetType::it iterl = st.lower_bound(4);
			__SetType::it iteru = st.upper_bound(16);
			if(*iterl != 5)
				bFunctionSuccess = GAIA::False;
			if(*iteru != 12)
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicSet function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicSet function test FAILED!");
		}
		TEST_END;
	}

	// BasicMultiSet function test.
	{
		TEST_BEGIN("<BasicMultiSet function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMultiSet<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MultiSetType;
			__MultiSetType mst;
			if(!mst.insert(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.insert(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.erase(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.empty())
				bFunctionSuccess = GAIA::False;
			if(!mst.empty())
				bFunctionSuccess = GAIA::False;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				mst.insert(x);
				mst.insert(x);
			}
			GAIA::N32 nSize = mst.size();
			GAIA::N32 nCapacity = mst.capacity();
			__MultiSetType::__DataListType lr;
			if(!mst.find(16, lr))
				bFunctionSuccess = GAIA::False;
			mst.clear();
			mst.destroy();
			nSize = 0;
			nCapacity = 0;
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicMultiSet function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicMultiSet function test FAILED!");
		}
		TEST_END;
	}
	
	// BasicMap function test.
	{
		TEST_BEGIN("<BasicMap function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMap<GAIA::N32, GAIA::CONTAINER::AString, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MapType;
			__MapType mp;
			*mp["Arm"] = 30;
			*mp["Box"] = 30;
			*mp["NeedLight"] = 32;
			GAIA::N32 n = *mp["Arm"];
			if(n != 30)
				bFunctionSuccess = GAIA::False;
			n = *mp["Box"];
			if(n != 30)
				bFunctionSuccess = GAIA::False;
			n = *mp["NeedLight"];
			if(n != 32)
				bFunctionSuccess = GAIA::False;
			n = 0;
			mp.erase("Arm");
			mp.clear();
			mp.destroy();
			*mp["c"] = 32;
			*mp["b"] = 16;
			*mp["a"] = 22;
			*mp["d"] = 1;
			*mp["f"] = 2;
			__MapType::it iterl = mp.lower_bound("f");
			__MapType::it iteru = mp.lower_bound("b");
			if(*iterl != 2)
				bFunctionSuccess = GAIA::False;
			if(*iteru != 16)
				bFunctionSuccess = GAIA::False;
			iterl = mp.front_it();
			iteru = mp.back_it();
			if(*iterl != 22)
				bFunctionSuccess = GAIA::False;
			if(*iteru != 2)
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicMap function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicMap function test FAILED!");

			{
				bFunctionSuccess = GAIA::True;
				typedef GAIA::CONTAINER::BasicMap<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MapType;
				__MapType mp;
				GAIA::MATH::random_seed(0);
				for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				{
					GAIA::N32 n = (GAIA::MATH::random() | (GAIA::MATH::random() << 16));
					*mp[n] = n;
				}
				GAIA::MATH::random_seed(0);
				for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				{
					GAIA::N32 n = (GAIA::MATH::random() | (GAIA::MATH::random() << 16));
					if(*mp[n] != n)
						bFunctionSuccess = GAIA::False;
				}
			}
		}
		TEST_END;
	}

	// BasicMultiMap function test.
	{
		TEST_BEGIN("<BasicMultiMap function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMultiMap<GAIA::N32, GAIA::CONTAINER::AString, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MultiMapType;
			__MultiMapType mmp;
			mmp.insert("Arm", 30);
			mmp.insert("Arm", 31);
			mmp.insert("NeedLight", 32);
			mmp.insert("Box", 30);
			mmp.erase("Arm");
			mmp.clear();
			mmp.destroy();
			if(bFunctionSuccess)
				TEST_FILE_LINE("BasicMultiMap function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("BasicMultiMap function test FAILED!");
		}
		TEST_END;
	}
	
	// BasicGraph function test.
	{
		TEST_BEGIN("<BasicGraph function test>");
		{
			typedef GAIA::CONTAINER::BasicGraph<GAIA::REAL, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > _MyGraphType;
			_MyGraphType graph;
			_MyGraphType::Node* pNode = GNULL;
			for(GAIA::N32 x = 0; x < 100; ++x)
				pNode = graph.insert((GAIA::REAL)x, pNode);
			_MyGraphType::__NodeListType listResult;
			graph.find(GNULL, 3.0, listResult);
			if(listResult.empty())
				TEST_FILE_LINE("basic graph find FAILED!");
			else
				TEST_FILE_LINE("basic graph find SUCCESSFULLY!");

			{
				listResult.clear();
				graph.find(GNULL, 8.0F, listResult);
				if(!listResult.empty())
				{
					_MyGraphType::Node* pNode1 = listResult[0];
					if(pNode1 == GNULL)
						TEST_FILE_LINE("basic graph find FAILED!");
					graph.insert(80.0F, listResult[0]);
				}
				else
					TEST_FILE_LINE("basic graph find FAILED!");
				listResult.clear();
				graph.find(GNULL, 80.0F, listResult);
				if(!listResult.empty())
				{
					_MyGraphType::Node* pNode2 = listResult[1];
					if(pNode2 == GNULL)
						TEST_FILE_LINE("basic graph find FAILED!");
				}
				else
					TEST_FILE_LINE("basic graph find FAILED!");
			}

			{
				/*
				 *	1-------2
				 *	|     / | \
				 *	|   /   |  3
				 *	| /     | /
				 *	5-------4
				 */

				graph.destroy();
				_MyGraphType::Node* pNode0 = graph.insert(0.0F, GNULL);
				_MyGraphType::Node* pNode1 = graph.insert(1.0F, GNULL);
				_MyGraphType::Node* pNode2 = graph.insert(2.0F, GNULL);
				_MyGraphType::Node* pNode3 = graph.insert(3.0F, GNULL);
				_MyGraphType::Node* pNode4 = graph.insert(4.0F, GNULL);
				_MyGraphType::Node* pNode5 = graph.insert(5.0F, GNULL);
				graph.erase(*pNode0);
				graph.root(pNode1);
				graph.link(*pNode1, *pNode5);
				graph.link(*pNode1, *pNode2);
				graph.link(*pNode2, *pNode3);
				graph.link(*pNode2, *pNode4);
				graph.link(*pNode2, *pNode5);
				graph.link(*pNode3, *pNode4);
				graph.link(*pNode4, *pNode5);
				_MyGraphType::__NodeListType listResult1;
				graph.find(GNULL, 5.0F, listResult1);
				_MyGraphType::__NodeListType listResult2;
				graph.find(GNULL, 3.0F, listResult2);
				if(!listResult1.empty() && !listResult2.empty())
				{
					_MyGraphType::__NodeListType listResultNode;
					graph.navpath<GAIA::REAL, 5>(*listResult1[0], *listResult2[0], 3, listResultNode);
					graph.navpath<GAIA::REAL, 5>(*listResult1[0], 4.0F, 3, listResultNode);

					_MyGraphType::__PathTreeType treeResult;
					graph.paths(*listResult1[0], *listResult2[0], treeResult);
					if(treeResult.empty())
						TEST_FILE_LINE("basic graph path from one node to another FAILED!");
					_MyGraphType::__PathTreeType::__PathListType pathlist;
					treeResult.paths(GNULL, pathlist);
					for(_MyGraphType::__PathTreeType::__PathListType::_sizetype x = 0; x < pathlist.size(); ++x)
					{
						_MyGraphType::__PathTreeType::__PathListType::_datatype& path = pathlist[x];
						for(_MyGraphType::__PathTreeType::__PathListType::_datatype::_sizetype y = 0; y < path.size(); ++y)
						{
							_MyGraphType::__PathTreeType::Node* pTreeNode = path[y];
							GAIA_AST(pTreeNode != GNULL);
							_MyGraphType::Node* pNode = **pTreeNode;
							GAIA_AST(pNode != GNULL);
							if(pNode != GNULL)
							{
								_MyGraphType::_datatype data = **pNode;
#ifdef PERFORMANCE_COMPARE
								std::cout << data << " ";
#endif
								GAIA::N32 nDebug = 0;
								nDebug = 0;
							}
						}
#ifdef PERFORMANCE_COMPARE
						std::cout << std::endl;
#endif
					}
					if(pathlist.size() != 6)
						TEST_FILE_LINE("basic graph paths FAILED!");
				}
				else
					TEST_FILE_LINE("basic graph find FAILED!");

				_MyGraphType::__LinkListType listLinkResult;
				graph.collect_link_list(listLinkResult);
				if(listLinkResult.empty())
					TEST_FILE_LINE("collect graph link list FAILED!");
			}

			{
				/*
				 *	3
				 *     \
				 *		1-------2
				 *		|     / | \
				 *		|   /   |  3
				 *		| /     | /
				 *		5-------4
				 */
#ifdef PERFORMANCE_COMPARE
				std::cout << std::endl;
#endif
				graph.destroy();
				_MyGraphType::Node* pNode0 = graph.insert(0.0F, GNULL);
				_MyGraphType::Node* pNode1 = graph.insert(1.0F, GNULL);
				_MyGraphType::Node* pNode2 = graph.insert(2.0F, GNULL);
				_MyGraphType::Node* pNode3 = graph.insert(3.0F, GNULL);
				_MyGraphType::Node* pNode4 = graph.insert(4.0F, GNULL);
				_MyGraphType::Node* pNode5 = graph.insert(5.0F, GNULL);
				_MyGraphType::Node* pNode33= graph.insert(3.0F, GNULL);
				graph.erase(*pNode0);
				graph.root(pNode1);
				graph.link(*pNode1, *pNode5);
				graph.link(*pNode1, *pNode2);
				graph.link(*pNode2, *pNode3);
				graph.link(*pNode2, *pNode4);
				graph.link(*pNode2, *pNode5);
				graph.link(*pNode3, *pNode4);
				graph.link(*pNode4, *pNode5);
				graph.link(*pNode1, *pNode33);
				_MyGraphType::__NodeListType listResult1;
				graph.find(GNULL, 5.0F, listResult1);
				if(!listResult1.empty())
				{
					_MyGraphType::__PathTreeType treeResult;
					graph.paths(*listResult1[0], 3.0F, treeResult);
					if(treeResult.empty())
						TEST_FILE_LINE("basic graph path from one node to another FAILED!");
					_MyGraphType::__PathTreeType::__PathListType pathlist;
					treeResult.paths(GNULL, pathlist);
					for(_MyGraphType::__PathTreeType::__PathListType::_sizetype x = 0; x < pathlist.size(); ++x)
					{
						_MyGraphType::__PathTreeType::__PathListType::_datatype& path = pathlist[x];
						for(_MyGraphType::__PathTreeType::__PathListType::_datatype::_sizetype y = 0; y < path.size(); ++y)
						{
							_MyGraphType::__PathTreeType::Node* pTreeNode = path[y];
							GAIA_AST(pTreeNode != GNULL);
							_MyGraphType::Node* pNode = **pTreeNode;
							GAIA_AST(pNode != GNULL);
							if(pNode != GNULL)
							{
								_MyGraphType::_datatype data = **pNode;
#ifdef PERFORMANCE_COMPARE
								std::cout << data << " ";
#endif
								GAIA::N32 nDebug = 0;
								nDebug = 0;
							}
						}
#ifdef PERFORMANCE_COMPARE
						std::cout << std::endl;
#endif
					}
					if(pathlist.size() != 9)
						TEST_FILE_LINE("basic graph paths FAILED!");
				}
				else
					TEST_FILE_LINE("basic graph find FAILED!");

				_MyGraphType::__PoolType::__IndexListType listIndex;
				graph.collect_valid_index_list(listIndex);
				for(_MyGraphType::__PoolType::__IndexListType::_sizetype x = 0; x < listIndex.size(); ++x)
				{
					_MyGraphType::__PoolType::__IndexListType::_sizetype index = listIndex[x];
					_MyGraphType::Node& n = graph[index];
					if(*n == 5.0F)
					{
					}
				}
			}

			if(graph.dbg_check_traveling())
				TEST_FILE_LINE("basic graph debug check traveling SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic graph debug check traveling FAILED!");

			if(graph.dbg_check_relation())
				TEST_FILE_LINE("basic graph debug check relation SUCCESSFULLY!");
			else
				TEST_FILE_LINE("basic graph debug check relation FAILED!");
		}
		TEST_END;
	}

	// Storage test.
	{
		TEST_BEGIN("<Storage test>");
		{
			typedef GAIA::CONTAINER::Storage<GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>, 32> __StorageType;
			__StorageType st;
			bFunctionSuccess = GAIA::True;
			if(!st.increase_reserve(10000, 1024 * 1024 * __StorageType::_pagesize))
				bFunctionSuccess = GAIA::False;
			__StorageType::Node n;
			if(!st.insert(40, n))
				bFunctionSuccess = GAIA::False;
			if(!st.erase(n.head()))
				bFunctionSuccess = GAIA::False;
			if(st.capacity() != 1024 * 1024 * __StorageType::_pagesize)
				bFunctionSuccess = GAIA::False;
			st.clear();
			typedef GAIA::CONTAINER::Vector<GAIA::NM> __VectorType;
			__VectorType vt;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			{
				GAIA::N32 nSize = GAIA::MATH::random() % 256 + 1;
				if(!st.insert(nSize, n))
					bFunctionSuccess = GAIA::False;
				vt.push_back(n.head());
			}
			for(GAIA::N32 x = 0; x < vt.size(); x += 2)
			{
				if(!st.erase(vt[x]))
				{
					std::cout << x << std::endl;
					bFunctionSuccess = GAIA::False;
					break;
				}
			}
			for(GAIA::N32 x = 1; x < vt.size(); x += 2)
			{
				if(!st.erase(vt[x]))
				{
					std::cout << x << std::endl;
					bFunctionSuccess = GAIA::False;
					break;
				}
			}
			if(st.capacity() != 1024 * 1024 * __StorageType::_pagesize)
				bFunctionSuccess = GAIA::False;
			if(bFunctionSuccess)
				TEST_FILE_LINE("storage function test SUCCESSFULLY!");
			else
				TEST_FILE_LINE("storage function test FAILED!");
		}
		TEST_END;
	}

	// Basic math test.
	{
		TEST_BEGIN("<Basic math test>");
		{
			GAIA::REAL f = GAIA::MATH::xcos(10.0F);
			f = 0.0F;
		}
		TEST_END;
	}
	
	// VEC2 math cookies test.
	{
		GAIA::MATH::VEC2<GAIA::REAL> v0(1.0);
		GAIA::MATH::VEC2<GAIA::N32> v1(1, 2.0F);
		GAIA::MATH::VEC2<GAIA::REAL> v2 = v0;
		v2.normalize();
		GAIA::MATH::VEC2<GAIA::REAL> v4 = v1 + v2;
		v4 = 0.0F;
		if(v1 == v2)
		{
		}
	}

	// Thread test.
	{
		TEST_BEGIN("<Thread test>");
		{
			MyThread thread;
			thread.Run();
			thread.Wait();
			GAIA_AST(thread.IsRuned());
		}
		TEST_END;
	}

	// File test.
	{
		TEST_BEGIN("<File test>");
		{
			GAIA::FILESYSTEM::File file;
			GAIA::BL bResult = file.Open("filetest.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
			file.Write(L"My name is Armterla!");
			bResult = file.Close();
			bResult = file.Open("filetest.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ);
			GAIA::U64 uFileSize = file.Size();
			GAIA::CONTAINER::BasicBuffer<GAIA::U64, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U64> > buf;
			buf.resize(uFileSize);
			file.Read(buf.front_ptr(), buf.write_size());
			const GAIA::GWCH* p = (GAIA::GWCH*)buf.front_ptr();
			GAIA::GWCH szTemp[1024];
			GAIA::ALGORITHM::strcpy(szTemp, p);
			GAIA::N32 nDebug = 0;
			nDebug = 0;
		}
		TEST_END;
	}
	
	// Network test.
	{
		TEST_BEGIN("<Network function test>");
		{
			bFunctionSuccess = GAIA::True;

			GAIA::GCH szTemp[64];
			{
				GAIA::NETWORK::IP ip;
				ip.Invalid();
				ip.FromString("192.168.1.1");
				if(ip.u0 != 192 || ip.u1 != 168 || ip.u2 != 1 || ip.u3 != 1)
					bFunctionSuccess = GAIA::False;
				ip.ToString(szTemp);
				if(GAIA::ALGORITHM::strcmp(szTemp, "192.168.1.1") != 0)
					bFunctionSuccess = GAIA::False;
				ip.IsInvalid();
			}

			{
				GAIA::NETWORK::NetworkAddress na;
				na.Invalid();
				na.FromString("192.168.1.8:4321");
				if(na.ip.u0 != 192 || na.ip.u1 != 168 || na.ip.u2 != 1 || na.ip.u3 != 8)
					bFunctionSuccess = GAIA::False;
				na.ToString(szTemp);
				if(GAIA::ALGORITHM::strcmp(szTemp, "192.168.1.8:4321") != 0)
					bFunctionSuccess = GAIA::False;
				na.IsInvalid();
			}

			{
				GAIA::NETWORK::NetworkHandle h;
				GAIA::NETWORK::NetworkListener l;
				GAIA::NETWORK::NetworkSender s;
				GAIA::NETWORK::NetworkReceiver r;
			}

			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				WSAData wsadata;
				WSAStartup(MAKEWORD(2, 2), &wsadata);
			#endif

				GAIA::CONTAINER::Vector<GAIA::NETWORK::IP> listResult;
				GAIA::GCH szHostName[128];
				GAIA::NETWORK::GetHostName(szHostName, 128);
				GAIA::NETWORK::GetHostIPList(szHostName, listResult);
				for(GAIA::N32 x = 0; x < listResult.size(); ++x)
				{
					GAIA::GCH szIP[128];
					listResult[x].ToString(szIP);
					PERF_PRINT_LINE(szIP);
				}

				MyNetworkHandle* pNewHandle = new MyNetworkHandle;
				MyNetworkHandle& h = *pNewHandle;
				MyNetworkListener l;
				GAIA::NETWORK::NetworkSender s;
				MyNetworkReceiver r;

				s.Begin();
				r.Begin();

				MyNetworkListener::ListenDesc descListen;
				descListen.addr.FromString("127.0.0.1:8765");
				l.SetDesc(descListen);
				l.Begin();

				GAIA::SYNC::sleep(1000);

				MyNetworkHandle::ConnectDesc descConn;
				descConn.addr.FromString("127.0.0.1:8765");
				descConn.bStabilityLink = GAIA::True;
				h.Connect(descConn);

				h.SetSender(&s);
				h.SetReceiver(&r);

				while(s_pNH == GNULL)
					GAIA::SYNC::sleep(1000);

				s_pNH->SetSender(&s);
				s_pNH->SetReceiver(&r);

				for(GAIA::U32 x = 0; x < 10; x++)
					h.Send((const GAIA::U8*)"Hello Kitty!", sizeof("Hello Kitty!"));

				GAIA::SYNC::sleep(1000);

				s.End();
				r.End();
				l.End();

				h.SetSender(GNULL);
				h.SetReceiver(GNULL);

				s_pNH->SetSender(GNULL);
				s_pNH->SetReceiver(GNULL);

				h.Release();
				s_pNH->Release();
			#if GAIA_OS == GAIA_OS_WINDOWS
				WSACleanup();
			#endif
			}

			if(bFunctionSuccess)
				TEST_FILE_LINE("IPAddress to or from string convert SUCCESSFULLY!");
			else
				TEST_FILE_LINE("IPAddress to or from string convert FAILED!");
		}
		TEST_END;
	}

	// Basic factory test 1.
	{
		TEST_BEGIN("<Data traffic test>");
		{
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;

			GAIA::DATATRAFFIC::TransmissionIDM* pTrans = dynamic_cast<GAIA::DATATRAFFIC::TransmissionIDM*>(pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_TRANSMISSION_IDM, GNULL));
			GAIA::DATATRAFFIC::GatewayMem* pGateway1 = dynamic_cast<GAIA::DATATRAFFIC::GatewayMem*>(pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_GATEWAY_MEM, GNULL));
			GAIA::DATATRAFFIC::GatewayMem* pGateway2 = dynamic_cast<GAIA::DATATRAFFIC::GatewayMem*>(pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_GATEWAY_MEM, GNULL));
			GAIA::DATATRAFFIC::RouteMem* pRoute = dynamic_cast<GAIA::DATATRAFFIC::RouteMem*>(pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_ROUTE_MEM, GNULL));

			pRoute->AddGateway(pGateway1);
			pRoute->AddGateway(pGateway2);
			pGateway1->AddRoute(pRoute);
			pGateway2->AddRoute(pRoute);
			pTrans->AddRoute(pRoute);

			pTrans->Run();
			pTrans->Wait();

			pRoute->RemoveGateway(pGateway1);
			pRoute->RemoveGateway(pGateway2);
			pGateway1->RemoveRoute(pRoute);

			GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*> listResult;
			pGateway2->CollectRoutes(listResult);
			for(GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>::_sizetype x = 0; x < listResult.size(); ++x)
			{
				pGateway2->RemoveRoute(listResult[x]);
				listResult[x]->Release();
			}

			pTrans->Release();
			pGateway1->Release();
			pGateway2->Release();
			pRoute->Release();

			delete pFactory;
		}
		TEST_END;
	}

	// Serializer test.
	{
		TEST_BEGIN("<Serializer test>");
		{
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			{
				{
					GAIA::SERIALIZER::Serializer* pSerializer = (GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
					{
						GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);	
						pFileIO->Open("io.tmp", GAIA::IO::IO::IO_TYPE_WRITE);

						pSerializer->BindIO(pFileIO);
						pFileIO->Release();

						GAIA::SERIALIZER::Serializer& sr = *pSerializer;
						GAIA::N32 n = 32;
						sr << n;

						typedef GAIA::CONTAINER::BasicArray<GAIA::N32, GAIA::N32, 32> __ArrayType;
						__ArrayType at;
						for(__ArrayType::_sizetype x = 0; x < 100; ++x)
							at.push_back(x);
						sr << at;

						typedef GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __VectorType;
						__VectorType vt;
						for(__VectorType::_sizetype x = 0; x < 100; ++x)
							vt.push_back(x);
						sr << vt;

						typedef GAIA::CONTAINER::AString __AStringType;
						__AStringType astr = "Hello World!";
						sr << astr;

						typedef GAIA::CONTAINER::AChars __ACharsType;
						__ACharsType achars = "Hello World!";
						sr << achars;

						typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __StackType;
						__StackType st;
						for(__StackType::_sizetype x = 0; x < 100; ++x)
							st.push(x);
						sr << st;

						typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __QueueType;
						__QueueType qt;
						for(__QueueType::_sizetype x = 0; x < 100; ++x)
							qt.push(x);
						sr << qt;

						typedef GAIA::CONTAINER::BasicList<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __ListType;
						__ListType lt;
						for(__ListType::_sizetype x = 0; x < 100; ++x)
							lt.push_back(x);
						sr << lt;

						typedef GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __AVLTreeType;
						__AVLTreeType avlt;
						for(__AVLTreeType::_sizetype x = 100; x > 0; --x)
							avlt.insert(x);
						sr << avlt;

						typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __TrieTreeType;
						__TrieTreeType triet;
						triet.insert("Hello World", sizeof("Hello World") - sizeof(GAIA::GCH));
						triet.insert("Hello Kitty", sizeof("Hello Kitty") - sizeof(GAIA::GCH));
						triet.insert("ThisIsGAIA", sizeof("ThisIsGAIA") - sizeof(GAIA::GCH));
						sr << triet;

						typedef GAIA::CONTAINER::BasicStackBitset<GAIA::N32, 32> __StackBitsetType;
						__StackBitsetType sbitsett;
						~sbitsett;
						sr << sbitsett;

						typedef GAIA::CONTAINER::BasicBitset<GAIA::N32> __BitsetType;
						__BitsetType bitsett;
						bitsett.resize(10);
						~bitsett;
						sr << bitsett;
					}
					pSerializer->Release();
				}

				{
					GAIA::SERIALIZER::Serializer* pSerializer = (GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
					{
						GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);
						pFileIO->Open("io.tmp", GAIA::IO::IO::IO_TYPE_READ);

						pSerializer->BindIO(pFileIO);
						pFileIO->Release();

						GAIA::SERIALIZER::Serializer& sr = *pSerializer;
						GAIA::N32 n = 32;
						sr >> n;

						typedef GAIA::CONTAINER::BasicArray<GAIA::N32, GAIA::N32, 32> __ArrayType;
						__ArrayType at;
						sr >> at;

						typedef GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __VectorType;
						__VectorType vt;
						sr >> vt;

						typedef GAIA::CONTAINER::AString __AStringType;
						__AStringType astr;
						sr >> astr;

						typedef GAIA::CONTAINER::AChars __ACharsType;
						__ACharsType achars;
						sr >> achars;

						typedef GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __StackType;
						__StackType st;
						sr >> st;

						typedef GAIA::CONTAINER::BasicQueue<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __QueueType;
						__StackType qt;
						sr >> qt;

						typedef GAIA::CONTAINER::BasicList<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __ListType;
						__ListType lt;
						sr >> lt;

						typedef GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __AVLTreeType;
						__AVLTreeType avlt;
						sr >> avlt;

						typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __TrieTreeType;
						__TrieTreeType triet;
						sr >> triet;
						__TrieTreeType::Node* pNode = triet.find(GNULL, "Hello World", sizeof("Hello World") - sizeof(GAIA::GCH));
						pNode = triet.find(GNULL, "Hello Kitty", sizeof("Hello Kitty") - sizeof(GAIA::GCH));
						pNode = triet.find(GNULL, "ThisIsGAIA", sizeof("ThisIsGAIA") - sizeof(GAIA::GCH));

						typedef GAIA::CONTAINER::BasicStackBitset<GAIA::N32, 32> __StackBitsetType;
						__StackBitsetType sbitsett;
						sr >> sbitsett;

						typedef GAIA::CONTAINER::BasicBitset<GAIA::N32> __BitsetType;
						__BitsetType bitsett;
						sr >> bitsett;
					}
					pSerializer->Release();
				}
			}
			delete pFactory;
		}
		TEST_END;
	}

	logfile.WriteText("[GAIA TEST END]");
	logfile.Close();

	return 0;
}
