#ifndef 	__GAIA_MATH_COORD_H__
#define 	__GAIA_MATH_COORD_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _OffsetType, typename _BlockType, typename _BlockSizeType, _BlockSizeType _BlockSize> class Coord : public GAIA::Base
		{
		public:
			typedef _OffsetType _offsettype;
			typedef _BlockType _blocktype;
			typedef _BlockSizeType _blocksizetype;
		public:
			static const _BlockSizeType _blocksize = _BlockSize;
		public:
			typedef Coord<_OffsetType, _BlockType, _BlockSizeType, _BlockSize> __MyType;
		public:
			GINL Coord(){}
			GINL Coord(const __MyType& src){this->operator = (src);}
			template<typename _ParamType> GINL Coord(const _ParamType& t){this->operator = (t);}
			GINL ~Coord(){}
			GINL const _OffsetType& offset() const{return m_offset;}
			GINL const _BlockType& block() const{return m_block;}
			GINL GAIA::GVOID offset(const _OffsetType& offset){m_offset = offset;}
			GINL GAIA::GVOID block(const _BlockType& block){m_block = block;}
			GINL __MyType& operator = (const __MyType& src){m_offset = src.m_offset; m_block = src.m_block; return *this;}
			template<typename _ParamType> GINL __MyType& operator = (const _ParamType& t)
			{
				m_block = (_BlockType)(t / _BlockSize);
				m_offset = (_OffsetType)(t - m_block * _BlockSize);
				return *this;
			}
			GINL __MyType& operator += (const __MyType& src){m_offset += src.m_offset; m_block += src.m_block; this->single_normalize(); return *this;}
			GINL __MyType& operator -= (const __MyType& src){m_offset -= src.m_offset; m_block -= src.m_block; this->single_normalize(); return *this;}
			GINL __MyType& operator *= (const __MyType& src){return *this;}
			GINL __MyType& operator /= (const __MyType& src){return *this;}
			template<typename _ParamType> GINL __MyType& operator += (const _ParamType& src){return *this;}
			template<typename _ParamType> GINL __MyType& operator -= (const _ParamType& src){return *this;}
			template<typename _ParamType> GINL __MyType& operator *= (const _ParamType& src){return *this;}
			template<typename _ParamType> GINL __MyType& operator /= (const _ParamType& src){return *this;}
			GINL __MyType operator + (const __MyType& src) const{__MyType ret = *this; ret += src; return ret;}
			GINL __MyType operator - (const __MyType& src) const{__MyType ret = *this; ret -= src; return ret;}
			GINL __MyType operator * (const __MyType& src) const{__MyType ret = *this; ret *= src; return ret;}
			GINL __MyType operator / (const __MyType& src) const{__MyType ret = *this; ret /= src; return ret;}
			template<typename _ParamType> GINL __MyType operator + (const _ParamType& src) const{__MyType ret = *this; ret += src; return ret;}
			template<typename _ParamType> GINL __MyType operator - (const _ParamType& src) const{__MyType ret = *this; ret -= src; return ret;}
			template<typename _ParamType> GINL __MyType operator * (const _ParamType& src) const{__MyType ret = *this; ret *= src; return ret;}
			template<typename _ParamType> GINL __MyType operator / (const _ParamType& src) const{__MyType ret = *this; ret /= src; return ret;}
			template<typename _ReturnType> GINL operator _ReturnType() const{return (_ReturnType)(m_block * _BlockSize + m_offset);}
		private:
			GINL GAIA::GVOID single_normalize()
			{
				if(GAIA::MATH::xabs(m_offset) >= (_OffsetType)_BlockSize)
				{
					if(m_offset < (_OffsetType)0)
					{
						m_offset += _BlockSize;
						--m_block;
					}
					else
					{
						m_offset -= _BlockSize;
						++m_block;
					}
				}
			}
		private:
			_OffsetType m_offset;
			_BlockType m_block;
		};
	};
};

#endif
