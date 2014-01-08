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

	// Stack basic string test.
	{
		GAIA::CONTAINER::BasicStackString<GAIA::GCH, GAIA::N32, 260> str;
	}

	// BasicQueue test.
	{
		GAIA::CONTAINER::BasicQueue<GAIA::U32, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > que;
		for(GAIA::U32 x = 0; x < 100; x++)
			que.push(x);
		for(GAIA::U32 x = 0; x < 50; x++)
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
		for(GAIA::N32 x = 0; x < 1000; x++)
			pool.alloc();
		pool.clear();
		pool.destroy();
		for(GAIA::N32 x = 0; x < 1000; x++)
			pool.alloc();
	}

	// AVLTree test.
	{
		GAIA::CONTAINER::AVLTree<GAIA::N32, GAIA::U32, GAIA::U16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, 100> btr;
		static const GAIA::N32 FIRST_SAMPLE_COUNT = 100000;
		for(GAIA::N32 x = 0; x < FIRST_SAMPLE_COUNT; x++)
		{
			GAIA::BL bResult = btr.insert(x);
			GAIA_ASSERT(bResult);
			bResult = GAIA::True;
		}
		for(GAIA::N32 x = 0; x < FIRST_SAMPLE_COUNT; x++)
		{
			GAIA::BL bResult = btr.exist(x);
			GAIA_ASSERT(bResult);
			bResult = GAIA::True;
		}
		for(GAIA::N32 x = 0; x < FIRST_SAMPLE_COUNT; x++)
		{
			GAIA::BL bResult = btr.erase(x);
			GAIA_ASSERT(bResult);
			bResult = GAIA::True;
		}

		GAIA::N32 nDebug = 0;
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

	return 0;
}
