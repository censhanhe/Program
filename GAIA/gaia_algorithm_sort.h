#ifndef		__GAIA_ALGORITHM_SORT_H__
#define		__GAIA_ALGORITHM_SORT_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType> GINL GAIA::GVOID bsort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
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
		template<typename _DataType> GINL GAIA::GVOID isort(_DataType* pBegin, _DataType* pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID ssort(_DataType* pBegin, _DataType* pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID hsort(_DataType* pBegin, _DataType* pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID qsort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			if(pBegin >= pEnd)
				return;
			if(pEnd - pBegin < 10)
				return bsort(pBegin, pEnd);

			/* Inverse order optimize and find mid element. */
//#define INVERSE
#ifdef INVERSE
			if((pEnd - pBegin) * sizeof(_DataType) > 10000)
			{
				/* Inverse order optimize. */
				GAIA::NM nIncreaseCnt = 0;
				GAIA::NM nDecreaseCnt = 0;
				_DataType* pCursor = pBegin;
				while(pCursor < pEnd)
				{
					if(*pCursor < *(pCursor + 1))
						nIncreaseCnt++;
					else if(*pCursor > *(pCursor + 1))
						nDecreaseCnt++;
					++pCursor;
				}
				if(nDecreaseCnt == 0)
					return;
				if(nDecreaseCnt > nIncreaseCnt * 2)
					GAIA::ALGORITHM::inverse(pBegin, pEnd);
			}
#endif

			GAIA::ALGORITHM::swap(*pEnd, *(pBegin + (pEnd - pBegin) / 2));

			/* Standard quick sort algorithm. */
			_DataType* pCursor = pBegin;
			_DataType* pSplit = pBegin;
			while(pCursor < pEnd)
			{
				if(*pCursor < *pEnd) // pEnd is the key.
				{
					GAIA::ALGORITHM::swap(*pCursor, *pSplit);
					++pSplit;
				}
				++pCursor;
			}
			GAIA::ALGORITHM::swap(*pSplit, *pEnd);
			GAIA::ALGORITHM::qsort(pBegin, pSplit - 1);
			GAIA::ALGORITHM::qsort(pSplit + 1, pEnd);
		}
		template<typename _DataType> GINL GAIA::GVOID esort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(pBegin < pEnd);
		}
		template<typename _DataType> GINL GAIA::GVOID sort(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			if(pEnd - pBegin < 10)
				bsort(pBegin, pEnd);
			else
				qsort(pBegin, pEnd);
		}
		template<typename _DataType> GINL GAIA::BL issorted(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(pBegin < pEnd);
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
