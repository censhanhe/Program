#ifndef		__GAIA_ARITHMETIC_COMPARE_H__
#define		__GAIA_ARITHMETIC_COMPARE_H__

namespace GAIA
{
	template <typename Type> GINL const Type& max(const Type& v1, const Type& v2)
	{
		if(v1 > v2)
			return v1;
		else if(v1 < v2)
			return v2;
		else
			return v1;
	}

	template <typename Type> GINL const Type& min(const Type& v1, const Type& v2)
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