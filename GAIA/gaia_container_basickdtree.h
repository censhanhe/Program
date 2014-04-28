#ifndef		__GAIA_CONTAINER_BASICKDTREE_H__
#define		__GAIA_CONTAINER_BASICKDTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<
			typename _DataType, 
			typename _SizeType, 
			typename _HeightType,
			typename _SizeIncreaserType
		> class BasicKDTree : public GAIA::Base
		{
		public:
			class Node;
			class Split
			{
			private:
				friend class BasicKDTree;
			public:
				GINL Split(){}
				GINL ~Split(){}
			private:
				Node* m_pParent;
				Node* m_pLeft;
				Node* m_pRight;
			};
			class Node
			{
			private:
				friend class BasicKDTree;
			public:
				typedef BasicAVLTree<_DataType*, _SizeType, _HeightType, _SizeIncreaserType> __AVLTreeType;
			public:
				Node(){}
				~Node(){}
			private:
				__AVLTreeType m_avltree;
				Split* m_pParent;
				Split* m_pSplit;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicKDTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType> __NodePoolType;
			typedef BasicPool<Split, _SizeType, _SizeIncreaserType> __SplitPoolType;
			typedef BasicAVLTree<Pair<_DataType, Node*>, _SizeType, _HeightType, _SizeIncreaserType> __AVLTreeType;
		public:
			GINL BasicKDTree(){this->init();}
			GINL BasicKDTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicKDTree(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL const _SizeType& size() const{return m_size;}
			GINL GAIA::GVOID clear(){m_pRoot = GNULL; m_nodepool.clear(); m_splitpool.clear(); m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_pRoot = GNULL; m_nodepool.destroy(); m_splitpool.destroy(); m_avltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t)
			{
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				typename __AVLTreeType::_datatype pr(t, GNULL);
				typename __AVLTreeType::_datatype* pGlobalRec = m_avltree.find(pr);
				if(pGlobalRec == GNULL)
					return GAIA::False;
				Node* pNode = pGlobalRec->back();
				GAIA_AST(!!pNode);
				GAIA::BL ret = pNode->m_avltree.erase(&pGlobalRec->front());
				if(ret)
					--m_size;
				Split* pSplit = GNULL;
				while(pNode != GNULL || pSplit != GNULL)
				{
					if(pSplit != GNULL)
					{
						if(pSplit->m_pLeft == pNode)
							pSplit->m_pLeft = GNULL;
						else
							pSplit->m_pRight = GNULL;
						if(pSplit->m_pLeft != GNULL || pSplit->m_pRight != GNULL)
							break;
						else
						{
							pSplit->m_pParent->m_pSplit = GNULL;
							pNode = pSplit->m_pParent;
							m_splitpool.release(pSplit);
							pSplit = GNULL;
						}
					}
					else if(pNode != GNULL)
					{
						if(!pNode->m_avltree.empty())
							break;
						pSplit = pNode->m_pParent;
						m_nodepool.release(pNode);
						pNode = GNULL;
					}
				}
				return ret;
			}
			GINL _DataType* find(const _DataType& t){return m_avltree.find(t);}
			GINL const _DataType* find(const _DataType& t) const{return m_avltree.find(t);}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){m_pRoot = GNULL; m_size = 0;}
		private:
			Node* m_pRoot;
			_SizeType m_size;
			__NodePoolType m_nodepool;
			__SplitPoolType m_splitpool;
			__AVLTreeType m_avltree;
		};
	};
};

#endif
