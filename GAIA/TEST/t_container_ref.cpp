#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_ref(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ELEMENT_COUNT = 100;
		GAIA::N32* pElements = GAIA_MALLOC(GAIA::N32, ELEMENT_COUNT);
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
			pElements[x] = x;

		typedef GAIA::CTN::Ref<GAIA::N32> __RefType;
		{
			__RefType rr;
			if(!rr.empty())
			{
				GTLINE2("New ref must empty!");
				++nRet;
			}
		}
		__RefType r = pElements;
		if(r.empty())
		{
			GTLINE2("Ref construct from valid pointer must not been empty!");
			++nRet;
		}
		if(*r != 0)
		{
			GTLINE2("Ref operator * failed!");
			++nRet;
		}
		if(**static_cast<const __RefType*>(&r) != 0)
		{
			GTLINE2("Ref const operator * failed!");
			++nRet;
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if(r[x] != x)
			{
				GTLINE2("Ref operator [] failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if((*static_cast<const __RefType*>(&r))[x] != x)
			{
				GTLINE2("Ref operator [] failed!");
				++nRet;
				break;
			}
		}
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
			r[x] = 123456;
		for(GAIA::N32 x = 0; x < ELEMENT_COUNT; ++x)
		{
			if(r[x] != 123456)
			{
				GTLINE2("Ref operator [] failed!");
				++nRet;
				break;
			}
		}
		__RefType r1 = r;
		if(!(r1 == r && r1 >= r && r1 <= r))
		{
			GTLINE2("Ref operator == __MyType failed!");
			++nRet;
		}
		if(r1 != r || r1 > r || r1 < r)
		{
			GTLINE2("Ref operator != __MyType failed!");
			++nRet;
		}
		if(!(r == pElements && r >= pElements && r <= pElements))
		{
			GTLINE2("Ref operator == >= <= pointer failed!");
			++nRet;
		}
		if(r != pElements || r > pElements || r < pElements)
		{
			GTLINE2("Ref operator != > < pointer failed!");
			++nRet;
		}
		if(!(r == GSCAST(const GAIA::N32*)(pElements) && r >= GSCAST(const GAIA::N32*)(pElements) && r <= GSCAST(const GAIA::N32*)(pElements)))
		{
			GTLINE2("Ref operator == >= <= pointer failed!");
			++nRet;
		}
		if(r != GSCAST(const GAIA::N32*)(pElements) || r > GSCAST(const GAIA::N32*)(pElements) || r < GSCAST(const GAIA::N32*)(pElements))
		{
			GTLINE2("Ref operator != > < pointer failed!");
			++nRet;
		}
		GAIA::N32* pElementTemp = r;
		if(r != pElementTemp)
		{
			GTLINE2("Ref operator _DataType* failed!");
			++nRet;
		}
		const GAIA::N32* pConstElementTemp = r;
		if(r != pConstElementTemp)
		{
			GTLINE2("Ref operator const _DataType* failed!");
			++nRet;
		}
		GAIA_MFREE(pElements);
		pElements = GNIL;
		return nRet;
	}
};
