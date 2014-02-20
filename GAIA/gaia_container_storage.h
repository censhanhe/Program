#ifndef 	__GAIA_CONTAINER_STORAGE_H__
#define 	__GAIA_CONTAINER_STORAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType, typename _SizeIncreaserType, _SizeType _PageSize, _SizeType _GroupElementSize> class Storage
		{
		public:
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _pagesize = _PageSize;
		public:
			class Node
			{
			public:
				GINL Node(){}
				GINL Node(const Node& src){this->operator = (src);}
				GINL ~Node(){}
				GINL const _SizeType& head() const{return m_head;}
				GINL const _SizeType& size() const{return m_size;}
				GINL const _SizeType& capacity() const{return m_capacity;}
				GINL Node& operator = (const Node& src){m_head = src.m_head; m_size = src.m_size; m_capacity = src.m_capacity; return *this;}
				GINL GAIA::BL operator == (const Node& src) const{return m_head == src.m_head;}
				GINL GAIA::BL operator != (const Node& src) const{return m_head != src.m_head;}
				GINL GAIA::BL operator >= (const Node& src) const{return m_head >= src.m_head;}
				GINL GAIA::BL operator <= (const Node& src) const{return m_head <= src.m_head;}
				GINL GAIA::BL operator > (const Node& src) const{return m_head > src.m_head;}
				GINL GAIA::BL operator < (const Node& src) const{return m_head < src.m_head;}
			private:
				_SizeType m_head;
				_SizeType m_size;
				_SizeType m_capacity;
			};
			class NodeSize
			{
			public:
				GINL NodeSize(){this->init();}
				GINL NodeSize(const NodeSize& src){this->operator = (src);}
				GINL ~NodeSize(){}
				GINL GAIA::GVOID node(Node* pNode){m_pNode = pNode;}
				GINL const Node* node() const{return m_pNode;} 
				GINL NodeSize& operator = (const NodeSize& src){m_pNode = src.m_pNode; return *this;}
				GINL GAIA::BL operator == (const NodeSize& src) const{return m_pNode->size() == src.m_pNode->size();}
				GINL GAIA::BL operator != (const NodeSize& src) const{return m_pNode->size() != src.m_pNode->size();}
				GINL GAIA::BL operator >= (const NodeSize& src) const{return m_pNode->size() >= src.m_pNode->size();}
				GINL GAIA::BL operator <= (const NodeSize& src) const{return m_pNode->size() <= src.m_pNode->size();}
				GINL GAIA::BL operator > (const NodeSize& src) const{return m_pNode->size() > src.m_pNode->size();}
				GINL GAIA::BL operator < (const NodeSize& src) const{return m_pNode->size() < src.m_pNode->size();}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL;}
			private:
				Node* m_pNode;
			};
		public:
			typedef Storage<_SizeType, _SizeIncreaserType, _PageSize, _GroupElementSize> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
			typedef BasicAVLTree<NodeSize, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __SizeAVLTreeType;
		public:
			GINL Storage(){this->init();}
			GINL Storage(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~Storage(){}
			GINL GAIA::BL empty() const{return m_size == 0;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::BL increase_reserve(const _SizeType& start, const _SizeType& size)
			{
			}
			GINL GAIA::GVOID clear()
			{
			}
			GINL GAIA::GVOID destroy()
			{
			}
			GINL Node* insert(const _SizeType& size)
			{
			}
			GINL GAIA::BL erase(const _SizeType& head)
			{
			}
			GINL Node* find(const _SizeType& head) const
			{
			}
			GINL GAIA::GVOID optimize()
			{
			}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){m_size = 0; m_capacity = 0;}
		private:
			__AVLTreeType m_using_a;
			__SizeAVLTreeType m_free_s;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
