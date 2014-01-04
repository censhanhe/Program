#ifndef		__GAIA_DATA_ANALYZE_XML_H__
#define		__GAIA_DATA_ANALYZE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template <typename _StringType, typename _StringLengthType, typename _DataSizeType> class XML
		{
		public:
			typedef GAIA::CONTAINER::BasicString<_StringType, _StringLengthType> __MyString;

		public:
			GINL XML(){}
			GINL ~XML(){}
			GINL GAIA::BL Load(GAIA::Stream<_DataSizeType>* pStream);
			GINL GAIA::BL Save(GAIA::Stream<_DataSizeType>* pStream) const;
			GINL GAIA::BL BeginNodeRead(__MyString& strNode);
			GINL GAIA::BL EndNodeRead();
			GINL GAIA::BL ReadAttr(__MyString& strAttrName, __MyString& strAttrValue);
			GINL GAIA::BL BeginNodeWrite(const __MyString& strNode);
			GINL GAIA::BL EndNodeWrite();
			GINL GAIA::BL WriteAttr(const __MyString& strAttrName, const __MyString& strAttrValue);
		};
	};
};

#endif
