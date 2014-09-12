#ifndef 	__GAIA_CONTAINER_BASICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BAISCSTRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStringPool : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStringPool<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicStringPool(){this->init();}
			GINL ~BasicStringPool(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL _DataType* request(const _DataType* p){}
			GINL GAIA::BL release(const _DataType* p){}
		private:
			GINL GAIA::GVOID init(){}
		private:
		};
	};
};

#endif
