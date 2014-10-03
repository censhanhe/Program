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
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL Pen(){this->init();}
				GINL ~Pen(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Pen::PenDesc& desc)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pGDIPPen = new Gdiplus::Pen((Gdiplus::Color)0xFF000000, 1.0F);
				#endif
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pGDIPPen);
				#endif
				}
				const PenDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_PEN;}
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pGDIPPen = GNIL;
				#endif
				}
			private:
				PenDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::Pen* m_pGDIPPen;
			#endif
			};

			class Brush : public virtual GAIA::RENDER::Render2D::Brush
			{
			public:
				class BrushDesc : public virtual GAIA::RENDER::Render2D::Brush::BrushDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL Brush(){this->init();}
				GINL ~Brush(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Brush::BrushDesc& desc)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pGDIPBrush = new Gdiplus::SolidBrush((Gdiplus::Color)0xFF000000);
				#endif
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					GAIA_DELETE_SAFE(m_pGDIPBrush);
				#endif
				}
				const BrushDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_BRUSH;}
			private:
				GINL GAIA::GVOID init()
				{
				#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
					m_pGDIPBrush = GNIL;
				#endif
				}
			private:
				BrushDesc m_desc;
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				Gdiplus::SolidBrush* m_pGDIPBrush;
			#endif
			};

			class FontFamily : public virtual GAIA::RENDER::Render2D::FontFamily
			{
			public:
				class FontFamilyDesc : public virtual GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~FontFamily(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const FontFamilyDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFAMILY;}
			private:
				FontFamilyDesc m_desc;
			};

			class FontPainter : public virtual GAIA::RENDER::Render2D::FontPainter
			{
			public:
				class FontPainterDesc : public virtual GAIA::RENDER::Render2D::FontPainter::FontPainterDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~FontPainter(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const FontPainterDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTPAINTER;}
			private:
				FontPainterDesc m_desc;
			};

			class FontFormat : public virtual GAIA::RENDER::Render2D::FontFormat
			{
			public:
				class FontFormatDesc : public virtual GAIA::RENDER::Render2D::FontFormat::FontFormatDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~FontFormat(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const FontFormatDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTFORMAT;}
			private:
				FontFormatDesc m_desc;
			};

			class Target : public virtual GAIA::RENDER::Render2D::Target
			{
			public:
				class TargetDesc : public virtual GAIA::RENDER::Render2D::Target::TargetDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~Target(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const TargetDesc& GetDesc() const{return m_desc;}
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
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~Shader(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const ShaderDesc& GetDesc() const{return m_desc;}
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
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				GINL ~Texture(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Texture::TextureDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const TextureDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_TEXTURE;}
			private:
				TextureDesc m_desc;
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
				if(m_pSwapGraphics == GNIL)
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
				Gdiplus::Color crTemp(cr.a * 255.0F, cr.r * 255.0F, cr.g * 255.0F, cr.b * 255.0F);
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
				case QUALITY2D_STATE_ANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						if(GAIA::ALGO::strcmp(pszState, RENDER_STATEWORD_STRING[RENDER_STATEWORD_NONE]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeDefault) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, RENDER_STATEWORD_STRING[RENDER_STATEWORD_LOW]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, RENDER_STATEWORD_STRING[RENDER_STATEWORD_MID]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality) != Gdiplus::Ok)
								return;
						}
						else if(GAIA::ALGO::strcmp(pszState, RENDER_STATEWORD_STRING[RENDER_STATEWORD_HIGH]) == 0)
						{
							if(m_pSwapGraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias) != Gdiplus::Ok)
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
					return GNIL;
				switch(qs)
				{
				case QUALITY2D_STATE_ANTIALIAS:
					{
					#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
						Gdiplus::SmoothingMode sm = m_pSwapGraphics->GetSmoothingMode();
						switch(sm)
						{
						case Gdiplus::SmoothingModeDefault:
							return RENDER_STATEWORD_STRING[RENDER_STATEWORD_NONE];
						case Gdiplus::SmoothingModeHighSpeed:
							return RENDER_STATEWORD_STRING[RENDER_STATEWORD_LOW];
						case Gdiplus::SmoothingModeHighQuality:
							return RENDER_STATEWORD_STRING[RENDER_STATEWORD_MID];
						case Gdiplus::SmoothingModeAntiAlias:
							return RENDER_STATEWORD_STRING[RENDER_STATEWORD_HIGH];
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
				return GNIL;
			}
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs, const GAIA::CH* pszState)
			{
				if(!GAIA_ENUM_VALID(RENDER2D_STATE, rs))
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetRender2DState(rs, RENDER2D_RENDERSTATE_DEFAULT[rs]);
				switch(rs)
				{
				case RENDER2D_STATE_ALPHABLEND:
					{
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
					return GNIL;
				switch(rs)
				{
				case RENDER2D_STATE_ALPHABLEND:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNIL;
			}
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState)
			{
				if(!GAIA_ENUM_VALID(SAMPLER2D_STATE, ss))
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetSampler2DState(nSamplerIndex, ss, RENDER2D_SAMPLERSTATE_DEFAULT[ss]);
				switch(ss)
				{
				case SAMPLER2D_STATE_ADDRESSU:
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
					return GNIL;
				switch(ss)
				{
				case SAMPLER2D_STATE_ADDRESSU:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNIL;
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
				if(!pPen->Create(*this, GSCAST(const GAIA::RENDER::Render2D::Pen::PenDesc&)(desc)))
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
				if(!pBrush->Create(*this, GSCAST(const GAIA::RENDER::Render2D::Brush::BrushDesc&)(desc)))
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
				if(!pFontFamily->Create(*this, GSCAST(const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc&)(desc)))
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
				GAIA::RENDER::Render2D::FontFamily& ff,
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)
				FontPainter* pFontPainter = GDCAST(FontPainter*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS_FONTPAINTER, GNIL));
				GAIA_AST(pFontPainter != GNIL);
				if(pFontPainter == GNIL)
					return GNIL;
				pFontPainter->SetRender(this);
				if(!pFontPainter->Create(*this, GSCAST(const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc&)(desc)))
				{
					pFontPainter->Release();
					return GNIL;
				}
				return pFontPainter;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID DrawFontPainter(
				const GAIA::TCH* pszText,
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				GAIA::RENDER::Render2D::Brush* pBrush,
				GAIA::RENDER::Render2D::FontFormat* pFontFormat)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS && defined(GAIA_PLATFORM_GDIPLUS)

			#endif
			}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture()
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture)
			{
			}
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const
			{
			}
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr, 
				GAIA::RENDER::Render2D::Texture& tex, 
				const GAIA::MATH::MTX22<GAIA::REAL>& mtxTM)
			{
			}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget()
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
			virtual GAIA::RENDER::Render2D::Shader* CreateShader()
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
			}
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::Brush* pBrush)
			{
			}
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL> pos[3],
				GAIA::RENDER::Render2D::Brush* pBrush)
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
		};
	};
};

#endif
