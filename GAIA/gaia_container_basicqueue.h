#ifndef		__GAIA_CONTAINER_BASICQUEUE_H__
#define		__GAIA_CONTAINER_BASICQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicQueue
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicQueue<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicQueue;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL || m_index >= m_pContainer->size() || m_index < 0;}
				GINL virtual _DataType& operator * (){GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_AST(m_pContainer != GNULL); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_AST(m_pContainer != GNULL); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				__MyType* m_pContainer;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicQueue;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL || m_index >= m_pContainer->size() || m_index < 0;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(m_pContainer != GNULL); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(m_pContainer != GNULL); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicQueue(){this->init();}
			GINL BasicQueue(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicQueue(){if(m_pData != GNULL) delete[] m_pData;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{return m_size;}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& front(){return this->operator[](0);}
			GINL GAIA::GVOID clear(){m_pBack = m_pFront = m_pData; m_size = 0;}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_pData = m_pFront = m_pBack = GNULL; m_capacity = m_size = 0;}}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				this->clear();
				if(size <= this->capacity())
				{
					m_size = size;
					return;
				}
				this->reserve(size);
				m_size = size;
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(size == this->capacity())
				{
					this->clear();
					return;
				}
				if(m_pData != GNULL)
				{
					delete[] m_pData;
					m_pData = GNULL;
				}
				m_pFront = GNULL;
				m_pBack = GNULL;
				m_capacity = 0;
				m_size = 0;
				if(size != 0)
				{
					m_pData = new _DataType[size];
					m_pFront = m_pData;
					m_pBack = m_pData;
					m_capacity = size;
				}
			}
			GINL GAIA::GVOID push(const _DataType& t)
			{
				if(this->capacity() == 0)
				{
					m_pBack = m_pFront = m_pData = new _DataType[1];
					m_capacity = 1;
				}
				else if(this->size() == this->capacity())
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(this->capacity());
					_DataType* pTemp = new _DataType[newsize];
					_SizeType uLenHead = static_cast<_SizeType>(this->capacity() - (m_pFront - m_pData));
					for(_SizeType x = 0; x < uLenHead; ++x)
						pTemp[x] = m_pFront[x];
					_SizeType uLenTail = this->capacity() - uLenHead;
					for(_SizeType x = 0; x < uLenTail; ++x)
						pTemp[x + uLenHead] = m_pData[x];
					m_pFront = pTemp;
					m_pBack = &pTemp[this->capacity()];
					delete[] m_pData;
					m_pData = pTemp;
					m_capacity = newsize;
				}
				if(m_pBack == m_pData + this->capacity())
					m_pBack = m_pData;
				if(m_pFront == m_pData + this->capacity())
					m_pFront = m_pData;
				*m_pBack++ = t;
				++m_size;
			}
			GINL GAIA::BL pop()
			{
				if(!this->empty())
				{
					if(m_pFront == m_pData + this->capacity())
						m_pFront = m_pData;
					m_pFront++;
					if(m_pFront == m_pData + this->capacity() && m_pBack != m_pFront)
						m_pFront = m_pData;
					--m_size;
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL it front_it(){it ret; ret.m_index = 0; ret.m_pContainer = this; return ret;}
			GINL it back_it(){it ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pContainer = this; return ret;}
			GINL const_it const_front_it() const{const_it ret; ret.m_index = 0; ret.m_pContainer = this; return ret;}
			GINL const_it const_back_it() const{const_it ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pContainer = this; return ret;}
			GINL __MyType& operator << (const _DataType& t){this->push(t); return *this;}
			GINL __MyType& operator << (const __MyType& src)
			{
				while(!src.empty())
				{
					this->push(src.front());
					src.pop();
				}
				return *this;
			}
			GINL const __MyType& operator = (const __MyType& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.size(); ++x)
				{
					const _DataType* pTemp;
					if(src.m_pFront < src.m_pBack)
						pTemp = &src.m_pFront[x];
					else
					{
						if(src.capacity() - (src.m_pFront - src.m_pData) > x)
							pTemp = &src.m_pFront[x];
						else
							pTemp = &src.m_pData[x - (src.capacity() - (src.m_pFront - src.m_pData))];
					}
					this->push(*pTemp);
				}
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_AST(index < this->size());
				if(m_pFront < m_pBack)
					return m_pFront[index];
				else
				{
					if(this->capacity() - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (this->capacity() - (m_pFront - m_pData))];
				}
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_AST(index < this->size());
				if(m_pFront < m_pBack)
					return m_pFront[index];
				else
				{
					if(this->capacity() - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (this->capacity() - (m_pFront - m_pData))];
				}
			}
		private:
			GINL GAIA::GVOID init(){m_pData = m_pFront = m_pBack = GNULL; m_capacity = m_size = 0;}
		private:
			_DataType* m_pData;
			_DataType* m_pFront;
			_DataType* m_pBack;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
