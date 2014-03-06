#ifndef		__GAIA_CONTAINER_BASICLIST_H__
#define		__GAIA_CONTAINER_BASICLIST_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicList
		{
		private:
			class Node
			{
			public:
				_DataType t;
				Node* pNext;
				Node* pPrev;
			};
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicPool<Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicList;
			public:
				GINL it(){m_pNode = GNULL;}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){return m_pNode->t;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){m_pNode = m_pNode->pPrev; return *this;}
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
				GINL GAIA::BL operator == (const it& src) const{if(m_pNode == src.m_pNode) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const it& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const it& src) const{}
				GINL GAIA::BL operator <= (const it& src) const{}
				GINL GAIA::BL operator > (const it& src) const{}
				GINL GAIA::BL operator < (const it& src) const{}
				GINL it& operator = (const it& src){m_pNode = src.m_pNode; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){m_pNode = m_pNode->pPrev; return *this;}
			private:
				Node* m_pNode;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicList;
			public:
				GINL const_it(){m_pNode = GNULL;}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){m_pNode = m_pNode->pPrev; return *this;}
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
				GINL GAIA::BL operator == (const const_it& src) const{if(m_pNode == src.m_pNode) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const const_it& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const const_it& src) const{}
				GINL GAIA::BL operator <= (const const_it& src) const{}
				GINL GAIA::BL operator > (const const_it& src) const{}
				GINL GAIA::BL operator < (const const_it& src) const{}
				GINL const_it& operator = (const const_it& src){m_pNode = src.m_pNode; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){m_pNode = m_pNode->pPrev; return *this;}
			private:
				const Node* m_pNode;
			};
		public:
			GINL BasicList(){this->init();}
			GINL BasicList(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicList(){}
			GINL _SizeType capacity() const{return m_pool.capacity();}
			GINL _SizeType size() const{return m_pool.size();}
			GINL GAIA::BL empty() const{return m_pool.empty();}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID resize(const _SizeType& size){}
			GINL GAIA::GVOID destroy(){m_pFront = m_pBack = GNULL; m_pool.destroy();}
			GINL GAIA::GVOID clear(){m_pFront = m_pBack = GNULL; m_pool.clear();}
			GINL GAIA::GVOID insert(it& iter, const _DataType& t)
			{
				if(iter.empty())
				{
					if(m_pBack == GNULL)
					{
						m_pFront = m_pBack = m_pool.alloc();
						m_pBack->t = t;
						m_pBack->pPrev = GNULL;
						m_pBack->pNext = GNULL;
					}
					else
					{
						Node* pNew = m_pool.alloc();
						pNew->t = t;
						m_pBack->pNext = pNew;
						pNew->pPrev = m_pBack;
						pNew->pNext = GNULL;
						m_pBack = pNew;
					}
				}
				else
				{
					Node* pNew = m_pool.alloc();
					pNew->t = t;
					pNew->pNext = iter.m_pNode;
					pNew->pPrev = iter.m_pNode->pPrev;
					if(iter.m_pNode->pPrev != GNULL)
						iter.m_pNode->pPrev->pNext = pNew;
					else
						m_pFront = pNew;
					iter.m_pNode->pPrev = pNew;
				}
			}
			GINL GAIA::BL erase(it& iter)
			{
				if(iter.empty())
					return GAIA::False;
				if(iter.m_pNode == m_pFront)
				{
					m_pFront = m_pFront->pNext;
					if(m_pFront != GNULL)
						m_pFront->pPrev = GNULL;
				}
				if(iter.m_pNode == m_pBack)
				{
					m_pBack = m_pBack->pPrev;
					if(m_pBack != GNULL)
						m_pBack->pNext = GNULL;
				}
				Node* pErase = iter.m_pNode;
				++iter;
				m_pool.release(pErase);
				return GAIA::True;
			}
			GINL GAIA::GVOID swap(it& iter1, it& iter2){GAIA::ALGORITHM::swap(*iter1, *iter2);}
			GINL GAIA::GVOID push_front(const _DataType& t)
			{
				it iter;
				iter.m_pNode = m_pFront;
				this->insert(iter, t);
			}
			GINL GAIA::BL pop_front()
			{
				it iter;
				iter.m_pNode = m_pFront;
				return this->erase(iter);
			}
			GINL GAIA::GVOID push_back(const _DataType& t)
			{
				it iter;
				iter.m_pNode = GNULL;
				this->insert(iter, t);
			}
			GINL GAIA::BL pop_back()
			{
				it iter;
				iter.m_pNode = m_pBack;
				return this->erase(iter);
			}
			GINL _DataType& front(){return m_pFront->t;}
			GINL const _DataType& front() const{return m_pFront->t;}
			GINL _DataType& back(){return m_pBack->t;}
			GINL const _DataType& back() const{return m_pBack->t;}
			GINL it front_it(){it ret; ret.m_pNode = m_pFront; return ret;}
			GINL it back_it(){it ret; ret.m_pNode = m_pBack; return ret;}
			GINL const_it const_front_it() const{const_it ret; ret.m_pNode = m_pFront; return ret;}
			GINL const_it const_back_it() const{const_it ret; ret.m_pNode = m_pBack; return ret;}
			GINL GAIA::GVOID inverse()
			{
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->destroy();
				const_it iter = src.const_front_it();
				while(!iter.empty())
				{
					this->push_back(*iter);
					++iter;
				}
				return *this;
			}
		private:
			GINL GAIA::GVOID init(){m_pFront = m_pBack = GNULL;}
		private:
			Node* m_pFront;
			Node* m_pBack;
			__PoolType m_pool;
		};
	};
};

#endif