#ifndef		__GAIA_MATH_NRGB_H__
#define		__GAIA_MATH_NRGB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class NRGB : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef NRGB<_DataType> __MyType;
		public:
			GINL NRGB(){}
			template<
				typename _ParamDataType1, 
				typename _ParamDataType2, 
				typename _ParamDataType3> NRGB(
					const _ParamDataType1& r,
					const _ParamDataType2& g,
					const _ParamDataType3& b)
			{
				this->r = (_DataType)r;
				this->g = (_DataType)g;
				this->b = (_DataType)b;
			}
			template<typename _ParamDataType> NRGB(const GAIA::MATH::NRGB<_ParamDataType>& src){this->operator = (src);}
			template<typename _ParamDataType> NRGB(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> NRGB(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> NRGB(const _ParamDataType& t){this->operator = (t);}

			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq());}
			GINL _DataType lengthsq() const{return r * r + g * g + b * b;}

			GINL _DataType avg_rgb() const{return GAIA::MATH::xavg3(r, g, b);}
			GINL _DataType max_rgb() const{return GAIA::ALGORITHM::maximize3(r, g, b);}
			GINL _DataType min_rgb() const{return GAIA::ALGORITHM::minimize3(r, g, b);}

			template<typename _ParamEndDataType, typename _ParamFactorDataType> GAIA::GVOID lerp(GAIA::MATH::NRGB<_ParamEndDataType>& end, const _ParamFactorDataType& factor)
			{
				r = GAIA::MATH::lerp(r, end.r, factor);
				g = GAIA::MATH::lerp(g, end.g, factor);
				b = GAIA::MATH::lerp(b, end.b, factor);
			}

			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::NRGB<_ParamDataType>& src){r = src.r; g = src.g; b = src.b; return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){r = p[0]; g = p[1]; b = p[2]; return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = ((const _ParamDataType*)p);}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){r = g = b = t; return *this;}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const _ParamDataType*)&src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const _ParamDataType*)&src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmp3((const _DataType*)this, (const _ParamDataType*)&src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::NRGB<_ParamDataType>& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, src) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, src) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& src) const{return GAIA::ALGORITHM::cmp3k((const _DataType*)this, src) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{GAIA_AST(index < 3); return (&r)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){GAIA_AST(index < 3); return (&r)[index];}

		public:
			_DataType r, g, b;
		};
	};
};

#endif