#ifndef		__GAIA_FRAMEWORK_CLSID_H__
#define		__GAIA_FRAMEWORK_CLSID_H__

namespace GAIA
{
	namespace FWORK
	{
		class ClsID : public GAIA::Entity
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

		/* Layout. */

		/* Painter. */

		/* State. */
		static const ClsID CLSID_STATE_STATE							= ClsID(0x06, 0x01, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_STATE_STATECTN							= ClsID(0x06, 0x02, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_STATE_STATEMGR							= ClsID(0x06, 0x03, 0x0000, 0x0000, ClsID::FLAG_SYSDEFINE);

		/* Timer. */

		/* Render. */
		static const ClsID CLSID_RENDER_2D_DDRAW						= ClsID(0x08, 0x01, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS						= ClsID(0x08, 0x01, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9							= ClsID(0x08, 0x01, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10							= ClsID(0x08, 0x01, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11							= ClsID(0x08, 0x01, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1							= ClsID(0x08, 0x01, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2							= ClsID(0x08, 0x01, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3							= ClsID(0x08, 0x01, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1						= ClsID(0x08, 0x01, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2						= ClsID(0x08, 0x01, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3						= ClsID(0x08, 0x01, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_PEN					= ClsID(0x08, 0x02, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_PEN					= ClsID(0x08, 0x02, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_PEN						= ClsID(0x08, 0x02, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_PEN						= ClsID(0x08, 0x02, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_PEN						= ClsID(0x08, 0x02, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_PEN						= ClsID(0x08, 0x02, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_PEN						= ClsID(0x08, 0x02, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_PEN						= ClsID(0x08, 0x02, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_PEN					= ClsID(0x08, 0x02, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_PEN					= ClsID(0x08, 0x02, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_PEN					= ClsID(0x08, 0x02, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_BRUSH					= ClsID(0x08, 0x03, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_BRUSH				= ClsID(0x08, 0x03, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_BRUSH					= ClsID(0x08, 0x03, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_BRUSH					= ClsID(0x08, 0x03, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_BRUSH					= ClsID(0x08, 0x03, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_BRUSH					= ClsID(0x08, 0x03, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_BRUSH					= ClsID(0x08, 0x03, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_BRUSH					= ClsID(0x08, 0x03, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_BRUSH					= ClsID(0x08, 0x03, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_BRUSH					= ClsID(0x08, 0x03, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_BRUSH					= ClsID(0x08, 0x03, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_FONTPAINTER			= ClsID(0x08, 0x04, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_FONTPAINTER			= ClsID(0x08, 0x04, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_FONTPAINTER				= ClsID(0x08, 0x04, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_FONTPAINTER				= ClsID(0x08, 0x04, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_FONTPAINTER				= ClsID(0x08, 0x04, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_FONTPAINTER				= ClsID(0x08, 0x04, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_FONTPAINTER				= ClsID(0x08, 0x04, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_FONTPAINTER				= ClsID(0x08, 0x04, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_FONTPAINTER			= ClsID(0x08, 0x04, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_FONTPAINTER			= ClsID(0x08, 0x04, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_FONTPAINTER			= ClsID(0x08, 0x04, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_FONTFAMILY				= ClsID(0x08, 0x05, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_FONTFAMILY			= ClsID(0x08, 0x05, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_FONTFAMILY				= ClsID(0x08, 0x05, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_FONTFAMILY				= ClsID(0x08, 0x05, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_FONTFAMILY				= ClsID(0x08, 0x05, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_FONTFAMILY				= ClsID(0x08, 0x05, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_FONTFAMILY				= ClsID(0x08, 0x05, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_FONTFAMILY				= ClsID(0x08, 0x05, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_FONTFAMILY				= ClsID(0x08, 0x05, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_FONTFAMILY				= ClsID(0x08, 0x05, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_FONTFAMILY				= ClsID(0x08, 0x05, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_FONTFORMAT				= ClsID(0x08, 0x06, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_FONTFORMAT			= ClsID(0x08, 0x06, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_FONTFORMAT				= ClsID(0x08, 0x06, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_FONTFORMAT				= ClsID(0x08, 0x06, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_FONTFORMAT				= ClsID(0x08, 0x06, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_FONTFORMAT				= ClsID(0x08, 0x06, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_FONTFORMAT				= ClsID(0x08, 0x06, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_FONTFORMAT				= ClsID(0x08, 0x06, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_FONTFORMAT				= ClsID(0x08, 0x06, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_FONTFORMAT				= ClsID(0x08, 0x06, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_FONTFORMAT				= ClsID(0x08, 0x06, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_TARGET					= ClsID(0x08, 0x07, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_TARGET				= ClsID(0x08, 0x07, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_TARGET					= ClsID(0x08, 0x07, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_TARGET					= ClsID(0x08, 0x07, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_TARGET					= ClsID(0x08, 0x07, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_TARGET					= ClsID(0x08, 0x07, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_TARGET					= ClsID(0x08, 0x07, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_TARGET					= ClsID(0x08, 0x07, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_TARGET					= ClsID(0x08, 0x07, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_TARGET					= ClsID(0x08, 0x07, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_TARGET					= ClsID(0x08, 0x07, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_SHADER					= ClsID(0x08, 0x08, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_SHADER				= ClsID(0x08, 0x08, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_SHADER					= ClsID(0x08, 0x08, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_SHADER					= ClsID(0x08, 0x08, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_SHADER					= ClsID(0x08, 0x08, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_SHADER					= ClsID(0x08, 0x08, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_SHADER					= ClsID(0x08, 0x08, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_SHADER					= ClsID(0x08, 0x08, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_SHADER					= ClsID(0x08, 0x08, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_SHADER					= ClsID(0x08, 0x08, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_SHADER					= ClsID(0x08, 0x08, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_TEXTURE				= ClsID(0x08, 0x09, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_TEXTURE				= ClsID(0x08, 0x09, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_TEXTURE					= ClsID(0x08, 0x09, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_TEXTURE					= ClsID(0x08, 0x09, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_TEXTURE					= ClsID(0x08, 0x09, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_TEXTURE					= ClsID(0x08, 0x09, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_TEXTURE					= ClsID(0x08, 0x09, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_TEXTURE					= ClsID(0x08, 0x09, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_TEXTURE				= ClsID(0x08, 0x09, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_TEXTURE				= ClsID(0x08, 0x09, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_TEXTURE				= ClsID(0x08, 0x09, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_3D_DX9_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_VERTEXDECLARATION		= ClsID(0x08, 0x0A, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_3D_DX9_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_INDEXBUFFER				= ClsID(0x08, 0x0B, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_INDEXBUFFER			= ClsID(0x08, 0x0B, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_INDEXBUFFER			= ClsID(0x08, 0x0B, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_INDEXBUFFER			= ClsID(0x08, 0x0B, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_3D_DX9_VERTEXBUFFER				= ClsID(0x08, 0x0C, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_VERTEXBUFFER			= ClsID(0x08, 0x0C, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_VERTEXBUFFER			= ClsID(0x08, 0x0C, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_VERTEXBUFFER				= ClsID(0x08, 0x0C, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_VERTEXBUFFER				= ClsID(0x08, 0x0C, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_VERTEXBUFFER				= ClsID(0x08, 0x0C, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_VERTEXBUFFER			= ClsID(0x08, 0x0C, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_VERTEXBUFFER			= ClsID(0x08, 0x0C, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_VERTEXBUFFER			= ClsID(0x08, 0x0C, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_CONTEXT				= ClsID(0x08, 0x0D, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_CONTEXT				= ClsID(0x08, 0x0D, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_CONTEXT					= ClsID(0x08, 0x0D, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_CONTEXT					= ClsID(0x08, 0x0D, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_CONTEXT					= ClsID(0x08, 0x0D, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_CONTEXT					= ClsID(0x08, 0x0D, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_CONTEXT					= ClsID(0x08, 0x0D, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_CONTEXT					= ClsID(0x08, 0x0D, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_CONTEXT				= ClsID(0x08, 0x0D, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_CONTEXT				= ClsID(0x08, 0x0D, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_CONTEXT				= ClsID(0x08, 0x0D, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_TEXTUREFETCHDATA			= ClsID(0x08, 0x0E, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_TEXTUREFETCHDATA			= ClsID(0x08, 0x0E, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_TEXTUREFETCHDATA			= ClsID(0x08, 0x0E, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_TEXTUREFETCHDATA			= ClsID(0x08, 0x0E, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_TEXTUREFETCHDATA		= ClsID(0x08, 0x0E, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_2D_DDRAW_TARGETFETCHDATA		= ClsID(0x08, 0x0F, 0x0001, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_2D_GDIPLUS_TARGETFETCHDATA		= ClsID(0x08, 0x0F, 0x0002, 0x0000, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX9_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_TARGETFETCHDATA			= ClsID(0x08, 0x0F, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_TARGETFETCHDATA		= ClsID(0x08, 0x0F, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_TARGETFETCHDATA		= ClsID(0x08, 0x0F, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_TARGETFETCHDATA		= ClsID(0x08, 0x0F, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_3D_DX9_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_VERTEXBUFFERFETCHDATA	= ClsID(0x08, 0x10, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

		static const ClsID CLSID_RENDER_3D_DX9_INDEXBUFFERFETCHDATA		= ClsID(0x08, 0x11, 0x0003, 0x0009, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX10_INDEXBUFFERFETCHDATA	= ClsID(0x08, 0x11, 0x0003, 0x000A, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_DX11_INDEXBUFFERFETCHDATA	= ClsID(0x08, 0x11, 0x0003, 0x000B, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL1_INDEXBUFFERFETCHDATA		= ClsID(0x08, 0x11, 0x0004, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL2_INDEXBUFFERFETCHDATA		= ClsID(0x08, 0x11, 0x0004, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GL3_INDEXBUFFERFETCHDATA		= ClsID(0x08, 0x11, 0x0004, 0x0003, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES1_INDEXBUFFERFETCHDATA	= ClsID(0x08, 0x11, 0x0005, 0x0001, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES2_INDEXBUFFERFETCHDATA	= ClsID(0x08, 0x11, 0x0005, 0x0002, ClsID::FLAG_SYSDEFINE);
		static const ClsID CLSID_RENDER_3D_GLES3_INDEXBUFFERFETCHDATA	= ClsID(0x08, 0x11, 0x0005, 0x0003, ClsID::FLAG_SYSDEFINE);

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

			CLSID_STATE_STATE,
			CLSID_STATE_STATECTN,
			CLSID_STATE_STATEMGR,

			CLSID_RENDER_2D_DDRAW,
			CLSID_RENDER_2D_GDIPLUS,
			CLSID_RENDER_3D_DX9,
			CLSID_RENDER_3D_DX10,
			CLSID_RENDER_3D_DX11,
			CLSID_RENDER_3D_GL1,
			CLSID_RENDER_3D_GL2,
			CLSID_RENDER_3D_GL3,
			CLSID_RENDER_3D_GLES1,
			CLSID_RENDER_3D_GLES2,
			CLSID_RENDER_3D_GLES3,

			CLSID_RENDER_2D_DDRAW_PEN,
			CLSID_RENDER_2D_GDIPLUS_PEN,
			CLSID_RENDER_3D_DX9_PEN,
			CLSID_RENDER_3D_DX10_PEN,
			CLSID_RENDER_3D_DX11_PEN,
			CLSID_RENDER_3D_GL1_PEN,
			CLSID_RENDER_3D_GL2_PEN,
			CLSID_RENDER_3D_GL3_PEN,
			CLSID_RENDER_3D_GLES1_PEN,
			CLSID_RENDER_3D_GLES2_PEN,
			CLSID_RENDER_3D_GLES3_PEN,

			CLSID_RENDER_2D_DDRAW_BRUSH,
			CLSID_RENDER_2D_GDIPLUS_BRUSH,
			CLSID_RENDER_3D_DX9_BRUSH,
			CLSID_RENDER_3D_DX10_BRUSH,
			CLSID_RENDER_3D_DX11_BRUSH,
			CLSID_RENDER_3D_GL1_BRUSH,
			CLSID_RENDER_3D_GL2_BRUSH,
			CLSID_RENDER_3D_GL3_BRUSH,
			CLSID_RENDER_3D_GLES1_BRUSH,
			CLSID_RENDER_3D_GLES2_BRUSH,
			CLSID_RENDER_3D_GLES3_BRUSH,

			CLSID_RENDER_2D_DDRAW_FONTPAINTER,
			CLSID_RENDER_2D_GDIPLUS_FONTPAINTER,
			CLSID_RENDER_3D_DX9_FONTPAINTER,
			CLSID_RENDER_3D_DX10_FONTPAINTER,
			CLSID_RENDER_3D_DX11_FONTPAINTER,
			CLSID_RENDER_3D_GL1_FONTPAINTER,
			CLSID_RENDER_3D_GL2_FONTPAINTER,
			CLSID_RENDER_3D_GL3_FONTPAINTER,
			CLSID_RENDER_3D_GLES1_FONTPAINTER,
			CLSID_RENDER_3D_GLES2_FONTPAINTER,
			CLSID_RENDER_3D_GLES3_FONTPAINTER,

			CLSID_RENDER_2D_DDRAW_FONTFAMILY,
			CLSID_RENDER_2D_GDIPLUS_FONTFAMILY,
			CLSID_RENDER_3D_DX9_FONTFAMILY,
			CLSID_RENDER_3D_DX10_FONTFAMILY,
			CLSID_RENDER_3D_DX11_FONTFAMILY,
			CLSID_RENDER_3D_GL1_FONTFAMILY,
			CLSID_RENDER_3D_GL2_FONTFAMILY,
			CLSID_RENDER_3D_GL3_FONTFAMILY,
			CLSID_RENDER_3D_GLES1_FONTFAMILY,
			CLSID_RENDER_3D_GLES2_FONTFAMILY,
			CLSID_RENDER_3D_GLES3_FONTFAMILY,

			CLSID_RENDER_2D_DDRAW_FONTFORMAT,
			CLSID_RENDER_2D_GDIPLUS_FONTFORMAT,
			CLSID_RENDER_3D_DX9_FONTFORMAT,
			CLSID_RENDER_3D_DX10_FONTFORMAT,
			CLSID_RENDER_3D_DX11_FONTFORMAT,
			CLSID_RENDER_3D_GL1_FONTFORMAT,
			CLSID_RENDER_3D_GL2_FONTFORMAT,
			CLSID_RENDER_3D_GL3_FONTFORMAT,
			CLSID_RENDER_3D_GLES1_FONTFORMAT,
			CLSID_RENDER_3D_GLES2_FONTFORMAT,
			CLSID_RENDER_3D_GLES3_FONTFORMAT,

			CLSID_RENDER_2D_DDRAW_TARGET,
			CLSID_RENDER_2D_GDIPLUS_TARGET,
			CLSID_RENDER_3D_DX9_TARGET,
			CLSID_RENDER_3D_DX10_TARGET,
			CLSID_RENDER_3D_DX11_TARGET,
			CLSID_RENDER_3D_GL1_TARGET,
			CLSID_RENDER_3D_GL2_TARGET,
			CLSID_RENDER_3D_GL3_TARGET,
			CLSID_RENDER_3D_GLES1_TARGET,
			CLSID_RENDER_3D_GLES2_TARGET,
			CLSID_RENDER_3D_GLES3_TARGET,

			CLSID_RENDER_2D_DDRAW_SHADER,
			CLSID_RENDER_2D_GDIPLUS_SHADER,
			CLSID_RENDER_3D_DX9_SHADER,
			CLSID_RENDER_3D_DX10_SHADER,
			CLSID_RENDER_3D_DX11_SHADER,
			CLSID_RENDER_3D_GL1_SHADER,
			CLSID_RENDER_3D_GL2_SHADER,
			CLSID_RENDER_3D_GL3_SHADER,
			CLSID_RENDER_3D_GLES1_SHADER,
			CLSID_RENDER_3D_GLES2_SHADER,
			CLSID_RENDER_3D_GLES3_SHADER,

			CLSID_RENDER_2D_DDRAW_TEXTURE,
			CLSID_RENDER_2D_GDIPLUS_TEXTURE,
			CLSID_RENDER_3D_DX9_TEXTURE,
			CLSID_RENDER_3D_DX10_TEXTURE,
			CLSID_RENDER_3D_DX11_TEXTURE,
			CLSID_RENDER_3D_GL1_TEXTURE,
			CLSID_RENDER_3D_GL2_TEXTURE,
			CLSID_RENDER_3D_GL3_TEXTURE,
			CLSID_RENDER_3D_GLES1_TEXTURE,
			CLSID_RENDER_3D_GLES2_TEXTURE,
			CLSID_RENDER_3D_GLES3_TEXTURE,

			CLSID_RENDER_3D_DX9_VERTEXDECLARATION,
			CLSID_RENDER_3D_DX10_VERTEXDECLARATION,
			CLSID_RENDER_3D_DX11_VERTEXDECLARATION,
			CLSID_RENDER_3D_GL1_VERTEXDECLARATION,
			CLSID_RENDER_3D_GL2_VERTEXDECLARATION,
			CLSID_RENDER_3D_GL3_VERTEXDECLARATION,
			CLSID_RENDER_3D_GLES1_VERTEXDECLARATION,
			CLSID_RENDER_3D_GLES2_VERTEXDECLARATION,
			CLSID_RENDER_3D_GLES3_VERTEXDECLARATION,

			CLSID_RENDER_3D_DX9_INDEXBUFFER,
			CLSID_RENDER_3D_DX10_INDEXBUFFER,
			CLSID_RENDER_3D_DX11_INDEXBUFFER,
			CLSID_RENDER_3D_GL1_INDEXBUFFER,
			CLSID_RENDER_3D_GL2_INDEXBUFFER,
			CLSID_RENDER_3D_GL3_INDEXBUFFER,
			CLSID_RENDER_3D_GLES1_INDEXBUFFER,
			CLSID_RENDER_3D_GLES2_INDEXBUFFER,
			CLSID_RENDER_3D_GLES3_INDEXBUFFER,

			CLSID_RENDER_3D_DX9_VERTEXBUFFER,
			CLSID_RENDER_3D_DX10_VERTEXBUFFER,
			CLSID_RENDER_3D_DX11_VERTEXBUFFER,
			CLSID_RENDER_3D_GL1_VERTEXBUFFER,
			CLSID_RENDER_3D_GL2_VERTEXBUFFER,
			CLSID_RENDER_3D_GL3_VERTEXBUFFER,
			CLSID_RENDER_3D_GLES1_VERTEXBUFFER,
			CLSID_RENDER_3D_GLES2_VERTEXBUFFER,
			CLSID_RENDER_3D_GLES3_VERTEXBUFFER,

			CLSID_RENDER_2D_DDRAW_CONTEXT,
			CLSID_RENDER_2D_GDIPLUS_CONTEXT,
			CLSID_RENDER_3D_DX9_CONTEXT,
			CLSID_RENDER_3D_DX10_CONTEXT,
			CLSID_RENDER_3D_DX11_CONTEXT,
			CLSID_RENDER_3D_GL1_CONTEXT,
			CLSID_RENDER_3D_GL2_CONTEXT,
			CLSID_RENDER_3D_GL3_CONTEXT,
			CLSID_RENDER_3D_GLES1_CONTEXT,
			CLSID_RENDER_3D_GLES2_CONTEXT,
			CLSID_RENDER_3D_GLES3_CONTEXT,

			CLSID_RENDER_2D_DDRAW_TEXTUREFETCHDATA,
			CLSID_RENDER_2D_GDIPLUS_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_DX9_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_DX10_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_DX11_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GL1_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GL2_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GL3_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GLES1_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GLES2_TEXTUREFETCHDATA,
			CLSID_RENDER_3D_GLES3_TEXTUREFETCHDATA,

			CLSID_RENDER_2D_DDRAW_TARGETFETCHDATA,
			CLSID_RENDER_2D_GDIPLUS_TARGETFETCHDATA,
			CLSID_RENDER_3D_DX9_TARGETFETCHDATA,
			CLSID_RENDER_3D_DX10_TARGETFETCHDATA,
			CLSID_RENDER_3D_DX11_TARGETFETCHDATA,
			CLSID_RENDER_3D_GL1_TARGETFETCHDATA,
			CLSID_RENDER_3D_GL2_TARGETFETCHDATA,
			CLSID_RENDER_3D_GL3_TARGETFETCHDATA,
			CLSID_RENDER_3D_GLES1_TARGETFETCHDATA,
			CLSID_RENDER_3D_GLES2_TARGETFETCHDATA,
			CLSID_RENDER_3D_GLES3_TARGETFETCHDATA,

			CLSID_RENDER_3D_DX9_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_DX10_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_DX11_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL1_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL2_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL3_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES1_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES2_VERTEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES3_VERTEXBUFFERFETCHDATA,

			CLSID_RENDER_3D_DX9_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_DX10_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_DX11_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL1_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL2_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GL3_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES1_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES2_INDEXBUFFERFETCHDATA,
			CLSID_RENDER_3D_GLES3_INDEXBUFFERFETCHDATA,
		};
	};
};

#endif
