#ifndef 	__GAIA_DATAPHASE_TDIFF_H__
#define 	__GAIA_DATAPHASE_TDIFF_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _DataType, typename _SizeType> class TDiff : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef TDiff<_DataType, _SizeType> __MyType;
		public:
			GINL TDiff(){}
			GINL ~TDiff(){}
		private:
		};
	};
};

#endif
