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

		public:
			class VIEWPORT
			{
			public:
			};

			GAIA_ENUM_BEGIN(DRAW_TRIANGLE_TYPE)
				DRAW_TRIANGLE_TYPE_TRIANGLELIST,
				DRAW_TRIANGLE_TYPE_TRIANGLESTRIP,
				DRAW_TRIANGLE_TYPE_TRIANGLEFAN,
			GAIA_ENUM_END(DRAW_TRIANGLE_TYPE)

			GAIA_ENUM_BEGIN(RENDER_STATE)
				RENDER_STATE_ENABLEZTEST,
				RENDER_STATE_ENABLEZWRITE,
				RENDER_STATE_ALPHABLEND,
				RENDER_STATE_ALPHATEST,
				RENDER_STATE_CULLMODE,
				RENDER_STATE_FILLMODE,
			GAIA_ENUM_END(RENDER_STATE)

			GAIA_ENUM_BEGIN(SAMPLER_STATE)
				SAMPLER_STATE_ADDRESSU,
				SAMPLER_STATE_ADDRESSV,
				SAMPLER_STATE_ADDRESSW,
				SAMPLER_STATE_MINFILTER,
				SAMPLER_STATE_MAXFILTER,
				SAMPLER_STATE_MIPFILTER,
			GAIA_ENUM_END(SAMPLER_STATE)

			GAIA_ENUM_BEGIN(ALPHA_BLEND_TYPE)
				ALPHA_BLEND_TYPE_SRCALPHA,
				ALPHA_BLEND_TYPE_DSTALPHA,
				ALPHA_BLEND_TYPE_INVSRCALPHA,
				ALPHA_BLEND_TYPE_INVDSTALPHA,
			GAIA_ENUM_END(ALPHA_BLEND_TYPE)

			GAIA_ENUM_BEGIN(INDEX_FORMAT_TYPE)
				INDEX_FORMAT_TYPE_16,
				INDEX_FORMAT_TYPE_32,
			GAIA_ENUM_END(INDEX_FORMAT_TYPE)

			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp) = 0;
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const = 0;

			/* State. */
			virtual GAIA::GVOID SetRenderState(const RENDER_STATE& rs) = 0;
			virtual GAIA::GVOID GetRenderState(RENDER_STATE& rs) const = 0;
			virtual GAIA::GVOID SetSampleState(GAIA::N32 nSamplerIndex, const SAMPLER_STATE& ss) = 0;
			virtual GAIA::GVOID GetSampleState(GAIA::N32 nSamplerIndex, SAMPLER_STATE& ss) const = 0;

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