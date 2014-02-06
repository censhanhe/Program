#ifndef		__GAIA_CONTAINER_BASICMULTISET_H__
#define		__GAIA_CONTAINER_BASICMULTISET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMultiSet
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMultiSet<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
		public:
			GINL BasicMultiSet(){this->init();}
			GINL BasicMultiSet(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicMultiSet(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL GAIA::BL insert(const _DataType& t){}
			GINL GAIA::BL erase(const _DataType& t){}
			GINL GAIA::BL erase(const Pair<_DataType, _SizeType>& tp){}
			GINL _SizeType count(const _DataType& t){}
			GINL GAIA::BL find(const _DataType& t, BasicVector<Pair<_DataType, _SizeType>, _SizeType, _SizeIncreaserType>& result) const{}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
		private:
		};
	};
};

#endif
