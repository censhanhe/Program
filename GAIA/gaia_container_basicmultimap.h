#ifndef		__GAIA_CONTAINER_BASICMULTIMAP_H__
#define		__GAIA_CONTAINER_BASICMULTIMAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _KeyType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> class BasicMultiMap : public GAIA::Base
		{
		public:
			class Node
			{
			private:
				friend class BasicMultiMap;
			public:
				GINL Node(){}
				GINL ~Node(){}
				GAIA_CLASS_OPERATOR_COMPARE(m_key, m_key, Node);
				GINL Node& operator = (const Node& src){m_key = src.m_key; m_data = src.m_data; return *this;}
			private:
				_KeyType m_key;
				_DataType m_data;
			};
		public:
			typedef _DataType _datatype;
			typedef _KeyType _keytype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicMultiMap<_DataType, _KeyType, _SizeType, _HeightType, _SizeIncreaserType> __MyType;
			typedef BasicMultiAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType> __MultiAVLTreeType;
			typedef BasicVector<Pair<_DataType, _SizeType>, _SizeType, _SizeIncreaserType> __DataListType;
		public:
			GINL BasicMultiMap(){}
			GINL BasicMultiMap(const __MyType& src){this->operator = (src);}
			GINL ~BasicMultiMap(){}
			GINL GAIA::BL empty() const{return m_mavltree.empty();}
			GINL const _SizeType& size() const{return m_mavltree.size();}
			GINL const _SizeType& capacity() const{return m_mavltree.capacity();}
			GINL GAIA::GVOID clear(){m_mavltree.clear();}
			GINL GAIA::GVOID destroy(){m_mavltree.destroy();}
			GINL GAIA::BL insert(const _KeyType& key, const _DataType& t)
			{
				Node n;
				n.m_key = key;
				n.m_data = t;
				return m_mavltree.insert(n);
			}
			GINL GAIA::BL erase(const _KeyType& key)
			{
				Node n;
				n.m_key = key;
				return m_mavltree.erase(n);
			}
			GINL GAIA::BL erase(const Pair<_KeyType, _SizeType>& t)
			{
				Node n;
				n.m_key = t.front();
				Pair<Node, _SizeType> pr(n, t.back());
				return m_mavltree.erase(pr);
			}
			GINL GAIA::BL find(const _DataType& t, __DataListType& result) const
			{
				BasicVector<Pair<Node, _SizeType>, _SizeType, _SizeIncreaserType> lr;
				if(!m_mavltree.find(lr))
					return GAIA::False;
				for(_SizeType x = 0; x < lr.size(); ++x)
				{
					Pair<_DataType, _SizeType> pr(lr[x].front().m_data, lr[x].back());
					result.push_back(pr);
				}
				return GAIA::True;
			}
			GINL __MyType& operator = (const __MyType& src){m_mavltree = src.m_mavltree; return *this;}
		private:
			__MultiAVLTreeType m_mavltree;
		};
	};
};

#endif
