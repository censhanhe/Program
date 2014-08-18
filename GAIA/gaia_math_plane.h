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
		public:
			_DataType a, b, c, d;
		};
	};
};

#endif