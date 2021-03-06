#ifndef 	__GAIA_CONTAINER_PTR_H__
#define 	__GAIA_CONTAINER_PTR_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Ptr : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef Ptr<_DataType> __MyType;
		public:
			GINL Ptr(){this->init();}
			GINL Ptr(const __MyType& src){this->init(); this->operator = (src);}
			GINL Ptr(_DataType* p){this->init(); this->operator = (p);}
			GINL ~Ptr(){}
			GINL GAIA::BL empty() const{return m_p == GNIL;}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); m_p = src.m_p; return *this;}
			GINL __MyType& operator = (_DataType* p){m_p = p; return *this;}
			GINL _DataType& operator * (){return *m_p;}
			GINL const _DataType& operator * () const{return *m_p;}
			GAIA::NM operator - (const __MyType& src) const{return m_p - src.m_p;}
			template<typename _ParamSizeType> __MyType& operator += (const _ParamSizeType& size){m_p += size; return *this;}
			template<typename _ParamSizeType> __MyType& operator -= (const _ParamSizeType& size){m_p -= size; return *this;}
			template<typename _ParamSizeType> __MyType operator + (const _ParamSizeType& size) const{__MyType ret = *this; ret += size; return ret;}
			template<typename _ParamSizeType> __MyType operator - (const _ParamSizeType& size) const{__MyType ret = *this; ret -= size; return ret;}
			GINL __MyType& operator ++ (){(*this) += 1; return *this;}
			GINL __MyType& operator -- (){(*this) -= 1; return *this;}
			GINL __MyType operator ++ (GAIA::N32){__MyType ret = *this; ++ret; return ret;}
			GINL __MyType operator -- (GAIA::N32){__MyType ret = *this; --ret; return ret;}
			template<typename _ParamSizeType> _DataType& operator [] (const _ParamSizeType& index){return m_p[index];}
			template<typename _ParamSizeType> const _DataType& operator [] (const _ParamSizeType& index) const{return m_p[index];}
			GAIA_CLASS_OPERATOR_COMPARE(m_p, m_p, __MyType);
			GINL GAIA::BL operator == (const _DataType* p) const{return m_p == p;}
			GINL GAIA::BL operator != (const _DataType* p) const{return m_p != p;}
			GINL GAIA::BL operator >= (const _DataType* p) const{return m_p >= p;}
			GINL GAIA::BL operator <= (const _DataType* p) const{return m_p <= p;}
			GINL GAIA::BL operator > (const _DataType* p) const{return m_p > p;}
			GINL GAIA::BL operator < (const _DataType* p) const{return m_p < p;}
			GINL GAIA::BL operator == (_DataType* p) const{return m_p == p;}
			GINL GAIA::BL operator != (_DataType* p) const{return m_p != p;}
			GINL GAIA::BL operator >= (_DataType* p) const{return m_p >= p;}
			GINL GAIA::BL operator <= (_DataType* p) const{return m_p <= p;}
			GINL GAIA::BL operator > (_DataType* p) const{return m_p > p;}
			GINL GAIA::BL operator < (_DataType* p) const{return m_p < p;}
			GINL GAIA::BL operator == (const _DataType& t) const{return *m_p == t;}
			GINL GAIA::BL operator != (const _DataType& t) const{return *m_p != t;}
			GINL GAIA::BL operator >= (const _DataType& t) const{return *m_p >= t;}
			GINL GAIA::BL operator <= (const _DataType& t) const{return *m_p <= t;}
			GINL GAIA::BL operator > (const _DataType& t) const{return *m_p > t;}
			GINL GAIA::BL operator < (const _DataType& t) const{return *m_p < t;}
			GINL operator const _DataType*() const{return m_p;}
			GINL operator _DataType*(){return m_p;}
		private:
			GINL GAIA::GVOID init(){m_p = GNIL;}
		private:
			_DataType* m_p;
		};
	};
};

#endif
