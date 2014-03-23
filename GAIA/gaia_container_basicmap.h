#ifndef		__GAIA_CONTAINER_BASICMAP_H__
#define		__GAIA_CONTAINER_BASICMAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _KeyType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> class BasicMap : public GAIA::Base
		{
		public:
			class Node
			{
			private:
				friend class BasicMap;
			public:
				GINL Node(){}
				GINL Node(const Node& src){this->operator = (src);}
				GINL ~Node(){}
				GINL _DataType& data(){return m_data;}
				GINL const _DataType& data() const{return m_data;}
				GINL _KeyType& key(){return m_key;}
				GINL const _KeyType& key() const{return m_key;}
				GINL Node& operator = (const Node& src){m_key = src.m_key; m_data = src.m_data; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE(m_key, m_key, Node);
			private:
				_KeyType m_key;
				_DataType m_data;
			};
		public:
			typedef _DataType _datatype;
			typedef _KeyType _keytype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicMap<_DataType, _KeyType, _SizeType, _HeightType, _SizeIncreaserType> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType> __AVLTreeType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicMap;
			public:
				GINL it(){}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual _DataType& operator * (){return (*m_iter).data();}
				GINL virtual const _DataType& operator * () const{return (*m_iter).data();}
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
				friend class BasicMap;
			public:
				GINL const_it(){}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_iter.empty();}
				GINL virtual const _DataType& operator * () const{return (*m_iter).data();}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){++m_iter; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){--m_iter; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::const_it m_iter;
			};
		public:
			GINL BasicMap(){}
			GINL BasicMap(const __MyType& src){this->operator = (src);}
			GINL ~BasicMap(){}
			GINL GAIA::BL empty() const{return m_avltree.empty();}
			GINL _SizeType size() const{return m_avltree.size();}
			GINL _SizeType capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID clear(){m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_avltree.destroy();}
			GINL GAIA::BL erase(const _KeyType& key)
			{
				Node n;
				n.m_key = key;
				return m_avltree.erase(n);
			}
			GINL _DataType* operator [] (const _KeyType& key)
			{
				Node n;
				n.m_key = key;
				Node* pNode = m_avltree.find(n);
				if(pNode == GNULL)
				{
					m_avltree.insert(n);
					pNode = m_avltree.find(n);
				}
				return &pNode->m_data;
			}
			GINL const _DataType* operator [] (const _KeyType& key) const
			{
				Node n;
				n.m_key = key;
				Node* pNode = m_avltree.find(n);
				if(pNode == GNULL)
					return GNULL;
				return pNode->m_data;
			}
			GINL __MyType& operator = (const __MyType& src){m_avltree = src.m_avltree; return *this;}
			GINL it lower_bound(const _KeyType& key){it ret; Node f; f.m_key = key; ret.m_iter = m_avltree.lower_bound(f); return ret;}
			GINL it upper_bound(const _KeyType& key){it ret; Node f; f.m_key = key; ret.m_iter = m_avltree.upper_bound(f); return ret;}
			GINL const_it lower_bound(const _KeyType& key) const{const_it ret; Node f; f.m_key = key; ret.m_iter = m_avltree.lower_bound(f); return ret;}
			GINL const_it upper_bound(const _KeyType& key) const{const_it ret; Node f; f.m_key = key; ret.m_iter = m_avltree.upper_bound(f); return ret;}
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
