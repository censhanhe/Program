#ifndef		__GAIA_CONTAINER_BASICVECTOR_H__
#define		__GAIA_CONTAINER_BASICVECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicVector
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicVector;
			public:
				GINL BidirectionalIterator(){m_pVector = GNULL; m_index = 0;}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pVector == GNULL || m_index >= m_pVector->size()) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) --m_index; return *this;}
				GINL GAIA::BL operator == (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index == src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(*this == src) return GAIA::False; return GAIA::True;}
				GINL GAIA::BL operator >= (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index >= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator <= (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index <= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator > (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index > src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator < (const BidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index < src.m_index) return GAIA::True; return GAIA::False;}
				GINL BidirectionalIterator& operator = (const BidirectionalIterator& src){m_index = src.m_index; m_pVector = src.m_pVector; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				_SizeType m_index;
				BasicVector<_DataType, _SizeType, _SizeIncreaserType>* m_pVector;
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicVector;
			public:
				GINL ConstBidirectionalIterator(){m_pVector = GNULL; m_index = 0;}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pVector == GNULL || m_index >= m_pVector->size()) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{GAIA_ASSERT(m_pVector != GNULL); return (*m_pVector)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) +m_index; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) --m_index; return *this;}
				GINL GAIA::BL operator == (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index == src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(*this == src) return GAIA::False; return GAIA::True;}
				GINL GAIA::BL operator >= (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index >= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator <= (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index <= src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator > (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index > src.m_index) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator < (const ConstBidirectionalIterator& src) const{GAIA_ASSERT(m_pVector != GNULL); GAIA_ASSERT(m_pVector == src.m_pVector); if(m_index < src.m_index) return GAIA::True; return GAIA::False;}
				GINL ConstBidirectionalIterator& operator = (const ConstBidirectionalIterator& src){m_index = src.m_index; m_pVector = src.m_pVector; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index < m_pVector->size()) +m_index; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){GAIA_ASSERT(m_pVector != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				_SizeType m_index;
				const BasicVector<_DataType, _SizeType, _SizeIncreaserType>* m_pVector;
			};
		public:
			GINL BasicVector(){this->init();}
			GINL BasicVector(const BasicVector<_DataType, _SizeType, _SizeIncreaserType>& src){this->init(); this->operator = (src);}
			GINL ~BasicVector(){if(m_pData != GNULL) delete[] m_pData;}
			GINL const _SizeType& size() const{return m_size;}
			GINL const _SizeType& capacity() const{return m_capacity;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				GAIA_ASSERT(size > 0);
				if(size <= this->capacity())
				{
					m_size = size;
					return;
				}
				this->destroy();
				m_capacity = m_size = size;
				if(size != 0)
					m_pData = new _DataType[size];
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				GAIA_ASSERT(size > 0);
				if(this->capacity() == size)
					return;
				this->destroy();
				m_capacity = size;
				m_size = 0;
				if(size != 0)
					m_pData = new _DataType[size];
			}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL GAIA::GVOID destroy()
			{
				if(m_pData != GNULL)
				{
					delete[] m_pData;
					m_pData = GNULL;
					m_size = m_capacity = 0;
				}
			}
			GINL GAIA::GVOID push_back(const _DataType& t)
			{
				if(this->size() == this->capacity())
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(this->capacity());
					_DataType* pTemp = new _DataType[newsize];
					if(m_pData != GNULL)
					{
						for(_SizeType c = 0; c < this->size(); ++c)
							pTemp[c] = m_pData[c];
						delete[] m_pData;
					}
					m_pData = pTemp;
					m_capacity = newsize;
				}
				m_pData[m_size++] = t;
			}
			GINL GAIA::GVOID pop_back()
			{
				GAIA_ASSERT(this->size() > 0);
				if(m_size > 0)
					--m_size;
			}
			GINL GAIA::BL insert(const _SizeType& index, const _DataType& t)
			{
				GAIA_ASSERT(index >= 0 && index <= this->size());
				if(index > this->size())
					return GAIA::False;
				this->push_back(t);
				if(this->size() == 1)
					return GAIA::True;
				GAIA::ALGORITHM::move_next(m_pData + this->size() - 1, m_pData + this->size() - 2, this->size() - index);
				this->operator[](index) = t;
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
				GAIA_ASSERT(index >= 0 && index < this->size());
				if(index >= this->size())
					return GAIA::False;
				if(index != this->size() - 1)
					GAIA::ALGORITHM::move_prev(m_pData + index, m_pData + index + 1, this->size() - 1 - index);
				--m_size;
				return GAIA::True;
			}
			GINL _SizeType find(const _DataType& t) const
			{
				for(_SizeType x = 0; x < this->size(); ++x)
					if(this->operator[](x) == t)
						return x;
				return (_SizeType)-1;
			}
			GINL _SizeType count(const _DataType& t) const
			{
				if(this->empty())
					return 0;
				_SizeType ret = 0;
				GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, ret);
				return ret;
			}
			GINL GAIA::GVOID sort(){if(this->size() == 0) return; GAIA::ALGORITHM::sort(m_pData, m_pData + this->size() - 1);}
			GINL _SizeType unique()
			{
				if(this->empty())
					return 0;
				_DataType* p = GAIA::ALGORITHM::unique_order(this->front_ptr(), this->back_ptr());
				_SizeType ret = m_size - (p - this->front_ptr() + 1);
				m_size = p - this->front_ptr() + 1;
				return ret;
			}
			GINL _SizeType search(const _DataType& t)
			{
				if(this->size() <= 0)
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::search(m_pData, m_pData + this->size() - 1, t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pData;
			}
			GINL GAIA::BL swap(const _SizeType& index1, const _SizeType& index2){GAIA::ALGORITHM::swap(this->operator[](index1), this->operator[](index2));}
			GINL const _DataType& operator[](const _SizeType& index) const{GAIA_ASSERT(index >= 0 && index < this->size()); return m_pData[index];}
			GINL _DataType& operator[](const _SizeType& index){GAIA_ASSERT(index >= 0 && index < this->size()); return m_pData[index];}
			GINL BasicVector<_DataType, _SizeType, _SizeIncreaserType>& operator = (const BasicVector<_DataType, _SizeType, _SizeIncreaserType>& src)
			{
				this->destroy();
				this->reserve(src.size());
				for(_SizeType x = 0; x < src.size(); ++x)
					this->push_back(src[x]);
				return *this;
			}
			GINL _DataType& front(){return this->operator[](0);}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& back(){return this->operator[](this->size() - 1);}
			GINL const _DataType& back() const{return this->operator[](this->size() - 1);}
			GINL _DataType* front_ptr(){return &this->operator[](0);}
			GINL const _DataType* front_ptr() const{return &this->operator[](0);}
			GINL _DataType* back_ptr(){return &this->operator[](this->size() - 1);}
			GINL const _DataType* back_ptr() const{return &this->operator[](this->size() - 1);}
			GINL BidirectionalIterator front_iterator(){BidirectionalIterator ret; ret.m_index = 0; ret.m_pVector = this; return ret;}
			GINL BidirectionalIterator back_iterator(){BidirectionalIterator ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pVector = this; return ret;}
			GINL ConstBidirectionalIterator const_front_iterator() const{ConstBidirectionalIterator ret; ret.m_index = 0; ret.m_pVector = this; return ret;}
			GINL ConstBidirectionalIterator const_back_iterator() const{ConstBidirectionalIterator ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pVector = this; return ret;}
		private:
			GINL GAIA::GVOID init(){m_pData = GNULL; m_capacity = m_size = 0;}
		private:
			_DataType* m_pData;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
