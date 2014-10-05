#ifndef		__GAIA_ALGORITHM_COMPARE_H__
#define		__GAIA_ALGORITHM_COMPARE_H__

namespace GAIA
{
	namespace ALGO
	{
		template<typename _DataType1, typename _DataType2> const typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType maximize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 > v2)
				return v1;
			else if(v1 < v2)
				return v2;
			else
				return v1;
		}
		template<typename _DataType1, typename _DataType2> const typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType minimize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return v1;
			else if(v1 > v2)
				return v2;
			else
				return v1;
		}
		template<typename _DataType> _DataType maximize3(_DataType v1, _DataType v2, _DataType v3)
		{
			return maximize(maximize(v1, v2), v3);
		}
		template<typename _DataType> _DataType minimize3(_DataType v1, _DataType v2, _DataType v3)
		{
			return minimize(minimize(v1, v2), v3);
		}
		template<typename _DataType> _DataType middle3(_DataType v1, _DataType v2, _DataType v3)
		{
			if(v1 > v2)
			{
				if(v2 > v3)
					return v2;
				else
				{
					if(v3 > v1)
						return v1;
					else
						return v3;
				}
			}
			else
			{
				if(v1 > v3)
					return v1;
				else
				{
					if(v3 > v2)
						return v2;
					else
						return v3;
				}
			}
		}
		template<typename _DataType, typename _ResultType> GAIA::GVOID maximizes(_DataType pBegin, _DataType pEnd, _ResultType& res)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin > res)
					res = *pBegin;
				++pBegin;
			}
			if(*pBegin > res)
				res = *pBegin;
		}
		template<typename _DataType, typename _ResultType> GAIA::GVOID minimizes(_DataType pBegin, _DataType pEnd, _ResultType& res)
		{
			GAIA_AST(!!pBegin);
			GAIA_AST(!!pEnd);
			while(pBegin != pEnd)
			{
				if(*pBegin < res)
					res = *pBegin;
				++pBegin;
			}
			if(*pBegin < res)
				res = *pBegin;
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 cmp(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return -1;
			else if(v1 > v2)
				return +1;
			else
				return 0;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::N32 cmps(_DataType1 p1, _DataType2 p2, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				if(*p1 < *p2)
					return -1;
				else if(*p1 > *p2)
					return +1;
				++p1;
				++p2;
				--sizet;
			}
			return 0;
		}
		template<typename _DataType1, typename _SizeType1, typename _DataType2, typename _SizeType2> GAIA::N32 cmps(_DataType1 p1, const _SizeType1& size1, _DataType2 p2, const _SizeType2& size2)
		{
			if(size1 < size2)
				return -1;
			else if(size1 > size2)
				return +1;
			else
				return GAIA::ALGO::cmps(p1, p2, size1);
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::N32 cmpk(_DataType p, const _KeyType& key, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				if(*p < key)
					return -1;
				else if(*p > key)
					return +1;
				++p;
				--sizet;
			}
			return 0;
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 cmp2(_DataType1 p1, _DataType2 p2)
		{
			if(p1[0] < p2[0])
				return -1;
			else if(p1[0] > p2[0])
				return +1;
			else
			{
				if(p1[1] < p2[1])
					return -1;
				else if(p1[1] > p2[1])
					return +1;
				else
					return 0;
			}
		}
		template<typename _DataType, typename _KeyType> GAIA::N32 cmp2k(_DataType p, const _KeyType& key)
		{
			if(p[0] < key)
				return -1;
			else if(p[0] > key)
				return +1;
			else
			{
				if(p[1] < key)
					return -1;
				else if(p[1] > key)
					return +1;
				else
					return 0;
			}
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 cmp3(_DataType1 p1, _DataType2 p2)
		{
			if(p1[0] < p2[0])
				return -1;
			else if(p1[0] > p2[0])
				return +1;
			else
			{
				if(p1[1] < p2[1])
					return -1;
				else if(p1[1] > p2[1])
					return +1;
				else
				{
					if(p1[2] < p2[2])
						return -1;
					else if(p1[2] > p2[2])
						return +1;
					else
						return 0;
				}
			}
		}
		template<typename _DataType, typename _KeyType> GAIA::N32 cmp3k(_DataType p, const _KeyType& key)
		{
			if(p[0] < key)
				return -1;
			else if(p[0] > key)
				return +1;
			else
			{
				if(p[1] < key)
					return -1;
				else if(p[1] > key)
					return +1;
				else
				{
					if(p[2] < key)
						return -1;
					else if(p[2] > key)
						return +1;
					else
						return 0;
				}
			}
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 cmp4(_DataType1 p1, _DataType2 p2)
		{
			if(p1[0] < p2[0])
				return -1;
			else if(p1[0] > p2[0])
				return +1;
			else
			{
				if(p1[1] < p2[1])
					return -1;
				else if(p1[1] > p2[1])
					return +1;
				else
				{
					if(p1[2] < p2[2])
						return -1;
					else if(p1[2] > p2[2])
						return +1;
					else
					{
						if(p1[3] < p2[3])
							return -1;
						else if(p1[3] > p2[3])
							return +1;
						else
							return 0;
					}
				}
			}
		}
		template<typename _DataType, typename _KeyType> GAIA::N32 cmp4k(_DataType p, const _KeyType& key)
		{
			if(p[0] < key)
				return -1;
			else if(p[0] > key)
				return +1;
			else
			{
				if(p[1] < key)
					return -1;
				else if(p[1] > key)
					return +1;
				else
				{
					if(p[2] < key)
						return -1;
					else if(p[2] > key)
						return +1;
					else
					{
						if(p[3] < key)
							return -1;
						else if(p[3] > key)
							return +1;
						else
							return 0;
					}
				}
			}
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 cmpp(_DataType1 p1, _DataType2 p2)
		{
			if(p1 == GNIL && p2 == GNIL)
				return 0;
			else if(p1 != GNIL && p2 == GNIL)
				return -1;
			else if(p1 == GNIL && p2 != GNIL)
				return +1;
			else
			{
				if(*p1 < *p2)
					return -1;
				else if(*p1 > *p2)
					return +1;
				else
					return 0;
			}
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID copy(_DataType1 dst, _DataType2 src, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				*dst = *src;
				++src;
				++dst;
				--sizet;
			}
		}
		template<typename _DataType, typename _SizeType> GAIA::GVOID nil(_DataType dst, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				*dst = GNIL;
				++dst;
				--sizet;
			}
		}
		template<typename _DataType, typename _KeyType, typename _SizeType> GAIA::GVOID set(_DataType dst, const _KeyType& t, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				*dst = t;
				++dst;
				--sizet;
			}
		}
	};
};

#endif
