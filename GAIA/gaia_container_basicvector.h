#ifndef		__GAIA_CONTAINER_BASICVECTOR_H__
#define		__GAIA_CONTAINER_BASICVECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicVector
		{
		public:
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
				friend class BasicVector;

			public:
				GINL BidirectionalIterator(){m_pVector = GNULL; m_index = 0;}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pVector == GNULL || m_index >= m_pVector->size()) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) m_index++; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) m_index--; return *this;}
				GINL GAIA::BL operator == (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index == src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(*this == src) return GAIA::False; return GAIA::True;}
				GINL GAIA::BL operator >= (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index >= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator <= (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index <= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator > (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index > src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator < (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index < src.m_index) return GAIA::True; return GAIA::False;}
				GINL const BidirectionalIterator& operator = (const BidirectionalIterator& src){m_index = src.m_index; m_pVector = src.m_pVector; return *this;}

			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) m_index++; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) m_index--; return *this;}

			private:
				_SizeType m_index;
				BasicVector<_DataType, _SizeType, _SizeIncreaserType>* m_pVector;
			};

			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
				friend class BasicVector;

			public:
				GINL ConstBidirectionalIterator(){m_pVector = GNULL; m_index = 0;}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pVector == GNULL || m_index >= m_pVector->size()) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) m_index++; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) m_index--; return *this;}
				GINL GAIA::BL operator == (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index == src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(*this == src) return GAIA::False; return GAIA::True;}
				GINL GAIA::BL operator >= (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index >= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator <= (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index <= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator > (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index > src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator < (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index < src.m_index) return GAIA::True; return GAIA::False;}
				GINL const ConstBidirectionalIterator& operator = (const ConstBidirectionalIterator& src){m_index = src.m_index; m_pVector = src.m_pVector; return *this;}

			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) m_index++; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) m_index--; return *this;}

			private:
				_SizeType m_index;
				const BasicVector<_DataType, _SizeType, _SizeIncreaserType>* m_pVector;
			};

		public:
			GINL BasicVector(){m_pData = GNULL; m_size = m_cursize = 0;}
			GINL ~BasicVector(){delete[] m_pData;}
			GINL const _SizeType& size() const{return m_cursize;}
			GINL const _SizeType& capacity() const{return m_size;}
			GINL GAIA::BL empty() const{if(m_cursize == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				GAIA_ASSERT(size > 0);
				if(size < m_size)
				{
					m_cursize = size;
					return;
				}
				this->destroy();
				m_pData = new _DataType[size];
				m_size = m_cursize = size;
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				GAIA_ASSERT(size > 0);
				if(m_size == size)
					return;
				this->destroy();
				m_pData = new _DataType[size];
				m_size = size;
				m_cursize = 0;
			}
			GINL GAIA::GVOID clear(){m_cursize = 0;}
			GINL GAIA::GVOID destroy()
			{
				if(m_pData != GNULL)
				{
					delete[] m_pData;
					m_pData = GNULL;
					m_cursize = m_size = 0;
				}
			}
			GINL GAIA::GVOID push_back(const _DataType& t)
			{
				if(m_cursize == m_size)
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(m_size);
					_DataType* pTemp = new _DataType[newsize];
					if(m_pData != GNULL)
					{
						for(_SizeType c = 0; c < m_cursize; c++)
							pTemp[c] = m_pData[c];
						delete[] m_pData;
					}
					m_pData = pTemp;
					m_size = newsize;
				}
				m_pData[m_cursize++] = t;
			}
			GINL GAIA::GVOID pop_back()
			{
				GAIA_ASSERT(m_cursize > 0);
				if(m_cursize > 0)
					m_cursize--;
			}
			GINL GAIA::GVOID insert(const _SizeType& index, const _DataType& t)
			{
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
			}
			GINL GAIA::BL swap(const _SizeType& index1, const _SizeType& index2)
			{
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_ASSERT(index < m_cursize);
				return m_pData[index];
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_ASSERT(index < m_cursize);
				return m_pData[index];
			}
			GINL BidirectionalIterator front(){BidirectionalIterator ret; ret.m_index = 0; ret.m_pVector = this; return ret;}
			GINL ConstBidirectionalIterator front() const{ConstBidirectionalIterator ret; ret.m_index = 0; ret.m_pVector = this; return ret;}
			GINL BidirectionalIterator back(){BidirectionalIterator ret; ret.m_index = m_cursize > 0 ? m_cursize - 1 : 0; ret.m_pVector = this; return ret;}
			GINL ConstBidirectionalIterator back() const{ConstBidirectionalIterator ret; ret.m_index = m_cursize > 0 ? m_cursize - 1 : 0; ret.m_pVector = this; return ret;}

		private:
			_DataType* m_pData;
			_SizeType m_size;
			_SizeType m_cursize;
		};
	};
};

#endif