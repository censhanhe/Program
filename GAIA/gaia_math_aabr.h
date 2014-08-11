#ifndef		__GAIA_MATH_AABR_H__
#define		__GAIA_MATH_AABR_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class AABR : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef AABR<_DataType> __MyType;
		public:
			GINL AABR(){}
			GINL AABR(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> AABR(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABR(const _ParamDataType& t){this->operator = (t);}

			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::BL isidentity() const{return pmin.x > pmax.x || pmin.y > pmax.y;}

			GINL GAIA::MATH::VEC2<_DataType> center() const{return (pmin + pmax) / (_DataType)2;}
			GINL GAIA::MATH::VEC2<_DataType> size() const{return pmax - pmin;}
			GINL _DataType long_radius() const{(pmax - pmin).length() / (_DataType)2;}
			GINL _DataType short_radius() const{(pmax - pmin).minimize() / (_DataType)2;}
			GINL _DataType width() const{return pmax.x - pmin.x;}
			GINL _DataType height() const{return pmax.y - pmin.y;}

			template<typename _ParamDataType> __MyType& expand(const GAIA::MATH::AABR<_ParamDataType>& t){pmin.minimize(t.pmin); pmax.maximize(t.pmax);}
			template<typename _ParamDataType> __MyType& expand(const GAIA::MATH::VEC2<_ParamDataType>& t){pmin.minimize(t); pmax.maximize(t);}

			template<typename _ParamDataType> __MyType operator + (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin + v; ret.pmax = pmax + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin - v; ret.pmax = pmax - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin * v; ret.pmax = pmax * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin / v; ret.pmax = pmax / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin += v; pmax += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin -= v; pmax -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin *= v; pmax *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin /= v; pmax /= v; return *this;}

			template<typename _ParamDataType> _DataType distance(const __MyType& src) const
			{
			}
			template<typename _ParamDataType> _DataType distancesq(const __MyType& src) const
			{
			}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::VEC2<_ParamDataType>& v) const
			{
			}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::VEC2<_ParamDataType>& v) const
			{
			}

			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_point(const GAIA::MATH::VEC2<_ParamDataType>& v) const
			{
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_aabr(const GAIA::MATH::AABR<_ParamDataType>& aabb) const
			{
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_line(const GAIA::MATH::PLANE* pPlanes, const GAIA::SIZE& sPlaneCount) const
			{
				GAIA_AST(pPlanes != GNULL);
			}

			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::AABR<_ParamDataType>& src){pmin = src.pmin; pmax = src.pmax; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){pmin = p; pmax = p + 2; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){pmin = v; pmax = v; return *this;}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::AABR<_ParamDataType>& t) const{return pmin == t.pmin && pmax == t.pmax;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator = (t));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::AABR<_ParamDataType>& t) const
			{
				if(pmin < t.pmin)
					return GAIA::False;
				if(pmax < t.pmax)
					return GAIA::False;
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::AABR<_ParamDataType>& t) const
			{
				if(pmin > t.pmin)
					return GAIA::False;
				if(pmax > t.pmax)
					return GAIA::False;
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator <= (t));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator >= (t));}
			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){return ((_DataType*)this)[index];}

		private:
			GINL GAIA::GVOID selfupdate()
			{
				if(pmin.x > pmax.x)
					GAIA::ALGORITHM::swap(pmin.x, pmax.x);
				if(pmin.y > pmax.y)
					GAIA::ALGORITHM::swap(pmin.y, pmax.y);
			}

		public:
			GAIA::MATH::VEC2<_DataType> pmin;
			GAIA::MATH::VEC2<_DataType> pmax;
		};
	};
};

#endif