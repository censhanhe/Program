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
			};

		public:
			class FontPainterFamily : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class FontPainterFamilyDesc : public virtual GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc
				{
				public:
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
				};
			public:
				const TextureDesc& GetDesc() const{return m_desc;}
			private:
				TextureDesc m_desc;
			};

		public:
			GINL Render2DDDraw(){this->init();}
			GINL ~Render2DDDraw(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW;}

			virtual GAIA::BL Initialize(const GAIA::RENDER::Render::RenderDesc& desc)
			{
				if(m_bInitialized)
					return GAIA::False;
				m_bInitialized = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL Release()
			{
				if(!m_bInitialized)
					return GAIA::False;
				m_bInitialized = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsInitialized() const
			{
				return m_bInitialized;
			}
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const
			{
				return m_desc;
			}

			virtual GAIA::GVOID Flush()
			{
			}

			/* State. */
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs){}
			virtual GAIA::GVOID GetRender2DState(RENDER2D_STATE& rs) const{}
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss){}
			virtual GAIA::GVOID GetSampler2DState(GAIA::N32 nSamplerIndex, SAMPLER2D_STATE& ss) const{}

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
				m_bInitialized = GAIA::False;
			}

		private:
			GAIA::BL m_bInitialized;
			RenderDesc m_desc;
		};
	};
};

#endif
