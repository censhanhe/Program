#ifndef		__GAIA_CONTAINER_BASICLIST_H__
#define		__GAIA_CONTAINER_BASICLIST_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class List
		{
		public:
			GINL List();
			template <typename _ParamType> GINL List(const List<_DataType, _SizeType, _ParamType>& src);
			GINL ~List();
			GINL _SizeType capacity() const;
			GINL _SizeType size() const;
			GINL GAIA::BL empty() const;
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID destroy();
			GINL GAIA::GVOID insert(const _SizeType& index, const _DataType& t);
			GINL GAIA::BL erase(const _SizeType& index);
			GINL GAIA::BL swap(const _SizeType& index, const _SizeType& index);
			GINL GAIA::GVOID push_back(const _DataType& t);
			GINL GAIA::BL pop_back();
			GINL _DataType& back();
			GINL const _DataType& back() const;
			GINL GAIA::GVOID push_front(const _DataType& t);
			GINL GAIA::BL pop_back();
			GINL _DataType& back();
			GINL const _DataType& back() const;
			GINL GAIA::GVOID inverse();
			template <typename _ParamType> GINL const List<_DataType, _SizeType, _SizeIncreaserType>& operator = (const List<_DataType, _SizeType, _ParamType)& src);
			GINL _DataType& operator[](const _SizeType& index);
			GINL const _DataType& operator[](const _SizeType& index) const;
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
			BasicStack<_DataType, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif