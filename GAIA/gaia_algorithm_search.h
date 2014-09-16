#ifndef		__GAIA_ALGORITHM_SEARCH_H__
#define		__GAIA_ALGORITHM_SEARCH_H__

namespace GAIA
{
	namespace ALGO
	{
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::BL equal(_DataType1 pBegin, _DataType2 p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				if(pBegin[x] != p[x])
					return GAIA::False;
			}
			return GAIA::True;
		}
		template<typename _DataType, typename _KeyType> _DataType find(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			while(pBegin <= pEnd)
			{
				if(*pBegin == key)
					return pBegin;
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType* findp(const _DataType** ppBegin, const _DataType** ppEnd, const _KeyType& key)
		{
			while(ppBegin <= ppEnd)
			{
				if(**ppBegin == key)
					return const_cast<_DataType*>(*ppBegin);
				++ppBegin;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> _DataType finds(_DataType pBegin, _DataType pEnd, _KeyType p, const _SizeType& size)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(!!p);
			GAIA_AST(size != 0);
			while(pEnd - pBegin + 1 >= size)
			{
				if(GAIA::ALGO::equal(pBegin, p, size))
					return pBegin;
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType rfind(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			while(pBegin <= pEnd)
			{
				if(*pEnd == key)
					return pEnd;
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType* rfindp(const _DataType** ppBegin, const _DataType** ppEnd, const _KeyType& key)
		{
			while(ppBegin <= ppEnd)
			{
				if(**ppEnd == key)
					return const_cast<_DataType*>(*ppEnd);
				--ppEnd;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> _DataType rfinds(_DataType pBegin, _DataType pEnd, _KeyType p, const _SizeType& size)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(!!p);
			GAIA_AST(size != 0);
			while(pEnd - pBegin + 1 >= size)
			{
				if(GAIA::ALGO::equal(pEnd - size + 1, p, size))
					return pEnd - size + 1;
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType ssearch(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin == key)
					return pBegin;
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType bsearch(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin <= pEnd);
			if(pBegin == pEnd)
			{
				if(*pBegin == key)
					return pBegin;
				return GNULL;
			}
			else
			{
				if(pEnd - pBegin <= 16)
					return GAIA::ALGO::ssearch(pBegin, pEnd, key);
			}
			_DataType pMid = pBegin + (pEnd - pBegin) / 2;
			if(key <= *pMid)
				return GAIA::ALGO::bsearch(pBegin, pMid, key);
			else if(key > *pMid)
				return GAIA::ALGO::bsearch(pMid + 1, pEnd, key);
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType search(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(pBegin <= pEnd);
			if(pEnd < pBegin)
				return GNULL;
			if(pEnd == pBegin)
			{
				if(*pBegin == key)
					return pBegin;
				return GNULL;
			}
			return GAIA::ALGO::bsearch(pBegin, pEnd, key);
		}
		template<typename _DataType, typename _KeyType> _DataType lower_bound(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			if(pBegin == pEnd)
			{
				if(*pBegin >= key)
					return pBegin;
				return GNULL;
			}
			_DataType pMid = pBegin + (pEnd - pBegin) / 2;
			if(key <= *pMid)
			{
				_DataType pRet = GAIA::ALGO::lower_bound(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key > *pMid)
			{
				_DataType pRet = GAIA::ALGO::lower_bound(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
		template<typename _DataType, typename _KeyType> _DataType upper_bound(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			if(pBegin == pEnd)
			{
				if(*pEnd <= key)
					return pEnd;
				return GNULL;
			}
			_DataType pMid = pBegin + (pEnd - pBegin) / 2;
			if((pEnd - pBegin) % 2 != 0)
				++pMid;
			if(key >= *pMid)
			{
				_DataType pRet = GAIA::ALGO::upper_bound(pMid, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key < *pMid)
			{
				_DataType pRet = GAIA::ALGO::upper_bound(pBegin, pMid - 1, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
		template<typename _DataType, typename _SizeType> GAIA::GVOID index(_DataType pBegin, _DataType pCurrent, _SizeType& result)
		{
			result = pCurrent - pBegin;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID count(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin == key)
					++result;
				++pBegin;
			}
			if(*pBegin == key)
				++result;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID counts(_DataType pBegin, _DataType pEnd, _KeyType pKeyBegin, _KeyType pKeyEnd, _SizeType& result)
		{
			GAIA_AST(pKeyBegin <= pKeyEnd);
			while(pKeyBegin != pKeyEnd)
			{
				GAIA::ALGO::count(pBegin, pEnd, *pKeyBegin, result);
				++pKeyBegin;
			}
			GAIA::ALGO::count(pBegin, pEnd, *pKeyBegin, result);
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID prevcount(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin != pEnd)
			{
				if(*pEnd != key)
					break;
				--pEnd;
				++result;
			}
			if(*pEnd == key)
				++result;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID nextcount(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin != key)
					break;
				++pBegin;
				++result;
			}
			if(*pBegin == key)
				++result;
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID lower_equal_count(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin <= key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID upper_equal_count(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin >= key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID lower_count(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin < key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID upper_count(_DataType pBegin, _DataType pEnd, const _KeyType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin > key)
					++result;
				++pBegin;
			}
		}
	};
};

#endif
