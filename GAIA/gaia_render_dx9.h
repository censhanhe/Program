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
			};

		public:
			class FontPainterFamily : public virtual GAIA::RENDER::Render2D::FontPainterFamily
			{
			public:
				class FontPainterFamilyDesc : public GAIA::RENDER::Render2D::FontPainterFamily::FontPainterFamilyDesc
				{
				public:
				};
			public:
				const FontPainterFamilyDesc& GetDesc() const{return m_desc;}
			private:
				FontPainterFamilyDesc m_desc;
			};

			class FontPainter : public virtual GAIA::RENDER::Render2D::FontPainter
			{
			public:
				class FontPainterDesc : public GAIA::RENDER::Render2D::FontPainter::FontPainterDesc
				{
				public:
				};
			public:
				const FontPainterDesc& GetDesc() const{return m_desc;}
			private:
				FontPainterDesc m_desc;
			};

			class Target : public virtual GAIA::RENDER::Render2D::Target
			{
			public:
				class TargetDesc : public GAIA::RENDER::Render2D::Target::TargetDesc
				{
				public:
				};
			public:
				const TargetDesc& GetDesc() const{return m_desc;}
			private:
				TargetDesc m_desc;
			};

			class Shader : public virtual GAIA::RENDER::Render2D::Shader
			{
			public:
				class ShaderDesc : public GAIA::RENDER::Render2D::Shader::ShaderDesc
				{
				public:
				};
			public:
				const ShaderDesc& GetDesc() const{return m_desc;}
			private:
				ShaderDesc m_desc;
			};

			class Texture : public virtual GAIA::RENDER::Render2D::Texture
			{
			public:
				class TextureDesc : public GAIA::RENDER::Render2D::Texture::TextureDesc
				{
				public:
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
				class VertexDeclarationDesc : public GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc
				{
				public:
				};
			public:
				const VertexDeclarationDesc& GetDesc() const{return m_desc;}
			private:
				VertexDeclarationDesc m_desc;
			};

			class IndexBuffer : public virtual GAIA::RENDER::Render3D::IndexBuffer
			{
			public:
				class IndexBufferDesc : public GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc
				{
				public:
				};
			public:
				const IndexBufferDesc& GetDesc() const{return m_desc;}
			private:
				IndexBufferDesc m_desc;
			};

			class VertexBuffer : public virtual GAIA::RENDER::Render3D::VertexBuffer
			{
			public:
				class VertexBufferDesc : public GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc
				{
				public:
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
				m_bInitialized = GAIA::False;
			}

		private:
			GAIA::BL m_bInitialized;
			RenderDesc m_desc;
		};
	};
};

#endif
