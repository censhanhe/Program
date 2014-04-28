#ifndef		__GAIA_ALGORITHM_SORT_H__
#define		__GAIA_ALGORITHM_SORT_H__

#ifdef GAIA_USESTL
#	include <algorithm>
#endif

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType> GINL GAIA::GVOID bsort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			while(pBegin < pEnd)
			{
				_DataType pTemp = pBegin + 1;
				while(pTemp <= pEnd)
				{
					if(*pBegin > *pTemp)
						GAIA::ALGORITHM::swap(*pBegin, *pTemp);
					++pTemp;
				}
				++pBegin;
			}
		}
		template<typename _DataType> GINL GAIA::GVOID isort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID ssort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID hsort(_DataType pBegin, _DataType pEnd)
		{
		}
		template<typename _DataType> GINL GAIA::GVOID qsort(_DataType pBegin, _DataType pEnd)
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
			GAIA::ALGORITHM::swap(*pEnd, *(pBegin + (pEnd - pBegin) / 2));

			/* Standard quick sort algorithm. */
			_DataType pCursor = pBegin;
			_DataType pSplit = pBegin;
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
		#endif
		}
		template<typename _DataType> GINL GAIA::GVOID esort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin < pEnd);
		}
		template<typename _DataType> GINL GAIA::GVOID sort(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			if(pEnd - pBegin < 10)
				GAIA::ALGORITHM::bsort(pBegin, pEnd);
			else
				GAIA::ALGORITHM::qsort(pBegin, pEnd);
		}
		template<typename _DataType> GINL GAIA::BL issorted(_DataType pBegin, _DataType pEnd)
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
