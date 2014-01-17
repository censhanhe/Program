#ifndef		__GAIA_CONTAINER_BASICLIST_H__
#define		__GAIA_CONTAINER_BASICLIST_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicList
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicPool<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicList(){this->init();}
			GINL BasicList(const __MyType& src);
			GINL ~BasicList();
			GINL _SizeType capacity() const;
			GINL _SizeType size() const;
			GINL GAIA::BL empty() const;
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID destroy();
			GINL GAIA::GVOID insert(const _SizeType& index, const _DataType& t);
			GINL GAIA::BL erase(const _SizeType& index);
			GINL GAIA::BL swap(const _SizeType& index1, const _SizeType& index2);
			GINL GAIA::GVOID push_back(const _DataType& t);
			GINL GAIA::BL pop_back();
			GINL _DataType& back();
			GINL const _DataType& back() const;
			GINL GAIA::GVOID push_front(const _DataType& t);
			GINL GAIA::BL pop_front();
			GINL _DataType& front();
			GINL const _DataType& front() const;
			GINL GAIA::GVOID inverse();
			template <typename _ParamType> GINL const __MyType& operator = (const BasicList<_DataType, _SizeType, _ParamType, _GroupElementSize>& src);
			GINL _DataType& operator[](const _SizeType& index);
			GINL const _DataType& operator[](const _SizeType& index) const;
		private:
			GINL GAIA::GVOID init(){m_pFront = m_pBack = m_pCurrent = GNULL;}
		private:
			class Node
			{
			public:
				_DataType t;
				Node* pNext;
				Node* pPrev;
			};
		private:
			Node* m_pFront;
			Node* m_pBack;
			Node* m_pCurrent;
			__PoolType m_pool;
		};
	};
};

#endif