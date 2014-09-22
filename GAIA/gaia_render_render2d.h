#ifndef		__GAIA_RENDER_RENDER2D_H__
#define		__GAIA_RENDER_RENDER2D_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render2D : public virtual GAIA::RENDER::Render
		{
		public:
			class Render2DDesc : public GAIA::RENDER::Render::RenderDesc
			{
			public:
			};
			class FontFamily : public virtual GAIA::RENDER::Resource
			{
			public:
				class FontFamilyDesc : public GAIA::Base
				{
				public:
				};
			public:
				const FontFamilyDesc& GetDesc() const{return m_desc;}
			private:
				FontFamilyDesc m_desc;
			};

			class Font : public virtual GAIA::RENDER::Resource
			{
			public:
				class FontDesc : public GAIA::Base
				{
				public:
				};
			public:
				const FontDesc& GetDesc() const{return m_desc;}
			private:
				FontDesc m_desc;
			};

			class Target : public virtual GAIA::RENDER::Resource
			{
			public:
				class TargetDesc : public GAIA::Base
				{
				public:
				};
			public:
				const TargetDesc& GetDesc() const{return m_desc;}
			private:
				TargetDesc m_desc;
			};

			class Shader : public virtual GAIA::RENDER::Resource
			{
			public:
				class ShaderDesc : public GAIA::Base
				{
				public:
				};
			public:
				const ShaderDesc& GetDesc() const{return m_desc;}
			private:
				ShaderDesc m_desc;
			};

			class Texture : public virtual GAIA::RENDER::Resource
			{
			public:
				class TextureDesc : public GAIA::Base
				{
				public:
				};
			public:
				const TextureDesc& GetDesc() const{return m_desc;}
			private:
				TextureDesc m_desc;
			};

		public:

			/* Font. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::Font* CreateFont(
				GAIA::RENDER::Render2D::FontFamily& ff,
				const GAIA::RENDER::Render2D::Font::FontDesc& desc) = 0;
			virtual GAIA::GVOID DrawFont(
				GAIA::RENDER::Render2D::Font* pFont,
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* Pen and brush. */
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
			virtual GAIA::GVOID SetShader() = 0;
			virtual GAIA::GVOID GetShader() const = 0;
			virtual GAIA::GVOID SetShaderConstant() = 0;
			virtual GAIA::GVOID GetShaderConstant() const = 0;

		private:
		};
	};
};

#endif