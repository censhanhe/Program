#ifndef 	__GAIA_CONTAINER_AVLTREE_H__
#define 	__GAIA_CONTAINER_AVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class AVLTree
		{
		public:
			GINL GAIA::BL empty() const;
			GINL _SizeType size() const;
			GINL _SizeType capacity() const;
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID destroy();
			GINL GAIA::GVOID insert();
			GINL GAIA::GVOID erase();
			GINL GAIA::GVOID find() const;
			GINL GAIA::GVOID lower_bound() const;
			GINL GAIA::GVOID upper_bound() const;
			GINL GAIA::GVOID front_prev();
			GINL GAIA::GVOID back_prev();
			GINL GAIA::GVOID front_mid();
			GINL GAIA::GVOID back_mid();
			GINL GAIA::GVOID front_next();
			GINL GAIA::GVOID back_next();
		private:
			class Node
			{
			public:
				_DataType t;
				_HeightType h;
				Node* pPrev;
				Node* pNext;
			};
		private:
			GINL GAIA::GVOID rotate_left();
			GINL GAIA::GVOID rotate_right();
		private:
			Node* m_pRoot;
			BasicPool<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> m_pool;
		};
	};
};

#endif
