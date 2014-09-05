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
			GINL MTX44(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> MTX44(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX44(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX44(const _ParamDataType& t){this->operator = (t);}

			GINL GAIA::GVOID identity()
			{
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0; m[0][3] = (_DataType)0; 
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0; m[1][3] = (_DataType)0; 
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1; m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0; m[3][3] = (_DataType)1; 
			}
			GINL GAIA::BL isidentity() const
			{
				if(	m[0][0] == (_DataType)1 && m[0][1] == (_DataType)0 && m[0][2] == (_DataType)0 && m[0][3] == (_DataType)0 && 
					m[1][0] == (_DataType)0 && m[1][1] == (_DataType)1 && m[1][2] == (_DataType)0 && m[1][3] == (_DataType)0 && 
					m[2][0] == (_DataType)0 && m[2][1] == (_DataType)0 && m[2][2] == (_DataType)1 && m[2][3] == (_DataType)0 && 
					m[3][0] == (_DataType)0 && m[3][1] == (_DataType)0 && m[3][2] == (_DataType)0 && m[3][3] == (_DataType)1)
					return GAIA::True;
				return GAIA::False;
			}

			GINL GAIA::GVOID transpose()
			{
				GAIA::ALGORITHM::swap(m[0][1], m[1][0]);
				GAIA::ALGORITHM::swap(m[0][2], m[2][0]);
				GAIA::ALGORITHM::swap(m[0][3], m[3][0]);
				GAIA::ALGORITHM::swap(m[1][2], m[2][1]);
				GAIA::ALGORITHM::swap(m[1][3], m[3][1]);
				GAIA::ALGORITHM::swap(m[2][3], m[3][2]);
			}
			GINL GAIA::GVOID inverse()
			{
			}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> GAIA::GVOID translate(const _ParamDataType1& x, const _ParamDataType2& y, const _ParamDataType3& z)
			{
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0; m[0][3] = (_DataType)0; 
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0; m[1][3] = (_DataType)0; 
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1; m[2][3] = (_DataType)0; 
				m[3][0] =    x; m[3][1] =    y; m[3][2] =    z; m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType> GAIA::GVOID rotatex(const _ParamDataType& x)
			{
				_DataType cosv = GAIA::MATH::xcos(x);
				_DataType sinv = GAIA::MATH::xsin(x);
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0; m[0][3] = (_DataType)0; 
				m[1][0] = (_DataType)0; m[1][1] = cosv;			m[1][2] = sinv;			m[1][3] = (_DataType)0; 
				m[2][0] = (_DataType)0; m[2][1] = -sinv;		m[2][2] = cosv;			m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0; m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType> GAIA::GVOID rotatey(const _ParamDataType& y)
			{
				_DataType cosv = GAIA::MATH::xcos(y);
				_DataType sinv = GAIA::MATH::xsin(y);
				m[0][0] = cosv;			m[0][1] = (_DataType)0; m[0][2] = -sinv; m[0][3] = (_DataType)0; 
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0; m[1][3] = (_DataType)0; 
				m[2][0] = sinv;			m[2][1] = (_DataType)0; m[2][2] = cosv; m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0; m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType> GAIA::GVOID rotatez(const _ParamDataType& z)
			{
				_DataType cosv = GAIA::MATH::xcos(z);
				_DataType sinv = GAIA::MATH::xsin(z);
				m[0][0] = cosv;			m[0][1] = sinv;			m[0][2] = (_DataType)0; m[0][3] = (_DataType)0; 
				m[1][0] = -sinv;		m[1][1] = cosv;			m[1][2] = (_DataType)0; m[1][3] = (_DataType)0; 
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1; m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0; m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType1, typename _ParamDataType2> GAIA::GVOID rotate(const GAIA::MATH::VEC3<_ParamDataType1>& nor, const _ParamDataType2& radian)
			{
				_DataType cosv = GAIA::MATH::xcos(radian);
				_DataType sinv = GAIA::MATH::xsin(radian);
				_DataType cosvi = (_DataType)1 - cosv;
				m[0][0] = nor.x * nor.x * cosvi + cosv; m[0][1] = nor.x * nor.y * cosvi + nor.z * sinv; m[0][2] = nor.x * nor.z * cosvi - nor.y * sinv; m[0][3] = (_DataType)0; 
				m[1][0] = nor.x * nor.y * cosvi - nor.z * sinv; m[1][1] = nor.y * nor.y * cosvi + cosv; m[1][2] = nor.y * nor.z * cosvi + nor.x * sinv; m[1][3] = (_DataType)0; 
				m[2][0] = nor.x * nor.z * cosvi + nor.y * sinv; m[2][1] = nor.y * nor.z * cosvi - nor.x * sinv; m[2][2] = nor.z * nor.z * cosvi + cosv; m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0;							m[3][1] = (_DataType)0;							m[3][2] = (_DataType)0;					m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> GAIA::GVOID scale(const _ParamDataType1& x, const _ParamDataType2& y, const _ParamDataType3& z)
			{
				m[0][0] =    x;			m[0][1] = (_DataType)0; m[0][2] = (_DataType)0; m[0][3] = (_DataType)0; 
				m[1][0] = (_DataType)0; m[1][1] =    y;			m[1][2] = (_DataType)0; m[1][3] = (_DataType)0; 
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] =    z;			m[2][3] = (_DataType)0; 
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0; m[3][3] = (_DataType)1; 
			}
			template<typename _ParamDataType> GAIA::GVOID position(const GAIA::MATH::VEC3<_ParamDataType>& src){m[3][0] = src.x; m[3][1] = src.y; m[3][2] = src.z;}
			template<typename _ParamDataType> GAIA::MATH::VEC3<_ParamDataType> position() const{GAIA::MATH::VEC3<_ParamDataType> ret; ret.x = m[3][0]; ret.y = m[3][1]; ret.z = m[3][2]; return ret;}
			template<typename _ParamEndDataType, typename _ParamFactorDataType> __MyType& lerp(const GAIA::MATH::MTX44<_ParamEndDataType>& end, const _ParamFactorDataType& factor)
			{
			}

			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX44<_ParamDataType>& src) const
			{
				__MyType ret;
				ret.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0] + m[0][3] * src.m[3][0];
				ret.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1] + m[0][3] * src.m[3][1];
				ret.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2] + m[0][3] * src.m[3][2];
				ret.m[0][3] = m[0][0] * src.m[0][3] + m[0][1] * src.m[1][3] + m[0][2] * src.m[2][3] + m[0][3] * src.m[3][3];
				ret.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0] + m[1][3] * src.m[3][0];
				ret.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1] + m[1][3] * src.m[3][1];
				ret.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2] + m[1][3] * src.m[3][2];
				ret.m[1][3] = m[1][0] * src.m[0][3] + m[1][1] * src.m[1][3] + m[1][2] * src.m[2][3] + m[1][3] * src.m[3][3];
				ret.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0] + m[2][3] * src.m[3][0];
				ret.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1] + m[2][3] * src.m[3][1];
				ret.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2] + m[2][3] * src.m[3][2];
				ret.m[2][3] = m[2][0] * src.m[0][3] + m[2][1] * src.m[1][3] + m[2][2] * src.m[2][3] + m[2][3] * src.m[3][3];
				ret.m[3][0] = m[3][0] * src.m[0][0] + m[3][1] * src.m[1][0] + m[3][2] * src.m[2][0] + m[3][3] * src.m[3][0];
				ret.m[3][1] = m[3][0] * src.m[0][1] + m[3][1] * src.m[1][1] + m[3][2] * src.m[2][1] + m[3][3] * src.m[3][1];
				ret.m[3][2] = m[3][0] * src.m[0][2] + m[3][1] * src.m[1][2] + m[3][2] * src.m[2][2] + m[3][3] * src.m[3][2];
				ret.m[3][3] = m[3][0] * src.m[0][3] + m[3][1] * src.m[1][3] + m[3][2] * src.m[2][3] + m[3][3] * src.m[3][3];
				return ret;
			}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX43<_ParamDataType>& src) const
			{
				__MyType ret;
				ret.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0] + m[0][3] * src.m[3][0];
				ret.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1] + m[0][3] * src.m[3][1];
				ret.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2] + m[0][3] * src.m[3][2];
				ret.m[0][3] = m[0][3] * src.m[3][3];
				ret.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0] + m[1][3] * src.m[3][0];
				ret.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1] + m[1][3] * src.m[3][1];
				ret.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2] + m[1][3] * src.m[3][2];
				ret.m[1][3] = m[1][3] * src.m[3][3];
				ret.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0] + m[2][3] * src.m[3][0];
				ret.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1] + m[2][3] * src.m[3][1];
				ret.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2] + m[2][3] * src.m[3][2];
				ret.m[2][3] = m[2][3] * src.m[3][3];
				ret.m[3][0] = m[3][0] * src.m[0][0] + m[3][1] * src.m[1][0] + m[3][2] * src.m[2][0] + m[3][3] * src.m[3][0];
				ret.m[3][1] = m[3][0] * src.m[0][1] + m[3][1] * src.m[1][1] + m[3][2] * src.m[2][1] + m[3][3] * src.m[3][1];
				ret.m[3][2] = m[3][0] * src.m[0][2] + m[3][1] * src.m[1][2] + m[3][2] * src.m[2][2] + m[3][3] * src.m[3][2];
				ret.m[3][3] = m[3][3] * src.m[3][3];
				return ret;
			}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX33<_ParamDataType>& src) const
			{
				__MyType ret;
				ret.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0];
				ret.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1];
				ret.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2];
				ret.m[0][3] = m[0][3];
				ret.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0];
				ret.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1];
				ret.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2];
				ret.m[1][3] = m[1][3];
				ret.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0];
				ret.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1];
				ret.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2];
				ret.m[2][3] = m[2][3];
				ret.m[3][0] = m[3][0] * src.m[0][0] + m[3][1] * src.m[1][0] + m[3][2] * src.m[2][0];
				ret.m[3][1] = m[3][0] * src.m[0][1] + m[3][1] * src.m[1][1] + m[3][2] * src.m[2][1];
				ret.m[3][2] = m[3][0] * src.m[0][2] + m[3][1] * src.m[1][2] + m[3][2] * src.m[2][2];
				ret.m[3][3] = m[3][3];
				return ret;
			}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX22<_ParamDataType>& src) const
			{
				__MyType ret;
				ret.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0];
				ret.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1];
				ret.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2];
				ret.m[0][3] = m[0][3];
				ret.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0];
				ret.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1];
				ret.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2];
				ret.m[1][3] = m[1][3];
				ret.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0];
				ret.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1];
				ret.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2];
				ret.m[2][3] = m[2][3];
				ret.m[3][0] = m[3][0] * src.m[0][0] + m[3][1] * src.m[1][0];
				ret.m[3][1] = m[3][0] * src.m[0][1] + m[3][1] * src.m[1][1];
				ret.m[3][2] = m[3][0] * src.m[0][2] + m[3][1] * src.m[1][2] + m[3][2];
				ret.m[3][3] = m[3][3];
				return ret;
			}

			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX44<_ParamDataType>& src){__MyType temp = *this; *this = temp * src; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX43<_ParamDataType>& src){__MyType temp = *this; *this = temp * src; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX33<_ParamDataType>& src){__MyType temp = *this; *this = temp * src; return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX22<_ParamDataType>& src){__MyType temp = *this; *this = temp * src; return *this;}

			GINL __MyType& operator = (const __MyType& src)
			{
				m[0][0] = (_DataType)src.m[0][0]; m[0][1] = (_DataType)src.m[0][1]; m[0][2] = (_DataType)src.m[0][2]; m[0][3] = (_DataType)src.m[0][3];
				m[1][0] = (_DataType)src.m[1][0]; m[1][1] = (_DataType)src.m[1][1]; m[1][2] = (_DataType)src.m[1][2]; m[1][3] = (_DataType)src.m[1][3];
				m[2][0] = (_DataType)src.m[2][0]; m[2][1] = (_DataType)src.m[2][1]; m[2][2] = (_DataType)src.m[2][2]; m[2][3] = (_DataType)src.m[2][3];
				m[3][0] = (_DataType)src.m[3][0]; m[3][1] = (_DataType)src.m[3][1]; m[3][2] = (_DataType)src.m[3][2]; m[3][3] = (_DataType)src.m[3][3];
				return *this;
			}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){GAIA_AST(p != GNULL); GAIA::ALGORITHM::copy(GSCAST(_DataType*)(m), p, sizeofarray2(m));}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){GAIA::ALGORITHM::set((_DataType*)m, t, sizeofarray2(m));}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmps(GSCAST(_DataType)(m), GSCAST(_DataType)(src.m), sizeofarray2(m)) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmps(GSCAST(_DataType)(m), GSCAST(_DataType)(src.m), sizeofarray2(m)) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return GAIA::ALGORITHM::cmps(GSCAST(_DataType)(m), GSCAST(_DataType)(src.m), sizeofarray2(m)) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX44<_ParamDataType>& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX43<_ParamDataType>& src) const
			{
				if(	m[0][0] == src.m[0][0] && m[0][1] == src.m[0][1] && m[0][2] == src.m[0][2] && m[0][3] == (_DataType)0 && 
					m[1][0] == src.m[1][0] && m[1][1] == src.m[1][1] && m[1][2] == src.m[1][2] && m[1][3] == (_DataType)0 && 
					m[2][0] == src.m[2][0] && m[2][1] == src.m[2][1] && m[2][2] == src.m[2][2] && m[2][3] == (_DataType)0 && 
					m[3][0] == src.m[3][0] && m[3][1] == src.m[3][1] && m[3][2] == src.m[3][2] && m[3][3] == (_DataType)1)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX43<_ParamDataType>& src) const
			{
				if(m[0][0] > src.m[0][0])
					return GAIA::True;
				if(m[0][0] < src.m[0][0])
					return GAIA::False;
				if(m[0][1] > src.m[0][1])
					return GAIA::True;
				if(m[0][1] < src.m[0][1])
					return GAIA::False;
				if(m[0][2] > src.m[0][2])
					return GAIA::True;
				if(m[0][2] < src.m[0][2])
					return GAIA::False;
				if(m[0][3] > (_DataType)0)
					return GAIA::True;
				if(m[0][3] < (_DataType)0)
					return GAIA::False;

				if(m[1][0] > src.m[1][0])
					return GAIA::True;
				if(m[1][0] < src.m[1][0])
					return GAIA::False;
				if(m[1][1] > src.m[1][1])
					return GAIA::True;
				if(m[1][1] < src.m[1][1])
					return GAIA::False;
				if(m[1][2] > src.m[1][2])
					return GAIA::True;
				if(m[1][2] < src.m[1][2])
					return GAIA::False;
				if(m[1][3] > (_DataType)0)
					return GAIA::True;
				if(m[1][3] < (_DataType)0)
					return GAIA::False;

				if(m[2][0] > src.m[2][0])
					return GAIA::True;
				if(m[2][0] < src.m[2][0])
					return GAIA::False;
				if(m[2][1] > src.m[2][1])
					return GAIA::True;
				if(m[2][1] < src.m[2][1])
					return GAIA::False;
				if(m[2][2] > src.m[2][2])
					return GAIA::True;
				if(m[2][2] < src.m[2][2])
					return GAIA::False;
				if(m[2][3] > (_DataType)0)
					return GAIA::True;
				if(m[2][3] < (_DataType)0)
					return GAIA::False;

				if(m[3][0] > src.m[3][0])
					return GAIA::True;
				if(m[3][0] < src.m[3][0])
					return GAIA::False;
				if(m[3][1] > src.m[3][1])
					return GAIA::True;
				if(m[3][1] < src.m[3][1])
					return GAIA::False;
				if(m[3][2] > src.m[3][2])
					return GAIA::True;
				if(m[3][2] < src.m[3][2])
					return GAIA::False;
				if(m[3][3] >= (_DataType)1)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX43<_ParamDataType>& src) const
			{
				if(m[0][0] < src.m[0][0])
					return GAIA::True;
				if(m[0][0] > src.m[0][0])
					return GAIA::False;
				if(m[0][1] < src.m[0][1])
					return GAIA::True;
				if(m[0][1] > src.m[0][1])
					return GAIA::False;
				if(m[0][2] < src.m[0][2])
					return GAIA::True;
				if(m[0][2] > src.m[0][2])
					return GAIA::False;
				if(m[0][3] < (_DataType)0)
					return GAIA::True;
				if(m[0][3] > (_DataType)0)
					return GAIA::False;

				if(m[1][0] < src.m[1][0])
					return GAIA::True;
				if(m[1][0] > src.m[1][0])
					return GAIA::False;
				if(m[1][1] < src.m[1][1])
					return GAIA::True;
				if(m[1][1] > src.m[1][1])
					return GAIA::False;
				if(m[1][2] < src.m[1][2])
					return GAIA::True;
				if(m[1][2] > src.m[1][2])
					return GAIA::False;
				if(m[1][3] < (_DataType)0)
					return GAIA::True;
				if(m[1][3] > (_DataType)0)
					return GAIA::False;

				if(m[2][0] < src.m[2][0])
					return GAIA::True;
				if(m[2][0] > src.m[2][0])
					return GAIA::False;
				if(m[2][1] < src.m[2][1])
					return GAIA::True;
				if(m[2][1] > src.m[2][1])
					return GAIA::False;
				if(m[2][2] < src.m[2][2])
					return GAIA::True;
				if(m[2][2] > src.m[2][2])
					return GAIA::False;
				if(m[2][3] < (_DataType)0)
					return GAIA::True;
				if(m[2][3] > (_DataType)0)
					return GAIA::False;

				if(m[3][0] < src.m[3][0])
					return GAIA::True;
				if(m[3][0] > src.m[3][0])
					return GAIA::False;
				if(m[3][1] < src.m[3][1])
					return GAIA::True;
				if(m[3][1] > src.m[3][1])
					return GAIA::False;
				if(m[3][2] < src.m[3][2])
					return GAIA::True;
				if(m[3][2] > src.m[3][2])
					return GAIA::False;
				if(m[3][3] <= (_DataType)1)
					return GAIA::True;
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator >= (src));}

			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{return const_cast<__MyType*>(this)[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){return (GSCAST(_DataType*)(m))[index];}
		public:
			_DataType m[4][4];
		};
	};
};

#endif
