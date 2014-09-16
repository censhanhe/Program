#ifndef		__GAIA_ALGORITHM_SORT_H__
#define		__GAIA_ALGORITHM_SORT_H__

#ifdef GAIA_USESTL
#	include <algorithm>
#endif

namespace GAIA
{
	namespace ALGO
	{
		template<typename _DataType> GAIA::GVOID bsort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			while(pBegin < pEnd)
			{
				_DataType pTemp = pBegin + 1;
				while(pTemp <= pEnd)
				{
					if(*pBegin > *pTemp)
						GAIA::ALGO::swap(*pBegin, *pTemp);
					++pTemp;
				}
				++pBegin;
			}
		}
		template<typename _DataType> GAIA::GVOID isort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GAIA::GVOID ssort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GAIA::GVOID hsort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GAIA::GVOID qsort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			if(pBegin >= pEnd)
				return;
		#ifdef GAIA_USESTL
			std::sort(pBegin, pEnd + 1);
		#else
			// quick sort optimize.
			if(pEnd - pBegin < 16)
				return bsort(pBegin, pEnd);
			GAIA::ALGO::swap(*pEnd, *(pBegin + (pEnd - pBegin) / 2));

			/* Standard quick sort algorithm. */
			_DataType pCursor = pBegin;
			_DataType pSplit = pBegin;
			while(pCursor < pEnd)
			{
				if(*pCursor < *pEnd) // pEnd is the key.
				{
					GAIA::ALGO::swap(*pCursor, *pSplit);
					++pSplit;
				}
				++pCursor;
			}
			GAIA::ALGO::swap(*pSplit, *pEnd);
			GAIA::ALGO::qsort(pBegin, pSplit - 1);
			GAIA::ALGO::qsort(pSplit + 1, pEnd);
		#endif
		}
		template<typename _DataType> GAIA::GVOID esort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin < pEnd);
		}
		template<typename _DataType> GAIA::GVOID sort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			if(pEnd - pBegin < 10)
				GAIA::ALGO::bsort(pBegin, pEnd);
			else
				GAIA::ALGO::qsort(pBegin, pEnd);
		}
		template<typename _DataType> GAIA::BL issorted(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin < pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin > *(pBegin + 1))
					return GAIA::False;
				++pBegin;
			}
			return GAIA::True;
		}
	};
};

#endif
