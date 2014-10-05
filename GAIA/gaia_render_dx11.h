#ifndef		__GAIA_RENDER_DX11_H__
#define		__GAIA_RENDER_DX11_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render3DDX11 : public virtual GAIA::RENDER::Render3D
		{
		public:
			typedef Render3DDX11 __MyType;

		public:
			class RenderDesc : public virtual GAIA::RENDER::Render3D::RenderDesc
			{
			public:
				virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::RenderDesc::reset();}
				virtual GAIA::BL check() const
				{
					if(!GAIA::RENDER::Render3D::RenderDesc::check())
						return GAIA::False;
					return GAIA::True;
				}
			};

			class Context : public virtual GAIA::RENDER::Render3D::Context
			{
			public:
				class ContextDesc : public virtual GAIA::RENDER::Render3D::Context::ContextDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::Context::ContextDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::Context::ContextDesc::check()) return GAIA::False; return GAIA::True;}
				};
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_PEN;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_BRUSH;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_FONTFAMILY;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_FONTPAINTER;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_FONTFORMAT;}
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
			public:
				GINL ~Target(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const TargetDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_TARGET;}
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
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_SHADER;}
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
				GINL ~Texture(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const TextureDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_TEXTURE;}
			private:
				TextureDesc m_desc;
			};

		public:
			class VertexDeclaration : public virtual GAIA::RENDER::Render3D::VertexDeclaration
			{
			public:
				class VertexDeclarationDesc : public virtual GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~VertexDeclaration(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const VertexDeclarationDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_VERTEXDECLARATION;}
			private:
				VertexDeclarationDesc m_desc;
			};

			class IndexBuffer : public virtual GAIA::RENDER::Render3D::IndexBuffer
			{
			public:
				class IndexBufferDesc : public virtual GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~IndexBuffer(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const IndexBufferDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_INDEXBUFFER;}
			private:
				IndexBufferDesc m_desc;
			};

			class VertexBuffer : public virtual GAIA::RENDER::Render3D::VertexBuffer
			{
			public:
				class VertexBufferDesc : public virtual GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL ~VertexBuffer(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc& desc){return GAIA::True;}
				virtual GAIA::GVOID Destroy(){m_desc.reset();}
				virtual const VertexBufferDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11_VERTEXBUFFER;}
			private:
				VertexBufferDesc m_desc;
			};

		public:
			GINL Render3DDX11(){this->init();}
			GINL ~Render3DDX11(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX11;}

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

			virtual GAIA::RENDER::Render::Context* CreateContent(const GAIA::RENDER::Render::Context::ContextDesc& desc){return GNIL;}

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
			virtual GAIA::GVOID SetPen(GAIA::RENDER::Render2D::Pen* pPen){}
			virtual GAIA::GVOID GetPen(GAIA::RENDER::Render2D::Pen*& pPen){}

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetBrush(GAIA::RENDER::Render2D::Brush* pBrush){}
			virtual GAIA::GVOID GetBrush(GAIA::RENDER::Render2D::Brush*& pBrush){}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc){return GNIL;}
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetFontFamily(GAIA::RENDER::Render2D::FontFamily* pFontFamily){}
			virtual GAIA::GVOID GetFontFamily(GAIA::RENDER::Render2D::FontFamily*& pFontFamily){}
			virtual GAIA::GVOID SetFontPainter(GAIA::RENDER::Render2D::FontPainter* pFontPainter){}
			virtual GAIA::GVOID GetFontPainter(GAIA::RENDER::Render2D::FontPainter*& pFontPainter){}
			virtual GAIA::GVOID SetFontFormat(GAIA::RENDER::Render2D::FontFormat* pFontFormat){}
			virtual GAIA::GVOID GetFontFormat(GAIA::RENDER::Render2D::FontFormat*& pFontFormat){}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture){}
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const{}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget){}
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const{}

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc){return GNIL;}
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
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3,
				GAIA::RENDER::Render2D::Brush* pBrush){}
			virtual GAIA::GVOID DrawFontPainter(
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				GAIA::RENDER::Render2D::FontPainter* pFontPainter,
				GAIA::RENDER::Render2D::Brush* pBrush,
				GAIA::RENDER::Render2D::FontFormat* pFontFormat){}
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM){}

		public:
			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp){}
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const{}

			/* State. */
			virtual GAIA::GVOID SetQuality3DState(const QUALITY3D_STATE& qs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetQuality3DState(const QUALITY3D_STATE& qs){return GNIL;}
			virtual GAIA::GVOID SetRender3DState(const RENDER3D_STATE& rs, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetRender3DState(const RENDER3D_STATE& rs) const{return GNIL;}
			virtual GAIA::GVOID SetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss, const GAIA::CH* pszState){}
			virtual const GAIA::CH* GetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss) const{return GNIL;}

			/* Declaration. */
			virtual GAIA::RENDER::Render3D::VertexDeclaration* CreateVertexDeclaration(
				const GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration* pVDecl){}
			virtual GAIA::GVOID GetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration*& pVDecl){}

			/* Index buffer. */
			virtual GAIA::RENDER::Render3D::IndexBuffer* CreateIndexBuffer(
				const GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer* pIB){}
			virtual GAIA::GVOID GetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer*& pIB) const{}

			/* Vertex buffer. */
			virtual GAIA::RENDER::Render3D::VertexBuffer* CreateVertexBuffer(
				const GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc& desc){return GNIL;}
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer* pVB){}
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer*& pVB) const{}

			/* Draw. */
			virtual GAIA::GVOID SetTriangleType(DRAW_TRIANGLE_TYPE dtt){}
			virtual GAIA::GVOID GetTriangleType(DRAW_TRIANGLE_TYPE& dtt) const{}
			virtual GAIA::GVOID DrawTriangle(){}
			virtual GAIA::GVOID DrawIndexedTriangle(){}

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
