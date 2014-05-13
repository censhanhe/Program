#ifndef		__GAIA_CONTAINER_BASICSTACKSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACKSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicStackStack : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicStackStack<_DataType, _SizeType, _Size> __MyType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicStackStack;
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
				friend class BasicStackStack;
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
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicStackStack(){this->init();}
			GINL BasicStackStack(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicStackStack(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL const _SizeType& size() const{return m_size;}
			GINL _SizeType capacity() const{return _Size;}
			GINL GAIA::BL resize(const _SizeType& size)
			{
				GAIA_AST(size >= 0 && size <= this->capacity());
				if(size >= 0 && size <= this->capacity())
				{
					m_size = size;
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL _SizeType count(const _DataType& t) const{_SizeType ret = 0; GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, ret); return ret;}
			GINL GAIA::BL push_back(const _DataType& t)
			{
				if(this->size() < this->capacity()) 
				{
					m_data[m_size] = t; 
					++m_size;
					return GAIA::True;
				}
				else
					return GAIA::False;
			}
			GINL GAIA::BL pop_back()
			{
				if(m_size > 0)
				{
					--m_size;
					return GAIA::True;
				}
				else
					return GAIA::False;
			}
			GINL _DataType& front(){return this->operator[](0);}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& back(){return this->operator[](this->size() - 1);}
			GINL const _DataType& back() const{return this->operator[](this->size() - 1);}
			GINL _DataType* front_ptr(){return m_data;}
			GINL const _DataType* front_ptr() const{return m_data;}
			GINL _DataType* back_ptr(){return &m_data[m_size - 1];}
			GINL const _DataType* back_ptr() const{return &m_data[m_size - 1];}
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
				GAIA_AST(&src != this); 
				this->clear();
				if(!src.empty())
				{
					GAIA::ALGORITHM::copy(m_data, src.m_data, src.size());
					m_size = src.size();
				}
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index){return m_data[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return m_data[index];}
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
				while(!it.empty())
				{
					this->push_back(*it);
					++it;
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
		private:
			GINL GAIA::GVOID init(){m_size = 0;}
		private:
			_DataType m_data[_Size];
			_SizeType m_size;
		};
	};
};

#endif
