#ifndef		__GAIA_CONTAINER_BASICPRIQUEUE_H__
#define		__GAIA_CONTAINER_BASICPRIQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicPriQueue
		{
		public:
			class Node
			{
			public:
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicPriQueue<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeList;
			typedef BasicAVLTree<_DataType, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
		public:
			GINL BasicPriQueue(){this->init();}
			GINL BasicPriQueue(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicPriQueue(){}
			GINL GAIA::BL empty() const{return m_avltree.empty();}
			GINL _SizeType size() const{return m_avltree.size();}
			GINL _SizeType capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID resize(const _SizeType& size){return m_avltree.resize();}
			GINL GAIA::GVOID reserve(const _SizeType& size){return m_avltree.reserve();}
			GINL GAIA::GVOID clear(){return m_avltree.clear();}
			GINL GAIA::GVOID destroy(){return m_avltree.destroy();}
			GINL GAIA::GVOID insert(const _DataType& t);
			GINL GAIA::GVOID erase(Node& n);
			GINL GAIA::BL exist(const _DataType& t) const;
			GINL _SizeType count(const _DataType& t) const;
			GINL GAIA::GVOID find(const _DataType& t, __NodeList& result) const;
			GINL GAIA::GVOID push_front(const _DataType& t);
			GINL GAIA::GVOID pop_front();
			GINL GAIA::GVOID push_back(const _DataType& t);
			GINL GAIA::GVOID pop_back();
			GINL const _DataType& front() const;
			GINL _DataType& front();
			GINL const _DataType& back() const;
			GINL _DataType& back();
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif