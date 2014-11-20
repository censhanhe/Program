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

			GINL GAIA::SIZE size() const{return 4;}

			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return r * r + g * g + b * b;}

			GINL GAIA::BL iszero() const{return a == (_DataType)0 && r == (_DataType)0 && g == (_DataType)0 && b == (_DataType)0;}
			GINL GAIA::BL isfinited() const{return GAIA::MATH::xfinite(a) && GAIA::MATH::xfinite(r) && GAIA::MATH::xfinite(g) && GAIA::MATH::xfinite(b);}

			GINL _DataType avg_rgb() const{return GAIA::MATH::xavg3(r, g, b);}
			GINL _DataType avg_argb() const{return GAIA::MATH::xavg4(a, r, g, b);}
			GINL _DataType max_rgb() const{return GAIA::ALGO::maximize3(r, g, b);}
			GINL _DataType max_argb() const{return GAIA::ALGO::maximize(GAIA::ALGO::maximize(a, r), GAIA::ALGO::maximize(g, b));}
			GINL _DataType min_rgb() const{return GAIA::ALGO::minimize3(r, g, b);}
			GINL _DataType min_argb() const{return GAIA::ALGO::minimize(GAIA::ALGO::minimize(a, r), GAIA::ALGO::minimize(g, b));}

			GINL GAIA::GVOID torealmode(){(*this) /= 255;}
			GINL GAIA::GVOID tobytemode(){(*this) *= 255;}

			GINL GAIA::U32 tou32() const
			{
				GAIA::U32 ret;
				GRCAST(GAIA::U8*)(&ret)[3] = GSCAST(GAIA::U8)(a);
				GRCAST(GAIA::U8*)(&ret)[2] = GSCAST(GAIA::U8)(r);
				GRCAST(GAIA::U8*)(&ret)[1] = GSCAST(GAIA::U8)(g);
				GRCAST(GAIA::U8*)(&ret)[0] = GSCAST(GAIA::U8)(b);
				return ret;
			}
			GINL GAIA::GVOID fromu32(GAIA::U32 u)
			{
				a = GSCAST(_DataType)(GRCAST(GAIA::U8*)(&u)[3]);
				r = GSCAST(_DataType)(GRCAST(GAIA::U8*)(&u)[2]);
				g = GSCAST(_DataType)(GRCAST(GAIA::U8*)(&u)[1]);
				b = GSCAST(_DataType)(GRCAST(GAIA::U8*)(&u)[0]);
			}

			GINL const _DataType* front_ptr() const{return &r;}
			GINL _DataType* front_ptr(){return &r;}
			GINL const _DataType* back_ptr() const{return this->front_ptr() + this->size() - 1;}
			GINL _DataType* back_ptr(){return this->front_ptr() + this->size() - 1;}

			template<typename _ParamEndDataType, typename _ParamFactorDataType> GAIA::GVOID lerp(GAIA::MATH::ARGB<_ParamEndDataType>& end, const _ParamFactorDataType& factor)
			{
				a = GAIA::MATH::lerp(a, end.a, factor);
				r = GAIA::MATH::lerp(r, end.r, factor);
				g = GAIA::MATH::lerp(g, end.g, factor);
				b = GAIA::MATH::lerp(b, end.b, factor);
			}

			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::ARGB<_ParamDataType>& src){a = src.a; r = src.r; g = src.g; b = src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){r = p[0]; g = p[1]; b = p[2]; a = p[3]; return *this;}
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

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGO::cmp4((const _DataType*)*this, (const _ParamDataType*)src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGO::cmp4((const _DataType*)*this, (const _ParamDataType*)src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return GAIA::ALGO::cmp4((const _DataType*)*this, (const _ParamDataType*)src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::ARGB<_ParamDataType>& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& src) const{return GAIA::ALGO::cmp4k((const _DataType*)*this, src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& src) const{return GAIA::ALGO::cmp4k((const _DataType*)*this, src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& src) const{return GAIA::ALGO::cmp4k((const _DataType*)*this, src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& src) const{return !(this->operator >= (src));}

			GINL operator _DataType*(){return this->front_ptr();}
			GINL operator const _DataType*() const{return this->front_ptr();}

		public:
			_DataType r, g, b, a;
		};
	};
};

#endif
