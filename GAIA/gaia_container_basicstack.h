#ifndef		__GAIA_CONTAINER_BASICSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStack
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStack<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicStack;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{if(m_pStack == GNULL || m_index >= m_pStack->size()) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){GAIA_AST(m_pStack != GNULL); return (*m_pStack)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pStack != GNULL); return (*m_pStack)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_AST(m_pStack != GNULL); if(m_index < m_pStack->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_AST(m_pStack != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){GAIA_AST(m_pStack != GNULL); if(m_index < m_pStack->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){GAIA_AST(m_pStack != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				GINL GAIA::GVOID init(){m_pStack = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				__MyType* m_pStack;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicStack;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{if(m_pStack == GNULL || m_index >= m_pStack->size()) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pStack != GNULL); return (*m_pStack)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(m_pStack != GNULL); if(m_index < m_pStack->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(m_pStack != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){GAIA_AST(m_pStack != GNULL); if(m_index < m_pStack->size()) ++m_index; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){GAIA_AST(m_pStack != GNULL); if(m_index > 0) --m_index; return *this;}
			private:
				GINL GAIA::GVOID init(){m_pStack = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pStack;
			};
		public:
			GINL BasicStack(){this->init();}
			GINL BasicStack(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicStack(){if(m_pData != GNULL) delete[] m_pData;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				GAIA_AST(size >= 0);
				if(size <= this->capacity())
				{
					m_size = size;
					return;
				}
				this->reserve(size);
				m_size = size;
			}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy();if(size > 0){m_pData = new _DataType[size];m_capacity = size;m_size = 0;}}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_pData = GNULL; m_capacity = m_size = 0;}}
			GINL _DataType* front_ptr(){return m_pData;}
			GINL const _DataType* front_ptr() const{return m_pData;}
			GINL _DataType* back_ptr(){return &m_pData[m_size - 1];}
			GINL const _DataType* back_ptr() const{return &m_pData[m_size - 1];}
			GINL _SizeType count(const _DataType& t) const
			{
				if(this->empty())
					return 0;
				_SizeType ret = 0;
				GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, ret);
				return ret;
			}
			GINL GAIA::GVOID push(const _DataType& t)
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
			GINL GAIA::BL pop(){if(this->size() > 0){--m_size; return GAIA::True;} return GAIA::False;}
			GINL const _DataType& top() const{return m_pData[this->size() - 1];}
			GINL _DataType& top(){return m_pData[this->size() - 1];}
			GINL it front_it(){it ret; ret.m_index = 0; ret.m_pStack = this; return ret;}
			GINL it back_it(){it ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pStack = this; return ret;}
			GINL const_it const_front_it() const{const_it ret; ret.m_index = 0; ret.m_pStack = this; return ret;}
			GINL const_it const_back_it() const{const_it ret; ret.m_index = this->size() > 0 ? this->size() - 1 : 0; ret.m_pStack = this; return ret;}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->reserve(src.size());
				GAIA::ALGORITHM::copy(m_pData, src.m_pData, src.size());
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_AST(index < m_size);
				return m_pData[index];
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_AST(index < m_size);
				return m_pData[index];
			}
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
