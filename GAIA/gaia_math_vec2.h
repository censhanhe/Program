#ifndef		__GAIA_MATH_VEC2_H__
#define		__GAIA_MATH_VEC2_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class VEC2 : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC2<_DataType> __MyType;
		public:
			GINL VEC2(){}
			template<typename _ParamType> VEC2(const VEC2<_ParamType>& v){this->operator = (v);}
			template<typename _ParamType1, typename _ParamType2> VEC2(const _ParamType1& x, const _ParamType2& y){this->x = (_DataType)x; this->y = (_DataType)y;}
			template<typename _ParamType> VEC2(const _ParamType& v){this->operator = (v);}
			template<typename _ParamType> VEC2(const _ParamType* pV){this->operator = (pV);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize(x, y);}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize(x, y);}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalized() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0;}
			template<typename _ParamType> _DataType dot(const VEC2<_ParamType>& v) const{return x * v.x + y * v.y;}
			template<typename _ParamType> VEC2 num(const VEC2<_ParamType>& v) const{VEC2 ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamType> __MyType operator + (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}
			template<typename _ParamType> __MyType operator - (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; return ret;}
			template<typename _ParamType> __MyType operator * (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamType> __MyType operator / (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; return ret;}
			template<typename _ParamType> __MyType operator + (const _ParamType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; return ret;}
			template<typename _ParamType> __MyType operator - (const _ParamType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; return ret;}
			template<typename _ParamType> __MyType operator * (const _ParamType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; return ret;}
			template<typename _ParamType> __MyType operator / (const _ParamType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; return ret;}
			template<typename _ParamType> const __MyType& operator += (const VEC2<_ParamType>& v){x += v.x; y += v.y; return *this;}
			template<typename _ParamType> const __MyType& operator -= (const VEC2<_ParamType>& v){x -= v.x; y -= v.y; return *this;}
			template<typename _ParamType> const __MyType& operator *= (const VEC2<_ParamType>& v){x *= v.x; y *= v.y; return *this;}
			template<typename _ParamType> const __MyType& operator /= (const VEC2<_ParamType>& v){x /= v.x; y /= v.y; return *this;}
			template<typename _ParamType> const __MyType& operator += (const _ParamType& v){x += v; y += v; return *this;}
			template<typename _ParamType> const __MyType& operator -= (const _ParamType& v){x -= v; y -= v; return *this;}
			template<typename _ParamType> const __MyType& operator *= (const _ParamType& v){x *= v; y *= v; return *this;}
			template<typename _ParamType> const __MyType& operator /= (const _ParamType& v){x /= v; y /= v; return *this;}
			template<typename _ParamType> const __MyType& operator = (const VEC2<_ParamType>& v){x = (_DataType)v.x; y = (_DataType)v.y; return *this;}
			template<typename _ParamType> const __MyType& operator = (const _ParamType& v){x = y = (_DataType)v; return *this;}
			template<typename _ParamType> const __MyType& operator = (const _ParamType* pV){x = (_DataType)pV[0]; y = (_DataType)pV[1]; return *this;}
			template<typename _ParamType> GAIA::BL operator == (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) == 0;}
			template<typename _ParamType> GAIA::BL operator != (const VEC2<_ParamType>& v) const{return !this->operator == (v);}
			template<typename _ParamType> GAIA::BL operator >= (const VEC2<_ParamType>& v) const{return !this->operator < (v);}
			template<typename _ParamType> GAIA::BL operator <= (const VEC2<_ParamType>& v) const{return !this->operator > (v);}
			template<typename _ParamType> GAIA::BL operator > (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) > 0;}
			template<typename _ParamType> GAIA::BL operator < (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) < 0;}
			template<typename _ParamType> GAIA::BL operator == (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) == 0;}
			template<typename _ParamType> GAIA::BL operator != (const _ParamType& v) const{return !this->operator == (v);}
			template<typename _ParamType> GAIA::BL operator >= (const _ParamType& v) const{return !this->operator < (v);}
			template<typename _ParamType> GAIA::BL operator <= (const _ParamType& v) const{return !this->operator > (v);}
			template<typename _ParamType> GAIA::BL operator > (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) > 0;}
			template<typename _ParamType> GAIA::BL operator < (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) < 0;}
			template<typename _ParamType> const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamType> _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y;
		};
	};
};

#endif