#ifndef		__GAIA_ALGORITHM_SEARCH_H__
#define		__GAIA_ALGORITHM_SEARCH_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType, typename _SizeType> GINL GAIA::BL equal(const _DataType* pBegin, const _DataType* p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				if(pBegin[x] != p[x])
					return GAIA::False;
			}
			return GAIA::True;
		}
		template<typename _DataType> GINL _DataType* find(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			while(pBegin <= pEnd)
			{
				if(*pBegin == key)
					return const_cast<_DataType*>(pBegin);
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType** findp(const _DataType** pBegin, const _DataType** pEnd, const _DataType& key)
		{
			while(pBegin <= pEnd)
			{
				if(**pBegin == key)
					return const_cast<_DataType**>(pBegin);
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType, typename _SizeType> GINL _DataType* finds(const _DataType* pBegin, const _DataType* pEnd, const _DataType* p, const _SizeType& size)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(p != GNULL);
			GAIA_AST(size != 0);
			while(pEnd - pBegin + 1 >= size)
			{
				if(equal(pBegin, p, size))
					return const_cast<_DataType*>(pBegin);
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* rfind(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			while(pBegin <= pEnd)
			{
				if(*pEnd == key)
					return const_cast<_DataType*>(pEnd);
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* rfindp(const _DataType** pBegin, const _DataType** pEnd, const _DataType& key)
		{
			while(pBegin <= pEnd)
			{
				if(**pEnd == key)
					return const_cast<_DataType**>(pEnd);
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType, typename _SizeType> GINL _DataType* rfinds(const _DataType* pBegin, const _DataType* pEnd, const _DataType* p, const _SizeType& size)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(p != GNULL);
			GAIA_AST(size != 0);
			while(pEnd - pBegin + 1 >= size)
			{
				if(equal(pEnd - size + 1, p, size))
					return const_cast<_DataType*>(pEnd - size + 1);
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* bsearch(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(pBegin <= pEnd);
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
		template<typename _DataType> GINL _DataType* ssearch(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(pBegin <= pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin == key)
					return const_cast<_DataType*>(pBegin);
				++pBegin;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* search(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			GAIA_AST(pBegin <= pEnd);
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
		template<typename _DataType> GINL _DataType* lower_bound(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			if(pBegin == pEnd)
			{
				if(*pBegin >= key)
					return const_cast<_DataType*>(pBegin);
				return GNULL;
			}
			const _DataType* pMid = pBegin + (pEnd - pBegin) / 2;
			if(key <= *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::lower_bound(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key > *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::lower_bound(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* upper_bound(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			if(pBegin == pEnd)
			{
				if(*pEnd <= key)
					return const_cast<_DataType*>(pEnd);
				return GNULL;
			}
			const _DataType* pMid = pBegin + (pEnd - pBegin) / 2;
			if(key > *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::upper_bound(pMid + 1, pEnd, key);
				if(pRet != GNULL)
					return pRet;
			}
			else if(key <= *pMid)
			{
				_DataType* pRet = GAIA::ALGORITHM::upper_bound(pBegin, pMid, key);
				if(pRet != GNULL)
					return pRet;
			}
			return GNULL;
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID index(const _DataType* pBegin, const _DataType* pCurrent, _SizeType& result)
		{
			result = pCurrent - pBegin;
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID count(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin == key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID lower_equal_count(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin <= key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID upper_equal_count(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin >= key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID lower_count(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key, _SizeType& result)
		{
			GAIA_AST(pBegin <= pEnd);
			while(pBegin <= pEnd)
			{
				if(*pBegin < key)
					++result;
				++pBegin;
			}
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID upper_count(const _DataType* pBegin, const _DataType* pEnd, const _DataType& key, _SizeType& result)
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
