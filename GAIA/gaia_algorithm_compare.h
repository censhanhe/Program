#ifndef		__GAIA_ALGORITHM_COMPARE_H__
#define		__GAIA_ALGORITHM_COMPARE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType maximize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 > v2)
				return v1;
			else if(v1 < v2)
				return v2;
			else
				return v1;
		}
		template<typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType minimize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return v1;
			else if(v1 > v2)
				return v2;
			else
				return v1;
		}
		template<typename _DataType, typename _SizeType> GINL const _DataType& maximize(const _DataType* p, const _SizeType& size)
		{
			_SizeType resindex = 0;
			for(_SizeType x = 1; x < size; ++x)
			{
				if(p[resindex] < p[x])
					resindex = x;
			}
			return p[resindex];
		}
		template<typename _DataType, typename _SizeType> GINL const _DataType& minimize(const _DataType* p, const _SizeType& size)
		{
			_SizeType resindex = 0;
			for(_SizeType x = 1; x < size; ++x)
			{
				if(p[resindex] > p[x])
					resindex = x;
			}
			return p[resindex];
		}
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return -1;
			else if(v1 > v2)
				return +1;
			else
				return 0;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::N32 cmp(const _DataType1* p1, const _DataType2* p2, const _SizeType& size)
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
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::N32 cmp(const _DataType1* p, const _DataType2& key, const _SizeType& size)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp2(const _DataType1* p1, const _DataType2* p2)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp2(const _DataType1* p, const _DataType2& key)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp3(const _DataType1* p1, const _DataType2* p2)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp3(const _DataType1* p, const _DataType2& key)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp4(const _DataType1* p1, const _DataType2* p2)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp4(const _DataType1* p, const _DataType2& key)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 cmpp(const _DataType1* p1, const _DataType2* p2)
		{
			if(p1 == GNULL && p2 == GNULL)
				return 0;
			else if(p1 != GNULL && p2 == GNULL)
				return -1;
			else if(p1 == GNULL && p2 != GNULL)
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
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::GVOID copy(_DataType1* dst, const _DataType2* src, const _SizeType& size)
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
		template<typename _DataType, typename _KeyType, typename _SizeType> GINL GAIA::GVOID set(_DataType* dst, const _KeyType& t, const _SizeType& size)
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
