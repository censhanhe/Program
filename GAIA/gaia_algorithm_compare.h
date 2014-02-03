#ifndef		__GAIA_ALGORITHM_COMPARE_H__
#define		__GAIA_ALGORITHM_COMPARE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType& maximize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 > v2)
				return v1;
			else if(v1 < v2)
				return v2;
			else
				return v1;
		}
		template <typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType& minimize(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return v1;
			else if(v1 > v2)
				return v2;
			else
				return v1;
		}
		template <typename _DataType, typename _SizeType> GINL const _DataType& maximize(const _DataType* p, const _SizeType& size)
		{
			_SizeType resindex = 0;
			for(_SizeType x = 1; x < size; ++x)
			{
				if(p[resindex] < p[x])
					resindex = x;
			}
			return p[resindex];
		}
		template <typename _DataType, typename _SizeType> GINL const _DataType& minimize(const _DataType* p, const _SizeType& size)
		{
			_SizeType resindex = 0;
			for(_SizeType x = 1; x < size; ++x)
			{
				if(p[resindex] > p[x])
					resindex = x;
			}
			return p[resindex];
		}
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return -1;
			else if(v1 > v2)
				return +1;
			else
				return 0;
		}
		template <typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::N32 cmp(const _DataType1* p1, const _DataType2* p2, const _SizeType& size)
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
		template <typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::N32 cmp(const _DataType1* p, const _DataType2& key, const _SizeType& size)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp2(const _DataType1* p1, const _DataType2* p2)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp2(const _DataType1* p, const _DataType2& key)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp3(const _DataType1* p1, const _DataType2* p2)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp3(const _DataType1* p, const _DataType2& key)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp4(const _DataType1* p1, const _DataType2* p2)
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
		template <typename _DataType1, typename _DataType2> GINL GAIA::N32 cmp4(const _DataType1* p, const _DataType2& key)
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
		template <typename _DataType, typename _SizeType> GINL GAIA::GVOID copy(_DataType* dst, const _DataType* src, const _SizeType& size)
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
		template <typename _DataType, typename _SizeType> GINL GAIA::GVOID set(_DataType* dst, const _DataType& t, const _SizeType& size)
		{
			_SizeType sizet = size;
			while(sizet > 0)
			{
				*dst = t;
				++dst;
				--sizet;
			}
		}
		template <typename _DataType> GINL _DataType abs(const _DataType& t)
		{
			if(t < 0)
				return -t;
			return t;
		}
		template <typename _DataType, typename _ParamType1, typename _ParamType2> GINL _DataType clamp(const _DataType& src, const _ParamType1& limitlow, const _ParamType2& limithigh)
		{
			GAIA_ASSERT(limitlow <= limithigh);
			_DataType ret = src;
			if(ret < limitlow)
				ret = (_DataType)limitlow;
			if(ret > limithigh)
				ret = (_DataType)limithigh;
			return ret;
		}
		template <typename _DataType> GINL _DataType saturate(const _DataType& src)
		{
			return clamp(src, (_DataType)0, (_DataType)1);
		}
		template <typename _DataType> GINL _DataType floor(const _DataType& src)
		{
		}
		template <typename _DataType> GINL _DataType ceil(const _DataType& src)
		{
		}
	};
};

#endif
