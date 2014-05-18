#ifndef		__GAIA_CONTAINER_BASICVECTOR_H__
#define		__GAIA_CONTAINER_BASICVECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicVector : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicVector<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicVector;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
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
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
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
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				__MyType* m_pContainer;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicVector;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL const_it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
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
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicVector(){this->init();}
			GINL BasicVector(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicVector(){if(m_pFront != GNULL) delete[] m_pFront;}
			GINL const _SizeType& size() const{return m_size;}
			GINL const _SizeType& capacity() const{return m_capacity;}
			GINL GAIA::BL empty() const{return this->size() == 0;}
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
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(this->capacity() == size)
				{
					this->clear();
					return;
				}
				this->destroy();
				if(size > 0)
				{
					m_pFront = new _DataType[size];
					m_capacity = size;
				}
			}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL GAIA::GVOID destroy()
			{
				if(m_pFront != GNULL)
				{
					delete[] m_pFront;
					m_pFront = GNULL;
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
			GINL GAIA::GVOID push_back(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				_SizeType newsize = this->size() + size;
				if(newsize > this->capacity())
				{
					_DataType* pTemp = new _datatype[newsize];
					if(m_pFront != GNULL)
					{
						for(_SizeType c = 0; c < this->size(); ++c)
							pTemp[c] = m_pFront[c];
						delete[] m_pFront;
					}
					m_pFront = pTemp;
					m_capacity = newsize;
				}
				for(_SizeType x = 0; x < size; ++x)
					m_pFront[m_size++] = p[x];
			}
			GINL GAIA::BL pop_back()
			{
				GAIA_AST(this->size() > 0);
				if(this->size() > 0)
				{
					m_size--;
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL pop_back(_DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				if(size > this->size())
					return GAIA::False;
				for(_SizeType x = 0; x < size; ++x)
					p[x] = m_pFront[this->size() - size + x];
				m_size -= size;
				return GAIA::True;
			}
			GINL GAIA::GVOID inverse(){if(this->size() > 1) GAIA::ALGORITHM::inverse(this->front_ptr(), this->back_ptr());}
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index)
			{
				GAIA_AST(index >= 0 && index <= this->size());
				if(index > this->size())
					return GAIA::False;
				this->push_back(t);
				if(this->size() == 1)
					return GAIA::True;
				GAIA::ALGORITHM::move_next(this->back_ptr(), this->front_ptr() + this->size() - 2, this->size() - index);
				this->operator[](index) = t;
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
				GAIA_AST(index >= 0 && index < this->size());
				if(index >= this->size())
					return GAIA::False;
				if(index != this->size() - 1)
					GAIA::ALGORITHM::move_prev(this->front_ptr() + index, this->front_ptr() + index + 1, this->size() - 1 - index);
				--m_size;
				return GAIA::True;
			}
			GINL _SizeType find(const _DataType& t, const _SizeType& index) const
			{
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::find(this->front_ptr() + index, this->back_ptr(), t);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const _DataType& t, const _SizeType& index) const
			{
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::rfind(this->front_ptr(), this->front_ptr() + index, t);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL GAIA::GVOID reset(const _DataType& t){for(_SizeType x = 0; x < this->size(); ++x) m_pFront[x] = t;}
			GINL _SizeType count(const _DataType& t) const
			{
				if(this->empty())
					return 0;
				_SizeType ret = 0;
				GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, ret);
				return ret;
			}
			GINL GAIA::GVOID sort(){if(this->empty()) return; GAIA::ALGORITHM::sort(this->front_ptr(), this->back_ptr());}
			GINL _SizeType unique()
			{
				if(this->empty())
					return 0;
				_DataType* p = GAIA::ALGORITHM::unique_order(this->front_ptr(), this->back_ptr());
				_SizeType newsize = static_cast<_SizeType>(p - this->front_ptr()) + 1;
				_SizeType ret = m_size - newsize;
				m_size = newsize;
				return ret;
			}
			GINL _SizeType unique_noorder()
			{
				if(this->empty())
					return 0;
				_DataType* p = GAIA::ALGORITHM::unique_noorder(this->front_ptr(), this->back_ptr());
				_SizeType newsize = static_cast<_SizeType>(p - this->front_ptr()) + 1;
				_SizeType ret = m_size - newsize;
				m_size = newsize;
				return ret;
			}
			GINL _SizeType search(const _DataType& t) const
			{
				if(this->size() <= 0)
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::search(this->front_ptr(), this->back_ptr(), t);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return (_SizeType)(pFinded - this->front_ptr());
			}
			GINL GAIA::GVOID swap(const _SizeType& index1, const _SizeType& index2){GAIA::ALGORITHM::swap(this->operator[](index1), this->operator[](index2));}
			GINL it lower_bound(const _DataType& t)
			{
				it iter;
				if(!this->empty())
				{
					_DataType* p = GAIA::ALGORITHM::lower_bound(this->front_ptr(), this->back_ptr(), t);
					if(p != GNULL)
					{
						iter.m_pContainer = this;
						iter.m_index = (_SizeType)(p - this->front_ptr());
					}
				}
				return iter;
			}
			GINL const_it lower_bound(const _DataType& t) const
			{
				const_it iter;
				if(!this->empty())
				{
					const _DataType* p = GAIA::ALGORITHM::lower_bound(this->front_ptr(), this->back_ptr(), t);
					if(p != GNULL)
					{
						iter.m_pContainer = this;
						iter.m_index = (_SizeType)(p - this->front_ptr());
					}
				}
				return iter;
			}
			GINL it upper_bound(const _DataType& t)
			{
				it iter;
				if(!this->empty())
				{
					_DataType* p = GAIA::ALGORITHM::upper_bound(this->front_ptr(), this->back_ptr(), t);
					if(p != GNULL)
					{
						iter.m_pContainer = this;
						iter.m_index = (_SizeType)(p - this->front_ptr());
					}
				}
				return iter;
			}
			GINL const_it upper_bound(const _DataType& t) const
			{
				const_it iter;
				if(!this->empty())
				{
					const _DataType* p = GAIA::ALGORITHM::upper_bound(this->front_ptr(), this->back_ptr(), t);
					if(p != GNULL)
					{
						iter.m_pContainer = this;
						iter.m_index = (_SizeType)(p - this->front_ptr());
					}
				}
				return iter;
			}
			GINL __MyType& operator += (const __MyType& src)
			{
				if(!src.empty())
				{
					if(this == &src)
					{
						__MyType temp = *this;
						this->reserve(this->capacity() * 2);
						this->push_back(temp.front_ptr(), temp.size());
						this->push_back(temp.front_ptr(), temp.size());
						return *this;
					}
					this->push_back(src.front_ptr(), src.size());
				}
				return *this;
			}
			GINL const _DataType& operator[](const _SizeType& index) const{GAIA_AST(index >= 0 && index < this->size()); return m_pFront[index];}
			GINL _DataType& operator[](const _SizeType& index){GAIA_AST(index >= 0 && index < this->size()); return m_pFront[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this); 
				this->reserve(src.size());
				if(src.size() > 0)
				{
					GAIA::ALGORITHM::copy(m_pFront, src.m_pFront, src.size());
					m_size = src.size();
				}
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
			GINL GAIA::BL operator != (const __MyType& src) const{return !(this->operator == (src));}
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
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
			GINL _DataType& front(){return this->operator[](0);}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& back(){return this->operator[](this->size() - 1);}
			GINL const _DataType& back() const{return this->operator[](this->size() - 1);}
			GINL _DataType* front_ptr(){return &this->operator[](0);}
			GINL const _DataType* front_ptr() const{return &this->operator[](0);}
			GINL _DataType* back_ptr(){return &this->operator[](this->size() - 1);}
			GINL const _DataType* back_ptr() const{return &this->operator[](this->size() - 1);}
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