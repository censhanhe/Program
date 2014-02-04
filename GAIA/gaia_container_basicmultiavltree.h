#ifndef		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__
#define		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMultiAVLTree
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMultiAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
		public:
			GINL BasicMultiAVLTree(){this->init();}
			GINL BasicMultiAVLTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicMultiAVLTree(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL GAIA::BL insert(const _DataType& t){}
			GINL GAIA::BL erase(const _DataType& t){}
			GINL _DataType* find(const _DataType& t){}
			GINL const _DataType* find(const _DataType& t) const{}
			GINL GAIA::GVOID lower_bound(const _DataType& t) const{}
			GINL GAIA::GVOID upper_bound(const _DataType& t) const{}
			GINL const _DataType* minimize() const{}
			GINL _DataType* minimize(){}
			GINL const _DataType* maximize() const{}
			GINL _DataType* maximize(){}
			GINL GAIA::GVOID front_iterator(){}
			GINL GAIA::GVOID back_iterator(){}
			GINL GAIA::GVOID const_front_iterator(){}
			GINL GAIA::GVOID const_back_iterator(){}
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
			GINL GAIA::GVOID init(){}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif