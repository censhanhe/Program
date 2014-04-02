#ifndef		__GAIA_FRAMEWORK_CLSID_H__
#define		__GAIA_FRAMEWORK_CLSID_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class ClsID : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(FLAG)
				FLAG_SYSDEFINE = 0x00000001,
				FLAG_USERDEFINE = 0x00000002,
			GAIA_ENUM_END(FLAG)
		public:
			GINL ClsID(){}
			GINL ClsID(const ClsID& src){this->operator = (src);}
			GINL ClsID(GAIA::U8 uMainType, GAIA::U8 uSubType, GAIA::U16 uMajorVersion, GAIA::U16 uMinorVersion, GAIA::U16 uFlag){this->uMainType = uMainType; this->uSubType = uSubType; this->uMajorVersion = uMajorVersion; this->uMinorVersion = uMinorVersion; this->uFlag = uFlag;}
			GINL GAIA::GVOID Invalid(){uMainType = uSubType = 0; uMajorVersion = uMinorVersion = 0; uFlag = FLAG_INVALID;}
			GINL GAIA::BL IsInvalid() const{return uMainType == 0 && uSubType == 0 && uMajorVersion == 0 && uMinorVersion == 0 && uFlag == FLAG_INVALID;}
			GINL const ClsID& operator = (const ClsID& src){uMainType = src.uMainType; uSubType = src.uSubType; uMajorVersion = src.uMajorVersion; uMinorVersion = src.uMinorVersion; uFlag = src.uFlag; return *this;}
			GINL const GAIA::BL operator == (const ClsID& src) const{return uMainType == src.uMainType && uSubType == src.uSubType && uMajorVersion == src.uMajorVersion && uMinorVersion == src.uMinorVersion && uFlag == src.uFlag;}
			GINL const GAIA::BL operator != (const ClsID& src) const{return uMainType != src.uMainType || uSubType != src.uSubType || uMajorVersion != src.uMajorVersion || uMinorVersion != src.uMinorVersion || uFlag != src.uFlag;}
			GINL const GAIA::BL operator >= (const ClsID& src) const
			{
				if(uMainType < src.uMainType)
					return GAIA::False;
				else if(uMainType > src.uMainType)
					return GAIA::True;
				if(uSubType < src.uSubType)
					return GAIA::False;
				else if(uSubType > src.uSubType)
					return GAIA::True;
				if(uMajorVersion < src.uMajorVersion)
					return GAIA::False;
				else if(uMajorVersion > src.uMajorVersion)
					return GAIA::True;
				if(uMinorVersion < src.uMinorVersion)
					return GAIA::False;
				else if(uMinorVersion > src.uMinorVersion)
					return GAIA::True;
				if(uFlag < src.uFlag)
					return GAIA::False;
				else
					return GAIA::True;
			}
			GINL const GAIA::BL				operator <= (const ClsID& src) const
			{
				if(uMainType > src.uMainType)
					return GAIA::False;
				else if(uMainType < src.uMainType)
					return GAIA::True;
				if(uSubType > src.uSubType)
					return GAIA::False;
				else if(uSubType < src.uSubType)
					return GAIA::True;
				if(uMajorVersion > src.uMajorVersion)
					return GAIA::False;
				else if(uMajorVersion < src.uMajorVersion)
					return GAIA::True;
				if(uMinorVersion > src.uMinorVersion)
					return GAIA::False;
				else if(uMinorVersion < src.uMinorVersion)
					return GAIA::True;
				if(uFlag > src.uFlag)
					return GAIA::False;
				else
					return GAIA::True;
			}
			GINL const GAIA::BL				operator > (const ClsID& src) const
			{
				if(uMainType < src.uMainType)
					return GAIA::False;
				else if(uMainType > src.uMainType)
					return GAIA::True;
				if(uSubType < src.uSubType)
					return GAIA::False;
				else if(uSubType > src.uSubType)
					return GAIA::True;
				if(uMajorVersion < src.uMajorVersion)
					return GAIA::False;
				else if(uMajorVersion > src.uMajorVersion)
					return GAIA::True;
				if(uMinorVersion < src.uMinorVersion)
					return GAIA::False;
				else if(uMinorVersion > src.uMinorVersion)
					return GAIA::True;
				if(uFlag <= src.uFlag)
					return GAIA::False;
				else
					return GAIA::True;
			}
			GINL const GAIA::BL				operator < (const ClsID& src) const
			{
				if(uMainType > src.uMainType)
					return GAIA::False;
				else if(uMainType < src.uMainType)
					return GAIA::True;
				if(uSubType > src.uSubType)
					return GAIA::False;
				else if(uSubType < src.uSubType)
					return GAIA::True;
				if(uMajorVersion > src.uMajorVersion)
					return GAIA::False;
				else if(uMajorVersion < src.uMajorVersion)
					return GAIA::True;
				if(uMinorVersion > src.uMinorVersion)
					return GAIA::False;
				else if(uMinorVersion < src.uMinorVersion)
					return GAIA::True;
				if(uFlag >= src.uFlag)
					return GAIA::False;
				else
					return GAIA::True;
			}
		private:
			GAIA::U8 uMainType;
			GAIA::U8 uSubType;
			GAIA::U16 uMajorVersion;
			GAIA::U16 uMinorVersion;
			GAIA::U16 uFlag;
		};
		static const ClsID GAIA_CLSID_GATEWAY_MEM		= ClsID(0x02, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_GATEWAY_SHAREMEM	= ClsID(0x02, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_GATEWAY_FILE		= ClsID(0x02, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_ROUTE_MEM			= ClsID(0x02, 0x04, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_ROUTE_NET			= ClsID(0x02, 0x05, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_TRANSMISSION_IDM	= ClsID(0x02, 0x06, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_FILEIO			= ClsID(0x03, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_MEMIO				= ClsID(0x03, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_SCREENIO			= ClsID(0x03, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID GAIA_CLSID_SERIALIZER		= ClsID(0x04, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
	};
};

#endif
