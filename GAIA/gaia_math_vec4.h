#ifndef		__GAIA_MATH_VEC4_H__
#define		__GAIA_MATH_VEC4_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class VEC4 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC4<_DataType> __MyType;
		public:
			GINL VEC4(){}
			template<typename _ParamDataType> VEC4(const VEC4<_ParamDataType>& v){this->operator = (v);}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3, typename _ParamDataType4> VEC4(const _ParamDataType1& x, const _ParamDataType2& y, const _ParamDataType3& z, const _ParamDataType4& w){this->x = (_DataType)x; this->y = (_DataType)y; this->z = (_DataType)z; this->w = (_DataType)w;}
			template<typename _ParamDataType> VEC4(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> VEC4(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> VEC4(_ParamDataType* p){this->operator = (p);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return (x * x + y * y + z * z) * (w * w);}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize3(x, y, z) * w;}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize3(x, y, z) * w;}
			template<typename _ParamDataType> __MyType& minimize(const _ParamDataType& src){if(x * w > src) x = src; if(y * w > src) y = src; if(z * w > src) z = src; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const _ParamDataType& src){if(x * w < src) x = src; if(y * w < src) y = src; if(z * w < src) z = src; return *this;}
			template<typename _ParamDataType> __MyType& minimize(const GAIA::MATH::VEC4<_ParamDataType>& src){if(x * w > src.x * src.w) x = src.x * src.w / w; if(y * w > src.y * src.w) y = src.y * src.w / w; if(z * w > src.z * src.w) z = src.z * src.w / w; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const GAIA::MATH::VEC4<_ParamDataType>& src){if(x * w < src.x * src.w) x = src.x * src.w / w; if(y * w < src.y * src.w) y = src.y * src.w / w; if(z * w < src.z * src.w) z = src.z * src.w / w; return *this;}
			GINL GAIA::GVOID normalize(){((GAIA::MATH::VEC3<_DataType>*)this)->normalize(); w = (_DataType)1;}
			GINL GAIA::BL isnormalized() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0 && z == (_DataType)0 && w == (_DataType)1;}
			GINL GAIA::GVOID inverse(){x = (_DataType)1 / x; y = (_DataType)1 / y; z = (_DataType)1 / z; w = (_DataType)1 / w;}
			template<typename _ParamDataType> _DataType dot(const VEC4<_ParamDataType>& v) const{return (x * v.x + y * v.y + z * v.z) * w * v.w;}
			template<typename _ParamDataType> __MyType num(const VEC4<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z; ret.w = w * v.w; return ret;}
			template<typename _ParamDataType> __MyType operator + (const VEC4<_ParamDataType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z; ret.w = w + v.w; return ret;}
			template<typename _ParamDataType> __MyType operator - (const VEC4<_ParamDataType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; ret.z = z - v.z; ret.w = w - v.w; return ret;}
			template<typename _ParamDataType> __MyType operator * (const VEC4<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z; ret.w = w * v.w; return ret;}
			template<typename _ParamDataType> __MyType operator / (const VEC4<_ParamDataType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; ret.z = z / v.z; ret.w = w / v.w; return ret;}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; ret.z = z + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; ret.z = z - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; ret.z = z * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; ret.z = z / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const VEC4<_ParamDataType>& v){x += v.x; y += v.y; z += v.z; w += v.w; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const VEC4<_ParamDataType>& v){x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const VEC4<_ParamDataType>& v){x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const VEC4<_ParamDataType>& v){x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){x += v; y += v; z += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){x -= v; y -= v; z -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){x *= v; y *= v; z *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){x /= v; y /= v; z /= v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const VEC4<_ParamDataType>& v){x = (_DataType)v.x; y = (_DataType)v.y; z = (_DataType)v.z; w = (_DataType)v.w; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){x = y = z = (_DataType)v; w = (_DataType)1; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){x = (_DataType)p[0]; y = (_DataType)p[1]; z = (_DataType)p[2]; w = (_DataType)p[3]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = ((const _ParamDataType*)p);}
			template<typename _ParamDataType> GAIA::BL operator == (const VEC4<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)this, (const typename VEC4<_ParamDataType>::_datatype*)&v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const VEC4<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const VEC4<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const VEC4<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const VEC4<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)this, (const typename VEC4<_ParamDataType>::_datatype*)&v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const VEC4<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)this, (const typename VEC4<_ParamDataType>::_datatype*)&v) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)this, v) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y, z, w;
		};
#define GAIA_TEMP_MACRO(objtype, type) \
		template<typename _ParamDataType> objtype<_ParamDataType> operator + (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret += v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator - (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret -= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator * (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret *= v; return ret;}\
		template<typename _ParamDataType> objtype<_ParamDataType> operator / (type t, const objtype<_ParamDataType>& v){objtype<_ParamDataType> ret = t; ret /= v; return ret;}
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::UM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::NM)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::U8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::N8)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::U16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::N16)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::U32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::N32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::F32)
		GAIA_TEMP_MACRO(GAIA::MATH::VEC4, GAIA::F64)
#undef GAIA_TEMP_MACRO
	};
};

#endif