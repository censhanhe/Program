#ifndef		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__
#define		__GAIA_CONTAINER_BASICMULTIAVLTREE_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> class BasicMultiAVLTree : public GAIA::Entity
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
				typedef BasicVector<_DataType, _SizeType, _SizeIncreaserType> __DataListType;
			public:
				GINL GAIA::BL operator == (const Node& src) const{return m_datas.front() == src.m_datas.front();}
				GINL GAIA::BL operator != (const Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const Node& src) const{return !this->operator < (src);}
				GINL GAIA::BL operator <= (const Node& src) const{return !this->operator > (src);}
				GINL GAIA::BL operator > (const Node& src) const{return m_datas.front() > src.m_datas.front();}
				GINL GAIA::BL operator < (const Node& src) const{return m_datas.front() < src.m_datas.front();}
				GINL Node& operator = (const Node& src){GAIA_AST(&src != this); m_datas = src.m_datas; return *this;}
			private:
				__DataListType m_datas;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicMultiAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _HeightType, _SizeIncreaserType> __AVLTreeType;
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
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){GAIA_AST(&src != this); m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
				GINL it& operator += (_SizeType c)
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
				GINL it& operator -= (_SizeType c)
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
					for(; !iter.empty(); --iter)
					{
						if(iter == src)
							return ret;
						++ret;
					}
					iter = *this;
					ret = 0;
					for(; !iter.empty(); ++iter)
					{
						if(iter == src)
							return ret;
						--ret;
					}
					return ret;
				}
				GAIA_CLASS_OPERATOR_COMPARE2(m_iter_n, m_iter_n, m_iter_d, m_iter_d, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
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
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_iter_n = src.m_iter_n; m_iter_d = src.m_iter_d; return *this;}
				GINL const_it& operator += (_SizeType c)
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
				GINL const_it& operator -= (_SizeType c)
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
					for(; !iter.empty(); --iter)
					{
						if(iter == src)
							return ret;
						++ret;
					}
					iter = *this;
					ret = 0;
					for(; !iter.empty(); ++iter)
					{
						if(iter == src)
							return ret;
						--ret;
					}
					return ret;
				}
				GAIA_CLASS_OPERATOR_COMPARE2(m_iter_n, m_iter_n, m_iter_d, m_iter_d, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
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
			GINL const _SizeType& capacity() const{return m_avltree.capacity();}
			GINL GAIA::GVOID clear(){m_avltree.clear();}
			GINL GAIA::GVOID destroy(){m_avltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t)
			{
				Node* pN = this->find_node(t);
				if(pN == GNIL)
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
				if(pN == GNIL)
					return GAIA::False;
				if(t.back() >= pN->m_datas.size())
					return GAIA::False;
				return pN->m_datas.erase(t.back());
			}
			GINL _SizeType count(const _DataType& t) const
			{
				Node* pN = this->find_node(t);
				if(pN == GNIL)
					return 0;
				return pN->m_datas.size();
			}
			GINL _DataType* find(const _DataType& t)
			{
				Node* pN = this->find_node(t);
				if(pN == GNIL)
					return GNIL;
				return &pN->m_datas.front();
			}
			GINL const _DataType* find(const _DataType& t) const
			{
				const Node* pN = this->find_node(t);
				if(pN == GNIL)
					return GNIL;
				return &pN->m_datas.front();
			}
			GINL GAIA::BL find(const _DataType& t, __DataListType& result) const
			{
				const Node* pN = this->find_node(t);
				if(pN == GNIL)
					return GNIL;
				typename Node::__DataListType::const_it iter = pN->m_datas.const_front_it();
				if(iter.empty())
					return GAIA::False;
				_SizeType index = 0;
				for(; !iter.empty(); ++iter)
				{
					Pair<_DataType, _SizeType> pr(*iter, index);
					result.push_back(pr);
					++index;
				}
				return GAIA::True;
			}
			GINL it lower_bound(const _DataType& t)
			{
				it ret;
				Node n;
				n.m_datas.push_back(t);
				ret.m_iter_n = m_avltree.lower_bound(n);
				if(!ret.m_iter_n.empty())
					ret.m_iter_d = (*ret.m_iter_n).m_datas.front_it();
				return ret;
			}
			GINL it upper_bound(const _DataType& t)
			{
				it ret;
				Node n;
				n.m_datas.push_back(t);
				ret.m_iter_n = m_avltree.upper_bound(n);
				if(!ret.m_iter_n.empty())
					ret.m_iter_d = (*ret.m_iter_n).m_datas.front_it();
				return ret;
			}
			GINL const_it lower_bound(const _DataType& t) const
			{
				const_it ret;
				Node n;
				n.m_datas.push_back(t);
				ret.m_iter_n = m_avltree.lower_bound(n);
				if(!ret.m_iter_n.empty())
					ret.m_iter_d = (*ret.m_iter_n).m_datas.const_front_it();
				return ret;
			}
			GINL const_it upper_bound(const _DataType& t) const
			{
				const_it ret;
				Node n;
				n.m_datas.push_back(t);
				ret.m_iter_n = m_avltree.upper_bound(n);
				if(!ret.m_iter_n.empty())
					ret.m_iter_d = (*ret.m_iter_n).m_datas.const_back_it();
				return ret;
			}
			GINL const _DataType* minimize() const
			{
				const Node* pN = m_avltree.minimize();
				if(pN == GNIL)
					return GNIL;
				return &pN->m_datas.front();
			}
			GINL _DataType* minimize()
			{
				Node* pN = m_avltree.minimize();
				if(pN == GNIL)
					return GNIL;
				return &pN->m_datas.front();
			}
			GINL const _DataType* maximize() const
			{
				const Node* pN = m_avltree.maximize();
				if(pN == GNIL)
					return GNIL;
				return &pN->m_datas.front();
			}
			GINL _DataType* maximize()
			{
				Node* pN = m_avltree.maximize();
				if(pN == GNIL)
					return GNIL;
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
			GINL const_it const_front_it() const
			{
				const_it iter;
				iter.m_iter_n = m_avltree.const_front_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_front_it();
				return iter;
			}
			GINL const_it const_back_it() const
			{
				const_it iter;
				iter.m_iter_n = m_avltree.const_back_it();
				if(!iter.m_iter_n.empty())
					iter.m_iter_d = (*iter.m_iter_n).m_datas.const_back_it();
				return iter;
			}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); m_avltree = src.m_avltree; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(m_avltree, m_avltree, __MyType);
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
