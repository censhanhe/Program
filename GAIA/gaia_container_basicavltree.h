#ifndef 	__GAIA_CONTAINER_BASICAVLTREE_H__
#define 	__GAIA_CONTAINER_BASICAVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicAVLTree
		{
		private:
			friend class BidirectionalIterator;
			friend class ConstBidirectionalIterator;
		private:
			class Node
			{
			public:
				_DataType t;
				_HeightType h;
				Node* pPrev;
				Node* pNext;
				Node* pParent;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicAVLTree;
			public:
				GINL BidirectionalIterator(){m_pNode = GNULL; m_pAVLTree = GNULL;}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){return m_pNode->t;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					m_pNode = this->select_next(m_pNode);
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					m_pNode = this->select_prev(m_pNode);
					return *this;
				}
				GINL BidirectionalIterator& operator += (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
					{
						if(!this->empty())
							++(*this);
					}
					return *this;
				}
				GINL BidirectionalIterator& operator -= (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
					{
						if(!this->empty())
							--(*this);
					}
					return *this;
				}
				GINL BidirectionalIterator operator + (const _SizeType& c) const
				{
					BidirectionalIterator ret = *this;
					ret += c;
					return ret;
				}
				GINL BidirectionalIterator operator - (const _SizeType& c) const
				{
					BidirectionalIterator ret = *this;
					ret -= c;
					return ret;
				}
				GINL GAIA::BL operator == (const BidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::False;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t == src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator != (const BidirectionalIterator& src) const{return !(*this == src);}
				GINL GAIA::BL operator >= (const BidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t >= *src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator <= (const BidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t <= src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator > (const BidirectionalIterator& src) const{return !(*this <= src);}
				GINL GAIA::BL operator < (const BidirectionalIterator& src) const{return !(*this >= src);}
				GINL BidirectionalIterator& operator = (const BidirectionalIterator& src){m_pNode = src.m_pNode; m_pAVLTree = src.m_pAVLTree; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
				GINL Node* select_next(Node* pNode)
				{
					if(pNode->pNext != GNULL)
						pNode = m_pAVLTree->front_node(pNode->pNext);
					else
					{
						while(GAIA::ALWAYSTRUE)
						{
							if(pNode->pParent == GNULL)
							{
								pNode = GNULL;
								break;
							}
							else
							{
								if(pNode == pNode->pParent->pPrev)
								{
									pNode = pNode->pParent;
									break;
								}
								else
									pNode = pNode->pParent;
							}
						}
					}
					return pNode;
				}
				GINL Node* select_prev(Node* pNode)
				{
					if(pNode->pPrev != GNULL)
						pNode = m_pAVLTree->back_node(pNode->pPrev);
					else
					{
						while(GAIA::ALWAYSTRUE)
						{
							if(pNode->pParent == GNULL)
							{
								pNode = GNULL;
								break;
							}
							else
							{
								if(pNode == pNode->pParent->pNext)
								{
									pNode = pNode->pParent;
									break;
								}
								else
									pNode = pNode->pParent;
							}
						}
					}
					return pNode;
				}
			private:
				Node* m_pNode;
				__MyType* m_pAVLTree;
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicAVLTree;
			public:
				GINL ConstBidirectionalIterator(){m_pNode = GNULL; m_pAVLTree = GNULL;}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					if(m_pNode == GNULL)
						return *this;
					m_pNode = this->select_next(m_pNode);
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					if(m_pNode == GNULL)
						return *this;
					m_pNode = this->select_prev(m_pNode);
					return *this;
				}
				GINL ConstBidirectionalIterator& operator += (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
						++(*this);
					return *this;
				}
				GINL ConstBidirectionalIterator& operator -= (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
						--(*this);
					return *this;
				}
				GINL ConstBidirectionalIterator operator + (const _SizeType& c) const
				{
					ConstBidirectionalIterator ret = *this;
					ret += c;
					return ret;
				}
				GINL ConstBidirectionalIterator operator - (const _SizeType& c) const
				{
					ConstBidirectionalIterator ret = *this;
					ret -= c;
					return ret;
				}
				GINL GAIA::BL operator == (const ConstBidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::False;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t == src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator != (const ConstBidirectionalIterator& src) const{return !(*this == src);}
				GINL GAIA::BL operator >= (const ConstBidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t >= *src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator <= (const ConstBidirectionalIterator& src) const
				{
					if(m_pNode == GNULL && src.m_pNode == GNULL)
						return GAIA::True;
					else if(m_pNode == GNULL && src.m_pNode != GNULL)
						return GAIA::True;
					else if(m_pNode != GNULL && src.m_pNode == GNULL)
						return GAIA::False;
					else
					{
						if(m_pNode->t <= src.m_pNode->t)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator > (const ConstBidirectionalIterator& src) const{return !(*this <= src);}
				GINL GAIA::BL operator < (const ConstBidirectionalIterator& src) const{return !(*this >= src);}
				GINL ConstBidirectionalIterator& operator = (const ConstBidirectionalIterator& src){m_pNode = src.m_pNode; m_pAVLTree = src.m_pAVLTree; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
				GINL Node* select_next(Node* pNode)
				{
					if(pNode->pNext != GNULL)
						return this->select_prev(pNode->pNext);
					else
					{
						while(GAIA::ALWAYSTRUE)
						{
							if(pNode->pParent == GNULL)
							{
								pNode = GNULL;
								break;
							}
							else
							{
								if(pNode == pNode->pParent->pPrev)
									return this->select_next(pNode->pParent);
								else
									pNode = pNode->pParent;
							}
						}
					}
				}
				GINL Node* select_prev(Node* pNode)
				{
					if(pNode->pPrev != GNULL)
						return this->select_next(pNode->pPrev);
					else
					{
						while(GAIA::ALWAYSTRUE)
						{
							if(pNode->pParent == GNULL)
							{
								pNode = GNULL;
								break;
							}
							else
							{
								if(pNode == pNode->pParent->pNext)
									return this->select_prev(pNode->pParent);
								else
									pNode = pNode->pParent;
							}
						}
					}
				}
			private:
				const Node* m_pNode;
				const __MyType* m_pAVLTree;
			};
		public:
			GINL BasicAVLTree(){m_pRoot = GNULL;}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID clear(){m_pRoot = GNULL; m_pool.clear();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNULL; m_pool.destroy();}
			GINL GAIA::BL insert(const _DataType& t)
			{
				if(m_pRoot == GNULL)
				{
					m_pRoot = m_pool.alloc();
					m_pRoot->t = t;
					m_pRoot->h = 1;
					m_pRoot->pPrev = GNULL;
					m_pRoot->pNext = GNULL;
					m_pRoot->pParent = GNULL;
					return GAIA::True;
				}
				else
				{
					GAIA::BL bResult = GAIA::False;
					m_pRoot = this->insert_node(m_pRoot, t, bResult);
					m_pRoot->pParent = GNULL;
					return bResult;
				}
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				if(m_pRoot == GNULL)
					return GAIA::False;
				GAIA::BL bResult = GAIA::False;
				m_pRoot = this->erase_node(m_pRoot, t, bResult);
				if(m_pRoot != GNULL)
					m_pRoot->pParent = GNULL;
				return bResult;
			}
			GINL _DataType* find(const _DataType& t)
			{
				if(m_pRoot == GNULL)
					return GNULL;
				return this->find_node(m_pRoot, t);
			}
			GINL const _DataType* find(const _DataType& t) const
			{
				if(m_pRoot == GNULL)
					return GNULL;
				return this->find_node(m_pRoot, t);
			}
			GINL BidirectionalIterator lower_bound(const _DataType& t)
			{
				BidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
					return iter;
				}
				iter.m_pNode = this->lower_bound_node(m_pRoot, t);
				if(iter.m_pNode != GNULL)
					iter.m_pAVLTree = this;
				return iter;
			}
			GINL BidirectionalIterator upper_bound(const _DataType& t)
			{
				BidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
					return iter;
				}
				iter.m_pNode = this->upper_bound_node(m_pRoot, t);
				if(iter.m_pNode != GNULL)
					iter.m_pAVLTree = this;
				return iter;
			}
			GINL ConstBidirectionalIterator lower_bound(const _DataType& t) const
			{
				ConstBidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
					return iter;
				}
				iter.m_pNode = this->lower_bound_node(m_pRoot, t);
				if(iter.m_pNode != GNULL)
					iter.m_pAVLTree = this;
				return iter;
			}
			GINL ConstBidirectionalIterator upper_bound(const _DataType& t) const
			{
				ConstBidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
					return iter;
				}
				iter.m_pNode = this->upper_bound_node(m_pRoot, t);
				if(iter.m_pNode != GNULL)
					iter.m_pAVLTree = this;
				return iter;
			}
			GINL const _DataType* minimize() const{if(m_pRoot == GNULL) return GNULL; return &this->findmin(m_pRoot);}
			GINL _DataType* minimize(){if(m_pRoot == GNULL) return GNULL; return &this->findmin(m_pRoot);}
			GINL const _DataType* maximize() const{if(m_pRoot == GNULL) return GNULL; return &this->findmax(m_pRoot);}
			GINL _DataType* maximize(){if(m_pRoot == GNULL) return GNULL; return &this->findmax(m_pRoot);}
			GINL BidirectionalIterator front_iterator()
			{
				BidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
				}
				else
				{
					iter.m_pNode = this->front_node(m_pRoot);
					iter.m_pAVLTree = this;
				}
				return iter;
			}
			GINL BidirectionalIterator back_iterator()
			{
				BidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
				}
				else
				{
					iter.m_pNode = this->back_node(m_pRoot);
					iter.m_pAVLTree = this;
				}
				return iter;
			}
			GINL ConstBidirectionalIterator const_front_iterator() const
			{
				ConstBidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
				}
				else
				{
					iter.m_pNode = this->front_node(m_pRoot);
					iter.m_pAVLTree = this;
				}
				return iter;
			}
			GINL ConstBidirectionalIterator const_back_iterator() const
			{
				ConstBidirectionalIterator iter;
				if(m_pRoot == GNULL)
				{
					iter.m_pNode = GNULL;
					iter.m_pAVLTree = GNULL;
				}
				else
				{
					iter.m_pNode = this->back_node(m_pRoot);
					iter.m_pAVLTree = this;
				}
				return iter;
			}
			GINL GAIA::GVOID front_prev_iterator(){}
			GINL GAIA::GVOID back_prev_iterator(){}
			GINL GAIA::GVOID front_mid_iterator(){}
			GINL GAIA::GVOID back_mid_iterator(){}
			GINL GAIA::GVOID front_next_iterator(){}
			GINL GAIA::GVOID back_next_iterator(){}
			GINL GAIA::GVOID const_front_prev_iterator(){}
			GINL GAIA::GVOID const_back_prev_iterator(){}
			GINL GAIA::GVOID const_front_mid_iterator(){}
			GINL GAIA::GVOID const_back_mid_iterator(){}
			GINL GAIA::GVOID const_front_next_iterator(){}
			GINL GAIA::GVOID const_back_next_iterator(){}
		private:
			GINL GAIA::GVOID rotate_prev(Node*& pNode)
			{
				Node* pTemp = pNode->pNext;
				pNode->pNext = pTemp->pPrev;
				if(pNode->pNext != GNULL)
					pNode->pNext->pParent = pNode;
				pTemp->pPrev = pNode;
				if(pTemp->pPrev != GNULL)
					pTemp->pPrev->pParent = pTemp;
				pNode->h = this->height(pNode);
				pTemp->h = this->height(pTemp);
				pNode = pTemp;
			}
			GINL GAIA::GVOID rotate_next(Node*& pNode)
			{
				Node* pTemp = pNode->pPrev;
				pNode->pPrev = pTemp->pNext;
				if(pNode->pPrev != GNULL)
					pNode->pPrev->pParent = pNode;
				pTemp->pNext = pNode;
				if(pTemp->pNext != GNULL)
					pTemp->pNext->pParent = pTemp;
				pNode->h = this->height(pNode);
				pTemp->h = this->height(pTemp);
				pNode = pTemp;
			}
			GINL _HeightType height(Node* pNode)
			{
				_HeightType prevh = pNode->pPrev == GNULL ? 0 : pNode->pPrev->h;
				_HeightType nexth = pNode->pNext == GNULL ? 0 : pNode->pNext->h;
				return GAIA::ALGORITHM::maximize(prevh, nexth) + 1;
			}
			GINL _HeightType balance_factor(Node* pNode)
			{
				_HeightType prevh = pNode->pPrev == GNULL ? 0 : pNode->pPrev->h;
				_HeightType nexth = pNode->pNext == GNULL ? 0 : pNode->pNext->h;
				return prevh - nexth;
			}
			GINL GAIA::GVOID balance(Node*& pNode)
			{
				_HeightType prevh = pNode->pPrev == GNULL ? 0 : pNode->pPrev->h;
				_HeightType nexth = pNode->pNext == GNULL ? 0 : pNode->pNext->h;
				if(prevh - nexth > 1)
				{
					_HeightType prevnexth = pNode->pPrev->pNext == GNULL ? 0 : pNode->pPrev->pNext->h;
					_HeightType prevprevh = pNode->pPrev->pPrev == GNULL ? 0 : pNode->pPrev->pPrev->h;
					if(prevnexth > prevprevh)
						this->rotate_prev(pNode->pPrev);
					this->rotate_next(pNode);
				}
				else if(nexth - prevh > 1)
				{
					_HeightType nextprevh = pNode->pNext->pPrev == GNULL ? 0 : pNode->pNext->pPrev->h;
					_HeightType nextnexth = pNode->pNext->pNext == GNULL ? 0 : pNode->pNext->pNext->h;
					if(nextprevh > nextnexth)
						this->rotate_next(pNode->pNext);
					this->rotate_prev(pNode);
				}
			}
			GINL Node* front_node(Node* pNode) const
			{
				if(pNode->pPrev != GNULL)
					return this->front_node(pNode->pPrev);
				else
					return pNode;
			}
			GINL Node* back_node(Node* pNode) const
			{
				if(pNode->pNext != GNULL)
					return this->back_node(pNode->pNext);
				else
					return pNode;
			}
			GINL _DataType& findmin(Node* pNode) const
			{
				if(pNode->pPrev == GNULL)
					return pNode->t;
				return this->findmin(pNode->pPrev);
			}
			GINL _DataType& findmax(Node* pNode) const
			{
				if(pNode->pNext == GNULL)
					return pNode->t;
				return this->findmax(pNode->pNext);
			}
			GINL Node* insert_node(Node* pNode, const _DataType& t, GAIA::BL& bResult)
			{
				if(pNode == GNULL)
				{
					bResult = GAIA::True;
					Node* pNew = m_pool.alloc();
					pNew->t = t;
					pNew->h = 1;
					pNew->pPrev = GNULL;
					pNew->pNext = GNULL;
					pNew->pParent = GNULL;
					return pNew;
				}
				if(t < pNode->t)
				{
					pNode->pPrev = this->insert_node(pNode->pPrev, t, bResult);
					if(pNode->pPrev != GNULL)
						pNode->pPrev->pParent = pNode;
				}
				else if(t > pNode->t)
				{
					pNode->pNext = this->insert_node(pNode->pNext, t, bResult);
					if(pNode->pNext != GNULL)
						pNode->pNext->pParent = pNode;
				}
				else
					return pNode;
				pNode->h = this->height(pNode);
				this->balance(pNode);
				return pNode;
			}
			GINL Node* erase_node(Node* pNode, const _DataType& t, GAIA::BL& bResult)
			{
				if(pNode == GNULL)
					return GNULL;
				if(t < pNode->t)
				{
					pNode->pPrev = this->erase_node(pNode->pPrev, t, bResult);
					if(pNode->pPrev != GNULL)
						pNode->pPrev->pParent = pNode;
				}
				else if(t > pNode->t)
				{
					pNode->pNext = this->erase_node(pNode->pNext, t, bResult);
					if(pNode->pNext != GNULL)
						pNode->pNext->pParent = pNode;
				}
				else
				{
					bResult = GAIA::True;
					if(pNode->h == 1)
					{
						m_pool.release(pNode);
						return GNULL;
					}
					else if(pNode->pPrev != GNULL && pNode->pNext == GNULL)
					{
						pNode->pPrev->pParent = pNode->pParent;
						Node* pTemp = pNode;
						pNode = pNode->pPrev;
						m_pool.release(pTemp);
						return pNode;
					}
					else if(pNode->pPrev == GNULL && pNode->pNext != GNULL)
					{
						pNode->pNext->pParent = pNode->pParent;
						Node* pTemp = pNode;
						pNode = pNode->pNext;
						m_pool.release(pTemp);
						return pNode;
					}
					else if(pNode->pPrev != GNULL && pNode->pNext != GNULL)
					{
						const _DataType& mindata = this->findmin(pNode->pNext);
						pNode->t = mindata;
						pNode->pNext = this->erase_node(pNode->pNext, pNode->t, bResult);
						if(pNode->pNext != GNULL)
							pNode->pNext->pParent = pNode;
					}
				}
				pNode->h = this->height(pNode);
				this->balance(pNode);
				return pNode;
			}
			GINL _DataType* find_node(Node* pNode, const _DataType& t)
			{
				if(t < pNode->t)
				{
					if(pNode->pPrev != GNULL)
						return this->find_node(pNode->pPrev, t);
				}
				else if(t > pNode->t)
				{
					if(pNode->pNext != GNULL)
						return this->find_node(pNode->pNext, t);
				}
				else
					return &pNode->t;
				return GNULL;
			}
			GINL const _DataType* find_node(Node* pNode, const _DataType& t) const
			{
				if(t < pNode->t)
				{
					if(pNode->pPrev != GNULL)
						return this->find_node(pNode->pPrev, t);
				}
				else if(t > pNode->t)
				{
					if(pNode->pNext != GNULL)
						return this->find_node(pNode->pNext, t);
				}
				else
					return &pNode->t;
				return GNULL;
			}
			GINL Node* lower_bound_node(Node* pNode, const _DataType& t) const
			{
				if(pNode == GNULL)
					return GNULL;
				if(pNode->t < t)
					return this->lower_bound_node(pNode->pNext, t);
				else
				{
					Node* pNew = this->lower_bound_node(pNode->pPrev, t);
					if(pNew == GNULL)
						return pNode;
					return pNew;
				}
			}
			GINL Node* upper_bound_node(Node* pNode, const _DataType& t) const
			{
				if(pNode == GNULL)
					return GNULL;
				if(pNode->t > t)
					return this->upper_bound_node(pNode->pPrev, t);
				else
				{
					Node* pNew = this->upper_bound_node(pNode->pNext, t);
					if(pNew == GNULL)
						return pNode;
					return pNew;
				}
			}
		private:
			Node* m_pRoot;
			__PoolType m_pool;
		public:
		#ifdef GAIA_DEBUG_INTERNALROUTINE
			GINL GAIA::BL dbg_check_balance()
			{
				if(m_pRoot == GNULL)
					return GAIA::True;
				else
					return this->dbg_check_balance_node(m_pRoot);
			}
			GINL GAIA::BL dbg_check_balance_node(Node* pNode)
			{
				if(pNode == GNULL)
					return GAIA::True;
				_HeightType prevh = pNode->pPrev == GNULL ? 0 : pNode->pPrev->h;
				_HeightType nexth = pNode->pNext == GNULL ? 0 : pNode->pNext->h;
				if(prevh - nexth > 1 || nexth - prevh > 1)
					return GAIA::False;
				if(!this->dbg_check_balance_node(pNode->pPrev))
					return GAIA::False;
				if(!this->dbg_check_balance_node(pNode->pNext))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL dbg_check_parent()
			{
				if(m_pRoot == GNULL)
					return GAIA::True;
				else
				{
					if(m_pRoot->pParent != GNULL)
						return GAIA::False;
					return this->dbg_check_parent_node(m_pRoot);
				}
			}
			GINL GAIA::BL dbg_check_parent_node(Node* pNode)
			{
				if(pNode == GNULL)
					return GAIA::True;
				if(pNode->pPrev != GNULL)
				{
					if(pNode->pPrev->pParent != pNode)
						return GAIA::False;
				}
				if(pNode->pNext != GNULL)
				{
					if(pNode->pNext->pParent != pNode)
						return GAIA::False;
				}
				if(!this->dbg_check_parent_node(pNode->pPrev))
					return GAIA::False;
				if(!this->dbg_check_parent_node(pNode->pNext))
					return GAIA::False;
				return GAIA::True;
			}
		#endif
		};
	};
};

#endif