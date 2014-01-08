#ifndef		__GAIA_ALGORITHM_SEARCH_H__
#define		__GAIA_ALGORITHM_SEARCH_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType> _DataType* bsearch(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin <= pEnd);
			if(pBegin == pEnd)
			{
				if(*pBegin == key)
					return const_cast<_DataType*>(pBegin);
				return GNULL;
			}
			_DataType* pMid = const_cast<_DataType*>(pBegin + (pEnd - pBegin) / 2);
			if(key <= *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::bsearch(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key > *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::bsearch(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}	
			return GNULL;
		}
		template <typename _DataType> _DataType* ssearch(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin <= pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin == key)
					return const_cast<_DataType*>(pBegin);
				++pBegin;
			}
			return GNULL;
		}
		template <typename _DataType> _DataType* search(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin <= pEnd);
			if(pEnd < pBegin)
				return GNULL;
			if(pEnd == pBegin)
			{
				if(*pBegin == key)
					return const_cast<_DataType*>(pBegin);
				return GNULL;
			}
			if(pEnd - pBegin < 10)
				return ssearch(pBegin, pEnd, key);
			return bsearch(pBegin, pEnd, key);
		}
		template <typename _DataType> _DataType* lower_bound(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin <= pEnd);
			if(pBegin == pEnd)
			{
				if(*pBegin >= key)
					return pBegin;
				return GNULL;
			}
			_DataType* pMid = pBegin + (pEnd - pBegin) / 2;
			if(key <= *pMid)
			{
				_DataType* pRet = lower_bound(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key > *pMid)
			{
				_DataType* pRet = lower_bound(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
		template <typename _DataType> _DataType* upper_bound(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_ASSERT(pBegin != GNULL);
			GAIA_ASSERT(pEnd != GNULL);
			GAIA_ASSERT(pBegin < pEnd);
			if(pBegin == pEnd)
			{
				if(*pEnd <= key)
					return pEnd;
				return GNULL;
			}
			_DataType* pMid = pBegin + (pEnd - pBegin) / 2;
			if(key > *pMid)
			{
				_DataType* pRet = lower_bound(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key <= *pMid)
			{
				_DataType* pRet = lower_bound(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
	};
};

#endif
