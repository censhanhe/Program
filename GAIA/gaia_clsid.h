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
	};
};

#endif
