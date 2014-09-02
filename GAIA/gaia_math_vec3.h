#ifndef		__GAIA_MATH_VEC3_H__
#define		__GAIA_MATH_VEC3_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class VEC3 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC3<_DataType> __MyType;
		public:
			GINL VEC3(){}
			template<typename _ParamDataType> VEC3(const VEC3<_ParamDataType>& v){this->operator = (v);}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> VEC3(const _ParamDataType1& x, const _ParamDataType2& y, const _ParamDataType3& z){this->x = (_DataType)x; this->y = (_DataType)y; this->z = (_DataType)z;}
			template<typename _ParamDataType> VEC3(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> VEC3(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> VEC3(_ParamDataType* p){this->operator = (p);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y + z * z;}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize3(x, y, z);}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize3(x, y, z);}
			template<typename _ParamDataType> __MyType& minimize(const _ParamDataType& src){if(x > src) x = src; if(y > src) y = src; if(z > src) z = src; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const _ParamDataType& src){if(x < src) x = src; if(y < src) y = src; if(z < src) z = src; return *this;}
			template<typename _ParamDataType> __MyType& minimize(const GAIA::MATH::VEC3<_ParamDataType>& src){if(x > src.x) x = src.x; if(y > src.y) y = src.y; if(z > src.z) z = src.z; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const GAIA::MATH::VEC3<_ParamDataType>& src){if(x < src.x) x = src.x; if(y < src.y) y = src.y; if(z < src.z) z = src.z; return *this;}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalized() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0 && z == (_DataType)0;}
			GINL GAIA::GVOID inverse(){x = (_DataType)1 / x; y = (_DataType)1 / y; z = (_DataType)1 / z;}
			template<typename _ParamDataType> _DataType dot(const VEC3<_ParamDataType>& v) const{return x * v.x + y * v.y + z * v.z;}
			template<typename _ParamDataType> __MyType num(const VEC3<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z; return ret;}
			template<typename _ParamDataType> __MyType operator + (const VEC3<_ParamDataType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z; return ret;}
			template<typename _ParamDataType> __MyType operator - (const VEC3<_ParamDataType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; ret.z = z - v.z; return ret;}
			template<typename _ParamDataType> __MyType operator * (const VEC3<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z; return ret;}
			template<typename _ParamDataType> __MyType operator / (const VEC3<_ParamDataType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; ret.z = z / v.z; return ret;}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; ret.z = z + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; ret.z = z - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; ret.z = z * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; ret.z = z / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const VEC3<_ParamDataType>& v){x += v.x; y += v.y; z += v.z; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const VEC3<_ParamDataType>& v){x -= v.x; y -= v.y; z -= v.z; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const VEC3<_ParamDataType>& v){x *= v.x; y *= v.y; z *= v.z; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const VEC3<_ParamDataType>& v){x /= v.x; y /= v.y; z /= v.z; return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){x += v; y += v; z += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){x -= v; y -= v; z -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){x *= v; y *= v; z *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){x /= v; y /= v; z /= v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const VEC3<_ParamDataType>& v){x = (_DataType)v.x; y = (_DataType)v.y; z = (_DataType)v.z; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){x = y = z = (_DataType)v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){x = (_DataType)p[0]; y = (_DataType)p[1]; z = (_DataType)p[2]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = ((const _ParamDataType*)p);}
			template<typename _ParamDataType> GAIA::BL operator == (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const VEC3<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const VEC3<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const VEC3<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, v) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{GAIA_AST(index < 3); return (&x)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){GAIA_AST(index < 3); return (&x)[index];}
			GINL operator _DataType*(){return &x;}
			GINL operator const _DataType*() const{return &x;}
		public:
			_DataType x, y, z;
		};
#define GAIA_TEMP_MACRO(objtype, type) \
		template<typename _ParamDataType> objtype<_ParamDataType> operator + (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret += v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator - (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret -= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator * (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret *= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator / (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret /= v; return ret;}
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::UM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::NM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::U8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::N8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::U16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::N16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::U32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::N32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::F32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC3, GAIA::F64)
#undef GAIA_TEMP_MACRO
	};
};

#endif