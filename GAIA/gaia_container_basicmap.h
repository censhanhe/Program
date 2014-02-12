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
				friend class BasicMap;
			public:
				GINL Node(){}
				GINL Node(const Node& src){this->operator = (src);}
				GINL ~Node(){}
				GINL GAIA::BL operator == (const Node& src) const{if(m_key == src.m_key) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const Node& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const Node& src) const{return !(this->operator > (src));}
				GINL GAIA::BL operator <= (const Node& src) const{return !(this->operator < (src));}
				GINL GAIA::BL operator > (const Node& src) const{if(m_key > src.m_key) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator < (const Node& src) const{if(m_key < src.m_key) return GAIA::True; return GAIA::False;}
				GINL Node& operator = (const Node& src){m_key = src.m_key; m_data = src.m_data; return *this;}
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
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMap<_DataType, _KeyType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
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
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
