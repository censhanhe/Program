#ifndef		__GAIA_MATH_QUA_H__
#define		__GAIA_MATH_QUA_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class QUA : public GAIA::Base
		{
		public:
		public:
			typedef QUA<_DataType> __MyType;
		public:
			GINL QUA(){}
			template<typename _ParamDataType> QUA(const QUA<_ParamDataType>& src){this->operator = (src);}
			template<typename _ParamDataType> QUA(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> QUA(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> QUA(const _ParamDataType& t){this->operator = (t);}

			GINL _DataType length() const{}
			GINL _DataType lengthsq() const{}
			GINL GAIA::GVOID normalize(){}
			GINL GAIA::BL isnormalized() const{}
			GINL GAIA::GVOID identity();
			GINL GAIA::BL isidentity() const{}
			GINL GAIA::BL iszero() const{return x == (_DataType)0 && y == (_DataType)0 && z == (_DataType)0 && w == (_DataType)0;}
			GINL GAIA::BL isfinited() const{return GAIA::MATH::xfinite(x) && GAIA::MATH::xfinite(y) && GAIA::MATH::xfinite(z) && GAIA::MATH::xfinite(w);}
			GINL GAIA::GVOID inverse();

			template<typename _ParamDataType> _DataType dot(const GAIA::MATH::QUA<_ParamDataType>& v) const{return (x * v.x + y * v.y + z * v.z) * w * v.w;}
			template<typename _ParamDataType> __MyType num(const GAIA::MATH::QUA<_ParamDataType>& v) const{__MyType ret; ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z; ret.w = w * v.w; return ret;}
			template<typename _ParamDataType> _DataType exp(const GAIA::MATH::QUA<_ParamDataType>& v) const{}

			template<typename _ParamEndDataType, typename _ParamFactorDataType> __MyType& slerp(const GAIA::MATH::QUA<_ParamEndDataType>& end, const _ParamFactorDataType& factor){}

			template<typename _ParamDataType> GAIA::GVOID rotatex(const _ParamDataType& x){}
			template<typename _ParamDataType> GAIA::GVOID rotatey(const _ParamDataType& y){}
			template<typename _ParamDataType> GAIA::GVOID rotatez(const _ParamDataType& z){}
			template<typename _ParamDataType1, typename _ParamDataType2> GAIA::GVOID rotate(const GAIA::MATH::VEC3<_ParamDataType1>& nor, const _ParamDataType2& radian){}

			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}

			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::QUA<_ParamDataType>& src){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::QUA<_ParamDataType>& src) const{}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& src) const{}

			template<typename _ParamDataType> _DataType operator [] (const _ParamDataType& index){}
		public:
			_DataType x, y, z, w;
		};
	};
};

#endif
