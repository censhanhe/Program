#ifndef		__GAIA_RENDER_RENDER3D_H__
#define		__GAIA_RENDER_RENDER3D_H__

namespace GAIA
{
	namespace RENDER
	{
		static const GAIA::CH* RENDER3D_QUALITYSTATE_DEFAULT[] = 
		{
			"invalid",	// QUALITY3D_STATE_INVALID
		};
		static const GAIA::CH* RENDER3D_RENDERSTATE_DEFAULT[] = 
		{
			"invalid",	// RENDER3D_STATE_INVALID
		};
		static const GAIA::CH* RENDER3D_SAMPLERSTATE_DEFAULT[] = 
		{
			"invalid",	// SAMPLER3D_STATE_INVALID
		};

		class Render3D : public virtual GAIA::RENDER::Render2D
		{
		public:
			typedef GAIA::RENDER::Render3D __MyType;

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

		public:
			class VertexDeclaration : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class VertexDeclarationDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class IndexBuffer : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class IndexBufferDesc : public virtual GAIA::FWORK::InstanceDesc
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

			class VertexBuffer : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class VertexBufferDesc : public virtual GAIA::FWORK::InstanceDesc
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
			class VIEWPORT
			{
			public:
			};

		public:
			GAIA_ENUM_BEGIN(QUALITY3D_STATE)
				QUALITY3D_STATE_ANTIALIAS,
			GAIA_ENUM_END(QUALITY3D_STATE)

			GAIA_ENUM_BEGIN(RENDER3D_STATE)
				RENDER3D_STATE_ENABLEZTEST,
				RENDER3D_STATE_ENABLEZWRITE,
			GAIA_ENUM_END(RENDER3D_STATE)

			GAIA_ENUM_BEGIN(SAMPLER3D_STATE)
				SAMPLER3D_STATE_ADDRESSW,
				SAMPLER3D_STATE_MIPFILTER,
			GAIA_ENUM_END(SAMPLER3D_STATE)

			GAIA_ENUM_BEGIN(DRAW_TRIANGLE_TYPE)
				DRAW_TRIANGLE_TYPE_TRIANGLELIST,
				DRAW_TRIANGLE_TYPE_TRIANGLESTRIP,
				DRAW_TRIANGLE_TYPE_TRIANGLEFAN,
			GAIA_ENUM_END(DRAW_TRIANGLE_TYPE)

			GAIA_ENUM_BEGIN(INDEX_FORMAT_TYPE)
				INDEX_FORMAT_TYPE_16,
				INDEX_FORMAT_TYPE_32,
			GAIA_ENUM_END(INDEX_FORMAT_TYPE)

		public:
			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp) = 0;
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const = 0;

			/* State. */
			virtual GAIA::GVOID SetQuality3DState(const QUALITY3D_STATE& qs, const GAIA::CH* pszState) = 0;
			virtual const GAIA::CH* GetQuality3DState(const QUALITY3D_STATE& qs) = 0;
			virtual GAIA::GVOID SetRender3DState(const RENDER3D_STATE& rs, const GAIA::CH* pszState) = 0;
			virtual const GAIA::CH* GetRender3DState(const RENDER3D_STATE& rs) const = 0;
			virtual GAIA::GVOID SetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss, const GAIA::CH* pszState) = 0;
			virtual const GAIA::CH* GetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss) const = 0;

			/* Index buffer. */
			virtual GAIA::RENDER::Render3D::IndexBuffer* CreateIndexBuffer() = 0;
			virtual GAIA::GVOID SetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer* pIB) = 0;
			virtual GAIA::GVOID GetIndexBuffer(const GAIA::RENDER::Render3D::IndexBuffer*& pIB) const = 0;

			/* Vertex buffer. */
			virtual GAIA::RENDER::Render3D::VertexBuffer* CreateVertexBuffer() = 0;
			virtual GAIA::GVOID SetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer* pVB) = 0;
			virtual GAIA::GVOID GetVertexBuffer(GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer*& pVB) const = 0;

			/* Declaration. */
			virtual GAIA::RENDER::Render3D::VertexDeclaration* CreateVertexDeclaration() = 0;
			virtual GAIA::GVOID SetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration* pVDecl) = 0;
			virtual GAIA::GVOID GetVertexDeclaration(GAIA::RENDER::Render3D::VertexDeclaration*& pVDecl) = 0;

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