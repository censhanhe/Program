#ifndef		__GAIA_MATH_MTX33_H__
#define		__GAIA_MATH_MTX33_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX33 : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
		public:
			typedef MTX33<_DataType> __MyType;
		public:
			GINL MTX33(){}
			GINL MTX33(const __MyType& src){this->operator = (src);}
			template<typename _ParamDataType> MTX33(const _ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX33(_ParamDataType* p){this->operator = (p);}
			template<typename _ParamDataType> MTX33(const _ParamDataType& t){this->operator = (t);}
			GINL GAIA::SIZE size() const{return sizeofarray2(m);}
			GINL GAIA::SIZE sizex() const{return sizeofarray(m[0]);}
			GINL GAIA::SIZE sizey() const{return this->size() / this->sizex();}
			GINL GAIA::GVOID identity()
			{
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0;
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0;
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1;
			}
			GINL GAIA::BL isidentity() const
			{
				if(	m[0][0] == (_DataType)1 && m[0][1] == (_DataType)0 && m[0][2] == (_DataType)0 && 
					m[1][0] == (_DataType)0 && m[1][1] == (_DataType)1 && m[1][2] == (_DataType)0 && 
					m[2][0] == (_DataType)0 && m[2][1] == (_DataType)0 && m[2][2] == (_DataType)1)
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::BL isalmostidentity() const
			{
				if(	GAIA::MATH::xequal(m[0][0], (_DataType)1) && GAIA::MATH::xequal(m[0][1], (_DataType)0) && GAIA::MATH::xequal(m[0][2], (_DataType)0) && 
					GAIA::MATH::xequal(m[1][0], (_DataType)0) && GAIA::MATH::xequal(m[1][1], (_DataType)1) && GAIA::MATH::xequal(m[1][2], (_DataType)0) && 
					GAIA::MATH::xequal(m[2][0], (_DataType)0) && GAIA::MATH::xequal(m[2][1], (_DataType)0) && GAIA::MATH::xequal(m[2][2], (_DataType)1))
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::BL isalmostidentity(const _DataType& epsilon) const
			{
				if(	GAIA::MATH::xequal(m[0][0], (_DataType)1, epsilon) && GAIA::MATH::xequal(m[0][1], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[0][2], (_DataType)0, epsilon) && 
					GAIA::MATH::xequal(m[1][0], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[1][1], (_DataType)1, epsilon) && GAIA::MATH::xequal(m[1][2], (_DataType)0, epsilon) && 
					GAIA::MATH::xequal(m[2][0], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[2][1], (_DataType)0, epsilon) && GAIA::MATH::xequal(m[2][2], (_DataType)1, epsilon))
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
					GAIA::MATH::xfinite(m[2][2]);
			}
			GINL GAIA::GVOID transpose()
			{
				GAIA::ALGO::swap(m[0][1], m[1][0]);
				GAIA::ALGO::swap(m[0][2], m[2][0]);
				GAIA::ALGO::swap(m[1][2], m[2][1]);
			}
			GINL _DataType inverse()
			{
				__MyType m = (*this);
				_DataType det = GSCAST(_DataType)(1);
				GAIA::N8 is[3];
				GAIA::N8 js[3];
				GAIA::N8 f = 1;
				for(GAIA::N8 k = 0; k < 3; ++k)
				{
					_DataType tmax = 0;
					for(GAIA::N8 i = k; i < 3; ++i)
					{
						for(GAIA::N8 j = k; j < 3; ++j)
						{
							const _DataType t = GAIA::MATH::xabs(m(i, j));
							if(t > tmax)
							{
								tmax = t;
								is[k] = i;
								js[k] = j;
							}
						}
					}
					if(GAIA::MATH::xequalzero(tmax))
						return GSCAST(_DataType)(0);
					if(is[k] != k)
					{
						f = -f;
						GAIA::ALGO::swap(m(k, 0), m(is[k], 0));
						GAIA::ALGO::swap(m(k, 1), m(is[k], 1));
						GAIA::ALGO::swap(m(k, 2), m(is[k], 2));
					}
					if(js[k] != k)
					{
						f = -f;
						GAIA::ALGO::swap(m(0, k), m(0, js[k]));
						GAIA::ALGO::swap(m(1, k), m(1, js[k]));
						GAIA::ALGO::swap(m(2, k), m(2, js[k]));
					}
					det *= m(k, k);
					m(k, k) = 1 / m(k, k);	
					for(GAIA::N8 j = 0; j < 3; ++j)
					{
						if(j != k)
							m(k, j) *= m(k, k);
					}
					for(GAIA::N8 i = 0; i < 3; ++i)
					{
						if(i != k)
						{
							for(GAIA::N8 j = 0; j < 3; ++j)
							{
								if(j != k)
									m(i, j) = m(i, j) - m(i, k) * m(k, j);
							}
						}
					}
					for(GAIA::N8 i = 0; i < 3; ++i)
					{
						if(i != k)
							m(i, k) *= -m(k, k);
					}
				}
				for(GAIA::N8 k = 2; k >= 0; --k)
				{
					if(js[k] != k)
					{
						GAIA::ALGO::swap(m(k, 0), m(js[k], 0));
						GAIA::ALGO::swap(m(k, 1), m(js[k], 1));
						GAIA::ALGO::swap(m(k, 2), m(js[k], 2));
					}
					if(is[k] != k)
					{
						GAIA::ALGO::swap(m(0, k), m(0, is[k]));
						GAIA::ALGO::swap(m(1, k), m(1, is[k]));
						GAIA::ALGO::swap(m(2, k), m(2, is[k]));
					}
				}
				(*this) = m;
				if(f < 0)
					return -det;
				else
					return +det;
			}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> GAIA::GVOID translate(const _ParamDataType1& x, const _ParamDataType2& y)
			{
				m[0][0] = (_DataType)1; m[0][1] = (_DataType)0; m[0][2] = (_DataType)0;
				m[1][0] = (_DataType)0; m[1][1] = (_DataType)1; m[1][2] = (_DataType)0;
				m[2][0] = (_DataType)x;	m[2][1] = (_DataType)y;	m[2][2] = (_DataType)1;
			}
			template<typename _ParamDataType> GAIA::GVOID rotatex(const _ParamDataType& x)
			{
			}
			template<typename _ParamDataType> GAIA::GVOID rotatey(const _ParamDataType& y)
			{
			}
			template<typename _ParamDataType1, typename _ParamDataType2> GAIA::GVOID rotate(const GAIA::MATH::VEC2<_ParamDataType1>& nor, const _ParamDataType2& radian)
			{
			}
			template<typename _ParamDataType1, typename _ParamDataType2, typename _ParamDataType3> GAIA::GVOID scale(const _ParamDataType1& x, const _ParamDataType2& y)
			{
				m[0][0] =    x;			m[0][1] = (_DataType)0; m[0][2] = (_DataType)0;
				m[1][0] = (_DataType)0; m[1][1] =    y;			m[1][2] = (_DataType)0;
				m[2][0] = (_DataType)0; m[2][1] = (_DataType)0; m[2][2] = (_DataType)1;
			}
			template<typename _ParamDataType> GAIA::GVOID position(const GAIA::MATH::VEC2<_ParamDataType>& src){m[2][0] = src.x; m[2][1] = src.y;}
			GAIA::MATH::VEC2<_DataType> position() const{GAIA::MATH::VEC2<_DataType> ret; ret.x = m[2][0]; ret.y = m[2][1]; return ret;}
			template<typename _ParamEndDataType, typename _ParamFactorDataType> __MyType& lerp(const GAIA::MATH::MTX33<_ParamEndDataType>& end, const _ParamFactorDataType& factor)
			{
			}
			template<typename _ParamDataType> __MyType operator * (const GAIA::MATH::MTX33<_ParamDataType>& src) const
			{
				__MyType ret;
				ret.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0];
				ret.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1];
				ret.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2];
				ret.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0];
				ret.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1];
				ret.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2];
				ret.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0];
				ret.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1];
				ret.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2];
				return ret;
			}
			template<typename _ParamDataType> __MyType& operator *= (const GAIA::MATH::MTX33<_ParamDataType>& src){__MyType temp = *this; *this = temp * src; return *this;}
			GINL const _DataType* front_ptr() const{return GRCAST(const _DataType*)(m);}
			GINL _DataType* front_ptr(){return GRCAST(_DataType*)(m);}
			GINL const _DataType* back_ptr() const{return this->front_ptr() + this->size() - 1;}
			GINL _DataType* back_ptr(){return this->front_ptr() + this->size() - 1;}
			GINL GAIA::GVOID to32(GAIA::MATH::MTX32<_DataType>& dst) const
			{
				dst.m[0][0] = m[0][0]; dst.m[0][1] = m[0][1];
				dst.m[1][0] = m[1][0]; dst.m[1][1] = m[1][1];
				dst.m[2][0] = m[2][0]; dst.m[2][1] = m[2][1];
			}
			GINL GAIA::GVOID from32(const GAIA::MATH::MTX32<_DataType>& src)
			{
				m[0][0] = src.m[0][0]; m[0][1] = src.m[0][1];
				m[1][0] = src.m[1][0]; m[1][1] = src.m[1][1];
				m[2][0] = src.m[2][0]; m[2][1] = src.m[2][1];
			}
			GINL GAIA::GVOID to22(GAIA::MATH::MTX22<_DataType>& dst) const
			{
				dst.m[0][0] = m[0][0]; dst.m[0][1] = m[0][1];
				dst.m[1][0] = m[1][0]; dst.m[1][1] = m[1][1];
			}
			GINL GAIA::GVOID from22(const GAIA::MATH::MTX22<_DataType>& src)
			{
				m[0][0] = src.m[0][0]; m[0][1] = src.m[0][1];
				m[1][0] = src.m[1][0]; m[1][1] = src.m[1][1];
			}
			template<typename _ParamDataType> __MyType& operator = (const GAIA::MATH::MTX33<_ParamDataType>& src)
			{
				m[0][0] = (_DataType)src.m[0][0]; m[0][1] = (_DataType)src.m[0][1]; m[0][2] = (_DataType)src.m[0][2];
				m[1][0] = (_DataType)src.m[1][0]; m[1][1] = (_DataType)src.m[1][1]; m[1][2] = (_DataType)src.m[1][2];
				m[2][0] = (_DataType)src.m[2][0]; m[2][1] = (_DataType)src.m[2][1]; m[2][2] = (_DataType)src.m[2][2];
				return *this;
			}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){GAIA_AST(p != GNIL); GAIA::ALGO::copy(this->front_ptr(), p, this->size()); return *this;}
			template<typename _ParamDataType> __MyType& operator = (_ParamDataType* p){return this->operator = (GSCAST(const _ParamDataType*)(p));}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType& t){GAIA::ALGO::set(this->front_ptr(), t, this->size()); return *this;}
			template<typename _ParamDataType> GAIA::BL operator == (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return !(this->operator == (src));}
			template<typename _ParamDataType> GAIA::BL operator >= (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return GAIA::ALGO::cmps(this->front_ptr(), src.front_ptr(), this->size()) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return !(this->operator <= (src));}
			template<typename _ParamDataType> GAIA::BL operator < (const GAIA::MATH::MTX33<_ParamDataType>& src) const{return !(this->operator >= (src));}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) != 0;}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType* p) const{return GAIA::ALGO::cmps(this->front_ptr(), p, this->size()) < 0;}
			template<typename _ParamDataType> const _DataType& operator [] (const _ParamDataType& index) const{GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			template<typename _ParamDataType> _DataType& operator [] (const _ParamDataType& index){GAIA_AST(index >= 0 && index < this->size()); return this->front_ptr()[index];}
			template<typename _ParamDataType1, typename _ParamDataType2> _DataType& operator () (const _ParamDataType1& i1, const _ParamDataType2& i2){GAIA_AST(i1 >= 0 && i1 < 3); GAIA_AST(i2 >= 0 && i2 < 3); return m[i1][i2];}
		public:
			_DataType m[3][3];
		};
	};
};

#endif