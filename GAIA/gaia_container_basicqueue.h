#ifndef		__GAIA_CONTAINER_BASICQUEUE_H__
#define		__GAIA_CONTAINER_BASICQUEUE_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicQueue : public GAIA::Entity
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
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNIL;}
				GINL virtual _DataType& operator * (){GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index -= c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it operator + (const _SizeType& c) const
				{
					it ret = *this;
					ret += c;
					return ret;
				}
				GINL it operator - (const _SizeType& c) const
				{
					it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					return this->m_index - src.m_index;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNIL; m_index = 0;}
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
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNIL;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL const_it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index -= c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it operator + (const _SizeType& c) const
				{
					const_it ret = *this;
					ret += c;
					return ret;
				}
				GINL const_it operator - (const _SizeType& c) const
				{
					const_it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const const_it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					return this->m_index - src.m_index;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNIL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicQueue(){this->init();}
			GINL BasicQueue(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicQueue(){if(m_pData != GNIL) delete[] m_pData;}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL const _SizeType& size() const{return m_size;}
			GINL const _SizeType& capacity() const{return m_capacity;}
			GINL _SizeType count(const _DataType& t) const
			{
				if(this->empty())
					return 0;
				_SizeType ret = 0;
				GAIA::ALGO::count(this->const_front_it(), this->const_back_it(), t, ret);
				return ret;
			}
			GINL _DataType& front(){return this->operator[](0);}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& back(){return this->operator[](this->size() - 1);}
			GINL const _DataType& back() const{return this->operator[](this->size() - 1);}
			GINL GAIA::GVOID clear(){m_pBack = m_pFront = m_pData; m_size = 0;}
			GINL GAIA::GVOID destroy(){if(m_pData != GNIL){delete[] m_pData; m_pData = m_pFront = m_pBack = GNIL; m_capacity = m_size = 0;}}
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
				this->destroy();
				if(size != 0)
				{
					m_pData = new _DataType[size];
					m_pFront = m_pData;
					m_pBack = m_pData;
					m_capacity = size;
				}
			}
			GINL GAIA::GVOID push_back(const _DataType& t)
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
			GINL GAIA::BL pop_front()
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
			GINL it front_it()
			{
				it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNIL;
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
					ret.m_pContainer = GNIL;
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
					ret.m_pContainer = GNIL;
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
					ret.m_pContainer = GNIL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL const __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this);
				this->reserve(src.size());
				for(_SizeType x = 0; x < src.size(); ++x)
					this->push_back(src[x]);
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_AST(index >= 0 && index < this->size());
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
				GAIA_AST(index >= 0 && index < this->size());
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
			GINL __MyType& operator += (const __MyType& src)
			{
				if(this == &src)
				{
					if(!this->empty())
					{
						__MyType temp = *this;
						*this += temp;
						return *this;
					}
				}
				const_it it = src.const_front_it();
				for(; !it.empty(); ++it)
					this->push_back(*it);
				return *this;
			}
			GINL GAIA::BL operator == (const __MyType& src) const
			{
				if(this->size() == src.size())
				{
					const_it srcit = this->const_front_it();
					const_it dstit = src.const_front_it();
					for(;;)
					{
						if(srcit.empty() || dstit.empty())
							break;
						if(*srcit != *dstit)
							return GAIA::False;
						++srcit;
						++dstit;
					}
					return GAIA::True;
				}
				else
					return GAIA::False;
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(this->size() > src.size())
					return GAIA::True;
				else if(this->size() < src.size())
					return GAIA::False;
				else
				{
					const_it srcit = this->const_front_it();
					const_it dstit = src.const_front_it();
					for(;;)
					{
						if(srcit.empty() || dstit.empty())
							break;
						if(*srcit > *dstit)
							return GAIA::True;
						else if(*srcit < *dstit)
							return GAIA::False;
						++srcit;
						++dstit;
					}
					return GAIA::True;
				}
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(this->size() < src.size())
					return GAIA::True;
				else if(this->size() > src.size())
					return GAIA::False;
				else
				{
					const_it srcit = this->const_front_it();
					const_it dstit = src.const_front_it();
					for(;;)
					{
						if(srcit.empty() || dstit.empty())
							break;
						if(*srcit < *dstit)
							return GAIA::True;
						else if(*srcit > *dstit)
							return GAIA::False;
						++srcit;
						++dstit;
					}
					return GAIA::True;
				}
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const __MyType& src) const{return !this->operator >= (src);}
		private:
			GINL GAIA::GVOID init(){m_pData = m_pFront = m_pBack = GNIL; m_capacity = m_size = 0;}
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
