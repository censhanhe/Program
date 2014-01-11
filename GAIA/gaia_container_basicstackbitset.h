#ifndef		__GAIA_CONTAINER_BASICSTACKBITSET_H__
#define		__GAIA_CONTAINER_BASICSTACKBITSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		#define GAIA_BITSET_SRC (m_bits[index / 8])
		#define GAIA_BITSET_CUR (1 << (index % 8))
		template <typename _SizeType, _SizeType _Size> class BasicStackBitset
		{
		public:
			GINL BasicStackBitset(){this->clear();}
			GINL BasicStackBitset(const BasicStackBitset<_SizeType, _Size>& src){this->operator = (src);}
			GINL BasicStackBitset(const _SizeType& index){this->operator = (index);}
			GINL ~BasicStackBitset(){}
			GINL GAIA::GVOID clear(){GAIA::ALGORITHM::memset(m_bits, 0, _Size);}
			GINL _SizeType capacity(){return _Size;}
			GINL GAIA::BL exist(const _SizeType& index){return (GAIA_BITSET_SRC & GAIA_BITSET_CUR) != 0;}
			GINL GAIA::GVOID set(const _SizeType& index){GAIA_BITSET_SRC |= GAIA_BITSET_CUR;}
			GINL GAIA::GVOID reset(const _SizeType& index){GAIA_BITSET_SRC &= ~GAIA_BITSET_CUR;}
			GINL GAIA::GVOID inverse(const _SizeType& index){if(this->exist(index)) this->reset(index); else this->set(index);}
			GINL BasicStackBitset<_SizeType, _Size>& operator = (const _SizeType& index){this->clear(); GAIA_BITSET_SRC |= GAIA_BITSET_CUR; return *this;}
			GINL BasicStackBitset<_SizeType, _Size>& operator = (const BasicStackBitset<_SizeType, _Size>& src){GAIA::ALGORITHM::memcpy(m_bits, src.m_bits, _Size); return *this;}
			GINL BasicStackBitset<_SizeType, _Size>& operator += (const _SizeType& index){this->set(index); return *this;}
			GINL BasicStackBitset<_SizeType, _Size>& operator += (const BasicStackBitset<_SizeType, _Size>& src){for(_SizeType x = 0; x < _Size; x++) m_bits[x] |= src.m_bit[x]; return *this;}
			GINL BasicStackBitset<_SizeType, _Size>& operator -= (const _SizeType& index){this->reset(index); return *this;}
			GINL BasicStackBitset<_SizeType, _Size>& operator -= (const BasicStackBitset<_SizeType, _Size>& src){for(_SizeType x = 0; x < _Size; x++) m_bits[x] &= ~src.m_bits[x]; return *this;}
			GINL GAIA::BL operator == (const _SizeType& index){return this->exist(index);}
			GINL GAIA::BL operator == (const BasicStackBitset<_SizeType, _Size>& src){if(GAIA::ALGORITHM::memcmp(m_bits, src.m_bits, _Size) == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL operator != (const _SizeType& index){return !(this->operator == (index));}
			GINL GAIA::BL operator != (const BasicStackBitset<_SizeType, _Size>& src){return !(this->operator == (src));}
			GINL BasicStackBitset<_SizeType, _Size>& operator ~ (){for(_SizeType x = 0; x < _Size; x++) m_bits[x] ^ (GAIA::U8)-1; return *this;}
		private:
			GAIA::U8 m_bits[_Size];
		};
	};
};

#endif