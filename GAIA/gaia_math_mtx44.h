#ifndef		__GAIA_MATH_MTX44_H__
#define		__GAIA_MATH_MTX44_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX44 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef MTX44<_DataType> __MyType;
		public:
			GINL MTX44(){}
			GINL MTX44(const __MyType& src){}
			template<typename _ParamDataType> MTX44(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX44(const _ParamDataType& t){this->operator = (t);}

			GINL GAIA::GVOID identity();
			GINL GAIA::BL isidentity() const{}

			GINL GAIA::GVOID transpose();
			GINL GAIA::GVOID inverse();
			template<typename _ParamDataType> GAIA::GVOID position(const GAIA::MATH::VEC3<_ParamDataType>& src){}
			template<typename _ParamDataType> const GAIA::MATH::VEC3<_ParamDataType>& position() const{}
			template<typename _ParamEndDataType, typename _ParamFactorDataType> __MyType& lerp(const GAIA::MATH::MTX44<_ParamEndDataType>& end, const _ParamFactorDataType& factor);

			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX33<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX22<_ParamDataType>& src) const{}

			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX33<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX22<_ParamDataType>& src) const{}

			GINL __MyType& operator = (const __MyType& src){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX44<_ParamDataType>& src) const{}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX34<_ParamDataType>& src) const{}

			template<typename _ParamDataType> _DataType operator [] (const _ParamDataType& index){}
		public:
			_DataType m[4][4];
		};
	};
};

#endif