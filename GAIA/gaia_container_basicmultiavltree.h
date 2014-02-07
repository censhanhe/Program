#ifndef		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__
#define		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMultiAVLTree
		{
		private:
			friend class BidirectionalIterator;
			friend class ConstBidirectionalIterator;
		public:
			class Node
			{
			private:
				friend class BasicMultiAVLTree;
			public:
				typedef BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __DataListType;
			public:
				GINL GAIA::BL operator == (const Node& src) const
				{
					if(m_datas.front() == src.m_datas.front())
						return GAIA::True;
					return GAIA::False;
				}
				GINL GAIA::BL operator != (const Node& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const Node& src) const{return !(this->operator < (src));}
				GINL GAIA::BL operator <= (const Node& src) const{return !(this->operator > (src));}
				GINL GAIA::BL operator > (const Node& src) const
				{
					if(m_datas.front() > src.m_datas.front())
						return GAIA::True;
					return GAIA::False;
				}
				GINL GAIA::BL operator < (const Node& src) const
				{
					if(m_datas.front() < src.m_datas.front())
						return GAIA::True;
					return GAIA::False;
				}
				GINL Node& operator = (const Node& src){m_datas = src.m_datas; return *this;}
			private:
				__DataListType m_datas;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMultiAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
		public:
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicMultiAVLTree;
			public:
				GINL BidirectionalIterator(){}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{return m_iter_d.empty();}
				GINL virtual _DataType& operator * (){return *m_iter_d;}
				GINL virtual const _DataType& operator * () const{return *m_iter_d;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					++m_iter_d;
					if(m_iter_d.empty())
					{
						++m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.front_iterator();
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					--m_iter_d;
					if(m_iter_d.empty())
					{
						--m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.back_iterator();
					}
					return *this;
				}
				GINL GAIA::BL operator == (const BidirectionalIterator& src) const
				{
					if(m_iter_n == src.m_iter_n && m_iter_d == src.m_iter_d)
						return GAIA::True;
					return GAIA::False;
				}
				GINL GAIA::BL operator != (const BidirectionalIterator& src) const{return !(*this == src);}
				GINL GAIA::BL operator >= (const BidirectionalIterator& src) const
				{
					if(m_iter_n > src.m_iter_n)
						return GAIA::True;
					else if(m_iter_n < src.m_iter_n)
						return GAIA::False;
					else
					{
						if(m_iter_d >= src.m_iter_d)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator <= (const BidirectionalIterator& src) const
				{
					if(m_iter_n < src.m_iter_n)
						return GAIA::True;
					else if(m_iter_n > src.m_iter_n)
						return GAIA::False;
					else
					{
						if(m_iter_d <= src.m_iter_d)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator > (const BidirectionalIterator& src) const{return !(*this <= src);}
				GINL GAIA::BL operator < (const BidirectionalIterator& src) const{return !(*this >= src);}
				GINL BidirectionalIterator& operator = (const BidirectionalIterator& src){m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::BidirectionalIterator m_iter_n;
				typename Node::__DataListType::BidirectionalIterator m_iter_d;
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicMultiAVLTree;
			public:
				GINL ConstBidirectionalIterator(){}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{return m_iter_d.empty();}
				GINL virtual const _DataType& operator * () const{return *m_iter_d;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ ()
				{
					++m_iter_d;
					if(m_iter_d.empty())
					{
						++m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.const_front_iterator();
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- ()
				{
					--m_iter_d;
					if(m_iter_d.empty())
					{
						--m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.const_back_iterator();
					}
					return *this;
				}
				GINL GAIA::BL operator == (const ConstBidirectionalIterator& src) const
				{
					if(m_iter_n == src.m_iter_n && m_iter_d == src.m_iter_d)
						return GAIA::True;
					return GAIA::False;
				}
				GINL GAIA::BL operator != (const ConstBidirectionalIterator& src) const{return !(*this == src);}
				GINL GAIA::BL operator >= (const ConstBidirectionalIterator& src) const
				{
					if(m_iter_n > src.m_iter_n)
						return GAIA::True;
					else if(m_iter_n < src.m_iter_n)
						return GAIA::False;
					else
					{
						if(m_iter_d >= src.m_iter_d)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator <= (const ConstBidirectionalIterator& src) const
				{
					if(m_iter_n < src.m_iter_n)
						return GAIA::True;
					else if(m_iter_n > src.m_iter_n)
						return GAIA::False;
					else
					{
						if(m_iter_d <= src.m_iter_d)
							return GAIA::True;
						else
							return GAIA::False;
					}
				}
				GINL GAIA::BL operator > (const ConstBidirectionalIterator& src) const{return !(*this <= src);}
				GINL GAIA::BL operator < (const ConstBidirectionalIterator& src) const{return !(*this >= src);}
				GINL ConstBidirectionalIterator& operator = (const ConstBidirectionalIterator& src){m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::ConstBidirectionalIterator m_iter_n;
				typename Node::_DataListType::ConstBidirectionalIterator m_iter_d;
			};
		public:
			GINL BasicMultiAVLTree(){this->init();}
			GINL BasicMultiAVLTree(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicMultiAVLTree(){}
			GINL GAIA::BL empty() const{return m_avltree.empty();}
			GINL _SizeType size() const{return m_avltree.size();}
			GINL _SizeType capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID clear(){m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_avltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t)
			{
				Node* pN = this->find_node(t);
				if(pN == GNULL)
				{
					Node n;
					n.m_datas.push_back(t);
					return m_avltree.insert(n);
				}
				else
				{
					pN->m_datas.push_back(t);
					return GAIA::True;
				}
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				Node n;
				n.m_datas.push_back(t);
				return m_avltree.erase(n);
			}
			GINL GAIA::BL erase(const Pair<_DataType, _SizeType>& t)
			{
			}
			GINL _SizeType count() const
			{
			}
			GINL _DataType* find(const _DataType& t)
			{
				Node* pN = this->find_node(t);
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL const _DataType* find(const _DataType& t) const
			{
				const Node* pN = this->find_node(t);
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL GAIA::GVOID lower_bound(const _DataType& t) const{}
			GINL GAIA::GVOID upper_bound(const _DataType& t) const{}
			GINL const _DataType* minimize() const
			{
				const Node* pN = m_avltree.minimize();
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL _DataType* minimize()
			{
				Node* pN = m_avltree.minimize();
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL const _DataType* maximize() const
			{
				const Node* pN = m_avltree.maximize();
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL _DataType* maximize()
			{
				Node* pN = m_avltree.maximize();
				if(pN == GNULL)
					return GNULL;
				return &pN->m_datas.front();
			}
			GINL BidirectionalIterator front_iterator()
			{
				BidirectionalIterator iter;
				iter.m_iter_n = m_avltree.front_iterator();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.front_iterator();
				return iter;
			}
			GINL BidirectionalIterator back_iterator()
			{
				BidirectionalIterator iter;
				iter.m_iter_n = m_avltree.back_iterator();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.back_iterator();
				return iter;
			}
			GINL ConstBidirectionalIterator const_front_iterator()
			{
				ConstBidirectionalIterator iter;
				iter.m_iter_n = m_avltree.const_front_iterator();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_front_iterator();
				return iter;
			}
			GINL ConstBidirectionalIterator const_back_iterator()
			{
				ConstBidirectionalIterator iter;
				iter.m_iter_n = m_avltree.const_back_iterator();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_back_iterator();
				return iter;
			}
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
			GINL __MyType& operator = (const __MyType& src){m_avltree = src.m_avltree; return *this;}
		private:
			GINL GAIA::GVOID init(){}
			GINL Node* find_node(const _DataType& t)
			{
				Node n;
				n.m_datas.push_back(t);
				return m_avltree.find(n);
			}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
