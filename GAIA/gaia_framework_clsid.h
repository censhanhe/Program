#ifndef		__GAIA_FRAMEWORK_CLSID_H__
#define		__GAIA_FRAMEWORK_CLSID_H__

namespace GAIA
{
	namespace FWORK
	{
		class ClsID : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(FLAG)
				FLAG_SYSDEFINE = 1 << 0,
				FLAG_USERDEFINE = 1 << 1,
			GAIA_ENUM_END(FLAG)
		public:
			GINL ClsID(){}
			GINL ClsID(const ClsID& src){this->operator = (src);}
			GINL ClsID(GAIA::U8 uMainType, GAIA::U8 uSubType, GAIA::U16 uMajorVersion, GAIA::U16 uMinorVersion, GAIA::U16 uFlag){this->uMainType = uMainType; this->uSubType = uSubType; this->uMajorVersion = uMajorVersion; this->uMinorVersion = uMinorVersion; this->uFlag = uFlag;}
			GINL GAIA::GVOID Invalid(){uMainType = uSubType = 0; uMajorVersion = uMinorVersion = 0; uFlag = FLAG_INVALID;}
			GINL GAIA::BL IsInvalid() const{return uMainType == 0 && uSubType == 0 && uMajorVersion == 0 && uMinorVersion == 0 && uFlag == FLAG_INVALID;}
			GAIA::GVOID MainType(GAIA::U8 uMainType){this->uMainType = uMainType;}
			GAIA::U8 MainType() const{return uMainType;}
			GAIA::GVOID SubType(GAIA::U8 uSubType){this->uSubType = uSubType;}
			GAIA::U8 SubType() const{return uSubType;}
			GAIA::GVOID MajorVersion(GAIA::U16 uMajorVersion){this->uMajorVersion = uMajorVersion;}
			GAIA::U16 MajorVersion() const{return uMajorVersion;}
			GAIA::GVOID MinorVersion(GAIA::U16 uMinorVersion){this->uMinorVersion = uMinorVersion;}
			GAIA::U16 MinorVersion() const{return uMinorVersion;}
			GAIA::GVOID Flag(GAIA::U16 uFlag){this->uFlag = uFlag;}
			GAIA::U16 Flag() const{return uFlag;}
			GINL const ClsID& operator = (const ClsID& src){GAIA_AST(&src != this); uMainType = src.uMainType; uSubType = src.uSubType; uMajorVersion = src.uMajorVersion; uMinorVersion = src.uMinorVersion; uFlag = src.uFlag; return *this;}
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
			GINL const GAIA::BL operator <= (const ClsID& src) const
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
			GINL const GAIA::BL operator > (const ClsID& src) const
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
			GINL const GAIA::BL	operator < (const ClsID& src) const
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

		/* Data traffic. */
		static const ClsID CLSID_DATATRAFFIC_GATEWAYMEM					= ClsID(0x02, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_DATATRAFFIC_GATEWAYSHAREMEM			= ClsID(0x02, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_DATATRAFFIC_GATEWAYFILE				= ClsID(0x02, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_DATATRAFFIC_ROUTEMEM					= ClsID(0x02, 0x04, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_DATATRAFFIC_ROUTENET					= ClsID(0x02, 0x05, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_DATATRAFFIC_TRANSMISSIONIDM			= ClsID(0x02, 0x06, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		/* IO. */
		static const ClsID CLSID_IO_FILEIO								= ClsID(0x03, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_IO_MEMIO								= ClsID(0x03, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_IO_SCREENIO							= ClsID(0x03, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		/* Serializer. */
		static const ClsID CLSID_SERIALIZER								= ClsID(0x04, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		/* Model. */

		/* Controller. */

		/* UI. */
		static const ClsID CLSID_UI_CANVAS								= ClsID(0x05, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_PAINTER								= ClsID(0x05, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_FORM								= ClsID(0x05, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_PUSHBUTTON							= ClsID(0x05, 0x04, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_RADIOBUTTON							= ClsID(0x05, 0x05, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_CHECKBUTTON							= ClsID(0x05, 0x06, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_LABEL								= ClsID(0x05, 0x07, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_EDIT								= ClsID(0x05, 0x08, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_DOCUMENT							= ClsID(0x05, 0x09, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_UI_PROGRESSBAR							= ClsID(0x05, 0x0A, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		

		/* Layout. */

		/* State. */
		static const ClsID CLSID_STATE_STATE							= ClsID(0x06, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_STATE_STATECTN							= ClsID(0x06, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_STATE_STATEMGR							= ClsID(0x06, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		/* Timer. */
		static const ClsID CLSID_TIMER_TIMER							= ClsID(0x07, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_TIMER_TIMERMGR							= ClsID(0x07, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_LIST[] = 
		{
			CLSID_DATATRAFFIC_GATEWAYMEM,
			CLSID_DATATRAFFIC_GATEWAYSHAREMEM,
			CLSID_DATATRAFFIC_GATEWAYFILE,
			CLSID_DATATRAFFIC_ROUTEMEM,
			CLSID_DATATRAFFIC_ROUTENET,
			CLSID_DATATRAFFIC_TRANSMISSIONIDM,

			CLSID_IO_FILEIO,
			CLSID_IO_MEMIO,
			CLSID_IO_SCREENIO,

			CLSID_SERIALIZER,

			CLSID_UI_CANVAS,
			CLSID_UI_PAINTER,
			CLSID_UI_FORM,
			CLSID_UI_PUSHBUTTON,
			CLSID_UI_RADIOBUTTON,
			CLSID_UI_CHECKBUTTON,
			CLSID_UI_LABEL,
			CLSID_UI_EDIT,
			CLSID_UI_DOCUMENT,
			CLSID_UI_PROGRESSBAR,

			CLSID_STATE_STATE,
			CLSID_STATE_STATECTN,
			CLSID_STATE_STATEMGR,

			CLSID_TIMER_TIMER,
			CLSID_TIMER_TIMERMGR,
		};
	};
};

#endif
