#ifndef		__GAIA_MATH_MTX43_H__
#define		__GAIA_MATH_MTX43_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX43 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef MTX43<_DataType> __MyType;
		public:
			GINL MTX43(){}
			GINL MTX43(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> MTX43(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX43(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX43(const _ParamDataType& t){this->operator = (t);}
			GINL GAIA::SIZE size() const{return sizeofarray2(m);}
			GINL GAIA::SIZE sizex() const{return sizeofarray(m[0]);}
			GINL GAIA::SIZE sizey() const{return this->size() / this->sizex();}
			GINL GAIA::GVOID identity()
			{
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0;
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0;
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1;
				m[3][0] = (_DataType)0; m[3][1] = (_DataType)0; m[3][2] = (_DataType)0;
			}
			GINL GAIA::BL isidentity() const
			{
				if(	m[0][0] == (_DataType)1 && m[0][1] == (_DataType)0 && m[0][2] == (_DataType)0 && 
					m[1][0] == (_DataType)0 && m[1][1] == (_DataType)1 && m[1][2] == (_DataType)0 && 
					m[2][0] == (_DataType)0 && m[2][1] == (_DataType)0 && m[2][2] == (_DataType)1 && 
					m[3][0] == (_DataType)0 && m[3][1] == (_DataType)0 && m[3][2] == (_DataType)0)
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::BL isalmostidentity() const
			{
				if(	GAIA::MATH::xequal(m[0][0], (_DataType)1) && GAIA::MATH::xequal(m[0][1], (_DataType)0) && GAIA::MATH::xequal(m[0][2], (_DataType)0) && 
					GAIA::MATH::xequal(m[1][0], (_DataType)0) && GAIA::MATH::xequal(m[1][1], (_DataType)1) && GAIA::MATH::xequal(m[1][2], (_DataType)0) && 
					GAIA::MATH::xequal(m[2][0], (_DataType)0) && GAIA::MATH::xequal(m[2][1], (_DataType)0) && GAIA::MATH::xequal(m[2][2], (_DataType)1) && 
					GAIA::MATH::xequal(m[3][0], (_DataType)0) && GAIA::MATH::xequal(m[3][1], (_DataType)0) && GAIA::MATH::xequal(m[3][2], (_DataType)0))
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::BL isalmostidentity(const _DataType& epsilon) const
			{
				if(	GAIA::MATH::xequal(m[0][0], (_DataType)1, epsilon) && GAIA::MATH::xequal(m[0][1], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[0][2], (_DataType)0, epsilon) && 
					GAIA::MATH::xequal(m[1][0], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[1][1], (_DataType)1, epsilon) && GAIA::MATH::xequal(m[1][2], (_DataType)0, epsilon) && 
					GAIA::MATH::xequal(m[2][0], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[2][1], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[2][2], (_DataType)1, epsilon) && 
					GAIA::MATH::xequal(m[3][0], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[3][1], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[3][2], (_DataType)0, epsilon))
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::BL isfinited() const
			{
				return
					GAIA::MATH::xfinite(m[0][0]) && 
					GAIA::MATH::xfinite(m[0][1]) && 
					GAIA::MATH::xfinite(m[0][2]) && 
					GAIA::MATH::xfinite(m[1][0]) && 
					GAIA::MATH::xfinite(m[1][1]) && 
					GAIA::MATH::xfinite(m[1][2]) && 
					GAIA::MATH::xfinite(m[2][0]) && 
					GAIA::MATH::xfinite(m[2][1]) && 
					GAIA::MATH::xfinite(m[2][2]) && 
					GAIA::MATH::xfinite(m[3][0]) && 
					GAIA::MATH::xfinite(m[3][1]) && 
					GAIA::MATH::xfinite(m[3][2]);
			}
			GINL const _DataType* front_ptr() const{return GRCAST(const _DataType*)(m);}
			GINL _DataType* front_ptr(){return GRCAST(_DataType*)(m);}
			GINL const _DataType* back_ptr() const{return this->front_ptr() + this->size() - 1;}
			GINL _DataType* back_ptr(){return this->front_ptr() + this->size() - 1;}
			GINL __MyType& operator = (const __MyType& src)
			{
				m[0][0] = (_DataType)src.m[0][0]; m[0][1] = (_DataType)src.m[0][1]; m[0][2] = (_DataType)src.m[0][2];
				m[1][0] = (_DataType)src.m[1][0]; m[1][1] = (_DataType)src.m[1][1]; m[1][2] = (_DataType)src.m[1][2];
				m[2][0] = (_DataType)src.m[2][0]; m[2][1] = (_DataType)src.m[2][1]; m[2][2] = (_DataType)src.m[2][2];
				m[3][0] = (_DataType)src.m[3][0]; m[3][1] = (_DataType)src.m[3][1]; m[3][2] = (_DataType)src.m[3][2];
				return *this;
			}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){GAIA_AST(p != GNIL); GAIA::ALGO::copy(this->front_ptr(), p, this->size()); return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){GAIA::ALGO::set(this->front_ptr(), t, this->size()); return *this;}
			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX43<_ParamDataType>& src) const{return !(this->operator >= (src));}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) != 0;}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			template<typename _ParamDataType1, typename _ParamDataType2> _DataType& operator () (const _ParamDataType1& i1, const _ParamDataType2& i2){GAIA_AST(i1 >= 0 && i1 < 4); GAIA_AST(i2 >= 0 && i2 < 3); return m[i1][i2];}
		public:
			_DataType m[4][3];
		};
	};
};

#endif