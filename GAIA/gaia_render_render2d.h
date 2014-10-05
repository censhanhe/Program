#ifndef		__GAIA_RENDER_RENDER2D_H__
#define		__GAIA_RENDER_RENDER2D_H__

namespace GAIA
{
	namespace RENDER
	{
		static const GAIA::CH* RENDER2D_QUALITYSTATE_DEFAULT[] = 
		{
			"invalid",	// QUALITY2D_STATE_INVALID
			"none",		// QUALITY2D_STATE_ANTIALIAS
			"none",		// QUALITY2D_STATE_FONTANTIALIAS
		};
		static const GAIA::CH* RENDER2D_RENDERSTATE_DEFAULT[] = 
		{
			"invalid",	// RENDER2D_STATE_INVALID
		};
		static const GAIA::CH* RENDER2D_SAMPLERSTATE_DEFAULT[] = 
		{
			"invalid",	// SAMPLER2D_STATE_INVALID
		};

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
			class Pen : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class PenDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Pen::PenDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const PenDesc& GetDesc() const = 0;
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const = 0;
				virtual GAIA::BL SetWidth(const GAIA::REAL& rWidth) = 0;
				virtual GAIA::BL GetWidth(GAIA::REAL& rWidth) const = 0;
			};

			class Brush : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class BrushDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const BrushDesc& GetDesc() const = 0;
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const = 0;
			};

			class FontFamily : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class FontFamilyDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset()
					{
						strFontName.clear();
					}
					virtual GAIA::BL check() const
					{
						if(strFontName.empty())
							return GAIA::False;
						return GAIA::True;
					}
					GAIA::CTN::TString strFontName;
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const FontFamilyDesc& GetDesc() const = 0;
			};

			class FontPainter : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class FontPainterDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset()
					{
						pFontFamily = GNIL;
						rSize = 16.0F;
						bBold = GAIA::False;
						bItalic = GAIA::False;
						bUnderline = GAIA::False;
					}
					virtual GAIA::BL check() const
					{
						if(pFontFamily == GNIL)
							return GAIA::False;
						if(rSize <= 0.0F)
							return GAIA::False;
						return GAIA::True;
					}
					GAIA::RENDER::Render2D::FontFamily* pFontFamily;
					GAIA::REAL rSize;
					GAIA::U8 bBold : 1;
					GAIA::U8 bItalic : 1;
					GAIA::U8 bUnderline : 1;
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const FontPainterDesc& GetDesc() const = 0;
			};

			class FontFormat : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class FontFormatDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const FontFormatDesc& GetDesc() const = 0;
				virtual GAIA::BL SetAlignDirectionH(GAIA::N8 nDirection) = 0;
				virtual GAIA::BL GetAlignDirectionH(GAIA::N8& nDirection) = 0;
				virtual GAIA::BL SetAlignDirectionV(GAIA::N8 nDirection) = 0;
				virtual GAIA::BL GetAlignDirectionV(GAIA::N8& nDirection) = 0;
				virtual GAIA::BL EnableWrap(GAIA::BL bEnable) = 0;
				virtual GAIA::BL IsEnableWrap(GAIA::BL& bEnable) = 0;
			};

			class Target : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class TargetDesc : public virtual GAIA::RENDER::Render::ImageFormatDesc
				{
				public:
					virtual GAIA::GVOID reset()
					{
						GAIA::RENDER::Render::ImageFormatDesc::reset();
					}
					virtual GAIA::BL check() const
					{
						if(!GAIA::RENDER::Render::ImageFormatDesc::check())
							return GAIA::False;
						return GAIA::True;
					}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const TargetDesc& GetDesc() const = 0;
			};

			class Shader : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class ShaderDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const ShaderDesc& GetDesc() const = 0;
			};

			class Texture : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class TextureDesc : public virtual GAIA::RENDER::Render::ImageFormatDesc
				{
				public:
					virtual GAIA::GVOID reset()
					{
						GAIA::RENDER::Render::ImageFormatDesc::reset();
						pszFileName = GNIL;
						uWidth = 0;
						uHeight = 0;
					}
					virtual GAIA::BL check() const
					{
						if(!GAIA::RENDER::Render::ImageFormatDesc::check())
							return GAIA::False;
						if(pszFileName == GNIL)
						{
							if(uWidth == 0 && uHeight == 0)
								return GAIA::False;
						}
						else
						{
							if(uWidth != 0 || uHeight != 0)
								return GAIA::False;
						}
						return GAIA::True;
					}
					GAIA::TCH* pszFileName;
					GAIA::U32 uWidth;
					GAIA::U32 uHeight;
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const TextureDesc& GetDesc() const = 0;
			};

		public:
			GAIA_ENUM_BEGIN(QUALITY2D_STATE)
				QUALITY2D_STATE_ANTIALIAS,		// Support "none", "low", "mid", "high". Default is "none".
				QUALITY2D_STATE_FONTANTIALIAS,	// Support "none", "low", "mid", "high". Default is "none".
			GAIA_ENUM_END(QUALITY2D_STATE)

			GAIA_ENUM_BEGIN(RENDER2D_STATE)
				RENDER2D_STATE_ALPHABLEND,		// Support "on", "off". Default is "off".
				RENDER2D_STATE_ALPHATEST,		// Support "on", "off". Default is "off".
			GAIA_ENUM_END(RENDER2D_STATE)

			GAIA_ENUM_BEGIN(SAMPLER2D_STATE)
				SAMPLER2D_STATE_ADDRESSU,
				SAMPLER2D_STATE_ADDRESSV,
				SAMPLER2D_STATE_MINFILTER,
				SAMPLER2D_STATE_MAXFILTER,
			GAIA_ENUM_END(SAMPLER2D_STATE)

		public:
			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(const QUALITY2D_STATE& qs, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetQuality2DState(const QUALITY2D_STATE& qs) = 0; // This function will never return GNIL, it will return "" instead.
			virtual GAIA::GVOID SetRender2DState(const RENDER2D_STATE& rs, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetRender2DState(const RENDER2D_STATE& rs) const = 0; // This function will never return GNIL, it will return "" instead.
			virtual GAIA::GVOID SetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetSampler2DState(GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const = 0; // This function will never return GNIL, it will return "" instead.

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(const GAIA::RENDER::Render2D::Pen::PenDesc& desc) = 0;
			virtual GAIA::GVOID SetPen(GAIA::RENDER::Render2D::Pen* pPen) = 0;
			virtual GAIA::GVOID GetPen(GAIA::RENDER::Render2D::Pen*& pPen) = 0;

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc) = 0;
			virtual GAIA::GVOID SetBrush(GAIA::RENDER::Render2D::Brush* pBrush) = 0;
			virtual GAIA::GVOID GetBrush(GAIA::RENDER::Render2D::Brush*& pBrush) = 0;

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc) = 0;
			virtual GAIA::GVOID SetFontFamily(GAIA::RENDER::Render2D::FontFamily* pFontFamily) = 0;
			virtual GAIA::GVOID GetFontFamily(GAIA::RENDER::Render2D::FontFamily*& pFontFamily) = 0;
			virtual GAIA::GVOID SetFontPainter(GAIA::RENDER::Render2D::FontPainter* pFontPainter) = 0;
			virtual GAIA::GVOID GetFontPainter(GAIA::RENDER::Render2D::FontPainter*& pFontPainter) = 0;
			virtual GAIA::GVOID SetFontFormat(GAIA::RENDER::Render2D::FontFormat* pFontFormat) = 0;
			virtual GAIA::GVOID GetFontFormat(GAIA::RENDER::Render2D::FontFormat*& pFontFormat) = 0;

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc) = 0;
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture) = 0;
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const = 0;

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc) = 0;
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget) = 0;
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const = 0;

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc) = 0;
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render2D::Shader* pShader) = 0;
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render2D::Shader*& pShader) const = 0;
			virtual GAIA::GVOID SetShaderConstant() = 0;
			virtual GAIA::GVOID GetShaderConstant() const = 0;

			/* Draw. */
			virtual GAIA::GVOID DrawLine(
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e,
				GAIA::RENDER::Render2D::Pen* pPen) = 0;
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::Brush* pBrush) = 0;
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3,
				GAIA::RENDER::Render2D::Brush* pBrush) = 0;
			virtual GAIA::GVOID DrawFontPainter(
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				GAIA::RENDER::Render2D::Brush* pBrush,
				GAIA::RENDER::Render2D::FontFormat* pFontFormat) = 0;
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM) = 0;
		private:
		};
	};
};

#endif