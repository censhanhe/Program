#ifndef		__GAIA_MATH_COOKIES_H__
#define		__GAIA_MATH_COOKIES_H__

namespace GAIA
{
	namespace MATH
	{
		template <typename _DataType> class VEC2
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef VEC2<_DataType> __MyType;
		public:
			GINL VEC2(){}
			template <typename _ParamType> GINL VEC2(const VEC2<_ParamType>& v){this->operator = (v);}
			template <typename _ParamType1, typename _ParamType2> GINL VEC2(const _ParamType1& x, const _ParamType2& y){this->x = (_DataType)x; this->y = (_DataType)y;}
			template <typename _ParamType> GINL VEC2(const _ParamType& v){this->operator = (v);}
			template <typename _ParamType> GINL VEC2(const _ParamType* pV){this->operator = (pV);}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType minimize() const{return GAIA::ALGORITHM::minimize(x, y);}
			GINL _DataType maximize() const{return GAIA::ALGORITHM::maximize(x, y);}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); (*this) /= t;}
			GINL GAIA::BL isnormalize() const{if(this->lengthsq() == (_DataType)1) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL iszero() const{if(x == (_DataType)0 && y == (_DataType)0) return GAIA::True; return GAIA::False;}
			template <typename _ParamType> GINL __MyType dot(const VEC2<_ParamType>& v) const{return x * v.x + y * v.y;}
			template <typename _ParamType> GINL __MyType cross(const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL VEC2 num(const VEC2<_ParamType>& v) const{VEC2 ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template <typename _ParamType> GINL __MyType operator + (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}
			template <typename _ParamType> GINL __MyType operator - (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x - v.x; ret.y = y - v.y; return ret;}
			template <typename _ParamType> GINL __MyType operator * (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; return ret;}
			template <typename _ParamType> GINL __MyType operator / (const VEC2<_ParamType>& v) const{__MyType ret; ret.x = x / v.x; ret.y = y / v.y; return ret;}
			template <typename _ParamType> GINL __MyType operator + (const _ParamType& v) const{__MyType ret; ret.x = x + v; ret.y = y + v; return ret;}
			template <typename _ParamType> GINL __MyType operator - (const _ParamType& v) const{__MyType ret; ret.x = x - v; ret.y = y - v; return ret;}
			template <typename _ParamType> GINL __MyType operator * (const _ParamType& v) const{__MyType ret; ret.x = x * v; ret.y = y * v; return ret;}
			template <typename _ParamType> GINL __MyType operator / (const _ParamType& v) const{__MyType ret; ret.x = x / v; ret.y = y / v; return ret;}
			template <typename _ParamType> GINL const __MyType& operator += (const VEC2<_ParamType>& v){x += v.x; y += v.y; return *this;}
			template <typename _ParamType> GINL const __MyType& operator -= (const VEC2<_ParamType>& v){x -= v.x; y -= v.y; return *this;}
			template <typename _ParamType> GINL const __MyType& operator *= (const VEC2<_ParamType>& v){x *= v.x; y *= v.y; return *this;}
			template <typename _ParamType> GINL const __MyType& operator /= (const VEC2<_ParamType>& v){x /= v.x; y /= v.y; return *this;}
			template <typename _ParamType> GINL const __MyType& operator += (const _ParamType& v){x += v; y += v; return *this;}
			template <typename _ParamType> GINL const __MyType& operator -= (const _ParamType& v){x -= v; y -= v; return *this;}
			template <typename _ParamType> GINL const __MyType& operator *= (const _ParamType& v){x *= v; y *= v; return *this;}
			template <typename _ParamType> GINL const __MyType& operator /= (const _ParamType& v){x /= v; y /= v; return *this;}
			template <typename _ParamType> GINL const __MyType& operator = (const VEC2<_ParamType>& v){x = v.x; y = v.y; return *this;}
			template <typename _ParamType> GINL const __MyType& operator = (const _ParamType& v){x = y = v; return *this;}
			template <typename _ParamType> GINL const __MyType& operator = (const _ParamType* pV){x = pV[0]; y = pV[1]; return *this;}
			template <typename _ParamType> GINL GAIA::BL operator == (const VEC2<_ParamType>& v) const{if(x == v.x && y == v.y) return GAIA::True; return GAIA::False;}
			template <typename _ParamType> GINL GAIA::BL operator != (const VEC2<_ParamType>& v) const{if(this->operator == (v)) return GAIA::False; return GAIA::True;}
			template <typename _ParamType> GINL GAIA::BL operator >= (const VEC2<_ParamType>& v) const{return !this->operator < (v);}
			template <typename _ParamType> GINL GAIA::BL operator <= (const VEC2<_ParamType>& v) const{return !this->operator > (v);}
			template <typename _ParamType> GINL GAIA::BL operator > (const VEC2<_ParamType>& v) const{if(GAIA::ALGORITHM::cmp2((const _DataType*)this, (const VEC2<_ParamType>*)&v) > 0) return GAIA::True; return GAIA::False;}
			template <typename _ParamType> GINL GAIA::BL operator < (const VEC2<_ParamType>& v) const{if(GAIA::ALGORITHM::cmp2((const _DataType*)this, (const VEC2<_ParamType>*)&v) < 0) return GAIA::True; return GAIA::False;}
			template <typename _ParamType> GINL const _DataType& operator [] (const _DataType& index) const{return ((_DataType*)this)[index];}
			template <typename _ParamType> GINL _DataType& operator [] (const _DataType& index){return ((_DataType*)this)[index];}
			GINL operator _DataType*(){return (_DataType*)this;}
			GINL operator const _DataType*() const{return (_DataType*)this;}
		public:
			_DataType x, y;
		};

		template <typename _DataType> class VEC3
		{
		public:
		public:
			_DataType x, y, z;
		};
		
		template <typename _DataType> class VEC4
		{
		public:
		private:
			_DataType x, y, z, w;
		};

		template <typename _DataType> class QUA
		{
		public:
		};

		template <typename _DataType> class MTX22
		{
		public:
			GINL MTX22<_DataType>& identity(){}
			GINL GAIA::BL isidentity() const{}
			GINL MTX22<_DataType>& inverse(){}
			GINL MTX22<_DataType>& transpose(){}
		};

		template <typename _DataType> class MTX33
		{
		public:
		};

		template <typename _DataType> class MTX34
		{
		public:
		};

		template <typename _DataType> class MTX44
		{
		public:
		};

		template <typename _DataType> class PLANE
		{
		public:
		};

		template <typename _DataType> class AABR
		{
		public:
			
		public:
			VEC2<_DataType> posMin;
			VEC2<_DataType> posMax;
		};

		template <typename _DataType> class AABB
		{
		public:
			
		public:
			VEC3<_DataType> posMin;
			VEC3<_DataType> posMax;
		};

		template <typename _DataType> class COLOR
		{
		};
	};
};

#endif
