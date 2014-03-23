#ifndef 	__GAIA_CONTAINER_PTR_H__
#define 	__GAIA_CONTAINER_PTR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Ptr : public GAIA::Base
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
			GINL GAIA::BL empty() const{return m_p == GNULL;}
			GINL __MyType& operator = (const __MyType& src){m_p = src.m_p; return *this;}
			GINL __MyType& operator = (_DataType* p){m_p = p; return *this;}
			GINL _DataType& operator * (){return *m_p;}
			GINL const _DataType& operator * () const{return *m_p;}
			template<typename _ParamSizeType> GINL _DataType& operator [] (const _ParamSizeType& index){return m_p[index];}
			template<typename _ParamSizeType> GINL const _DataType& operator [] (const _ParamSizeType& index) const{return m_p[index];}
			GAIA_CLASS_OPERATOR_COMPARE(m_p, m_p, __MyType);
			GINL GAIA::BL operator == (const _DataType* p) const{return m_p == p;}
			GINL GAIA::BL operator != (const _DataType* p) const{return m_p != p;}
			GINL GAIA::BL operator >= (const _DataType* p) const{return m_p >= p;}
			GINL GAIA::BL operator <= (const _DataType* p) const{return m_p <= p;}
			GINL GAIA::BL operator > (const _DataType* p) const{return m_p > p;}
			GINL GAIA::BL operator < (const _DataType* p) const{return m_p < p;}
			GINL GAIA::BL operator == (_DataType* p) const{return *m_p == *p;}
			GINL GAIA::BL operator != (_DataType* p) const{return *m_p != *p;}
			GINL GAIA::BL operator >= (_DataType* p) const{return *m_p >= *p;}
			GINL GAIA::BL operator <= (_DataType* p) const{return *m_p <= *p;}
			GINL GAIA::BL operator > (_DataType* p) const{return *m_p > *p;}
			GINL GAIA::BL operator < (_DataType* p) const{return *m_p < *p;}
			GINL GAIA::BL operator == (const _DataType& t) const{return *m_p == t;}
			GINL GAIA::BL operator != (const _DataType& t) const{return *m_p != t;}
			GINL GAIA::BL operator >= (const _DataType& t) const{return *m_p >= t;}
			GINL GAIA::BL operator <= (const _DataType& t) const{return *m_p <= t;}
			GINL GAIA::BL operator > (const _DataType& t) const{return *m_p > t;}
			GINL GAIA::BL operator < (const _DataType& t) const{return *m_p < t;}
			GINL operator const _DataType*() const{return m_p;}
			GINL operator _DataType*(){return m_p;}
		private:
			GINL GAIA::GVOID init(){m_p = GNULL;}
		private:
			_DataType* m_p;
		};
	};
};

#endif
