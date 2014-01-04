#ifndef		__GAIA_ALGORITHM_COMPARE_H__
#define		__GAIA_ALGORITHM_COMPARE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType& max(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 > v2)
				return v1;
			else if(v1 < v2)
				return v2;
			else
				return v1;
		}
		template <typename _DataType1, typename _DataType2> GINL const typename GAIA::DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType& min(const _DataType1& v1, const _DataType2& v2)
		{
			if(v1 < v2)
				return v1;
			else if(v1 > v2)
				return v2;
			else
				return v1;
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
		template <typename _DataType> GINL _DataType abs(const _DataType& t)
		{
			if(t < 0)
				return -t;
			return t;
		}
		template <typename _DataType, typename _ParamType1, typename _ParamType2> _DataType clamp(const _DataType& src, const _ParamType1& limitlow, const _ParamType2& limithigh)
		{
			GAIA_ASSERT(limitlow <= limithigh);
			_DataType ret = src;
			if(ret < limitlow)
				ret = (_DataType)limitlow;
			if(ret > limithigh)
				ret = (_DataType)limithigh;
			return ret;
		}
		template <typename _DataType> _DataType saturate(const _DataType& src)
		{
			return clamp(src, (_DataType)0, (_DataType)1);
		}
	};
};

#endif
