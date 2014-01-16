#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render : public GAIA::FRAMEWORK::Instance
		{
		public:
			class RENDER_DESC
			{
			public:
			};

			class VIEWPORT
			{
			public:
			};

			ENUM_BEGIN(DRAW_TRIANGLE_TYPE)
				DRAW_TRIANGLE_TYPE_TRIANGLELIST,
				DRAW_TRIANGLE_TYPE_TRIANGLESTRIP,
				DRAW_TRIANGLE_TYPE_TRIANGLEFAN,
			ENUM_END(DRAW_TRIANGLE_TYPE)

			ENUM_BEGIN(RENDER_STATE)
				RENDER_STATE_ENABLEZTEST,
				RENDER_STATE_ENABLEZWRITE,
				RENDER_STATE_ALPHABLEND,
				RENDER_STATE_ALPHATEST,
				RENDER_STATE_CULLMODE,
				RENDER_STATE_FILLMODE,
			ENUM_END(RENDER_STATE)

			ENUM_BEGIN(SAMPLER_STATE)
				SAMPLER_STATE_ADDRESSU,
				SAMPLER_STATE_ADDRESSV,
				SAMPLER_STATE_ADDRESSW,
				SAMPLER_STATE_MINFILTER,
				SAMPLER_STATE_MAXFILTER,
				SAMPLER_STATE_MIPFILTER,
			ENUM_END(SAMPLER_STATE)

			ENUM_BEGIN(ALPHA_BLEND_TYPE)
				ALPHA_BLEND_TYPE_SRCALPHA,
				ALPHA_BLEND_TYPE_DSTALPHA,
				ALPHA_BLEND_TYPE_INVSRCALPHA,
				ALPHA_BLEND_TYPE_INVDSTALPHA,
			ENUM_END(ALPHA_BLEND_TYPE)

			ENUM_BEGIN(INDEX_FORMAT_TYPE)
				INDEX_FORMAT_TYPE_16,
				INDEX_FORMAT_TYPE_32,
			ENUM_END(INDEX_FORMAT_TYPE)

		public:
			GINL Render();
			GINL ~Render() = 0;

			virtual GAIA::BL Initialize(const RENDER_DESC& desc) = 0;
			virtual GAIA::BL Release() = 0;
			virtual GAIA::BL IsInitialized() const = 0;
			virtual const RENDER_DESC& GetDesc() const = 0;

			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp) = 0;
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const = 0;

			virtual GAIA::GVOID SetRenderState(const RENDER_STATE& rs) = 0;
			virtual GAIA::GVOID GetRenderState(RENDER_STATE& rs) const = 0;
			virtual GAIA::GVOID SetSampleState(GAIA::N32 nSamplerIndex, const SAMPLER_STATE& ss) = 0;
			virtual GAIA::GVOID GetSampleState(GAIA::N32 nSamplerIndex, SAMPLER_STATE& ss) const = 0;

			virtual GAIA::GVOID SetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Texture* pTexture) = 0;
			virtual GAIA::GVOID GetTexture(GAIA::N32 nTextureIndex, GAIA::RENDER::Texture*& pTexture) const = 0;

			virtual GAIA::GVOID SetShader() = 0;
			virtual GAIA::GVOID GetShader() const = 0;
			virtual GAIA::GVOID SetShaderConstant() = 0;
			virtual GAIA::GVOID GetShaderConstant() const = 0;

			virtual GAIA::GVOID SetIndexBuffer(const GAIA::RENDER::IndexBuffer* pIB) = 0;
			virtual GAIA::GVOID GetIndexBuffer(const GAIA::RENDER::IndexBuffer*& pIB) const = 0;
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::VertexBuffer* pVB) = 0;
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::VertexBuffer*& pVB) const = 0;
			
			virtual GAIA::GVOID SetRenderTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::RenderTarget* pTarget) = 0;
			virtual GAIA::GVOID GetRenderTarget(GAIA::N32 nTargetIndex, GAIA::RENDER::RenderTarget*& pTarget) const = 0;
			
			virtual GAIA::GVOID SetTriangleType(DRAW_TRIANGLE_TYPE dtt) = 0;
			virtual GAIA::GVOID GetTriangleType(DRAW_TRIANGLE_TYPE& dtt) const = 0;
			
			virtual GAIA::GVOID DrawTriangle() = 0;
			virtual GAIA::GVOID DrawIndexedTriangle() = 0;

			virtual GAIA::GVOID Flush() = 0;
		};
	};
};

#endif