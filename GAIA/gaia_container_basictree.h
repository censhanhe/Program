#ifndef		__GAIA_CONTAINER_BASICTREE_H__
#define		__GAIA_CONTAINER_BASICTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicTree : public GAIA::Base
		{
		public:
			class Node;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			class Node
			{
			private:
				friend class it;
				friend class const_it;
				friend class BasicTree;
			public:
			#ifdef GAIA_DEBUG_INTERNALROUTINE
				Node(){m_pParent = GNULL;}
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
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL;}
				GINL virtual _DataType& operator * (){return **m_pNode;}
				GINL virtual const _DataType& operator * () const{return **m_pNode;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.empty())
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(m_pNode);
						GAIA_AST(index != GINVALID);
						for(_SizeType x = index + 1; x < m_pNode->m_pParent->m_links.size(); ++x)
						{
							if(m_pNode->m_pParent->m_links[x] != GNULL)
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
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								m_pNode = *it;
								return *this;
							}
							++it;
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.empty())
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(m_pNode);
						GAIA_AST(index != GINVALID);
						if(index > 0)
						{
							_SizeType x = index - 1;
							for(;;)
							{
								if(m_pNode->m_pParent->m_links[x] != GNULL)
								{
									m_pNode = m_pNode->m_pParent->m_links[x];
									return *this;
								}
								if(x == 0)
									break;
								--x;
							}
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						typename __NodeListType::it it = m_pNode->m_links.back_it();
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								m_pNode = *it;
								return *this;
							}
							--it;
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){m_pNode = src.m_pNode; return *this;}
				GINL GAIA::BL operator == (const it& src) const{return m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const it& src) const{return !(this->operator == (src));}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL;}
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
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL;}
				GINL virtual const _DataType& operator * () const{return **m_pNode;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.empty())
					{
						NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(const_cast<Node* const>(m_pNode));
						GAIA_AST(index != GINVALID);
						for(_SizeType x = index + 1; x < m_pNode->m_pParent->m_links.size(); ++x)
						{
							if(m_pNode->m_pParent->m_links[x] != GNULL)
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
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								m_pNode = *it;
								return *this;
							}
							++it;
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.empty())
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						_SizeType index = m_pNode->m_pParent->m_links.find(const_cast<Node* const>(m_pNode));
						GAIA_AST(index != GINVALID);
						if(index > 0)
						{
							_SizeType x = index - 1;
							for(;;)
							{
								if(m_pNode->m_pParent->m_links[x] != GNULL)
								{
									m_pNode = m_pNode->m_pParent->m_links[x];
									return *this;
								}
								if(x == 0)
									break;
								--x;
							}
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						typename __NodeListType::const_it it = m_pNode->m_links.const_back_it();
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								m_pNode = *it;
								return *this;
							}
							--it;
						}
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){m_pNode = src.m_pNode; return *this;}
				GINL GAIA::BL operator == (const const_it& src) const{return m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const const_it& src) const{return !(this->operator == (src));}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL;}
			private:
				const Node* m_pNode;
			};
		public:
			GINL BasicTree(){this->init();}
			GINL BasicTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTree(){}
			GINL GAIA::BL empty() const{return m_pRoot == GNULL;}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNULL; m_pool.destroy();}
			GINL GAIA::GVOID clear(){m_pRoot = GNULL; m_pool.clear();}
			GINL GAIA::GVOID resize(const _SizeType& size){}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL Node* root(){return m_pRoot;}
			GINL const Node* root() const{return m_pRoot;}
			GINL Node* parent(Node* p){if(p != GNULL) return p->m_pParent; return GNULL;}
			GINL const Node* parent(Node* p) const{if(p != GNULL) return p->m_pParent; return GNULL;}
			GINL Node* insert(const _DataType& t, Node* pNode)
			{
				Node* pNew = m_pool.alloc();
				pNew->m_t = t;
				pNew->m_pParent = GNULL;
				pNew->m_links.clear();
				if(pNode == GNULL)
				{
					if(m_pRoot == GNULL)
						m_pRoot = pNew;
					else
						this->link(*m_pRoot, *pNew);
				}
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
					if(pNode == GNULL)
						continue;
					this->erase(*pNode);
				}
				if(n.m_pParent != GNULL)
					this->unlink(*n.m_pParent, n);
				m_pool.release(&n);
				if(&n == m_pRoot)
					m_pRoot = GNULL;
			}
			GINL GAIA::BL link(Node& parent, Node& child)
			{
				if(child.m_pParent != GNULL)
					this->unlink(*child.m_pParent, child);
				Node** ppn;
				if(!parent.m_links.empty())
					ppn = GAIA::ALGORITHM::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), (Node*)GNULL);
				else
					ppn = GNULL;
				if(ppn == GNULL)
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
				Node** pFinded = GAIA::ALGORITHM::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), &child);
				*pFinded = GNULL;
				child.m_pParent = GNULL;
				if(parent.m_links.count(GNULL) == parent.m_links.size())
					parent.m_links.clear();
				return GAIA::True;
			}
			GINL GAIA::BL islinked(const Node& parent, const Node& child) const{return child.m_pParent == &parent;}
			GINL Node* parent(const Node& n) const{return n.m_pParent;}
			GINL _SizeType getlinksize(const Node& n) const{return n.m_links.size();}
			GINL Node* getlink(const Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::BL leaf(const Node& n) const
			{
				if(n.m_links.count(GNULL) == this->getlinksize(n))
					return GAIA::True;
				return GAIA::False;
			}
			GINL GAIA::GVOID find(const Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc == GNULL)
					pSrc = m_pRoot;
				if(pSrc == GNULL)
					return;
				if(pSrc->m_t == t)
					result.push_back((const_cast<Node*>(pSrc)));
				for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
				{
					const Node* pNode = pSrc->m_links[x];
					if(pNode == GNULL)
						continue;
					this->find(pNode, t, result);
				}
			}
			GINL GAIA::GVOID paths(const Node* pSrc, __PathListType& result) const
			{
				if(pSrc == GNULL)
					pSrc = m_pRoot;
				if(pSrc == GNULL)
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
				if(pNode != GNULL)
				{
					for(;;)
					{
						typename __NodeListType::it it = pNode->m_links.back_it();
						GAIA::BL bExistChild = GAIA::False;
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								pNode = *it;
								bExistChild = GAIA::True;
								break;
							}
							--it;
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
				if(pNode != GNULL)
				{
					for(;;)
					{
						typename __NodeListType::const_it it = pNode->m_links.const_back_it();
						GAIA::BL bExistChild = GAIA::False;
						while(!it.empty())
						{
							if(*it != GNULL)
							{
								pNode = *it;
								bExistChild = GAIA::True;
								break;
							}
							--it;
						}
						if(!bExistChild)
							break;
					}
				}
				const_it iter;
				iter.m_pNode = pNode;
				return iter;
			}
			GINL GAIA::GVOID collect_valid_index_list(typename __PoolType::__IndexListType& result) const{m_pool.collect_valid_index_list(result);}
			GINL Node& operator[](const _SizeType& index){return m_pool[index];}
			GINL const Node& operator[](const _SizeType& index) const{return m_pool[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				if(!src.empty())
				{
					m_pRoot = m_pool.alloc();
					m_pRoot->m_pParent = GNULL;
					m_pRoot->m_links.clear();
					this->copy_node(*m_pRoot, *src.m_pRoot);
				}
				return *this;
			}
		private:
			GINL GAIA::GVOID init(){m_pRoot = GNULL;}
			GINL GAIA::GVOID paths_node(const Node& root, const Node& n, __PathListType& result) const
			{
				if(this->leaf(n))
				{
					__NodeListType temp;
					result.push_back(temp);
					__NodeListType& listNode = result[result.size() - 1];
					const Node* pTempNode = &n;
					while(pTempNode != GNULL)
					{
						listNode.push_back(const_cast<Node*>(pTempNode));
						pTempNode = pTempNode->m_pParent;
					}
					if(!listNode.empty())
						GAIA::ALGORITHM::inverse(listNode.front_ptr(), listNode.back_ptr());
					return;
				}
				for(_SizeType x = 0; x < n.m_links.size(); ++x)
				{
					Node* pNode = n.m_links[x];
					if(pNode == GNULL)
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
					if(c != GNULL)
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
