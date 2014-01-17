#ifndef		__GAIA_CONTAINER_BASICTREE_H__
#define		__GAIA_CONTAINER_BASICTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicTree
		{
		public:
			class Node
			{
			private:
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
				BasicVector<Node*, _SizeType, _SizeIncreaserType> m_links;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicVector<__NodeListType, _SizeType, _SizeIncreaserType> __PathListType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
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
					GAIA_ASSERT(m_pRoot != GNULL);
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
				*pFinded = NULL;
				child.m_pParent = GNULL;
				return GAIA::True;
			}
			GINL GAIA::BL islinked(const Node& parent, const Node& child) const{if(child.m_pParent == &parent) return GAIA::True; return GAIA::False;}
			GINL Node* parent(const Node& n) const{return n.m_pParent;}
			GINL _SizeType getlinksize(const Node& n) const{return n.m_links.size();}
			GINL _SizeType getlinkcount(const Node& n, Node* p) const{return n.m_links.count(p);}
			GINL Node* getlink(const Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::BL leaf(const Node& n) const
			{
				if(this->getlinkcount(n, GNULL) == this->getlinksize(n))
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
			GINL __MyType& operator = (const __MyType& src)
			{
				return *this;
			}
		public:
		#ifdef GAIA_DEBUG_INTERNALROUTINE
			GINL GAIA::BL dbg_check_relation()
			{
			}
		#endif
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
		private:
			Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif