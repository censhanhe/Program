#if defined(_MSC_VER) && defined(_DEBUG)
#	ifdef		_DEBUG
#		define	_CRTDBG_MAP_ALLOC
#	endif
#	include	<stdlib.h>
#	include	<stdio.h>
#	include	<crtdbg.h>
#endif

#define PERFORMANCE_COMPARE
#ifdef PERFORMANCE_COMPARE
#	include <vector>
#	include <set>
#	include <algorithm>
#	include <iostream>
#	define PERF_PRINT_NAME(name) std::cout<<name<<std::endl;
#	define PERF_PRINT_TIME std::cout<<'\t'<<"TIME-LOST="<<uPerfEnd - uPerfStart<<"(MS)"<<std::endl;
#else
#	define PERF_PRINT_NAME(name)
#	define PERF_PRINT_TIME
#endif

#define BEGIN_TEST(name)	PERF_PRINT_NAME(name); do{logfile.WriteText(name); logfile.WriteText("\r\n");}while(0) ;PERF_START("TIME-LOST")
#define END_TEST			PERF_END; PERF_PRINT_TIME; do{logfile.WriteText("\r\n\r\n");}while(0)
#define LINE_TEST(text)		do{logfile.WriteText("\t");logfile.WriteText(text);logfile.WriteText("\r\n");}while(0)
#define TEXT_TEST(text)		do{logfile.WriteText(text);}while(0)
#define PERF_START(name)	uPerfStart = GAIA::TIME::clock_time(); GAIA::ALGORITHM::strcpy(szPerfName, name);
#define PERF_END 			uPerfEnd = GAIA::TIME::clock_time();\
							sprintf(szPerf, "%d(MS)", uPerfEnd - uPerfStart);\
							TEXT_TEST("\t");\
							TEXT_TEST(szPerfName);\
							LINE_TEST(szPerf);

#include "gaia.h"

#if defined(_MSC_VER) && defined(_DEBUG)
#	define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

template <typename _DataType> class SNode
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

GAIA::N32 main()
{
#if defined(_MSC_VER) && defined(_DEBUG)
#	if defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#	endif
#endif

#ifdef _DEBUG
	static const GAIA::N32 SAMPLE_COUNT = 10000;
#else
	static const GAIA::N32 SAMPLE_COUNT = 100000;
#endif

	GAIA::BL bFunctionSuccess = GAIA::True;

	//
	GAIA::MATH::random_seed(GAIA::TIME::clock_time());

	//
	GAIA::GCH szPerf[256];
	GAIA::GCH szPerfName[256];
	GAIA::U32 uPerfStart, uPerfEnd;
	GAIA::FILESYSTEM::File logfile;
#if GAIA_OS == GAIA_OS_WINDOWS
	logfile.Open("../gaia_test_result.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
#else
	logfile.Open("/users/armterla/gaia_test_result.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
#endif
	logfile.WriteText("[GAIA TEST BEGIN]\r\n\r\n");

	// Real number float equal test.
	{
		BEGIN_TEST("<Float equal function test>");
		{
			GAIA::BL bEqual = GAIA::MATH::equal(0.1F, 0.100001F);
			if(bEqual)
				LINE_TEST("equal(2) convert SUCCESSFULLY!");
			else
				LINE_TEST("equal(2) convert FAILED!");

			bEqual = GAIA::MATH::equal(0.1F, 0.11F, 0.1F);
			if(bEqual)
				LINE_TEST("equal(3) convert SUCCESSFULLY!");
			else
				LINE_TEST("equal(3) convert FAILED!");
		}
		END_TEST;
	}

	// X128 test.
	{
		BEGIN_TEST("<X128 test>");
		{
			GAIA::X128 id;
			id = "0123456789ABCDEF0123456789ABCDEF";
			GAIA::X128 tid;
			tid.u0 = 0x01234567;
			tid.u1 = 0x89ABCDEF;
			tid.u2 = 0x01234567;
			tid.u3 = 0x89ABCDEF;
			if(tid == id)
				LINE_TEST("X128 type convert and compare SUCCESSFULLY!");
			else
				LINE_TEST("X128 type convert and compare FAILED!");
		}
		END_TEST;
	}

	// Unique test.
	{
		BEGIN_TEST("<Unique algorithm test>");
		{
			GAIA::N32 listNum[] = {3,1,4,5,2,1,6,8,1,3,2,6,4,9,7,0};
			GAIA::N32* pNew = GAIA::ALGORITHM::unique_noorder(listNum, &listNum[sizeof(listNum) / sizeof(listNum[0]) - 1]);
			GAIA::N64 nCount = pNew - listNum + 1;
			if(nCount != 10)
				LINE_TEST("unique_noorder FAILED!");
		}
		END_TEST;
	}

	// String convert function test.
	{
		BEGIN_TEST("<String convert function test>");
		{
			GAIA::NM n;
			GAIA::ALGORITHM::str2int("-123456789", n);
			if(n != -123456789)
				LINE_TEST("str2int convert FAILED!");
			else
				LINE_TEST("str2int convert SUCCESSFULLY!");

			GAIA::REAL r;
			GAIA::ALGORITHM::str2real("-.1234", r);
			if(!GAIA::MATH::equal(r, -0.1234))
				LINE_TEST("str2real convert FAILED!");
			else
				LINE_TEST("str2real convert SUCCESSFULLY!");

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
				LINE_TEST("int2str convert FAILED!");
			else
				LINE_TEST("int2str convert SUCCESSFULLY!");

			bFunctionSuccess = GAIA::True;
			r = -1.2;
			GAIA::ALGORITHM::real2str(r, szTemp);
			if(GAIA::ALGORITHM::strmch(szTemp, L"-1.2") != szTemp)
				bFunctionSuccess = GAIA::False;
			r = 0;
			GAIA::ALGORITHM::real2str(r, szTemp);
			if(GAIA::ALGORITHM::strcmp(szTemp, L"0.0") != 0)
				bFunctionSuccess = GAIA::False;
			if(!bFunctionSuccess)
				LINE_TEST("real2str convert FAILED!");
			else
				LINE_TEST("real2str convert SUCCESSFULLY!");

			n = GAIA::ALGORITHM::string_cast<GAIA::U8>("-124.456");
			r = GAIA::ALGORITHM::string_cast<GAIA::REAL>("-123.456");
			n = GAIA::ALGORITHM::string_autocast("-123.456");
			r = GAIA::ALGORITHM::string_autocast("-123.456");

			n = 0;
		}
		END_TEST;
	}

	// Pair test.
	{
		BEGIN_TEST("<Pair test>");
		{
			GAIA::CONTAINER::Pair<const GAIA::GCH*, GAIA::N32> pair("abc", 123);
			GAIA::CONTAINER::Pair<const GAIA::GCH*, GAIA::N32> newpair = pair;
			if(newpair != pair)
				LINE_TEST("Pair equal function test FAILED!");
			GAIA::N32 nDebug = 0;
			nDebug++;
		}
		END_TEST;
	}

	// Basic stack bitset test.
	{
		BEGIN_TEST("<Basic stack bitset test>");
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
				LINE_TEST("multi and operation test SUCCESSFULLY!");
			else
				LINE_TEST("multi and operation test FAILED!");
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
				LINE_TEST("inverse operation test FAILED!");
			else
				LINE_TEST("inverse operation test SUCCESSFULLY!");
		}
		END_TEST;
	}

	// Basic array test
	{
		BEGIN_TEST("<Basic array test>");
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
				{
					v.push_back(GAIA::MATH::random()%100);
				}
				v.sort();
				GAIA::N64 nDrop = v.unique();
				nDrop = 0;
				v.sort();
			}
		}
		END_TEST;
	};

	// Array test.
	{
		GAIA::CONTAINER::Array<GAIA::N32, 32> temp;
		temp[0] = 10;
	}

	// Basic vector test.
	{
		GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>> bv;
		bv.push_back(10);
		bv.push_back(20);
		GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>>::BidirectionalIterator iter = bv.front_iterator();
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
			typedef GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>> __VectorType;
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

	// Basic stack test.
	{
		GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>> bs;
		bs.push(10);
		bs.push(20);
		GAIA::N32 n = bs.top();
		bs.pop();
		n = bs.top();
		bs.pop();
		GAIA::U32 uSize = bs.size();
		uSize = 0;
	}

	// BasicBuffer test.
	{
		GAIA::N32 arr[32];
		for(GAIA::N32 x = 0; x < sizeof(arr) / sizeof(GAIA::N32); ++x)
			arr[x] = x;

		GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32> buf;
		buf.push(arr);
		buf.push(48);
		GAIA::U64 size = buf.size();
		size = 0;
	}

	// String algorithm test.
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

	// Chars class test.
	{
		BEGIN_TEST("<Chars class test>");

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
			LINE_TEST("insert test SUCCESSFULLY!");
		else
			LINE_TEST("insert test FAILED!");

		END_TEST;
	}

	// String class test.
	{
		BEGIN_TEST("<String class test>");

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
			LINE_TEST("insert test SUCCESSFULLY!");
		else
			LINE_TEST("insert test FAILED!");

		END_TEST;
	}

	// BasicQueue test.
	{
		typedef GAIA::CONTAINER::BasicQueue<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>> __QueueType;
		__QueueType que;
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
			que.push(x);
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
			que.pop();
		que.front();
		GAIA_ASSERT(que.size() == 50);
		__QueueType newque = que;
	}

	// BasicOrderless test.
	{
		GAIA::CONTAINER::BasicOrderless<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, (GAIA::U32)-1> ol;
		GAIA::U32 u0 = ol.insert(32);
		GAIA::U32 u1 = ol.insert(48);
		ol.erase(u0);
		ol.erase(u1);
	}

	// BasicPool test.
	{
		GAIA::CONTAINER::BasicPool<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 32> pool;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			pool.alloc();
		pool.clear();
		pool.destroy();
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			pool.alloc();
	}

	// GAIA sort algorithm test.
	{
		BEGIN_TEST("<Sort algorithm test>");
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
				LINE_TEST("GAIA bsort is SUCCESSFULLY!");
			else
				LINE_TEST("GAIA bsort is FAILED!");

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
		END_TEST;
	}

	// GAIA sort and search function test.
	{
		BEGIN_TEST("<Sort function test>");
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
				LINE_TEST("GAIA vector's sort is SUCCESSFULLY!");
			else
				LINE_TEST("GAIA vector's sort is FAILED!");
		}
		END_TEST;

		BEGIN_TEST("<Search function test>");
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
				LINE_TEST("GAIA search is SUCCESSFULLY!");
			else
				LINE_TEST("GAIA search is FAILED!");
		}
		END_TEST;
	}

	// Sort and search function performance compare.
	{
#ifdef PERFORMANCE_COMPARE
		BEGIN_TEST("<Sort function performance>");

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

		END_TEST;
#endif
	}

	// BasicList function test.
	{
		BEGIN_TEST("<BasicList Function Test>");
		{
			typedef GAIA::CONTAINER::BasicList<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __ListType;
			__ListType list;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.push_back(x);
			__ListType::BidirectionalIterator iter = list.front_iterator();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.erase(iter);
			list.destroy();
			list.clear();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.push_front(x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.pop_front();
			if(!list.empty())
				LINE_TEST("list front push pop operator FAILED!");
			iter = list.front_iterator();
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.insert(iter, x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
				list.pop_back();
			if(!list.empty())
				LINE_TEST("list back push pop operator FAILED!");
		}
		END_TEST;
	}
	
	// BasicAVLTree test.
	{
		BEGIN_TEST("<BasicAVLTree Function Test>");

		GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 100> btr;

		bFunctionSuccess = GAIA::True;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::BL bResult = btr.insert(x);
			GAIA_ASSERT(bResult);
			if(!bResult)
				bFunctionSuccess = GAIA::False;
		}
		if(bFunctionSuccess)
			LINE_TEST("Insert by key operator is SUCCESSFULLY!");
		else
			LINE_TEST("Insert by key operator is FAILED!");
		GAIA::BL bCheckParent = btr.dbg_check_parent();
		bCheckParent = true;
		GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 100>::BidirectionalIterator iter = btr.front_iterator();
		while(!iter.empty())
		{
			GAIA::N32 n = *iter;
			n = 0;
			++iter;
		}
		iter = btr.back_iterator();
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
			GAIA_ASSERT(pFinded != GNULL);
			if(pFinded == GNULL)
				bFunctionSuccess = GAIA::False;
		}
		if(bFunctionSuccess)
			LINE_TEST("Exist by key operator is SUCCESSFULLY!");
		else
			LINE_TEST("Exist by key operator is FAILED!");

		bFunctionSuccess = GAIA::True;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
		{
			GAIA::BL bResult = btr.erase(x);
			GAIA_ASSERT(bResult);
			bResult = GAIA::True;
			if(!bResult)
				bFunctionSuccess = GAIA::False;
		}
		if(bFunctionSuccess)
			LINE_TEST("Erase element by key operator is SUCCESSFULLY!");
		else
			LINE_TEST("Erase element by key operator is FAILED!");

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
			LINE_TEST("Random data insertion and find AVL-Tree function check SUCCESSFULLY!");
		else
			LINE_TEST("Random data insertion and find AVL-Tree function check FAILED!");

		for(GAIA::N32 x = 0; x < listSample.size(); x += 10)
			btr.erase(listSample[x]);

		if(btr.dbg_check_balance())
			LINE_TEST("Check AVL-Tree balance SUCCESSFULLY!");
		else
			LINE_TEST("Check AVL-Tree balance FAILED!");

		if(btr.dbg_check_parent())
			LINE_TEST("Check AVL-Tree parent SUCCESSFULLY!");
		else
			LINE_TEST("Check AVL-Tree parent FAILED!");

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
			LINE_TEST("Random data insertion and erase AVL-Tree function check SUCCESSFULLY!");
		else
			LINE_TEST("Random data insertion and erase AVL-Tree function check FAILED!");

		{
			typedef GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __AVLTreeType;
			__AVLTreeType av;
			for(GAIA::N32 x = 0; x < 100; ++x)
				av.insert(x);
			__AVLTreeType::BidirectionalIterator iter = av.lower_bound(32);
			GAIA::N32 nCount = 0;
			while(!iter.empty())
			{
				++iter;
				++nCount;
			}
			if(nCount != 68)
				LINE_TEST("Lower bound function FAILED!");
			iter = av.upper_bound(32);
			nCount = 0;
			while(!iter.empty())
			{
				--iter;
				++nCount;
			}
			if(nCount != 33)
				LINE_TEST("Upper bound function FAILED!");
		}
		
		END_TEST;
	}

	// BasicAVLTree performance compare.
	{
#ifdef PERFORMANCE_COMPARE
		BEGIN_TEST("<BasicAVLTree performance>");

		PERF_START("STL set use");
		std::set<GAIA::N32> setSTL;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			setSTL.insert(GAIA::MATH::random());
		PERF_END;

		PERF_START("GAIA BasicAVLTree use");
		GAIA::CONTAINER::BasicAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> avltree;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			avltree.insert(GAIA::MATH::random());
		PERF_END;

		END_TEST;
#endif
	}
	
	// BasicMultiAVLTree function test.
	{
		BEGIN_TEST("<BasicMultiAVLTree function test>");

		bFunctionSuccess = GAIA::True;
		typedef GAIA::CONTAINER::BasicMultiAVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 32> __MAVLTreeType;
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
		__MAVLTreeType::BidirectionalIterator iter = mavlt.front_iterator();
		if(iter.empty())
			bFunctionSuccess = GAIA::False;
		while(!iter.empty())
			++iter;
		if(bFunctionSuccess)
			LINE_TEST("BasicMultiAVLTree function test SUCCESSFULLY!");
		else
			LINE_TEST("BasicMultiAVLTree function test FAILED!");

		END_TEST;
	}

	// BasicTrieTree function test.
	{
		BEGIN_TEST("<BasicTrieTree function test>");
		{
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 1000> __TrieTree;
			__TrieTree tt;
			tt.insert("hello", 5);
			tt.insert("world", 5);
			tt.insert("kitty", 5);
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
		}
		END_TEST;
	}

	// BasicTrieTree performance test.
	{
	#ifdef PERFORMANCE_COMPARE
		BEGIN_TEST("<BasicTrieTree performance test>");
		{
			typedef GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::N64>, GAIA::N64, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U64>> __StringList;
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

			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::GCH, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 10000> __TrieTree;
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
				}
			}
			PERF_END;
		}
		END_TEST;
	#endif
	}

	// BasicTree function test.
	{
		BEGIN_TEST("<BasicTree function test>");

		typedef GAIA::CONTAINER::BasicTree<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> _MyTreeType;
		_MyTreeType tree;
		_MyTreeType::Node* pNode = tree.insert(10, GNULL);
		tree.insert(20, pNode);
		_MyTreeType::Node* pChildNode = tree.insert(30, pNode);
		tree.insert(40, pNode);
		_MyTreeType::Node* pChildChild = tree.insert(40, pChildNode);
		_MyTreeType::__NodeListType listResult;

		tree.find(GNULL, 40, listResult);
		if(listResult.size() == 2)
			LINE_TEST("basic tree find SUCCESSFULLY!");
		else
			LINE_TEST("basic tree find FAILED!");

		GAIA::BL bResult = tree.link(*pNode, *pChildChild);
		if(bResult)
			LINE_TEST("basic tree link function SUCCESSFULLY!");
		else
			LINE_TEST("basic tree link function FAILED!");

		bResult = tree.unlink(*pNode, *pChildChild);
		if(bResult)
			LINE_TEST("basic tree unlink function SUCCESSFULLY!");
		else
			LINE_TEST("basic tree unlink function FAILED!");

		bResult = tree.islinked(*pNode, *pChildChild);
		if(!bResult)
			LINE_TEST("basic tree islinked function SUCCESSFULLY!");
		else
			LINE_TEST("basic tree islinked function FAILED!");

		bResult = tree.link(*pNode, *pChildChild);
		if(bResult)
			LINE_TEST("basic tree link function SUCCESSFULLY!");
		else
			LINE_TEST("basic tree link function FAILED!");

		tree.erase(*pChildChild);
		tree.erase(*pNode);

		END_TEST;
	}
	
	// BasicPriQueue function test.
	{
		BEGIN_TEST("<BasicPriQueue function test>");
		{
			typedef GAIA::CONTAINER::BasicPriQueue<SNode<GAIA::N32>, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __PriQueueType;
			typedef GAIA::CONTAINER::BasicVector<SNode<GAIA::N32>, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>> __VectorType;
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
				LINE_TEST("BasicPriQueue insert and pop_front SUCCESSFULLY!");
			else
				LINE_TEST("BasicPriQueue insert and pop_front FAILED!");
		}
		END_TEST;
	}
	
	// BasicSet function test.
	{
		BEGIN_TEST("<BasicSet function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicSet<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __SetType;
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
			if(bFunctionSuccess)
				LINE_TEST("BasicSet function test SUCCESSFULLY!");
			else
				LINE_TEST("BasicSet function test FAILED!");
		}
		END_TEST;
	}

	// BasicMultiSet function test.
	{
		BEGIN_TEST("<BasicMultiSet function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMultiSet<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 256> __MultiSetType;
			__MultiSetType mst;
			if(!mst.insert(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.insert(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.erase(32))
				bFunctionSuccess = GAIA::False;
			if(!mst.empty())
				bFunctionSuccess = GAIA::False;
			if(mst.size() != 0)
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
				LINE_TEST("BasicMultiSet function test SUCCESSFULLY!");
			else
				LINE_TEST("BasicMultiSet function test FAILED!");
		}
		END_TEST;
	}
	
	// BasicMap function test.
	{
		BEGIN_TEST("<BasicMap function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMap<GAIA::N32, GAIA::CONTAINER::AString, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __MapType;
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
			if(bFunctionSuccess)
				LINE_TEST("BasicMap function test SUCCESSFULLY!");
			else
				LINE_TEST("BasicMap function test FAILED!");

			{
				bFunctionSuccess = GAIA::True;
				typedef GAIA::CONTAINER::BasicMap<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> __MapType;
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
		END_TEST;
	}

	// BasicMultiMap function test.
	{
		BEGIN_TEST("<BasicMultiMap function test>");
		{
			bFunctionSuccess = GAIA::True;
			typedef GAIA::CONTAINER::BasicMultiMap<GAIA::N32, GAIA::CONTAINER::AString, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 256> __MultiMapType;
			__MultiMapType mmp;
			mmp.insert("Arm", 30);
			mmp.insert("Arm", 31);
			mmp.insert("NeedLight", 32);
			mmp.insert("Box", 30);
			mmp.erase("Arm");
			mmp.clear();
			mmp.destroy();
			if(bFunctionSuccess)
				LINE_TEST("BasicMultiMap function test SUCCESSFULLY!");
			else
				LINE_TEST("BasicMultiMap function test FAILED!");
		}
		END_TEST;
	}
	
	// BasicGraph function test.
	{
		BEGIN_TEST("<BasicGraph function test>");
		
		typedef GAIA::CONTAINER::BasicGraph<GAIA::REAL, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 1000> _MyGraphType;
		_MyGraphType graph;
		_MyGraphType::Node* pNode = GNULL;
		for(GAIA::N32 x = 0; x < 100; ++x)
			pNode = graph.insert((GAIA::REAL)x, pNode);
		_MyGraphType::__NodeListType listResult;
		graph.find(GNULL, 3.0, listResult);
		if(listResult.empty())
			LINE_TEST("basic graph find FAILED!");
		else
			LINE_TEST("basic graph find SUCCESSFULLY!");

		{
			listResult.clear();
			graph.find(GNULL, 8.0F, listResult);
			if(!listResult.empty())
			{
				_MyGraphType::Node* pNode1 = listResult[0];
				if(pNode1 == GNULL)
					LINE_TEST("basic graph find FAILED!");
				graph.insert(80.0F, listResult[0]);
			}
			else
				LINE_TEST("basic graph find FAILED!");
			listResult.clear();
			graph.find(GNULL, 80.0F, listResult);
			if(!listResult.empty())
			{
				_MyGraphType::Node* pNode2 = listResult[1];
				if(pNode2 == GNULL)
					LINE_TEST("basic graph find FAILED!");
			}
			else
				LINE_TEST("basic graph find FAILED!");
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
				graph.navpath<GAIA::REAL, 5>(*listResult1[0], *listResult2[0], listResultNode);
				graph.navpath<GAIA::REAL, 5>(*listResult1[0], 4.0F, listResultNode);

				_MyGraphType::__PathTreeType treeResult;
				graph.paths(*listResult1[0], *listResult2[0], treeResult);
				if(treeResult.empty())
					LINE_TEST("basic graph path from one node to another FAILED!");
				_MyGraphType::__PathTreeType::__PathListType pathlist;
				treeResult.paths(GNULL, pathlist);
				for(_MyGraphType::__PathTreeType::__PathListType::_sizetype x = 0; x < pathlist.size(); ++x)
				{
					_MyGraphType::__PathTreeType::__PathListType::_datatype& path = pathlist[x];
					for(_MyGraphType::__PathTreeType::__PathListType::_datatype::_sizetype y = 0; y < path.size(); ++y)
					{
						_MyGraphType::__PathTreeType::Node* pTreeNode = path[y];
						GAIA_ASSERT(pTreeNode != GNULL);
						_MyGraphType::Node* pNode = **pTreeNode;
						GAIA_ASSERT(pNode != GNULL);
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
					LINE_TEST("basic graph paths FAILED!");
			}
			else
				LINE_TEST("basic graph find FAILED!");

			_MyGraphType::__LinkListType listLinkResult;
			graph.collect_link_list(listLinkResult);
			if(listLinkResult.size() == 0)
				LINE_TEST("collect graph link list FAILED!");
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
					LINE_TEST("basic graph path from one node to another FAILED!");
				_MyGraphType::__PathTreeType::__PathListType pathlist;
				treeResult.paths(GNULL, pathlist);
				for(_MyGraphType::__PathTreeType::__PathListType::_sizetype x = 0; x < pathlist.size(); ++x)
				{
					_MyGraphType::__PathTreeType::__PathListType::_datatype& path = pathlist[x];
					for(_MyGraphType::__PathTreeType::__PathListType::_datatype::_sizetype y = 0; y < path.size(); ++y)
					{
						_MyGraphType::__PathTreeType::Node* pTreeNode = path[y];
						GAIA_ASSERT(pTreeNode != GNULL);
						_MyGraphType::Node* pNode = **pTreeNode;
						GAIA_ASSERT(pNode != GNULL);
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
					LINE_TEST("basic graph paths FAILED!");
			}
			else
				LINE_TEST("basic graph find FAILED!");

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
			_MyGraphType::_sizetype k = _MyGraphType::_groupelementsize;
			k = 0;
		}

		if(graph.dbg_check_traveling())
			LINE_TEST("basic graph debug check traveling SUCCESSFULLY!");
		else
			LINE_TEST("basic graph debug check traveling FAILED!");

		if(graph.dbg_check_relation())
			LINE_TEST("basic graph debug check relation SUCCESSFULLY!");
		else
			LINE_TEST("basic graph debug check relation FAILED!");

		END_TEST;
	}

	// Basic math test.
	{
		GAIA::REAL f = GAIA::MATH::xcos(10.0F);
		f = 0.0F;
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
		MyThread thread;
		thread.Run();
		thread.Wait();
		GAIA_ASSERT(thread.IsRuned());
	}

	// File test.
	{
		GAIA::FILESYSTEM::File file;
		GAIA::BL bResult = file.Open("filetest.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
		file.Write(L"My name is Armterla!");
		bResult = file.Close();
		bResult = file.Open("filetest.tmp", GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ);
		GAIA::U64 uFileSize = file.Size();
		GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U64>, GAIA::U64> buf;
		buf.resize(uFileSize);
		file.Read(buf.front_ptr(), buf.size());
		const GAIA::GWCH* p = (GAIA::GWCH*)buf.front_ptr();
		GAIA::GWCH szTemp[1024];
		GAIA::ALGORITHM::strcpy(szTemp, p);
		GAIA::N32 nDebug = 0;
		nDebug = 0;
	}
	
	// Network test.
	{
		BEGIN_TEST("Network function test");
		
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
		
		if(bFunctionSuccess)
			TEXT_TEST("IPAddress to or from string convert SUCCESSFULLY!");
		else
			TEXT_TEST("IPAddress to or from string convert FAILED!");
	}

	// Basic factory test 1.
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

	// Basic factory test 2.
	{
	}
		
	logfile.WriteText("[GAIA TEST END]");
	logfile.Close();

	return 0;
}
