#ifndef 	__GAIA_CONTAINER_AVLTREE_H__
#define 	__GAIA_CONTAINER_AVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class AVLTree
		{
		public:
			GINL AVLTree(){m_pRoot = GNULL;}
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
					return bResult;
				}
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				if(m_pRoot == GNULL)
					return GAIA::False;
				GAIA::BL bResult = GAIA::False;
				m_pRoot = this->erase_node(m_pRoot, t, bResult);
				return bResult;
			}
			GINL GAIA::BL exist(const _DataType& t) const
			{
				if(m_pRoot == GNULL)
					return GAIA::False;
				return this->exist_node(m_pRoot, t);
			}
			GINL GAIA::GVOID lower_bound() const{}
			GINL GAIA::GVOID upper_bound() const{}
			GINL GAIA::GVOID front_prev(){}
			GINL GAIA::GVOID back_prev(){}
			GINL GAIA::GVOID front_mid(){}
			GINL GAIA::GVOID back_mid(){}
			GINL GAIA::GVOID front_next(){}
			GINL GAIA::GVOID back_next(){}
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
		private:
			GINL GAIA::GVOID rotate_prev(Node*& pNode)
			{
				Node* pTemp = pNode->pNext;
				pNode->pNext = pTemp->pPrev;
				pTemp->pPrev = pNode;
				pNode->h = this->height(pNode);
				pTemp->h = this->height(pTemp);
				pNode = pTemp;
			}
			GINL GAIA::GVOID rotate_next(Node*& pNode)
			{
				Node* pTemp = pNode->pPrev;
				pNode->pPrev = pTemp->pNext;
				pTemp->pNext = pNode;
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
			GINL const _DataType& findmin(Node* pNode)
			{
				if(pNode->pPrev == GNULL)
					return pNode->t;
				return this->findmin(pNode->pPrev);
			}
			GINL const _DataType& findmax(Node* pNode)
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
					pNode->pPrev = this->insert_node(pNode->pPrev, t, bResult);
				else if(t > pNode->t)
					pNode->pNext = this->insert_node(pNode->pNext, t, bResult);
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
					pNode->pPrev = this->erase_node(pNode->pPrev, t, bResult);
				else if(t > pNode->t)
					pNode->pNext = this->erase_node(pNode->pNext, t, bResult);
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
						Node* pTemp = pNode;
						pNode = pNode->pPrev;
						m_pool.release(pTemp);
						return pNode;
					}
					else if(pNode->pPrev == GNULL && pNode->pNext != GNULL)
					{
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
					}
				}
				pNode->h = this->height(pNode);
				this->balance(pNode);
				return pNode;
			}
			GINL GAIA::BL exist_node(Node* pNode, const _DataType& t) const
			{
				if(t < pNode->t)
				{
					if(pNode->pPrev != GNULL)
						return this->exist_node(pNode->pPrev, t);
				}
				else if(t > pNode->t)
				{
					if(pNode->pNext != GNULL)
						return this->exist_node(pNode->pNext, t);
				}
				else
					return GAIA::True;
				return GAIA::False;
			}
		private:
			Node* m_pRoot;
			BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> m_pool;
		};
	};
};

#endif
