#ifndef		__GAIA_CONTAINER_BASICTRIETREE_H__
#define		__GAIA_CONTAINER_BASICTRIETREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicTrieTree
		{
		public:
			class Node;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicVector<__NodeListType, _SizeType, _SizeIncreaserType> __PathListType;
		public:
			class Node
			{
			private:
				friend class BasicTrieTree;
			public:
				GINL _DataType& operator * (){return m_t;}
				GINL const _DataType& operator * () const{return m_t;}
			private:
				GINL GAIA::BL match_linked_index(const _DataType& t, _SizeType& result) const
				{
					for(_SizeType x = 0; x < m_links.size(); ++x)
					{
						if(m_links[x] == GNULL)
							continue;
						if(**m_links[x] == t)
						{
							result = x;
							return GAIA::True;
						}
					}
					return GAIA::False;
				}
				GINL GAIA::BL free_linked_index(_SizeType& result) const
				{
					if(m_links.empty())
						return GAIA::False;
					typename __NodeListType::_datatype* pTemp = GAIA::ALGORITHM::find(m_links.front_ptr(), m_links.back_ptr(), (typename __NodeListType::_datatype)GNULL);
					if(pTemp == GNULL)
						return GAIA::False;
					GAIA::ALGORITHM::index(m_links.front_ptr(), pTemp, result);
					return GAIA::True;
				}
			private:
				Node* m_pParent;
				__NodeListType m_links;
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
			typedef BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicTrieTree(){this->init();}
			GINL BasicTrieTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTrieTree(){}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID resize(const _SizeType& size) const{}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID clear(){this->init(); m_root.m_links.clear(); m_pool.clear();}
			GINL GAIA::GVOID destroy(){this->init(); m_root.m_links.destroy(); m_pool.destroy();}
			GINL GAIA::GVOID insert(const _DataType* p, const _SizeType& size)
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				if(this->insert_node(m_root, p, size))
					++m_root.m_category_count;
			}
			GINL GAIA::BL erase(const _DataType* p, const _SizeType& size)
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
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
							{
								for(_SizeType x = 0; x < pNode->m_pParent->m_links.size(); ++x)
								{
									if(pNode->m_pParent->m_links[x] == pNode)
									{
										pNode->m_pParent->m_links[x] = GNULL;
										break;
									}
								}
							}
							m_pool.release(pNode);
						}
						pNode = pNode->m_pParent;
					}
				}
				return GAIA::True;
			}
			GINL GAIA::BL exist(const _DataType* p, const _SizeType& size) const
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				Node* pFinded = this->match_node(m_root, p, size);
				if(pFinded == GNULL)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL leaf(const _DataType* p, const _SizeType& size) const
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				Node* pFinded = this->match_node(m_root, p, size);
				if(pFinded != GNULL)
				{
					if(pFinded->m_links.size() == pFinded->m_links.count(GNULL))
						return GAIA::True;
					else
						return GAIA::False;
				}
				return GAIA::False;
			}
			GINL Node* find(const Node* pNode, const _DataType* p, const _SizeType& size) const
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				return this->match_node(pNode == GNULL? m_root : *pNode, p, size);
			}
			GINL GAIA::GVOID paths(const Node* pNode, const _DataType* p, const _SizeType& size, __PathListType& result) const
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				Node* pTempNode = this->match_node(pNode == GNULL ? m_root : *pNode, p, size);
				if(pTempNode == GNULL)
					return;
			}
			GINL _SizeType count(Node& n) const{return n.m_count;}
			GINL _SizeType catagory_count(Node& n) const{return n.m_category_count;}
			GINL _SizeType full_count(Node& n) const{return n.m_full_count;}
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
				_SizeType index;
				if(n.match_linked_index(*p, index))
				{
					if(this->insert_node(*n.m_links[index], p + 1, size - 1))
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
					if(n.free_linked_index(index))
						n.m_links[index] = pNew;
					else
						n.m_links.push_back(pNew);
					ret = GAIA::True;
					this->insert_node(*pNew, p + 1, size - 1);
					pNew->m_full_count = 1;
				}
				return ret;
			}
			GINL Node* match_node(const Node& n, const _DataType* p, const _SizeType& size) const
			{
				GAIA_ASSERT(p != GNULL);
				GAIA_ASSERT(size > 0);
				const _DataType* pTemp = p;
				_SizeType sizetemp = size;
				const Node* pNodeTemp = &n;
				while(GAIA::ALWAYSTRUE)
				{
					_SizeType index;
					if(pNodeTemp->match_linked_index(*pTemp, index))
					{
						pNodeTemp = pNodeTemp->m_links[index];
						++pTemp;
						--sizetemp;
					}
					else
						return GNULL;
					if(sizetemp == 0)
						return const_cast<Node*>(pNodeTemp);
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