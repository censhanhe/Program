#ifndef		__GAIA_RENDER_RENDER2D_H__
#define		__GAIA_RENDER_RENDER2D_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render2D : public virtual GAIA::RENDER::Render
		{
		public:
			typedef GAIA::RENDER::Render2D __MyType;

		public:
			class RenderDesc : public virtual GAIA::RENDER::Render::RenderDesc
			{
			public:
				virtual GAIA::GVOID reset(){GAIA::RENDER::Render::RenderDesc::reset();}
				virtual GAIA::BL check() const
				{
					if(!GAIA::RENDER::Render::RenderDesc::check())
						return GAIA::False;
					return GAIA::True;
				}
			};

		public:
			class FontPainterFamily : public virtual GAIA::RENDER::Resource
			{
			public:
				class FontPainterFamilyDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class FontPainter : public virtual GAIA::RENDER::Resource
			{
			public:
				class FontPainterDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class Target : public virtual GAIA::RENDER::Resource
			{
			public:
				class TargetDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class Shader : public virtual GAIA::RENDER::Resource
			{
			public:
				class ShaderDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class Texture : public virtual GAIA::RENDER::Resource
			{
			public:
				class TextureDesc : public virtual GAIA::FWORK::InstanceDesc
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
			GAIA_ENUM_BEGIN(RENDER2D_STATE)
				RENDER2D_STATE_ALPHABLEND,
				RENDER2D_STATE_ALPHATEST,
				RENDER2D_STATE_CULLMODE,
				RENDER2D_STATE_FILLMODE,
			GAIA_ENUM_END(RENDER2D_STATE)

			GAIA_ENUM_BEGIN(SAMPLER2D_STATE)
				SAMPLER2D_STATE_ADDRESSU,
				SAMPLER2D_STATE_ADDRESSV,
				SAMPLER2D_STATE_MINFILTER,
				SAMPLER2D_STATE_MAXFILTER,
			GAIA_ENUM_END(SAMPLER2D_STATE)

			GAIA_ENUM_BEGIN(ALPHA_BLEND_TYPE)
				ALPHA_BLEND_TYPE_SRCALPHA,
				ALPHA_BLEND_TYPE_DSTALPHA,
				ALPHA_BLEND_TYPE_INVSRCALPHA,
				ALPHA_BLEND_TYPE_INVDSTALPHA,
			GAIA_ENUM_END(ALPHA_BLEND_TYPE)

		public:
			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* State. */
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs) = 0;
			virtual GAIA::GVOID GetRender2DState(RENDER2D_STATE& rs) const = 0;
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) = 0;
			virtual GAIA::GVOID GetSampler2DState(GAIA::N32 nSamplerIndex, SAMPLER2D_STATE& ss) const = 0;

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontPainterFamily* CreateFontPainterFamily(
				const GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainterPainter(
				GAIA::RENDER::Render2D::FontPainterFamily& ff,
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc) = 0;
			virtual GAIA::GVOID DrawFontPainter(
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture() = 0;
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture) = 0;
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const = 0;
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr, 
				GAIA::RENDER::Render2D::Texture& tex, 
				const GAIA::MATH::MTX22<GAIA::REAL>& mtxTM) = 0;

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget() = 0;
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget) = 0;
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const = 0;

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader() = 0;
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render2D::Shader* pShader) = 0;
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render2D::Shader*& pShader) const = 0;
			virtual GAIA::GVOID SetShaderConstant() = 0;
			virtual GAIA::GVOID GetShaderConstant() const = 0;

			/* Draw. */
			virtual GAIA::GVOID DrawLine(
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e,
				const GAIA::MATH::ARGB<GAIA::REAL>& crs,
				const GAIA::MATH::ARGB<GAIA::REAL>& cre, const GAIA::REAL& rWidth) = 0;
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL> crs[4]) = 0;
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL> pos[3],
				const GAIA::MATH::AABR<GAIA::REAL> crs[3]) = 0;

		private:
		};
	};
};

#endif