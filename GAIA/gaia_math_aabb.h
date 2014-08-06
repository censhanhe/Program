#ifndef		__GAIA_MATH_AABB_H__
#define		__GAIA_MATH_AABB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class AABB : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef AABB<_DataType> __MyType;
		public:
			GINL AABB(){}
			GINL AABB(const __MyType& src){}
			template<typename _ParamDataType> AABB(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABB(const _ParamDataType& t){this->operator = (t);}

			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::BL isidentity() const{}

			GINL GAIA::MATH::VEC3<_DataType> center() const{}
			GINL GAIA::MATH::VEC3<_DataType> size() const{}
			GINL _DataType long_radius() const{}
			GINL _DataType short_radius() const{}

			GINL __MyType operator + (const __MyType& t) const{}
			template<typename _ParamDataType> __MyType operator += (const GAIA::MATH::VEC3<_ParamDataType>& v){}
			GINL __MyType& operator + (const __MyType& t) const{}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::VEC3<_ParamDataType>& v){}

			GINL _DataType distance(const __MyType& src) const{}
			GINL _DataType distancesq(const __MyType& src) const{}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::VEC3<_ParamDataType>& v) const{}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::VEC3<_ParamDataType>& v) const{}

			template<typename _ParamDataType> INTERSECT_TYPE intersect_point() const{}
			template<typename _ParamDataType>  INTERSECT_TYPE intersect_aabb() const{}
			template<typename _ParamDataType>  INTERSECT_TYPE intersect_ray() const{}
			template<typename _ParamDataType>  INTERSECT_TYPE intersect_plane() const{}

			GINL __MyType& operator = (const __MyType& src){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){}

			template<typename _ParamDataType> GAIA::BL operator == (const AABB<_ParamDataType>& t) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const AABB<_ParamDataType>& t) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const AABB<_ParamDataType>& t) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const AABB<_ParamDataType>& t) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const AABB<_ParamDataType>& t) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const AABB<_ParamDataType>& t) const{}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{}

			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX33<_ParamDataType>& mtx) const{}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX34<_ParamDataType>& mtx) const{}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX44<_ParamDataType>& mtx) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX33<_ParamDataType>& mtx){}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX34<_ParamDataType>& mtx){}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX44<_ParamDataType>& mtx){}

		public:
			GAIA::MATH::VEC3<_DataType> pmin;
			GAIA::MATH::VEC3<_DataType> pmax;
		};
	};
};

#endif