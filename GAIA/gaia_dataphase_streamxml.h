#ifndef		__GAIA_DATAPHASE_STREAMXML_H__
#define		__GAIA_DATAPHASE_STREAMXML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _CharType, typename _DataSizeType, typename _SizeIncreaserType> class StreamXML : public GAIA::Entity
		{
		public:
			typedef _CharType _chartype;
			typedef _DataSizeType _datasizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef StreamXML<_CharType, _DataSizeType, _SizeIncreaserType> __MyType;
			typedef const _CharType* __ConstCharPtrType;
		public:
			GINL StreamXML(){}
			GINL ~StreamXML(){}
		};
	};
};

#endif
