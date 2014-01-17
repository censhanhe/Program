#ifndef		__GAIA_CONTAINER_BASICGRAPH_H__
#define		__GAIA_CONTAINER_BASICGRAPH_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _DistanceType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicGraph
		{
		public:
			class Node
			{
			private:
				friend class BasicGraph;
			public:
			#ifdef GAIA_DEBUG_INTERNALROUTINE
				Node(){m_bTraveling = GAIA::False;}
			#endif
			public:
				GINL GAIA::GVOID EnterTraveling() const
				{
					GAIA_ASSERT(!m_bTraveling);
					(const_cast<Node*>(this))->m_bTraveling = GAIA::True;
				}
				GINL GAIA::GVOID LeaveTraveling() const
				{
					GAIA_ASSERT(m_bTraveling);
					(const_cast<Node*>(this))->m_bTraveling = GAIA::False;
				}
				GINL _DataType& operator * (){return m_t;}
				GINL const _DataType& operator * () const{return m_t;}
			private:
				_DataType m_t;
				BasicVector<Node*, _SizeType, _SizeIncreaserType> m_links;
				GAIA::BL m_bTraveling : 1;
			};
		public:
			typedef _DataType _datatype;
			typedef _DistanceType _distancetype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicGraph<_DataType, _DistanceType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicTree<Node*, _SizeType, _SizeIncreaserType, _GroupElementSize> __PathTreeType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicGraph(){this->init();}
			GINL BasicGraph(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicGraph(){}
			GINL GAIA::BL empty() const{return m_pRoot == GNULL;}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNULL; m_pool.destroy();}
			GINL GAIA::GVOID clear(){m_pRoot = GNULL; m_pool.clear();}
			GINL GAIA::GVOID resize(const _SizeType& size){}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL Node* root(){return m_pRoot;}
			GINL const Node* root() const{return m_pRoot;}
			GINL GAIA::GVOID root(Node* pNewRoot){m_pRoot = pNewRoot;}
			GINL Node* insert(const _DataType& t, Node* pNode)
			{
				Node* pNew = m_pool.alloc();
				pNew->m_t = t;
				pNew->m_links.clear();
				pNew->m_bTraveling = GAIA::False;
				if(pNode == NULL)
				{
					if(m_pRoot == NULL)
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
					if(pNode != GNULL)
					{
						for(_SizeType y = 0; y < pNode->m_links.size(); ++y)
						{
							if(pNode->m_links[y] == &n)
							{
								pNode->m_links[y] = GNULL;
								break;
							}
						}
					}
				}
				n.m_links.clear();
				m_pool.release(&n);
				if(&n == m_pRoot)
					m_pRoot = GNULL;
			}
			GINL GAIA::BL link(Node& n1, Node& n2)
			{
				if(this->islinked(n1, n2))
					return GAIA::False;
				Node** ppn1 = GNULL;
				Node** ppn2 = GNULL;
				for(_SizeType x = 0; x < n1.m_links.size(); ++x)
				{
					if(n1.m_links[x] == GNULL)
					{
						ppn1 = &n1.m_links[x];
						break;
					}
				}
				for(_SizeType x = 0; x < n2.m_links.size(); ++x)
				{
					if(n2.m_links[x] == GNULL)
					{
						ppn2 = &n2.m_links[x];
						break;
					}
				}
				if(ppn1 == NULL)
					n1.m_links.push_back(&n2);
				else
					*ppn1 = &n2;
				if(ppn2 == NULL)
					n2.m_links.push_back(&n1);
				else
					*ppn2 = &n1;
				return GAIA::True;
			}
			GINL GAIA::BL unlink(Node& n1, Node& n2)
			{
				GAIA::BL bRet = GAIA::False;
				for(_SizeType x = 0; x < n1.m_links.size(); ++x)
				{
					if(n1.m_links[x] == &n2)
					{
						n1.m_links[x] = GNULL;
						bRet = GAIA::True;
						break;
					}
				}
				if(bRet)
				{
					for(_SizeType x = 0; x < n2.m_links.size(); ++x)
					{
						if(n2.m_links[x] == &n1)
						{
							n2.m_links[x] = GNULL;
							break;
						}
					}
				}
				return bRet;
			}
			GINL GAIA::BL islinked(const Node& n1, const Node& n2) const
			{
				for(_SizeType x = 0; x < n1.m_links.size(); ++x)
				{
					if(n1.m_links[x] == &n2)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL _SizeType getlinksize(const Node& n) const{return n.m_links.size();}
			GINL _SizeType getlinkcount(const Node& n, Node* p) const{return n.m_links.count(p);}
			GINL Node* getlink(const Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::GVOID find(const Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc == GNULL)
					pSrc = m_pRoot;
				if(pSrc == GNULL)
					return;
				this->find_node(pSrc, t, result);
				if(!result.empty())
				{
					result.sort();
					result.unique();
				}
			}
			GINL GAIA::GVOID paths(const Node& src, const Node& dst, __PathTreeType& result) const
			{
				result.clear();
				this->paths_node(src, dst, result, GNULL);
			}
			GINL GAIA::GVOID paths(const Node& src, const _DataType& t, __PathTreeType& result) const
			{
				result.clear();
				this->paths_node(src, t, result, GNULL);
			}
			GINL GAIA::GVOID collect_valid_index_list(typename __PoolType::__IndexListType& result) const{m_pool.collect_valid_index_list(result);}
			GINL Node& operator[](const _SizeType& index){return m_pool[index];}
			GINL const Node& operator[](const _SizeType& index) const{return m_pool[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				return *this;
			}
		public:
		#ifdef GAIA_DEBUG_INTERNALROUTINE
			GINL GAIA::BL dbg_check_traveling()
			{
				typename __PoolType::__IndexListType result;
				m_pool.collect_valid_index_list(result);
				for(_SizeType x = 0; x < result.size(); ++x)
				{
					Node& t = m_pool[result[x]];
					if(t.m_bTraveling)
						return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL dbg_check_relation()
			{
				typename __PoolType::__IndexListType result;
				m_pool.collect_valid_index_list(result);
				for(_SizeType x = 0; x < result.size(); ++x)
				{
					Node& t = m_pool[result[x]];
					for(_SizeType y = 0; y < t.m_links.size(); ++y)
					{
						Node* pNode = t.m_links[y];
						if(pNode == GNULL)
							continue;
						GAIA::BL bExist  = GAIA::False;
						for(_SizeType z = 0; z < pNode->m_links.size(); ++z)
						{
							if(pNode->m_links[z] == &t)
							{
								bExist = GAIA::True;
								break;
							}
						}
						if(!bExist)
							return GAIA::False;
					}
				}
				return GAIA::True;
			}
		#endif
		private:
			GINL GAIA::GVOID init(){m_pRoot = GNULL;}
			GINL GAIA::GVOID find_node(const Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc->m_bTraveling)
					return;
				if(pSrc->m_t == t)
				{
					result.push_back(const_cast<Node*>(pSrc));
					return;
				}
				pSrc->EnterTraveling();
				{
					for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
					{
						const Node* pNode = pSrc->m_links[x];
						if(pNode == GNULL)
							continue;
						this->find_node(pNode, t, result);
					}
				}
				pSrc->LeaveTraveling();
			}
			GINL GAIA::GVOID paths_node(const Node& src, const Node& dst, __PathTreeType& result, typename __PathTreeType::Node* pParentTreeNode) const
			{
				if(src.m_bTraveling)
					return;
				if(&dst == &src)
				{
					result.insert(const_cast<Node*>(&src), pParentTreeNode);
					return;
				}
				src.EnterTraveling();
				{
					typename __PathTreeType::Node* pNewTreeNode = result.insert(const_cast<Node*>(&src), pParentTreeNode);
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;
						this->paths_node(*pNode, dst, result, pNewTreeNode);
					}
					if(result.leaf(*pNewTreeNode))
						result.erase(*pNewTreeNode);
				}
				src.LeaveTraveling();
			}
			GINL GAIA::GVOID paths_node(const Node& src, const _DataType& t, __PathTreeType& result, typename __PathTreeType::Node* pParentTreeNode) const
			{
				if(src.m_bTraveling)
					return;
				if(src.m_t == t)
				{
					result.insert(const_cast<Node*>(&src), pParentTreeNode);
					return;
				}
				src.EnterTraveling();
				{
					typename __PathTreeType::Node* pNewTreeNode = result.insert(const_cast<Node*>(&src), pParentTreeNode);
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;
						this->paths_node(*pNode, t, result, pNewTreeNode);
					}
					if(result.leaf(*pNewTreeNode))
						result.erase(*pNewTreeNode);
				}
				src.LeaveTraveling();
			}
		private:
			Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif