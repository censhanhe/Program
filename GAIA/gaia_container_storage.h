#ifndef 	__GAIA_CONTAINER_STORAGE_H__
#define 	__GAIA_CONTAINER_STORAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType, _SizeType _PageSize> class Storage
		{
		public:
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _pagesize = _PageSize;
		public:
			typedef Storage<_SizeType, _PageSize> __MyType;
		public:
			class Node
			{
			public:
				GINL Node();
				GINL Node(const Node& src);
				GINL ~Node();
				GINL _SizeType size() const;
				GINL _SizeType capacity() const;
			private:
				GINL GAIA::GVOID init(){}
			};
		public:
			GINL Storage(){}
			GINL Storage(const __MyType& src){this->operator = (src);}
			GINL ~Storage(){}
			GINL GAIA::BL empty() const;
			GINL _SizeType size() const;
			GINL _SizeType capacity() const;
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID destroy();
			GINL GAIA::GVOID optimize();
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){}
		private:
		};
	};
};

#endif