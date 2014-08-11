#ifndef		__GAIA_MATH_VEC3_H__
#define		__GAIA_MATH_VEC3_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class VEC3 : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC3<_DataType> __MyType;
		public:
			GINL VEC3(){}
			template<typename _ParamDataType> VEC3(const VEC3<_ParamDataType>& v){this->operator = (v);}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> VEC3(const _ParamDataType1& tx, const _ParamDataType2& ty, const _ParamDataType3& tz){x = (_DataType)tx; y = (_DataType)ty; z = (_DataType)tz;}
			template<typename _ParamDataType> VEC3(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> VEC3(const _ParamDataType* pV){this->operator = (pV);}
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
			template<typename _ParamDataType> const __MyType& operator += (const VEC3<_ParamDataType>& v){x += v.x; y += v.y; z += v.z; return *this;}
			template<typename _ParamDataType> const __MyType& operator -= (const VEC3<_ParamDataType>& v){x -= v.x; y -= v.y; z -= v.z; return *this;}
			template<typename _ParamDataType> const __MyType& operator *= (const VEC3<_ParamDataType>& v){x *= v.x; y *= v.y; z *= v.z; return *this;}
			template<typename _ParamDataType> const __MyType& operator /= (const VEC3<_ParamDataType>& v){x /= v.x; y /= v.y; z /= v.z; return *this;}
			template<typename _ParamDataType> const __MyType& operator += (const _ParamDataType& v){x += v; y += v; z += v; return *this;}
			template<typename _ParamDataType> const __MyType& operator -= (const _ParamDataType& v){x -= v; y -= v; z -= v; return *this;}
			template<typename _ParamDataType> const __MyType& operator *= (const _ParamDataType& v){x *= v; y *= v; z *= v; return *this;}
			template<typename _ParamDataType> const __MyType& operator /= (const _ParamDataType& v){x /= v; y /= v; z /= v; return *this;}
			template<typename _ParamDataType> const __MyType& operator = (const VEC3<_ParamDataType>& v){x = (_DataType)v.x; y = (_DataType)v.y; z = (_DataType)v.z; return *this;}
			template<typename _ParamDataType> const __MyType& operator = (const _ParamDataType& v){x = y = z = (_DataType)v; return *this;}
			template<typename _ParamDataType> const __MyType& operator = (const _ParamDataType* pV){x = (_DataType)pV[0]; y = (_DataType)pV[1]; z = (_DataType)pV[2]; return *this;}
			template<typename _ParamDataType> GAIA::BL operator == (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const VEC3<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const VEC3<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const VEC3<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const VEC3<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const typename VEC3<_ParamDataType>::_datatype*)&v) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, v) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y, z;
		};
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC3<_DataType1> 
			operator + (_DataType2 t, const GAIA::MATH::VEC3<_DataType1>& v)
		{
			GAIA::MATH::VEC3<_DataType1> ret = t;
			ret += v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC3<_DataType1> 
			operator - (_DataType2 t, const GAIA::MATH::VEC3<_DataType1>& v)
		{
			GAIA::MATH::VEC3<_DataType1> ret = t;
			ret -= v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC3<_DataType1> 
			operator * (_DataType2 t, const GAIA::MATH::VEC3<_DataType1>& v)
		{
			GAIA::MATH::VEC3<_DataType1> ret = t;
			ret *= v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC3<_DataType1> 
			operator / (_DataType2 t, const GAIA::MATH::VEC3<_DataType1>& v)
		{
			GAIA::MATH::VEC3<_DataType1> ret = t;
			ret /= v;
			return ret;
		}
	};
};

#endif