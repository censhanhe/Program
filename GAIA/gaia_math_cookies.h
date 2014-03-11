#ifndef		__GAIA_MATH_COOKIES_H__
#define		__GAIA_MATH_COOKIES_H__

namespace GAIA
{
	namespace MATH
	{		
		template<typename _DataType> class VEC2
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC2<_DataType> __MyType;
		public:
			GINL VEC2(){}
			template<typename _ParamType> GINL VEC2(const VEC2<_ParamType>& v){this->operator = (v);}
			template<typename _ParamType1, typename _ParamType2> GINL VEC2(const _ParamType1& x, const _ParamType2& y){this->x = (_DataType)x; this->y = (_DataType)y;}
			template<typename _ParamType> GINL VEC2(const _ParamType& v){this->operator = (v);}
			template<typename _ParamType> GINL VEC2(const _ParamType* pV){this->operator = (pV);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize(x, y);}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize(x, y);}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalize() const{return this->lengthsq() == (_DataType)1;}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0;}
			template<typename _ParamType> GINL _DataType dot(const VEC2<_ParamType>& v) const{return x * v.x + y * v.y;}
			template<typename _ParamType> GINL VEC2 num(const VEC2<_ParamType>& v) const{VEC2 ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamType> GINL __MyType operator + (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}
			template<typename _ParamType> GINL __MyType operator - (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; return ret;}
			template<typename _ParamType> GINL __MyType operator * (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template<typename _ParamType> GINL __MyType operator / (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; return ret;}
			template<typename _ParamType> GINL __MyType operator + (const _ParamType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; return ret;}
			template<typename _ParamType> GINL __MyType operator - (const _ParamType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; return ret;}
			template<typename _ParamType> GINL __MyType operator * (const _ParamType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; return ret;}
			template<typename _ParamType> GINL __MyType operator / (const _ParamType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; return ret;}
			template<typename _ParamType> GINL const __MyType& operator += (const VEC2<_ParamType>& v){x += v.x; y += v.y; return *this;}
			template<typename _ParamType> GINL const __MyType& operator -= (const VEC2<_ParamType>& v){x -= v.x; y -= v.y; return *this;}
			template<typename _ParamType> GINL const __MyType& operator *= (const VEC2<_ParamType>& v){x *= v.x; y *= v.y; return *this;}
			template<typename _ParamType> GINL const __MyType& operator /= (const VEC2<_ParamType>& v){x /= v.x; y /= v.y; return *this;}
			template<typename _ParamType> GINL const __MyType& operator += (const _ParamType& v){x += v; y += v; return *this;}
			template<typename _ParamType> GINL const __MyType& operator -= (const _ParamType& v){x -= v; y -= v; return *this;}
			template<typename _ParamType> GINL const __MyType& operator *= (const _ParamType& v){x *= v; y *= v; return *this;}
			template<typename _ParamType> GINL const __MyType& operator /= (const _ParamType& v){x /= v; y /= v; return *this;}
			template<typename _ParamType> GINL const __MyType& operator = (const VEC2<_ParamType>& v){x = v.x; y = v.y; return *this;}
			template<typename _ParamType> GINL const __MyType& operator = (const _ParamType& v){x = y = (_DataType)v; return *this;}
			template<typename _ParamType> GINL const __MyType& operator = (const _ParamType* pV){x = pV[0]; y = pV[1]; return *this;}
			template<typename _ParamType> GINL GAIA::BL operator == (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) == 0;}
			template<typename _ParamType> GINL GAIA::BL operator != (const VEC2<_ParamType>& v) const{return !(this->operator == (v));}
			template<typename _ParamType> GINL GAIA::BL operator >= (const VEC2<_ParamType>& v) const{return !this->operator < (v);}
			template<typename _ParamType> GINL GAIA::BL operator <= (const VEC2<_ParamType>& v) const{return !this->operator > (v);}
			template<typename _ParamType> GINL GAIA::BL operator > (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) > 0;}
			template<typename _ParamType> GINL GAIA::BL operator < (const VEC2<_ParamType>& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, (const typename VEC2<_ParamType>::_datatype*)&v) < 0;}
			template<typename _ParamType> GINL GAIA::BL operator == (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) == 0;}
			template<typename _ParamType> GINL GAIA::BL operator != (const _ParamType& v) const{return !(this->operator == (v));}
			template<typename _ParamType> GINL GAIA::BL operator >= (const _ParamType& v) const{return !this->operator < (v);}
			template<typename _ParamType> GINL GAIA::BL operator <= (const _ParamType& v) const{return !this->operator > (v);}
			template<typename _ParamType> GINL GAIA::BL operator > (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) > 0;}
			template<typename _ParamType> GINL GAIA::BL operator < (const _ParamType& v) const{return GAIA::ALGORITHM::cmp2((const _DataType*)this, v) < 0;}
			template<typename _ParamType> GINL const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template<typename _ParamType> GINL _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y;
		};

		template<typename _DataType> class VEC3
		{
		public:
		public:
			_DataType x, y, z;
		};
		
		template<typename _DataType> class VEC4
		{
		public:
		public:
			_DataType x, y, z, w;
		};

		template<typename _DataType> class QUA
		{
		public:
			_DataType x, y, z, w;
		};

		template<typename _DataType> class MTX22
		{
		public:
			GINL GAIA::GVOID identity(){}
			GINL GAIA::BL isidentity() const;
			GINL GAIA::GVOID inverse(){}
			GINL GAIA::GVOID transpose(){}
		};

		template<typename _DataType> class MTX33
		{
		public:
		public:
		};

		template<typename _DataType> class MTX34
		{
		public:
		public:
		};

		template<typename _DataType> class MTX44
		{
		public:
		public:
		};

		template<typename _DataType> class PLANE
		{
		public:
		public:
			_DataType a, b, c, d;
		};

		template<typename _DataType> class AABR
		{
		public:
			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::GVOID isidentity() const{}
			GINL GAIA::GVOID zero(){pmin = (_DataType)0; pmax = (_DataType)0;}
			GINL GAIA::GVOID iszero() const{}
		public:
			VEC2<_DataType> pmin;
			VEC2<_DataType> pmax;
		};

		template<typename _DataType> class AABB
		{
		public:
			
		public:
			VEC3<_DataType> pmin;
			VEC3<_DataType> pmax;
		};

		template<typename _DataType> class ARGB
		{
		public:
		public:
			_DataType a, r, g, b;
		};
		
		template<typename _DataType> class RGB
		{
		public:
		public:
			_DataType r, g, b;
		};
	};
};

#endif
