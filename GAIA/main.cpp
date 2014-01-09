#define PERFORMANCE_COMPARE
#ifdef PERFORMANCE_COMPARE
#	include <vector>
#	include <set>
#	include <algorithm>
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
	static const GAIA::N32 SAMPLE_COUNT = 100000;
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

	// Basic array test
	{
		BEGIN_TEST("<Basic array test>");
		{
			GAIA::CONTAINER::BasicArray<GAIA::U32, GAIA::U32, 100> ba;
			for(GAIA::CONTAINER::BasicArray<GAIA::U32, GAIA::U32, 100>::_sizetype x = 0; x < ba.capacity(); x++)
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
		GAIA::CONTAINER::BasicVector<GAIA::N32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> >::BidirectionalIterator iter = bv.front();
		while(!iter.empty())
			++iter;
		bv.clear();
		bv.insert(0, 10);
		bv.insert(0, 20);
		bv.insert(2, 30);
		bv.erase(1);
		bv.clear();
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
		for(GAIA::N32 x = 0; x < sizeof(arr) / sizeof(GAIA::N32); x++)
			arr[x] = x;

		GAIA::CONTAINER::Buffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32> buf;
		buf.push(arr);
		buf.push(48);
		GAIA::U64 size = buf.size();
	}

	// Chars test.
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

	// String class test.
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
	}

	// Stack basic string test.
	{
		GAIA::CONTAINER::BasicStackString<GAIA::GCH, GAIA::N32, 260> str;
	}

	// BasicQueue test.
	{
		GAIA::CONTAINER::BasicQueue<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > que;
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; x++)
			que.push(x);
		for(GAIA::U32 x = 0; x < SAMPLE_COUNT; x++)
			que.pop();
		que.front();
		GAIA_ASSERT(que.size() == 50);
	}

	// BasicOrderless test.
	{
		GAIA::CONTAINER::BasicOrderless<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, (GAIA::U32)-1> ol;
		GAIA::U32 u0 = ol.insert(32);
		GAIA::U32 u1 = ol.insert(48);
		ol.remove(u0);
		ol.remove(u1);
	}

	// BasicPool test.
	{
		GAIA::CONTAINER::BasicPool<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 32> pool;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			pool.alloc();
		pool.clear();
		pool.destroy();
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			pool.alloc();
	}

	// GAIA sort and search function test.
	{
		BEGIN_TEST("<Sort function test>");
		{
			bFunctionSuccess = GAIA::True;
			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
				listGAIA.push_back(GAIA::MATH::random());
			listGAIA.sort();
			GAIA::N32 nOldValue = -1;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			{
				if(nOldValue >= listGAIA[x])
				{
					bFunctionSuccess = GAIA::False;
					break;
				}
			}
			if(bFunctionSuccess)
				LINE_TEST("GAIA sort is SUCCESSFULLY!");
			else
				LINE_TEST("GAIA sort is FAILED!");
		}
		END_TEST;

		BEGIN_TEST("<Search function test>");
		{
			bFunctionSuccess = GAIA::True;
			GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
				listGAIA.push_back(x);
			for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
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
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			listSTL.push_back(GAIA::MATH::random());
		PERF_START("STL sort use");
		std::sort(listSTL.begin(), listSTL.end());
		PERF_END;

		GAIA::CONTAINER::Vector<GAIA::N32> listGAIA;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			listGAIA.push_back(GAIA::MATH::random());
		PERF_START("GAIA sort use");
		GAIA::ALGORITHM::sort(&listGAIA[0], &listGAIA[listGAIA.size() - 1]);
		PERF_END;

		PERF_START("STL bsearch use");
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			binary_search(listSTL.begin(), listSTL.end(), listSTL[x]);
		PERF_END;

		PERF_START("GAIA bsearch use");
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
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
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
		{
			GAIA::BL bResult = btr.insert(x);
			GAIA_ASSERT(bResult);
			if(!bResult)
				bFunctionSuccess;
		}
		if(bFunctionSuccess)
			LINE_TEST("Insert by key operator is SUCCESSFULLY!");
		else
			LINE_TEST("Insert by key operator is FAILED!");

		bFunctionSuccess = GAIA::True;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
		{
			GAIA::BL bResult = btr.exist(x);
			GAIA_ASSERT(bResult);
			bResult = GAIA::True;
			if(!bResult)
				bFunctionSuccess;
		}
		if(bFunctionSuccess)
			LINE_TEST("Exist by key operator is SUCCESSFULLY!");
		else
			LINE_TEST("Exist by key operator is FAILED!");

		bFunctionSuccess = GAIA::True;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
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
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
		{
			GAIA::N32 nRand = GAIA::MATH::random();
			btr.insert(nRand);
			listSample.push_back(nRand);
		}
		bFunctionSuccess = GAIA::True;
		for(GAIA::N32 x = 0; x < listSample.size(); x++)
		{
			if(!btr.exist(listSample[x]))
				bFunctionSuccess = GAIA::False;
		}
		if(bFunctionSuccess)
			LINE_TEST("Random data insertion and find AVL-Tree function check SUCCESSFULLY!");
		else
			LINE_TEST("Random data insertion and find AVL-Tree function check FAILED!");

		if(btr.dbg_check_balance())
			LINE_TEST("Check AVL-Tree balance SUCCESSFULLY!");
		else
			LINE_TEST("Check AVL-Tree balance FAILED!");

		listSample.sort();
		bFunctionSuccess = GAIA::True;
		GAIA::N32 n = -1;
		for(GAIA::N32 x = 0; x < listSample.size(); x++)
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
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			setSTL.insert(GAIA::MATH::random());
		PERF_END;

		PERF_START("GAIA AVLTree use");
		GAIA::CONTAINER::AVLTree<GAIA::N32, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 1000> avltree;
		for(GAIA::N32 x = 0; x < SAMPLE_COUNT; x++)
			avltree.insert(GAIA::MATH::random());
		PERF_END;

		END_TEST;
#endif
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
		file.Read(buf.front(), buf.size());
		const GAIA::GWCH* p = (GAIA::GWCH*)buf.front();
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
		for(GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>::_sizetype x = 0; x < listResult.size(); x++)
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