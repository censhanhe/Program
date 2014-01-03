#ifndef		__GAIA_ARITHMETIC_COMPARE_H__
#define		__GAIA_ARITHMETIC_COMPARE_H__

namespace GAIA
{
	template <typename _DataType> GINL const _DataType& max(const _DataType& v1, const _DataType& v2)
	{
		if(v1 > v2)
			return v1;
		else if(v1 < v2)
			return v2;
		else
			return v1;
	}

	template <typename _DataType> GINL const _DataType& min(const _DataType& v1, const _DataType& v2)
	{
		if(v1 < v2)
			return v1;
		else if(v1 > v2)
			return v2;
		else
			return v1;
	}
};

#endif