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
			template<typename _ParamDataType> VEC2(const VEC2<_ParamDataType>& v){this->operator = (v);}
			template<typename _ParamDataType1, typename _ParamDataType2> VEC2(const _ParamDataType1& tx, const _ParamDataType2& ty){x = (_DataType)tx; y = (_DataType)ty;}
			template<typename _ParamDataType> VEC2(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> VEC2(const _ParamDataType* pV){this->operator = (pV);}
			template<typename _ParamDataType> VEC2(_ParamDataType* pV){this->operator = (pV);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize(x, y);}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize(x, y);}
			template<typename _ParamDataType> __MyType& minimize(const _ParamDataType& src){if(x > src) x = src; if(y > src) y = src; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const _ParamDataType& src){if(x < src) x = src; if(y < src) y = src; return *this;}
			template<typename _ParamDataType> __MyType& minimize(const GAIA::MATH::VEC2<_ParamDataType>& src){if(x > src.x) x = src.x; if(y > src.y) y = src.y; return *this;}
			template<typename _ParamDataType> __MyType& maximize(const GAIA::MATH::VEC2<_ParamDataType>& src){if(x < src.x) x = src.x; if(y < src.y) y = src.y; return *this;}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalized() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0;}
			GINL GAIA::GVOID inverse(){x = (_DataType)1 / x; y = (_DataType)1 / y;}
			template<typename _ParamDataType> _DataType dot(const VEC2<_ParamDataType>& v) const{return x * v.x + y * v.y;}
			template<typename _ParamDataType> __MyType num(const VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamDataType> __MyType operator + (const VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}
			template<typename _ParamDataType> __MyType operator - (const VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; return ret;}
			template<typename _ParamDataType> __MyType operator * (const VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamDataType> __MyType operator / (const VEC2<_ParamDataType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; return ret;}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const VEC2<_ParamDataType>& v){x += v.x; y += v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const VEC2<_ParamDataType>& v){x -= v.x; y -= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const VEC2<_ParamDataType>& v){x *= v.x; y *= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const VEC2<_ParamDataType>& v){x /= v.x; y /= v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){x += v; y += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){x -= v; y -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){x *= v; y *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){x /= v; y /= v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const VEC2<_ParamDataType>& v){x = (_DataType)v.x; y = (_DataType)v.y; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){x = y = (_DataType)v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* pV){x = (_DataType)pV[0]; y = (_DataType)pV[1]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* pV){return this->operator = ((const _ParamDataType*)pV);}
			template<typename _ParamDataType> GAIA::BL operator == (const VEC2<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamDataType>::_datatype*)&v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const VEC2<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const VEC2<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const VEC2<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const VEC2<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamDataType>::_datatype*)&v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const VEC2<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamDataType>::_datatype*)&v) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp2k((const _DataType*)this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp2k((const _DataType*)this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp2k((const _DataType*)this, v) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y;
		};
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC2<_DataType1> 
			operator + (_DataType2 t, const GAIA::MATH::VEC2<_DataType1>& v)
		{
			GAIA::MATH::VEC2<_DataType1> ret = t;
			ret += v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC2<_DataType1> 
			operator - (_DataType2 t, const GAIA::MATH::VEC2<_DataType1>& v)
		{
			GAIA::MATH::VEC2<_DataType1> ret = t;
			ret -= v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC2<_DataType1> 
			operator * (_DataType2 t, const GAIA::MATH::VEC2<_DataType1>& v)
		{
			GAIA::MATH::VEC2<_DataType1> ret = t;
			ret *= v;
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::MATH::VEC2<_DataType1> 
			operator / (_DataType2 t, const GAIA::MATH::VEC2<_DataType1>& v)
		{
			GAIA::MATH::VEC2<_DataType1> ret = t;
			ret /= v;
			return ret;
		}
	};
};

#endif