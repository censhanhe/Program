#ifndef		__GAIA_CONTAINER_BASICTREE_H__
#define		__GAIA_CONTAINER_BASICTREE_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicTree : public GAIA::Entity
		{
		public:
			class Node;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			class Node
			{
			private:
				friend class BasicTree;
				friend class it;
				friend class const_it;
			public:
			#ifdef GAIA_DEBUG_INTERNALROUTINE
				Node(){m_pParent = GNIL;}
				GINL _DataType& operator * (){return m_t;}
				GINL const _DataType& operator * () const{return m_t;}
			#endif
			private:
				_DataType m_t;
				Node* m_pParent;
				__NodeListType m_links;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicTree<_DataType, _SizeType, _SizeIncreaserType> __MyType;
			typedef BasicVector<__NodeListType, _SizeType, _SizeIncreaserType> __PathListType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType> __PoolType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicTree;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNIL;}
				GINL virtual _DataType& operator * (){return **m_pNode;}
				GINL virtual const _DataType& operator * () const{return **m_pNode;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNIL)
						return *this;
					if(m_pNode->m_links.empty())
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNIL)
						{
							m_pNode = GNIL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(m_pNode, 0);
						GAIA_AST(index != GINVALID);
						for(_SizeType x = index + 1; x < m_pNode->m_pParent->m_links.size(); ++x)
						{
							if(m_pNode->m_pParent->m_links[x] != GNIL)
							{
								m_pNode = m_pNode->m_pParent->m_links[x];
								return *this;
							}
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						typename __NodeListType::it it = m_pNode->m_links.front_it();
						for(; !it.empty(); ++it)
						{
							if(*it != GNIL)
							{
								m_pNode = *it;
								return *this;
							}
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNIL)
						return *this;
					if(m_pNode->m_pParent == GNIL)
					{
						m_pNode = GNIL;
						return *this;
					}
					_SizeType index = m_pNode->m_pParent->m_links.find(const_cast<Node* const>(m_pNode), 0);
					GAIA_AST(index != GINVALID);
					if(index > 0)
					{
						_SizeType x = index - 1;
						for(;;)
						{
							if(m_pNode->m_pParent->m_links[x] != GNIL)
							{
								m_pNode = m_pNode->m_pParent->m_links[x];
							NEXT_LOOP:
								while(!m_pNode->m_links.empty())
								{
									typename __NodeListType::it it = m_pNode->m_links.back_it();
									for(; !it.empty(); --it)
									{
										if(*it != GNIL)
										{
											m_pNode = *it;
											goto NEXT_LOOP;
										}
									}
								}
								return *this;
							}
							if(x == 0)
								break;
							--x;
						}
					}
					m_pNode = m_pNode->m_pParent;
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){GAIA_AST(&src != this); m_pNode = src.m_pNode; return *this;}
				GINL it& operator += (_SizeType c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL it& operator -= (_SizeType c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						++c;
					}
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
					it iter = *this;
					_SizeType ret = 0;
					for(; !iter.empty(); --iter)
					{
						if(iter == src)
							return ret;
						++ret;
					}
					iter = *this;
					ret = 0;
					for(; !iter.empty(); ++iter)
					{
						if(iter == src)
							return ret;
						--ret;
					}
					return ret;
				}
				GINL GAIA::BL operator == (const it& src) const{return m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const it& src) const{return !this->operator == (src);}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNIL;}
			private:
				Node* m_pNode;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicTree;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNIL;}
				GINL virtual const _DataType& operator * () const{return **m_pNode;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNIL)
						return *this;
					if(m_pNode->m_links.empty())
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNIL)
						{
							m_pNode = GNIL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(const_cast<Node* const>(m_pNode), 0);
						GAIA_AST(index != GINVALID);
						for(_SizeType x = index + 1; x < m_pNode->m_pParent->m_links.size(); ++x)
						{
							if(m_pNode->m_pParent->m_links[x] != GNIL)
							{
								m_pNode = m_pNode->m_pParent->m_links[x];
								return *this;
							}
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						typename __NodeListType::const_it it = m_pNode->m_links.const_front_it();
						for(; !it.empty(); ++it)
						{
							if(*it != GNIL)
							{
								m_pNode = *it;
								return *this;
							}
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNIL)
						return *this;
					if(m_pNode->m_pParent == GNIL)
					{
						m_pNode = GNIL;
						return *this;
					}
					_SizeType index = m_pNode->m_pParent->m_links.find(const_cast<Node* const>(m_pNode), 0);
					GAIA_AST(index != GINVALID);
					if(index > 0)
					{
						_SizeType x = index - 1;
						for(;;)
						{
							if(m_pNode->m_pParent->m_links[x] != GNIL)
							{
								m_pNode = m_pNode->m_pParent->m_links[x];
							NEXT_LOOP:
								while(!m_pNode->m_links.empty())
								{
									typename __NodeListType::const_it it = m_pNode->m_links.const_back_it();
									for(; !it.empty(); --it)
									{
										if(*it != GNIL)
										{
											m_pNode = *it;
											goto NEXT_LOOP;
										}
									}
								}
								return *this;
							}
							if(x == 0)
								break;
							--x;
						}
					}
					m_pNode = m_pNode->m_pParent;
					return *this;
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_pNode = src.m_pNode; return *this;}
				GINL const_it& operator += (_SizeType c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL const_it& operator -= (_SizeType c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						++c;
					}
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
					const_it iter = *this;
					_SizeType ret = 0;
					for(; !iter.empty(); --iter)
					{
						if(iter == src)
							return ret;
						++ret;
					}
					iter = *this;
					ret = 0;
					for(; !iter.empty(); ++iter)
					{
						if(iter == src)
							return ret;
						--ret;
					}
					return ret;
				}
				GINL GAIA::BL operator == (const const_it& src) const{return m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const const_it& src) const{return !this->operator == (src);}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNIL;}
			private:
				const Node* m_pNode;
			};
		public:
			GINL BasicTree(){this->init();}
			GINL BasicTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTree(){}
			GINL GAIA::BL empty() const{return m_pRoot == GNIL;}
			GINL _SizeType size() const{return m_pool.size();}
			GINL const _SizeType& capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNIL; m_pool.destroy();}
			GINL GAIA::GVOID clear(){m_pRoot = GNIL; m_pool.clear();}
			GINL GAIA::GVOID resize(const _SizeType& size){}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL Node* root(){return m_pRoot;}
			GINL const Node* root() const{return m_pRoot;}
			GINL Node* parent(Node* p){if(p != GNIL) return p->m_pParent; return GNIL;}
			GINL const Node* parent(Node* p) const{if(p != GNIL) return p->m_pParent; return GNIL;}
			GINL Node* insert(const _DataType& t, Node* pNode)
			{
				if(pNode == GNIL && m_pRoot != GNIL)
					return GNIL;
				Node* pNew = m_pool.alloc();
				pNew->m_t = t;
				pNew->m_pParent = GNIL;
				pNew->m_links.clear();
				if(pNode == GNIL)
					m_pRoot = pNew;
				else
				{
					GAIA_AST(!!m_pRoot);
					this->link(*pNode, *pNew);
				}
				return pNew;
			}
			GINL GAIA::GVOID erase(Node& n)
			{
				for(_SizeType x = 0; x < n.m_links.size(); ++x)
				{
					Node* pNode = n.m_links[x];
					if(pNode == GNIL)
						continue;
					this->erase(*pNode);
				}
				if(n.m_pParent != GNIL)
					this->unlink(*n.m_pParent, n);
				m_pool.release(&n);
				if(&n == m_pRoot)
					m_pRoot = GNIL;
			}
			GINL GAIA::BL link(Node& parent, Node& child)
			{
				if(child.m_pParent != GNIL)
					this->unlink(*child.m_pParent, child);
				Node** ppn;
				if(!parent.m_links.empty())
					ppn = GAIA::ALGO::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), (Node*)GNIL);
				else
					ppn = GNIL;
				if(ppn == GNIL)
					parent.m_links.push_back(&child);
				else
					*ppn = &child;
				child.m_pParent = &parent;
				return GAIA::True;
			}
			GINL GAIA::BL unlink(Node& parent, Node& child)
			{
				if(child.m_pParent != &parent)
					return GAIA::False;
				if(parent.m_links.empty())
					return GAIA::False;
				Node** pFinded = GAIA::ALGO::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), &child);
				*pFinded = GNIL;
				child.m_pParent = GNIL;
				if(parent.m_links.count(GNIL) == parent.m_links.size())
					parent.m_links.clear();
				return GAIA::True;
			}
			GINL GAIA::BL islinked(const Node& parent, const Node& child) const{return child.m_pParent == &parent;}
			GINL Node* parent(const Node& n) const{return n.m_pParent;}
			GINL _SizeType getlinksize(const Node& n) const{return n.m_links.size();}
			GINL Node* getlink(const Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::BL leaf(const Node& n) const
			{
				if(n.m_links.count(GNIL) == this->getlinksize(n))
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::GVOID find(const Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc == GNIL)
					pSrc = m_pRoot;
				if(pSrc == GNIL)
					return;
				if(pSrc->m_t == t)
					result.push_back((const_cast<Node*>(pSrc)));
				for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
				{
					const Node* pNode = pSrc->m_links[x];
					if(pNode == GNIL)
						continue;
					this->find(pNode, t, result);
				}
			}
			GINL GAIA::GVOID paths(const Node* pSrc, __PathListType& result) const
			{
				if(pSrc == GNIL)
					pSrc = m_pRoot;
				if(pSrc == GNIL)
					return;
				this->paths_node(*pSrc, *pSrc, result);
			}
			GINL it front_it()
			{
				it iter;
				iter.m_pNode = m_pRoot;
				return iter;
			}
			GINL it back_it()
			{
				Node* pNode = m_pRoot;
				if(pNode != GNIL)
				{
					for(;;)
					{
						typename __NodeListType::it it = pNode->m_links.back_it();
						GAIA::BL bExistChild = GAIA::False;
						for(; !it.empty(); --it)
						{
							if(*it != GNIL)
							{
								pNode = *it;
								bExistChild = GAIA::True;
								break;
							}
						}
						if(!bExistChild)
							break;
					}
				}
				it iter;
				iter.m_pNode = pNode;
				return iter;
			}
			GINL const_it const_front_it() const
			{
				const_it iter;
				iter.m_pNode = m_pRoot;
				return iter;
			}
			GINL const_it const_back_it() const
			{
				const Node* pNode = m_pRoot;
				if(pNode != GNIL)
				{
					for(;;)
					{
						typename __NodeListType::const_it it = pNode->m_links.const_back_it();
						GAIA::BL bExistChild = GAIA::False;
						for(; !it.empty(); --it)
						{
							if(*it != GNIL)
							{
								pNode = *it;
								bExistChild = GAIA::True;
								break;
							}
						}
						if(!bExistChild)
							break;
					}
				}
				const_it iter;
				iter.m_pNode = pNode;
				return iter;
			}
			GINL Node* tonode(it& it){return it.m_pNode;}
			GINL const Node* tonode(const const_it& it) const{return it.m_pNode;}
			GINL it toit(Node& n){it iter; iter.m_pNode = &n; return iter;}
			GINL const_it toit(const Node& n) const{const_it iter; iter.m_pNode = &n; return iter;}
			GINL GAIA::GVOID collect_valid_index_list(typename __PoolType::__IndexListType& result) const{m_pool.collect_valid_index_list(result);}
			GINL Node& operator[](const _SizeType& index){return m_pool[index];}
			GINL const Node& operator[](const _SizeType& index) const{return m_pool[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this);
				this->clear();
				if(!src.empty())
				{
					m_pRoot = m_pool.alloc();
					m_pRoot->m_pParent = GNIL;
					m_pRoot->m_links.clear();
					this->copy_node(*m_pRoot, *src.m_pRoot);
				}
				return *this;
			}
			GINL GAIA::BL operator == (const __MyType& src) const
			{
				if(this->size() != src.size())
					return GAIA::False;
				const_it srcit = src.const_front_it();
				const_it selfit = this->const_front_it();
				for(; !srcit.empty(); ++srcit, ++selfit)
				{
					if(*selfit != *srcit)
						return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(this->size() > src.size())
					return GAIA::True;
				else if(this->size() < src.size())
					return GAIA::False;
				const_it srcit = src.const_front_it();
				const_it selfit = this->const_front_it();
				for(; !srcit.empty(); ++srcit, ++selfit)
				{
					if(*selfit > *srcit)
						return GAIA::True;
					else if(*selfit < *srcit)
						return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(this->size() < src.size())
					return GAIA::True;
				else if(this->size() > src.size())
					return GAIA::False;
				const_it srcit = src.const_front_it();
				const_it selfit = this->const_front_it();
				for(; !srcit.empty(); ++srcit, ++selfit)
				{
					if(*selfit < *srcit)
						return GAIA::True;
					else if(*selfit > *srcit)
						return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const __MyType& src) const{return !this->operator >= (src);}
		private:
			GINL GAIA::GVOID init(){m_pRoot = GNIL;}
			GINL GAIA::GVOID paths_node(const Node& root, const Node& n, __PathListType& result) const
			{
				if(this->leaf(n))
				{
					__NodeListType temp;
					result.push_back(temp);
					__NodeListType& listNode = result[result.size() - 1];
					const Node* pTempNode = &n;
					while(pTempNode != GNIL)
					{
						listNode.push_back(const_cast<Node*>(pTempNode));
						pTempNode = pTempNode->m_pParent;
					}
					if(!listNode.empty())
						GAIA::ALGO::inverse(listNode.front_ptr(), listNode.back_ptr());
					return;
				}
				for(_SizeType x = 0; x < n.m_links.size(); ++x)
				{
					Node* pNode = n.m_links[x];
					if(pNode == GNIL)
						continue;
					this->paths_node(root, *pNode, result);
				}
			}
			GINL GAIA::GVOID copy_node(Node& dst, const Node& src)
			{
				dst.m_t = src.m_t;
				for(_SizeType x = 0; x < src.m_links.size(); ++x)
				{
					const typename __NodeListType::_datatype& c = src.m_links[x];
					if(c != GNIL)
					{
						Node* pNew = m_pool.alloc();
						pNew->m_pParent = &dst;
						pNew->m_links.clear();
						dst.m_links.push_back(pNew);
						this->copy_node(*pNew, *c);
					}
				}
			}
		private:
			Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif
