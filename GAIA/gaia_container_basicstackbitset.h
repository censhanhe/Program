#ifndef		__GAIA_CONTAINER_BASICSTACKBITSET_H__
#define		__GAIA_CONTAINER_BASICSTACKBITSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		#define GAIA_STACKBITSET_SRC (m_bits[index / 8])
		#define GAIA_STACKBITSET_CUR (1 << (index % 8))
		template<typename _SizeType, _SizeType _Size> class BasicStackBitset
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
			GINL GAIA::GVOID clear(){GAIA::ALGORITHM::memset(m_bits, 0, _Size);}
			GINL GAIA::BL empty() const{return GAIA::False;}
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
			GINL __MyType& operator = (const _SizeType& index){this->clear(); this->set(index); return *this;}
			GINL __MyType& operator = (const __MyType& src){GAIA::ALGORITHM::memcpy(m_bits, src.m_bits, _Size); return *this;}
			GINL __MyType& operator += (const _SizeType& index){this->set(index); return *this;}
			GINL __MyType& operator += (const __MyType& src){for(_SizeType x = 0; x < _Size; ++x) m_bits[x] |= src.m_bits[x]; return *this;}
			GINL __MyType& operator -= (const _SizeType& index){this->reset(index); return *this;}
			GINL __MyType& operator -= (const __MyType& src){for(_SizeType x = 0; x < _Size; ++x) m_bits[x] &= ~src.m_bits[x]; return *this;}
			GINL GAIA::BL operator == (const _SizeType& index){return this->exist(index);}
			GINL GAIA::BL operator == (const __MyType& src){if(GAIA::ALGORITHM::memcmp(m_bits, src.m_bits, _Size) == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL operator != (const _SizeType& index){return !(this->operator == (index));}
			GINL GAIA::BL operator != (const __MyType& src){return !(this->operator == (src));}
			GINL __MyType& operator ~ (){for(_SizeType x = 0; x < _Size; ++x) m_bits[x] ^= (GAIA::U8)-1; return *this;}
			GINL GAIA::BL operator[](const _SizeType& index) const{return this->exist(index);}
		private:
			GAIA::U8 m_bits[_Size];
		};
	};
};

#endif