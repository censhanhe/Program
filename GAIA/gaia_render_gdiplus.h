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
			class FontPainterFamily : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class FontPainterFamilyDesc : public virtual GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const FontPainterFamilyDesc& GetDesc() const{return m_desc;}
			private:
				FontPainterFamilyDesc m_desc;
			};

			class FontPainter : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class FontPainterDesc : public virtual GAIA::RENDER::Render2D::FontPainter::FontPainterDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const FontPainterDesc& GetDesc() const{return m_desc;}
			private:
				FontPainterDesc m_desc;
			};

			class Target : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class TargetDesc : public virtual GAIA::RENDER::Render2D::Target::TargetDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const TargetDesc& GetDesc() const{return m_desc;}
			private:
				TargetDesc m_desc;
			};

			class Shader : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class ShaderDesc : public virtual GAIA::RENDER::Render2D::Shader::ShaderDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const ShaderDesc& GetDesc() const{return m_desc;}
			private:
				ShaderDesc m_desc;
			};

			class Texture : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class TextureDesc : public virtual GAIA::RENDER::Render2D::Texture::TextureDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const TextureDesc& GetDesc() const{return m_desc;}
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
					}
					break;

				default:
					GAIA_AST(GAIA::False);
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
					}
					break;

				default:
					GAIA_AST(GAIA::False);
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
					GAIA_AST(GAIA::False);
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
					GAIA_AST(GAIA::False);
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
					GAIA_AST(GAIA::False);
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
					GAIA_AST(GAIA::False);
					break;
				}
				return GNIL;
			}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontPainterFamily* CreateFontPainterFamily(
				const GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainterPainter(
				GAIA::RENDER::Render2D::FontPainterFamily& ff,
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GNIL;}
			virtual GAIA::GVOID DrawFontPainter(
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL>& cr){}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(){return GNIL;}
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture){}
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const{}
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr, 
				GAIA::RENDER::Render2D::Texture& tex, 
				const GAIA::MATH::MTX22<GAIA::REAL>& mtxTM){}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(){return GNIL;}
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget){}
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const{}

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(){return GNIL;}
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render2D::Shader* pShader){}
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render2D::Shader*& pShader) const{}
			virtual GAIA::GVOID SetShaderConstant(){}
			virtual GAIA::GVOID GetShaderConstant() const{}

			/* Draw. */
			virtual GAIA::GVOID DrawLine(
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e,
				const GAIA::MATH::ARGB<GAIA::REAL>& crs,
				const GAIA::MATH::ARGB<GAIA::REAL>& cre, const GAIA::REAL& rWidth){}
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL> crs[4]){}
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL> pos[3],
				const GAIA::MATH::AABR<GAIA::REAL> crs[3]){}

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
