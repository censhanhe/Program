#ifndef		__GAIA_ALGORITHM_SORT_H__
#define		__GAIA_ALGORITHM_SORT_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType> GAIA::GVOID qsort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
			if(pBegin >= pEnd)
				return;
			_DataType* pBeginT = pBegin;
			_DataType* pEndT = pEnd;
			_DataType* pMid = pBegin; // pMid works as a cursor.
			while(pBeginT < pEndT)
			{
				if(*pBeginT < *pEndT)
				{
					GAIA::ALGORITHM::swap(*pBeginT, *pMid);
					++pMid;
				}
				++pBeginT;
			}
			GAIA::ALGORITHM::swap(*pMid, *pEnd);
			GAIA::ALGORITHM::qsort(pBegin, pMid - 1);
			GAIA::ALGORITHM::qsort(pMid + 1, pEnd);
		}
		template <typename _DataType> GAIA::GVOID bsort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
			while(pBegin < pEnd)
			{
				_DataType* pTemp = pBegin + 1;
				while(pTemp <= pEnd)
				{
					if(*pBegin > *pTemp)
						GAIA::ALGORITHM::swap(*pBegin, *pTemp);
					++pTemp;
				}
				++pBegin;
			}
		}
		template <typename _DataType> GAIA::GVOID esort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
		}
		template <typename _DataType> GAIA::GVOID sort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
			if(pEnd - pBegin < 10)
				bsort(pBegin, pEnd);
			else
				qsort(pBegin, pEnd);
		}
		template <typename _DataType> GAIA::BL issorted(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin > *(pBegin + 1))
					return GAIA::False;
				++pBegin;
			}
			return GAIA::False;
		}
	};
};

#endif
