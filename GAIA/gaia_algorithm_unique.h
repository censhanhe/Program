#ifndef		__GAIA_ALGORITHM_UNIQUE_H__
#define		__GAIA_ALGORITHM_UNIQUE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType> GAIA::BL isunique(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin < pEnd)
			{
				_DataType pTemp = pBegin + 1;
				while(pTemp <= pEnd)
				{
					if(*pTemp == *pBegin)
						return GAIA::False;
					++pTemp;
				}
				++pBegin;
			}
			return GAIA::True;
		}
		template<typename _DataType> _DataType unique_order(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(pBegin <= pEnd);
			_DataType pLast = pBegin;
			++pBegin;
			while(pBegin <= pEnd)
			{
				if(*pBegin != *pLast)
				{
					++pLast;
					if(pLast != pBegin) // OPT for large object copy.
						*pLast = *pBegin;
				}
				++pBegin;
			}
			return pLast;
		}
		template<typename _DataType> _DataType unique_noorder(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(pBegin <= pEnd);
			_DataType pFirst = pBegin;
			_DataType pLast = pBegin;
			++pBegin;
			while(pBegin <= pEnd)
			{
				GAIA::BL bExist = GAIA::False;
				_DataType pTemp = pFirst;
				while(pTemp <= pLast)
				{
					if(*pTemp == *pBegin)
					{
						bExist = GAIA::True;
						break;
					}
					++pTemp;
				}
				if(!bExist)
				{
					++pLast;
					if(pLast != pBegin) // OPT for large object copy.
						*pLast = *pBegin;
				}
				++pBegin;
			}
			return pLast;
		}
	};
};

#endif
