#ifndef		__GAIA_MATH_ARGB_H__
#define		__GAIA_MATH_ARGB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class ARGB : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef ARGB<_DataType> __MyType;
		public:
			GINL ARGB(){}
			template<
				typename _ParamDataType1, 
				typename _ParamDataType2, 
				typename _ParamDataType3, 
				typename _ParamDataType4> ARGB(
					const _ParamDataType1& a,
					const _ParamDataType2& r,
					const _ParamDataType3& g,
					const _ParamDataType4& b)
			{
				this->a = GSCAST(_DataType)(a);
				this->r = GSCAST(_DataType)(r);
				this->g = GSCAST(_DataType)(g);
				this->b = GSCAST(_DataType)(b);
			}
			template<typename _ParamDataType> ARGB(const GAIA::MATH::ARGB<_ParamDataType>& src){this->operator = (src);}
			template<typename _ParamDataType> ARGB(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> ARGB(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> ARGB(const _ParamDataType& t){this->operator = (t);}

			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return r * r + g * g + b * b;}

			GINL GAIA::BL iszero() const{return a == (_DataType)0 && r == (_DataType)0 && g == (_DataType)0 && b == (_DataType)0;}
			GINL GAIA::BL isfinite() const{return GAIA::MATH::xfinite(a) && GAIA::MATH::xfinite(r) && GAIA::MATH::xfinite(g) && GAIA::MATH::xfinite(b);}

			GINL _DataType avg_rgb() const{return GAIA::MATH::xavg3(r, g, b);}
			GINL _DataType avg_argb() const{return GAIA::MATH::xavg4(a, r, g, b);}
			GINL _DataType max_rgb() const{return GAIA::ALGORITHM::maximize3(r, g, b);}
			GINL _DataType max_argb() const{return GAIA::ALGORITHM::maximize(GAIA::ALGORITHM::maximize(a, r), GAIA::ALGORITHM::maximize(g, b));}
			GINL _DataType min_rgb() const{return GAIA::ALGORITHM::minimize3(r, g, b);}
			GINL _DataType min_argb() const{return GAIA::ALGORITHM::minimize(GAIA::ALGORITHM::minimize(a, r), GAIA::ALGORITHM::minimize(g, b));}

			template<typename _ParamEndDataType, typename _ParamFactorDataType> GAIA::GVOID lerp(GAIA::MATH::ARGB<_ParamEndDataType>& end, const _ParamFactorDataType& factor)
			{
				a = GAIA::MATH::lerp(a, end.a, factor);
				r = GAIA::MATH::lerp(r, end.r, factor);
				g = GAIA::MATH::lerp(g, end.g, factor);
				b = GAIA::MATH::lerp(b, end.b, factor);
			}

			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::ARGB<_ParamDataType>& src){a = src.a; r = src.r; g = src.g; b = src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){a = p[0]; r = p[1]; g = p[2]; b = p[3]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){a = r = g = b = t; return *this;}

			template<typename _ParamDataType> __MyType operator + (const GAIA::MATH::ARGB<_ParamDataType>& src) const{__MyType ret = *this; ret += src; return ret;}
			template<typename _ParamDataType> __MyType operator - (const GAIA::MATH::ARGB<_ParamDataType>& src) const{__MyType ret = *this; ret -= src; return ret;}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::ARGB<_ParamDataType>& src) const{__MyType ret = *this; ret *= src; return ret;}
			template<typename _ParamDataType> __MyType operator / (const GAIA::MATH::ARGB<_ParamDataType>& src) const{__MyType ret = *this; ret /= src; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const GAIA::MATH::ARGB<_ParamDataType>& src){a += src.a; r += src.r; g += src.g; b += src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const GAIA::MATH::ARGB<_ParamDataType>& src){a -= src.a; r -= src.r; g -= src.g; b -= src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::ARGB<_ParamDataType>& src){a *= src.a; r *= src.r; g *= src.g; b *= src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const GAIA::MATH::ARGB<_ParamDataType>& src){a /= src.a; r /= src.r; g /= src.g; b /= src.b; return *this;}

			template<typename _ParamDataType> __MyType operator + (const _ParamDataType& src) const{__MyType ret = *this; ret.a += src; ret.r += src; ret.g += src; ret.b += src; return ret;}
			template<typename _ParamDataType> __MyType operator - (const _ParamDataType& src) const{__MyType ret = *this; ret.a -= src; ret.r -= src; ret.g -= src; ret.b -= src; return ret;}
			template<typename _ParamDataType> __MyType operator * (const _ParamDataType& src) const{__MyType ret = *this; ret.a *= src; ret.r *= src; ret.g *= src; ret.b *= src; return ret;}
			template<typename _ParamDataType> __MyType operator / (const _ParamDataType& src) const{__MyType ret = *this; ret.a /= src; ret.r /= src; ret.g /= src; ret.b /= src; return ret;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& src){a += src; r += src; g += src; b += src; return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& src){a -= src; r -= src; g -= src; b -= src; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& src){a *= src; r *= src; g *= src; b *= src; return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& src){a /= src; r /= src; g /= src; b /= src; return *this;}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp4((const _DataType*)*this, (const _ParamDataType*)src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp4k((const _DataType*)*this, src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{GAIA_AST(index < 4); return (&a)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){GAIA_AST(index < 4); return (&a)[index];}
			GINL operator _DataType*(){return &a;}
			GINL operator const _DataType*() const{return &a;}

		public:
			_DataType a, r, g, b;
		};
	};
};

#endif