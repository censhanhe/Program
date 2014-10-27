#ifndef		__GAIA_MATH_VEC2_H__
#define		__GAIA_MATH_VEC2_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class VEC2 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC2<_DataType> __MyType;
		public:
			GINL VEC2(){}
			template<typename _ParamDataType> VEC2(const GAIA::MATH::VEC2<_ParamDataType>& v){this->operator = (v);}
			template<typename _ParamDataType1, typename _ParamDataType2> VEC2(const _ParamDataType1& x, const _ParamDataType2& y){this->x = GSCAST(_DataType)(x); this->y = GSCAST(_DataType)(y);}
			template<typename _ParamDataType> VEC2(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> VEC2(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> VEC2(_ParamDataType* p){this->operator = (p);}
			GINL GAIA::SIZE size() const{return 2;}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType minimize() const{return GAIA::ALGO::minimize(x, y);}
			GINL _DataType maximize() const{return GAIA::ALGO::maximize(x, y);}
			template<typename _ParamDataType> __MyType& minimize(const _ParamDataType& src){if(x > src) x = src; if(y > src) y = src; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const _ParamDataType& src){if(x < src) x = src; if(y < src) y = src; return *this;}
			template<typename _ParamDataType> __MyType& minimize(const GAIA::MATH::VEC2<_ParamDataType>& src){if(x > src.x) x = src.x; if(y > src.y) y = src.y; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const GAIA::MATH::VEC2<_ParamDataType>& src){if(x < src.x) x = src.x; if(y < src.y) y = src.y; return *this;}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalized() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0;}
			GINL GAIA::BL isfinited() const{return GAIA::MATH::xfinite(x) && GAIA::MATH::xfinite(y);}
			GINL GAIA::GVOID inverse(){x = (_DataType)1 / x; y = (_DataType)1 / y;}
			template<typename _ParamDataType> _DataType dot(const GAIA::MATH::VEC2<_ParamDataType>& v) const{return x * v.x + y * v.y;}
			template<typename _ParamDataType> __MyType num(const GAIA::MATH::VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamDataType> __MyType operator + (const GAIA::MATH::VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}
			template<typename _ParamDataType> __MyType operator - (const GAIA::MATH::VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; return ret;}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamDataType> __MyType operator / (const GAIA::MATH::VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; return ret;}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::VEC2<_ParamDataType>& v){x += v.x; y += v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const GAIA::MATH::VEC2<_ParamDataType>& v){x -= v.x; y -= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::VEC2<_ParamDataType>& v){x *= v.x; y *= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const GAIA::MATH::VEC2<_ParamDataType>& v){x /= v.x; y /= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){x += v; y += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){x -= v; y -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){x *= v; y *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){x /= v; y /= v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::VEC2<_ParamDataType>& v){x = GSCAST(_DataType)(v.x); y = GSCAST(_DataType)(v.y); return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){x = y = GSCAST(_DataType)(v); return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){x = GSCAST(_DataType)(p[0]); y = GSCAST(_DataType)(p[1]); return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return GAIA::ALGO::cmp2(GSCAST(const _DataType*)(*this), GSCAST(const _ParamDataType*)(v)) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return GAIA::ALGO::cmp2(GSCAST(const _DataType*)(*this), GSCAST(const _ParamDataType*)(v)) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::VEC2<_ParamDataType>& v) const{return GAIA::ALGO::cmp2(GSCAST(const _DataType*)(*this), GSCAST(const _ParamDataType*)(v)) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGO::cmp2k((const _DataType*)*this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGO::cmp2k((const _DataType*)*this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGO::cmp2k((const _DataType*)*this, v) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{GAIA_AST(index < 2); return (&x)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){GAIA_AST(index < 2); return (&x)[index];}
			GINL operator _DataType*(){return &x;}
			GINL operator const _DataType*() const{return &x;}
		public:
			_DataType x, y;
		};

#define GAIA_TEMP_MACRO(objtype, type) \
		template<typename _ParamDataType> objtype<_ParamDataType> operator + (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret += v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator - (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret -= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator * (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret *= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator / (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret /= v; return ret;}
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::UM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::NM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::U8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::N8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::U16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::N16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::U32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::N32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::F32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC2, GAIA::F64)
#undef GAIA_TEMP_MACRO
	};
};

#endif
