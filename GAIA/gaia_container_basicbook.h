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
			GINL GAIA::BL empty() const{return m_usedlist.empty();}
			GINL _SizeType size() const{return m_usedlist.size();}
			GINL _SizeType capacity() const{return m_fixedlist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(m_fixedlist.size() == size)
					return;
				m_fixedlist.reserve(size);
				m_freestack.reserve(size);
				m_usedlist.reserve(size);
			}
			GINL GAIA::GVOID clear()
			{
				m_pool.clear();
				m_fixedlist.clear();
				m_freestack.clear();
				m_usedlist.clear();
			}
			GINL GAIA::GVOID destroy()
			{
				m_pool.destroy();
				m_fixedlist.destroy();
				m_freestack.destroy();
				m_usedlist.destroy();
			}
			GINL _SizeType set(const _DataType& t)
			{
				UsedNode* p = m_pool.alloc();
				FixedNode n;
				n.t = t;
				n.p = p;
				if(m_freestack.empty())
				{
					m_fixedlist.push_back(n);
					p->fi = m_fixedlist.size() - 1;
				}
				else
				{
					p->fi = m_freestack.back();
					m_fixedlist[p->fi] = n;
					m_freestack.pop_back();
				}
				m_usedlist.push_back(p);
				p->ui = m_usedlist.size() - 1;
				return p->ui;
			}
			GINL GAIA::BL erase(const _SizeType& usedindex)
			{
				GAIA_AST(usedindex >= 0 && usedindex < m_usedlist.size());
				if(usedindex < 0)
					return GAIA::False;
				if(usedindex >= m_usedlist.size())
					return GAIA::False;
				_SizeType fixedindex = this->fixedindex(usedindex);
				GAIA_AST(fixedindex >= 0 && fixedindex < m_fixedlist.size());
				if(fixedindex < 0)
					return GAIA::False;
				if(fixedindex >= m_fixedlist.size())
					return GAIA::False;
				FixedNode& n = m_fixedlist[fixedindex];
				GAIA_AST(n.p != GNIL);
				m_freestack.push_back(n.p->fi);
				if(usedindex + 1 != m_usedlist.size())
				{
					m_usedlist.back()->ui = usedindex;
					m_usedlist[usedindex] = m_usedlist.back();
				}
				m_usedlist.resize(m_usedlist.size() - 1);
				m_pool.release(n.p);
				n.p = GNIL;
				return GAIA::True;
			}
			GINL _SizeType usedindex(const _SizeType& fixedindex) const
			{
				UsedNode* p = m_fixedlist[fixedindex].p;
				if(p == GNIL)
					return GINVALID;
				GAIA_AST(p->ui < m_usedlist.size());
				return p->ui;
			}
			GINL _SizeType fixedindex(const _SizeType& usedindex) const
			{
				UsedNode* p = m_usedlist[usedindex];
				GAIA_AST(p != GNIL);
				if(p == GNIL)
					return GINVALID;
				GAIA_AST(p->fi < m_fixedlist.size());
				return p->fi;
			}
			GINL const _DataType& operator[](const _SizeType& usedindex) const
			{
				_SizeType fixedindex = this->fixedindex(usedindex);
				GAIA_AST(fixedindex != GINVALID);
				return m_fixedlist[fixedindex].t;
			}
			GINL _DataType& operator[](const _SizeType& usedindex)
			{
				_SizeType fixedindex = this->fixedindex(usedindex);
				GAIA_AST(fixedindex != GINVALID);
				return m_fixedlist[fixedindex].t;
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				m_fixedlist = src.m_fixedlist;
				m_freestack = src.m_freestack;
				m_usedlist = src.m_usedlist;
				for(_SizeType x = 0; x < m_usedlist.size(); ++x)
				{
					UsedNode* p = m_usedlist[x];
					GAIA_AST(p != GNIL);
					UsedNode* pNew = m_pool.alloc();
					*pNew = *p;
					m_usedlist[x] = pNew;
					m_fixedlist[pNew->fi].p = pNew;
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
			class UsedNode : public GAIA::Base
			{
			public:
				_SizeType fi; // Fixed index.
				_SizeType ui; // Used index.
			};
			class FixedNode : public GAIA::Base
			{
			public:
				_DataType t;
				UsedNode* p;
			};
		private:
			typedef GAIA::CTN::BasicPool<UsedNode, _SizeType, _SizeIncreaserType> __PoolType; // UsedNode pool.
			typedef GAIA::CTN::BasicVector<FixedNode, _SizeType, _SizeIncreaserType> __FixedListType;
			typedef GAIA::CTN::BasicStack<_SizeType, _SizeType, _SizeIncreaserType> __FreeStackType; // Fixed list free stack.
			typedef GAIA::CTN::BasicVector<UsedNode*, _SizeType, _SizeIncreaserType> __UsedListType;
		private:
			GINL GAIA::GVOID init(){}
		private:
			__PoolType m_pool;
			__FixedListType m_fixedlist;
			__FreeStackType m_freestack;
			__UsedListType m_usedlist;
		};
	};
};

#endif
