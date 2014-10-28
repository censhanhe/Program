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

			class Context : public virtual GAIA::RENDER::Render::Context, public virtual GAIA::FWORK::InstanceId
			{
			public:
				class ContextDesc : public virtual GAIA::RENDER::Render::Context::ContextDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render::Context::ContextDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render::Context::ContextDesc::check()) return GAIA::False; return GAIA::True;}
				};
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
						rSize = 16;
						bBold = GAIA::False;
						bItalic = GAIA::False;
						bUnderline = GAIA::False;
					}
					virtual GAIA::BL check() const
					{
						if(pFontFamily == GNIL)
							return GAIA::False;
						if(rSize <= 0)
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
				class FetchData : public virtual GAIA::FAVO::FetchData2, public virtual GAIA::RENDER::RenderResource
				{
				public:
					class FetchDataDesc : public virtual GAIA::FAVO::FetchData2::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset()
						{
							GAIA::FAVO::FetchData2::FetchDataDesc::reset();
						}
						virtual GAIA::BL check() const
						{
							if(!GAIA::FAVO::FetchData2::FetchDataDesc::check())
								return GAIA::False;
							return GAIA::True;
						}
					};
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const TargetDesc& GetDesc() const = 0;
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc) = 0;
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
				class FetchData : public virtual GAIA::FAVO::FetchData2, public virtual GAIA::RENDER::RenderResource
				{
				public:
					class FetchDataDesc : public virtual GAIA::FAVO::FetchData2::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset()
						{
							GAIA::FAVO::FetchData2::FetchDataDesc::reset();
							pTexture = GNIL;
						}
						virtual GAIA::BL check() const
						{
							if(!GAIA::FAVO::FetchData2::FetchDataDesc::check())
								return GAIA::False;
							if(pTexture == GNIL)
								return GAIA::False;
							return GAIA::True;
						}
						GAIA::RENDER::Render2D::Texture* pTexture;
					};
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const TextureDesc& GetDesc() const = 0;
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc) = 0;
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
			/* Scissor. */
			virtual GAIA::GVOID SetScissor(const GAIA::MATH::AABR<GAIA::REAL>& aabr) = 0;
			virtual GAIA::GVOID GetScissor(GAIA::MATH::AABR<GAIA::REAL>& aabr) const = 0;

			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs) const = 0; // This function will never return GNIL, it will return "" instead.
			virtual GAIA::GVOID SetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs) const = 0; // This function will never return GNIL, it will return "" instead.
			virtual GAIA::GVOID SetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState) = 0; // if pszState is GNIL or "", the state will be reset to default state.
			virtual const GAIA::CH* GetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const = 0; // This function will never return GNIL, it will return "" instead.

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Pen::PenDesc& desc) = 0;
			virtual GAIA::GVOID SetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen* pPen) = 0;
			virtual GAIA::GVOID GetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen*& pPen) const = 0;

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Brush::BrushDesc& desc) = 0;
			virtual GAIA::GVOID SetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush* pBrush) = 0;
			virtual GAIA::GVOID GetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush*& pBrush) const = 0;

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc) = 0;
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc) = 0;
			virtual GAIA::GVOID SetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily* pFontFamily) = 0;
			virtual GAIA::GVOID GetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily*& pFontFamily) const = 0;
			virtual GAIA::GVOID SetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter* pFontPainter) = 0;
			virtual GAIA::GVOID GetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter*& pFontPainter) const = 0;
			virtual GAIA::GVOID SetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat* pFontFormat) = 0;
			virtual GAIA::GVOID GetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat*& pFontFormat) const = 0;

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc) = 0;
			virtual GAIA::GVOID SetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture) = 0;
			virtual GAIA::GVOID GetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const = 0;

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc) = 0;
			virtual GAIA::GVOID SetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget) = 0;
			virtual GAIA::GVOID GetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const = 0;

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc) = 0;
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader* pShader) = 0;
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader*& pShader) const = 0;
			virtual GAIA::GVOID SetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, const GAIA::REAL* p, const GAIA::SIZE& sSize) = 0;
			virtual GAIA::GVOID GetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, GAIA::REAL* p, const GAIA::SIZE& sSize, GAIA::SIZE& sResultSize) const = 0;

			/* Draw. */
			virtual GAIA::GVOID DrawLine(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e) = 0;
			virtual GAIA::GVOID DrawRect(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr) = 0;
			virtual GAIA::GVOID DrawTriangle(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3) = 0;
			virtual GAIA::GVOID DrawFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr) = 0;
			virtual GAIA::GVOID DrawTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM) = 0;
		private:
		};
	};
};

#endif