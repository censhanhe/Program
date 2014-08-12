#ifndef 	__GAIA_MATH_LERP_H__
#define 	__GAIA_MATH_LERP_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> _ParamDataType1 lerp(const _ParamDataType1& start, const _ParamDataType2& end, const _ParamDataType3& s){return start + s * (end - start);}
		template<typename _ParamDataType> _ParamDataType lerp_cosfactor(_ParamDataType s){return (1 - GAIA::MATH::xcos(s * GAIA::MATH::PI)) / 2;}
	};
};

#endif
