#ifndef		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__
#define		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMultiAVLTree
		{
		private:
			friend class it;
			friend class const_it;
		public:
			class Node
			{
			private:
				friend class BasicMultiAVLTree;
				friend class it;
				friend class const_it;
			public:
				typedef BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __DataListType;
			public:
				GINL GAIA::BL operator == (const Node& src) const{return m_datas.front() == src.m_datas.front();}
				GINL GAIA::BL operator != (const Node& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const Node& src) const{return !(this->operator < (src));}
				GINL GAIA::BL operator <= (const Node& src) const{return !(this->operator > (src));}
				GINL GAIA::BL operator > (const Node& src) const{return m_datas.front() > src.m_datas.front();}
				GINL GAIA::BL operator < (const Node& src) const{return m_datas.front() < src.m_datas.front();}
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
			typedef BasicVector<Pair<_DataType, _SizeType>, _SizeType, _SizeIncreaserType> __DataListType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicMultiAVLTree;
			public:
				GINL it(){}
				GINL virtual ~it(){}
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
							m_iter_d = (*m_iter_n).m_datas.front_it();
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
							m_iter_d = (*m_iter_n).m_datas.back_it();
					}
					return *this;
				}
				GINL it& operator += (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
					{
						if(!this->empty())
							++(*this);
					}
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
					{
						if(!this->empty())
							--(*this);
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
				GINL it& operator = (const it& src){m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE2(m_iter_n, m_iter_n, m_iter_d, m_iter_d, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::it m_iter_n;
				typename Node::__DataListType::it m_iter_d;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicMultiAVLTree;
			public:
				GINL const_it(){}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_iter_d.empty();}
				GINL virtual const _DataType& operator * () const{return *m_iter_d;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ ()
				{
					++m_iter_d;
					if(m_iter_d.empty())
					{
						++m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.const_front_it();
					}
					return *this;
				}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- ()
				{
					--m_iter_d;
					if(m_iter_d.empty())
					{
						--m_iter_n;
						if(!m_iter_n.empty())
							m_iter_d = (*m_iter_n).m_datas.const_back_it();
					}
					return *this;
				}
				GINL const_it& operator += (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
						++(*this);
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					for(_SizeType x = 0; x < c; ++x)
						--(*this);
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
				GINL const_it& operator = (const const_it& src){m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
				GAIA_CLASS_OPERATOR_COMPARE2(m_iter_n, m_iter_n, m_iter_d, m_iter_d, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){--(*this); return *this;}
			private:
				typename __AVLTreeType::const_it m_iter_n;
				typename Node::__DataListType::const_it m_iter_d;
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
				Node* pN = this->find_node(t.front());
				if(pN == GNULL)
					return GAIA::False;
				if(t.back() >= pN->m_datas.size())
					return GAIA::False;
				typename Node::__DataListType::it iter = pN->m_datas.front_it();
				iter += t.back();
				pN->m_datas.erase(iter);
				return GAIA::True;
			}
			GINL _SizeType count(const _DataType& t) const
			{
				Node* pN = this->find_node(t);
				if(pN == GNULL)
					return 0;
				return pN->m_datas.size();
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
			GINL GAIA::BL find(const _DataType& t, __DataListType& result) const
			{
				const Node* pN = this->find_node(t);
				if(pN == GNULL)
					return GNULL;
				typename Node::__DataListType::const_it iter = pN->m_datas.const_front_it();
				if(iter.empty())
					return GAIA::False;
				_SizeType index = 0;
				while(!iter.empty())
				{
					Pair<_DataType, _SizeType> pr(*iter, index);
					result.push_back(pr);
					++index;
					++iter;
				}
				return GAIA::True;
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
			GINL it front_it()
			{
				it iter;
				iter.m_iter_n = m_avltree.front_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.front_it();
				return iter;
			}
			GINL it back_it()
			{
				it iter;
				iter.m_iter_n = m_avltree.back_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.back_it();
				return iter;
			}
			GINL const_it const_front_it()
			{
				const_it iter;
				iter.m_iter_n = m_avltree.const_front_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_front_it();
				return iter;
			}
			GINL const_it const_back_it()
			{
				const_it iter;
				iter.m_iter_n = m_avltree.const_back_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_back_it();
				return iter;
			}
			GINL GAIA::GVOID front_prev_it(){}
			GINL GAIA::GVOID back_prev_it(){}
			GINL GAIA::GVOID front_mid_it(){}
			GINL GAIA::GVOID back_mid_it(){}
			GINL GAIA::GVOID front_next_it(){}
			GINL GAIA::GVOID back_next_it(){}
			GINL GAIA::GVOID const_front_prev_it(){}
			GINL GAIA::GVOID const_back_prev_it(){}
			GINL GAIA::GVOID const_front_mid_it(){}
			GINL GAIA::GVOID const_back_mid_it(){}
			GINL GAIA::GVOID const_front_next_it(){}
			GINL GAIA::GVOID const_back_next_it(){}
			GINL __MyType& operator = (const __MyType& src){m_avltree = src.m_avltree; return *this;}
		private:
			GINL GAIA::GVOID init(){}
			GINL Node* find_node(const _DataType& t) const
			{
				Node n;
				n.m_datas.push_back(t);
				return const_cast<Node*>(m_avltree.find(n));
			}
		private:
			__AVLTreeType m_avltree;
		};
	};
};

#endif
