#ifndef 	__GAIA_CONTAINER_BASICBOOK_H__
#define 	__GAIA_CONTAINER_BASICBOOK_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicBook : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicBook<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicBook;
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
				friend class BasicBook;
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
			GINL BasicBook(){this->init();}
			GINL ~BasicBook(){}
			GINL GAIA::BL empty() const{return m_uselist.empty();}
			GINL _SizeType size() const{return m_uselist.size();}
			GINL _SizeType capacity() const{return m_fixedlist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(m_fixedlist.size() == size)
					return;
				m_fixedlist.reserve(size);
				m_freestack.reserve(size);
				m_uselist.reserve(size);
			}
			GINL GAIA::GVOID clear()
			{
				m_fixedlist.clear();
				m_freestack.clear();
				m_uselist.clear();
			}
			GINL GAIA::GVOID destroy()
			{
				m_fixedlist.destroy();
				m_freestack.destroy();
				m_uselist.destroy();
			}
			GINL _SizeType set(const _DataType& t)
			{
				Node n;
				if(m_freestack.empty())
				{
					m_fixedlist.push_back(n);
					n.fixedindex = m_fixedlist.size() - 1;
				}
				else
				{
					n.fixedindex = m_freestack.back()
					m_freestack.pop_back();
				}
				Node& nref = m_fixedlist[n.fixedindex];
				nref.t = t;
				m_uselist.push_back(nref.fixedindex);
				nref.useindex = m_uselist.size() - 1;
				return nref.useindex;
			}
			GINL GAIA::BL erase(const _SizeType& useindex)
			{
				GAIA_AST(useindex >= 0 && useindex < m_uselist.size());
				if(useindex < 0)
					return GAIA::False;
				if(useindex >= m_uselist.size())
					return GAIA::False;
				_SizeType fixedindex = m_uselist[useindex];
				GAIA_AST(fixedindex >= 0 && fixedindex < m_fixedlist.size());
				if(fixedindex < 0)
					return GAIA::False;
				if(fixedindex >= m_fixedlist.size())
					return GAIA::False;
				Node& nref = m_fixedlist[fixedindex];
				GAIA_AST(nref.fixedindex != GINVALID);
				GAIA_AST(nref.useindex != GINVALID);
				nref.fixedindex = GINVALID;
				nref.useindex = GINVALID;
				m_freestack.push_back(fixedindex);
				if(useindex + 1 != m_uselist.size())
					m_uselist[useindex] = m_uselist.back();
				m_uselist.resize(m_uselist.size() - 1);
				return GAIA::True;
			}
			GINL _SizeType useindex(const _SizeType& fixedindex) const{return m_fixedlist[fixedindex].useindex;}
			GINL _SizeType fixedindex(const _SizeType& useindex) const{return m_uselist[useindex];}
			GINL const _DataType& operator[](const _SizeType& useindex) const{return m_fixedlist[m_uselist[useindex]].t;}
			GINL __MyType& operator = (const __MyType& src)
			{
				m_fixedlist = src.m_fixedlist;
				m_freestack = src.m_freestack;
				m_uselist = src.m_uselist;
				return *this;
			}
			GINL GAIA::BL operator == (const __MyType& src)
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
		private:
			class Node : public GAIA::Base
			{
			public:
				_DataType t;
				_SizeType fixedindex;
				_SizeType useindex;
			};
		private:
			typedef GAIA::CTN::BasicVector<Node, _SizeType, _SizeIncreaserType> __ListType;
			typedef GAIA::CTN::BasicStack<_SizeType, _SizeType, _SizeIncreaserType> __FreeStackType;
			typedef GAIA::CTN::BasicVector<_SizeType, _SizeType, _SizeIncreaserType> __UseListType;
		private:
			GINL GAIA::GVOID init(){}
		private:
			__ListType m_fixedlist;
			__FreeStackType m_freestack;
			__UseListType m_uselist;
		};
	};
};

#endif
