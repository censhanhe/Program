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
			private:
				friend class BasicSet;
			public:
				GINL BidirectionalIterator(){}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual _DataType& operator * (){return *m_iter;}
				GINL virtual const _DataType& operator * () const{return *m_iter;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){++m_iter; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){--m_iter; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::BidirectionalIterator m_iter;
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicSet;
			public:
				GINL ConstBidirectionalIterator(){}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual const _DataType& operator * () const{return *m_iter;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){++m_iter; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){--m_iter; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::ConstBidirectionalIterator m_iter;
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
			GINL BidirectionalIterator lower_bound(const _DataType& t){BidirectionalIterator ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL BidirectionalIterator upper_bound(const _DataType& t){BidirectionalIterator ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL ConstBidirectionalIterator lower_bound(const _DataType& t) const{ConstBidirectionalIterator ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL ConstBidirectionalIterator upper_bound(const _DataType& t) const{ConstBidirectionalIterator ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL BidirectionalIterator front_iterator(){BidirectionalIterator ret; ret.m_iter = m_avltree.front_iterator(); return ret;}
			GINL BidirectionalIterator back_iterator(){BidirectionalIterator ret; ret.m_iter = m_avltree.back_iterator(); return ret;}
			GINL ConstBidirectionalIterator const_front_iterator() const{ConstBidirectionalIterator ret; ret.m_iter = m_avltree.front_iterator(); return ret;}
			GINL ConstBidirectionalIterator const_back_iterator() const{ConstBidirectionalIterator ret; ret.m_iter = m_avltree.back_iterator(); return ret;}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
