#ifndef		__GAIA_MATH_COOPERATION_H__
#define		__GAIA_MATH_COOPERATION_H__

namespace GAIA
{
	namespace MATH
	{
		/* AABB and MTX. */
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType> operator * (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX33<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType> operator * (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX34<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType> operator * (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX44<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType>& operator *= (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX33<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType>& operator *= (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX34<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABBDataType, typename _MatrixDataType> GAIA::MATH::AABB<_AABBDataType>& operator *= (const GAIA::MATH::AABB<_AABBDataType>& aabb, const GAIA::MATH::MTX44<_MatrixDataType>& mtx)
		{
		}

		/* AABR and MTX. */
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType> operator * (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX33<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType> operator * (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX34<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType> operator * (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX44<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType>& operator *= (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX33<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType>& operator *= (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX34<_MatrixDataType>& mtx)
		{
		}
		template<typename _AABRDataType, typename _MatrixDataType> GAIA::MATH::AABR<_AABRDataType>& operator *= (const GAIA::MATH::AABR<_AABRDataType>& aabr, const GAIA::MATH::MTX44<_MatrixDataType>& mtx)
		{
		}
	};
};

#endif