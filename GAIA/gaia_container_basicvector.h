#ifndef		__GAIA_CONTAINER_BASICVECTOR_H__
#define		__GAIA_CONTAINER_BASICVECTOR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicVector
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
				GINL virtual _DataType& operator * (){GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_AST(m_pContainer != GNULL); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_AST(m_pContainer != GNULL); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size())
						m_index = m_pContainer->size();
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index -= c;
					if(m_index < 0)
						m_index = 0;
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
				GINL it& operator = (const it& src){m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
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
				GINL virtual const _DataType& operator * () const{GAIA_AST(m_pContainer != GNULL); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(m_pContainer != GNULL); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(m_pContainer != GNULL); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL const_it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size())
						m_index = m_pContainer->size();
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index -= c;
					if(m_index < 0)
						m_index = 0;
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
				GINL const_it& operator = (const const_it& src){m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){--(*this); return *this;}
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
					return;
				this->destroy();
				m_capacity = size;
				m_size = 0;
				if(size != 0)
					m_pFront = new _DataType[size];
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
			GINL GAIA::GVOID pop_back()
			{
				GAIA_AST(this->size() > 0);
				if(m_size > 0)
					--m_size;
			}
			GINL GAIA::GVOID inverse(){GAIA::ALGORITHM::inverse(this->front_ptr(), this->back_ptr());}
			GINL GAIA::BL insert(const _SizeType& index, const _DataType& t)
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
			GINL _SizeType find(const _DataType& t) const
			{
				for(_SizeType x = 0; x < this->size(); ++x)
					if(this->operator[](x) == t)
						return x;
				return (_SizeType)GINVALID;
			}
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
				_DataType* pFinded = GAIA::ALGORITHM::search(this->front_ptr(), this->back_ptr(), t);
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
					iter.m_pContainer = this;
					iter.m_index = p - this->front_ptr();
				}
				return iter;
			}
			GINL const_it lower_bound(const _DataType& t) const
			{
				const_it iter;
				if(!this->empty())
				{
					_DataType* p = GAIA::ALGORITHM::lower_bound(this->front_ptr(), this->back_ptr(), t);
					iter.m_pContainer = this;
					iter.m_index = p - this->front_ptr();
				}
				return iter;
			}
			GINL it upper_bound(const _DataType& t)
			{
				it iter;
				if(!this->empty())
				{
					_DataType* p = GAIA::ALGORITHM::upper_bound(this->front_ptr(), this->back_ptr(), t);
					iter.m_pContainer = this;
					iter.m_index = p - this->front_ptr();
				}
				return iter;
			}
			GINL const_it upper_bound(const _DataType& t) const
			{
				const_it iter;
				if(!this->empty())
				{
					_DataType* p = GAIA::ALGORITHM::upper_bound(this->front_ptr(), this->back_ptr(), t);
					iter.m_pContainer = this;
					iter.m_index = p - this->front_ptr();
				}
				return iter;
			}
			GINL const _DataType& operator[](const _SizeType& index) const{GAIA_AST(index >= 0 && index < this->size()); return m_pFront[index];}
			GINL _DataType& operator[](const _SizeType& index){GAIA_AST(index >= 0 && index < this->size()); return m_pFront[index];}
			GINL __MyType& operator = (const __MyType& src)
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
