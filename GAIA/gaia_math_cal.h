#ifndef 	__GAIA_MATH_CAL_H__
#define 	__GAIA_MATH_CAL_H__

namespace GAIA
{
	namespace MATH
	{
		GAIA_ENUM_BEGIN(CALOP)
			CALOP_ADD,
			CALOP_SUB,
			CALOP_MUL,
			CALOP_DIV,
			CALOP_MOD,
			CALOP_SQRT,
			CALOP_POW,
			CALOP_LOG,
			CALOP_LN,
			CALOP_SIN,
			CALOP_COS,
			CALOP_TAN,
			CALOP_ATAN2,
			CALOP_ASIN,
			CALOP_ACOS,
			CALOP_RANDOM,
			CALOP_RANDOMF,
			CALOP_ABS,
			CALOP_CLAMP,
			CALOP_MAX,
			CALOP_MIN,
			CALOP_SIGN,
			CALOP_FLOOR,
			CALOP_CEIL,
			CALOP_ROUND,
		GAIA_ENUM_END(CALOP)
		static const GAIA::CH* CALOP_STRINGA[] = 
		{
			"CALOP_INVALID",
			"CALOP_ADD",
			"CALOP_SUB",
			"CALOP_MUL",
			"CALOP_DIV",
			"CALOP_MOD",
			"CALOP_SQRT",
			"CALOP_POW",
			"CALOP_LOG",
			"CALOP_LN",
			"CALOP_SIN",
			"CALOP_COS",
			"CALOP_TAN",
			"CALOP_ATAN2",
			"CALOP_ASIN",
			"CALOP_ACOS",
			"CALOP_RANDOM",
			"CALOP_RANDOMF",
			"CALOP_ABS",
			"CALOP_CLAMP",
			"CALOP_MAX",
			"CALOP_MIN",
			"CALOP_SIGN",
			"CALOP_FLOOR",
			"CALOP_CEIL",
			"CALOP_ROUND",
		};
		static const GAIA::WCH* CALOP_STRINGW[] = 
		{
			L"CALOP_INVALID",
			L"CALOP_ADD",
			L"CALOP_SUB",
			L"CALOP_MUL",
			L"CALOP_DIV",
			L"CALOP_MOD",
			L"CALOP_SQRT",
			L"CALOP_POW",
			L"CALOP_LOG",
			L"CALOP_LN",
			L"CALOP_SIN",
			L"CALOP_COS",
			L"CALOP_TAN",
			L"CALOP_ATAN2",
			L"CALOP_ASIN",
			L"CALOP_ACOS",
			L"CALOP_RANDOM",
			L"CALOP_RANDOMF",
			L"CALOP_ABS",
			L"CALOP_CLAMP",
			L"CALOP_MAX",
			L"CALOP_MIN",
			L"CALOP_SIGN",
			L"CALOP_FLOOR",
			L"CALOP_CEIL",
			L"CALOP_ROUND",
		};
		template<typename _DataType> class CalUnitCmn : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;

		public:
			typedef CalUnitCmn<_DataType> __MyType;

		public:
			GINL CalUnitCmn(){}
			GINL ~CalUnitCmn(){}

			GINL CalUnitCmn(const __MyType& src){this->operator = (src);}
			GINL CalUnitCmn(const GAIA::BL& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::NM& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::UM& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::U8& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::U16& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::U32& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::U64& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::N8& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::N16& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::N32& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::N64& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::F32& v){this->operator = (v);}
			GINL CalUnitCmn(const GAIA::F64& v){this->operator = (v);}

			GINL __MyType& operator = (const __MyType& src){m_v = src.m_v; return *this;}
			GINL __MyType& operator = (const GAIA::BL& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::NM& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::UM& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::U8& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::U16& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::U32& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::U64& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::N8& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::N16& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::N32& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::N64& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::F32& v){m_v = (_DataType)v; return *this;}
			GINL __MyType& operator = (const GAIA::F64& v){m_v = (_DataType)v; return *this;}

			GINL operator GAIA::BL() const{return (GAIA::BL)m_v;}
			GINL operator GAIA::NM() const{return (GAIA::NM)m_v;}
			GINL operator GAIA::UM() const{return (GAIA::UM)m_v;}
			GINL operator GAIA::U8() const{return (GAIA::U8)m_v;}
			GINL operator GAIA::U16() const{return (GAIA::U16)m_v;}
			GINL operator GAIA::U32() const{return (GAIA::U32)m_v;}
			GINL operator GAIA::U64() const{return (GAIA::U64)m_v;}
			GINL operator GAIA::N8() const{return (GAIA::N8)m_v;}
			GINL operator GAIA::N16() const{return (GAIA::N16)m_v;}
			GINL operator GAIA::N32() const{return (GAIA::N32)m_v;}
			GINL operator GAIA::N64() const{return (GAIA::N64)m_v;}
			GINL operator GAIA::F32() const{return (GAIA::F32)m_v;}
			GINL operator GAIA::F64() const{return (GAIA::F64)m_v;}

			GINL __MyType& operator = (const GAIA::CH* p){m_v = GAIA::ALGO::string_cast<_DataType>(p); return *this;}
			GINL __MyType& operator = (const GAIA::WCH* p){m_v = GAIA::ALGO::string_cast<_DataType>(p); return *this;}
			template<typename _ParamCharType, typename _ParamSizeType> GAIA::BL tostring(_ParamCharType* p, const _ParamSizeType& size) const{return GAIA::ALGO::value_cast(m_v, p, size);}

			GINL __MyType& operator += (const __MyType& src){m_v += src.m_v; return *this;}
			GINL __MyType& operator += (const GAIA::BL& v){m_v += (_DataType)(v ? 1 : 0); return *this;}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType& v){m_v += (_DataType)v; return *this;}
			GINL __MyType& operator -= (const __MyType& src){m_v -= src.m_v; return *this;}
			GINL __MyType& operator -= (const GAIA::BL& v){m_v -= (_DataType)(v ? 1 : 0); return *this;}
			template<typename _ParamDataType> __MyType& operator -= (const _ParamDataType& v){m_v -= (_DataType)v; return *this;}
			GINL __MyType& operator *= (const __MyType& src){m_v *= src.m_v; return *this;}
			GINL __MyType& operator *= (const GAIA::BL& v){m_v *= (_DataType)(v ? 1 : 0); return *this;}
			template<typename _ParamDataType> __MyType& operator *= (const _ParamDataType& v){m_v *= (_DataType)v; return *this;}
			GINL __MyType& operator /= (const __MyType& src){m_v /= src.m_v; return *this;}
			GINL __MyType& operator /= (const GAIA::BL& v){m_v /= (_DataType)(v ? 1 : 0); return *this;}
			template<typename _ParamDataType> __MyType& operator /= (const _ParamDataType& v){m_v /= (_DataType)v; return *this;}

			GINL __MyType operator + (const __MyType& src) const{__MyType ret = *this; ret += src; return ret;}
			GINL __MyType operator + (const GAIA::BL& v) const{__MyType ret = *this; ret += v; return ret;}
			GINL __MyType operator + (const GAIA::NM& v) const{__MyType ret = *this; ret += v; return ret;}
			GINL __MyType operator - (const __MyType& src) const{__MyType ret = *this; ret -= src; return ret;}
			GINL __MyType operator - (const GAIA::BL& v) const{__MyType ret = *this; ret -= v; return ret;}
			GINL __MyType operator - (const GAIA::NM& v) const{__MyType ret = *this; ret -= v; return ret;}
			GINL __MyType operator * (const __MyType& src) const{__MyType ret = *this; ret *= src; return ret;}
			GINL __MyType operator * (const GAIA::BL& v) const{__MyType ret = *this; ret *= v; return ret;}
			GINL __MyType operator * (const GAIA::NM& v) const{__MyType ret = *this; ret *= v; return ret;}
			GINL __MyType operator / (const __MyType& src) const{__MyType ret = *this; ret /= src; return ret;}
			GINL __MyType operator / (const GAIA::BL& v) const{__MyType ret = *this; ret /= v; return ret;}
			GINL __MyType operator / (const GAIA::NM& v) const{__MyType ret = *this; ret /= v; return ret;}

		private:
			_DataType m_v;
		};
		typedef CalUnitCmn<GAIA::N32> CalUnitN32;
		typedef CalUnitCmn<GAIA::N64> CalUnitN64;
		typedef CalUnitCmn<GAIA::F32> CalUnitF32;
		typedef CalUnitCmn<GAIA::F64> CalUnitF64;
	};
};

#endif
