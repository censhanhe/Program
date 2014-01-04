#include	"gaia.h"
using namespace GAIA;
using namespace GAIA::CONTAINER;
using namespace GAIA::ALGORITHM;
using namespace GAIA::MATH;
using namespace GAIA::FILESYSTEM;

class MyThread : public GAIA::THREAD::Thread
{
public:
	MyThread(){}
	~MyThread(){}

	virtual GAIA::GVOID WorkProcedure()
	{
		N32 nDebug = 0;
		nDebug = 0;
	}
};

N32 main()
{
	// Array test.
	{
		Array<N32, 32> temp;
		temp[0] = 10;
	}

	// Basic vector test.
	{
		BasicVector<N32, U32, TwiceSizeIncreaser<U32> > bv;
		bv.push_back(10);
		bv.push_back(20);
		BasicVector<N32, U32, TwiceSizeIncreaser<U32> >::BidirectionalIterator iter = bv.front();
		while(!iter.empty())
			++iter;
	}

	// Basic stack test.
	{
		BasicStack<N32, U32, TwiceSizeIncreaser<U32> > bs;
		bs.push(10);
		bs.push(20);
		N32 n = bs.top();
		bs.pop();
		n = bs.top();
		bs.pop();
		U32 uSize = bs.size();
		uSize = 0;
	}

	// Buffer test.
	{
		N32 arr[32];
		for(N32 x = 0; x < sizeof(arr) / sizeof(N32); x++)
			arr[x] = x;

		Buffer<TwiceSizeIncreaser<U32>, U32> buf;
		buf.push(arr);
		buf.push(48);
		U64 size = buf.size();
	}

	// String algorithm test.
	{
		GAIA::GTCH ch = tolower('A');
		GAIA::GTCH sz[128] = L"abcdefgABCDEFG1234567!@#$%^&";
		GAIA::UM uLen = strlen(sz);
		uLen = 0;
		tolower(sz);
		sz[0] = 0;
		GAIA::N32 nCompare = strcmp(L"Hello world", L"Hello kitty!");

		GAIA::ALGORITHM::strcpy(sz, L"Helloword");
		GAIA::ALGORITHM::strcat(sz, L"My name is arm!");
		N32 nCmp = GAIA::ALGORITHM::strcmp(sz, L"Helloxitty");
		nCmp = GAIA::ALGORITHM::strcmp(sz, sz);
		GAIA::ALGORITHM::strcpy(sz, L"Helloworld");
		GAIA::GTCH* pResult = GAIA::ALGORITHM::strstr(sz, L"lo");
		pResult = GAIA::ALGORITHM::strmch(sz, L"Hel");
		sz[0] = 0;
	}

	// Stack basic string test.
	{
		BasicStackString<GAIA::GCH, GAIA::N32, 260> str;
	}

	// BasicQueue test.
	{
		BasicQueue<GAIA::U32, GAIA::U32> que;
		for(GAIA::U32 x = 0; x < 100; x++)
			que.push(x);
		for(GAIA::U32 x = 0; x < 50; x++)
			que.pop();
		que.front();
		GAIA_ASSERT(que.size() == 50);
	}

	// Basic math test.
	{
		REAL f = xcos(10.0F);
		f = 0.0F;
	}
	
	// VEC2 math cookies test.
	{
		VEC2<GAIA::REAL> v0(1.0);
		VEC2<GAIA::N32> v1(1, 2.0F);
		VEC2<GAIA::REAL> v3 = v0;
	}

	// Thread test.
	{
		MyThread thread;
		thread.Run();
		thread.Wait(0xFFFFFFFF);
	}

	// File test.
	{
		File file;
		GAIA::BL bResult = file.Open("filetest.txt", FILE_OPEN_TYPE_CREATEALWAYS | FILE_OPEN_TYPE_WRITE);
		file.Write(L"My name is Armterla!");
		bResult = file.Close();
		bResult = file.Open("filetest.txt", FILE_OPEN_TYPE_READ);
		GAIA::U64 uFileSize = file.Size();
		GAIA::CONTAINER::Buffer<TwiceSizeIncreaser<U32>, U32> buf;
		buf.resize(uFileSize);
		file.Read(buf.front(), buf.size());
		const GAIA::GWCH* p = (GAIA::GWCH*)buf.front();
		GAIA::GWCH szTemp[1024];
		GAIA::ALGORITHM::strcpy(szTemp, p);
		N32 nDebug = 0;
	}
	
	return 0;
}
