#ifndef		__GAIA_CONTAINER_BASICGRAPH_H__
#define		__GAIA_CONTAINER_BASICGRAPH_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicGraph
		{
		public:
			class Node
			{
			private:
				friend class BasicGraph;
			public:
			#ifdef GAIA_DEBUG_INTERNALROUTINE
				Node(){m_traveling = GAIA::False;}
			#endif
			public:
				GINL GAIA::GVOID enter_traveling() const
				{
					GAIA_ASSERT(!m_traveling);
					(const_cast<Node*>(this))->m_traveling = GAIA::True;
				}
				GINL GAIA::GVOID leave_traveling() const
				{
					GAIA_ASSERT(m_traveling);
					(const_cast<Node*>(this))->m_traveling = GAIA::False;
				}
				GINL _DataType& operator * (){return m_t;}
				GINL const _DataType& operator * () const{return m_t;}
			private:
				_DataType m_t;
				BasicVector<Node*, _SizeType, _SizeIncreaserType> m_links;
				GAIA::BL m_traveling : 1;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicGraph<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicTree<Node*, _SizeType, _SizeIncreaserType, _GroupElementSize> __PathTreeType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
			typedef BasicVector<Pair<Node*, Node*>, _SizeType, GAIA::ALGORITHM::TwiceSizeIncreaser<_SizeType>> __LinkListType;
			typedef BasicStack<Node*, _SizeType, _SizeIncreaserType> __TravelingStackType;
		public:
			GINL BasicGraph(){this->init();}
			GINL BasicGraph(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicGraph(){}
			GINL GAIA::BL empty() const{return m_pRoot == GNULL;}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNULL; m_pool.destroy(); m_tstack.destroy();}
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
				pNew->m_traveling = GAIA::False;
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
				if(ppn1 == GNULL)
					n1.m_links.push_back(&n2);
				else
					*ppn1 = &n2;
				if(ppn2 == GNULL)
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
			GINL Node* getlink(const Node& n, const _SizeType& index) const{return n.m_links[index];}
			GINL GAIA::BL exist(const _DataType& t) const;
			GINL _SizeType count(const _DataType& t) const;
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
			GINL GAIA::GVOID anypath(const Node& src, const Node& dst, __NodeListType& result) const
			{
				result.clear();
				if(this->anypath_node(src, dst, result))
					GAIA::ALGORITHM::inverse(result.front_ptr(), result.back_ptr());
				this->reset_tstack();
			}
			GINL GAIA::GVOID anypath(const Node& src, const _DataType& t, __NodeListType& result) const
			{
				result.clear();
				if(this->anypath_node(src, t, result))
					GAIA::ALGORITHM::inverse(result.front_ptr(), result.back_ptr());
				this->reset_tstack();
			}
			template <typename _KeyType, _SizeType _MaxLinkCount> GINL GAIA::GVOID navpath(const Node& src, const Node& dst, __NodeListType& result) const
			{
				result.clear();
				if(this->navpath_node<_KeyType, _MaxLinkCount>(src, dst, result))
					GAIA::ALGORITHM::inverse(result.front_ptr(), result.back_ptr());
				this->reset_tstack();
			}
			template <typename _KeyType, _SizeType _MaxLinkCount> GINL GAIA::GVOID navpath(const Node& src, const _DataType& t, __NodeListType& result) const
			{
				result.clear();
				if(this->navpath_node<_KeyType, _MaxLinkCount>(src, t, result))
					GAIA::ALGORITHM::inverse(result.front_ptr(), result.back_ptr());
				this->reset_tstack();
			}
			GINL GAIA::GVOID collect_link_list(__LinkListType& result) const
			{
				result.clear();
				typename __PoolType::__IndexListType listIndex;
				this->collect_valid_index_list(listIndex);
				for(typename __PoolType::__IndexListType::_sizetype x = 0; x < listIndex.size(); ++x)
				{
					const Node& n = this->operator[](listIndex[x]);
					for(_SizeType y = 0; y < n.m_links.size(); ++y)
					{
						Node* pNext = n.m_links[y];
						if(pNext == GNULL)
							continue;
						GAIA::CONTAINER::Pair<Node*, Node*> rec;
						if(&n > pNext)
							rec.frontback(const_cast<Node*>(&n), pNext);
						else
							rec.frontback(pNext, const_cast<Node*>(&n));
						result.push_back(rec);
					}
				}
				result.sort();
				result.unique();
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
					if(t.m_traveling)
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
			GINL GAIA::GVOID reset_tstack() const
			{
				while(!m_tstack.empty())
				{
					Node* pNode = m_tstack.top();
					pNode->leave_traveling();
					const_cast<__MyType*>(this)->m_tstack.pop();
				}
			}
			GINL GAIA::GVOID find_node(const Node* pSrc, const _DataType& t, __NodeListType& result) const
			{
				if(pSrc->m_traveling)
					return;
				if(pSrc->m_t == t)
				{
					result.push_back(const_cast<Node*>(pSrc));
					return;
				}
				pSrc->enter_traveling();
				{
					for(_SizeType x = 0; x < pSrc->m_links.size(); ++x)
					{
						const Node* pNode = pSrc->m_links[x];
						if(pNode == GNULL)
							continue;
						this->find_node(pNode, t, result);
					}
				}
				pSrc->leave_traveling();
			}
			GINL GAIA::GVOID paths_node(const Node& src, const Node& dst, __PathTreeType& result, typename __PathTreeType::Node* pParentTreeNode) const
			{
				if(src.m_traveling)
					return;
				if(&dst == &src)
				{
					result.insert(const_cast<Node*>(&src), pParentTreeNode);
					return;
				}
				src.enter_traveling();
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
				src.leave_traveling();
			}
			GINL GAIA::GVOID paths_node(const Node& src, const _DataType& t, __PathTreeType& result, typename __PathTreeType::Node* pParentTreeNode) const
			{
				if(src.m_traveling)
					return;
				if(src.m_t == t)
				{
					result.insert(const_cast<Node*>(&src), pParentTreeNode);
					return;
				}
				src.enter_traveling();
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
				src.leave_traveling();
			}
			GINL GAIA::BL anypath_node(const Node& src, const Node& dst, __NodeListType& result) const
			{
				if(src.m_traveling)
					return GAIA::False;
				if(&dst == &src)
				{
					result.push_back(const_cast<Node*>(&src));
					return GAIA::True;
				}
				src.enter_traveling();
				{
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;
						if(this->anypath_node(*pNode, dst, result))
						{
							result.push_back(const_cast<Node*>(&src));
							src.leave_traveling();
							return GAIA::True;
						}
					}
				}
				if(src.m_links.size() - src.m_links.count(GNULL) <= 2)
					const_cast<__MyType*>(this)->m_tstack.push(const_cast<Node*>(&src));
				else
					src.leave_traveling();
				return GAIA::False;
			}
			GINL GAIA::BL anypath_node(const Node& src, const _DataType& t, __NodeListType& result) const
			{
				if(src.m_traveling)
					return GAIA::False;
				if(src.m_t == t)
				{
					result.push_back(const_cast<Node*>(&src));
					return GAIA::True;
				}
				src.enter_traveling();
				{
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;
						if(this->anypath_node(*pNode, t, result))
						{
							result.push_back(const_cast<Node*>(&src));
							src.leave_traveling();
							return GAIA::True;
						}
					}
				}
				if(src.m_links.size() - src.m_links.count(GNULL) <= 2)
					const_cast<__MyType*>(this)->m_tstack.push(const_cast<Node*>(&src));
				else
					src.leave_traveling();
				return GAIA::False;
			}
			template <typename _KeyType, _SizeType _MaxLinkCount> GINL GAIA::BL navpath_node(const Node& src, const Node& dst, __NodeListType& result) const
			{
				if(src.m_traveling)
					return GAIA::False;
				if(&dst == &src)
				{
					result.push_back(const_cast<Node*>(&src));
					return GAIA::True;
				}
				src.enter_traveling();
				{
					BasicArray<Pair<_KeyType, const Node*>, _SizeType, _MaxLinkCount> arrlink;
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;	
						arrlink.push_back(Pair<_KeyType, const Node*>(dst.m_t - pNode->m_t, pNode));
						GAIA_ASSERT(arrlink.size() < arrlink.capacity());
						if(arrlink.size() == arrlink.capacity())
							break;
					}
					arrlink.sort();
					for(_SizeType x = 0; x < arrlink.size(); ++x)
					{
						const Node* pNode = arrlink[x].back();
						if(pNode == GNULL)
							continue;
						if(this->navpath_node<_KeyType, _MaxLinkCount>(*pNode, dst, result))
						{
							result.push_back(const_cast<Node*>(&src));
							src.leave_traveling();
							return GAIA::True;
						}
					}
				}
				if(src.m_links.size() - src.m_links.count(GNULL) <= 2)
					const_cast<__MyType*>(this)->m_tstack.push(const_cast<Node*>(&src));
				else
					src.leave_traveling();
				return GAIA::False;
			}
			template <typename _KeyType, _SizeType _MaxLinkCount> GINL GAIA::BL navpath_node(const Node& src, const _DataType& t, __NodeListType& result) const
			{
				if(src.m_traveling)
					return GAIA::False;
				if(src.m_t == t)
				{
					result.push_back(const_cast<Node*>(&src));
					return GAIA::True;
				}
				src.enter_traveling();
				{
					BasicArray<Pair<_KeyType, const Node*>, _SizeType, _MaxLinkCount> arrlink;
					for(_SizeType x = 0; x < src.m_links.size(); ++x)
					{
						const Node* pNode = src.m_links[x];
						if(pNode == GNULL)
							continue;	
						arrlink.push_back(Pair<_KeyType, const Node*>(t - pNode->m_t, pNode));
						GAIA_ASSERT(arrlink.size() < arrlink.capacity());
						if(arrlink.size() == arrlink.capacity())
							break;
					}
					arrlink.sort();
					for(_SizeType x = 0; x < arrlink.size(); ++x)
					{
						const Node* pNode = arrlink[x].back();
						if(pNode == GNULL)
							continue;
						if(this->navpath_node<_KeyType, _MaxLinkCount>(*pNode, t, result))
						{
							result.push_back(const_cast<Node*>(&src));
							src.leave_traveling();
							return GAIA::True;
						}
					}
				}
				if(src.m_links.size() - src.m_links.count(GNULL) <= 2)
					const_cast<__MyType*>(this)->m_tstack.push(const_cast<Node*>(&src));
				else
					src.leave_traveling();
				return GAIA::False;
			}
		private:
			Node* m_pRoot;
			__PoolType m_pool;
			__TravelingStackType m_tstack;
		};
	};
};

#endif