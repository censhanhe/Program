#ifndef		__GAIA_CONTAINER_BASICTRIETREE_H__
#define		__GAIA_CONTAINER_BASICTRIETREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicTrieTree
		{
		public:
			class Node;
			typedef BasicAVLTree<Ref<Node>, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __NodeTreeType;
			typedef BasicVector<__NodeTreeType, _SizeType, _SizeIncreaserType> __PathListType;
		public:
			class Node
			{
			private:
				friend class it;
				friend class const_it;
				friend class BasicTrieTree;
			public:
				GINL _DataType& operator * (){return m_t;}
				GINL const _DataType& operator * () const{return m_t;}
				GINL Node& operator = (const Node& src)
				{
					m_pParent = src.m_pParent;
					m_links = src.m_links;
					m_t = src.m_t;
					m_count = src.m_count;
					m_category_count = src.m_category_count;
					m_full_count = src.m_full_count;
					return *this;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_t, m_t, Node);
			private:
				GINL Node* find_child_node(const _DataType& t) const
				{
					Node n;
					n.m_t = t;
					Ref<Node> rn = &n;
					Ref<Node>* pResult = const_cast<Ref<Node>*>(m_links.find(rn));
					if(pResult == GNULL)
						return GNULL;
					return *pResult;
				}
			private:
				Node* m_pParent;
				__NodeTreeType m_links;
				_DataType m_t;
				_SizeType m_count;
				_SizeType m_category_count;
				_SizeType m_full_count;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicTrieTree;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL;}
				GINL virtual _DataType& operator * (){return m_pNode->m_t;}
				GINL virtual const _DataType& operator * () const{return m_pNode->m_t;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.size() == 0)
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						typename __NodeTreeType::it it = m_pNode->m_pParent->m_links.lower_bound(Ref<Node>(m_pNode));
						GAIA_AST(!it.empty());
						++it;
						if(!it.empty())
						{
							m_pNode = *it;
							return *this;
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						m_pNode = *m_pNode->m_links.front_it();
						return *this;
					}
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_pParent != GNULL)
					{
						typename __NodeTreeType::it it = m_pNode->m_pParent->m_links.lower_bound(Ref<Node>(m_pNode));
						GAIA_AST(!it.empty());
						--it;
						if(!it.empty())
						{
							m_pNode = *it;
							return *this;
						}
						else
						{
							m_pNode = m_pNode->m_pParent;
							if(m_pNode->m_pParent == GNULL)
								m_pNode = GNULL;
							return *this;
						}
					}
					else
					{
						m_pNode = GNULL;
						return *this;
					}
				}
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
				friend class BasicTrieTree;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL;}
				GINL virtual const _DataType& operator * () const{return m_pNode->m_t;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_links.size() == 0)
					{
					NEXT_LOOP:
						if(m_pNode->m_pParent == GNULL)
						{
							m_pNode = GNULL;
							return *this;
						}
						typename __NodeTreeType::const_it it = 
							(const_cast<const Node*>(m_pNode->m_pParent))->m_links.lower_bound(
								Ref<Node>(const_cast<Node*>(m_pNode)));
						GAIA_AST(!it.empty());
						++it;
						if(!it.empty())
						{
							m_pNode = *it;
							return *this;
						}
						m_pNode = m_pNode->m_pParent;
						goto NEXT_LOOP;
					}
					else
					{
						m_pNode = *m_pNode->m_links.const_front_it();
						return *this;
					}
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					if(m_pNode->m_pParent != GNULL)
					{
						typename __NodeTreeType::const_it it = 
							(const_cast<const Node*>(m_pNode->m_pParent))->m_links.lower_bound(
								Ref<Node>(const_cast<Node*>(m_pNode)));
						GAIA_AST(!it.empty());
						--it;
						if(!it.empty())
						{
							m_pNode = *it;
							return *this;
						}
						else
						{
							m_pNode = m_pNode->m_pParent;
							if(m_pNode->m_pParent == GNULL)
								m_pNode = GNULL;
							return *this;
						}
					}
					else
					{
						m_pNode = GNULL;
						return *this;
					}
				}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL;}
			private:
				const Node* m_pNode;
			};
		public:
			typedef BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicTrieTree(){this->init();}
			GINL BasicTrieTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTrieTree(){}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID clear(){this->init(); m_root.m_links.clear(); m_pool.clear();}
			GINL GAIA::GVOID destroy(){this->init(); m_root.m_links.destroy(); m_pool.destroy();}
			GINL GAIA::GVOID insert(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				if(this->insert_node(m_root, p, size))
					++m_root.m_category_count;
			}
			GINL GAIA::BL erase(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				Node* pNode = this->match_node(m_root, p, size);
				if(pNode == GNULL)
					return GAIA::False;
				else
				{
					if(pNode->m_count == 0)
						return GAIA::False;
					--pNode->m_count;
					while(pNode != GNULL)
					{
						--pNode->m_category_count;
						--pNode->m_full_count;
						if(pNode->m_count == 0 && pNode->m_category_count == 0 && pNode->m_full_count == 0)
						{
							if(pNode->m_pParent != GNULL)
								pNode->m_pParent->m_links.erase(pNode);
							m_pool.release(pNode);
						}
						pNode = pNode->m_pParent;
					}
				}
				return GAIA::True;
			}
			GINL GAIA::BL exist(const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				Node* pFinded = this->match_node(m_root, p, size);
				if(pFinded == GNULL)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL leaf(const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				Node* pFinded = this->match_node(m_root, p, size);
				if(pFinded != GNULL)
				{
					if(pFinded->m_links.empty())
						return GAIA::True;
					else
						return GAIA::False;
				}
				return GAIA::False;
			}
			GINL GAIA::BL leaf(const it& iter) const{if(iter.empty()) return GAIA::False; return iter.m_pNode->m_links.size() == 0;}
			GINL GAIA::BL leaf(const const_it& iter) const{if(iter.empty()) return GAIA::False; return iter.m_pNode->m_links.size() == 0;}
			GINL GAIA::BL root(const it& iter) const{return iter.m_pNode == &m_root;}
			GINL GAIA::BL root(const const_it& iter) const{return iter.m_pNode == &m_root;}
			GINL it root(){it iter; iter.m_pNode = &m_root; return iter;}
			GINL const_it root() const{const_it iter; iter.m_pNode = &m_root; return iter;}
			GINL it parent(const it& iter){it ret; ret.m_pNode = iter.m_pNode == GNULL ? GNULL : iter.m_pNode->m_pParent; return ret;}
			GINL const_it parent(const const_it& iter) const{const_it ret; ret.m_pNode = iter.m_pNode == GNULL ? GNULL : iter.m_pNode->m_pParent; return ret;}
			GINL Node* find(const Node* pNode, const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				return this->match_node(pNode == GNULL? m_root : *pNode, p, size);
			}
			GINL it lower_bound(const _DataType* p, const _SizeType& size)
			{
			}
			GINL it upper_bound(const _DataType* p, const _SizeType& size)
			{
			}
			GINL const_it lower_bound(const _DataType* p, const _SizeType& size) const
			{
			}
			GINL const_it upper_bound(const _DataType* p, const _SizeType& size) const
			{
			}
			GINL GAIA::GVOID paths(const Node* pNode, const _DataType* p, const _SizeType& size, __PathListType& result) const
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				Node* pTempNode = this->match_node(pNode == GNULL ? m_root : *pNode, p, size);
				if(pTempNode == GNULL)
					return;
			}
			GINL _SizeType count(Node& n) const{return n.m_count;}
			GINL _SizeType catagory_count(Node& n) const{return n.m_category_count;}
			GINL _SizeType full_count(Node& n) const{return n.m_full_count;}
			GINL it front_it()
			{
				it iter;
				typename __NodeTreeType::it itf = m_root.m_links.front_it();
				if(!itf.empty())
					iter.m_pNode = *itf;
				return iter;
			}
			GINL it back_it()
			{
				Node* pNode = &m_root;
				if(pNode != GNULL)
				{
					for(;;)
					{
						typename __NodeTreeType::it it = pNode->m_links.back_it();
						GAIA::BL bExistChild = GAIA::False;
						while(!it.empty())
						{
							if(*it != (const Node*)GNULL)
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
				if(pNode != &m_root)
					iter.m_pNode = pNode;
				return iter;
			}
			GINL const_it const_front_it()
			{
				const_it iter;
				typename __NodeTreeType::const_it itf = m_root.m_links.const_front_it();
				if(!itf.empty())
					iter.m_pNode = *itf;
				return iter;
			}
			GINL const_it const_back_it()
			{
				const Node* pNode = &m_root;
				if(pNode != GNULL)
				{
					for(;;)
					{
						typename __NodeTreeType::const_it it = pNode->m_links.const_back_it();
						GAIA::BL bExistChild = GAIA::False;
						while(!it.empty())
						{
							if(*it != (const Node*)GNULL)
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
				if(pNode != &m_root)
					iter.m_pNode = pNode;
				return iter;
			}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init()
			{
				m_root.m_pParent = GNULL;
				m_root.m_count = 0;
				m_root.m_category_count = 0;
				m_root.m_full_count = 0;
			}
			GINL GAIA::BL insert_node(Node& n, const _DataType* p, const _SizeType& size)
			{
				GAIA::BL ret = GAIA::False;
				if(size == 0)
				{
					if(n.m_count == 0)
						ret = GAIA::True;
					++n.m_count;
					return ret;
				}
				++n.m_full_count;
				Node* pFinded = n.find_child_node(*p);
				if(pFinded != GNULL)
				{
					if(this->insert_node(*pFinded, p + 1, size - 1))
					{
						++n.m_category_count;
						ret = GAIA::True;
					}
				}
				else
				{
					Node* pNew = m_pool.alloc();
					pNew->m_pParent = &n;
					pNew->m_links.clear();
					pNew->m_t = *p;
					pNew->m_count = 0;
					pNew->m_category_count = 1;
					n.m_links.insert(pNew);
					ret = GAIA::True;
					this->insert_node(*pNew, p + 1, size - 1);
					pNew->m_full_count = 1;
				}
				return ret;
			}
			GINL Node* match_node(const Node& n, const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(p != GNULL);
				GAIA_AST(size > 0);
				const _DataType* pTemp = p;
				_SizeType sizetemp = size;
				const Node* pNodeTemp = &n;
				while(GAIA::ALWAYSTRUE)
				{
					Node* pFinded = pNodeTemp->find_child_node(*pTemp);
					if(pFinded != GNULL)
					{
						pNodeTemp = pFinded;
						++pTemp;
						--sizetemp;
						if(sizetemp == 0)
							return const_cast<Node*>(pNodeTemp);
					}
					else
						return GNULL;
				}
				return GNULL;
			}
		private:
			Node m_root;
			__PoolType m_pool;
		};
	};
};

#endif
