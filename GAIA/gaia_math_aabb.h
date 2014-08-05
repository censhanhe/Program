#ifndef		__GAIA_MATH_AABB_H__
#define		__GAIA_MATH_AABB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class AABB : public GAIA::Entity
		{
		public:

		public:
			VEC3<_DataType> pmin;
			VEC3<_DataType> pmax;
		};
	};
};

#endif