#ifndef		__GAIA_CONTAINER_BASICBITSET_H__
#define		__GAIA_CONTAINER_BASICBITSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		#define GAIA_BITSET_SRC (m_pFront[index / 8])
		#define GAIA_BITSET_CUR (1 << (index % 8))
		template <typename _SizeType> class BasicBitset
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef BasicBitset<_SizeType> __MyType;
		public:
			GINL BasicBitset(){this->init();}
			GINL BasicBitset(const BasicBitset<_SizeType>& src){this->init(); this->operator = (src);}
			GINL BasicBitset(const _SizeType& index){this->init(); this->set(index);}
			GINL ~BasicBitset(){this->destroy();}
			GINL GAIA::GVOID clear(){GAIA::ALGORITHM::set(this->front_ptr(), 0, this->size()); m_size = 0;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNULL){delete[] m_pFront; m_pFront = GNULL;} m_size = m_capacity = 0;}
			GINL GAIA::U8* front_ptr(){return m_pFront;}
			GINL const GAIA::U8* front_ptr() const{return m_pFront;}
			GINL GAIA::BL exist(const _SizeType& index) const{GAIA_ASSERT(index / 8 < this->size()); if(index / 8 >= this->size()) return GAIA::False; return (GAIA_BITSET_SRC & GAIA_BITSET_CUR) != 0;}
			GINL GAIA::GVOID set(const _SizeType& index){GAIA_ASSERT(index / 8 < this->size()); if(index / 8 >= this->size()) return; GAIA_BITSET_SRC |= GAIA_BITSET_CUR;}
			GINL GAIA::GVOID reset(const _SizeType& index){GAIA_ASSERT(index / 8 < this->size()); if(index / 8 >= this->size()) return; GAIA_BITSET_SRC &= ~GAIA_BITSET_CUR;}
			GINL GAIA::GVOID inverse(const _SizeType& index){GAIA_ASSERT(index / 8 < this->size()); if(index / 8 >= this->size()) return; if(this->exist(index)) this->reset(index); else this->set(index);}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				if(size < this->size())
					m_size = size;
				else
				{
					if(this->size() > m_capacity)
					{
						this->destroy();
						this->reverse(size);
						m_size = size;
						this->clear();
						m_size = size;
					}
					else
					{
						for(_SizeType x = m_size; x < size; ++x)
							this->front_ptr()[x] = 0;
						m_size = size;
					}
				}
			}
			GINL GAIA::GVOID reverse(const _SizeType& size)
			{
				GAIA_ASSERT(size >= 0);
				this->destroy();
				if(size > 0)
				{
					m_pFront = new GAIA::U8[size];
					GAIA::ALGORITHM::set(m_pFront, 0, size);
					m_capacity = size;
					m_size = 0;
				}
			}
			GINL BasicBitset<_SizeType>& operator = (const _SizeType& index){this->clear(); this->set(index); return *this;}
			GINL BasicBitset<_SizeType>& operator = (const BasicBitset<_SizeType>& src)
			{
				this->destroy();
				this->reverse(src.size());
				GAIA::ALGORITHM::copy(this->front_ptr(), src.front_ptr(), src.size());
				return *this;
			}
			GINL BasicBitset<_SizeType>& operator += (const _SizeType& index){this->set(index); return *this;}
			GINL BasicBitset<_SizeType>& operator += (const BasicBitset<_SizeType>& src)
			{
				if(this->capacity() < src.size())
					this->exten(src.size() - this->capacity());
				this->resize(src.size());
				for(_SizeType x = 0; x < src.size(); ++x)
					this->front_ptr()[x] |= src.front_ptr[x];
				return *this;
			}
			GINL BasicBitset<_SizeType>& operator -= (const _SizeType& index){this->reset(index); return *this;}
			GINL BasicBitset<_SizeType>& operator -= (const BasicBitset<_SizeType>& src)
			{
				_SizeType minsize = GAIA::ALGORITHM::minimize(this->size(), src.size());
				for(_SizeType x = 0; x < minsize; ++x)
					this->front_ptr()[x] &= ~src.front_ptr()[x];
				return *this;
			}
			GINL GAIA::BL operator == (const _SizeType& index){return this->exist(index);}
			GINL GAIA::BL operator == (const BasicBitset<_SizeType>& src)
			{
				if(this->size() != src.size())
					return GAIA::False;
				if(GAIA::ALGORITHM::cmp(this->front_ptr(), src.front_ptr(), this->size()) != 0) 
					return GAIA::False; 
				return GAIA::True;
			}
			GINL GAIA::BL operator != (const _SizeType& index){return !(this->operator == (index));}
			GINL GAIA::BL operator != (const BasicBitset<_SizeType>& src){return !(this->operator == (src));}
			GINL BasicBitset<_SizeType>& operator ~ (){for(_SizeType x = 0; x < this->size(); ++x) this->front_ptr()[x] ^ (GAIA::U8)-1; return *this;}
			GINL GAIA::BL operator[](const _SizeType& index) const{return this->exist(index);}
		private:
			GINL GAIA::GVOID init(){m_pFront = GNULL; m_size = m_capacity = 0;}
			GINL GAIA::GVOID exten(const _SizeType& size)
			{
				GAIA_ASSERT(size >= 0);
				if(size == 0)
					return;
				GAIA::U8* pNew = new GAIA::U8[this->capacity() + size];
				if(this->size() > 0)
					GAIA::ALGORITHM::memcpy(pNew, this->front_ptr(), this->size());
				if(m_pFront != GNULL)
					delete[]  m_pFront;
				m_pFront = pNew;
				m_capacity += size;
			}
		private:
			GAIA::U8* m_pFront;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif