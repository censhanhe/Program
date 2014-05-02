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
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicMultiMap;
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
				GINL it& operator += (const _SizeType& c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL it operator + (const _SizeType& c) const
				{
					it ret = *this;
					ret += c;
					return ret;
				}
				GINL it operator - (const _SizeType& c) const
				{
					it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					it iter = *this;
					_SizeType ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						++ret;
						--iter;
					}
					iter = *this;
					ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						--ret;
						++iter;
					}
					return ret;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_iter, m_iter, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __MultiAVLTreeType::it m_iter;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicMultiMap;
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
				GINL const_it& operator += (const _SizeType& c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					GAIA_AST(!this->empty());
					if(this->empty())
						return *this;
					while(c > 0)
					{
						--(*this);
						if(this->empty())
							return *this;
						--c;
					}
					while(c < 0)
					{
						++(*this);
						if(this->empty())
							return *this;
						++c;
					}
					return *this;
				}
				GINL const_it operator + (const _SizeType& c) const
				{
					const_it ret = *this;
					ret += c;
					return ret;
				}
				GINL const_it operator - (const _SizeType& c) const
				{
					const_it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const const_it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					const_it iter = *this;
					_SizeType ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						++ret;
						--iter;
					}
					iter = *this;
					ret = 0;
					while(!iter.empty())
					{
						if(iter == src)
							return ret;
						--ret;
						++iter;
					}
					return ret;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_iter, m_iter, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				typename __MultiAVLTreeType::const_it m_iter;
			};
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
			GINL it lower_bound(const _DataType& t){it ret; ret.m_iter = m_mavltree.lower_bound(t); return ret;}
			GINL it upper_bound(const _DataType& t){it ret; ret.m_iter = m_mavltree.upper_bound(t); return ret;}
			GINL const_it lower_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_mavltree.lower_bound(t); return ret;}
			GINL const_it upper_bound(const _DataType& t) const{const_it ret; ret.m_iter = m_mavltree.upper_bound(t); return ret;}
			GINL __MyType& operator = (const __MyType& src){m_mavltree = src.m_mavltree; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(m_mavltree, m_mavltree, __MyType);
		private:
			__MultiAVLTreeType m_mavltree;
		};
	};
};

#endif
