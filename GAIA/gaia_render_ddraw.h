#ifndef		__GAIA_RENDER_DDRAW_H__
#define		__GAIA_RENDER_DDRAW_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render2DDDraw : public virtual GAIA::RENDER::Render2D
		{
		public:
			typedef GAIA::RENDER::Render2DDDraw __MyType;

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
				GINL ~Pen(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Pen::PenDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const PenDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_PEN;}
			private:
				PenDesc m_desc;
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
				GINL ~Brush(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::Brush::BrushDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const BrushDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_BRUSH;}
			private:
				BrushDesc m_desc;
			};

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
				GINL ~FontPainterFamily(){this->Destroy();}
				virtual GAIA::BL Create(GAIA::RENDER::Render2D& render, const GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){}
				const FontPainterFamilyDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_FONTFAMILY;}
			private:
				FontPainterFamilyDesc m_desc;
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_FONTPAINTER;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_FONTFORMAT;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TARGET;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_SHADER;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TEXTURE;}
			private:
				TextureDesc m_desc;
			};

		public:
			GINL Render2DDDraw(){this->init();}
			GINL ~Render2DDDraw(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW;}

			virtual GAIA::BL Create(const GAIA::RENDER::Render::RenderDesc& desc)
			{
				if(m_bCreated)
					return GAIA::False;
				m_bCreated = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL Destroy()
			{
				if(!m_bCreated)
					return GAIA::False;
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
			}

		public:
			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr){}

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(const QUALITY2D_STATE& qs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetQuality2DState(const QUALITY2D_STATE& qs){return GNIL;}
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetRender2DState(const RENDER2D_STATE& rs) const{return GNIL;}
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const{return GNIL;}

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(const GAIA::RENDER::Render2D::Pen::PenDesc& desc){return GNIL;}

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc){return GNIL;}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontPainterFamily* CreateFontPainterFamily(
				const GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainterPainter(
				GAIA::RENDER::Render2D::FontPainterFamily& ff,
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GNIL;}
			virtual GAIA::GVOID DrawFontPainter(
				const GAIA::TCH* pszText,
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				GAIA::RENDER::Render2D::Brush* pBrush,
				GAIA::RENDER::Render2D::FontFormat* pFontFormat){}

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
				GAIA::RENDER::Render2D::Pen* pPen){}
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::Brush* pBrush){}
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL> pos[3],
				GAIA::RENDER::Render2D::Brush* pBrush){}

		private:
			GINL GAIA::GVOID init()
			{
				m_bCreated = GAIA::False;
			}

		private:
			GAIA::BL m_bCreated;
			RenderDesc m_desc;
		};
	};
};

#endif
