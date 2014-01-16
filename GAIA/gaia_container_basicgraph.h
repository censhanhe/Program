#ifndef		__GAIA_CONTAINER_BASICGRAPH_H__
#define		__GAIA_CONTAINER_BASICGRAPH_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _DistanceType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicGraph
		{
		public:
			template <typename _DataType, typename _DistanceType, typename _SizeType, typename _SizeIncreaserType> class Node
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
					(const_cast<Node<_DataType, _DistanceType, _SizeType, _SizeIncreaserType>*>(this))->m_bTraveling = GAIA::True;
				}
				GINL GAIA::GVOID LeaveTraveling() const
				{
					GAIA_ASSERT(m_bTraveling);
					(const_cast<Node<_DataType, _DistanceType, _SizeType, _SizeIncreaserType>*>(this))->m_bTraveling = GAIA::False;
				}
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
			typedef Node<_DataType, _DistanceType, _SizeType, _SizeIncreaserType> __Node;
			typedef BasicGraph<_DataType, _DistanceType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<__Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicTree<__Node*, _SizeType, _SizeIncreaserType, _GroupElementSize> __PathTreeType;
			typedef BasicPool<__Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
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
			GINL __Node* root(){return m_pRoot;}
			GINL const __Node* root() const{return m_pRoot;}
			GINL GAIA::GVOID root(__Node* pNewRoot){m_pRoot = pNewRoot;}
			GINL __Node* insert(const _DataType& t, __Node* pNode)
			{
				__Node* pNew = m_pool.alloc();
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
			GINL GAIA::GVOID erase(__Node& n)
			{
				for(_SizeType x = 0; x < n.m_links.size(); ++x)
				{
					__Node* pNode = n.m_links[x];
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
			GINL GAIA::BL link(__Node& n1, __Node& n2)
			{
				if(this->islinked(n1, n2))
					return GAIA::False;
				__Node** ppn1 = GNULL;
				__Node** ppn2 = GNULL;
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
			GINL GAIA::BL unlink(__Node& n1, __Node& n2)
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
			GINL GAIA::BL islinked(const __Node& n1, const __Node& n2) const
			{
				for(_SizeType x = 0; x < n1.m_links.size(); ++x)
				{
					if(n1.m_links[x] == &n2)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL _SizeType getlinksize(const __Node& n) const{return n.m_links.size();}
			GINL _SizeType getlinkcount(const __Node& n, __Node* p) const{return n.m_links.count(p);}
			GINL __Node* getlink(const __Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::GVOID find(const __Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc == GNULL)
					pSrc = m_pRoot;
				if(pSrc == GNULL)
					return;
				if(pSrc->m_bTraveling)
					return;
				if(pSrc->m_t == t)
					result.push_back(const_cast<__Node*>(pSrc));
				pSrc->EnterTraveling();
				{
					for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
					{
						const __Node* pNode = pSrc->m_links[x];
						if(pNode == GNULL)
							continue;
						this->find(pNode, t, result);
					}
				}
				pSrc->LeaveTraveling();
			}
			GINL GAIA::GVOID paths(const __Node& src, const __Node& dst, __PathTreeType& result) const
			{
				result.clear();
				this->paths_node(src, dst, result, GNULL);
			}
			GINL GAIA::GVOID paths(const __Node& src, const _DataType& t, __PathTreeType& result) const
			{
				result.clear();
				this->paths_node(src, t, result, GNULL);
			}
			GINL GAIA::GVOID paths(const _DataType& src, const _DataType& dst, __PathTreeType& result) const
			{
				result.clear();
				this->paths_node(src, dst, result, GNULL);
			}
			GINL GAIA::BL minimize(const __Node& src, const _DataType& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::BL maximize(const __Node& src, const _DataType& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::BL minimize(const __Node& src, const __Node& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::BL maximize(const __Node& src, const __Node& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::BL minimize(const _DataType& src, const _DataType& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::BL maximize(const _DataType& src, const _DataType& dst, __NodeListType& result, _DistanceType& dist) const;
			GINL GAIA::GVOID collect_valid_index_list(GAIA::CONTAINER::BasicVector<_SizeType, _SizeType, _SizeIncreaserType>& result) const{m_pool.collect_valid_index_list(result);}
			GINL _DataType& operator[](const _SizeType& index){return m_pool[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return m_pool[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				return *this;
			}
		public:
		#ifdef GAIA_DEBUG_INTERNALROUTINE
			GINL GAIA::BL dbg_check_traveling()
			{
				GAIA::CONTAINER::BasicVector<_SizeType, _SizeType, _SizeIncreaserType> result;
				m_pool.collect_valid_index_list(result);
				for(_SizeType x = 0; x < result.size(); ++x)
				{
					__Node& t = m_pool[result[x]];
					if(t.m_bTraveling)
						return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL dbg_check_relation()
			{
				GAIA::CONTAINER::BasicVector<_SizeType, _SizeType, _SizeIncreaserType> result;
				m_pool.collect_valid_index_list(result);
				for(_SizeType x = 0; x < result.size(); ++x)
				{
					__Node& t = m_pool[result[x]];
					for(_SizeType y = 0; y < t.m_links.size(); ++y)
					{
						__Node* pNode = t.m_links[y];
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
			GINL GAIA::GVOID paths_node(const __Node& src, const __Node& dst, __PathTreeType& result, typename __PathTreeType::__Node* pParentTreeNode) const
			{
				if(src.m_bTraveling)
					return;
				if(&dst == &src)
				{
					result.insert(const_cast<__Node*>(&src), pParentTreeNode);
					return;
				}
				src.EnterTraveling();
				{
					typename __PathTreeType::__Node* pNewTreeNode = result.insert(const_cast<__Node*>(&src), pParentTreeNode);
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const __Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;
						this->paths_node(*pNode, dst, result, pNewTreeNode);
					}
					if(result.getlinksize(*pNewTreeNode) == result.getlinkcount(*pNewTreeNode, GNULL))
						result.erase(*pNewTreeNode);
				}
				src.LeaveTraveling();
			}
			GINL GAIA::GVOID paths_node(const __Node& src, const _DataType& t, __PathTreeType& result, typename __PathTreeType::__Node* pParentTreeNode) const
			{
			}
			GINL GAIA::GVOID paths_node(const _DataType& src, const _DataType& dst, __PathTreeType& result, typename __PathTreeType::__Node* pParentTreeNode) const
			{
			}
		private:
			__Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif