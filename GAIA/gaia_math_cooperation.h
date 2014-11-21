#ifndef		__GAIA_MATH_COOPERATION_H__
#define		__GAIA_MATH_COOPERATION_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _VecType, typename _MatrixType> GAIA::MATH::VEC3<_VecType> operator * (const GAIA::MATH::VEC3<_VecType>& v, const GAIA::MATH::MTX44<_MatrixType>& mtx)
		{
			GAIA::MATH::VEC3<_VecType> ret;
			ret.x = v.x * mtx.m[0][0] + v.y * mtx.m[1][0] + v.z * mtx.m[2][0] + mtx.m[3][0];
			ret.y = v.x * mtx.m[0][1] + v.y * mtx.m[1][1] + v.z * mtx.m[2][1] + mtx.m[3][1];
			ret.z = v.x * mtx.m[0][2] + v.y * mtx.m[1][2] + v.z * mtx.m[2][2] + mtx.m[3][2];
			return ret;
		}

		template<typename _VecType, typename _MatrixType> GAIA::MATH::VEC4<_VecType> operator * (const GAIA::MATH::VEC4<_VecType>& v, const GAIA::MATH::MTX44<_MatrixType>& mtx)
		{
			GAIA::MATH::VEC4<_VecType> ret;
			ret.x = v.x * mtx.m[0][0] + v.y * mtx.m[1][0] + v.z * mtx.m[2][0] + v.w * mtx.m[3][0];
			ret.y = v.x * mtx.m[0][1] + v.y * mtx.m[1][1] + v.z * mtx.m[2][1] + v.w * mtx.m[3][1];
			ret.z = v.x * mtx.m[0][2] + v.y * mtx.m[1][2] + v.z * mtx.m[2][2] + v.w * mtx.m[3][2];
			ret.w = v.x * mtx.m[0][3] + v.y * mtx.m[1][3] + v.z * mtx.m[2][3] + v.w * mtx.m[3][3];
			return ret;
		}
	};
};

#endif