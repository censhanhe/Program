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
			GINL QUA(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> QUA(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> QUA(const _ParamDataType& t){this->operator = (t);}

			GINL GAIA::GVOID identity();
			GINL GAIA::BL isidentity() const{}

			GINL GAIA::GVOID inverse();

			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}

			GINL __MyType& operator = (const __MyType& src){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::QUA<_ParamDataType>& src) const{}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::QUA<_ParamDataType>& src) const{}

			template<typename _ParamDataType> _DataType operator [] (const _ParamDataType& index){}
		public:
			_DataType x, y, z, w;
		};
	};
};

#endif