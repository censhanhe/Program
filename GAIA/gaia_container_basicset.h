#ifndef 	__GAIA_CONTAINER_BASICSET_H__
#define 	__GAIA_CONTAINER_BASICSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> class BasicSet
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicSet<_DataType, _SizeType, _HeightType, _SizeIncreaserType> __MyType;
			typedef BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType> __AVLTreeType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicSet;
			public:
				GINL it(){}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual _DataType& operator * (){return *m_iter;}
				GINL virtual const _DataType& operator * () const{return *m_iter;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){++m_iter; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){--m_iter; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::it m_iter;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicSet;
			public:
				GINL const_it(){}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual const _DataType& operator * () const{return *m_iter;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){++m_iter; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){--m_iter; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::const_it m_iter;
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
			GINL it lower_bound(const _DataType& t){it ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL it upper_bound(const _DataType& t){it ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL const_it lower_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL const_it upper_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL it front_it(){it ret; ret.m_iter = m_avltree.front_it(); return ret;}
			GINL it back_it(){it ret; ret.m_iter = m_avltree.back_it(); return ret;}
			GINL const_it const_front_it() const{const_it ret; ret.m_iter = m_avltree.const_front_it(); return ret;}
			GINL const_it const_back_it() const{const_it ret; ret.m_iter = m_avltree.const_back_it(); return ret;}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
