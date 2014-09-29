#ifndef		__GAIA_RENDER_DX9_H__
#define		__GAIA_RENDER_DX9_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render3DDX9 : public virtual GAIA::RENDER::Render3D
		{
		public:
			typedef Render3DDX9 __MyType;

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
				const FontPainterDesc& GetDesc() const{return m_desc;}
			private:
				FontPainterDesc m_desc;
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
				const TargetDesc& GetDesc() const{return m_desc;}
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
				const ShaderDesc& GetDesc() const{return m_desc;}
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
				const TextureDesc& GetDesc() const{return m_desc;}
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
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const VertexDeclarationDesc& GetDesc() const{return m_desc;}
			private:
				VertexDeclarationDesc m_desc;
			};

			class IndexBuffer : public virtual GAIA::RENDER::Render3D::IndexBuffer
			{
			public:
				class IndexBufferDesc : public virtual GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const IndexBufferDesc& GetDesc() const{return m_desc;}
			private:
				IndexBufferDesc m_desc;
			};

			class VertexBuffer : public virtual GAIA::RENDER::Render3D::VertexBuffer
			{
			public:
				class VertexBufferDesc : public virtual GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				const VertexBufferDesc& GetDesc() const{return m_desc;}
			private:
				VertexBufferDesc m_desc;
			};

		public:
			GINL Render3DDX9(){this->init();}
			GINL ~Render3DDX9(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_DX9;}

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

		public:
			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp){}
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const{}

			/* State. */
			virtual GAIA::GVOID SetRender3DState(const RENDER3D_STATE& rs){}
			virtual GAIA::GVOID GetRender3DState(RENDER3D_STATE& rs) const{}
			virtual GAIA::GVOID SetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss){}
			virtual GAIA::GVOID GetSampler3DState(GAIA::N32 nSamplerIndex, SAMPLER3D_STATE& ss) const{}

			/* Index buffer. */
			virtual GAIA::RENDER::Render3D::IndexBuffer* CreateIndexBuffer(){return GNIL;}
			virtual GAIA::GVOID SetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer* pIB){}
			virtual GAIA::GVOID GetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer*& pIB) const{}

			/* Vertex buffer. */
			virtual GAIA::RENDER::Render3D::VertexBuffer* CreateVertexBuffer(){return GNIL;}
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer* pVB){}
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer*& pVB) const{}

			/* Declaration. */
			virtual GAIA::RENDER::Render3D::VertexDeclaration* CreateVertexDeclaration(){return GNIL;}
			virtual GAIA::GVOID SetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration* pVDecl){}
			virtual GAIA::GVOID GetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration*& pVDecl){}

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
