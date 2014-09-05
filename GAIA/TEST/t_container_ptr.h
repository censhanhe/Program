#ifndef		__T_CONTAINER_PTR_H__
#define		__T_CONTAINER_PTR_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_ptr(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ELEMENT_COUNT = 100;
		GAIA::N32* pElements = GAIA_MALLOC(GAIA::N32, ELEMENT_COUNT);
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
			pElements[x] = x;
		typedef GAIA::CONTAINER::Ptr<GAIA::N32> __PtrType;
		{
			__PtrType pp;
			if(!pp.empty())
			{
				GTLINE2("New ptr must empty!");
				++nRet;
			}
		}
		__PtrType p = pElements;
		if(p.empty())
		{
			GTLINE2("Ptr construct from valid pointer must not been empty!");
			++nRet;
		}
		if(*p != 0)
		{
			GTLINE2("Ptr operator * failed!");
			++nRet;
		}
		if(**static_cast<const __PtrType*>(&p) != 0)
		{
			GTLINE2("Ptr const operator * failed!");
			++nRet;
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if(p[x] != x)
			{
				GTLINE2("Ptr operator [] failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if((*static_cast<const __PtrType*>(&p))[x] != x)
			{
				GTLINE2("Ptr operator [] failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
			p[x] = 123456;
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if(p[x] != 123456)
			{
				GTLINE2("Ptr operator [] failed!");
				++nRet;
				break;
			}
		}
		__PtrType p1 = p;
		if(!(p1 == p && p1 >= p && p1 <= p))
		{
			GTLINE2("Ptr operator == __MyType failed!");
			++nRet;
		}
		if(p1 != p || p1 > p || p1 < p)
		{
			GTLINE2("Ptr operator != __MyType failed!");
			++nRet;
		}
		if(!(p == pElements && p >= pElements && p <= pElements))
		{
			GTLINE2("Ptr operator == >= <= pointer failed!");
			++nRet;
		}
		if(p != pElements || p > pElements || p < pElements)
		{
			GTLINE2("Ptr operator != > < pointer failed!");
			++nRet;
		}
		if(!(p == GSCAST(const GAIA::N32*)(pElements) && p >= GSCAST(const GAIA::N32*)(pElements) && p <= GSCAST(const GAIA::N32*)(pElements)))
		{
			GTLINE2("Ptr operator == >= <= pointer failed!");
			++nRet;
		}
		if(p != GSCAST(const GAIA::N32*)(pElements) || p > GSCAST(const GAIA::N32*)(pElements) || p < GSCAST(const GAIA::N32*)(pElements))
		{
			GTLINE2("Ptr operator != > < pointer failed!");
			++nRet;
		}
		GAIA::N32* pElementTemp = p;
		if(p != pElementTemp)
		{
			GTLINE2("Ptr operator _DataType* failed!");
			++nRet;
		}
		const GAIA::N32* pConstElementTemp = p;
		if(p != pConstElementTemp)
		{
			GTLINE2("Ptr operator const _DataType* failed!");
			++nRet;
		}
		p1 = p + 1;
		if(p1 - p != 1)
		{
			GTLINE2("Ptr operator + offset or operator - __MyType failed!");
			++nRet;
		}
		if(p - p1 != -1)
		{
			GTLINE2("Ptr operator + offset or operator - __MyType failed!");
			++nRet;
		}
		p1 += 10;
		p1 -= 5;
		if(p1 - p != 6)
		{
			GTLINE2("Ptr operator += or -= failed!");
			++nRet;
		}
		if(p != ((p + 10) - 10))
		{
			GTLINE2("Ptr operator + or - failed!");
			++nRet;
		}
		p1 = p;
		p1++;
		++p1;
		p1--;
		--p1;
		if(p1 != p)
		{
			GTLINE2("Ptr operator ++ or -- failed!");
			++nRet;
		}
		if(p1 + 10 - p != 10)
		{
			GTLINE2("Ptr operator + or - failed!");
			++nRet;
		}
		if(p1 - 10 - p != -10)
		{
			GTLINE2("Ptr operator + or - failed!");
			++nRet;
		}
		GAIA_MFREE(pElements);
		pElements = GNULL;
		return nRet;
	}
};

#endif
