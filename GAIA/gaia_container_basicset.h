#ifndef 	__GAIA_CONTAINER_BASICSET_H__
#define 	__GAIA_CONTAINER_BASICSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> class BasicSet : public GAIA::Base
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
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){m_iter = src.m_iter; return *this;}
				GINL it& operator += (const _SizeType& c){m_iter += c; return *this;}
				GINL it& operator -= (const _SizeType& c){m_iter -= c; return *this;}
				GINL it operator + (const _SizeType& c) const{it ret = *this; ret += c; return ret;}
				GINL it operator - (const _SizeType& c) const{it ret = *this; ret -= c; return ret;}
				GINL _SizeType operator - (const it& src) const{return m_iter - src.m_iter;}
				GAIA_CLASS_OPERATOR_COMPARE(m_iter, m_iter, it);
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
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){m_iter = src.m_iter; return *this;}
				GINL const_it& operator += (const _SizeType& c){m_iter += c; return *this;}
				GINL const_it& operator -= (const _SizeType& c){m_iter -= c; return *this;}
				GINL const_it operator + (const _SizeType& c) const{const_it ret = *this; ret += c; return ret;}
				GINL const_it operator - (const _SizeType& c) const{const_it ret = *this; ret -= c; return ret;}
				GINL _SizeType operator - (const const_it& src) const{return m_iter - src.m_iter;}
				GAIA_CLASS_OPERATOR_COMPARE(m_iter, m_iter, const_it);
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
			GINL const _SizeType& capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID clear(){m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_avltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t){return m_avltree.insert(t);}
			GINL GAIA::BL erase(const _DataType& t){return m_avltree.erase(t);}
			GINL _DataType* find(const _DataType& t){return m_avltree.find(t);}
			GINL const _DataType* find(const _DataType& t) const{return m_avltree.find(t);}
			GINL it lower_bound(const _DataType& t){it ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL it upper_bound(const _DataType& t){it ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL const_it lower_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_avltree.lower_bound(t); return ret;}
			GINL const_it upper_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_avltree.upper_bound(t); return ret;}
			GINL it front_it(){it ret; ret.m_iter = m_avltree.front_it(); return ret;}
			GINL it back_it(){it ret; ret.m_iter = m_avltree.back_it(); return ret;}
			GINL const_it const_front_it() const{const_it ret; ret.m_iter = m_avltree.const_front_it(); return ret;}
			GINL const_it const_back_it() const{const_it ret; ret.m_iter = m_avltree.const_back_it(); return ret;}
			GINL __MyType& operator = (const __MyType& src){m_avltree = src.m_avltree; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(m_avltree, m_avltree, __MyType);
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
