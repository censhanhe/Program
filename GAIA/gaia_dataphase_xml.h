#ifndef		__GAIA_DATA_ANALYZE_XML_H__
#define		__GAIA_DATA_ANALYZE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template <typename _StringType, typename _StringLengthType, typename _DataSizeType> class XML
		{
		public:
			typedef GAIA::CONTAINER::BasicString<_StringType, _StringLengthType> __MyStringType;
		public:
			GINL XML(){}
			GINL ~XML(){}
			GINL GAIA::BL Load(GAIA::FILESYSTEM::File& file);
			GINL GAIA::BL Save(GAIA::FILESYSTEM::File& file) const;
			GINL GAIA::BL Load(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf);
			GINL GAIA::BL Save(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf) const;
			GINL GAIA::BL BeginNodeRead(__MyStringType& strNode);
			GINL GAIA::BL EndNodeRead();
			GINL GAIA::BL ReadAttr(__MyStringType& strAttrName, __MyStringType& strAttrValue);
			GINL GAIA::BL BeginNodeWrite(const __MyStringType& strNode);
			GINL GAIA::BL EndNodeWrite();
			GINL GAIA::BL WriteAttr(const __MyStringType& strAttrName, const __MyStringType& strAttrValue);
		};
	};
};

#endif
