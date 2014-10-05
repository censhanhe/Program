#ifndef		__GAIA_RENDER_GDIPLUS_H__
#define		__GAIA_RENDER_GDIPLUS_H__

#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#	include <gdiplus.h>
#endif

namespace GAIA
{
	namespace RENDER
	{
		class Render2DGDIPlus : public virtual GAIA::RENDER::Render2D
		{
		public:
			typedef GAIA::RENDER::Render2DGDIPlus __MyType;

		public:
			class RenderDesc : public virtual GAIA::RENDER::Render2D::RenderDesc
			{
			public:
				virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::RenderDesc::reset();}
				virtual GAIA::BL check() const
				{
					if(!GAIA::RENDER::Render2D::RenderDesc::check())
						return GAIA::False;
					return GAIA::True;
				}
			};

		public:
			class Pen : public virtual GAIA::RENDER::Render2D::Pen
			{
			public:
				class PenDesc : public virtual GAIA::RENDER::Render2D::Pen::PenDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Pen::PenDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Pen::PenDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Pen(){this->init();}
				GINL ~Pen(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Pen::PenDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pPen = new Gdiplus::Pen((Gdiplus::Color)0xFF000000, 1.0F);
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::Pen::PenDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pPen);
				#endif
					m_desc.reset();
				}
				virtual const PenDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_PEN;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pPen == GNIL)
						return GAIA::False;
					GAIA::MATH::ARGB<GAIA::REAL> crNew = cr;
					crNew.tobytemode();
					Gdiplus::Color crTemp(crNew.a, crNew.r, crNew.g, crNew.b);
					if(m_pPen->SetColor(crTemp) != Gdiplus::Ok)
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pPen == GNIL)
						return GAIA::False;
					Gdiplus::Color crTemp;
					if(m_pPen->GetColor(&crTemp) != Gdiplus::Ok)
						return GAIA::False;
					cr.a = (GAIA::REAL)crTemp.GetA();
					cr.r = (GAIA::REAL)crTemp.GetR();
					cr.g = (GAIA::REAL)crTemp.GetG();
					cr.b = (GAIA::REAL)crTemp.GetB();
					cr.torealmode();
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL SetWidth(const GAIA::REAL& rWidth)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pPen == GNIL)
						return GAIA::False;
					if(m_pPen->SetWidth(rWidth) != Gdiplus::Ok)
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL GetWidth(GAIA::REAL& rWidth) const
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pPen == GNIL)
						return GAIA::False;
					rWidth = m_pPen->GetWidth();
				#endif
					return GAIA::True;
				}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Pen* GetInternalPen() const{return m_pPen;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pPen = GNIL;
				#endif
				}
			private:
				PenDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Pen* m_pPen;
			#endif
			};

			class Brush : public virtual GAIA::RENDER::Render2D::Brush
			{
			public:
				class BrushDesc : public virtual GAIA::RENDER::Render2D::Brush::BrushDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Brush::BrushDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Brush::BrushDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Brush(){this->init();}
				GINL ~Brush(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pBrush = new Gdiplus::SolidBrush((Gdiplus::Color)0xFF000000);
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::Brush::BrushDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pBrush);
				#endif
					m_desc.reset();
				}
				virtual const BrushDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_BRUSH;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pBrush == GNIL)
						return GAIA::False;
					GAIA::MATH::ARGB<GAIA::REAL> crNew = cr;
					crNew.tobytemode();
					Gdiplus::Color crTemp(crNew.a, crNew.r, crNew.g, crNew.b);
					if(m_pBrush->SetColor(crTemp) != Gdiplus::Ok)
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_pBrush == GNIL)
						return GAIA::False;
					Gdiplus::Color crTemp;
					if(m_pBrush->GetColor(&crTemp) != Gdiplus::Ok)
						return GAIA::False;
					cr.a = (GAIA::REAL)crTemp.GetA();
					cr.r = (GAIA::REAL)crTemp.GetR();
					cr.g = (GAIA::REAL)crTemp.GetG();
					cr.b = (GAIA::REAL)crTemp.GetB();
					cr.torealmode();
				#endif
					return GAIA::True;
				}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::SolidBrush* GetInternalBrush() const{return m_pBrush;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pBrush = GNIL;
				#endif
				}
			private:
				BrushDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::SolidBrush* m_pBrush;
			#endif
			};

			class FontFamily : public virtual GAIA::RENDER::Render2D::FontFamily
			{
			public:
				class FontFamilyDesc : public virtual GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontFamily(){this->init();}
				GINL ~FontFamily(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pFontFamily = new Gdiplus::FontFamily(desc.strFontName, GNIL);
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::FontFamily::FontFamilyDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pFontFamily);
				#endif
					m_desc.reset();
				}
				virtual const FontFamilyDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFAMILY;}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::FontFamily* GetInternalFontFamily() const{return m_pFontFamily;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pFontFamily = GNIL;
				#endif
				}
			private:
				FontFamilyDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::FontFamily* m_pFontFamily;
			#endif
			};

			class FontPainter : public virtual GAIA::RENDER::Render2D::FontPainter
			{
			public:
				class FontPainterDesc : public virtual GAIA::RENDER::Render2D::FontPainter::FontPainterDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontPainter::FontPainterDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontPainter::FontPainterDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontPainter(){this->init();}
				GINL ~FontPainter(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA::RENDER::Render2DGDIPlus::FontFamily* pFontFamily = GDCAST(GAIA::RENDER::Render2DGDIPlus::FontFamily*)(desc.pFontFamily);
					GAIA_AST(pFontFamily != GNIL);
					if(pFontFamily == GNIL)
						return GAIA::False;
					GAIA::N32 nStyle = 0;
					if(desc.bBold)
						nStyle |= Gdiplus::FontStyleBold;
					if(desc.bItalic)
						nStyle |= Gdiplus::FontStyleItalic;
					if(desc.bUnderline)
						nStyle |= Gdiplus::FontStyleUnderline;
					m_pFont = new Gdiplus::Font(pFontFamily->GetInternalFontFamily(), desc.rSize, nStyle, Gdiplus::UnitPixel);
					desc.pFontFamily->Reference();
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::FontPainter::FontPainterDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_desc.pFontFamily->Release();
					GAIA_DELETE_SAFE(m_pFont);
				#endif
					m_desc.reset();
				}
				virtual const FontPainterDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTPAINTER;}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Font* GetInternalFontPainter() const{return m_pFont;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pFont = GNIL;
				#endif
				}
			private:
				FontPainterDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Font* m_pFont;
			#endif
			};

			class FontFormat : public virtual GAIA::RENDER::Render2D::FontFormat
			{
			public:
				class FontFormatDesc : public virtual GAIA::RENDER::Render2D::FontFormat::FontFormatDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontFormat(){this->init();}
				GINL ~FontFormat(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::FontFormat::FontFormatDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				#endif
					m_desc.reset();
				}
				virtual const FontFormatDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFORMAT;}
				virtual GAIA::BL SetAlignDirectionH(GAIA::N8 nDirection)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(nDirection < 0)
					{
						if(m_StringFmt.SetAlignment(Gdiplus::StringAlignmentNear) != Gdiplus::Ok)
							return GAIA::False;
					}
					else if(nDirection > 0)
					{
						if(m_StringFmt.SetAlignment(Gdiplus::StringAlignmentFar) != Gdiplus::Ok)
							return GAIA::False;
					}
					else
					{
						if(m_StringFmt.SetAlignment(Gdiplus::StringAlignmentCenter) != Gdiplus::Ok)
							return GAIA::False;
					}
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL GetAlignDirectionH(GAIA::N8& nDirection)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_StringFmt.GetAlignment() == Gdiplus::StringAlignmentNear)
						nDirection = -1;
					else if(m_StringFmt.GetAlignment() == Gdiplus::StringAlignmentFar)
						nDirection = +1;
					else if(m_StringFmt.GetAlignment() == Gdiplus::StringAlignmentCenter)
						nDirection = 0;
					else
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL SetAlignDirectionV(GAIA::N8 nDirection)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(nDirection < 0)
					{
						if(m_StringFmt.SetLineAlignment(Gdiplus::StringAlignmentNear) != Gdiplus::Ok)
							return GAIA::False;
					}
					else if(nDirection > 0)
					{
						if(m_StringFmt.SetLineAlignment(Gdiplus::StringAlignmentFar) != Gdiplus::Ok)
							return GAIA::False;
					}
					else
					{
						if(m_StringFmt.SetLineAlignment(Gdiplus::StringAlignmentCenter) != Gdiplus::Ok)
							return GAIA::False;
					}
				#endif
					return GAIA::False;
				}
				virtual GAIA::BL GetAlignDirectionV(GAIA::N8& nDirection)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(m_StringFmt.GetLineAlignment() == Gdiplus::StringAlignmentNear)
						nDirection = -1;
					else if(m_StringFmt.GetLineAlignment() == Gdiplus::StringAlignmentFar)
						nDirection = +1;
					else if(m_StringFmt.GetLineAlignment() == Gdiplus::StringAlignmentCenter)
						nDirection = 0;
					else
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL EnableWrap(GAIA::BL bEnable)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA::N32 nFlagMask = m_StringFmt.GetFormatFlags();
					if(bEnable)
						nFlagMask |= Gdiplus::StringFormatFlagsNoWrap;
					else
						nFlagMask &= (~((GAIA::N32)Gdiplus::StringFormatFlagsNoWrap));
					if(m_StringFmt.SetFormatFlags(nFlagMask) != Gdiplus::Ok)
						return GAIA::False;
				#endif
					return GAIA::True;
				}
				virtual GAIA::BL IsEnableWrap(GAIA::BL& bEnable)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA::N32 nFlagMask = m_StringFmt.GetFormatFlags();
					if(nFlagMask & Gdiplus::StringFormatFlagsNoWrap)
						bEnable = GAIA::False;
					else
						bEnable = GAIA::True;
				#endif
					return GAIA::True;
				}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				const Gdiplus::StringFormat& GetInternalFontFormat() const{return m_StringFmt;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				#endif
				}
			private:
				FontFormatDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::StringFormat m_StringFmt;
			#endif
			};

			class Target : public virtual GAIA::RENDER::Render2D::Target
			{
			public:
				class TargetDesc : public virtual GAIA::RENDER::Render2D::Target::TargetDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Target::TargetDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Target::TargetDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~Target(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const TargetDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_TARGET;}
			private:
				TargetDesc m_desc;
			};

			class Shader : public virtual GAIA::RENDER::Render2D::Shader
			{
			public:
				class ShaderDesc : public virtual GAIA::RENDER::Render2D::Shader::ShaderDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Shader::ShaderDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Shader::ShaderDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~Shader(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const ShaderDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_SHADER;}
			private:
				ShaderDesc m_desc;
			};

			class Texture : public virtual GAIA::RENDER::Render2D::Texture
			{
			public:
				class TextureDesc : public virtual GAIA::RENDER::Render2D::Texture::TextureDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Texture::TextureDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Texture::TextureDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Texture(){this->init();}
				GINL ~Texture(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(GAIA::ALGO::stremp(desc.pszFileName))
					{
						Gdiplus::PixelFormat pf = PixelFormatUndefined;
						if(desc.channelfunction == GAIA::RENDER::Render::ImageFormatDesc::CHANNEL_FUNCTION_COLOR)
						{
							if(desc.channeldatatype == GAIA::RENDER::Render::ImageFormatDesc::CHANNEL_DATATYPE_INTEGER)
							{
								if(desc.compresstype == GAIA::RENDER::Render::ImageFormatDesc::COMPRESS_TYPE_NONE)
								{
									if(desc.uBPC[0] == 8 && desc.uBPC[1] == 8 && desc.uBPC[2] == 8 && desc.uBPC[3] == 8 && desc.uChannelCount == 4)
										pf = PixelFormat32bppARGB;
									else if(desc.uBPC[0] == 0 && desc.uBPC[1] == 8 && desc.uBPC[2] == 8 && desc.uBPC[3] == 8 && desc.uChannelCount == 3)
										pf = PixelFormat24bppRGB;
									else if(desc.uBPC[0] == 0 && desc.uBPC[1] == 8 && desc.uBPC[2] == 8 && desc.uBPC[3] == 8 && desc.uChannelCount == 4)
										pf = PixelFormat32bppRGB;
								}
							}
						}
						if(pf == PixelFormatUndefined)
							return GAIA::False;
						m_pImage = new Gdiplus::Bitmap(desc.uWidth, desc.uHeight, pf);
					}
					else
					{
						m_pImage = new Gdiplus::Bitmap(desc.pszFileName, GAIA::False);
						if(m_pImage == GNIL)
							return GAIA::False;
					}
				#endif
					m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::Texture::TextureDesc&)(desc);
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					if(!GAIA::ALGO::stremp(desc.pszFileName))
					{
						m_desc.channeldatatype = GAIA::RENDER::Render2D::ImageFormatDesc::CHANNEL_DATATYPE_INTEGER;
						m_desc.channelfunction = GAIA::RENDER::Render2D::ImageFormatDesc::CHANNEL_FUNCTION_COLOR;
						Gdiplus::PixelFormat pf = m_pImage->GetPixelFormat();
						switch(pf)
						{
						case PixelFormat1bppIndexed:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_INDEXED;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 1;
								m_desc.uBPC[2] = 0;
								m_desc.uBPC[3] = 0;
							}
							break;
						case PixelFormat4bppIndexed:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_INDEXED;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 4;
								m_desc.uBPC[2] = 0;
								m_desc.uBPC[3] = 0;
							}
							break;
						case PixelFormat8bppIndexed:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_INDEXED;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 8;
								m_desc.uBPC[2] = 0;
								m_desc.uBPC[3] = 0;
							}
							break;
						case PixelFormat16bppGrayScale:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 16;
								m_desc.uBPC[2] = 0;
								m_desc.uBPC[3] = 0;
							}
							break;
						case PixelFormat16bppRGB555:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 5;
								m_desc.uBPC[2] = 5;
								m_desc.uBPC[3] = 5;
							}
							break;
						case PixelFormat16bppRGB565:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 5;
								m_desc.uBPC[2] = 6;
								m_desc.uBPC[3] = 5;
							}
							break;
						case PixelFormat16bppARGB1555:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 1;
								m_desc.uBPC[1] = 5;
								m_desc.uBPC[2] = 5;
								m_desc.uBPC[3] = 5;
							}
							break;
						case PixelFormat24bppRGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
							}
							m_desc.uBPC[0] = 0;
							m_desc.uBPC[1] = 8;
							m_desc.uBPC[2] = 8;
							m_desc.uBPC[3] = 8;
							break;
						case PixelFormat32bppRGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 8;
								m_desc.uBPC[1] = 8;
								m_desc.uBPC[2] = 8;
								m_desc.uBPC[3] = 8;
							}
							break;
						case PixelFormat32bppARGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 8;
								m_desc.uBPC[1] = 8;
								m_desc.uBPC[2] = 8;
								m_desc.uBPC[3] = 8;
							}
							break;
						case PixelFormat32bppPARGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 8;
								m_desc.uBPC[1] = 8;
								m_desc.uBPC[2] = 8;
								m_desc.uBPC[3] = 8;
							}
							break;
						case PixelFormat48bppRGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 0;
								m_desc.uBPC[1] = 16;
								m_desc.uBPC[2] = 16;
								m_desc.uBPC[3] = 16;
							}
							break;
						case PixelFormat64bppARGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 16;
								m_desc.uBPC[1] = 16;
								m_desc.uBPC[2] = 16;
								m_desc.uBPC[3] = 16;
							}
							break;
						case PixelFormat64bppPARGB:
							{
								m_desc.compresstype = GAIA::RENDER::Render2D::ImageFormatDesc::COMPRESS_TYPE_NONE;
								m_desc.uBPC[0] = 16;
								m_desc.uBPC[1] = 16;
								m_desc.uBPC[2] = 16;
								m_desc.uBPC[3] = 16;
							}
							break;
						default:
							return GAIA::False;
						}
					}
				#endif
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pImage);
				#endif
					m_desc.reset();
				}
				virtual const TextureDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_TEXTURE;}
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Image* GetInternalTexture() const{return m_pImage;}
			#endif
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pImage = GNIL;
				#endif
				}
			private:
				TextureDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Image* m_pImage;
			#endif
			};

		public:
			GINL Render2DGDIPlus(){this->init();}
			GINL ~Render2DGDIPlus(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS;}

			virtual GAIA::BL Create(const GAIA::RENDER::Render::RenderDesc& desc)
			{
				if(m_bCreated)
					return GAIA::False;

				if(!desc.check())
					return GAIA::False;

				desc.pCanvas->Reference();
				m_desc = GDCAST(const GAIA::RENDER::Render2DGDIPlus::RenderDesc&)(desc);

				GAIA::GVOID* pHandle = desc.pCanvas->GetHandle();
				GAIA_AST(pHandle != GNIL);

			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				HWND hWnd = GSCAST(HWND)(pHandle);
				m_hDC = ::GetDC(hWnd);
				m_pGraphics = new Gdiplus::Graphics(m_hDC);
				m_pSwapBitmap = new Gdiplus::Bitmap(desc.pCanvas->Size().x, desc.pCanvas->Size().y, PixelFormat32bppARGB);
				m_pSwapGraphics = new Gdiplus::Graphics(m_pSwapBitmap);
			#endif

				m_bCreated = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL Destroy()
			{
				if(!m_bCreated)
					return GAIA::False;

				GAIA::GVOID* pHandle = m_desc.pCanvas->GetHandle();
				GAIA_AST(pHandle != GNIL);

			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_hDC != GNIL)
				{
					HWND hWnd = GSCAST(HWND)(pHandle);
					::ReleaseDC(hWnd, m_hDC);
					m_hDC = GNIL;
				}
				GAIA_DELETE_SAFE(m_pGraphics);
				GAIA_DELETE_SAFE(m_pSwapGraphics);
				GAIA_DELETE_SAFE(m_pSwapBitmap);
			#endif

				m_desc.pCanvas->Release();
				m_desc.reset();

				m_bCreated = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsCreated() const
			{
				return m_bCreated;
			}
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const
			{
				return m_desc;
			}

			virtual GAIA::GVOID Flush()
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pGraphics == GNIL)
					return;
				if(m_pSwapBitmap == GNIL)
					return;
				m_pGraphics->DrawImage(
					m_pSwapBitmap, 0, 0, 
					m_pSwapBitmap->GetWidth(), 
					m_pSwapBitmap->GetHeight());
			#endif
			}

		public:
			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pSwapGraphics == GNIL)
					return;
				GAIA::MATH::ARGB<GAIA::REAL> crNew = cr;
				crNew.tobytemode();
				Gdiplus::Color crTemp(crNew.a, crNew.r, crNew.g, crNew.b);
				m_pSwapGraphics->Clear(crTemp);
			#endif
			}

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(const QUALITY2D_STATE& qs, const GAIA::CH* pszState)
			{
				if(!GAIA_ENUM_VALID(QUALITY2D_STATE, qs))
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetQuality2DState(qs, RENDER2D_QUALITYSTATE_DEFAULT[qs]);
				switch(qs)
				{
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_NONE]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeDefault) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_LOW]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_MID]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias) != Gdiplus::Ok)
								return;
						}
						else
							GAIA_AST(GAIA::ALWAYSFALSE);
					#endif
					}
					break;
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_NONE]) == 0)
						{
							if(m_pSwapGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_LOW]) == 0)
						{
							if(m_pSwapGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_MID]) == 0)
						{
							if(m_pSwapGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH]) == 0)
						{
							if(m_pSwapGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit) != Gdiplus::Ok)
								return;
						}
						else
							GAIA_AST(GAIA::ALWAYSFALSE);
					#endif
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetQuality2DState(const QUALITY2D_STATE& qs)
			{
				if(!GAIA_ENUM_VALID(QUALITY2D_STATE, qs))
					return GNILSTR;
				switch(qs)
				{
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						Gdiplus::SmoothingMode sm = m_pSwapGraphics->GetSmoothingMode();
						switch(sm)
						{
						case Gdiplus::SmoothingModeDefault:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_NONE];
						case Gdiplus::SmoothingModeHighSpeed:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_LOW];
						case Gdiplus::SmoothingModeHighQuality:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_MID];
						case Gdiplus::SmoothingModeAntiAlias:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH];
						default:
							GAIA_AST(GAIA::ALWAYSFALSE);
							break;
						}
					#endif
					}
					break;
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						Gdiplus::TextRenderingHint trh = m_pSwapGraphics->GetTextRenderingHint();
						switch(trh)
						{
						case Gdiplus::TextRenderingHintSingleBitPerPixel:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_NONE];
						case Gdiplus::TextRenderingHintSingleBitPerPixelGridFit:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_LOW];
						case Gdiplus::TextRenderingHintAntiAlias:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_MID];
						case Gdiplus::TextRenderingHintClearTypeGridFit:
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_HIGH];
						default:
							GAIA_AST(GAIA::ALWAYSFALSE);
							break;
						}
					#endif
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs, const GAIA::CH* pszState)
			{
				if(!GAIA_ENUM_VALID(RENDER2D_STATE, rs))
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetRender2DState(rs, RENDER2D_RENDERSTATE_DEFAULT[rs]);
				switch(rs)
				{
				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND:
					{
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
							m_bEnableAlphaBlend = GAIA::True;
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF]) == 0)
							m_bEnableAlphaBlend = GAIA::False;
					}
					break;

				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHATEST:
					{
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
							m_bEnableAlphaTest = GAIA::True;
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF]) == 0)
							m_bEnableAlphaTest = GAIA::False;
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetRender2DState(const RENDER2D_STATE& rs) const
			{
				if(!GAIA_ENUM_VALID(RENDER2D_STATE, rs))
					return GNILSTR;
				switch(rs)
				{
				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND:
					{
						if(m_bEnableAlphaBlend)
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON];
						else
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF];
					}
					break;

				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHATEST:
					{
						if(m_bEnableAlphaTest)
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON];
						else
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF];
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState)
			{
				if(!GAIA_ENUM_VALID(SAMPLER2D_STATE, ss))
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetSampler2DState(nSamplerIndex, ss, RENDER2D_SAMPLERSTATE_DEFAULT[ss]);
				switch(ss)
				{
				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSU:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const
			{
				if(!GAIA_ENUM_VALID(SAMPLER2D_STATE, ss))
					return GNILSTR;
				switch(ss)
				{
				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSU:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(const GAIA::RENDER::Render2D::Pen::PenDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Pen* pPen = GDCAST(Pen*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_PEN, GNIL));
				GAIA_AST(pPen != GNIL);
				if(pPen == GNIL)
					return GNIL;
				pPen->SetRender(this);
				if(!pPen->Create(desc))
				{
					pPen->Release();
					return GNIL;
				}
				return pPen;
			#else
				return GNIL;
			#endif
			}

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Brush* pBrush = GDCAST(Brush*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_BRUSH, GNIL));
				pBrush->SetRender(this);
				if(!pBrush->Create(desc))
				{
					pBrush->Release();
					return GNIL;
				}
				return pBrush;
			#else
				return GNIL;
			#endif
			}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				FontFamily* pFontFamily = GDCAST(FontFamily*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFAMILY, GNIL));
				GAIA_AST(pFontFamily != GNIL);
				if(pFontFamily == GNIL)
					return GNIL;
				pFontFamily->SetRender(this);
				if(!pFontFamily->Create(desc))
				{
					pFontFamily->Release();
					return GNIL;
				}
				return pFontFamily;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				FontPainter* pFontPainter = GDCAST(FontPainter*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTPAINTER, GNIL));
				GAIA_AST(pFontPainter != GNIL);
				if(pFontPainter == GNIL)
					return GNIL;
				pFontPainter->SetRender(this);
				if(!pFontPainter->Create(desc))
				{
					pFontPainter->Release();
					return GNIL;
				}
				return pFontPainter;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				FontFormat* pFontFormat = GDCAST(FontFormat*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFORMAT, GNIL));
				GAIA_AST(pFontFormat != GNIL);
				if(pFontFormat == GNIL)
					return GNIL;
				pFontFormat->SetRender(this);
				if(!pFontFormat->Create(desc))
				{
					pFontFormat->Release();
					return GNIL;
				}
				return pFontFormat;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID DrawFontPainter(
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				GAIA::RENDER::Render2D::Brush* pBrush,
				GAIA::RENDER::Render2D::FontFormat* pFontFormat)
			{
				GPCHR_NULLSTRPTR(pszText);
				GPCHR_NULL(pFontPainter);
				GPCHR_NULL(pBrush);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pSwapGraphics == GNIL)
					return;

				/* Change alpha for pipeline. */
				GAIA::BL bCurrentAlphaBlend;
				GAIA::MATH::ARGB<GAIA::REAL> crOld;
				const GAIA::CH* pszAlphaBlendState = this->GetRender2DState(GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
				if(GAIA::ALGO::strcmp(pszAlphaBlendState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
					bCurrentAlphaBlend = GAIA::True;
				else
				{
					bCurrentAlphaBlend = GAIA::False;
					pBrush->GetColor(crOld);
					GAIA::MATH::ARGB<GAIA::REAL> crNew = crOld;
					crNew.a = 1.0F;
					pBrush->SetColor(crNew);
				}

				/* Render. */
				GAIA::RENDER::Render2DGDIPlus::FontPainter* pPracFontPainter = GDCAST(GAIA::RENDER::Render2DGDIPlus::FontPainter*)(pFontPainter);
				GAIA::RENDER::Render2DGDIPlus::Brush* pPracBrush = GDCAST(GAIA::RENDER::Render2DGDIPlus::Brush*)(pBrush);
				GPCHR_NULL(pPracFontPainter);
				GPCHR_NULL(pPracBrush);
				Gdiplus::RectF rc;
				rc.X = aabr.pmin.x;
				rc.Y = aabr.pmin.y;
				rc.Width = aabr.width();
				rc.Height = aabr.height();
				if(pFontFormat == GNIL)
				{
					Gdiplus::StringFormat sf;
					m_pSwapGraphics->DrawString(
						pszText, GAIA::ALGO::strlen(pszText),
						pPracFontPainter->GetInternalFontPainter(), 
						rc, &sf, 
						pPracBrush->GetInternalBrush());
				}
				else
				{
					GAIA::RENDER::Render2DGDIPlus::FontFormat* pPracFontFormat = GDCAST(GAIA::RENDER::Render2DGDIPlus::FontFormat*)(pFontFormat);
					GPCHR_NULL(pPracFontFormat);
					m_pSwapGraphics->DrawString(
						pszText, GAIA::ALGO::strlen(pszText),
						pPracFontPainter->GetInternalFontPainter(), 
						rc, &pPracFontFormat->GetInternalFontFormat(), 
						pPracBrush->GetInternalBrush());
				}

				/* Restore alpha for pipeline. */
				if(!bCurrentAlphaBlend)
					pBrush->SetColor(crOld);
			#endif
			}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Texture* pTex = GDCAST(Texture*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_TEXTURE, GNIL));
				GAIA_AST(pTex != GNIL);
				if(pTex == GNIL)
					return GNIL;
				pTex->SetRender(this);
				if(!pTex->Create(desc))
				{
					pTex->Release();
					return GNIL;
				}
				return pTex;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture)
			{
			}
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const
			{
			}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc)
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget)
			{
			}
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const
			{
			}

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc)
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render2D::Shader* pShader)
			{
			}
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render2D::Shader*& pShader) const
			{
			}
			virtual GAIA::GVOID SetShaderConstant()
			{
			}
			virtual GAIA::GVOID GetShaderConstant() const
			{
			}

			/* Draw. */
			virtual GAIA::GVOID DrawLine(
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e,
				GAIA::RENDER::Render2D::Pen* pPen)
			{
				GPCHR_NULL(pPen);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pSwapGraphics == GNIL)
					return;

				/* Change alpha for pipeline. */
				GAIA::BL bCurrentAlphaBlend;
				GAIA::MATH::ARGB<GAIA::REAL> crOld;
				const GAIA::CH* pszAlphaBlendState = this->GetRender2DState(GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
				if(GAIA::ALGO::strcmp(pszAlphaBlendState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
					bCurrentAlphaBlend = GAIA::True;
				else
				{
					bCurrentAlphaBlend = GAIA::False;
					pPen->GetColor(crOld);
					GAIA::MATH::ARGB<GAIA::REAL> crNew = crOld;
					crNew.a = 1.0F;
					pPen->SetColor(crNew);
				}

				/* Render. */
				GAIA::RENDER::Render2DGDIPlus::Pen* pPracPen = GDCAST(GAIA::RENDER::Render2DGDIPlus::Pen*)(pPen);
				GPCHR_NULL(pPracPen);
				m_pSwapGraphics->DrawLine(pPracPen->GetInternalPen(), s.x, s.y, e.x, e.y);

				/* Restore alpha for pipeline. */
				if(!bCurrentAlphaBlend)
					pPen->SetColor(crOld);
			#endif
			}
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::Brush* pBrush)
			{
				GPCHR_NULL(pBrush);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pSwapGraphics == GNIL)
					return;

				/* Change alpha for pipeline. */
				GAIA::BL bCurrentAlphaBlend;
				GAIA::MATH::ARGB<GAIA::REAL> crOld;
				const GAIA::CH* pszAlphaBlendState = this->GetRender2DState(GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
				if(GAIA::ALGO::strcmp(pszAlphaBlendState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
					bCurrentAlphaBlend = GAIA::True;
				else
				{
					bCurrentAlphaBlend = GAIA::False;
					pBrush->GetColor(crOld);
					GAIA::MATH::ARGB<GAIA::REAL> crNew = crOld;
					crNew.a = 1.0F;
					pBrush->SetColor(crNew);
				}

				/* Render. */
				GAIA::RENDER::Render2DGDIPlus::Brush* pPracBrush = GDCAST(GAIA::RENDER::Render2DGDIPlus::Brush*)(pBrush);
				GPCHR_NULL(pPracBrush);
				m_pSwapGraphics->FillRectangle(pPracBrush->GetInternalBrush(), aabr.pmin.x, aabr.pmin.y, aabr.width(), aabr.height());

				/* Restore alpha for pipeline. */
				if(!bCurrentAlphaBlend)
					pBrush->SetColor(crOld);
			#endif
			}
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3,
				GAIA::RENDER::Render2D::Brush* pBrush)
			{
				GPCHR_NULL(pBrush);
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				if(m_pSwapGraphics == GNIL)
					return;

				/* Change alpha for pipeline. */
				GAIA::BL bCurrentAlphaBlend;
				GAIA::MATH::ARGB<GAIA::REAL> crOld;
				const GAIA::CH* pszAlphaBlendState = this->GetRender2DState(GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
				if(GAIA::ALGO::strcmp(pszAlphaBlendState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
					bCurrentAlphaBlend = GAIA::True;
				else
				{
					bCurrentAlphaBlend = GAIA::False;
					pBrush->GetColor(crOld);
					GAIA::MATH::ARGB<GAIA::REAL> crNew = crOld;
					crNew.a = 1.0F;
					pBrush->SetColor(crNew);
				}

				/* Render. */
				GAIA::RENDER::Render2DGDIPlus::Brush* pPracBrush = GDCAST(GAIA::RENDER::Render2DGDIPlus::Brush*)(pBrush);
				GPCHR_NULL(pPracBrush);
				Gdiplus::PointF posTemp[3];
				posTemp[0].X = pos1.x;
				posTemp[0].Y = pos1.y;
				posTemp[1].X = pos2.x;
				posTemp[1].Y = pos2.y;
				posTemp[2].X = pos3.x;
				posTemp[2].Y = pos3.y;
				m_pSwapGraphics->FillPolygon(pPracBrush->GetInternalBrush(), posTemp, 3, Gdiplus::FillModeAlternate);

				/* Restore alpha for pipeline. */
				if(!bCurrentAlphaBlend)
					pBrush->SetColor(crOld);
			#endif
			}

			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM)
			{
			}
		private:
			GINL GAIA::GVOID init()
			{
				m_bCreated = GAIA::False;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				m_hDC = GNIL;
				m_pGraphics = GNIL;
				m_pSwapGraphics = GNIL;
				m_pSwapBitmap = GNIL;
			#endif
				m_bEnableAlphaBlend = GAIA::False;
				m_bEnableAlphaTest = GAIA::False;
			}

		private:
			GAIA::BL m_bCreated;
			RenderDesc m_desc;

		#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
			HDC m_hDC;
			Gdiplus::Graphics* m_pGraphics;
			Gdiplus::Graphics* m_pSwapGraphics;
			Gdiplus::Bitmap* m_pSwapBitmap;
		#endif

			GAIA::U8 m_bEnableAlphaBlend : 1;
			GAIA::U8 m_bEnableAlphaTest : 1;
		};
	};
};

#endif
