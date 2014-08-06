#ifndef		__GAIA_MATH_ARGB_H__
#define		__GAIA_MATH_ARGB_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class ARGB : public GAIA::Entity
		{
		public:
			typedef ARGB<_DataType> __MyType;
		public:
			GINL ARGB(){}
			GINL ARGB(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> ARGB(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> ARGB(const _ParamDataType& t){this->operator = (t);}

			GINL _DataType average_rgb() const{}
			GINL _DataType average_argb() const{}
			GINL _DataType max_rgb() const{}
			GINL _DataType max_argb() const{}
			GINL _DataType min_rgb() const{}
			GINL _DataType min_argb() const{}

			template<typename _ParamEndDataType, typename _ParamFactorDataType> __MyType& lerp(GAIA::MATH::ARGB<_ParamEndDataType>& end, const _ParamFactorDataType& factor);

			GINL __MyType& operator = (const __MyType& src){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::ARGB<_ParamDataType>& src) const{}

			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType& src) const{}
		public:
			_DataType a, r, g, b;
		};
	};
};

#endif