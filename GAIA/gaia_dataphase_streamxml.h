#ifndef		__GAIA_DATAPHASE_STREAMXML_H__
#define		__GAIA_DATAPHASE_STREAMXML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _StringType, typename _StringLengthType, typename _DataSizeType> class StreamXML : public GAIA::Entity
		{
		public:
			typedef GAIA::CONTAINER::BasicString<_StringType, _StringLengthType> __StringType;
		public:
			GINL StreamXML(){}
			GINL ~StreamXML(){}
			GINL GAIA::BL Load(GAIA::FILESYSTEM::FileBase& file);
			GINL GAIA::BL Save(GAIA::FILESYSTEM::FileBase& file) const;
			GINL GAIA::BL Load(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf);
			GINL GAIA::BL Save(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf) const;
		};
	};
};

#endif
