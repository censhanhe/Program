#ifndef		__GAIA_CONTAINER_BASICDIRTIONARY_H__
#define		__GAIA_CONTAINER_BASICDIRTIONARY_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicDictionary : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicDictionary<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicDictionary(){}
			GINL BasicDictionary(const __MyType& src){}
			GINL ~BasicDictionary(){}
			GINL GAIA::BL empty() const;
			GINL const _SizeType& size() const;
			GINL const _SizeType& capacity() const;
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID destroy();
		private:
			GINL GAIA::GVOID init(){}
		private:
		};
	};
};

#endif
