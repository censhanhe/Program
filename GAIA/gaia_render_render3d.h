#ifndef		__GAIA_RENDER_RENDER3D_H__
#define		__GAIA_RENDER_RENDER3D_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render3D : public virtual GAIA::RENDER::Render2D
		{
		public:
			typedef GAIA::RENDER::Render3D __MyType;

		public:
			class Render3DDesc : public GAIA::RENDER::Render::RenderDesc
			{
			public:
			};

			class VertexDeclaration : public virtual GAIA::RENDER::Resource
			{
			public:
				class VertexDeclarationDesc : public GAIA::Base
				{
				public:
				};
			public:
				const VertexDeclarationDesc& GetDesc() const{return m_desc;}
			private:
				VertexDeclarationDesc m_desc;
			};

			class IndexBuffer : public virtual GAIA::RENDER::Resource
			{
			public:
				class IndexBufferDesc : public GAIA::Base
				{
				public:
				};
			public:
				const IndexBufferDesc& GetDesc() const{return m_desc;}
			private:
				IndexBufferDesc m_desc;
			};

			class VertexBuffer : public virtual GAIA::RENDER::Resource
			{
			public:
				class VertexBufferDesc : public GAIA::Base
				{
				public:
				};
			public:
				const VertexBufferDesc& GetDesc() const{return m_desc;}
			private:
				VertexBufferDesc m_desc;
			};

			class VIEWPORT
			{
			public:
			};
		public:
			GAIA_ENUM_BEGIN(DRAW_TRIANGLE_TYPE)
				DRAW_TRIANGLE_TYPE_TRIANGLELIST,
				DRAW_TRIANGLE_TYPE_TRIANGLESTRIP,
				DRAW_TRIANGLE_TYPE_TRIANGLEFAN,
			GAIA_ENUM_END(DRAW_TRIANGLE_TYPE)

			GAIA_ENUM_BEGIN(RENDER3D_STATE)
				RENDER3D_STATE_ENABLEZTEST,
				RENDER3D_STATE_ENABLEZWRITE,
			GAIA_ENUM_END(RENDER3D_STATE)

			GAIA_ENUM_BEGIN(SAMPLER3D_STATE)
				SAMPLER3D_STATE_ADDRESSW,
				SAMPLER3D_STATE_MIPFILTER,
			GAIA_ENUM_END(SAMPLER3D_STATE)

			GAIA_ENUM_BEGIN(INDEX_FORMAT_TYPE)
				INDEX_FORMAT_TYPE_16,
				INDEX_FORMAT_TYPE_32,
			GAIA_ENUM_END(INDEX_FORMAT_TYPE)

			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp) = 0;
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const = 0;

			/* State. */
			virtual GAIA::GVOID SetRender3DState(const RENDER3D_STATE& rs) = 0;
			virtual GAIA::GVOID GetRender3DState(RENDER3D_STATE& rs) const = 0;
			virtual GAIA::GVOID SetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss) = 0;
			virtual GAIA::GVOID GetSampler3DState(GAIA::N32 nSamplerIndex, SAMPLER3D_STATE& ss) const = 0;

			/* Index buffer. */
			virtual __MyType::IndexBuffer* CreateIndexBuffer() = 0;
			virtual GAIA::GVOID SetIndexBuffer(const __MyType::IndexBuffer* pIB) = 0;
			virtual GAIA::GVOID GetIndexBuffer(const __MyType::IndexBuffer*& pIB) const = 0;

			/* Vertex buffer. */
			virtual __MyType::VertexBuffer* CreateVertexBuffer() = 0;
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const __MyType::VertexBuffer* pVB) = 0;
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const __MyType::VertexBuffer*& pVB) const = 0;

			/* Declaration. */
			virtual __MyType::VertexDeclaration* CreateVertexDeclaration() = 0;
			virtual GAIA::GVOID SetVertexDeclaration(__MyType::VertexDeclaration* pVDecl) = 0;
			virtual GAIA::GVOID GetVertexDeclaration(__MyType::VertexDeclaration*& pVDecl) = 0;

			/* Draw. */
			virtual GAIA::GVOID SetTriangleType(DRAW_TRIANGLE_TYPE dtt) = 0;
			virtual GAIA::GVOID GetTriangleType(DRAW_TRIANGLE_TYPE& dtt) const = 0;
			virtual GAIA::GVOID DrawTriangle() = 0;
			virtual GAIA::GVOID DrawIndexedTriangle() = 0;
		private:
		};
	};
};

#endif