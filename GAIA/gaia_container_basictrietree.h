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
			typedef GAIA::CONTAINER::BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeList;
		public:
			class Node
			{
			public:
				
			private:
				Node* m_pParent;
				__NodeList m_links;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef GAIA::CONTAINER::BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicTrieTree(){this->init();}
			GINL BasicTrieTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicTrieTree(){}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL GAIA::GVOID resize(const _SizeType& size) const{}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID clear(){m_pool.clear();}
			GINL GAIA::GVOID destroy(){m_pool.destroy();}
			GINL GAIA::GVOID insert();
			GINL GAIA::GVOID erase();
			GINL GAIA::GVOID exist();
			GINL GAIA::GVOID count();
			GINL GAIA::GVOID find();
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){m_pRoot = GNULL;}
		private:
			Node* m_pRoot;
			__PoolType m_pool;
		};
	};
};

#endif