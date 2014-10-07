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

			class Context : public virtual GAIA::RENDER::Render2D::Context
			{
			public:
				class ContextDesc : public virtual GAIA::RENDER::Render2D::Context::ContextDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Context::ContextDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Context::ContextDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~Context(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render::Context::ContextDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const ContextDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_CONTEXT;}
			private:
				ContextDesc m_desc;
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
				GINL ~Pen(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Pen::PenDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const PenDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_PEN;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr){return GAIA::False;}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const{return GAIA::False;}
				virtual GAIA::BL SetWidth(const GAIA::REAL& rWidth){return GAIA::False;}
				virtual GAIA::BL GetWidth(GAIA::REAL& rWidth) const{return GAIA::False;}
			private:
				PenDesc m_desc;
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
				GINL ~Brush(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const BrushDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_BRUSH;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr){return GAIA::False;}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const{return GAIA::False;}
			private:
				BrushDesc m_desc;
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
				GINL ~FontFamily(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const FontFamilyDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_FONTFAMILY;}
			private:
				FontFamilyDesc m_desc;
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
				GINL ~FontPainter(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const FontPainterDesc& GetDesc() const{return m_desc;}
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
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~FontFormat(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const FontFormatDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_FONTFORMAT;}
				virtual GAIA::BL SetAlignDirectionH(GAIA::N8 nDirection){return GAIA::False;}
				virtual GAIA::BL GetAlignDirectionH(GAIA::N8& nDirection){return GAIA::False;}
				virtual GAIA::BL SetAlignDirectionV(GAIA::N8 nDirection){return GAIA::False;}
				virtual GAIA::BL GetAlignDirectionV(GAIA::N8& nDirection){return GAIA::False;}
				virtual GAIA::BL EnableWrap(GAIA::BL bEnable){return GAIA::False;}
				virtual GAIA::BL IsEnableWrap(GAIA::BL& bEnable){return GAIA::False;}
			private:
				FontFormatDesc m_desc;
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
				class FetchData : public virtual GAIA::RENDER::Render2D::Target::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TARGETFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetSequenceSize() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetSequenceHead(const GAIA::SIZE& sOffset) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init(){m_desc.reset();}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL ~Target(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const TargetDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TARGET;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc){return GNIL;}
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
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Texture::TextureDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Texture::TextureDesc::check()) return GAIA::False; return GAIA::True;}
				};
				class FetchData : public virtual GAIA::RENDER::Render2D::Texture::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TEXTUREFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetSequenceSize() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetSequenceHead(const GAIA::SIZE& sOffset) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init(){m_desc.reset();}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL ~Texture(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const TextureDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_2D_DDRAW_TEXTURE;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc){return GNIL;}
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

			virtual GAIA::RENDER::Render::Context* CreateContext(const GAIA::RENDER::Render::Context::ContextDesc& desc){return GNIL;}

			virtual GAIA::GVOID Flush()
			{
			}

		public:
			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr){}

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs){return GNIL;}
			virtual GAIA::GVOID SetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs) const{return GNIL;}
			virtual GAIA::GVOID SetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const{return GNIL;}

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Pen::PenDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen* pPen){}
			virtual GAIA::GVOID GetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen*& pPen){}

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Brush::BrushDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush* pBrush){}
			virtual GAIA::GVOID GetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush*& pBrush){}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily* pFontFamily){}
			virtual GAIA::GVOID GetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily*& pFontFamily){}
			virtual GAIA::GVOID SetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter* pFontPainter){}
			virtual GAIA::GVOID GetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter*& pFontPainter){}
			virtual GAIA::GVOID SetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat* pFontFormat){}
			virtual GAIA::GVOID GetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat*& pFontFormat){}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture){}
			virtual GAIA::GVOID GetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const{}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget){}
			virtual GAIA::GVOID GetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const{}

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader* pShader){}
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader*& pShader) const{}
			virtual GAIA::GVOID SetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, const GAIA::REAL* p, const GAIA::SIZE& sSize){}
			virtual GAIA::GVOID GetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, GAIA::REAL* p, const GAIA::SIZE& sSize, GAIA::SIZE& sResultSize) const{}

			/* Draw. */
			virtual GAIA::GVOID DrawLine(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e){}
			virtual GAIA::GVOID DrawRect(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr){}
			virtual GAIA::GVOID DrawTriangle(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3){}
			virtual GAIA::GVOID DrawFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr){}
			virtual GAIA::GVOID DrawTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM){}

		private:
			GINL GAIA::GVOID init()
			{
				m_bCreated = GAIA::False;
				m_desc.reset();
			}

		private:
			GAIA::BL m_bCreated;
			RenderDesc m_desc;
		};
	};
};

#endif
