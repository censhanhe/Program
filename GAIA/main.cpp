#include	"gaia.h"
using namespace GAIA;
using namespace GAIA::CONTAINER;
using namespace GAIA::ALGORITHM;

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
	}
}