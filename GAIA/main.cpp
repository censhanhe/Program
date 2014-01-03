#include	"gaia.h"
using namespace GAIA;
using namespace GAIA::CONTAINER;
using namespace GAIA::ALGORITHM;
using namespace GAIA::MATH;

class MyThread : public GAIA::THREAD::Thread
{
public:
	MyThread(){}
	~MyThread(){}

	virtual GAIA::GVOID WorkProcedure()
	{
		N32 nDebug = 0;
	}
};

void main()
{
	// Array test.
	{
		Array<N32, 32> temp;
		temp[0] = 10;
	}

	// Basic vector test.
	{
		BasicVector<N32, U32, TwiceSizeIncreaser<U32>> bv;
		bv.push_back(10);
		bv.push_back(20);
		BasicVector<N32, U32, TwiceSizeIncreaser<U32>>::BidirectionalIterator iter = bv.front();
		while(!iter.empty())
			++iter;
	}

	// Basic stack test.
	{
		BasicStack<N32, U32, TwiceSizeIncreaser<U32>> bs;
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
		U64 uWriteSize = buf.size_w();
		U64 uReadSize = buf.size_r();
		uWriteSize = uReadSize;
	}

	// Basic math test.
	{
		REAL f = xcos(10.0F);
		f = 0.0F;
	}

	// Thread test.
	{
		MyThread thread;
		thread.Run();
		thread.Wait(0xFFFFFFFF);
	}
}