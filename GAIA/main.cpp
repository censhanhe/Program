#include	<stdio.h>
#include	<stdlib.h>
#include	<iostream>
using namespace std;

#include	"gaia.h"
using namespace GAIA;
using namespace GAIA::CONTAINER;
using namespace GAIA::ALGORITHM;

void main()
{
	{
		BasicVector<N32, U32, TwiceMemIncreaser<U32>> bv;
		bv.push_back(10);
		bv.push_back(20);
		BasicVector<N32, U32, TwiceMemIncreaser<U32>>::BidirectionalIterator iter = bv.front();
		while(!iter.empty())
		{
			++iter;
		}

		Array<N32, 32> temp;
		temp[0] = 10;
	}
}