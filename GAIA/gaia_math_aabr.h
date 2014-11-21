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
			typedef GAIA::MATH::VEC2<_DataType> _vectype;
		public:
			GINL AABR(){}
			template<
				typename _ParamDataType1,
				typename _ParamDataType2,
				typename _ParamDataType3,
				typename _ParamDataType4> AABR(
				const _ParamDataType1& pmin_x,
				const _ParamDataType2& pmin_y,
				const _ParamDataType3& pmax_x,
				const _ParamDataType4& pmax_y)
			{
				pmin.x = GSCAST(_DataType)(pmin_x);
				pmin.y = GSCAST(_DataType)(pmin_y);
				pmax.x = GSCAST(_DataType)(pmax_x);
				pmax.y = GSCAST(_DataType)(pmax_y);
			}
			template<typename _ParamDataType1, typename _ParamDataType2> AABR(const GAIA::MATH::VEC2<_ParamDataType1>& pmin, const GAIA::MATH::VEC2<_ParamDataType2>& pmax)
			{
				this->pmin = pmin;
				this->pmax = pmax;
			}
			template<typename _ParamDataType> AABR(const GAIA::MATH::AABR<_ParamDataType>& src){this->operator = (src);}
			template<typename _ParamDataType> AABR(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABR(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> AABR(_ParamDataType v){this->operator = (v);}
			GINL GAIA::SIZE size() const{return 4;}
			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::BL isidentity() const{return pmin.x > pmax.x || pmin.y > pmax.y;}
			GINL _vectype center() const{return (pmin + pmax) / (_DataType)2;}
			GINL _vectype long_size() const{return pmax - pmin;}
			GINL _DataType long_radius() const{return (pmax - pmin).length() / (_DataType)2;}
			GINL _DataType short_radius() const{return (pmax - pmin).minimize() / (_DataType)2;}
			GINL _DataType width() const{return pmax.x - pmin.x;}
			GINL _DataType height() const{return pmax.y - pmin.y;}
			GINL GAIA::BL iszero() const{return pmin.iszero() && pmax.iszero();}
			GINL GAIA::BL isfinited() const{return pmin.isfinited() && pmax.isfinited();}
			GINL _vectype point(const GAIA::SIZE& sIndex) const
			{
				switch(sIndex)
				{
				case 0:
					return this->ss();
				case 1:
					return this->bs();
				case 2:
					return this->bb();
				case 3:
					return this->sb();
				default:
					GAIA_AST(GAIA::False);
					return (_vectype)0;
				}
			}
			GINL _vectype ss() const{return _vectype(pmin.x, pmin.y);}
			GINL _vectype bs() const{return _vectype(pmax.x, pmin.y);}
			GINL _vectype bb() const{return _vectype(pmax.x, pmax.y);}
			GINL _vectype sb() const{return _vectype(pmin.x, pmax.y);}
			GINL const _DataType* front_ptr() const{return GRCAST(const _DataType*)(&pmin);}
			GINL _DataType* front_ptr(){return GRCAST(_DataType*)(&pmin);}
			GINL const _DataType* back_ptr() const{return this->front_ptr() + this->size() - 1;}
			GINL _DataType* back_ptr(){return this->front_ptr() + this->size() - 1;}
			template<typename _ParamDataType> GAIA::GVOID expand(const GAIA::MATH::AABR<_ParamDataType>& t){pmin.minimize(t.pmin); pmax.maximize(t.pmax);}
			template<typename _ParamDataType> GAIA::GVOID expand(const GAIA::MATH::VEC2<_ParamDataType>& t){pmin.minimize(t); pmax.maximize(t);}
			template<typename _ParamDataType> GAIA::BL clamp(GAIA::MATH::VEC2<_ParamDataType>& t) const
			{
				GAIA::BL bRet = GAIA::False;
				if(t.x < pmin.x){t.x = pmin.x; bRet = GAIA::True;}
				if(t.y < pmin.y){t.y = pmin.y; bRet = GAIA::True;}
				if(t.x > pmax.x){t.x = pmax.x; bRet = GAIA::True;}
				if(t.y > pmax.y){t.y = pmax.y; bRet = GAIA::True;}
				return bRet;
			}
			template<typename _ParamDataType> GAIA::BL clamp(GAIA::MATH::AABR<_ParamDataType>& t) const
			{
				GAIA::BL bRet = GAIA::False;
				if(t.pmin.x < pmin.x){t.pmin.x = pmin.x; bRet = GAIA::True;}
				if(t.pmin.y < pmin.y){t.pmin.y = pmin.y; bRet = GAIA::True;}
				if(t.pmax.x < pmin.x){t.pmax.x = pmin.x; bRet = GAIA::True;}
				if(t.pmax.y < pmin.y){t.pmax.y = pmin.y; bRet = GAIA::True;}
				if(t.pmin.x > pmax.x){t.pmin.x = pmax.x; bRet = GAIA::True;}
				if(t.pmin.y > pmax.y){t.pmin.y = pmax.y; bRet = GAIA::True;}
				if(t.pmax.x > pmax.x){t.pmax.x = pmax.x; bRet = GAIA::True;}
				if(t.pmax.y > pmax.y){t.pmax.y = pmax.y; bRet = GAIA::True;}
				return bRet;
			}
			template<typename _ParamDataType> __MyType operator + (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin + v; ret.pmax = pmax + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin - v; ret.pmax = pmax - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin * v; ret.pmax = pmax * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const GAIA::MATH::VEC2<_ParamDataType>& v){__MyType ret; ret.pmin = pmin / v; ret.pmax = pmax / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin += v; pmax += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin -= v; pmax -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin *= v; pmax *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const GAIA::MATH::VEC2<_ParamDataType>& v){pmin /= v; pmax /= v; return *this;}
			template<typename _ParamDataType> _vectype nearest_point(const GAIA::MATH::VEC2<_ParamDataType>& v) const
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
				return ret;
			}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::AABR<_ParamDataType>& src) const{return GAIA::MATH::xsqrt(this->distancesq(src));}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::AABR<_ParamDataType>& src) const
			{
				_DataType d[4];
				d[0] = GAIA::MATH::xabs(pmin.x - src.pmin.x);
				d[1] = GAIA::MATH::xabs(pmin.x - src.pmax.x);
				d[3] = GAIA::MATH::xabs(pmax.x - src.pmin.x);
				d[4] = GAIA::MATH::xabs(pmax.x - src.pmax.x);
				_DataType nearest_x = GAIA::ALGO::minimize(
					GAIA::ALGO::minimize(d[0], d[1]), GAIA::ALGO::minimize(d[2], d[3]));
				d[0] = GAIA::MATH::xabs(pmin.y - src.pmin.y);
				d[1] = GAIA::MATH::xabs(pmin.y - src.pmax.y);
				d[3] = GAIA::MATH::xabs(pmax.y - src.pmin.y);
				d[4] = GAIA::MATH::xabs(pmax.y - src.pmax.y);
				_DataType nearest_y = GAIA::ALGO::minimize(
					GAIA::ALGO::minimize(d[0], d[1]), GAIA::ALGO::minimize(d[2], d[3]));
				return nearest_x * nearest_x + nearest_y * nearest_y;
			}
			template<typename _ParamDataType> _DataType distance(const GAIA::MATH::VEC2<_ParamDataType>& v) const{return GAIA::MATH::xsqrt(this->distancesq(v));}
			template<typename _ParamDataType> _DataType distancesq(const GAIA::MATH::VEC2<_ParamDataType>& v) const
			{
				_vectype nearestpoint = this->nearest_point(v);
				return (v - nearestpoint).lengthsq();
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_point(const GAIA::MATH::VEC2<_ParamDataType>& v) const
			{
				if(v.x >= pmin.x && v.y >= pmin.y && 
					v.x <= pmax.x && v.y <= pmax.y)
					return GAIA::INTERSECT_TYPE_IN;
				return GAIA::INTERSECT_TYPE_OUT;
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_aabr(const GAIA::MATH::AABR<_ParamDataType>& aabb) const
			{
				if(pmax.x < aabb.pmin.x || pmin.x > aabb.pmax.x)
					return GAIA::INTERSECT_TYPE_OUT;
				if(pmax.y < aabb.pmin.y || pmin.y > aabb.pmax.y)
					return GAIA::INTERSECT_TYPE_OUT;
				if(pmin <= aabb.pmin && pmax >= aabb.pmax)
					return GAIA::INTERSECT_TYPE_IN;
				return GAIA::INTERSECT_TYPE_INTERSECT;
			}
			template<typename _ParamDataType> GAIA::INTERSECT_TYPE intersect_line(const GAIA::MATH::PLANE<_ParamDataType>* pPlanes, const GAIA::SIZE& sPlaneCount) const
			{
				GAIA_AST(pPlanes != GNIL);
			}
			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::AABR<_ParamDataType>& src){pmin = src.pmin; pmax = src.pmax; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){pmin = p; pmax = p + 2; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType v){pmin = v; pmax = v; return *this;}
			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::AABR<_ParamDataType>& t) const{return pmin == t.pmin && pmax == t.pmax;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator == (t));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::AABR<_ParamDataType>& t) const
			{
				if(pmin < t.pmin)
					return GAIA::False;
				else if(pmin > t.pmin)
					return GAIA::True;
				if(pmax < t.pmax)
					return GAIA::False;
				else if(pmax >= t.pmax)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::AABR<_ParamDataType>& t) const
			{
				if(pmin > t.pmin)
					return GAIA::False;
				else if(pmin < t.pmin)
					return GAIA::True;
				if(pmax > t.pmax)
					return GAIA::False;
				else if(pmax <= t.pmax)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator <= (t));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::AABR<_ParamDataType>& t) const{return !(this->operator >= (t));}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return pmin == v && pmax == v;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const
			{
				if(pmin < v)
					return GAIA::False;
				else if(pmin > v)
					return GAIA::True;
				if(pmax < v)
					return GAIA::False;
				else if(pmax >= v)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const
			{
				if(pmin > v)
					return GAIA::False;
				else if(pmin < v)
					return GAIA::True;
				if(pmax > v)
					return GAIA::False;
				else if(pmax <= v)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return !this->operator <= (v);}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return !this->operator >= (v);}
			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			GINL operator _DataType*(){return this->front_ptr();}
			GINL operator const _DataType*() const{return this->front_ptr();}
		private:
			GINL GAIA::GVOID selfupdate()
			{
				if(pmin.x > pmax.x)
					GAIA::ALGO::swap(pmin.x, pmax.x);
				if(pmin.y > pmax.y)
					GAIA::ALGO::swap(pmin.y, pmax.y);
			}
		public:
			_vectype pmin;
			_vectype pmax;
		};
	};
};

#endif
