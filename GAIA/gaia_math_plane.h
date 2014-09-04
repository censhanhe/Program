#ifndef		__GAIA_MATH_PLANE_H__
#define		__GAIA_MATH_PLANE_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class PLANE : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef PLANE<_DataType> __MyType;
		public:
			GINL PLANE(){}
			template<typename _ParamDataType> PLANE(const GAIA::MATH::PLANE<_DataType>& src){this->operator = (src);}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3, typename _ParamDataType4> PLANE(const _ParamDataType1& a, const _ParamDataType2& b, const _ParamDataType3& c, const _ParamDataType4& d)
			{
				this->a = a;
				this->b = b;
				this->c = c;
				this->d = d;
			}
			template<typename _ParamDataType> PLANE(const _ParamDataType& v){this->operator = (v);}
			template<typename _ParamDataType> PLANE(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> PLANE(_ParamDataType* p){this->operator = (p);}

			template<typename _ParamDataType> __MyType operator + (const PLANE<_ParamDataType>& v) const{__MyType ret; ret.a = a + v.a; ret.b = b + v.b; ret.c = c + v.c; ret.d = d + v.d; return ret;}
			template<typename _ParamDataType> __MyType operator - (const PLANE<_ParamDataType>& v) const{__MyType ret; ret.a = a - v.a; ret.b = b - v.b; ret.c = c - v.c; ret.d = d - v.d; return ret;}
			template<typename _ParamDataType> __MyType operator * (const PLANE<_ParamDataType>& v) const{__MyType ret; ret.a = a * v.a; ret.b = b * v.b; ret.c = c * v.c; ret.d = d * v.d; return ret;}
			template<typename _ParamDataType> __MyType operator / (const PLANE<_ParamDataType>& v) const{__MyType ret; ret.a = a / v.a; ret.b = b / v.b; ret.c = c / v.c; ret.d = d / v.d; return ret;}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& v) const{__MyType ret; ret.a = a + v; ret.b = b + v; ret.c = c + v; ret.d = d + v; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& v) const{__MyType ret; ret.a = a - v; ret.b = b - v; ret.c = c - v; ret.d = d - v; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& v) const{__MyType ret; ret.a = a * v; ret.b = b * v; ret.c = c * v; ret.d = d * v; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& v) const{__MyType ret; ret.a = a / v; ret.b = b / v; ret.c = c / v; ret.d = d / v; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const PLANE<_ParamDataType>& v){a += v.a; b += v.b; c += v.c; d += v.d; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const PLANE<_ParamDataType>& v){a -= v.a; b -= v.b; c -= v.c; d -= v.d; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const PLANE<_ParamDataType>& v){a *= v.a; b *= v.b; c *= v.c; d *= v.d; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const PLANE<_ParamDataType>& v){a /= v.a; b /= v.b; c /= v.c; d /= v.d; return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){a += v; b += v; c += v; d += v; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){a -= v; b -= v; c -= v; d -= v; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){a *= v; b *= v; c *= v; d *= v; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){a /= v; b /= v; c /= v; d /= v; return *this;}

			template<typename _ParamDataType> __MyType& operator = (const PLANE<_ParamDataType>& v){a = (_DataType)v.a; b = (_DataType)v.b; c = (_DataType)v.c; d = (_DataType)v.d; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& v){a = b = c = d = (_DataType)v; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){a = (_DataType)p[0]; b = (_DataType)p[1]; c = (_DataType)p[2]; d = (_DataType)p[3]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = ((const _ParamDataType*)p);}

			template<typename _ParamDataType> GAIA::BL operator == (const PLANE<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const PLANE<_ParamDataType>& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const PLANE<_ParamDataType>& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const PLANE<_ParamDataType>& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const PLANE<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const PLANE<_ParamDataType>& v) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)v) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, v) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& v) const{return !this->operator == (v);}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& v) const{return !this->operator < (v);}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& v) const{return !this->operator > (v);}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, v) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& v) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, v) < 0;}

			template<typename _ParamDataType> const _DataType& operator [] (const _DataType& index) const{GAIA_AST(index < 4); return (&a)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _DataType& index){GAIA_AST(index < 4); return (&a)[index];}

			GINL operator _DataType*(){return &a;}
			GINL operator const _DataType*() const{return &a;}
		public:
			_DataType a, b, c, d;
		};
	};
};

#endif