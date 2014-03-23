#ifndef		__GAIA_CONTAINER_BASICSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStack : public GAIA::Base
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
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
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
				friend class BasicStack;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
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
			GINL BasicStack(){this->init();}
			GINL BasicStack(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicStack(){if(m_pFront != GNULL) delete[] m_pFront;}
			GINL GAIA::BL empty() const{return this->size() == 0;}
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
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy();if(size > 0){m_pFront = new _DataType[size];m_capacity = size;m_size = 0;}}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNULL){delete[] m_pFront; m_pFront = GNULL; m_capacity = m_size = 0;}}
			GINL _DataType* front_ptr(){return m_pFront;}
			GINL const _DataType* front_ptr() const{return m_pFront;}
			GINL _DataType* back_ptr(){return &m_pFront[m_size - 1];}
			GINL const _DataType* back_ptr() const{return &m_pFront[m_size - 1];}
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
					if(m_pFront != GNULL)
					{
						for(_SizeType c = 0; c < this->size(); ++c)
							pTemp[c] = m_pFront[c];
						delete[] m_pFront;
					}
					m_pFront = pTemp;
					m_capacity = newsize;
				}
				m_pFront[m_size++] = t;
			}
			GINL GAIA::BL pop(){if(this->size() > 0){--m_size; return GAIA::True;} return GAIA::False;}
			GINL const _DataType& top() const{return m_pFront[this->size() - 1];}
			GINL _DataType& top(){return m_pFront[this->size() - 1];}
			GINL it front_it()
			{
				it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNULL;
				}
				else
				{
					ret.m_index = 0;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL it back_it()
			{
				it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNULL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL const_it const_front_it() const
			{
				const_it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNULL;
				}
				else
				{
					ret.m_index = 0;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL const_it const_back_it() const
			{
				const_it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNULL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->reserve(src.size());
				GAIA::ALGORITHM::copy(m_pFront, src.m_pFront, src.size());
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_AST(index < m_size);
				return m_pFront[index];
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_AST(index < m_size);
				return m_pFront[index];
			}
		private:
			GINL GAIA::GVOID init(){m_pFront = GNULL; m_capacity = m_size = 0;}
		private:
			_DataType* m_pFront;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
