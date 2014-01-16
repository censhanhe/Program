#ifndef		__GAIA_CONTAINER_BASICTREE_H__
#define		__GAIA_CONTAINER_BASICTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicTree
		{
		public:
			template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class Node
			{
			private:
				friend class BasicTree;
			public:
			#ifdef GAIA_DEBUG_INTERNALROUTINE
				Node(){m_pParent = GNULL;}
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
			typedef Node<_DataType, _SizeType, _SizeIncreaserType> __Node;
			typedef BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<__Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicPool<__Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
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
			GINL __Node* root(){return m_pRoot;}
			GINL const __Node* root() const{return m_pRoot;}
			GINL __Node* insert(const _DataType& t, __Node* pNode)
			{
				__Node* pNew = m_pool.alloc();
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
			GINL GAIA::GVOID erase(__Node& n)
			{
				for(_SizeType x = 0; x < n.m_links.size(); ++x)
				{
					__Node* pNode = n.m_links[x];
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
			GINL GAIA::BL link(__Node& parent, __Node& child)
			{
				if(child.m_pParent != GNULL)
					this->unlink(*child.m_pParent, child);
				__Node** ppn;
				if(!parent.m_links.empty())
					ppn = GAIA::ALGORITHM::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), (__Node*)GNULL);
				else
					ppn = GNULL;
				if(ppn == GNULL)
					parent.m_links.push_back(&child);
				else
					*ppn = &child;
				child.m_pParent = &parent;
				return GAIA::True;
			}
			GINL GAIA::BL unlink(__Node& parent, __Node& child)
			{
				if(child.m_pParent != &parent)
					return GAIA::False;
				if(parent.m_links.empty())
					return GAIA::False;
				__Node** pFinded = GAIA::ALGORITHM::find(parent.m_links.front_ptr(), parent.m_links.back_ptr(), &child);
				*pFinded = NULL;
				child.m_pParent = GNULL;
				return GAIA::True;
			}
			GINL GAIA::BL islinked(const __Node& parent, const __Node& child) const{if(child.m_pParent == &parent) return GAIA::True; return GAIA::False;}
			GINL __Node* parent(const __Node& n) const{return n.m_pParent;}
			GINL _SizeType getlinksize(const __Node& n) const{return n.m_links.size();}
			GINL _SizeType getlinkcount(const __Node& n, __Node* p) const{return n.m_links.count(p);}
			GINL __Node* getlink(const __Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::GVOID find(const __Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc == GNULL)
					pSrc = m_pRoot;
				if(pSrc == GNULL)
					return;
				if(pSrc->m_t == t)
					result.push_back((const_cast<__Node*>(pSrc)));
				for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
				{
					const __Node* pNode = pSrc->m_links[x];
					if(pNode == GNULL)
						continue;
					this->find(pNode, t, result);
				}
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
		private:
			__Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif