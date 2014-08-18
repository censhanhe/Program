#ifndef		__GAIA_MATH_AABB_H__
#define		__GAIA_MATH_AABB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class AABB : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef AABB<_DataType> __MyType;
		public:
			typedef GAIA::MATH::VEC3<_DataType> _vectype;
		public:
			GINL AABB(){}
			template<typename _ParamDataType> AABB(const GAIA::MATH::AABB<_ParamDataType>& src){this->operator = (src);}
			template<typename _ParamDataType> AABB(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABB(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABB(const _ParamDataType& t){this->operator = (t);}
			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::BL isidentity() const{return pmin.x > pmax.x || pmin.y > pmax.y || pmin.z > pmax.z;}
			GINL _vectype center() const{return (pmin + pmax) / (_DataType)2;}
			GINL _vectype size() const{return pmax - pmin;}
			GINL _DataType long_radius() const{return (pmax - pmin).length() / (_DataType)2;}
			GINL _DataType short_radius() const{return (pmax - pmin).minimize() / (_DataType)2;}
			GINL _DataType width() const{return pmax.x - pmin.x;}
			GINL _DataType height() const{return pmax.y - pmin.y;}
			GINL _DataType depth() const{return pmax.z - pmin.z;}
			template<typename _ParamDataType> GAIA::GVOID expand(const GAIA::MATH::AABB<_ParamDataType>& t){pmin.minimize(t.pmin); pmax.maximize(t.pmax);}
			template<typename _ParamDataType> GAIA::GVOID expand(const GAIA::MATH::VEC3<_ParamDataType>& t){pmin.minimize(t); pmax.maximize(t);}
			template<typename _ParamDataType> __MyType operator + (const GAIA::MATH::VEC3<_ParamDataType>& v){__MyType ret; ret.pmin = pmin + v; ret.pmax = pmax + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const GAIA::MATH::VEC3<_ParamDataType>& v){__MyType ret; ret.pmin = pmin - v; ret.pmax = pmax - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::VEC3<_ParamDataType>& v){__MyType ret; ret.pmin = pmin * v; ret.pmax = pmax * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const GAIA::MATH::VEC3<_ParamDataType>& v){__MyType ret; ret.pmin = pmin / v; ret.pmax = pmax / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::VEC3<_ParamDataType>& v){pmin += v; pmax += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const GAIA::MATH::VEC3<_ParamDataType>& v){pmin -= v; pmax -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::VEC3<_ParamDataType>& v){pmin *= v; pmax *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const GAIA::MATH::VEC3<_ParamDataType>& v){pmin /= v; pmax /= v; return *this;}
			template<typename _ParamDataType> _vectype nearest_point(const GAIA::MATH::VEC3<_ParamDataType>& v) const
			{
				_vectype ret;
				if(v.x < pmin.x)
					ret.x = pmin.x;
				else if(v.x > pmax.x)
					ret.x = pmax.x;
				if(v.y < pmin.y)
					ret.y = pmin.y;
				else if(v.y > pmax.y)
					ret.y = pmax.y;
				if(v.z < pmin.z)
					ret.z = pmin.z;
				else if(v.z > pmax.z)
					ret.z = pmax.z;
				return ret;
			}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::AABB<_ParamDataType>& src) const{return GAIA::MATH::xsqrt(this->distancesq(src));}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::AABB<_ParamDataType>& src) const
			{
				_DataType d[4];
				d[0] = GAIA::MATH::xabs(pmin.x - src.pmin.x);
				d[1] = GAIA::MATH::xabs(pmin.x - src.pmax.x);
				d[3] = GAIA::MATH::xabs(pmax.x - src.pmin.x);
				d[4] = GAIA::MATH::xabs(pmax.x - src.pmax.x);
				_DataType nearest_x = GAIA::ALGORITHM::minimize(
					GAIA::ALGORITHM::minimize(d[0], d[1]), GAIA::ALGORITHM::minimize(d[2], d[3]));
				d[0] = GAIA::MATH::xabs(pmin.y - src.pmin.y);
				d[1] = GAIA::MATH::xabs(pmin.y - src.pmax.y);
				d[3] = GAIA::MATH::xabs(pmax.y - src.pmin.y);
				d[4] = GAIA::MATH::xabs(pmax.y - src.pmax.y);
				_DataType nearest_y = GAIA::ALGORITHM::minimize(
					GAIA::ALGORITHM::minimize(d[0], d[1]), GAIA::ALGORITHM::minimize(d[2], d[3]));
				d[0] = GAIA::MATH::xabs(pmin.z - src.pmin.z);
				d[1] = GAIA::MATH::xabs(pmin.z - src.pmax.z);
				d[3] = GAIA::MATH::xabs(pmax.z - src.pmin.z);
				d[4] = GAIA::MATH::xabs(pmax.z - src.pmax.z);
				_DataType nearest_z = GAIA::ALGORITHM::minimize(
					GAIA::ALGORITHM::minimize(d[0], d[1]), GAIA::ALGORITHM::minimize(d[2], d[3]));
				return nearest_x * nearest_x + nearest_y * nearest_y + nearest_z * nearest_z;
			}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::VEC3<_ParamDataType>& v) const{return GAIA::MATH::xsqrt(this->distancesq(v));}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::VEC3<_ParamDataType>& v) const
			{
				_vectype nearestpoint = this->nearest_point(v);
				return (v - nearest_point).lengthsq();
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_point(const GAIA::MATH::VEC3<_ParamDataType>& v) const
			{
				if(v.x >= pmin.x && v.y >= pmin.y && v.z >= pmin.z && 
					v.x <= pmax.x && v.y <= pmax.y && v.z <= pmax.z)
					return GAIA::INTERSECT_TYPE_IN;
				return GAIA::INTERSECT_TYPE_OUT;
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_aabb(const GAIA::MATH::AABB<_ParamDataType>& aabb) const
			{
				if(pmax.x < aabb.pmin.x || pmin.x > aabb.pmax.x)
					return GAIA::INTERSECT_TYPE_OUT;
				if(pmax.y < aabb.pmin.y || pmin.y > aabb.pmax.y)
					return GAIA::INTERSECT_TYPE_OUT;
				if(pmax.z < aabb.pmin.z || pmin.z > aabb.pmax.z)
					return GAIA::INTERSECT_TYPE_OUT;
				if(pmin <= aabb.pmin && pmax >= aabb.pmax)
					return GAIA::INTERSECT_TYPE_IN;
				return GAIA::INTERSECT_TYPE_INTERSECT;
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_ray(const GAIA::MATH::VEC3<_ParamDataType>& pos, const GAIA::MATH::VEC3<_ParamDataType>& dir) const
			{
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_plane(const GAIA::MATH::PLANE<_ParamDataType>* pPlanes, const GAIA::SIZE& sPlaneCount) const
			{
				GAIA_AST(pPlanes != GNULL);
			}
			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::AABB<_ParamDataType>& src){pmin = src.pmin; pmax = src.pmax; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){pmin = p; pmax = p + 3; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = ((const _ParamDataType*)p);}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){pmin = v; pmax = v; return *this;}
			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::AABB<_ParamDataType>& t) const{return pmin == t.pmin && pmax == t.pmax;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::AABB<_ParamDataType>& t) const{return !(this->operator == (t));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::AABB<_ParamDataType>& t) const
			{
				if(pmin < t.pmin)
					return GAIA::False;
				if(pmax < t.pmax)
					return GAIA::False;
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::AABB<_ParamDataType>& t) const
			{
				if(pmin > t.pmin)
					return GAIA::False;
				if(pmax > t.pmax)
					return GAIA::False;
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::AABB<_ParamDataType>& t) const{return !(this->operator <= (t));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::AABB<_ParamDataType>& t) const{return !(this->operator >= (t));}
			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){return ((_DataType*)this)[index];}
		private:
			GINL GAIA::GVOID selfupdate()
			{
				if(pmin.x > pmax.x)
					GAIA::ALGORITHM::swap(pmin.x, pmax.x);
				if(pmin.y > pmax.y)
					GAIA::ALGORITHM::swap(pmin.y, pmax.y);
				if(pmin.z > pmax.z)
					GAIA::ALGORITHM::swap(pmin.z, pmax.z);
			}
		public:
			_vectype pmin;
			_vectype pmax;
		};
	};
};

#endif