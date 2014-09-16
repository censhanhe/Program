#ifndef		__T_CONTAINER_BITSET_H__
#define		__T_CONTAINER_BITSET_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_bitset(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CTN::BasicBitset<GAIA::U32, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __BitsetType;
		__BitsetType b;
		if(!b.empty())
		{
			GTLINE2("New Bitset is not empty!");
			++nRet;
		}
		b.resize(255);
		if(b.size() != 255)
		{
			GTLINE2("New Bitset size is error!");
			++nRet;
		}
		if(b.capacity() != 255)
		{
			GTLINE2("New Bitset capacity is error!");
			++nRet;
		}
		b.clear();
		for(__BitsetType::_sizetype x = 0; x < b.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(b.exist(x))
			{
				GTLINE2("Bitset clean failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		for(__BitsetType::_sizetype x = 0; x < b.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			__BitsetType::_sizetype index = x;
			b.set(x);
			if(!b.exist(x))
			{
				GTLINE2("Bitset set failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			b.reset(x);
			if(b.exist(x))
			{
				GTLINE2("Bitset reset failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			b.inverse(x);
			if(!b.exist(x))
			{
				GTLINE2("Bitset inverse failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		if(b.size() != 255)
		{
			GTLINE2("Bitset set reset inverse change size error!");
			++nRet;
		}
		if(b.capacity() != 255)
		{
			GTLINE2("Bitset set reset inverse change capacity error!");
			++nRet;
		}
		b.clear();
		for(__BitsetType::_sizetype x = 0; x < b.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(b.exist(x))
			{
				GTLINE2("Bitset clean failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		b = ~b;
		__BitsetType b1 = b;
		for(__BitsetType::_sizetype x = 0; x < b.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(b.exist(x) != b1.exist(x))
			{
				GTLINE2("Bitset operator = failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		if(b.back_ptr() - b.front_ptr() != 31)
		{
			GTLINE2("Bitset back_ptr or front_ptr error!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b1 = b;
		if(!(b1 == b && b1 >= b && b1 <= b))
		{
			GTLINE2("Bitset operator == >= <= error!");
			++nRet;
		}
		if(b1 != b || b1 > b || b1 < b)
		{
			GTLINE2("Bitset operator != > < error!");
			++nRet;
		}
		b ^= b1;
		b ^= b1;
		if(b != b1)
		{
			GTLINE2("Bitset operator ^= error!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b ^= b;
		if(b != b1)
		{
			GTLINE2("Bitset operator ^= self error!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b = ~b;
		b &= b1;
		if(b != b1)
		{
			GTLINE2("Bitset operator &= failed!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b = ~b;
		b &= b1;
		if(b != b1)
		{
			GTLINE2("Bitset operator &= self failed!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b = ~b;
		b1 |= b;
		if(b1 != b)
		{
			GTLINE2("Bitset operator |= failed!");
			++nRet;
		}
		b.clear();
		b1.clear();
		b = ~b;
		b |= b;
		if(b != b)
		{
			GTLINE2("Bitset operator |= failed!");
			++nRet;
		}
		b.clear();
		b1.clear();
		if(!b.zero())
		{
			GTLINE2("Bitset zero failed!");
			++nRet;
		}
		if(b.one())
		{
			GTLINE2("Bitset one failed!");
			++nRet;
		}
		b = ~b;
		if(b.zero())
		{
			GTLINE2("Bitset zero failed!");
			++nRet;
		}
		if(!b.one())
		{
			GTLINE2("Bitset one failed!");
			++nRet;
		}
		b.reset(10);
		if(b.zero())
		{
			GTLINE2("Bitset zero failed!");
			++nRet;
		}
		if(b.one())
		{
			GTLINE2("Bitset one failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
