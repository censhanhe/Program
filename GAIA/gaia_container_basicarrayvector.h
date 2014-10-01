#ifndef		__GAIA_CONTAINER_BASICARRAYVECTOR_H__
#define		__GAIA_CONTAINER_BASICARRAYVECTOR_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _Size> class BasicArrayVector : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicArrayVector<_DataType, _SizeType, _SizeIncreaserType, _Size> __MyType;
			typedef GAIA::CTN::BasicArray<_DataType, _SizeType, _Size> __ArrayType;
			typedef GAIA::CTN::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __VectorType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicArrayVector;
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
				friend class BasicArrayVector;
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
			GINL BasicArrayVector(){}
			GINL BasicArrayVector(const __MyType& src){this->operator = (src);}
			GINL ~BasicArrayVector(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL const _SizeType& size() const
			{
				if(m_vec.capacity() != 0)
					return m_vec.size();
				else
					return m_arr.size();
			}
			GINL _SizeType capacity() const{return GAIA::ALGO::maximize(m_vec.capacity(), m_arr.capacity());}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				if(size > m_arr.capacity())
				{
					m_arr.clear();
					m_vec.resize(size);
				}
				else
				{
					m_vec.clear();
					m_arr.resize(size);
				}
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(size > m_arr.capacity())
				{
					m_arr.clear();
					m_vec.reserve(size);
				}
				else
				{
					m_vec.destroy();
					m_arr.clear();
				}
			}
			GINL GAIA::GVOID clear(){m_arr.clear(); m_vec.clear();}
			GINL GAIA::GVOID destroy(){m_arr.clear(); m_vec.destroy();}
			GINL GAIA::GVOID push_back(const _DataType& t)
			{
				if(m_vec.capacity() != 0)
				{
					if(m_vec.size() == m_vec.capacity())
					{
						if(m_vec.size() >= m_arr.capacity())
							m_vec.push_back(t);
						else
						{
							m_arr.clear();
							for(_SizeType x = 0; x < m_vec.size(); ++x)
								m_arr.push_back(m_vec[x]);
							m_vec.destroy();
							m_arr.push_back(t);
						}
					}
					else
						m_vec.push_back(t);
				}
				else
				{
					if(m_arr.size() == m_arr.capacity())
					{
						m_vec.reserve(m_arr.size() + 1);
						for(_SizeType x = 0; x < m_arr.size(); ++x)
							m_vec.push_back(m_arr[x]);
						m_arr.clear();
						m_vec.push_back(t);
					}
					else
						m_arr.push_back(t);
				}
			}
			GINL GAIA::GVOID push_back(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(p != GNIL);
				GAIA_AST(size > 0);
				if(m_vec.capacity() != 0)
				{
					if(m_vec.capacity() - m_vec.size() < size)
					{
						if(m_vec.size() + size > m_arr.capacity())
							m_vec.push_back(p, size);
						else
						{
							m_arr.clear();
							for(_SizeType x = 0; x < m_vec.size(); ++x)
								m_arr.push_back(m_vec[x]);
							m_vec.destroy();
							m_arr.push_back(p, size);
						}
					}
					else
						m_vec.push_back(p, size);
				}
				else
				{
					if(m_arr.size() + size > m_arr.capacity())
					{
						m_vec.reserve(m_arr.size() + size);
						for(_SizeType x = 0; x < m_arr.size(); ++x)
							m_vec.push_back(m_arr[x]);
						m_arr.clear();
						m_vec.push_back(p, size);
					}
					else
						m_arr.push_back(p, size);
				}
			}
			GINL GAIA::BL pop_back()
			{
				if(m_vec.size() != 0)
					m_vec.pop_back();
				else
				{
					if(m_arr.empty())
						return GAIA::False;
					m_arr.pop_back();
				}
				return GAIA::True;
			}
			GINL GAIA::BL pop_back(_DataType* p, const _SizeType& size)
			{
				if(m_vec.capacity() != 0)
					return m_vec.pop_back(p, size);
				else
					return m_arr.pop_back(p, size);
			}
			GINL GAIA::GVOID inverse()
			{
				if(m_vec.size() > 1)
					m_vec.inverse();
				else if(m_arr.size() > 1)
					m_arr.inverse();
			}
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index)
			{
				if(m_vec.capacity() != 0)
				{
					if(m_vec.size() == m_vec.capacity())
					{
						if(m_vec.size() >= m_arr.capacity())
							return m_vec.insert(t, index);
						else
						{
							m_arr.clear();
							for(_SizeType x = 0; x < m_vec.size(); ++x)
								m_arr.push_back(m_vec[x]);
							m_vec.destroy();
							return m_arr.insert(t, index);
						}
					}
					else
						return m_vec.insert(t, index);
				}
				else
				{
					if(m_arr.size() == m_arr.capacity())
					{
						m_vec.reserve(m_arr.size() + 1);
						for(_SizeType x = 0; x < m_arr.size(); ++x)
							m_vec.push_back(m_arr[x]);
						m_arr.clear();
						return m_vec.insert(t, index);
					}
					else
						m_arr.push_back(t);
				}
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
				if(m_vec.capacity() != 0)
					return m_vec.erase(index);
				else
					return m_arr.erase(index);
			}
			GINL _SizeType find(const _DataType& t, const _SizeType& index) const
			{
				if(m_vec.capacity() != 0)
					return m_vec.find(t, index);
				else
					return m_arr.find(t, index);
			}
			GINL _SizeType rfind(const _DataType& t, const _SizeType& index) const
			{
				if(m_vec.capacity() != 0)
					return m_vec.rfind(t, index);
				else
					return m_arr.rfind(t, index);
			}
			GINL GAIA::GVOID reset(const _DataType& t)
			{
				if(m_vec.capacity() != 0)
					m_vec.reset(t);
				else
					m_arr.reset(t);
			}
			GINL _SizeType count(const _DataType& t) const
			{
				if(m_vec.capacity() != 0)
					return m_vec.count(t);
				else
					return m_arr.count(t);
			}
			GINL GAIA::GVOID sort()
			{
				if(m_vec.capacity() != 0)
					return m_vec.sort();
				else
					return m_arr.sort();
			}
			GINL _SizeType unique()
			{
				if(m_vec.capacity() != 0)
					return m_vec.unique();
				else
					return m_vec.unique_noorder();
			}
			GINL _SizeType unique_noorder()
			{
				if(m_vec.capacity() != 0)
					return m_vec.unique_noorder();
				else
					return m_arr.unique_noorder();
			}
			GINL _SizeType search(const _DataType& t) const
			{
				if(m_vec.capacity() != 0)
					return m_vec.search(t);
				else
					return m_arr.search(t);
			}
			GINL GAIA::GVOID swap(const _SizeType& index1, const _SizeType& index2)
			{
				if(m_vec.capacity() != 0)
					m_vec.swap(index1, index2);
				else
					m_arr.swap(index1, index2);
			}
			GINL it lower_bound(const _DataType& t)
			{
				it ret;
				if(m_vec.capacity() != 0)
				{
					typename __VectorType::it ittemp = m_vec.lower_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_vec.front_it();
				}
				else
				{
					typename __ArrayType::it ittemp = m_arr.lower_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_arr.front_it();
				}
				return ret;
			}
			GINL const_it lower_bound(const _DataType& t) const
			{
				const_it ret;
				if(m_vec.capacity() != 0)
				{
					typename __VectorType::const_it ittemp = m_vec.lower_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_vec.const_front_it();
				}
				else
				{
					typename __ArrayType::const_it ittemp = m_arr.lower_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_arr.const_front_it();
				}
				return ret;
			}
			GINL it upper_bound(const _DataType& t)
			{
				it ret;
				if(m_vec.capacity() != 0)
				{
					typename __VectorType::it ittemp = m_vec.upper_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_vec.front_it();
				}
				else
				{
					typename __ArrayType::it ittemp = m_arr.upper_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_arr.front_it();
				}
				return ret;
			}
			GINL const_it upper_bound(const _DataType& t) const
			{
				const_it ret;
				if(m_vec.capacity() != 0)
				{
					typename __VectorType::const_it ittemp = m_vec.upper_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_vec.const_front_it();
				}
				else
				{
					typename __ArrayType::const_it ittemp = m_arr.upper_bound(t);
					ret.m_pContainer = this;
					ret.m_index = ittemp - m_arr.const_front_it();
				}
				return ret;
			}
			GINL __MyType& operator += (const __MyType& src)
			{
				for(_SizeType x = 0; x < src.size(); ++x)
					this->push_back(src[x]);
				return *this;
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				if(m_vec.capacity() != 0)
					return m_vec[index];
				else
					return m_arr[index];
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				if(m_vec.capacity() != 0)
					return m_vec[index];
				else
					return m_arr[index];
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this);
				m_arr = src.m_arr;
				m_vec = src.m_vec;
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
			GINL GAIA::BL operator > (const __MyType& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const __MyType& src) const{return !this->operator >= (src);}
			GINL _DataType& front(){return *this->front_ptr();}
			GINL const _DataType& front() const{return *this->front_ptr();}
			GINL _DataType& back(){return *this->back_ptr();}
			GINL const _DataType& back() const{return *this->back_ptr();}
			GINL _DataType* front_ptr()
			{
				GAIA_AST(this->size() > 0);
				return &(*this)[0];
			}
			GINL const _DataType* front_ptr() const
			{
				GAIA_AST(this->size() > 0);
				return &(*this)[0];
			}
			GINL _DataType* back_ptr()
			{
				GAIA_AST(this->size() > 0);
				return &(*this)[this->size() - 1];
			}
			GINL const _DataType* back_ptr() const
			{
				GAIA_AST(this->size() > 0);
				return &(*this)[this->size() - 1];
			}
			GINL it front_it()
			{
				it ret;
				if(!this->empty())
				{
					ret.m_pContainer = this;
					ret.m_index = 0;
				}
				return ret;
			}
			GINL it back_it()
			{
				it ret;
				if(!this->empty())
				{
					ret.m_pContainer = this;
					ret.m_index = this->size() - 1;
				}
				return ret;
			}
			GINL const_it const_front_it() const
			{
				const_it ret;
				if(!this->empty())
				{
					ret.m_pContainer = this;
					ret.m_index = 0;
				}
				return ret;
			}
			GINL const_it const_back_it() const
			{
				const_it ret;
				if(!this->empty())
				{
					ret.m_pContainer = this;
					ret.m_index = this->size() - 1;
				}
				return ret;
			}
		private:
			__ArrayType m_arr;
			__VectorType m_vec;
		};
	};
};

#endif
