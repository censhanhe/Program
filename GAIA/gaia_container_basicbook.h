#ifndef 	__GAIA_CONTAINER_BASICBOOK_H__
#define 	__GAIA_CONTAINER_BASICBOOK_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicBook : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicBook<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL GAIA::BL empty() const;
			GINL _SizeType size() const;
			GINL _SizeType capacity() const;
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID destroy();
			GINL _SizeType set(const _DataType& t);
			GINL GAIA::BL erase(const _SizeType& index);
		private:
			class Node : public GAIA::Base
			{
			public:
				_DataType t;
				_SizeType index;
				_SizeType useindex;
			};
		private:
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __ListType;
			typedef GAIA::CONTAINER::BasicVector<_SizeType, _SizeType, _SizeIncreaserType> __UseListType;
			typedef GAIA::CONTAINER::BasicStack<_SizeType, _SizeType, _SizeIncreaserType> __FreeStackType;
		private:
			__ListType m_list;
			__UseListType m_uselist;
			__FreeStackType m_freestack;
		};
	};
};

#endif
