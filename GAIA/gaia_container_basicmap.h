#ifndef		__GAIA_CONTAINER_BASICMAP_H__
#define		__GAIA_CONTAINER_BASICMAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _KeyType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMap
		{
		public:
			class Node
			{
			private:
				_DataType m_data;
				_KeyType m_key;
			};
		public:
			typedef _DataType _datatype;
			typedef _KeyType _keytype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMap<_DataType, _KeyType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
		public:
			GINL BasicMap(){this->init();}
			GINL BasicMap(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicMap(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL GAIA::BL erase(const _KeyType& key){}
			GINL _DataType& operator [] (const _KeyType& key){}
			GINL const _DataType& operator [] (const _KeyType& key) const{}
		private:
			GAIA::GVOID init(){}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif