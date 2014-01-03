#ifndef		__GAIA_ARITHMETIC_COMPARE_H__
#define		__GAIA_ARITHMETIC_COMPARE_H__

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
	};
};

#endif