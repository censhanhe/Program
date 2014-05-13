#ifndef		__GAIA_CONTAINER_BASICTRIETREE_H__
#define		__GAIA_CONTAINER_BASICTRIETREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicTrieTree : public GAIA::Base
		{
		public:
			class Node;
			typedef BasicAVLTree<Ref<Node>, _SizeType, _SizeType, _SizeIncreaserType> __NodeTreeType;
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
					GAIA_AST(&src != this); 
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
			typedef BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType> __PoolType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicTrieTree;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL || m_pNode->m_pParent == GNULL;}
				GINL virtual _DataType& operator * (){return m_pNode->m_t;}
				GINL virtual const _DataType& operator * () const{return m_pNode->m_t;}
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
							m_pNode = m_pContainer->back_node(*it);
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
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){GAIA_AST(&src != this); m_pNode = src.m_pNode; m_pContainer = src.m_pContainer; return *this;}
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
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						++ret;
						--iter;
					}
					iter = *this;
					ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						--ret;
						++iter;
					}
					return ret;
				}
				GINL GAIA::BL operator == (const it& src) const{return m_pContainer == src.m_pContainer && m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const it& src) const{return !(this->operator == (src));}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL; m_pContainer = GNULL;}
			private:
				Node* m_pNode;
				__MyType* m_pContainer;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicTrieTree;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pNode == GNULL || m_pNode->m_pParent == GNULL;}
				GINL virtual const _DataType& operator * () const{return m_pNode->m_t;}
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
							m_pNode = m_pContainer->back_node(*it);
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
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_pNode = src.m_pNode; m_pContainer = src.m_pContainer; return *this;}
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
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						++ret;
						--iter;
					}
					iter = *this;
					ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						--ret;
						++iter;
					}
					return ret;
				}
				GINL GAIA::BL operator == (const const_it& src) const{return m_pContainer == src.m_pContainer && m_pNode == src.m_pNode;}
				GINL GAIA::BL operator != (const const_it& src) const{return !(this->operator == (src));}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL; m_pContainer = GNULL;}
			private:
				const Node* m_pNode;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicTrieTree(){this->init();}
			GINL BasicTrieTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTrieTree(){}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL const _SizeType& capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID clear(){this->init(); m_root.m_links.clear(); m_pool.clear();}
			GINL GAIA::GVOID destroy(){this->init(); m_root.m_links.destroy(); m_pool.destroy();}
			GINL GAIA::GVOID insert(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				if(this->insert_node(m_root, p, size))
					++m_root.m_category_count;
			}
			GINL GAIA::BL erase(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
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
						if(pNode->m_pParent != GNULL && 
							pNode->m_count == 0 && 
							pNode->m_category_count == 0 && 
							pNode->m_full_count == 0)
						{
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
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				Node* pFinded = this->match_node(m_root, p, size);
				if(pFinded == GNULL)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL leaf(const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(!!p);
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
			GINL GAIA::BL leaf(const it& iter) const{if(iter.empty()) return GAIA::False; return iter.m_pNode->m_links.empty();}
			GINL GAIA::BL leaf(const const_it& iter) const{if(iter.empty()) return GAIA::False; return iter.m_pNode->m_links.empty();}
			GINL Node& root(){return m_root;}
			GINL const Node& root() const{return m_root;}
			GINL GAIA::BL root(const it& iter) const{return iter.m_pNode == &m_root;}
			GINL GAIA::BL root(const const_it& iter) const{return iter.m_pNode == &m_root;}
			GINL it root_it(){it iter; iter.m_pNode = &m_root; iter.m_pContainer = this; return iter;}
			GINL const_it root_it() const{const_it iter; iter.m_pNode = &m_root; iter.m_pContainer = this; return iter;}
			GINL const Node* parent(const Node& n) const{return n.m_pParent;}
			GINL Node* parent(Node& n){return n.m_pParent;}
			GINL it parent_it(const it& iter){it ret; ret.m_pNode = iter.m_pNode == GNULL ? GNULL : iter.m_pNode->m_pParent; ret.m_pContainer = this; return ret;}
			GINL const_it parent_it(const const_it& iter) const{const_it ret; ret.m_pNode = iter.m_pNode == GNULL ? GNULL : iter.m_pNode->m_pParent; ret.m_pContainer = this; return ret;}
			GINL typename __NodeTreeType::_sizetype childsize(Node& n) const{return n.m_links.size();}
			GINL typename __NodeTreeType::const_it child_const_front_it(const Node& n) const{return n.m_links.const_front_it();}
			GINL typename __NodeTreeType::it child_front_it(Node& n){return n.m_links.front_it();}
			GINL typename __NodeTreeType::const_it child_const_back_it(const Node& n) const{return n.m_links.const_back_it();}
			GINL typename __NodeTreeType::it child_back_it(Node& n){return n.m_links.back_it();}
			GINL Node* tonode(it& it){return it.m_pNode;}
			GINL const Node* tonode(const const_it& it) const{return it.m_pNode;}
			GINL Node* tonode(typename __NodeTreeType::it& it){return *it;}
			GINL const Node* tonode(const typename __NodeTreeType::const_it& it) const{return *it;}
			GINL it toit(Node& n){it iter; iter.m_pNode = &n; iter.m_pContainer = this; return iter;}
			GINL const_it toit(const Node& n) const{const_it iter; iter.m_pNode = &n; iter.m_pContainer = this; return iter;}
			GINL Node* find(const Node* pNode, const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				return this->match_node(pNode == GNULL? m_root : *pNode, p, size);
			}
			GINL it lower_bound(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				Node* pNode = &m_root;
				for(_SizeType x = 0; x < size; ++x)
				{
					Node n;
					n.m_t = p[x];
					Ref<Node> rn = &n;
					typename __NodeTreeType::it itsub = pNode->m_links.lower_bound(rn);
					if(itsub.empty())
					{
						if(pNode->m_pParent == GNULL)
							break;
						typename __NodeTreeType::it itsubb = pNode->m_links.back_it();
						it itertemp;
						itertemp.m_pContainer = this;
						if(itsubb.empty())
							itertemp.m_pNode = pNode;
						else
							itertemp.m_pNode = *itsubb;
						++itertemp;
						pNode = itertemp.m_pNode;
						break;
					}
					else
					{
						pNode = *itsub;
						if((**pNode) != p[x])
							break;
					}
				}
				it iter;
				if(pNode != GNULL && pNode != &m_root)
				{
					iter.m_pNode = pNode;
					iter.m_pContainer = this;
				}
				return iter;
			}
			GINL it upper_bound(const _DataType* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				it iter = this->lower_bound(p, size);
				GAIA::BL bMatch = GAIA::True;
				it itertemp = iter;
				for(_SizeType x = 0; x < size; ++x)
				{
					if(itertemp.empty())
					{
						bMatch = GAIA::False;
						break;
					}
					if(*itertemp != p[size - x - 1])
					{
						bMatch = GAIA::False;
						break;
					}
					itertemp = this->parent_it(itertemp);
				}
				if(!itertemp.empty())
					bMatch = GAIA::False;
				if(!bMatch)
					--iter;
				return iter;
			}
			GINL const_it lower_bound(const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				const Node* pNode = &m_root;
				for(_SizeType x = 0; x < size; ++x)
				{
					Node n;
					n.m_t = p[x];
					Ref<Node> rn = &n;
					typename __NodeTreeType::const_it itsub = pNode->m_links.lower_bound(rn);
					if(itsub.empty())
					{
						if(pNode->m_pParent == GNULL)
							break;
						typename __NodeTreeType::const_it itsubb = pNode->m_links.const_back_it();
						const_it itertemp;
						itertemp.m_pContainer = this;
						if(itsubb.empty())
							itertemp.m_pNode = pNode;
						else
							itertemp.m_pNode = *itsubb;
						++itertemp;
						pNode = itertemp.m_pNode;
						break;
					}
					else
					{
						pNode = *itsub;
						if((**pNode) != p[x])
							break;
					}
				}
				const_it iter;
				if(pNode != GNULL && pNode != &m_root)
				{
					iter.m_pNode = pNode;
					iter.m_pContainer = this;
				}
				return iter;
			}
			GINL const_it upper_bound(const _DataType* p, const _SizeType& size) const
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				const_it iter = this->lower_bound(p, size);
				GAIA::BL bMatch = GAIA::True;
				const_it itertemp = iter;
				for(_SizeType x = 0; x < size; ++x)
				{
					if(itertemp.empty())
					{
						bMatch = GAIA::False;
						break;
					}
					if(*itertemp != p[size - x - 1])
					{
						bMatch = GAIA::False;
						break;
					}
					itertemp = this->parent_it(itertemp);
				}
				if(!itertemp.empty())
					bMatch = GAIA::False;
				if(!bMatch)
					--iter;
				return iter;
			}
			GINL GAIA::GVOID paths(const Node* pNode, const _DataType* p, const _SizeType& size, __PathListType& result) const
			{
				GAIA_AST(!!p);
				GAIA_AST(size > 0);
				Node* pTempNode = this->match_node(pNode == GNULL ? m_root : *pNode, p, size);
				if(pTempNode == GNULL)
					return;
			}
			GINL _SizeType count(const Node& n) const{return n.m_count;} // The insert element list stopped at parameter n's count.
			GINL _SizeType catagory_count(const Node& n) const{return n.m_category_count;} // The insert element list catagory count in the child tree, include self.
			GINL _SizeType full_count(const Node& n) const{return n.m_full_count;} // The insert element list pass at parameter n's count, include self.
			GINL it front_it()
			{
				it iter;
				typename __NodeTreeType::it itf = m_root.m_links.front_it();
				if(!itf.empty())
				{
					iter.m_pNode = *itf;
					iter.m_pContainer = this;
				}
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
				{
					iter.m_pNode = pNode;
					iter.m_pContainer = this;
				}
				return iter;
			}
			GINL const_it const_front_it() const
			{
				const_it iter;
				typename __NodeTreeType::const_it itf = m_root.m_links.const_front_it();
				if(!itf.empty())
				{
					iter.m_pNode = *itf;
					iter.m_pContainer = this;
				}
				return iter;
			}
			GINL const_it const_back_it() const
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
				{
					iter.m_pNode = pNode;
					iter.m_pContainer = this;
				}
				return iter;
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this); 
				typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __VectorType;
				__VectorType paths;
				this->clear();
				const_it it = src.const_front_it();
				while(!it.empty())
				{
					if(src.leaf(it))
					{
						paths.clear();
						const_it itt = it;
						while(!itt.empty())
						{
							paths.push_back(*itt);	
							itt = src.parent_it(itt);
						}
						if(!paths.empty())
						{
							paths.inverse();
							this->insert(paths.front_ptr(), paths.size());
						}
					}
					++it;
				}
				return *this;
			}
			GINL GAIA::BL operator == (const __MyType& src) const
			{
				if(this->size() != src.size())
					return GAIA::False;
				const_it srcit = src.const_front_it();
				const_it selfit = this->const_front_it();
				while(!srcit.empty())
				{
					if(*selfit != *srcit)
						return GAIA::False;
					++srcit;
					++selfit;
				}
				return GAIA::True;
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(this->size() > src.size())
					return GAIA::True;
				else if(this->size() < src.size())
					return GAIA::False;
				const_it srcit = src.const_front_it();
				const_it selfit = this->const_front_it();
				while(!srcit.empty())
				{
					if(*selfit > *srcit)
						return GAIA::True;
					else if(*selfit < *srcit)
						return GAIA::False;
					++srcit;
					++selfit;
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
				while(!srcit.empty())
				{
					if(*selfit < *srcit)
						return GAIA::True;
					else if(*selfit > *srcit)
						return GAIA::False;
					++srcit;
					++selfit;
				}
				return GAIA::True;
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
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
						++pFinded->m_category_count;
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
				GAIA_AST(!!p);
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
			GINL Node* front_node(Node* pNode)
			{
				typename __NodeTreeType::it iter = pNode->m_links.front_it();
				if(iter.empty())
					return pNode;
				else
					return this->front_node(*iter);
			}
			GINL Node* back_node(Node* pNode)
			{
				typename __NodeTreeType::it iter = pNode->m_links.back_it();
				if(iter.empty())
					return pNode;
				else
					return this->back_node(*iter);
			}
			GINL const Node* front_node(const Node* pNode) const
			{
				typename __NodeTreeType::const_it iter = pNode->m_links.const_front_it();
				if(iter.empty())
					return pNode;
				else
					return this->front_node(*iter);
			}
			GINL const Node* back_node(const Node* pNode) const
			{
				typename __NodeTreeType::const_it iter = pNode->m_links.const_back_it();
				if(iter.empty())
					return pNode;
				else
					return this->back_node(*iter);
			}
		private:
			Node m_root;
			__PoolType m_pool;
		};
	};
};

#endif
