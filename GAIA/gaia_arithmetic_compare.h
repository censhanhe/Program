#ifndef		__GAIA_ARITHMETIC_COMPARE_H__
#define		__GAIA_ARITHMETIC_COMPARE_H__

namespace GAIA
{
	template <typename _Type> GINL const _Type& max(const _Type& v1, const _Type& v2)
	{
		if(v1 > v2)
			return v1;
		else if(v1 < v2)
			return v2;
		else
			return v1;
	}

	template <typename _Type> GINL const _Type& min(const _Type& v1, const _Type& v2)
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