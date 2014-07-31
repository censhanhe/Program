#ifndef		__GAIA_ALGORITHM_BASE_H__
#define		__GAIA_ALGORITHM_BASE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType1, typename _DataType2> GAIA::GVOID move(_DataType1& dst, const _DataType2& src){dst = src;}
		template<typename _DataType, typename _SizeType> GAIA::GVOID move_prev(_DataType p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				*p = *(p + 1);
				++p;
			}
		}
		template<typename _DataType, typename _SizeType> GAIA::GVOID move_next(_DataType p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				*p = *(p - 1);
				--p;
			}
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID move_prev(_DataType1 dst, _DataType2 src, const _SizeType& size)
		{
			_SizeType sizetemp = size;
			while(sizetemp > 0)
			{
				*dst = *src;
				++dst;
				++src;
				--sizetemp;
			}
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID move_next(_DataType1 dst, _DataType2 src, const _SizeType& size)
		{
			_SizeType sizetemp = size;
			while(sizetemp > 0)
			{
				*dst = *src;
				--dst;
				--src;
				--sizetemp;
			}
		}
		template<typename _DataType1, typename _DataType2> GAIA::GVOID swap(_DataType1& t1, _DataType2& t2)
		{
			typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType t = t2;
			t2 = t1;
			t1 = t;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID swaps(_DataType1 p1, _DataType2 p2, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
				GAIA::ALGORITHM::swap(p1[x], p2[x]);
		}
		template<typename _DataType, typename _KeyType> _DataType swapleft(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			_DataType pTemp = pBegin;
			while(pTemp <= pEnd)
			{
				if(*pTemp == key)
				{
					if(pBegin != pTemp)
						GAIA::ALGORITHM::swap(*pBegin, *pTemp);
					++pBegin;
				}
				++pTemp;
			}
			return pBegin;
		}
		template<typename _DataType, typename _KeyType> _DataType swapleft(_DataType pBegin, _DataType pEnd, _KeyType pKeyBegin, _KeyType pKeyEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(!!pKeyBegin);
			GAIA_AST(!!pKeyBegin);
			while(pKeyBegin <= pKeyEnd)
			{
				pBegin = GAIA::ALGORITHM::swapleft(pBegin, pEnd, *pKeyBegin);
				++pKeyBegin;
			}
			return pBegin;
		}
		template<typename _DataType, typename _KeyType> _DataType swapleft_inversekey(_DataType pBegin, _DataType pEnd, const _KeyType& key)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			_DataType pTemp = pBegin;
			while(pTemp <= pEnd)
			{
				if(*pTemp != key)
				{
					if(pBegin != pTemp)
						GAIA::ALGORITHM::swap(*pBegin, *pTemp);
					++pBegin;
				}
				++pTemp;
			}
			return pBegin;
		}
		template<typename _DataType, typename _KeyType> _DataType swapleft_inversekey(_DataType pBegin, _DataType pEnd, _KeyType pKeyBegin, _KeyType pKeyEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			GAIA_AST(!!pKeyBegin);
			GAIA_AST(!!pKeyBegin);
			_DataType pTemp = pBegin;
			while(pTemp <= pEnd)
			{
				GAIA::BL bExist = GAIA::False;
				_KeyType pTempKey = pKeyBegin;
				while(pTempKey <= pKeyEnd)
				{
					if(*pTemp == *pTempKey)
					{
						bExist = GAIA::True;
						break;
					}
					++pTempKey;
				}
				if(!bExist)
				{
					if(pBegin != pTemp)
						GAIA::ALGORITHM::swap(*pBegin, *pTemp);
					++pBegin;
				}
				++pTemp;
			}
			return pBegin;
		}
		template<typename _DataType> GAIA::GVOID inverse(_DataType pBegin, _DataType pEnd)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			while(pBegin != pEnd)
			{
				GAIA::ALGORITHM::swap(*pBegin, *pEnd);
				++pBegin;
				if(pBegin == pEnd)
					break;
				--pEnd;
			}
		}
	};
};

#endif
