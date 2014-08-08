#ifndef		__GAIA_RENDER_RENDER3D_H__
#define		__GAIA_RENDER_RENDER3D_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render3D : public virtual GAIA::RENDER::Render2D
		{
		public:
			class Render3DDesc : public GAIA::RENDER::Render::RenderDesc
			{
			public:
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

			/* Texture. */
			virtual GAIA::RENDER::Texture* CreateTexture() = 0;
			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Texture* pTexture) = 0;
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Texture*& pTexture) const = 0;

			/* Shader. */
			virtual GAIA::RENDER::Shader* CreateShader() = 0;
			virtual GAIA::GVOID SetShader() = 0;
			virtual GAIA::GVOID GetShader() const = 0;
			virtual GAIA::GVOID SetShaderConstant() = 0;
			virtual GAIA::GVOID GetShaderConstant() const = 0;

			/* Index buffer. */
			virtual GAIA::RENDER::IndexBuffer* CreateIndexBuffer() = 0;
			virtual GAIA::GVOID SetIndexBuffer(const GAIA::RENDER::IndexBuffer* pIB) = 0;
			virtual GAIA::GVOID GetIndexBuffer(const GAIA::RENDER::IndexBuffer*& pIB) const = 0;

			/* Vertex buffer. */
			virtual GAIA::RENDER::VertexBuffer* CreateVertexBuffer() = 0;
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::VertexBuffer* pVB) = 0;
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::VertexBuffer*& pVB) const = 0;

			/* Target. */
			virtual GAIA::RENDER::Target* CreateTarget() = 0;
			virtual GAIA::GVOID SetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Target* pTarget) = 0;
			virtual GAIA::GVOID GetTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::Target*& pTarget) const = 0;

			/* Declaration. */
			virtual GAIA::RENDER::VertexDeclaration* CreateVertexDeclaration() = 0;
			virtual GAIA::GVOID SetVertexDeclaration(GAIA::RENDER::VertexDeclaration* pVDecl) = 0;
			virtual GAIA::GVOID GetVertexDeclaration(GAIA::RENDER::VertexDeclaration*& pVDecl) = 0;

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