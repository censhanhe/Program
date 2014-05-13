#ifndef		__GAIA_CONTAINER_BASICSTACKBITSET_H__
#define		__GAIA_CONTAINER_BASICSTACKBITSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		#define GAIA_STACKBITSET_SRC (m_bits[index / 8])
		#define GAIA_STACKBITSET_CUR (1 << (index % 8))
		template<typename _SizeType, _SizeType _Size> class BasicStackBitset : public GAIA::Base
		{
		public:
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicStackBitset<_SizeType, _Size> __MyType;
		public:
			GINL BasicStackBitset(){this->clear();}
			GINL BasicStackBitset(const __MyType& src){this->operator = (src);}
			GINL BasicStackBitset(const _SizeType& index){this->operator = (index);}
			GINL ~BasicStackBitset(){}
			GINL GAIA::GVOID clear(){GAIA::ALGORITHM::xmemset(this->front_ptr(), 0, _Size);}
			GINL GAIA::BL empty() const{return GAIA::False;}
			GINL GAIA::BL zero() const{return GAIA::ALGORITHM::xmemcheck(this->front_ptr(), 0, this->size()) == 0;}
			GINL GAIA::BL one() const{return GAIA::ALGORITHM::xmemcheck(this->front_ptr(), 0xFF, this->size()) == 0;}
			GINL _SizeType size() const{return _Size;}
			GINL _SizeType capacity() const{return _Size;}
			GINL GAIA::BL exist(const _SizeType& index) const{return (GAIA_STACKBITSET_SRC & GAIA_STACKBITSET_CUR) != 0;}
			GINL GAIA::GVOID set(const _SizeType& index){GAIA_STACKBITSET_SRC |= GAIA_STACKBITSET_CUR;}
			GINL GAIA::GVOID reset(const _SizeType& index){GAIA_STACKBITSET_SRC &= ~GAIA_STACKBITSET_CUR;}
			GINL GAIA::GVOID inverse(const _SizeType& index){if(this->exist(index)) this->reset(index); else this->set(index);}
			GINL GAIA::U8* front_ptr(){return m_bits;}
			GINL GAIA::U8* back_ptr(){return &m_bits[_Size - 1];}
			GINL const GAIA::U8* front_ptr() const{return m_bits;}
			GINL const GAIA::U8* back_ptr() const{return &m_bits[_Size - 1];}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); GAIA::ALGORITHM::xmemcpy(this->front_ptr(), src.front_ptr(), _Size); return *this;}
			GINL __MyType& operator |= (const __MyType& src){for(_SizeType x = 0; x < this->size(); ++x) this->front_ptr()[x] |= src.front_ptr()[x]; return *this;}
			GINL __MyType& operator &= (const __MyType& src){for(_SizeType x = 0; x < this->size(); ++x) this->front_ptr()[x] &= src.front_ptr()[x]; return *this;}
			GINL __MyType& operator ^= (const __MyType& src){for(_SizeType x = 0; x < this->size(); ++x) this->front_ptr()[x] ^= src.front_ptr()[x]; return *this;}
			GINL GAIA::BL operator == (const __MyType& src) const{return GAIA::ALGORITHM::xmemcmp(this->front_ptr(), src.front_ptr(), _Size) == 0;}
			GINL GAIA::BL operator != (const __MyType& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const __MyType& src) const{return GAIA::ALGORITHM::xmemcmp(this->front_ptr(), src.front_ptr(), _Size) >= 0;}
			GINL GAIA::BL operator <= (const __MyType& src) const{return GAIA::ALGORITHM::xmemcmp(this->front_ptr(), src.front_ptr(), _Size) <= 0;}
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
			GINL __MyType operator ~ () const
			{
				__MyType ret = *this;
				for(_SizeType x = 0; x < ret.size(); ++x)
					ret.front_ptr()[x] ^= (GAIA::U8)GINVALID;
				return ret;
			}
			GINL GAIA::BL operator[](const _SizeType& index) const{return this->exist(index);}
		private:
			GAIA::U8 m_bits[_Size];
		};
	};
};

#endif