#define PERFORMANCE_COMPARE
#ifdef PERFORMANCE_COMPARE
#	include <vector>
#	include <set>
#	include <algorithm>
#	include <iostream>
#endif

#define BEGIN_TEST(name)	do{logfile.WriteText(name); logfile.WriteText("\r\n");}while(0)
#define END_TEST			do{logfile.WriteText("\r\n\r\n");}while(0)
#define LINE_TEST(text)		do{logfile.WriteText("\t");logfile.WriteText(text);logfile.WriteText("\r\n");}while(0)
#define TEXT_TEST(text)		do{logfile.WriteText(text);}while(0)
#define PERF_START(name)	uPerfStart = GAIA::TIME::clock_time(); GAIA::ALGORITHM::strcpy(szPerfName, name);
#define PERF_END 			uPerfEnd = GAIA::TIME::clock_time();\
							sprintf(szPerf, "%d(MS)", uPerfEnd - uPerfStart);\
							TEXT_TEST("\t");\
							TEXT_TEST(szPerfName);\
							LINE_TEST(szPerf);

#include "gaia.h"

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
#ifdef _DEBUG
	static const GAIA::N32 SAMPLE_COUNT = 10000;
#else
	static const GAIA::N32 SAMPLE_COUNT = 1000000;
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
		GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > bv;
		bv.push_back(10);
		bv.push_back(20);
		GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> >::BidirectionalIterator iter = bv.front_iterator();
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
	}

	// Basic stack test.
	{
		GAIA::CONTAINER::BasicStack<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > bs;
		bs.push(10);
		bs.push(20);
		GAIA::N32 n = bs.top();
		bs.pop();
		n = bs.top();
		bs.pop();
		GAIA::U32 uSize = bs.size();
		uSize = 0;
	}

	// Buffer test.
	{
		GAIA::N32 arr[32];
		for(GAIA::N32 x = 0; x < sizeof(arr) / sizeof(GAIA::N32); ++x)
			arr[x] = x;

		GAIA::CONTAINER::Buffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32> buf;
		buf.push(arr);
		buf.push(48);
		GAIA::U64 size = buf.size();
	}

	// String algorithm test.
	{
		GAIA::GTCH ch = GAIA::ALGORITHM::tolower('A');
		GAIA::GTCH sz[128] = L"abcdefgABCDEFG1234567!@#$%^&";
		GAIA::UM uLen = GAIA::ALGORITHM::strlen(sz);
		uLen = 0;
		GAIA::ALGORITHM::tolower(sz);
		sz[0] = 0;
		GAIA::N32 nCompare = GAIA::ALGORITHM::strcmp(L"Hello world", L"Hello kitty!");

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
		GAIA::CONTAINER::BasicQueue<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > que;
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
			que.push(x);
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; ++x)
			que.pop();
		que.front();
		GAIA_ASSERT(que.size() == 50);
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

	// AVLTree test.
	{
		BEGIN_TEST("<AVL Tree Function Test>");

		GAIA::CONTAINER::AVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 100> btr;

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
		GAIA::CONTAINER::AVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 100>::BidirectionalIterator iter = btr.front_iterator();
		while(!iter.empty())
		{
			GAIA::N32 n = *iter;
			++iter;
		}
		iter = btr.back_iterator();
		while(!iter.empty())
		{
			GAIA::N32 n = *iter;
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
				bFunctionSuccess;
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

		END_TEST;
	}

	// AVLTree performance compare.
	{
#ifdef PERFORMANCE_COMPARE
		BEGIN_TEST("<AVLTree performance>");

		PERF_START("STL set use");
		std::set<GAIA::N32> setSTL;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			setSTL.insert(GAIA::MATH::random());
		PERF_END;

		PERF_START("GAIA AVLTree use");
		GAIA::CONTAINER::AVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> avltree;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; ++x)
			avltree.insert(GAIA::MATH::random());
		PERF_END;

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
	
	// BasicGraph function test.
	{
		BEGIN_TEST("<BasicGraph function test>");
		
		typedef GAIA::CONTAINER::BasicGraph<GAIA::REAL, GAIA::REAL, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 1000> _MyGraphType;
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
						}
					}
				#ifdef PERFORMANCE_COMPARE
					std::cout << std::endl;
				#endif
				}
				if(pathlist.size() != 6)
				{
				}
			}
			else
				LINE_TEST("basic graph find FAILED!");
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
						}
					}
				#ifdef PERFORMANCE_COMPARE
					std::cout << std::endl;
				#endif
				}
				if(pathlist.size() != 6)
				{
				}
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
		GAIA::MATH::VEC2<GAIA::REAL> v3 = v0;
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
		GAIA::CONTAINER::Buffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32> buf;
		buf.resize(uFileSize);
		file.Read(buf.front_ptr(), buf.size());
		const GAIA::GWCH* p = (GAIA::GWCH*)buf.front_ptr();
		GAIA::GWCH szTemp[1024];
		GAIA::ALGORITHM::strcpy(szTemp, p);
		GAIA::N32 nDebug = 0;
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