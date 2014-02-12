#ifndef 	__GAIA_CONTAINER_BASICSET_H__
#define 	__GAIA_CONTAINER_BASICSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicSet
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicSet<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
		public:
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
			public:
				GINL BidirectionalIterator(){}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{}
				GINL virtual _DataType& operator * (){}
				GINL virtual const _DataType& operator * () const{}
				GINL virtual Iterator& operator ++ (){}
				GINL virtual Iterator& operator -- (){}
			private:
				GINL virtual Iterator& operator ++ (GAIA::N32){}
				GINL virtual Iterator& operator -- (GAIA::N32){}
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			public:
				GINL ConstBidirectionalIterator(){}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{}
				GINL virtual const _DataType& operator * () const{}
				GINL virtual ConstIterator& operator ++ (){}
				GINL virtual ConstIterator& operator -- (){}
			private:
				GINL virtual ConstIterator& operator ++ (GAIA::N32){}
				GINL virtual ConstIterator& operator -- (GAIA::N32){}
			};
		public:
			GINL BasicSet(){}
			GINL BasicSet(const __MyType& src){this->operator = (src);}
			GINL ~BasicSet(){}
			GINL GAIA::BL empty() const{return m_avltree.empty();}
			GINL _SizeType size() const{return m_avltree.size();}
			GINL _SizeType capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID clear(){m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_avltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t){return m_avltree.insert(t);}
			GINL GAIA::BL erase(const _DataType& t){return m_avltree.erase(t);}
			GINL _DataType* find(const _DataType& t){return m_avltree.find(t);}
			GINL const _DataType* find(const _DataType& t) const{return m_avltree.find(t);}
			GINL __MyType& operator = (const __MyType& src){m_avltree = src.m_avltree; return *this;}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
