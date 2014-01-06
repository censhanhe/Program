#ifndef		__GAIA_MATH_COOKIES_H__
#define		__GAIA_MATH_COOKIES_H__

namespace GAIA
{
	namespace MATH
	{
		template <typename _DataType> class VEC2
		{
		public:
			GINL VEC2(){}
			template <typename _ParamType> GINL VEC2(const VEC2<_ParamType>& src){this->x = (_DataType)src.x;this->y = (_DataType)src.y;}
			template <typename _ParamType1, typename _ParamType2> GINL VEC2(const _ParamType1& x, const _ParamType2& y){this->x = (_DataType)x; this->y = (_DataType)y;}
			template <typename _ParamType> GINL VEC2(const _ParamType& v){this->y = this->x = (_DataType)v;}
			template <typename _ParamType> GINL VEC2(const _ParamType* pV){this->x = (_DataType)pV[0]; this->y = (_DataType)pV[1];}
			GINL _DataType length() const{return GAIA::MATH::xsqrt(this->lengthsq())}
			GINL _DataType lengthsq() const{return x * x + y * y;}
			GINL _DataType min() const{return GAIA::ALGORITHM::min(x, y);}
			GINL _DataType max() const{return GAIA::ALGORITHM::max(x, y);}
			GINL GAIA::GVOID normalize(){_DataType t = this->length(); x /= t; y /= t;}
			GINL GAIA::BL isnormalize() const{if(this->lengthsq() == (_DataType)1) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL iszero() const{if(x == (_DataType)0 && y == (_DataType)0) return GAIA::True; return GAIA::False;}
			template <typename _ParamType> GINL VEC2<_DataType> dot(const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL VEC2<_DataType> cross(const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL VEC2 num(const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator + (const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator - (const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator * (const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator / (const VEC2<_ParamType>& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator + (const _ParamType& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator - (const _ParamType& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator * (const _ParamType& src) const{}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator / (const _ParamType& src) const{}
			template <typename _ParamType> GINL VEC2<_DataType> operator + (const VEC2<_ParamType>& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator - (const VEC2<_ParamType>& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator * (const VEC2<_ParamType>& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator / (const VEC2<_ParamType>& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator + (const _ParamType& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator - (const _ParamType& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator * (const _ParamType& src){}
			template <typename _ParamType> GINL VEC2<_DataType> operator / (const _ParamType& src){}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator = (const VEC2<_ParamType>& src){}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator = (const _ParamType& v){}
			template <typename _ParamType> GINL const VEC2<_DataType>& operator = (const _ParamType* pV){}
			template <typename _ParamType> GINL GAIA::BL operator == (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL GAIA::BL operator != (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL GAIA::BL operator >= (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL GAIA::BL operator <= (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL GAIA::BL operator > (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL GAIA::BL operator < (const VEC2<_ParamType>& v) const{}
			template <typename _ParamType> GINL const _DataType& operator [] (const _DataType& index) const{}
			template <typename _ParamType> GINL _DataType& operator [] (const _DataType& index){}
			GINL operator _DataType*(){}
		public:
			_DataType x, y;
		};

		template <typename _DataType> class VEC3
		{
		public:
			GINL VEC3(){}
			template <typename _ParamType> VEC3(const VEC3<_ParamType>& src){this->x = (_DataType)src.x; this->y = (_DataType)src.y; this->z = (_DataType)src.z;}
			template <typename _ParamType1, typename _ParamType2, typename _ParamType3> VEC3(const _ParamType1& x, const _ParamType2& y, const _ParamType3& z){this->x = (_DataType)x; this->y = (_DataType)y; this->z = (_DataType)z;}
			template <typename _ParamType> VEC3(const _ParamType& v){this->z = this->y = this->x = (_DataType)v;}
			template <typename _ParamType> VEC3(const _ParamType* pV){this->x = (_DataType)pV[0]; this->y = (_DataType)pV[1]; this->z = (_DataType)pV[2];}
		public:
			_DataType x, y, z;
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
	};
};

#endif
