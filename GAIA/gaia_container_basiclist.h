#ifndef		__GAIA_CONTAINER_BASICLIST_H__
#define		__GAIA_CONTAINER_BASICLIST_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicList
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
			class BidirectionalIterator : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicList;
			public:
				GINL BidirectionalIterator(){m_pNode = GNULL;}
				GINL virtual ~BidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual _DataType& operator * (){return m_pNode->t;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){m_pNode = m_pNode->pPrev; return *this;}
				GINL GAIA::BL operator == (const BidirectionalIterator& src) const{if(m_pNode == src.m_pNode) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const BidirectionalIterator& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const BidirectionalIterator& src) const{}
				GINL GAIA::BL operator <= (const BidirectionalIterator& src) const{}
				GINL GAIA::BL operator > (const BidirectionalIterator& src) const{}
				GINL GAIA::BL operator < (const BidirectionalIterator& src) const{}
				GINL BidirectionalIterator& operator = (const BidirectionalIterator& src){m_pNode = src.m_pNode; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (N32){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (N32){m_pNode = m_pNode->pPrev; return *this;}
			private:
				Node* m_pNode;
			};
			class ConstBidirectionalIterator : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicList;
			public:
				GINL ConstBidirectionalIterator(){m_pNode = GNULL;}
				GINL virtual ~ConstBidirectionalIterator(){}
				GINL virtual GAIA::BL empty() const{if(m_pNode == GNULL) return GAIA::True; return GAIA::False;}
				GINL virtual const _DataType& operator * () const{return m_pNode->t;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){m_pNode = m_pNode->pPrev; return *this;}
				GINL GAIA::BL operator == (const ConstBidirectionalIterator& src) const{if(m_pNode == src.m_pNode) return GAIA::True; return GAIA::False;}
				GINL GAIA::BL operator != (const ConstBidirectionalIterator& src) const{return !(this->operator == (src));}
				GINL GAIA::BL operator >= (const ConstBidirectionalIterator& src) const{}
				GINL GAIA::BL operator <= (const ConstBidirectionalIterator& src) const{}
				GINL GAIA::BL operator > (const ConstBidirectionalIterator& src) const{}
				GINL GAIA::BL operator < (const ConstBidirectionalIterator& src) const{}
				GINL ConstBidirectionalIterator& operator = (const ConstBidirectionalIterator& src){m_pNode = src.m_pNode; return *this;}
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (N32){m_pNode = m_pNode->pNext; return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (N32){m_pNode = m_pNode->pPrev; return *this;}
			private:
				Node* m_pNode;
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
			GINL GAIA::GVOID insert(BidirectionalIterator& iter, const _DataType& t)
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
			GINL GAIA::BL erase(BidirectionalIterator& iter)
			{
				if(iter.empty())
					return GAIA::False;
				if(iter.m_pNode == m_pFront)
				{
					m_pFront = m_pFront->pNext;
					m_pFront->pPrev = GNULL;
				}
				else if(iter.m_pNode == m_pBack)
				{
					m_pBack = m_pBack->pPrev;
					m_pBack->pNext = GNULL;
				}
				Node* pErase = iter.m_pNode;
				++iter;
				m_pool.release(pErase);
				return GAIA::True;
			}
			GINL GAIA::GVOID swap(BidirectionalIterator& iter1, BidirectionalIterator& iter2){GAIA::ALGORITHM::swap(*iter1, *iter2);}
			GINL GAIA::GVOID push_front(const _DataType& t)
			{
				BidirectionalIterator iter;
				iter.m_pNode = m_pFront;
				this->insert(iter, t);
			}
			GINL GAIA::BL pop_front()
			{
				BidirectionalIterator iter;
				iter.m_pNode = m_pFront;
				return this->erase(iter);
			}
			GINL GAIA::GVOID push_back(const _DataType& t)
			{
				BidirectionalIterator iter;
				iter.m_pNode = GNULL;
				this->insert(iter, t);
			}
			GINL GAIA::BL pop_back()
			{
				BidirectionalIterator iter;
				iter.m_pNode = m_pBack;
				return this->erase(iter);
			}
			GINL _DataType& front(){return m_pFront->t;}
			GINL const _DataType& front() const{return m_pFront->t;}
			GINL _DataType& back(){return m_pBack->t;}
			GINL const _DataType& back() const{return m_pBack->t;}
			GINL BidirectionalIterator front_iterator(){BidirectionalIterator ret; ret.m_pNode = m_pFront; return ret;}
			GINL BidirectionalIterator back_iterator(){BidirectionalIterator ret; ret.m_pNode = m_pBack; return ret;}
			GINL ConstBidirectionalIterator const_front_iterator() const{ConstBidirectionalIterator ret; ret.m_pNode = m_pFront; return ret;}
			GINL ConstBidirectionalIterator const_back_iterator() const{ConstBidirectionalIterator ret; ret.m_pNode = m_pBack; return ret;}
			GINL GAIA::GVOID inverse()
			{
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->destroy();
				ConstBidirectionalIterator& iter = src.const_front_iterator();
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