#ifndef		__T_CONTAINER_STACKBITSET_H__
#define		__T_CONTAINER_STACKBITSET_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_stackbitset(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;
		typedef GAIA::CTN::BasicStackBitset<GAIA::U32, 255> __StackBitsetType;
		__StackBitsetType sb;
		if(sb.empty())
		{
			GTLINE2("New StackBitset is empty!");
			++nRet;
		}
		if(sb.size() != 255 * 8)
		{
			GTLINE2("New StackBitset size is error!");
			++nRet;
		}
		if(sb.capacity() != 255 * 8)
		{
			GTLINE2("New StackBitset capacity is error!");
			++nRet;
		}
		sb.clear();
		for(__StackBitsetType::_sizetype x = 0; x < sb.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(sb.exist(x))
			{
				GTLINE2("StackBitset clean failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		for(__StackBitsetType::_sizetype x = 0; x < sb.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			__StackBitsetType::_sizetype index = x;
			sb.set(index);
			if(!sb.exist(index))
			{
				GTLINE2("StackBitset set failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			sb.reset(index);
			if(sb.exist(index))
			{
				GTLINE2("StackBitset reset failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			sb.inverse(index);
			if(!sb.exist(index))
			{
				GTLINE2("StackBitset inverse failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		if(sb.size() != 255 * 8)
		{
			GTLINE2("StackBitset set reset inverse change size error!");
			++nRet;
		}
		if(sb.capacity() != 255 * 8)
		{
			GTLINE2("StackBitset set reset inverse change capacity error!");
			++nRet;
		}
		sb.clear();
		for(__StackBitsetType::_sizetype x = 0; x < sb.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(sb.exist(x))
			{
				GTLINE2("StackBitset clean failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		sb = ~sb;
		__StackBitsetType sb1 = sb;
		for(__StackBitsetType::_sizetype x = 0; x < sb.size(); ++x)
		{
			GAIA::BL bInvalid = GAIA::False;
			if(sb.exist(x) != sb1.exist(x))
			{
				GTLINE2("StackBitset operator = failed!");
				++nRet;
				bInvalid = GAIA::True;
				break;
			}
			if(bInvalid)
				break;
		}
		if(sb.back_ptr() - sb.front_ptr() != 254)
		{
			GTLINE2("StackBitset back_ptr or front_ptr error!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb1 = sb;
		if(!(sb1 == sb && sb1 >= sb && sb1 <= sb))
		{
			GTLINE2("StackBitset operator == >= <= error!");
			++nRet;
		}
		if(sb1 != sb || sb1 > sb || sb1 < sb)
		{
			GTLINE2("StackBitset operator != > < error!");
			++nRet;
		}
		sb ^= sb1;
		sb ^= sb1;
		if(sb != sb1)
		{
			GTLINE2("StackBitset operator ^= error!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb ^= sb;
		if(sb != sb1)
		{
			GTLINE2("StackBitset operator ^= self error!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb = ~sb;
		sb &= sb1;
		if(sb != sb1)
		{
			GTLINE2("StackBitset operator &= failed!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb = ~sb;
		sb &= sb1;
		if(sb != sb1)
		{
			GTLINE2("StackBitset operator &= self failed!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb = ~sb;
		sb1 |= sb;
		if(sb1 != sb)
		{
			GTLINE2("StackBitset operator |= failed!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		sb = ~sb;
		sb |= sb;
		if(sb != sb)
		{
			GTLINE2("StackBitset operator |= failed!");
			++nRet;
		}
		sb.clear();
		sb1.clear();
		if(!sb.zero())
		{
			GTLINE2("StackBitset zero failed!");
			++nRet;
		}
		if(sb.one())
		{
			GTLINE2("StackBitset one failed!");
			++nRet;
		}
		sb = ~sb;
		if(sb.zero())
		{
			GTLINE2("StackBitset zero failed!");
			++nRet;
		}
		if(!sb.one())
		{
			GTLINE2("StackBitset one failed!");
			++nRet;
		}
		sb.reset(10);
		if(sb.zero())
		{
			GTLINE2("StackBitset zero failed!");
			++nRet;
		}
		if(sb.one())
		{
			GTLINE2("StackBitset one failed!");
			++nRet;
		}
		return nRet;
	}
};

#endif
